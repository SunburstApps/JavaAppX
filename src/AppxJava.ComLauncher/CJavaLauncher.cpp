#include "stdafx.h"
#include "AppxJavaComLauncher_i.h"
#include <atlcoll.h>
#include <atlstr.h>

extern HRESULT CRunningProcess_Launch(CComPtr<IRunningProcess>& processPtr, LPWSTR commandLine, LPWSTR windowTitle, LPWSTR workingDirectory,
	const CAtlArray<CString>& environmentVariables, int nShowCmd, HANDLE hRecipientProcess);

class ATL_NO_VTABLE CJavaLauncher :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CJavaLauncher, &CLSID_JavaLauncher>,
	public IJavaLauncher
{
private:
	CComBSTR mWorkingDirectory = nullptr;
	CAtlArray<CString> mClassPath, mExtraJavaArguments, mProgramArguments, mEnvironmentVariables;

public:
	DECLARE_NOT_AGGREGATABLE(CJavaLauncher);
	DECLARE_PROTECT_FINAL_CONSTRUCT();

	BEGIN_COM_MAP(CJavaLauncher)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY(IJavaLauncher)
	END_COM_MAP()

	static HRESULT WINAPI UpdateRegistry(BOOL)
	{
		// This method is not used, but is required by ATL.
		return S_OK;
	}

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	virtual HRESULT STDMETHODCALLTYPE get_WorkingDirectory(BSTR *pstrWorkingDirectory)
	{
		if (pstrWorkingDirectory == nullptr) return E_NOTIMPL;
		*pstrWorkingDirectory = mWorkingDirectory.Copy();
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE put_WorkingDirectory(BSTR strWorkingDirectory)
	{
		mWorkingDirectory.AssignBSTR(strWorkingDirectory);
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE get_ClassPath(SAFEARRAY * *pClassPath)
	{
		if (pClassPath == nullptr) return E_INVALIDARG;

		LONG Count = mClassPath.GetCount();
		SAFEARRAYBOUND bound; bound.lLbound = 0; bound.cElements = Count;
		SAFEARRAY *psa = SafeArrayCreate(VT_BSTR, 1, &bound);

		for (LONG i = 0; i < Count; i++)
		{
			CComBSTR bstr = mClassPath.GetAt(i);
			SafeArrayPutElement(psa, &i, bstr.Detach());
		}

		*pClassPath = psa;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE put_ClassPath(SAFEARRAY * classPath)
	{
		if (classPath == nullptr) return E_INVALIDARG;
		CAtlArray<CString> oldValue; oldValue.Copy(mClassPath);
		
		VARTYPE vt = VT_NULL;
		HRESULT hr = SafeArrayGetVartype(classPath, &vt);
		if (FAILED(hr)) return hr;
		if (vt != VT_BSTR) return E_INVALIDARG;

		UINT dimensions = SafeArrayGetDim(classPath);
		if (dimensions != 1) return E_INVALIDARG;
		
		LONG lower, upper;
		hr = SafeArrayGetLBound(classPath, 0, &lower);
		if (FAILED(hr)) return hr;
		hr = SafeArrayGetUBound(classPath, 0, &upper);
		if (FAILED(hr)) return hr;
		if (lower != 0) return E_INVALIDARG;

		LONG length = upper - lower;
		mClassPath.RemoveAll();
		for (LONG i = 0; i < length; i++) {
			CComBSTR bstr;
			hr = SafeArrayGetElement(classPath, &i, &bstr);
			if (FAILED(hr)) goto failure;

			mClassPath.Add(bstr);
		}

		return S_OK;

	failure:
		// Don't leave the object in an inconsistent state.
		mClassPath.Copy(oldValue);
		return hr;
	}

	virtual HRESULT STDMETHODCALLTYPE get_ExtraJavaArguments(SAFEARRAY * *pExtraJavaArgv)
	{
		if (pExtraJavaArgv == nullptr) return E_INVALIDARG;

		LONG Count = mExtraJavaArguments.GetCount();
		SAFEARRAYBOUND bound; bound.lLbound = 0; bound.cElements = Count;
		SAFEARRAY *psa = SafeArrayCreate(VT_BSTR, 1, &bound);

		for (LONG i = 0; i < Count; i++)
		{
			CComBSTR bstr = mExtraJavaArguments.GetAt(i);
			SafeArrayPutElement(psa, &i, bstr.Detach());
		}

		*pExtraJavaArgv = psa;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE put_ExtraJavaArguments(SAFEARRAY * extraJavaArgv)
	{
		if (extraJavaArgv == nullptr) return E_INVALIDARG;
		CAtlArray<CString> oldValue; oldValue.Copy(mExtraJavaArguments);

		VARTYPE vt = VT_NULL;
		HRESULT hr = SafeArrayGetVartype(extraJavaArgv, &vt);
		if (FAILED(hr)) return hr;
		if (vt != VT_BSTR) return E_INVALIDARG;

		UINT dimensions = SafeArrayGetDim(extraJavaArgv);
		if (dimensions != 1) return E_INVALIDARG;

		LONG lower, upper;
		hr = SafeArrayGetLBound(extraJavaArgv, 0, &lower);
		if (FAILED(hr)) return hr;
		hr = SafeArrayGetUBound(extraJavaArgv, 0, &upper);
		if (FAILED(hr)) return hr;
		if (lower != 0) return E_INVALIDARG;

		LONG length = upper - lower;
		mClassPath.RemoveAll();
		for (LONG i = 0; i < length; i++) {
			CComBSTR bstr;
			hr = SafeArrayGetElement(extraJavaArgv, &i, &bstr);
			if (FAILED(hr)) goto failure;

			mExtraJavaArguments.Add(bstr);
		}

		return S_OK;

	failure:
		// Don't leave the object in an inconsistent state.
		mExtraJavaArguments.Copy(oldValue);
		return hr;
	}

	virtual HRESULT STDMETHODCALLTYPE get_ProgramArguments(SAFEARRAY * *pArgv)
	{
		if (pArgv == nullptr) return E_INVALIDARG;

		LONG Count = mProgramArguments.GetCount();
		SAFEARRAYBOUND bound; bound.lLbound = 0; bound.cElements = Count;
		SAFEARRAY *psa = SafeArrayCreate(VT_BSTR, 1, &bound);

		for (LONG i = 0; i < Count; i++)
		{
			CComBSTR bstr = mProgramArguments.GetAt(i);
			SafeArrayPutElement(psa, &i, bstr.Detach());
		}

		*pArgv = psa;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE put_ProgramArguments(SAFEARRAY * argv)
	{
		if (argv == nullptr) return E_INVALIDARG;
		CAtlArray<CString> oldValue; oldValue.Copy(mProgramArguments);

		VARTYPE vt = VT_NULL;
		HRESULT hr = SafeArrayGetVartype(argv, &vt);
		if (FAILED(hr)) return hr;
		if (vt != VT_BSTR) return E_INVALIDARG;

		UINT dimensions = SafeArrayGetDim(argv);
		if (dimensions != 1) return E_INVALIDARG;

		LONG lower, upper;
		hr = SafeArrayGetLBound(argv, 0, &lower);
		if (FAILED(hr)) return hr;
		hr = SafeArrayGetUBound(argv, 0, &upper);
		if (FAILED(hr)) return hr;
		if (lower != 0) return E_INVALIDARG;

		LONG length = upper - lower;
		mClassPath.RemoveAll();
		for (LONG i = 0; i < length; i++) {
			CComBSTR bstr;
			hr = SafeArrayGetElement(argv, &i, &bstr);
			if (FAILED(hr)) goto failure;

			mProgramArguments.Add(bstr);
		}

		return S_OK;

	failure:
		// Don't leave the object in an inconsistent state.
		mProgramArguments.Copy(oldValue);
		return hr;
	}

	virtual HRESULT STDMETHODCALLTYPE get_EnvironmentVariables(SAFEARRAY * *pEnvironmentVariables)
	{
		if (pEnvironmentVariables == nullptr) return E_INVALIDARG;

		LONG Count = mEnvironmentVariables.GetCount();
		SAFEARRAYBOUND bound; bound.lLbound = 0; bound.cElements = Count;
		SAFEARRAY *psa = SafeArrayCreate(VT_BSTR, 1, &bound);

		for (LONG i = 0; i < Count; i++)
		{
			CComBSTR bstr = mEnvironmentVariables.GetAt(i);
			SafeArrayPutElement(psa, &i, bstr.Detach());
		}

		*pEnvironmentVariables = psa;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE put_EnvironmentVariables(SAFEARRAY * environmentVariables)
	{
		if (environmentVariables == nullptr) return E_INVALIDARG;
		CAtlArray<CString> oldValue; oldValue.Copy(mEnvironmentVariables);

		VARTYPE vt = VT_NULL;
		HRESULT hr = SafeArrayGetVartype(environmentVariables, &vt);
		if (FAILED(hr)) return hr;
		if (vt != VT_BSTR) return E_INVALIDARG;

		UINT dimensions = SafeArrayGetDim(environmentVariables);
		if (dimensions != 1) return E_INVALIDARG;

		LONG lower, upper;
		hr = SafeArrayGetLBound(environmentVariables, 0, &lower);
		if (FAILED(hr)) return hr;
		hr = SafeArrayGetUBound(environmentVariables, 0, &upper);
		if (FAILED(hr)) return hr;
		if (lower != 0) return E_INVALIDARG;

		LONG length = upper - lower;
		mClassPath.RemoveAll();
		for (LONG i = 0; i < length; i++) {
			CComBSTR bstr;
			hr = SafeArrayGetElement(environmentVariables, &i, &bstr);
			if (FAILED(hr)) goto failure;

			mEnvironmentVariables.Add(bstr);
		}

		return S_OK;

	failure:
		// Don't leave the object in an inconsistent state.
		mEnvironmentVariables.Copy(oldValue);
		return hr;
	}

	virtual HRESULT STDMETHODCALLTYPE LaunchClass(BSTR className, JAVA_LAUNCH_STYLE launchStyle, DWORD callerProcessId, IRunningProcess **pProcess)
	{
		if (pProcess == nullptr) return E_INVALIDARG;
		if (launchStyle < JAVA_LAUNCH_STYLE_BACKGROUND || launchStyle > JAVA_LAUNCH_STYLE_GUI) return E_INVALIDARG;

		CString processArgv;
		if (launchStyle == JAVA_LAUNCH_STYLE_GUI) processArgv += L"\"C:\\Program Files\\OpenJDK\\bin\\javaw.exe\"";
		else processArgv += L"\"C:\\Program Files\\OpenJDK\\bin\\java.exe\"";
		processArgv += L" ";

		if (mClassPath.GetCount() != 0) {
			processArgv += L"-cp \"";
			bool firstTime = true;

			DWORD limit = mClassPath.GetCount();
			for (DWORD i = 0; i < limit; i++) {
				if (firstTime) firstTime = false;
				else processArgv += mClassPath[i];
			}
		}
		processArgv += L"\" ";

		if (mExtraJavaArguments.GetCount() != 0) {
			DWORD limit = mExtraJavaArguments.GetCount();
			for (DWORD i = 0; i < limit; i++) {
				processArgv += L"\"";
				processArgv += mExtraJavaArguments.GetAt(i);
				processArgv += L"\" ";
			}
		}

		processArgv += className;
		if (mProgramArguments.GetCount() != 0) {
			processArgv += L" ";
			DWORD limit = mProgramArguments.GetCount();
			for (DWORD i = 0; i < limit; i++) {
				processArgv += L"\"";
				processArgv += mProgramArguments.GetAt(i);
				processArgv += L"\" ";
			}
		}

		int nShowCmd = SW_SHOWNORMAL;
		if (launchStyle == JAVA_LAUNCH_STYLE_BACKGROUND) nShowCmd = SW_HIDE;

		HANDLE recipientProcess = OpenProcess(PROCESS_DUP_HANDLE, false, callerProcessId);
		if (recipientProcess == INVALID_HANDLE_VALUE) return HRESULT_FROM_WIN32(GetLastError());

		CComPtr<IRunningProcess> processPtr;
		HRESULT hr = CRunningProcess_Launch(processPtr, (LPWSTR)processArgv.GetString(), L"OpenJDK", mWorkingDirectory, mEnvironmentVariables, nShowCmd, recipientProcess);
		if (SUCCEEDED(hr)) *pProcess = processPtr.Detach();
		return hr;
	}

	virtual HRESULT STDMETHODCALLTYPE LaunchJarFile(BSTR jarPath, JAVA_LAUNCH_STYLE launchStyle, DWORD callerProcessId, IRunningProcess **pProcess)
	{
		if (pProcess == nullptr) return E_INVALIDARG;
		if (launchStyle < JAVA_LAUNCH_STYLE_BACKGROUND || launchStyle > JAVA_LAUNCH_STYLE_GUI) return E_INVALIDARG;

		CString processArgv;
		if (launchStyle == JAVA_LAUNCH_STYLE_GUI) processArgv += L"\"C:\\Program Files\\OpenJDK\\bin\\javaw.exe\"";
		else processArgv += L"\"C:\\Program Files\\OpenJDK\\bin\\java.exe\"";
		processArgv += L" ";

		if (mClassPath.GetCount() != 0) {
			processArgv += L"-cp \"";
			bool firstTime = true;

			DWORD limit = mClassPath.GetCount();
			for (DWORD i = 0; i < limit; i++) {
				if (firstTime) firstTime = false;
				else processArgv += mClassPath[i];
			}
		}
		processArgv += L"\" ";

		if (mExtraJavaArguments.GetCount() != 0) {
			DWORD limit = mExtraJavaArguments.GetCount();
			for (DWORD i = 0; i < limit; i++) {
				processArgv += L"\"";
				processArgv += mExtraJavaArguments.GetAt(i);
				processArgv += L"\" ";
			}
		}

		processArgv += L"-jar \"";
		processArgv += jarPath;
		processArgv += L"\"";

		if (mProgramArguments.GetCount() != 0) {
			processArgv += L" ";
			DWORD limit = mProgramArguments.GetCount();
			for (DWORD i = 0; i < limit; i++) {
				processArgv += L"\"";
				processArgv += mProgramArguments.GetAt(i);
				processArgv += L"\" ";
			}
		}

		int nShowCmd = SW_SHOWNORMAL;
		if (launchStyle == JAVA_LAUNCH_STYLE_BACKGROUND) nShowCmd = SW_HIDE;

		HANDLE recipientProcess = OpenProcess(PROCESS_DUP_HANDLE, false, callerProcessId);
		if (recipientProcess == INVALID_HANDLE_VALUE) return HRESULT_FROM_WIN32(GetLastError());

		CComPtr<IRunningProcess> processPtr;
		HRESULT hr = CRunningProcess_Launch(processPtr, (LPWSTR)processArgv.GetString(), L"OpenJDK", mWorkingDirectory, mEnvironmentVariables, nShowCmd, recipientProcess);
		if (SUCCEEDED(hr)) *pProcess = processPtr.Detach();
		CloseHandle(recipientProcess);
		return hr;
	}
};

OBJECT_ENTRY_AUTO(CLSID_JavaLauncher, CJavaLauncher);
