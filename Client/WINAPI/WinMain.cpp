
#include "stdHeaders.h"
#include "API_Setup.h"
//#include "Timer.h"


#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")



//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
//	PSTR cmdLine, int showCmd)
//{
//	// Enable run-time memory check for debug builds.
//#if defined(DEBUG) | defined(_DEBUG)
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif
//
//	try
//	{
//		CApiSetUP theApp(hInstance);
//		theApp.SetGeneralSettings(std::unique_ptr<CGeneralSettings>(
//			new CGeneralSettings(
//				std::shared_ptr<DxDevice>(new DxDevice),
//				std::shared_ptr<CTimer>(new CTimer),
//				std::shared_ptr<CTimer>(new CTimer))
//			));
//		//InitDirect3DApp theApp(hInstance);
//		if (!theApp.Initialize())
//			return 0;
//
//		return theApp.Run();
//	}
//	catch (DxException& e)
//	{
//		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
//		return 0;
//	}
//}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		CApiSetUP theApp(hInstance);
		theApp.SetGeneralSettings(std::unique_ptr<CGeneralSettings>(
			new CGeneralSettings(
				std::shared_ptr<DxDevice>(new DxDevice),
				std::shared_ptr<CTimer>(new CTimer),
				std::shared_ptr<CTimer>(new CTimer))
			));
		//InitDirect3DApp theApp(hInstance);
		if (!theApp.Initialize())
			return 0;

		return theApp.Run();
	}
	catch (DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}