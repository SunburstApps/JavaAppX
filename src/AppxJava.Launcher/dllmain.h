// dllmain.h : Declaration of module class.

class CAppxJavaLauncherModule : public ATL::CAtlDllModuleT< CAppxJavaLauncherModule >
{
public :
	DECLARE_LIBID(LIBID_AppxJavaLauncherLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_APPXJAVALAUNCHER, "{96696F0A-8B30-45F2-B347-C6DE06326A76}")
};

extern class CAppxJavaLauncherModule _AtlModule;
