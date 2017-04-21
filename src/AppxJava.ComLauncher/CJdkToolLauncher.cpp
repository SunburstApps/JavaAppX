#include "stdafx.h"
#include "AppxJavaComLauncher_i.h"
#include <atlstr.h>
#include <atlcoll.h>

extern HRESULT CRunningProcess_Launch(CComPtr<IRunningProcess>& processPtr, LPWSTR commandLine, LPWSTR windowTitle, LPWSTR workingDirectory,
	const CAtlArray<CString>& environmentVariables, int nShowCmd, HANDLE hRecipientProcess);

class ATL_NO_VTABLE CJdkToolLauncher :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<JdkToolLauncher, &CLSID_JdkToolLauncher>,
	public IJdkToolLauncher
{
private:
	JDK_TOOL mToolName;
	CComBSTR mWorkingDirectory;
	CAtlArray<CString> mProgramArguments, mEnvironmentVariables;

public:
	DECLARE_NOT_AGGREGATABLE(CJdkToolLauncher);
	DECLARE_PROTECT_FINAL_CONSTRUCT();

	BEGIN_COM_MAP(CJdkToolLauncher)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY(IJdkToolLauncher)
	END_COM_MAP()

	static HRESULT WINAPI UpdateRegistry(BOOL)
	{
		// This method is not used, but is required by ATL.
		return S_OK;
	}

	HRESULT FinalConstruct()
	{
		mToolName = JDK_TOOL_JAVA_COMPILER;
		mWorkingDirectory = nullptr;
		mProgramArguments.RemoveAll();
		mEnvironmentVariables.RemoveAll();

		return S_OK;
	}

	void FinalRelease()
	{
	}

	virtual HRESULT STDMETHODCALLTYPE get_ToolName(JDK_TOOL *pTool) {
		if (pTool == nullptr) return E_INVALIDARG;
		*pTool = mToolName;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE put_ToolName(JDK_TOOL tool) {
		if (tool < JDK_TOOL_JAVA_COMPILER || tool > JDK_TOOL_JAXB_BINDING_COMPILER) return E_INVALIDARG;
		mToolName = tool;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE get_WorkingDirectory(BSTR *pstrWorkingDirectory)
	{
		if (pstrWorkingDirectory == nullptr) return E_NOTIMPL;
		return mWorkingDirectory.CopyTo(pstrWorkingDirectory);
	}

	virtual HRESULT STDMETHODCALLTYPE put_WorkingDirectory(BSTR strWorkingDirectory)
	{
		mWorkingDirectory.AssignBSTR(strWorkingDirectory);
		return S_OK;
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
		mEnvironmentVariables.RemoveAll();
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
		mEnvironmentVariables.RemoveAll();
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

	virtual HRESULT STDMETHODCALLTYPE Launch(JAVA_LAUNCH_STYLE launchStyle, DWORD callerProcessId, IRunningProcess **pProcess)
	{
		if (pProcess == nullptr) return E_INVALIDARG;
		if (launchStyle < JAVA_LAUNCH_STYLE_BACKGROUND || launchStyle > JAVA_LAUNCH_STYLE_GUI) return E_INVALIDARG;
		if (launchStyle == JAVA_LAUNCH_STYLE_GUI) return E_INVALIDARG;

		CString processFileName, processTitle;
		switch (mToolName) {
		case JDK_TOOL_JAVA_COMPILER:
			processFileName = "javac.exe";
			processTitle = "Java Compiler";
			break;

		case JDK_TOOL_APPLETVIEWER:
			processFileName = "appletviewer.exe";
			processTitle = "OpenJDK Applet Viewer";
			break;

		case JDK_TOOL_EXTCHECK:
			processFileName = "extcheck.exe";
			processTitle = "OpenJDK Extcheck";
			break;

		case JDK_TOOL_IDL_TO_JAVA_COMPILER:
			processFileName = "idlj.exe";
			processTitle = "OpenJDK IDL-to-Java Compiler";
			break;

		case JDK_TOOL_JAR_ARCHIVER:
			processFileName = "jar.exe";
			processTitle = "OpenJDK JAR Utility";
			break;

		case JDK_TOOL_JAR_SIGNER:
			processFileName = "jarsigner.exe";
			processTitle = "OpenJDK JAR Signer";
			break;

		case JDK_TOOL_JAVA_DOCUMENTATION_GENERATOR:
			processFileName = "javadoc.exe";
			processTitle = "OpenJDK Documentation Processor";
			break;

		case JDK_TOOL_JNI_HEADER_GENERATOR:
			processFileName = "javah.exe";
			processTitle = "JNI Header Generator";
			break;

		case JDK_TOOL_JAVA_DISASSEMBLER:
			processFileName = "javap.exe";
			processTitle = "OpenJDK Disassembler";
			break;

		case JDK_TOOL_JAVA_RMI_RUNNER:
			processFileName = "java-rmi.exe";
			processTitle = "OpenJDK RMI Runner";
			break;

		case JDK_TOOL_JCMD:
			processFileName = "jcmd.exe";
			processTitle = "OpenJDK JCmd";
			break;

		case JDK_TOOL_JCONSOLE:
			processFileName = "jconsole.exe";
			processTitle = "OpenJDK JConsole";
			break;

		case JDK_TOOL_JAVA_DEBUGGER:
			processFileName = "jdb.exe";
			processTitle = "OpenJDK Debugger";
			break;

		case JDK_TOOL_DEPENDENCY_GRAPH_GENERATOR:
			processFileName = "jdeps.exe";
			processTitle = "OpenJDK Class Dependency Graph Generator";
			break;

		case JDK_TOOL_JHAT:
			processFileName = "jhat.exe";
			processTitle = "OpenJDK JHat";
			break;

		case JDK_TOOL_JVM_INTROSPECTION_UTILITY:
			processFileName = "jinfo.exe";
			processTitle = "OpenJDK JVM Introspection Utility";
			break;

		case JDK_TOOL_JAVA_SCRIPT_RUNNER:
			processFileName = "jjs.exe";
			processTitle = "OpenJDK JavaScript Runner";
			break;

		case JDK_TOOL_JVM_MEMORY_DUMP_UTILITY:
			processFileName = "jmap.exe";
			processTitle = "OpenJDK JVM Memory Dump Utility";
			break;

		case JDK_TOOL_JPS:
			processFileName = "jps.exe";
			processTitle = "OpenJDK JPS";
			break;

		case JDK_TOOL_JRUNSCRIPT:
			processFileName = "jrunscript.exe";
			processTitle = "OpenJDK JRunScript";
			break;

		case JDK_TOOL_JSADEBUG_DAEMON:
			processFileName = "jsadebugd.exe";
			processTitle = "OpenJDK JSA Debug Daemon";
			break;

		case JDK_TOOL_JAVA_STACK_DUMPER:
			processFileName = "jstack.exe";
			processTitle = "OpenJDK Java Stack Dump Utility";
			break;

		case JDK_TOOL_JVM_SAMPLER:
			processFileName = "jstat.exe";
			processTitle = "OpenJDK JVM Sampler";
			break;

		case JDK_TOOL_JSTAT_DAEMON:
			processFileName = "jstatd.exe";
			processTitle = "OpenJDK JStat Daemon";
			break;

		case JDK_TOOL_KEY_AND_CERT_MANAGER:
			processFileName = "keytool.exe";
			processTitle = "OpenJDK Key & Certificate Manager";
			break;

		case JDK_TOOL_KERBEROS_KINIT:
			processFileName = "kinit.exe";
			processTitle = "OpenJDK Kerberos KInit Tool";
			break;

		case JDK_TOOL_KERBEROS_KLIST:
			processFileName = "klist.exe";
			processTitle = "OpenJDK Kerberos KList Tool";
			break;

		case JDK_TOOL_KERBEROS_KTAB:
			processFileName = "ktab.exe";
			processTitle = "OpenJDK Kerberos KTab Tool";
			break;

		case JDK_TOOL_NATIVE2ASCII:
			processFileName = "native2ascii.exe";
			processTitle = "OpenJDK Character Set Conversion Utility";
			break;
			
		case JDK_TOOL_ORB_DAEMON:
			processFileName = "orbd.exe";
			processTitle = "OpenJDK Orb Daemon";
			break;

		case JDK_TOOL_PACK200:
			processFileName = "pack200.exe";
			processTitle = "OpenJDK Pack200 Tool";
			break;

		case JDK_TOOL_POLICY_TOOL:
			processFileName = "policytool.exe";
			processTitle = "OpenJDK Policy Tool";
			break;

		case JDK_TOOL_RMI_COMPILER:
			processFileName = "rmic.exe";
			processTitle = "OpenJDK RMI Compiler";
			break;

		case JDK_TOOL_RMI_DAEMON:
			processFileName = "rmid.exe";
			processTitle = "OpenJDK RMI Daemon";
			break;

		case JDK_TOOL_RMI_REGISTRY_TOOL:
			processFileName = "rmiregistry.exe";
			processTitle = "OpenJDK RMI Registry Utility";
			break;

		case JDK_TOOL_SCHEMA_GENERATOR:
			processFileName = "schemagen.exe";
			processTitle = "OpenJDK Schema Generator";
			break;

		case JDK_TOOL_SERIAL_VERSION_UTILITY:
			processFileName = "serialver.exe";
			processTitle = "OpenJDK Serial Version Utility";
			break;

		case JDK_TOOL_SERVER_TOOL:
			processFileName = "servertool.exe";
			processTitle = "OpenJDK Server Tool";
			break;

		case JDK_TOOL_TNAME_SERVICE:
			processFileName = "tnameserv.exe";
			processTitle = "OpenJDK TName Service";
			break;

		case JDK_TOOL_UNPACK200:
			processFileName = "unpack200.exe";
			processTitle = "OpenJDK Unpack200 Tool";
			break;

		case JDK_TOOL_WSDL_GENERATOR:
			processFileName = "wsgen.exe";
			processTitle = "OpenJDK WSDL Generator";
			break;

		case JDK_TOOL_WSDL_IMPORTER:
			processFileName = "wsimport.exe";
			processTitle = "OpenJDK WSDL Importer";
			break;

		case JDK_TOOL_JAXB_BINDING_COMPILER:
			processFileName = "xjc.exe";
			processTitle = "OpenJDK JAXB Binding Compiler";
			break;
			
		default:
			return E_INVALIDARG;
		}

		CString processArgv;
		processArgv += L"\"C:\\Program Files\\OpenJDK\\bin\\" + processFileName + L"\" ";

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
		HRESULT hr = CRunningProcess_Launch(processPtr, (LPWSTR)processArgv.GetString(), (LPWSTR)processTitle.GetString(), mWorkingDirectory, mEnvironmentVariables, nShowCmd, recipientProcess);
		if (SUCCEEDED(hr)) *pProcess = processPtr.Detach();
		return hr;
	}
};

OBJECT_ENTRY_AUTO(CLSID_JdkToolLauncher, CJdkToolLauncher);
