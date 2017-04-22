

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 22:14:07 2038
 */
/* Compiler settings for d:\wjk01\Documents\Visual Studio 2017\Projects\JavaAppX\src\AppxJava.ComLauncher\AppxJavaComLauncher.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AppxJavaComLauncher_h__
#define __AppxJavaComLauncher_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IRunningProcess_FWD_DEFINED__
#define __IRunningProcess_FWD_DEFINED__
typedef interface IRunningProcess IRunningProcess;

#endif 	/* __IRunningProcess_FWD_DEFINED__ */


#ifndef __IJavaLauncher_FWD_DEFINED__
#define __IJavaLauncher_FWD_DEFINED__
typedef interface IJavaLauncher IJavaLauncher;

#endif 	/* __IJavaLauncher_FWD_DEFINED__ */


#ifndef __IJdkToolLauncher_FWD_DEFINED__
#define __IJdkToolLauncher_FWD_DEFINED__
typedef interface IJdkToolLauncher IJdkToolLauncher;

#endif 	/* __IJdkToolLauncher_FWD_DEFINED__ */


#ifndef __JavaLauncher_FWD_DEFINED__
#define __JavaLauncher_FWD_DEFINED__

#ifdef __cplusplus
typedef class JavaLauncher JavaLauncher;
#else
typedef struct JavaLauncher JavaLauncher;
#endif /* __cplusplus */

#endif 	/* __JavaLauncher_FWD_DEFINED__ */


#ifndef __JdkToolLauncher_FWD_DEFINED__
#define __JdkToolLauncher_FWD_DEFINED__

#ifdef __cplusplus
typedef class JdkToolLauncher JdkToolLauncher;
#else
typedef struct JdkToolLauncher JdkToolLauncher;
#endif /* __cplusplus */

#endif 	/* __JdkToolLauncher_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IRunningProcess_INTERFACE_DEFINED__
#define __IRunningProcess_INTERFACE_DEFINED__

/* interface IRunningProcess */
/* [object][uuid] */ 


EXTERN_C const IID IID_IRunningProcess;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05E694E8-D211-4D1C-9DCB-D42B9C6E74C7")
    IRunningProcess : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_StandardInput( 
            /* [retval][out] */ LONG_PTR *hStdIn) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_StandardOutput( 
            /* [retval][out] */ LONG_PTR *hStdOut) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_StandardError( 
            /* [retval][out] */ LONG_PTR *hStdErr) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_HasExited( 
            /* [retval][out] */ VARIANT_BOOL *bExited) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ExitCode( 
            /* [retval][out] */ INT *iExitCode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Kill( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WaitForExit( 
            /* [in] */ DWORD ulTimeoutMillisconds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WaitForExitIndefinite( void) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Initialize( 
            HANDLE hProcess,
            HANDLE hStdIn,
            HANDLE hStdOut,
            HANDLE hStdErr) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRunningProcessVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRunningProcess * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRunningProcess * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRunningProcess * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StandardInput )( 
            IRunningProcess * This,
            /* [retval][out] */ LONG_PTR *hStdIn);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StandardOutput )( 
            IRunningProcess * This,
            /* [retval][out] */ LONG_PTR *hStdOut);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StandardError )( 
            IRunningProcess * This,
            /* [retval][out] */ LONG_PTR *hStdErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasExited )( 
            IRunningProcess * This,
            /* [retval][out] */ VARIANT_BOOL *bExited);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExitCode )( 
            IRunningProcess * This,
            /* [retval][out] */ INT *iExitCode);
        
        HRESULT ( STDMETHODCALLTYPE *Kill )( 
            IRunningProcess * This);
        
        HRESULT ( STDMETHODCALLTYPE *WaitForExit )( 
            IRunningProcess * This,
            /* [in] */ DWORD ulTimeoutMillisconds);
        
        HRESULT ( STDMETHODCALLTYPE *WaitForExitIndefinite )( 
            IRunningProcess * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IRunningProcess * This,
            HANDLE hProcess,
            HANDLE hStdIn,
            HANDLE hStdOut,
            HANDLE hStdErr);
        
        END_INTERFACE
    } IRunningProcessVtbl;

    interface IRunningProcess
    {
        CONST_VTBL struct IRunningProcessVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRunningProcess_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRunningProcess_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRunningProcess_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRunningProcess_get_StandardInput(This,hStdIn)	\
    ( (This)->lpVtbl -> get_StandardInput(This,hStdIn) ) 

#define IRunningProcess_get_StandardOutput(This,hStdOut)	\
    ( (This)->lpVtbl -> get_StandardOutput(This,hStdOut) ) 

#define IRunningProcess_get_StandardError(This,hStdErr)	\
    ( (This)->lpVtbl -> get_StandardError(This,hStdErr) ) 

#define IRunningProcess_get_HasExited(This,bExited)	\
    ( (This)->lpVtbl -> get_HasExited(This,bExited) ) 

#define IRunningProcess_get_ExitCode(This,iExitCode)	\
    ( (This)->lpVtbl -> get_ExitCode(This,iExitCode) ) 

#define IRunningProcess_Kill(This)	\
    ( (This)->lpVtbl -> Kill(This) ) 

#define IRunningProcess_WaitForExit(This,ulTimeoutMillisconds)	\
    ( (This)->lpVtbl -> WaitForExit(This,ulTimeoutMillisconds) ) 

#define IRunningProcess_WaitForExitIndefinite(This)	\
    ( (This)->lpVtbl -> WaitForExitIndefinite(This) ) 

#define IRunningProcess_Initialize(This,hProcess,hStdIn,hStdOut,hStdErr)	\
    ( (This)->lpVtbl -> Initialize(This,hProcess,hStdIn,hStdOut,hStdErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRunningProcess_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AppxJavaComLauncher_0000_0001 */
/* [local] */ 

typedef /* [public][public][public][public] */ 
enum __MIDL___MIDL_itf_AppxJavaComLauncher_0000_0001_0001
    {
        JAVA_LAUNCH_STYLE_BACKGROUND	= 0,
        JAVA_LAUNCH_STYLE_CREATE_CONSOLE_WINDOW	= ( JAVA_LAUNCH_STYLE_BACKGROUND + 1 ) ,
        JAVA_LAUNCH_STYLE_GUI	= ( JAVA_LAUNCH_STYLE_CREATE_CONSOLE_WINDOW + 1 ) 
    } 	JAVA_LAUNCH_STYLE;



extern RPC_IF_HANDLE __MIDL_itf_AppxJavaComLauncher_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AppxJavaComLauncher_0000_0001_v0_0_s_ifspec;

#ifndef __IJavaLauncher_INTERFACE_DEFINED__
#define __IJavaLauncher_INTERFACE_DEFINED__

/* interface IJavaLauncher */
/* [object][uuid] */ 


EXTERN_C const IID IID_IJavaLauncher;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D704B65E-8559-4087-88C7-0A5C7ADB2407")
    IJavaLauncher : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_WorkingDirectory( 
            /* [string][retval][out] */ BSTR *pstrWorkingDirectory) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_WorkingDirectory( 
            /* [string][in] */ BSTR strWorkingDirectory) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ClassPath( 
            /* [retval][out] */ SAFEARRAY * *pClassPath) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ClassPath( 
            /* [in] */ SAFEARRAY * classPath) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ExtraJavaArguments( 
            /* [retval][out] */ SAFEARRAY * *pExtraJavaArgv) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ExtraJavaArguments( 
            /* [in] */ SAFEARRAY * extraJavaArgv) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ProgramArguments( 
            /* [retval][out] */ SAFEARRAY * *pArgv) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ProgramArguments( 
            /* [in] */ SAFEARRAY * argv) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_EnvironmentVariables( 
            /* [retval][out] */ SAFEARRAY * *pEnvironmentVariables) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_EnvironmentVariables( 
            /* [in] */ SAFEARRAY * environmentVariables) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LaunchClass( 
            /* [in] */ BSTR className,
            /* [in] */ JAVA_LAUNCH_STYLE launchStyle,
            /* [in] */ DWORD callerProcessId,
            /* [retval][out] */ IRunningProcess **pProcess) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LaunchJarFile( 
            /* [in] */ BSTR jarPath,
            /* [in] */ JAVA_LAUNCH_STYLE launchStyle,
            /* [in] */ DWORD callerProcessId,
            /* [retval][out] */ IRunningProcess **pProcess) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IJavaLauncherVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IJavaLauncher * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IJavaLauncher * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IJavaLauncher * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WorkingDirectory )( 
            IJavaLauncher * This,
            /* [string][retval][out] */ BSTR *pstrWorkingDirectory);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_WorkingDirectory )( 
            IJavaLauncher * This,
            /* [string][in] */ BSTR strWorkingDirectory);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClassPath )( 
            IJavaLauncher * This,
            /* [retval][out] */ SAFEARRAY * *pClassPath);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ClassPath )( 
            IJavaLauncher * This,
            /* [in] */ SAFEARRAY * classPath);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExtraJavaArguments )( 
            IJavaLauncher * This,
            /* [retval][out] */ SAFEARRAY * *pExtraJavaArgv);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExtraJavaArguments )( 
            IJavaLauncher * This,
            /* [in] */ SAFEARRAY * extraJavaArgv);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProgramArguments )( 
            IJavaLauncher * This,
            /* [retval][out] */ SAFEARRAY * *pArgv);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProgramArguments )( 
            IJavaLauncher * This,
            /* [in] */ SAFEARRAY * argv);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnvironmentVariables )( 
            IJavaLauncher * This,
            /* [retval][out] */ SAFEARRAY * *pEnvironmentVariables);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_EnvironmentVariables )( 
            IJavaLauncher * This,
            /* [in] */ SAFEARRAY * environmentVariables);
        
        HRESULT ( STDMETHODCALLTYPE *LaunchClass )( 
            IJavaLauncher * This,
            /* [in] */ BSTR className,
            /* [in] */ JAVA_LAUNCH_STYLE launchStyle,
            /* [in] */ DWORD callerProcessId,
            /* [retval][out] */ IRunningProcess **pProcess);
        
        HRESULT ( STDMETHODCALLTYPE *LaunchJarFile )( 
            IJavaLauncher * This,
            /* [in] */ BSTR jarPath,
            /* [in] */ JAVA_LAUNCH_STYLE launchStyle,
            /* [in] */ DWORD callerProcessId,
            /* [retval][out] */ IRunningProcess **pProcess);
        
        END_INTERFACE
    } IJavaLauncherVtbl;

    interface IJavaLauncher
    {
        CONST_VTBL struct IJavaLauncherVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJavaLauncher_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IJavaLauncher_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IJavaLauncher_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IJavaLauncher_get_WorkingDirectory(This,pstrWorkingDirectory)	\
    ( (This)->lpVtbl -> get_WorkingDirectory(This,pstrWorkingDirectory) ) 

#define IJavaLauncher_put_WorkingDirectory(This,strWorkingDirectory)	\
    ( (This)->lpVtbl -> put_WorkingDirectory(This,strWorkingDirectory) ) 

#define IJavaLauncher_get_ClassPath(This,pClassPath)	\
    ( (This)->lpVtbl -> get_ClassPath(This,pClassPath) ) 

#define IJavaLauncher_put_ClassPath(This,classPath)	\
    ( (This)->lpVtbl -> put_ClassPath(This,classPath) ) 

#define IJavaLauncher_get_ExtraJavaArguments(This,pExtraJavaArgv)	\
    ( (This)->lpVtbl -> get_ExtraJavaArguments(This,pExtraJavaArgv) ) 

#define IJavaLauncher_put_ExtraJavaArguments(This,extraJavaArgv)	\
    ( (This)->lpVtbl -> put_ExtraJavaArguments(This,extraJavaArgv) ) 

#define IJavaLauncher_get_ProgramArguments(This,pArgv)	\
    ( (This)->lpVtbl -> get_ProgramArguments(This,pArgv) ) 

#define IJavaLauncher_put_ProgramArguments(This,argv)	\
    ( (This)->lpVtbl -> put_ProgramArguments(This,argv) ) 

#define IJavaLauncher_get_EnvironmentVariables(This,pEnvironmentVariables)	\
    ( (This)->lpVtbl -> get_EnvironmentVariables(This,pEnvironmentVariables) ) 

#define IJavaLauncher_put_EnvironmentVariables(This,environmentVariables)	\
    ( (This)->lpVtbl -> put_EnvironmentVariables(This,environmentVariables) ) 

#define IJavaLauncher_LaunchClass(This,className,launchStyle,callerProcessId,pProcess)	\
    ( (This)->lpVtbl -> LaunchClass(This,className,launchStyle,callerProcessId,pProcess) ) 

#define IJavaLauncher_LaunchJarFile(This,jarPath,launchStyle,callerProcessId,pProcess)	\
    ( (This)->lpVtbl -> LaunchJarFile(This,jarPath,launchStyle,callerProcessId,pProcess) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IJavaLauncher_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AppxJavaComLauncher_0000_0002 */
/* [local] */ 

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_AppxJavaComLauncher_0000_0002_0001
    {
        JDK_TOOL_JAVA_COMPILER	= 0,
        JDK_TOOL_APPLETVIEWER	= ( JDK_TOOL_JAVA_COMPILER + 1 ) ,
        JDK_TOOL_EXTCHECK	= ( JDK_TOOL_APPLETVIEWER + 1 ) ,
        JDK_TOOL_IDL_TO_JAVA_COMPILER	= ( JDK_TOOL_EXTCHECK + 1 ) ,
        JDK_TOOL_JAR_ARCHIVER	= ( JDK_TOOL_IDL_TO_JAVA_COMPILER + 1 ) ,
        JDK_TOOL_JAR_SIGNER	= ( JDK_TOOL_JAR_ARCHIVER + 1 ) ,
        JDK_TOOL_JAVA_DOCUMENTATION_GENERATOR	= ( JDK_TOOL_JAR_SIGNER + 1 ) ,
        JDK_TOOL_JNI_HEADER_GENERATOR	= ( JDK_TOOL_JAVA_DOCUMENTATION_GENERATOR + 1 ) ,
        JDK_TOOL_JAVA_DISASSEMBLER	= ( JDK_TOOL_JNI_HEADER_GENERATOR + 1 ) ,
        JDK_TOOL_JAVA_RMI_RUNNER	= ( JDK_TOOL_JAVA_DISASSEMBLER + 1 ) ,
        JDK_TOOL_JCMD	= ( JDK_TOOL_JAVA_RMI_RUNNER + 1 ) ,
        JDK_TOOL_JCONSOLE	= ( JDK_TOOL_JCMD + 1 ) ,
        JDK_TOOL_JAVA_DEBUGGER	= ( JDK_TOOL_JCONSOLE + 1 ) ,
        JDK_TOOL_DEPENDENCY_GRAPH_GENERATOR	= ( JDK_TOOL_JAVA_DEBUGGER + 1 ) ,
        JDK_TOOL_JHAT	= ( JDK_TOOL_DEPENDENCY_GRAPH_GENERATOR + 1 ) ,
        JDK_TOOL_JVM_INTROSPECTION_UTILITY	= ( JDK_TOOL_JHAT + 1 ) ,
        JDK_TOOL_JVM_MEMORY_DUMP_UTILITY	= ( JDK_TOOL_JVM_INTROSPECTION_UTILITY + 1 ) ,
        JDK_TOOL_JPS	= ( JDK_TOOL_JVM_MEMORY_DUMP_UTILITY + 1 ) ,
        JDK_TOOL_JRUNSCRIPT	= ( JDK_TOOL_JPS + 1 ) ,
        JDK_TOOL_JAVA_SCRIPT_RUNNER	= ( JDK_TOOL_JRUNSCRIPT + 1 ) ,
        JDK_TOOL_JSADEBUG_DAEMON	= ( JDK_TOOL_JAVA_SCRIPT_RUNNER + 1 ) ,
        JDK_TOOL_JAVA_STACK_DUMPER	= ( JDK_TOOL_JSADEBUG_DAEMON + 1 ) ,
        JDK_TOOL_JVM_SAMPLER	= ( JDK_TOOL_JAVA_STACK_DUMPER + 1 ) ,
        JDK_TOOL_JSTAT_DAEMON	= ( JDK_TOOL_JVM_SAMPLER + 1 ) ,
        JDK_TOOL_KEY_AND_CERT_MANAGER	= ( JDK_TOOL_JSTAT_DAEMON + 1 ) ,
        JDK_TOOL_KERBEROS_KINIT	= ( JDK_TOOL_KEY_AND_CERT_MANAGER + 1 ) ,
        JDK_TOOL_KERBEROS_KLIST	= ( JDK_TOOL_KERBEROS_KINIT + 1 ) ,
        JDK_TOOL_KERBEROS_KTAB	= ( JDK_TOOL_KERBEROS_KLIST + 1 ) ,
        JDK_TOOL_NATIVE2ASCII	= ( JDK_TOOL_KERBEROS_KTAB + 1 ) ,
        JDK_TOOL_ORB_DAEMON	= ( JDK_TOOL_NATIVE2ASCII + 1 ) ,
        JDK_TOOL_PACK200	= ( JDK_TOOL_ORB_DAEMON + 1 ) ,
        JDK_TOOL_POLICY_TOOL	= ( JDK_TOOL_PACK200 + 1 ) ,
        JDK_TOOL_RMI_COMPILER	= ( JDK_TOOL_POLICY_TOOL + 1 ) ,
        JDK_TOOL_RMI_DAEMON	= ( JDK_TOOL_RMI_COMPILER + 1 ) ,
        JDK_TOOL_RMI_REGISTRY_TOOL	= ( JDK_TOOL_RMI_DAEMON + 1 ) ,
        JDK_TOOL_SCHEMA_GENERATOR	= ( JDK_TOOL_RMI_REGISTRY_TOOL + 1 ) ,
        JDK_TOOL_SERIAL_VERSION_UTILITY	= ( JDK_TOOL_SCHEMA_GENERATOR + 1 ) ,
        JDK_TOOL_SERVER_TOOL	= ( JDK_TOOL_SERIAL_VERSION_UTILITY + 1 ) ,
        JDK_TOOL_TNAME_SERVICE	= ( JDK_TOOL_SERVER_TOOL + 1 ) ,
        JDK_TOOL_UNPACK200	= ( JDK_TOOL_TNAME_SERVICE + 1 ) ,
        JDK_TOOL_WSDL_GENERATOR	= ( JDK_TOOL_UNPACK200 + 1 ) ,
        JDK_TOOL_WSDL_IMPORTER	= ( JDK_TOOL_WSDL_GENERATOR + 1 ) ,
        JDK_TOOL_JAXB_BINDING_COMPILER	= ( JDK_TOOL_WSDL_IMPORTER + 1 ) 
    } 	JDK_TOOL;



extern RPC_IF_HANDLE __MIDL_itf_AppxJavaComLauncher_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AppxJavaComLauncher_0000_0002_v0_0_s_ifspec;

#ifndef __IJdkToolLauncher_INTERFACE_DEFINED__
#define __IJdkToolLauncher_INTERFACE_DEFINED__

/* interface IJdkToolLauncher */
/* [object][uuid] */ 


EXTERN_C const IID IID_IJdkToolLauncher;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BB3B0B30-9FA2-4D27-856A-4190FF19CA8B")
    IJdkToolLauncher : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ToolName( 
            /* [retval][out] */ JDK_TOOL *pToolId) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ToolName( 
            /* [in] */ JDK_TOOL toolId) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_WorkingDirectory( 
            /* [string][retval][out] */ BSTR *pstrWorkingDirectory) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_WorkingDirectory( 
            /* [string][in] */ BSTR strWorkingDirectory) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ProgramArguments( 
            /* [retval][out] */ SAFEARRAY * *pArgv) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ProgramArguments( 
            /* [in] */ SAFEARRAY * argv) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_EnvironmentVariables( 
            /* [retval][out] */ SAFEARRAY * *pEnvironmentVariables) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_EnvironmentVariables( 
            /* [in] */ SAFEARRAY * environmentVariables) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Launch( 
            /* [in] */ JAVA_LAUNCH_STYLE launchStyle,
            /* [in] */ DWORD callerProcessId,
            /* [retval][out] */ IRunningProcess **pProcess) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IJdkToolLauncherVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IJdkToolLauncher * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IJdkToolLauncher * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IJdkToolLauncher * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ToolName )( 
            IJdkToolLauncher * This,
            /* [retval][out] */ JDK_TOOL *pToolId);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ToolName )( 
            IJdkToolLauncher * This,
            /* [in] */ JDK_TOOL toolId);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WorkingDirectory )( 
            IJdkToolLauncher * This,
            /* [string][retval][out] */ BSTR *pstrWorkingDirectory);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_WorkingDirectory )( 
            IJdkToolLauncher * This,
            /* [string][in] */ BSTR strWorkingDirectory);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProgramArguments )( 
            IJdkToolLauncher * This,
            /* [retval][out] */ SAFEARRAY * *pArgv);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProgramArguments )( 
            IJdkToolLauncher * This,
            /* [in] */ SAFEARRAY * argv);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnvironmentVariables )( 
            IJdkToolLauncher * This,
            /* [retval][out] */ SAFEARRAY * *pEnvironmentVariables);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_EnvironmentVariables )( 
            IJdkToolLauncher * This,
            /* [in] */ SAFEARRAY * environmentVariables);
        
        HRESULT ( STDMETHODCALLTYPE *Launch )( 
            IJdkToolLauncher * This,
            /* [in] */ JAVA_LAUNCH_STYLE launchStyle,
            /* [in] */ DWORD callerProcessId,
            /* [retval][out] */ IRunningProcess **pProcess);
        
        END_INTERFACE
    } IJdkToolLauncherVtbl;

    interface IJdkToolLauncher
    {
        CONST_VTBL struct IJdkToolLauncherVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJdkToolLauncher_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IJdkToolLauncher_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IJdkToolLauncher_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IJdkToolLauncher_get_ToolName(This,pToolId)	\
    ( (This)->lpVtbl -> get_ToolName(This,pToolId) ) 

#define IJdkToolLauncher_put_ToolName(This,toolId)	\
    ( (This)->lpVtbl -> put_ToolName(This,toolId) ) 

#define IJdkToolLauncher_get_WorkingDirectory(This,pstrWorkingDirectory)	\
    ( (This)->lpVtbl -> get_WorkingDirectory(This,pstrWorkingDirectory) ) 

#define IJdkToolLauncher_put_WorkingDirectory(This,strWorkingDirectory)	\
    ( (This)->lpVtbl -> put_WorkingDirectory(This,strWorkingDirectory) ) 

#define IJdkToolLauncher_get_ProgramArguments(This,pArgv)	\
    ( (This)->lpVtbl -> get_ProgramArguments(This,pArgv) ) 

#define IJdkToolLauncher_put_ProgramArguments(This,argv)	\
    ( (This)->lpVtbl -> put_ProgramArguments(This,argv) ) 

#define IJdkToolLauncher_get_EnvironmentVariables(This,pEnvironmentVariables)	\
    ( (This)->lpVtbl -> get_EnvironmentVariables(This,pEnvironmentVariables) ) 

#define IJdkToolLauncher_put_EnvironmentVariables(This,environmentVariables)	\
    ( (This)->lpVtbl -> put_EnvironmentVariables(This,environmentVariables) ) 

#define IJdkToolLauncher_Launch(This,launchStyle,callerProcessId,pProcess)	\
    ( (This)->lpVtbl -> Launch(This,launchStyle,callerProcessId,pProcess) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IJdkToolLauncher_INTERFACE_DEFINED__ */



#ifndef __AppxJavaLauncherLib_LIBRARY_DEFINED__
#define __AppxJavaLauncherLib_LIBRARY_DEFINED__

/* library AppxJavaLauncherLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_AppxJavaLauncherLib;

EXTERN_C const CLSID CLSID_JavaLauncher;

#ifdef __cplusplus

class DECLSPEC_UUID("67CE3994-EC0A-4364-B8BD-DC6D1C61FCF0")
JavaLauncher;
#endif

EXTERN_C const CLSID CLSID_JdkToolLauncher;

#ifdef __cplusplus

class DECLSPEC_UUID("5EDE5D2D-C324-4970-86B3-6E006D4DD824")
JdkToolLauncher;
#endif
#endif /* __AppxJavaLauncherLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


