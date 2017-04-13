#include "stdafx.h"
#include "resource.h"
#include "AppxJavaComLauncher_i.h"

class CAppxJavaComLauncherModule : public ATL::CAtlExeModuleT< CAppxJavaComLauncherModule >
{
public:
	DECLARE_LIBID(LIBID_AppxJavaLauncherLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_APPXJAVACOMLAUNCHER, "{D678A3FB-9701-44B0-B585-1A340286FBD8}")
};

CAppxJavaComLauncherModule _AtlModule;

extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}
