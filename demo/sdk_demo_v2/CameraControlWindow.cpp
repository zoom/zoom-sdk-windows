#include "stdafx.h"
#include "CameraControlWindow.h"
#include "sdk_util.h"

CameraControlWindow::CameraControlWindow(CCustomizeInMeetingUIMgr* pMainUI)
{
	m_pMainUI = pMainUI;
	m_btnZoomIn = NULL;
	m_btnZoomOut = NULL;
	m_btnLeft = NULL;
	m_btnRight = NULL;
	m_btnUp = NULL;
	m_btnDown = NULL;
}

CameraControlWindow::CameraControlWindow()
{
	m_pMainUI = NULL;
	m_btnZoomIn = NULL;
	m_btnZoomOut = NULL;
	m_btnLeft = NULL;
	m_btnRight = NULL;
	m_btnUp = NULL;
	m_btnDown = NULL;
}

CameraControlWindow::~CameraControlWindow()
{

}

void CameraControlWindow::InitWindow()
{
	m_btnZoomIn = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_zoom_in"));
	m_btnZoomOut = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_zoom_out"));
	m_btnLeft = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_left"));
	m_btnRight = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_right"));
	m_btnUp = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_up"));
	m_btnDown = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_down"));
	m_btnCheck = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_check"));

	//position
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) 
		return;
	::SetWindowPos(m_hWnd, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top, SWP_HIDEWINDOW);
}

void CameraControlWindow::Notify( TNotifyUI& msg )
{
	if (msg.sType ==_T("click"))
	{
		//get sdk obj pointer
		ZOOM_SDK_NAMESPACE::IMeetingService* pMeetingService = SDKInterfaceWrap::GetInst().GetMeetingService();
		if(!pMeetingService)
			return;
		ZOOM_SDK_NAMESPACE::IMeetingVideoController* videoCtrl = pMeetingService->GetMeetingVideoController();
		if (!videoCtrl)
			return;	
		ZOOM_SDK_NAMESPACE::ICameraController* cameraCtrl = videoCtrl->GetMyCameraController();
		if (!cameraCtrl)
			return;

		//process btn event
		if (msg.pSender == m_btnZoomIn)
		{
			cameraCtrl->BeginZoomIn();
			cameraCtrl->ContinueZoomIn();
			Sleep(50);
			cameraCtrl->EndZoomIn();
		}
		else if(msg.pSender == m_btnZoomOut)
		{
			cameraCtrl->BeginZoomOut();
			cameraCtrl->ContinueZoomOut();
			Sleep(50);
			cameraCtrl->EndZoomOut();
		}
		else if (msg.pSender == m_btnLeft)
		{
			cameraCtrl->BeginTurnLeft();
			cameraCtrl->ContinueTurnLeft();
			Sleep(50);
			cameraCtrl->EndTurnLeft();
		}
		else if (msg.pSender == m_btnRight)
		{
			cameraCtrl->BeginTurnRight();
			cameraCtrl->ContinueTurnRight();
			Sleep(50);
			cameraCtrl->EndTurnRight();
		}
		else if (msg.pSender == m_btnUp)
		{
			cameraCtrl->BeginTurnUp();
			cameraCtrl->ContinueTurnUp();
			Sleep(50);
			cameraCtrl->EndTurnUp();
		}
		else if (msg.pSender == m_btnDown)
		{
			cameraCtrl->BeginTurnDown();
			cameraCtrl->ContinueTurnDown();
			Sleep(50);
			cameraCtrl->EndTurnDown();
		}
		else if (msg.pSender == m_btnCheck)
		{
			bool bCan;
			ZOOM_SDK_NAMESPACE::SDKError rtn = cameraCtrl->CanControlCamera(bCan);
			if (rtn == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
			{
				if (bCan) ::MessageBox(NULL, L"Can control camera", L"notify", MB_OK);
				else ::MessageBox(NULL, L"Can't control camera", L"notify", MB_OK);
			}else {
				::MessageBox(NULL, L"Error", L"notify", MB_OK);
			}
		}
	}
}

LRESULT CameraControlWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	if( uMsg == WM_CREATE )  
	{
		m_PaintManager.Init(m_hWnd);

		CDialogBuilder builder;
		STRINGorID xml(GetSkinRes());
		CControlUI* pRoot = builder.Create(xml, _T("xml"), 0, &m_PaintManager);
		ASSERT(pRoot && "Failed to parse XML");

		m_PaintManager.AttachDialog(pRoot);
		m_PaintManager.AddNotifier(this);
		InitWindow(); 

		return lRes;
	}
	else if (uMsg == WM_CLOSE)
	{
		OnClose(uMsg, wParam, lParam, bHandled);		
	}
	else if (uMsg == WM_DESTROY)
	{
		OnDestroy(uMsg, wParam, lParam, bHandled);		
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CameraControlWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return true;
}

LRESULT CameraControlWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return true;
}

bool CameraControlWindow::DestroyWindow()
{
	if(::IsWindow(m_hWnd))
	{
		return ::DestroyWindow(m_hWnd) ? true:false;
	}
	return false;
}