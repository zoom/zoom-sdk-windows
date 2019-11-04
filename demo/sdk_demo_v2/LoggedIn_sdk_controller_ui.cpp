#include "stdafx.h"
#include "LoggedIn_sdk_controller_ui.h"


CSDKLoggedInUIMgr::CSDKLoggedInUIMgr()
{
	m_demoMeetingType = demo_meetingType_None;
	m_pAppEvent = NULL;
	m_bInMeeting = false;
	m_bReallyLoggedIn = false;
}

CSDKLoggedInUIMgr::~CSDKLoggedInUIMgr()
{
	m_pAppEvent = NULL;
}

void CSDKLoggedInUIMgr::SetEvent(CSDKDemoAppEvent* pAppEvent)
{
	m_pAppEvent = pAppEvent;
}

void CSDKLoggedInUIMgr::InitWindow()
{
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) return;
	rc.right = rc.left + 524;
	rc.bottom = rc.top + 376;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), (!(GetWindowStyle(m_hWnd) & WS_CHILD) && (::GetMenu(m_hWnd) != NULL)), GetWindowExStyle(m_hWnd)) ) return;
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, NULL, (ScreenX - (rc.right - rc.left)) / 2, 
		(ScreenY - (rc.bottom - rc.top)) / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_SHOWWINDOW);

	m_pageBackToMeeting_Video = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(_T("container_returnToMeeting_Video")));
	m_pageBackToMeeting_Audio = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(_T("container_returnToMeeting_Audio")));
	m_pageBackToMeeting_JoinOnly = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(_T("container_returnToMeeting_JoinOnly")));
	m_pageStopDirectShare = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(_T("container_directShare_stop")));
	m_pageStartVideoMeeting = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(_T("container_startVideoMeeting")));
	m_pageStartAudioOnlyMeeting = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(_T("container_startAudioOnlyMeeting")));
	m_pageJoinMeeting = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(_T("container_joinMeetingOnly")));
	m_pageStartDirectShare = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(_T("container_directShare_start")));
	
	m_btnStartVideoMeeting = static_cast<CButtonUI* >(m_PaintManager.FindControl(_T("btn_startVideoMeeting")));
	m_btnStartAudioOnlyMeeting = static_cast<CButtonUI* >(m_PaintManager.FindControl(_T("btn_startAudioOnlyMeeting")));
	m_btnJoinMeeting = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_joinMeeting")));
	m_btnSchedule = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_scheduleMeeting")));
	m_btnConfigure = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_settingMeeting")));
	m_btnStartDirectShare = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_direct_share_start")));
	m_btnLogout = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_logout")));
	m_btnBackToMeeting_Video = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_returnToMeeting_Video")));
	m_btnBackToMeeting_Audio = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_returnToMeeting_Audio")));
	m_btnBackToMeeting_JoinOnly = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_returnToMeeting_JoinOnly")));
	m_btnStopDirectShare = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_direct_share_stop")));

	if(m_pageStopDirectShare)
		m_pageStopDirectShare->SetVisible(false);
	if(m_pageStartDirectShare)
		m_pageStartDirectShare->SetVisible(false);
	if(m_btnStartDirectShare)
		m_btnStartDirectShare->SetVisible(false);
	if(m_btnStopDirectShare)
		m_btnStopDirectShare->SetVisible(false);

	m_loggedInUIWorkFlow.SetUIEvent(this);
}

void CSDKLoggedInUIMgr::Notify(TNotifyUI& msg)
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnStartVideoMeeting)
		{
			m_demoMeetingType = demo_meetingType_Video_Meeting;
			DoStartMeetingBtnClick(true);
		}
		else if(msg.pSender == m_btnStartAudioOnlyMeeting)
		{
			m_demoMeetingType = demo_meetingType_NoVideo_Meeting;
			DoStartMeetingBtnClick(false);
		}
		else if(msg.pSender == m_btnJoinMeeting)
		{
			m_demoMeetingType = demo_meetingType_Join_Meeting;
			DoJoinMeetingBtnClick();
		}
		else if(msg.pSender == m_btnStartDirectShare)
		{
			m_demoMeetingType = demo_meetingType_Direct_Share;
			DoStartDirectShareBtnClick();
		}
		else if(msg.pSender == m_btnLogout)
		{
			DoLogoutBtnClick();
		}
		else if(msg.pSender == m_btnStopDirectShare)
		{
			DoStopDirectShareBtnClick();
		}
		else if(msg.pSender == m_btnSchedule)
		{
			DoScheduleBtnClick();
		}
		else if(msg.pSender == m_btnConfigure)
		{
			DoConfigureBtnClick();
		}
		else if(msg.pSender == m_btnBackToMeeting_Video || msg.pSender == m_btnBackToMeeting_Audio || msg.pSender == m_btnBackToMeeting_JoinOnly)
		{
			DoBackToMeetingBtnClick();
		}

	}
}

LRESULT CSDKLoggedInUIMgr::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT CSDKLoggedInUIMgr::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	

	if(m_bInMeeting)
	{
		if(demo_meetingType_NoVideo_Meeting == m_demoMeetingType || demo_meetingType_Video_Meeting == m_demoMeetingType
			|| demo_meetingType_RestAPI_Start_Meeting == m_demoMeetingType)
			m_loggedInUIWorkFlow.EndMeeting();
		else
			m_loggedInUIWorkFlow.LeaveMeeting();
	}
	
	if(m_pAppEvent && m_bReallyLoggedIn)
		m_pAppEvent->onSwitchToLoginUI(SwitchToLoginUIType_LOGOUT);

	return 0;
}

LRESULT CSDKLoggedInUIMgr::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_loggedInUIWorkFlow.SetUIEvent(NULL);
	return 0;
}

CSDKDemoAppEvent* CSDKLoggedInUIMgr::GetAppEvent()
{
	return m_pAppEvent;
}


void CSDKLoggedInUIMgr::ShowUI(LoggedIn_MeetingUI_type nType_)
{
	if (Demo_Really_LoggedIn == nType_)
		m_bReallyLoggedIn = true;
	else
		m_bReallyLoggedIn = false;
	switch(nType_)
	{
		/* Following code is used for rest api join meeting.
		case Demo_Meeting_RestAPI_Join_Meeting:
			m_demoMeetingType = demo_meetingType_RestAPI_Join_meeting;
			m_bInMeeting = true;
			DisableMeetingButton();
			ShowBackToMeetingButton();
			m_btnLogout->SetVisible(false);
			break;
		*/
		case Demo_Meeting_RestAPI_Start:
			m_demoMeetingType = demo_meetingType_RestAPI_Start_Meeting;
			m_bInMeeting = true;
			DisableMeetingButton();
			ShowBackToMeetingButton();
			m_btnLogout->SetVisible(false);
			break;
		case Demo_Meeting_Join_Only:
			m_demoMeetingType =demo_meetingType_Join_Meeting;
			m_bInMeeting = true;
			DisableMeetingButton();
			ShowBackToMeetingButton();
			m_btnLogout->SetVisible(false);
			break;
		case Demo_Really_LoggedIn:
			m_btnLogout->SetVisible(false);
			break;
		case Demo_Leave_Meeting:
			m_bInMeeting = false;
			m_bConnectToMeeting = false;
			DisableMeetingButton();
			ShowBackToMeetingButton();
			m_btnLogout->SetVisible(false);
			break;
	}

	ShowWindow(true);
}

void CSDKLoggedInUIMgr::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult)
{
	if(m_bReallyLoggedIn)
	{
		switch (status)
		{
		case ZOOM_SDK_NAMESPACE::MEETING_STATUS_CONNECTING:
			{
				m_bInMeeting = false;
				m_bConnectToMeeting = true;
			}
			break;
		case ZOOM_SDK_NAMESPACE::MEETING_STATUS_RECONNECTING:
			{
				if (SDKInterfaceWrap::GetInst().IsSelectCustomizedUIMode() && m_pAppEvent)
					m_pAppEvent->InitCustomizedUI();
			}
			break;
		case ZOOM_SDK_NAMESPACE::MEETING_STATUS_DISCONNECTING:
		case ZOOM_SDK_NAMESPACE::MEETING_STATUS_ENDED:
		case ZOOM_SDK_NAMESPACE::MEETING_STATUS_FAILED:
			{
				m_bInMeeting = false;
				m_bConnectToMeeting = false;
				m_demoMeetingType = demo_meetingType_None;
			}
			break;
		case ZOOM_SDK_NAMESPACE::MEETING_STATUS_INMEETING:
			{
				m_bInMeeting = true;
				m_bConnectToMeeting = false;
			}
		default:
			break;
		}
		updateUI();
	}
}

void CSDKLoggedInUIMgr::onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type)
{
	//to do
}

void CSDKLoggedInUIMgr::onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler)
{
	//to do
}

void CSDKLoggedInUIMgr::onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param)
{
	//to do
}


void CSDKLoggedInUIMgr::ShowErrorMessage(const wchar_t* error_message)
{
	if (error_message)
		::MessageBox(NULL, error_message, L"error", MB_OK);
}

void CSDKLoggedInUIMgr::DisableMeetingButton()
{
	if(NULL == m_btnJoinMeeting || NULL == m_btnStartAudioOnlyMeeting  || NULL == m_btnStartVideoMeeting
		||NULL == m_btnStartDirectShare ||NULL == m_btnSchedule || NULL ==  m_btnStartDirectShare)
		return;

	m_btnJoinMeeting->SetEnabled(false);
	m_btnStartAudioOnlyMeeting->SetEnabled(false);
	m_btnStartVideoMeeting->SetEnabled(false);
	m_btnStartDirectShare->SetEnabled(false);
	m_btnSchedule->SetEnabled(false);
	
	if (m_bReallyLoggedIn && !(m_bInMeeting || m_bConnectToMeeting))
	{
		m_btnJoinMeeting->SetEnabled(true);
		m_btnStartAudioOnlyMeeting->SetEnabled(true);
		m_btnStartVideoMeeting->SetEnabled(true);
		m_btnStartDirectShare->SetEnabled(true);
		m_btnSchedule->SetEnabled(true);
	}
	m_btnStartDirectShare->SetEnabled(false); //hide it for this version
	m_btnStartDirectShare->SetVisible(false); //hide it for this version
}

void CSDKLoggedInUIMgr::ShowBackToMeetingButton()
{	
	/*
	if(m_demoMeetingType == demo_meetingType_None)
		return;
	*/
	if(m_bInMeeting)
	{
		RECT rc;
		
		switch(m_demoMeetingType)
		{
		case demo_meetingType_Video_Meeting:
		case demo_meetingType_RestAPI_Start_Meeting:										  
			rc = m_pageStartVideoMeeting->GetRelativePos();
			m_pageStartVideoMeeting->SetVisible(false);
			m_pageBackToMeeting_Video->SetPos(rc);
			m_pageBackToMeeting_Video->SetVisible(true);
			break;
		case demo_meetingType_NoVideo_Meeting:
			rc = m_pageStartAudioOnlyMeeting->GetRelativePos();
			m_pageStartAudioOnlyMeeting->SetVisible(false);
			m_pageBackToMeeting_Audio->SetPos(rc);
			m_pageBackToMeeting_Audio->SetVisible(true);
			break;
		case demo_meetingType_Join_Meeting:
			rc = m_pageJoinMeeting->GetRelativePos();
			m_pageJoinMeeting->SetVisible(false);
			m_pageBackToMeeting_JoinOnly->SetPos(rc);
			m_pageBackToMeeting_JoinOnly->SetVisible(true);
			break;
		case demo_meetingType_Direct_Share:
			
			rc = m_pageStartDirectShare->GetRelativePos();
			m_pageStopDirectShare->SetPos(rc);
			m_pageStopDirectShare->SetVisible(false);
			m_pageStartDirectShare->SetVisible(false);			
			
			break;
		default:
			break;
		}
	}
	else
	{
		m_pageBackToMeeting_Video->SetVisible(false);
		m_pageBackToMeeting_Audio->SetVisible(false);
		m_pageBackToMeeting_JoinOnly->SetVisible(false);
		m_pageStopDirectShare->SetVisible(false);
		m_pageStartVideoMeeting->SetVisible(true);
		m_pageStartAudioOnlyMeeting->SetVisible(true);
		m_pageJoinMeeting->SetVisible(true);
		m_pageStartDirectShare->SetVisible(false);
	}

}

void CSDKLoggedInUIMgr::updateUI()
{
	DisableMeetingButton();
	ShowBackToMeetingButton();
}

void CSDKLoggedInUIMgr::DoStartMeetingBtnClick(bool bHasVideo)
{
	ZOOM_SDK_NAMESPACE::IMeetingConfiguration* pConfig = SDKInterfaceWrap::GetInst().GetMeetingService()->GetMeetingConfiguration();
	if (pConfig)
	{
		pConfig->EnableAutoEndOtherMeetingWhenStartMeeting(true);
	}
	ZOOM_SDK_NAMESPACE::StartParam startParam;
	startParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_NORMALUSER;
	startParam.param.normaluserStart.vanityID = NULL;
	startParam.param.normaluserStart.hDirectShareAppWnd = NULL;
	startParam.param.normaluserStart.participantId = NULL;
	startParam.param.normaluserStart.isVideoOff = bHasVideo ? false : true;
	startParam.param.normaluserStart.isAudioOff = false;
	startParam.param.normaluserStart.isDirectShareDesktop = false;

	
	if (SDKInterfaceWrap::GetInst().IsSelectCustomizedUIMode() && m_pAppEvent)
		m_pAppEvent->InitCustomizedUI();
	
	if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == m_loggedInUIWorkFlow.StartMeeting(startParam))
	{
		m_bConnectToMeeting = true;
		m_bInMeeting = false;
	}
	else
	{
		ShowErrorMessage(_T("Start meeting failed!"));
		m_bInMeeting = false;
		m_bConnectToMeeting = false;
		m_demoMeetingType = demo_meetingType_None;
	}
	updateUI();
}

void CSDKLoggedInUIMgr::DoJoinMeetingBtnClick()
{
	if(m_pAppEvent)
	{
		m_pAppEvent->onSwitchToJoinMeetingForLoginUserUI();
	}
}

void CSDKLoggedInUIMgr::DoLogoutBtnClick()
{
	::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
}

void CSDKLoggedInUIMgr::DoBackToMeetingBtnClick()
{
	if(m_pAppEvent)
		m_pAppEvent->ActivateCustomizedUI();				
	m_loggedInUIWorkFlow.BringMeetingToFront();
}

void CSDKLoggedInUIMgr::DoStopDirectShareBtnClick()
{
	//todo
}

void CSDKLoggedInUIMgr::DoStartDirectShareBtnClick()
{
	//todo
	m_loggedInUIWorkFlow.DirectShare();
}

void CSDKLoggedInUIMgr::DoScheduleBtnClick()
{
	//todo
	if (m_pAppEvent)
	{
		m_pAppEvent->onSwitchToScheduleMeetingUI();
	}
}

void CSDKLoggedInUIMgr::DoConfigureBtnClick()
{
	if(m_pAppEvent)
	{
		m_pAppEvent->onShowSettingsUI();
	}

}

void CSDKLoggedInUIMgr::OnDirectShareStatusUpdate( ZOOM_SDK_NAMESPACE::DirectShareStatus status, ZOOM_SDK_NAMESPACE::IDirectShareViaMeetingIDOrPairingCodeHandler* handler )
{

}