#include "stdafx.h"
#include "sdk_demo_app.h"
#include "display_cc_ui.h"
void CSDKDemoApp::Run(HINSTANCE hInstance)
{
	CPaintManagerUI::SetInstance(hInstance);

	m_sdk_init_auth_ui = new CSDKInitAuthUIMgr();
	if (!m_sdk_init_auth_ui)
		return;

	m_sdk_login_ui_mgr = new CSDKLoginUIMgr();
	if(!m_sdk_login_ui_mgr)
		return;

	m_sdk_init_auth_ui->SetEvent(this);
	m_sdk_init_auth_ui->Create(NULL, _T("Windows app using zoom win sdk"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	m_sdk_init_auth_ui->SetIcon(IDI_ICON_LOGO);

	m_sdk_login_ui_mgr->SetEvent(this);
	m_sdk_login_ui_mgr->Create(NULL, _T("Windows app using zoom win sdk"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	m_sdk_login_ui_mgr->SetIcon(IDI_ICON_LOGO);
	m_sdk_login_ui_mgr->ShowWindow(false);


	//m_sdk_init_auth_ui->SetEvent(this);
	//m_more_menu_ui = new CMoreMenuUIMgr;
	//m_more_menu_ui->Create(NULL, _T("Windows app using zoom win sdk"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	//m_more_menu_ui->SetIcon(IDI_ICON_LOGO);
	//ClosedCaptionDisplayUI* p = new ClosedCaptionDisplayUI(800, 800);
	//#define WND_STYLE (WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
	//p->Create(NULL, _T("test"), WND_STYLE, WS_EX_WINDOWEDGE|WS_EX_LAYERED);
	//p->ShowWindow(true);


}

void CSDKDemoApp::Stop()
{
	if (m_sdk_init_auth_ui)
	{
		::PostMessage(m_sdk_init_auth_ui->GetHWND(), WM_DESTROY, 0, 0);
	}
	if(m_sdk_login_ui_mgr)
	{
		::PostMessage(m_sdk_login_ui_mgr->GetHWND(), WM_DESTROY, 0, 0);
	}
	if (m_sdk_loggedIn_ui_mgr)
	{
		::PostMessage(m_sdk_loggedIn_ui_mgr->GetHWND(),WM_DESTROY, 0, 0);
	}
	if(m_sdk_settings_ui_mgr)
	{
		::PostMessage(m_sdk_settings_ui_mgr->GetHWND(),WM_DESTROY, 0, 0);
	}
	if (m_schedule_meeting_ui_mgr)
	{
		::PostMessage(m_schedule_meeting_ui_mgr->GetHWND(),WM_DESTROY, 0, 0);
	}
	if (m_sdk_join_meeting_for_login_user_ui_mgr)
	{
		::PostMessage(m_sdk_join_meeting_for_login_user_ui_mgr->GetHWND(), WM_DESTROY, 0, 0);
	}
	::PostQuitMessage(0);
}

CSDKDemoApp::CSDKDemoApp()
{
	m_sdk_init_auth_ui = NULL;
	m_sdk_login_ui_mgr = NULL;
	m_sdk_loggedIn_ui_mgr = NULL;
	m_schedule_meeting_ui_mgr = NULL;
	m_sdk_settings_ui_mgr = NULL;
	m_sdk_join_meeting_for_login_user_ui_mgr = NULL;
	m_customizedMeetingUI = NULL;
	m_more_menu_ui = NULL;
}

CSDKDemoApp::~CSDKDemoApp()
{
	if(m_customizedMeetingUI)
	{
		delete m_customizedMeetingUI;
		m_customizedMeetingUI = NULL;
	}

	if (m_sdk_init_auth_ui)
	{
		delete m_sdk_init_auth_ui;
		m_sdk_init_auth_ui = NULL;
	}

	if (m_sdk_login_ui_mgr)
	{
		delete m_sdk_login_ui_mgr;
		m_sdk_login_ui_mgr = NULL;
	}

	if(m_sdk_loggedIn_ui_mgr)
	{
		delete m_sdk_loggedIn_ui_mgr;
		m_sdk_loggedIn_ui_mgr = NULL;
	}

	if (m_schedule_meeting_ui_mgr)
	{
		delete m_schedule_meeting_ui_mgr;
		m_schedule_meeting_ui_mgr = NULL;
	}

	if(m_sdk_settings_ui_mgr)
	{
		delete m_sdk_settings_ui_mgr;
		m_sdk_settings_ui_mgr = NULL;
	}

	if (m_sdk_join_meeting_for_login_user_ui_mgr)
	{
		delete m_sdk_join_meeting_for_login_user_ui_mgr;
		m_sdk_join_meeting_for_login_user_ui_mgr = NULL;
	}
}

void CSDKDemoApp::onSwitchToLoginUI(SwitchToLoginUIType type_)
{
	//hide no use ui and show login ui
	CRect rc(0,0,0,0);
	HWND hwndUI(NULL);
	if (m_sdk_init_auth_ui)
	{
		hwndUI = m_sdk_init_auth_ui->GetHWND();
		if(NULL != hwndUI)
			::GetWindowRect(hwndUI, &rc);
		m_sdk_init_auth_ui->ShowWindow(false);
	}
	
	if(m_sdk_loggedIn_ui_mgr)
	{
		hwndUI = m_sdk_loggedIn_ui_mgr->GetHWND();
		if(NULL != hwndUI)
			::GetWindowRect(hwndUI, &rc);
		m_sdk_loggedIn_ui_mgr->ShowWindow(false);								   
	}

	if (m_sdk_login_ui_mgr)
	{
		hwndUI = m_sdk_login_ui_mgr->GetHWND();
		m_sdk_login_ui_mgr->SwitchToWaitingPage(L"",false);
		m_sdk_login_ui_mgr->ShowWindow(true);
		ActiveWindowToTop(hwndUI);
	}

	if (m_schedule_meeting_ui_mgr)
	{
		hwndUI = m_schedule_meeting_ui_mgr->GetHWND();
		if(NULL != hwndUI)
		{
			DestroyWindow(hwndUI);
			m_schedule_meeting_ui_mgr = NULL;
		}	
	}

	if (m_sdk_settings_ui_mgr)
	{
		hwndUI = m_sdk_settings_ui_mgr->GetHWND();
		if(NULL != hwndUI)
		{
			DestroyWindow(hwndUI);
		    m_sdk_settings_ui_mgr = NULL;
		}
	}

	if (m_sdk_join_meeting_for_login_user_ui_mgr)
	{
		m_sdk_join_meeting_for_login_user_ui_mgr->ShowWindow(false);
	}
	//

	switch (type_)
	{
	case SwitchToLoginUIType_AUTHDONE:
		{
			if (m_sdk_login_ui_mgr)
			{
				m_sdk_login_ui_mgr->NotifyAuthDone();
			}
		}
		break;
	case SwitchToLoginUIType_LOGOUT:
		{
			if (m_sdk_login_ui_mgr)
			{
				m_sdk_login_ui_mgr->LogOut();
			}
		}
		break;
	case SwitchToLoginUIType_MeetingEND:
	case SwitchToLoginUIType_LOGINFAILED:
	case SwitchToLoginUIType_MEETINGFAILED:
	default:
		break;
	}

}

void CSDKDemoApp::onShowLoggedInUI(LoggedIn_MeetingUI_type nType_)
{
	//first to delete the old instance if there is any
	if(m_sdk_loggedIn_ui_mgr)
	{
		DestroyWindow(m_sdk_loggedIn_ui_mgr->GetHWND());
		//delete m_sdk_loggedIn_ui_mgr;
		m_sdk_loggedIn_ui_mgr = NULL;
	}

	m_sdk_loggedIn_ui_mgr = new CSDKLoggedInUIMgr();
	if(NULL == m_sdk_loggedIn_ui_mgr)
		return;

	m_sdk_loggedIn_ui_mgr->SetEvent(this);
	m_sdk_loggedIn_ui_mgr->Create(NULL, _T("Windows app using zoom win sdk"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	m_sdk_loggedIn_ui_mgr->SetIcon(IDI_ICON_LOGO);

	CRect rc(0,0,0,0);
	HWND hwndUI(NULL);
	hwndUI = m_sdk_login_ui_mgr->GetHWND();
	if(NULL != hwndUI)
		::GetWindowRect(m_sdk_login_ui_mgr->GetHWND(), &rc);
	hwndUI = m_sdk_loggedIn_ui_mgr->GetHWND();
	if(rc.Height() != 0 && rc.Width() != 0 && NULL != hwndUI)
		::MoveWindow(hwndUI,rc.left,rc.top,rc.Width(),rc.Height(),FALSE);

	m_sdk_loggedIn_ui_mgr->ShowUI(nType_);

	if(m_sdk_login_ui_mgr)
	{
		m_sdk_login_ui_mgr->ShowWindow(false);
	}
}
void CSDKDemoApp::onShowSettingsUI(SettingsUI_page nPage)
{
	if(m_sdk_settings_ui_mgr)
	{
		DestroyWindow(m_sdk_settings_ui_mgr->GetHWND());
		m_sdk_settings_ui_mgr = NULL;
	}
	m_sdk_settings_ui_mgr = new CSDKSettingsUIMgr();
	if(NULL == m_sdk_settings_ui_mgr)
	{
		return;
	}

	//m_sdk_settings_ui_mgr->SetEvent(this);
	m_sdk_settings_ui_mgr->Create(NULL,_T("Settings"),UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	m_sdk_settings_ui_mgr->SetIcon(IDI_ICON_LOGO);
	m_sdk_settings_ui_mgr->SwitchToPage(nPage);

}
void CSDKDemoApp::onSwitchToJoinMeetingForLoginUserUI()
{
	if(m_sdk_join_meeting_for_login_user_ui_mgr)
	{
		DestroyWindow(m_sdk_join_meeting_for_login_user_ui_mgr->GetHWND());
		m_sdk_join_meeting_for_login_user_ui_mgr = NULL;
	}
	m_sdk_join_meeting_for_login_user_ui_mgr = new CSDKJoinMeetingForLoginUserUIMgr();
	if(NULL == m_sdk_join_meeting_for_login_user_ui_mgr)
	{
		return;
	}
	m_sdk_join_meeting_for_login_user_ui_mgr->SetEvent(this);
	m_sdk_join_meeting_for_login_user_ui_mgr->Create(NULL,_T("Join meeting"),UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	m_sdk_join_meeting_for_login_user_ui_mgr->SetIcon(IDI_ICON_LOGO);
	m_sdk_join_meeting_for_login_user_ui_mgr->ShowWindow(true);
}

void CSDKDemoApp::onQuitApp()
{
	Stop();
}

void CSDKDemoApp::onLoginFailed()
{
	onSwitchToLoginUI(SwitchToLoginUIType_LOGINFAILED);
	if (m_sdk_login_ui_mgr)
	{
		m_sdk_login_ui_mgr->ChangeUIforLoginFailed();
	}
}

void CSDKDemoApp::onJoinFailed()
{
 	onSwitchToLoginUI(SwitchToLoginUIType_MEETINGFAILED);
	if(m_sdk_loggedIn_ui_mgr)
	{
		m_sdk_loggedIn_ui_mgr->ShowWindow(false);
	}
 	if (m_sdk_login_ui_mgr)
 	{
		m_sdk_login_ui_mgr->ChangeUIforJoinFailed();
 	}
}

void CSDKDemoApp::onSwitchToScheduleMeetingUI()
{
	//m_schedule_meeting_ui_mgr = new CSDKSheduleMeetingUIMgr();
	if (m_schedule_meeting_ui_mgr)
	{
		::DestroyWindow(m_schedule_meeting_ui_mgr->GetHWND());
		m_schedule_meeting_ui_mgr = NULL;
	}
	
	m_schedule_meeting_ui_mgr = new CSDKSheduleMeetingUIMgr();


	if(NULL == m_schedule_meeting_ui_mgr)
		return;
	m_schedule_meeting_ui_mgr->SetEvent(this);
	m_schedule_meeting_ui_mgr->Create(NULL, _T("Windows app using zoom win sdk"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	m_schedule_meeting_ui_mgr->SetIcon(IDI_ICON_LOGO);
	m_schedule_meeting_ui_mgr->ShowWindow(true);
}

void CSDKDemoApp::InitCustomizedUI()
{
	if (SDKInterfaceWrap::GetInst().IsSelectCustomizedUIMode())
	{
		if(NULL == m_customizedMeetingUI)
		{
			m_customizedMeetingUI = new CCustomizeInMeetingUIMgr();
			if(m_customizedMeetingUI)
				m_customizedMeetingUI->SetEvent(this);
		}
		else
		{
			m_customizedMeetingUI->Init();
			m_customizedMeetingUI->SetEvent(this);
		}
	}
}

void CSDKDemoApp::ActivateCustomizedUI()
{
	if(m_customizedMeetingUI)
	{
		m_customizedMeetingUI->ActivateUI();
	}

}

void CSDKDemoApp::onShowChatWindow()
{
	if(m_customizedMeetingUI)
	{
		m_customizedMeetingUI->ShowHideChatWindow();
	}
}

void CSDKDemoApp::onShowCameraControlWindow()
{
	if(m_customizedMeetingUI)
	{
		m_customizedMeetingUI->ShowHideCameraControlWindow();
	}
}

void CSDKDemoApp::onShowShareWindow()
{
	if(m_customizedMeetingUI)
	{
		m_customizedMeetingUI->ShowShareWindow();
	}
}

void CSDKDemoApp::onShowGalleryViewWindow()
{
	if(m_customizedMeetingUI)
	{
		m_customizedMeetingUI->ShowHideGalleryViewWindow();
	}
}

void CSDKDemoApp::onShowParticipantWindow()
{
	if(m_customizedMeetingUI)
	{
		m_customizedMeetingUI->ShowHideParticipantWindow();
	}
}
void CSDKDemoApp::onPageButtonClick(ArrowButtonType btnType)
{
	if(m_customizedMeetingUI)
	{
		m_customizedMeetingUI->PageButtonClick(btnType);
	}
}

void CSDKDemoApp::onShowMoreMenuWindow(int x, int y)
{
	if (m_customizedMeetingUI)
	{
		m_customizedMeetingUI->ShowHideMoreMenuWindow(x, y);
	}
}
