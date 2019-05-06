#pragma once

#include "JdkComServer_h.h"

namespace JdkComServer {
	class JavaLauncher final : public winrt::implements<JavaLauncher, IJavaLauncher> {
	private:
		std::wstring workingDirectory;
		std::vector<std::wstring> classPath;
		std::vector<std::wstring> extraJavaArgv;
		std::vector<std::wstring> programArgv;
		std::vector<std::wstring> environment;

	public:
		virtual HRESULT STDMETHODCALLTYPE get_WorkingDirectory(BSTR* pstrWorkingDirectory) noexcept override;
		virtual HRESULT STDMETHODCALLTYPE put_WorkingDirectory(BSTR strWorkingDirectory) noexcept override;
		virtual HRESULT STDMETHODCALLTYPE get_ClassPath(SAFEARRAY** pClassPath) noexcept override;
		virtual HRESULT STDMETHODCALLTYPE put_ClassPath(SAFEARRAY* classPath) noexcept override;
		virtual HRESULT STDMETHODCALLTYPE get_ExtraJavaArguments(SAFEARRAY** pClassPath) noexcept override;
		virtual HRESULT STDMETHODCALLTYPE put_ExtraJavaArguments(SAFEARRAY* classPath) noexcept override;
		virtual HRESULT STDMETHODCALLTYPE get_ProgramArguments(SAFEARRAY** pClassPath) noexcept override;
		virtual HRESULT STDMETHODCALLTYPE put_ProgramArguments(SAFEARRAY* classPath) noexcept override;
		virtual HRESULT STDMETHODCALLTYPE get_EnvironmentVariables(SAFEARRAY** pClassPath) noexcept override;
		virtual HRESULT STDMETHODCALLTYPE put_EnvironmentVariables(SAFEARRAY* classPath) noexcept override;

		virtual HRESULT STDMETHODCALLTYPE LaunchClass(BSTR className, JAVA_LAUNCH_STYLE launchStyle, IRunningProcess** pProcess);
		virtual HRESULT STDMETHODCALLTYPE LaunchJarFile(BSTR jarPath, JAVA_LAUNCH_STYLE launchStyle, IRunningProcess** pProcess);
	};
}