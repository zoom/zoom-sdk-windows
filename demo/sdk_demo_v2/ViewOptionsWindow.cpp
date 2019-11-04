#include "stdafx.h"
#include "ViewOptionsWindow.h"
#include "AnnotateBarWindow.h"

ViewOptionsWindow::ViewOptionsWindow(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* pShareRender)
{
	m_btnGiveupRemoteControl  = NULL;
	m_btnRequestRemoteControl = NULL;
	m_btnAnnotate = NULL;

	m_pShareRender = pShareRender;
	m_pAnnotateBarWindow = NULL;
	m_bShowAnnoWin = false;
}

ViewOptionsWindow::~ViewOptionsWindow()
{
	if (m_pAnnotateBarWindow){
		delete m_pAnnotateBarWindow;
		m_pAnnotateBarWindow = NULL;
	}

	if (::IsWindow(m_hWnd)){
		::DestroyWindow(m_hWnd);
	}
}

void ViewOptionsWindow::InitWindow()
{
	m_btnRequestRemoteControl = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_request_remote_control"));
	m_btnGiveupRemoteControl  = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_giveup_remote_control"));
	m_btnAnnotate             = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_annotate"));

	RECT rc = { 0 };
	if (::GetWindowRect(m_hWnd, &rc)) {
		::SetWindowPos(m_hWnd, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top, SWP_HIDEWINDOW);
	}
}

void ViewOptionsWindow::ShowAnnotateBarWindow()
{
	if (m_pAnnotateBarWindow == NULL)
	{
		m_pAnnotateBarWindow = new AnnotateBarWindow(m_pShareRender);
		m_pAnnotateBarWindow->Create(m_hWnd, _T("Annotate Bar"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, WS_EX_TOPMOST|WS_EX_TOOLWINDOW);
	}

	if (::IsWindowVisible(m_pAnnotateBarWindow->GetHWND())){
		m_pAnnotateBarWindow->ShowWindow(false);
		m_pAnnotateBarWindow->HideOwnedWindows();
	}else {
		m_pAnnotateBarWindow->MoveWindowPosTo(m_hWnd);
		m_pAnnotateBarWindow->ShowWindow(true);
	}
}

void ViewOptionsWindow::Notify( TNotifyUI& msg )
{
	if (msg.sType ==_T("click"))
	{
		if (msg.pSender == m_btnRequestRemoteControl){
			SDKInterfaceWrap::GetInst().GetMeetingRemoteController()->RequestRemoteControl(m_pShareRender->GetUserID());
		}else if (msg.pSender == m_btnGiveupRemoteControl){
			//SDKInterfaceWrap::GetInst().GetMeetingRemoteController()->LeaveRemoteControllingStatus(m_pShareRender->GetUserID());
			SDKInterfaceWrap::GetInst().GetMeetingRemoteController()->GiveupRemoteControl(m_pShareRender->GetUserID());
		}else if (msg.pSender == m_btnAnnotate){
			ShowAnnotateBarWindow();
		}
	}
}

LRESULT ViewOptionsWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		this->ShowWindow(false);
		return lRes;
	}
	else if (uMsg == WM_DESTROY)
	{
		OnDestroy(uMsg, wParam, lParam, bHandled);		
	}
	else if (uMsg == WM_NCDESTROY)
	{
		//delete this;
		//window obj pointer = NULL
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT ViewOptionsWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return true;
}

LRESULT ViewOptionsWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return true;
}