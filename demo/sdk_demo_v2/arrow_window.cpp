#include "stdafx.h"
#include "arrow_window.h"

CArrowWindow::CArrowWindow(CCustomizeInMeetingUIMgr* pCustomizeUI)
{
	m_hParentWnd = NULL;
	m_pCustomizeUI = pCustomizeUI;
	m_btnArrowPre = NULL;
	m_btnArrowNext = NULL;
}

CArrowWindow::~CArrowWindow()
{
	m_hParentWnd = NULL;
	m_pCustomizeUI = NULL;
}

void CArrowWindow::InitWindow()
{
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) 
		return;
	rc.bottom = rc.top + DEFAULT_ARROW_HEIGHT;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), false, GetWindowExStyle(m_hWnd)) ) return;
	::SetWindowPos(m_hWnd, NULL, rc.left,rc.top, rc.right-rc.left,DEFAULT_ARROW_HEIGHT, SWP_SHOWWINDOW);
	m_btnArrowPre = static_cast<CButtonUI* >(m_PaintManager.FindControl(_T("btn_uparrow")));
	m_btnArrowNext = static_cast<CButtonUI* >(m_PaintManager.FindControl(_T("btn_downarrow")));

	//set the window to be transparent
	LONG nRet = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	nRet = nRet | WS_EX_LAYERED;
	//nRet = nRet | WS_EX_TOPMOST;
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, nRet);
}


LRESULT CArrowWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CArrowWindow::Notify(TNotifyUI& msg)
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnArrowPre)
			DoButtonClick(Arrow_button_up);
		else if(msg.pSender == m_btnArrowNext)
			DoButtonClick(Arrow_button_down);
	}
}

bool CArrowWindow::IsWindow()
{
	return ::IsWindow(m_hWnd) ? true:false;
}

bool CArrowWindow::DestroyWindow()
{
	if(IsWindow())
	{
		return ::DestroyWindow(m_hWnd) ? true:false;
	}
	return false;
}

void CArrowWindow::SetParent(HWND hParentWnd)
{
	m_hParentWnd = hParentWnd;
}

void CArrowWindow::EnableUsingButton(ArrowButtonType btnType, bool bEnable)
{

	if(m_btnArrowPre && m_btnArrowNext)
	{
		if(Arrow_button_down == btnType)		
		{
			m_btnArrowPre->SetEnabled(false);
			m_btnArrowPre->SetVisible(false);
			m_btnArrowNext->SetEnabled(bEnable);
			m_btnArrowNext->SetVisible(true);
		}
		else
		{
			m_btnArrowPre->SetEnabled(bEnable);
			m_btnArrowPre->SetVisible(true);
			m_btnArrowNext->SetEnabled(false);
			m_btnArrowNext->SetVisible(false);
		}
	}
}

void CArrowWindow::HandleSizeChanged(RECT newRC)
{
	RECT rc = {0};
	if(m_btnArrowPre && m_btnArrowPre->IsVisible())
	{
		rc.bottom = rc.top + DEFAULT_ARROW_HEIGHT;
		int nWidth = newRC.right - newRC.left - VideoElement_Normal_width;
		rc.left = nWidth;
		rc.right = newRC.right;
		//::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, nWidth, DEFAULT_ARROW_HEIGHT, SWP_NOZORDER|SWP_SHOWWINDOW);
		::MoveWindow(m_hWnd, rc.left, rc.top, rc.right-rc.left,DEFAULT_ARROW_HEIGHT , true);
	}
	if(m_btnArrowNext && m_btnArrowNext->IsVisible())
	{
		rc.bottom = newRC.bottom;
		rc.top = rc.bottom - DEFAULT_ARROW_HEIGHT;
		int nWidth = newRC.right - newRC.left - VideoElement_Normal_width;
		rc.left = nWidth;
		rc.right = newRC.right;
		//::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, nWidth, DEFAULT_ARROW_HEIGHT, SWP_NOZORDER|SWP_SHOWWINDOW);
		::MoveWindow(m_hWnd, rc.left, rc.top, rc.right-rc.left,DEFAULT_ARROW_HEIGHT , true);
	}
}

void CArrowWindow::DoButtonClick(ArrowButtonType btnType)
{
	//to do
	//true means show next page, false means show pre page
	if(m_pCustomizeUI)
		m_pCustomizeUI->PageButtonClick(btnType);

}
