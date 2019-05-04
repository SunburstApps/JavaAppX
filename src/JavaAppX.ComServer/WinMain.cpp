#include "StdAfx.h"

_Use_decl_annotations_
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE /* hPrevInstance */, LPWSTR cmdLine, int nCmdShow) {
	if (wcscmp(cmdLine, L"/Embedding") != 0) {
		::MessageBoxW(HWND_DESKTOP, L"This application is not intended to be run directly. It will be launched by the system automatically when needed.", L"OpenJDK for Windows 10", MB_ICONERROR | MB_OK);
		return 1;
	}

	return 0;
}
