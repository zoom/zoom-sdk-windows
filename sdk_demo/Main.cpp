#include <windows.h>
#include "UIlib.h"
#include "DemoUI.h"

using namespace DuiLib;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	CDemoUI* pDemoUI = new CDemoUI();
	if (!pDemoUI)
		return -1;

	pDemoUI->Create(NULL, _T("Windows app using zoom win sdk"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	pDemoUI->SetIcon(IDI_ICON_LOGO);
	pDemoUI->CenterWindow();
	pDemoUI->ShowModal();

	if (pDemoUI)
	{
		delete pDemoUI;
		pDemoUI = NULL;
	}

	return 0;
}