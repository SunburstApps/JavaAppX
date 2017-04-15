#include "stdafx.h"
#include "AppxJavaComLauncher_i.h"

class ATL_NO_VTABLE CRunningProcess :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRunningProcess>,
	public IRunningProcess
{
private:
	HANDLE hProcess;

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
	}

	virtual HRESULT STDMETHODCALLTYPE get_StandardInput(ISequentialStream **ppStream) { return E_NOTIMPL; }
	virtual HRESULT STDMETHODCALLTYPE get_StandardOutput(ISequentialStream **ppStream) { return E_NOTIMPL; }
	virtual HRESULT STDMETHODCALLTYPE get_StandardError(ISequentialStream **ppStream) { return E_NOTIMPL; }

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

	virtual HRESULT STDMETHODCALLTYPE Initialize(HANDLE hProcess)
	{
		if (hProcess == INVALID_HANDLE_VALUE) return E_INVALIDARG;
		if (this->hProcess != nullptr) return E_FAIL;
		this->hProcess = hProcess;
		return S_OK;
	}
};

HRESULT CRunningProcess_CreateInstance(CComPtr<IRunningProcess>& comObj, HANDLE hProcess)
{
	HRESULT hr = CRunningProcess::CreateInstance(&comObj);
	if (FAILED(hr)) return hr;

	hr = comObj->Initialize(hProcess);
	if (FAILED(hr)) return hr;

	return S_OK;
}
