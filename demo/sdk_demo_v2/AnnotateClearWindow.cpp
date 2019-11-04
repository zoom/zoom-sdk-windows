#include "stdafx.h"
#include "AnnotateClearWindow.h"

AnnotateClearWindow::AnnotateClearWindow(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj)
{
	m_customerAnnoObj = pAnnoObj;
	m_btnClearAll = NULL;
	m_btnClearMy = NULL;
	m_btnClearViewer = NULL;
}

AnnotateClearWindow::~AnnotateClearWindow()
{
	if (::IsWindow(m_hWnd)){
		::DestroyWindow(m_hWnd);
	}
}

void AnnotateClearWindow::MoveWindowPosTo(HWND hwOwner)
{
	RECT rcOwner;
	if (::GetWindowRect(hwOwner, &rcOwner)){
		RECT rc = { 0 };
		if (::GetWindowRect(m_hWnd, &rc)) {
			::SetWindowPos(m_hWnd, NULL, rcOwner.left + 780, rcOwner.bottom, rc.right-rc.left, rc.bottom-rc.top, SWP_HIDEWINDOW);
		}
	}
}

void AnnotateClearWindow::InitWindow()
{
	m_btnClearAll = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_clear_all"));
	m_btnClearMy  = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_clear_my"));
	m_btnClearViewer = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_clear_viewer"));
}

void AnnotateClearWindow::Notify( TNotifyUI& msg )
{
	if (msg.sType ==_T("click"))
	{
		if (m_customerAnnoObj == NULL){
			return;
		}

		ZOOM_SDK_NAMESPACE::AnnotationClearType annoToolType;
		if (msg.pSender == m_btnClearAll){
			annoToolType = ZOOM_SDK_NAMESPACE::ANNOCLEAR_ALL;
		} else if (msg.pSender == m_btnClearMy){
			annoToolType = ZOOM_SDK_NAMESPACE::ANNOCLEAR_SELF;
		} else if (msg.pSender == m_btnClearViewer){
			annoToolType = ZOOM_SDK_NAMESPACE::ANNOCLEAR_OTHER;
		}
		m_customerAnnoObj->Clear(annoToolType);
	}
}

LRESULT AnnotateClearWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT AnnotateClearWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 1;
}

LRESULT AnnotateClearWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 1;
}