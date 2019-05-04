#pragma once

#include "JdkComServer_h.h"

namespace JdkComServer {
	class RunningProcess final : public winrt::implements<RunningProcess, IRunningProcess> {
	public:
		static_assert(sizeof(LONG_PTR) >= sizeof(HANDLE), "Handles will be truncated during IPC transport");
		HRESULT STDMETHODCALLTYPE OpenStandardInput(DWORD destinationProcessId, LONG_PTR* hStdIn) noexcept override;
		HRESULT STDMETHODCALLTYPE OpenStandardOutput(DWORD destinationProcessId, LONG_PTR* hStdOut) noexcept override;
		HRESULT STDMETHODCALLTYPE OpenStandardError(DWORD destinationProcessId, LONG_PTR* hStdErr) noexcept override;

		HRESULT STDMETHODCALLTYPE get_ExitCode(INT* iExitCode) noexcept override;
		HRESULT STDMETHODCALLTYPE Kill(void) noexcept override;
		HRESULT STDMETHODCALLTYPE WaitForExit(void) noexcept override;
		HRESULT STDMETHODCALLTYPE WaitForExitTimeout(DWORD ulTimeoutMilliseconds) noexcept override;

	public:
		RunningProcess(HANDLE hProcess, HANDLE hStdIn, HANDLE hStdOut, HANDLE hStdErr) :
			hProcess(hProcess), hStdIn(hStdIn), hStdOut(hStdOut), hStdErr(hStdErr) {}
		~RunningProcess();

	private:
		HANDLE hProcess;
		HANDLE hStdIn, hStdOut, hStdErr;
	};
}
