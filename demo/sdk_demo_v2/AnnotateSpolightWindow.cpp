#include "stdafx.h"
#include "AnnotateSpolightWindow.h"

AnnotateSpolightWindow::AnnotateSpolightWindow(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj)
{
	m_customerAnnoObj = pAnnoObj;
	m_btnSpolight = NULL;
	m_btnArrow = NULL;
}

AnnotateSpolightWindow::~AnnotateSpolightWindow()
{
	if (::IsWindow(m_hWnd)){
		::DestroyWindow(m_hWnd);
	}
}

void AnnotateSpolightWindow::MoveWindowPosTo(HWND hwOwner)
{
	RECT rcOwner;
	if (::GetWindowRect(hwOwner, &rcOwner)){
		RECT rc = { 0 };
		if (::GetWindowRect(m_hWnd, &rc)) {
			::SetWindowPos(m_hWnd, NULL, rcOwner.left + 360, rcOwner.bottom, rc.right-rc.left, rc.bottom-rc.top, SWP_HIDEWINDOW);
		}
	}
}

void AnnotateSpolightWindow::InitWindow()
{
	m_btnSpolight = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_spolight"));;
	m_btnArrow = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_arrow"));;
}

void AnnotateSpolightWindow::Notify( TNotifyUI& msg )
{
	if (msg.sType ==_T("click"))
	{
		if (m_customerAnnoObj == NULL){
			return;
		}
		if (msg.pSender == m_btnSpolight){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_SPOTLIGHT);	
		}else if (msg.pSender == m_btnArrow){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_ARROW);
		}
	}
}

LRESULT AnnotateSpolightWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT AnnotateSpolightWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 1;
}

LRESULT AnnotateSpolightWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 1;
}