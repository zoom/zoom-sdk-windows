#include "stdafx.h"
#include "invitation_ui.h"

CInvitationUIMgr::CInvitationUIMgr()
{
	m_copy_invite_link_btn = NULL;
	m_copy_invite_info_btn = NULL;
	m_notify_lb = NULL;
}

CInvitationUIMgr::~CInvitationUIMgr()
{
	m_copy_invite_link_btn = NULL;
	m_copy_invite_info_btn = NULL;
	m_notify_lb = NULL;
}

LRESULT CInvitationUIMgr::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
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
		ShowWindow(false);
		SetForegroundWindow(GetParent(m_hWnd));		
		return lRes;
	}
	else if (uMsg == WM_TIMER)
	{
		if (m_notify_lb)
		{
			m_notify_lb->SetVisible(false);
		}
		KillTimer(m_hWnd, 2);
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CInvitationUIMgr::InitWindow()
{
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) return;
	rc.right = rc.left + 524;
	rc.bottom = rc.top + 376;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), (!(GetWindowStyle(m_hWnd) & WS_CHILD) && (::GetMenu(m_hWnd) != NULL)), GetWindowExStyle(m_hWnd)) ) return;
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, NULL, (ScreenX - (rc.right - rc.left)) / 2, 
		(ScreenY - (rc.bottom - rc.top)) / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_HIDEWINDOW);


	m_copy_invite_link_btn = dynamic_cast<CButtonUI* >(m_PaintManager.FindControl(L"copy_invitate_link_btn"));
	m_copy_invite_info_btn = dynamic_cast<CButtonUI* >(m_PaintManager.FindControl(L"copy_invitate_info_btn"));
	m_notify_lb = dynamic_cast<CLabelUI* >(m_PaintManager.FindControl(L"copy_notify"));
}

void CInvitationUIMgr::Notify( TNotifyUI& msg )
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_copy_invite_link_btn)
		{
			DoClickCopyLinkBtn();
		}
		else if(msg.pSender == m_copy_invite_info_btn)
		{
			DoClickCopyInviteInfoBtn();
		}
	}
}


void CInvitationUIMgr::DoClickCopyLinkBtn()
{
	if (SetDataToClipboard(m_invite_workflow.GetJoinMeetingUrl(),NULL))
	{
		if (m_notify_lb)
		{
			m_notify_lb->SetVisible(true);
		}
		SetTimer(m_hWnd,2, 2000, NULL);
	}
}

void CInvitationUIMgr::DoClickCopyInviteInfoBtn()
{
	std::wstring email_content = std::wstring(m_invite_workflow.GetInviteEmailTitle()) + std::wstring(m_invite_workflow.GetInviteEmailTeamplate());
	if (SetDataToClipboard(email_content.c_str(), NULL))
	{
		if (m_notify_lb)
		{
			m_notify_lb->SetVisible(true);
		}
		SetTimer(m_hWnd,2, 2000, NULL);
	}
}
