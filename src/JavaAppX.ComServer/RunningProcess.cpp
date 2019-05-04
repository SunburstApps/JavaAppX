#include "StdAfx.h"
#include "RunningProcess.h"

using namespace JdkComServer;

RunningProcess::~RunningProcess() {
	CloseHandle(hProcess);
	CloseHandle(hStdIn);
	CloseHandle(hStdOut);
	CloseHandle(hStdErr);
}

HRESULT RunningProcess::OpenStandardInput(DWORD destinationProcessId, LONG_PTR* handle) noexcept {
	if (hStdIn == nullptr) return E_INVALIDARG;
	if (hProcess == nullptr) return E_FAIL;

	HANDLE hDestinationProcess = OpenProcess(PROCESS_DUP_HANDLE, false, destinationProcessId);
	if (hDestinationProcess == INVALID_HANDLE_VALUE) return HRESULT_FROM_WIN32(GetLastError());

	BOOL success = DuplicateHandle(GetCurrentProcess(), this->hStdIn, hDestinationProcess, (LPHANDLE)handle, 0, false, 0);
	CloseHandle(hDestinationProcess);
	return success ? S_OK : E_UNEXPECTED;
}

HRESULT RunningProcess::OpenStandardOutput(DWORD destinationProcessId, LONG_PTR* handle) noexcept {
	if (hStdIn == nullptr) return E_INVALIDARG;
	if (hProcess == nullptr) return E_FAIL;

	HANDLE hDestinationProcess = OpenProcess(PROCESS_DUP_HANDLE, false, destinationProcessId);
	if (hDestinationProcess == INVALID_HANDLE_VALUE) return HRESULT_FROM_WIN32(GetLastError());

	BOOL success = DuplicateHandle(GetCurrentProcess(), this->hStdOut, hDestinationProcess, (LPHANDLE)handle, 0, false, 0);
	CloseHandle(hDestinationProcess);
	return success ? S_OK : E_UNEXPECTED;
}

HRESULT RunningProcess::OpenStandardError(DWORD destinationProcessId, LONG_PTR* handle) noexcept {
	if (hStdIn == nullptr) return E_INVALIDARG;
	if (hProcess == nullptr) return E_FAIL;

	HANDLE hDestinationProcess = OpenProcess(PROCESS_DUP_HANDLE, false, destinationProcessId);
	if (hDestinationProcess == INVALID_HANDLE_VALUE) return HRESULT_FROM_WIN32(GetLastError());

	BOOL success = DuplicateHandle(GetCurrentProcess(), this->hStdErr, hDestinationProcess, (LPHANDLE)handle, 0, false, 0);
	CloseHandle(hDestinationProcess);
	return success ? S_OK : E_UNEXPECTED;
}

HRESULT RunningProcess::get_ExitCode(INT* iExitCode) noexcept {
	DWORD exitCode;
	BOOL success = GetExitCodeProcess(hProcess, &exitCode);
	if (!success) return HRESULT_FROM_WIN32(GetLastError());

	if (exitCode == STILL_ACTIVE) return S_FALSE;
	*iExitCode = exitCode;
	return S_OK;
}

HRESULT RunningProcess::Kill(void) noexcept {
	BOOL success = TerminateProcess(hProcess, -1);
	return success ? S_OK : HRESULT_FROM_WIN32(GetLastError());
}

HRESULT RunningProcess::WaitForExit(void) noexcept {
	return WaitForExitTimeout(INFINITE);
}

HRESULT RunningProcess::WaitForExitTimeout(DWORD dwTimeoutMilliseconds) noexcept {
	WaitForSingleObject(hProcess, dwTimeoutMilliseconds);
	return S_OK;
}
