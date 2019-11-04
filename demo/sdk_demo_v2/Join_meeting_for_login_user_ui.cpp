#include "stdafx.h"
#include "Join_meeting_for_login_user_ui.h"
CSDKJoinMeetingForLoginUserUIGroup::CSDKJoinMeetingForLoginUserUIGroup()
{
	m_JoinMeetingForLoginUserPage = NULL;
	m_parentFrame = NULL;
	m_editMeetingNumber = NULL;
	m_editScreenName = NULL;
	m_editMeetingPassword = NULL;
	m_btnJoin = NULL;
	m_bJoinIn = false;
}
CSDKJoinMeetingForLoginUserUIGroup::~CSDKJoinMeetingForLoginUserUIGroup()
{
	m_JoinMeetingForLoginUserPage = NULL;
	m_parentFrame = NULL;
	m_editMeetingNumber = NULL;
	m_editScreenName = NULL;
	m_editMeetingPassword = NULL;
	m_btnJoin = NULL;
	m_bJoinIn = false;
}
void CSDKJoinMeetingForLoginUserUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKJoinMeetingForLoginUserUIMgr* main_frame_)
{
	m_JoinMeetingForLoginUserPage = static_cast<CVerticalLayoutUI* >(ui_mgr.FindControl(_T("panel_join_meeting")));
	m_editMeetingNumber = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_meeting_number")));
	m_editScreenName = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_screen_name")));
	m_editMeetingPassword = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_meeting_password")));
	m_btnJoin = static_cast<CButtonUI* >(ui_mgr.FindControl(_T("btn_join_meeeting")));
	m_parentFrame = main_frame_;
	m_joinMeetingForLoginUserWorkFlow.SetUIEvent(this);
}
void CSDKJoinMeetingForLoginUserUIGroup::UninitWindow()
{
	m_joinMeetingForLoginUserWorkFlow.SetUIEvent(NULL);
	m_joinMeetingForLoginUserWorkFlow.Cleanup();
}
void CSDKJoinMeetingForLoginUserUIGroup::Show()
{
	if(m_JoinMeetingForLoginUserPage)
	{
		m_JoinMeetingForLoginUserPage->SetVisible(true);
	}
}
void CSDKJoinMeetingForLoginUserUIGroup::Hide()
{
	if(m_JoinMeetingForLoginUserPage)
	{
		m_JoinMeetingForLoginUserPage->SetVisible(false);
	}
}
void CSDKJoinMeetingForLoginUserUIGroup::DoJoinMeetingBtnClick()
{
	if(NULL == m_editMeetingNumber || NULL == m_editMeetingPassword || NULL == m_editScreenName)
		return;
	std::wstring strMeetingNumber = m_editMeetingNumber->GetText().GetData();
	std::wstring strUserId = _T("");
	std::wstring strMeetingPassword = m_editMeetingPassword->GetText().GetData();
	std::wstring strUserName = m_editScreenName->GetText().GetData();
	if (strMeetingNumber.length() <= 0)
		return;

	ZOOM_SDK_NAMESPACE::JoinParam joinParam;
	joinParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_NORMALUSER;
	ZOOM_SDK_NAMESPACE::JoinParam4NormalUser& normalParam = joinParam.param.normaluserJoin;
	normalParam.meetingNumber = _wtoi64(strMeetingNumber.c_str());
	normalParam.vanityID = NULL;
	normalParam.userName = strUserName.c_str();
	normalParam.psw = strMeetingPassword.c_str();
	normalParam.hDirectShareAppWnd = NULL;
	normalParam.participantId = NULL;
	normalParam.webinarToken = NULL;
	normalParam.isVideoOff = false;
	normalParam.isAudioOff = false;
	normalParam.isDirectShareDesktop = false;

	if(m_parentFrame)
	{
		if (SDKInterfaceWrap::GetInst().IsSelectCustomizedUIMode())
		{
			CSDKDemoAppEvent* pAppEvent = m_parentFrame->GetAppEvent();
			if(pAppEvent)
				pAppEvent->InitCustomizedUI();
		}

		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != m_joinMeetingForLoginUserWorkFlow.JoinMeeting(joinParam))
		{
			m_parentFrame->ShowErrorMessage(_T("Join meeting failed!"));
			m_editMeetingNumber->SetFocus();
		}
	}
}
void CSDKJoinMeetingForLoginUserUIGroup::Notify(TNotifyUI& msg)
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnJoin)
		{
			DoJoinMeetingBtnClick();
		}
	}
}
void CSDKJoinMeetingForLoginUserUIGroup::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult)
{
 	switch (status)
 	{
 	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_FAILED:
		{
			if(m_parentFrame)
			{
				m_bJoinIn = false;
				m_parentFrame->ShowErrorMessage(L"Join meeting failed");
			}
		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_INMEETING:
		{
			if(m_parentFrame)
			{
				m_bJoinIn = true;
				m_parentFrame->ShowWindow(false);
			}
		}
		break;
 	default:
 		break;
 	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///CSDKJoinMeetingForLoginUserUIMgr
CSDKJoinMeetingForLoginUserUIMgr::CSDKJoinMeetingForLoginUserUIMgr()
{
	m_pAppEvent = NULL;
}
CSDKJoinMeetingForLoginUserUIMgr::~CSDKJoinMeetingForLoginUserUIMgr()
{
	m_pAppEvent = NULL;
}
void CSDKJoinMeetingForLoginUserUIMgr::SetEvent(CSDKDemoAppEvent* pAppEvent)
{
	m_pAppEvent = pAppEvent;
}
void CSDKJoinMeetingForLoginUserUIMgr::InitWindow()
{
	m_JoinMeetingForLoginUserUIGroup.InitWindow(m_PaintManager,this);
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) return;
	rc.right = rc.left + 524;
	rc.bottom = rc.top + 376;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), (!(GetWindowStyle(m_hWnd) & WS_CHILD) && (::GetMenu(m_hWnd) != NULL)), GetWindowExStyle(m_hWnd)) ) return;
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, NULL, (ScreenX - (rc.right - rc.left)) / 2, 
		(ScreenY - (rc.bottom - rc.top)) / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_SHOWWINDOW);
}
void CSDKJoinMeetingForLoginUserUIMgr::Notify( TNotifyUI& msg )
{
	m_JoinMeetingForLoginUserUIGroup.Notify(msg);
}
LRESULT CSDKJoinMeetingForLoginUserUIMgr::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
void CSDKJoinMeetingForLoginUserUIMgr::ShowErrorMessage(const wchar_t* error_message)
{
	if (error_message)
		::MessageBox(NULL, error_message, L"error", MB_OK);
}
 CSDKDemoAppEvent* CSDKJoinMeetingForLoginUserUIMgr::GetAppEvent()
 {
 	return m_pAppEvent;
 }
LRESULT CSDKJoinMeetingForLoginUserUIMgr::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return true;
}
LRESULT CSDKJoinMeetingForLoginUserUIMgr::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_JoinMeetingForLoginUserUIGroup.UninitWindow();																								  
	return 0;
}