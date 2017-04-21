#include "stdafx.h"
#include "AppxJavaComLauncher_i.h"
#include <atlcoll.h>
#include <atlstr.h>

class ATL_NO_VTABLE CRunningProcess :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRunningProcess>,
	public IRunningProcess
{
private:
	HANDLE hProcess, hStdInStream, hStdOutStream, hStdErrStream;

public:
	DECLARE_NOT_AGGREGATABLE(CRunningProcess)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CRunningProcess)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY(IRunningProcess)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
		if (hProcess != nullptr) CloseHandle(hProcess);
		if (hStdInStream != nullptr) CloseHandle(hStdInStream);
		if (hStdOutStream != nullptr) CloseHandle(hStdOutStream);
		if (hStdErrStream != nullptr) CloseHandle(hStdErrStream);
	}

	static_assert(sizeof(LONG_PTR) == sizeof(HANDLE), "I/O handles would be truncated during IPC");
	virtual HRESULT STDMETHODCALLTYPE get_StandardInput(LONG_PTR *hStdIn)
	{
		if (hStdIn == nullptr) return E_INVALIDARG;
		*hStdIn = (LONG_PTR) hStdInStream;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE get_StandardOutput(LONG_PTR *hStdOut)
	{
		if (hStdOut == nullptr) return E_INVALIDARG;
		*hStdOut = (LONG_PTR)hStdOutStream;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE get_StandardError(LONG_PTR *hStdErr)
	{
		if (hStdErr == nullptr) return E_INVALIDARG;
		*hStdErr = (LONG_PTR)hStdErrStream;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE get_HasExited(VARIANT_BOOL *bExited)
	{
		if (hProcess == nullptr) return E_HANDLE;
		if (bExited == nullptr) return E_INVALIDARG;

		DWORD exitCode;
		BOOL success = GetExitCodeProcess(hProcess, &exitCode);
		if (!success) return HRESULT_FROM_WIN32(GetLastError());

		bool processAlive = (exitCode == STILL_ACTIVE);
		*bExited = processAlive ? VARIANT_FALSE : VARIANT_TRUE;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE get_ExitCode(INT *iExitCode)
	{
		if (hProcess == nullptr) return E_HANDLE;
		if (iExitCode == nullptr) return E_INVALIDARG;

		DWORD exitCode;
		BOOL success = GetExitCodeProcess(hProcess, &exitCode);
		if (!success) return HRESULT_FROM_WIN32(GetLastError());
		
		if (exitCode == STILL_ACTIVE) return E_PENDING;
		
		*iExitCode = exitCode;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Kill(void)
	{
		if (hProcess == nullptr) return E_HANDLE;

		BOOL success = TerminateProcess(hProcess, -1);
		if (!success) return HRESULT_FROM_WIN32(GetLastError());
		else return S_OK;
	}
	
	virtual HRESULT STDMETHODCALLTYPE WaitForExit(DWORD ulTimeoutMillisconds)
	{
		if (hProcess == nullptr) return E_HANDLE;

		DWORD retval = WaitForSingleObject(hProcess, ulTimeoutMillisconds);
		if (retval == WAIT_OBJECT_0) return S_OK;
		else if (retval == WAIT_TIMEOUT) return S_FALSE;
		else return HRESULT_FROM_WIN32(GetLastError());
	}

	virtual HRESULT STDMETHODCALLTYPE WaitForExitIndefinite(void)
	{
		return WaitForExit(INFINITE);
	}

	virtual HRESULT STDMETHODCALLTYPE Initialize(HANDLE hProcess, HANDLE hStdIn, HANDLE hStdOut, HANDLE hStdErr)
	{
		if (hProcess == INVALID_HANDLE_VALUE) return E_INVALIDARG;
		if (this->hProcess != nullptr) return E_FAIL;
		this->hProcess = hProcess;
		this->hStdInStream = hStdIn;
		this->hStdOutStream = hStdOut;
		this->hStdErrStream = hStdErr;
		return S_OK;
	}
};

HRESULT CRunningProcess_CreateInstance(CComPtr<IRunningProcess>& comObj, HANDLE hProcess, HANDLE hStdIn, HANDLE hStdOut, HANDLE hStdErr)
{
	HRESULT hr = CRunningProcess::CreateInstance(&comObj);
	if (FAILED(hr)) return hr;

	hr = comObj->Initialize(hProcess, hStdIn, hStdOut, hStdErr);
	if (FAILED(hr)) return hr;

	return S_OK;
}

class CEnvironmentVariableBlock
{
public:
	CAtlMap<CString, CString> Variables;

	void SetToCurrent() {
		LPWCH envBlock = GetEnvironmentStrings();
		CString currentKey, currentValue;
		bool seenWholeKey = false;

		DWORD index = 0;
		while (true) {
			if (envBlock[index] == L'=') {
				seenWholeKey = true;
			}
			else if (envBlock[index] == L'\0') {
				// If an equals sign was not seen, or if the environment variable name is an empty string,
				// treat this entry as malformed and ignore it.
				if (seenWholeKey && !currentKey.IsEmpty()) {
					Variables[currentKey] = currentValue;
				}

				currentKey.Empty();
				currentValue.Empty();
				seenWholeKey = false;

				if (envBlock[index + 1] == L'\0') {
					// The environment block is terminated by two consecutive NUL characters.
					break;
				}
			}
			else {
				if (seenWholeKey) currentValue.AppendChar(envBlock[index]);
				else currentKey.AppendChar(envBlock[index]);
			}
		}

		FreeEnvironmentStrings(envBlock);
	}

	BSTR CreateBlockBSTR() {
		CComBSTR bstr;

		POSITION pos = Variables.GetStartPosition();
		while (pos != nullptr) {
			auto pair = Variables.GetNext(pos);
			bstr.Append(pair->m_key);
			bstr.Append(L'=');
			bstr.Append(pair->m_value);
			bstr.Append(L'\0');
		}

		bstr.Append(L'\0');
		return bstr;
	}
};

#define CloseHandleSafe(handle) do { if (handle != INVALID_HANDLE_VALUE) CloseHandle(handle); } while (0)
#define CloseDuplicatedHandle(handle, hProcess) do { if (handle != INVALID_HANDLE_VALUE) DuplicateHandle(hProcess, handle, nullptr, nullptr, 0, false, DUPLICATE_CLOSE_SOURCE); } while (0)

HRESULT CRunningProcess_Launch(CComPtr<IRunningProcess>& processPtr, LPWSTR commandLine, LPWSTR windowTitle, LPWSTR workingDirectory,
	const CAtlArray<CString>& environmentVariables, int nShowCmd, HANDLE hRecipientProcess)
{
	CEnvironmentVariableBlock envBlock; envBlock.SetToCurrent();
	DWORD envVarCount = environmentVariables.GetCount();
	for (DWORD i = 0; i < envVarCount; i++) {
		const CString& var = environmentVariables[i];
		int equalsPos = var.Find(L"=", 0);
		envBlock.Variables[var.Left(equalsPos - 1)] = var.Right(var.GetLength() - equalsPos);
	}

	HRESULT hr = E_FAIL;
	DWORD dwError = 0;

	STARTUPINFO startupInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	startupInfo.lpTitle = windowTitle;
	startupInfo.wShowWindow = nShowCmd;
	startupInfo.dwFlags = STARTF_USESHOWWINDOW;

	SECURITY_ATTRIBUTES secAttrs;
	ZeroMemory(&secAttrs, sizeof(secAttrs));
	secAttrs.nLength = sizeof(secAttrs);
	secAttrs.bInheritHandle = TRUE;
	secAttrs.lpSecurityDescriptor = nullptr;

	HANDLE hStdInRead = INVALID_HANDLE_VALUE, hStdInWrite = INVALID_HANDLE_VALUE;
	if (!CreatePipe(&hStdInRead, &hStdInWrite, &secAttrs, 0)) {
		dwError = GetLastError();
		goto failure;
	}

	if (!SetHandleInformation(hStdInWrite, HANDLE_FLAG_INHERIT, 0)) {
		dwError = GetLastError();
		goto failure;
	}

	HANDLE hStdOutRead = INVALID_HANDLE_VALUE, hStdOutWrite = INVALID_HANDLE_VALUE;
	if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &secAttrs, 0)) {
		dwError = GetLastError();
		goto failure;
	}

	if (!SetHandleInformation(hStdOutRead, HANDLE_FLAG_INHERIT, 0)) {
		dwError = GetLastError();
		goto failure;
	}

	HANDLE hStdErrRead = INVALID_HANDLE_VALUE, hStdErrWrite = INVALID_HANDLE_VALUE;
	if (!CreatePipe(&hStdErrRead, &hStdErrWrite, &secAttrs, 0)) {
		dwError = GetLastError();
		goto failure;
	}

	if (!SetHandleInformation(hStdErrRead, HANDLE_FLAG_INHERIT, 0)) {
		dwError = GetLastError();
		goto failure;
	}

	startupInfo.hStdInput = hStdInRead;
	startupInfo.hStdOutput = hStdOutWrite;
	startupInfo.hStdError = hStdErrWrite;
	startupInfo.dwFlags |= STARTF_USESTDHANDLES;

	PROCESS_INFORMATION processInfo;
	ZeroMemory(&processInfo, sizeof(processInfo));
	processInfo.hProcess = processInfo.hThread = INVALID_HANDLE_VALUE;
	BOOL success = CreateProcess(nullptr, commandLine, nullptr, nullptr, true, CREATE_SUSPENDED | CREATE_UNICODE_ENVIRONMENT, envBlock.CreateBlockBSTR(), workingDirectory, &startupInfo, &processInfo);
	if (!success) {
		dwError = GetLastError();
		goto failure;
	}

	HANDLE currentProcess = GetCurrentProcess();
	HANDLE hStdInDuplicated = INVALID_HANDLE_VALUE, hStdOutDuplicated = INVALID_HANDLE_VALUE, hStdErrDuplicated = INVALID_HANDLE_VALUE;

	if (!DuplicateHandle(currentProcess, hStdInWrite, hRecipientProcess, &hStdInDuplicated, 0, false, DUPLICATE_SAME_ACCESS)) {
		dwError = GetLastError();
		goto failure;
	}

	if (!DuplicateHandle(currentProcess, hStdOutRead, hRecipientProcess, &hStdOutDuplicated, 0, false, DUPLICATE_SAME_ACCESS)) {
		dwError = GetLastError();
		goto failure;
	}

	if (!DuplicateHandle(currentProcess, hStdErrRead, hRecipientProcess, &hStdErrDuplicated, 0, false, DUPLICATE_SAME_ACCESS)) {
		dwError = GetLastError();
		goto failure;
	}

	hr = CRunningProcess_CreateInstance(processPtr, processInfo.hProcess, hStdInDuplicated, hStdOutDuplicated, hStdErrDuplicated);
	if (FAILED(hr)) goto failure;

	// Only resume the process once the object to monitor it has been created.
	ResumeThread(processInfo.hThread);
	goto cleanup;

failure:
	// Since the caller cannot monitor the process, it is best to kill it instead.
	TerminateProcess(processInfo.hProcess, EXIT_FAILURE);
	if (processInfo.hProcess != INVALID_HANDLE_VALUE) CloseHandle(processInfo.hProcess);
	hr = HRESULT_FROM_WIN32(dwError);

cleanup:
	CloseHandleSafe(hStdInRead);
	CloseHandleSafe(hStdInWrite);
	CloseHandleSafe(hStdOutRead);
	CloseHandleSafe(hStdOutWrite);
	CloseHandleSafe(hStdErrRead);
	CloseHandleSafe(hStdErrWrite);
	CloseHandleSafe(processInfo.hThread);
	CloseDuplicatedHandle(hStdInDuplicated, currentProcess);
	CloseDuplicatedHandle(hStdOutDuplicated, currentProcess);
	CloseDuplicatedHandle(hStdErrDuplicated, currentProcess);

	return hr;
}
