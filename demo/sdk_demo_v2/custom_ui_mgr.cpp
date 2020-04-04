#include "stdafx.h"
#include "custom_ui_mgr.h"

//#include <atlbase.h>
//#include "./wtl/atlapp.h"
//#include "./wtl/atluser.h"

void CCustomizeInMeetingUIMgr::onVideoContainerDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer* pContainer)
{
	if(m_pCustomizeUIVideoMgr)
	{
		m_pCustomizeUIVideoMgr->HandleVideoContainerDestroyed(pContainer);
	}	
}

void CCustomizeInMeetingUIMgr::onShareRenderDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* pRender)
{
	if(m_pCustomizeShareMgr)
	{
		m_pCustomizeShareMgr->HandleShareRenderDestroyed(pRender);
	}
}

void CCustomizeInMeetingUIMgr::onSize(RECT& rc)
{
	int nWidth = 0;
	int nHeight = 0;
	rc.bottom = rc.bottom - DEFAULT_TOOLBAR_HEIGHT;
	if(m_bShowGalleryView)
	{
		nWidth = rc.right - rc.left;
		if(nWidth <= Custom_Smallest_UI_Weight)
			rc.right = rc.left + Custom_Smallest_UI_Weight;
		nHeight = rc.bottom - rc.top;
		if(nHeight <= Custom_Smallest_UI_Height)
			rc.bottom = rc.top + Custom_Smallest_UI_Height;

	}	

	if (m_pCustomizeUIVideoMgr)
		m_pCustomizeUIVideoMgr->HandleSizeChanged(rc);

	if(m_bInMeeting)
		m_pToolbarMgr.ResizeToolbarBottom();
	
	if(m_bShowGalleryView)
	{
		if(m_upArrowWindow)
			m_upArrowWindow->HandleSizeChanged(rc);
		if(m_downArrowWindow)
			m_downArrowWindow->HandleSizeChanged(rc);
	}	

	HideMenuWhenMenuVisible();
	if (m_display_cc_ui)
	{
		m_display_cc_ui->HandleSizeChanged(m_hOwnerHwnd);
	}
	if (m_more_menu_ui)
	{
		m_more_menu_ui->HandleMoveAndResize();
	}
}

void CCustomizeInMeetingUIMgr::onDestroyed()
{
	/*
	UninitUserList();
	DestroyArrowWindow();
	DestroyChatWindow();
	DestroyParticipantWindow();
	*/
	DestroyAllSubWindow();
	if(m_bNeedCallEndMeeting)
	{
		if(NULL == m_pToolbarMgr.GetParentWnd())
		{
			m_pToolbarMgr.SetEvent(m_pAppEvent);
			m_pToolbarMgr.SetParentWnd(m_hOwnerHwnd);
		}
		m_pToolbarMgr.EndMeeting();
	}
	else
	{
		m_customUIWorkFlow.Uninit();
	}
}

void CCustomizeInMeetingUIMgr::onRenderUserChanged(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement, unsigned int userid)
{

}

void CCustomizeInMeetingUIMgr::onRenderDataTypeChanged(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement, ZOOM_SDK_NAMESPACE::VideoRenderDataType dataType)
{

}

void CCustomizeInMeetingUIMgr::onLayoutNotification(RECT wnd_client_rect)
{
	DoLayout();
}

void CCustomizeInMeetingUIMgr::onVideoRenderElementDestroyed(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement)
{
	if(m_pCustomizeUIVideoMgr)
		m_pCustomizeUIVideoMgr->HandleVideoRenderElementDestroyed(pElement);

}

void CCustomizeInMeetingUIMgr::onSharingShareAnnotationStatusChanged(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_)
{
	if(m_pCustomizeShareMgr)
		m_pCustomizeShareMgr->HandleSharingShareAnnotationStatusChanged(share_render_, status_);
}

void CCustomizeInMeetingUIMgr::onVideoContainerWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (m_pCustomizeShareMgr)
		m_pCustomizeShareMgr->HandleShareRenderWindowMsgNotification(uMsg, wParam, lParam);
	return;
}

void CCustomizeInMeetingUIMgr::onSharingContentStartRecving()
{
	//to do
}

void CCustomizeInMeetingUIMgr::onSharingSourceUserIDNotification(unsigned int userid)
{
	//to do
}

void CCustomizeInMeetingUIMgr::onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper)
{
}

void CCustomizeInMeetingUIMgr::onShareRenderWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam)
{   
	if(m_pCustomizeShareMgr)
		m_pCustomizeShareMgr->HandleShareRenderWindowMsgNotification(uMsg, wParam, lParam);
}

CCustomizeInMeetingUIMgr::CCustomizeInMeetingUIMgr()
{
	Reset();
	m_customUIWorkFlow.Init(this); //can't call this in reset() function because stop will call it too.
	InitUserList();
}

void CCustomizeInMeetingUIMgr::Init()
{
	DestroyAllSubWindow();
	Reset();
	m_customUIWorkFlow.Init(this); //can't call this in reset() function because stop will call it too.
	InitUserList();
}

ZOOM_SDK_NAMESPACE::ICustomizedUIMgr* CCustomizeInMeetingUIMgr::GetCustomizedMgr()
{
	return m_pCustomUIMgr;
}

void CCustomizeInMeetingUIMgr::SetEvent(CSDKDemoAppEvent* pAppEvent)
{
	m_pAppEvent = pAppEvent;
	m_bNeedCallEndMeeting = true;
}

void CCustomizeInMeetingUIMgr::Reset()
{
	m_upArrowWindow = NULL;
	m_downArrowWindow = NULL;
	m_pAppEvent = NULL;
	m_pUserList = NULL;
	m_pCustomUIMgr = NULL;
	m_pCustomizeUIVideoMgr = NULL;
	m_pCustomizeShareMgr = NULL;
	m_pMeetingService = NULL;
	m_pChatUIMgr = NULL;
	m_pCameraControlWin = NULL;
	m_pParticipantUIMgr = NULL;	
	m_bShowGalleryView = false;
	m_bInMeeting = false;
	m_bUIIsReady = false;
	m_bInChat = false;
	m_bInCameraControl = false;
	m_bInShowParticipant = false;
	m_more_menu_ui = NULL;
	m_display_cc_ui = NULL;
}

void CCustomizeInMeetingUIMgr::DestroyAllSubWindow()
{
	m_pToolbarMgr.UnInit();
	UninitUserList();
	DestroyArrowWindow();
	DestroyChatWindow();
	DestroyParticipantWindow();
	DestroyMoreMenuWindow();
	DestroyDisplayCCWnd();
}
void CCustomizeInMeetingUIMgr::InitUserList()
{
	if(m_pUserList)
	{
		m_pUserList->ClearAll();
	}
	else
	{
		m_pUserList = new CSDKUserList();
	}
}

void CCustomizeInMeetingUIMgr::UninitUserList()
{
	if(m_pUserList)
	{
		m_pUserList->ClearAll();
		delete m_pUserList;
		m_pUserList = NULL;
	}
}

void CCustomizeInMeetingUIMgr::UpdateUserList()
{
	InitUserList();
	if(m_pMeetingService)
	{
		ZOOM_SDK_NAMESPACE::IMeetingParticipantsController* pUserCtrl = m_pMeetingService->GetMeetingParticipantsController();
		if(!pUserCtrl)
			return;
		ZOOM_SDK_NAMESPACE::IList<unsigned int>* lstUser = pUserCtrl->GetParticipantsList();
		if (lstUser)
		{
			int count = lstUser->GetCount();
			for (int i = 0; i < count; i++)
			{
				int userId = lstUser->GetItem(i);
				if(0 == userId)
					continue;
				ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = pUserCtrl->GetUserByUserID(userId);
				if(pUserInfo)
					m_pUserList->AddItem(pUserInfo);
			}
		}
	}
}

void CCustomizeInMeetingUIMgr::CreateArrowWindow()
{
	if(NULL == m_upArrowWindow)
	{
		m_upArrowWindow = new CArrowWindow(this);
		if(m_upArrowWindow)
		{
			m_upArrowWindow->Create(m_hOwnerHwnd, _T("custom ui arrow window"), WS_CHILDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_TOPMOST);
			m_upArrowWindow->EnableUsingButton(Arrow_button_up);
			m_upArrowWindow->ShowWindow(false);
		}
	}
	if(NULL == m_downArrowWindow)
	{
		m_downArrowWindow = new CArrowWindow(this);
		if(m_downArrowWindow)
		{
			m_downArrowWindow->Create(m_hOwnerHwnd, _T("custom ui arrow window"),  WS_CHILDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_TOPMOST);
			m_downArrowWindow->EnableUsingButton(Arrow_button_down);
			m_downArrowWindow->ShowWindow(false);
		}
	}	
}

void CCustomizeInMeetingUIMgr::DestroyArrowWindow()
{
	if(m_upArrowWindow)
	{
		if(::IsWindow(m_upArrowWindow->GetHWND()))
		{
			m_upArrowWindow->DestroyWindow();
		}
		delete m_upArrowWindow;
		m_upArrowWindow = NULL;
	}

	if(m_downArrowWindow)
	{
		if(::IsWindow(m_downArrowWindow->GetHWND()))
		{
			m_downArrowWindow->DestroyWindow();
		}
		delete m_downArrowWindow;
		m_downArrowWindow = NULL;
	}
}

void CCustomizeInMeetingUIMgr::CreateChatWindow()
{
	if(NULL == m_pChatUIMgr)
	{
		m_pChatUIMgr = new CSDKMeetingChatUIMgr(this);
		if(m_pChatUIMgr)
		{
			m_pChatUIMgr->Create(NULL, _T("Windows app using zoom win sdk"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
			m_pChatUIMgr->ShowWindow(false);
			m_pChatUIMgr->SetIcon(IDI_ICON_LOGO);
			m_pChatUIMgr->HandleUserChanged();
		}
	}
}
void CCustomizeInMeetingUIMgr::DestroyChatWindow()
{
	if(m_pChatUIMgr)
	{
		if(::IsWindow(m_pChatUIMgr->GetHWND()))
		{
			m_pChatUIMgr->DestroyWindow();
		}
		delete m_pChatUIMgr;
		m_pChatUIMgr = NULL;
	}
}

void CCustomizeInMeetingUIMgr::CreateCameraControlWindow()
{
	if(NULL == m_pCameraControlWin)
	{
		m_pCameraControlWin = new CameraControlWindow(this);
		if(m_pCameraControlWin)
		{
			m_pCameraControlWin->Create(m_hOwnerHwnd, _T("Camera Controller"), WS_OVERLAPPED | WS_CAPTION | WS_CHILDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
			m_pCameraControlWin->ShowWindow(false);
		}
	}
}

void CCustomizeInMeetingUIMgr::DestroyCameraControlWindow()
{
	if(m_pCameraControlWin)
	{
		if(::IsWindow(m_pCameraControlWin->GetHWND()))
		{
			m_pCameraControlWin->DestroyWindow();
		}
		delete m_pCameraControlWin;
		m_pCameraControlWin = NULL;
	}
}

void CCustomizeInMeetingUIMgr::CreateParticipantWindow()
{
	if(NULL == m_pParticipantUIMgr)
	{
		m_pParticipantUIMgr = new CParticipantUIMgr(this);
		if(m_pParticipantUIMgr)
		{			
			m_pParticipantUIMgr->Create(m_hOwnerHwnd, PARTICIPANT_UI_TITLE, WS_OVERLAPPED|WS_CAPTION | WS_CHILDWINDOW| WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
			m_pParticipantUIMgr->HandleUserChanged(SDK_USER_UPDATE);
			m_pParticipantUIMgr->ShowWindow(false);
		}
	}
}
void CCustomizeInMeetingUIMgr::DestroyParticipantWindow()
{
	if(m_pParticipantUIMgr)
	{
		if(::IsWindow(m_pParticipantUIMgr->GetHWND()))
		{
			m_pParticipantUIMgr->DestroyWindow();
		}
		delete m_pParticipantUIMgr;
		m_pParticipantUIMgr = NULL;
	}
}
void CCustomizeInMeetingUIMgr::ActivateUI()
{
	if(m_hOwnerHwnd && ::IsWindow(m_hOwnerHwnd))
	{
		if(::IsIconic(m_hOwnerHwnd))
			::ShowWindow(m_hOwnerHwnd, SW_RESTORE);
		::SetWindowPos(m_hOwnerHwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
	}
}

CSDKUserList* CCustomizeInMeetingUIMgr::GetUserList()
{
	return m_pUserList;
}

void CCustomizeInMeetingUIMgr::HandleChatWindowBeClosed()
{
	/* The following code is used to reset the status chat window once it is closed.
	if(m_pChatUIMgr)
	{
		m_pChatUIMgr = NULL;
		m_bInChat = !m_bInChat;
		m_pToolbarMgr.SetChatUIStatus(m_bInChat);
	}
	*/
	if(m_pChatUIMgr)
	{
		ShowHideChatWindow();
	}
}

bool CCustomizeInMeetingUIMgr::InitCustomizeUIVideoMgr()
{
	m_bUIIsReady = false;
	if(!m_pCustomizeUIVideoMgr)
	{
		m_pCustomizeUIVideoMgr = new CCustomizeUIVideoMgr(this);
	}
	if(!m_pCustomizeUIVideoMgr)
		return false;

	RECT rc = {0};
	::GetClientRect(m_hOwnerHwnd, &rc);

	m_pCustomizeUIVideoMgr->init();
	//m_pCustomizeUIVideoMgr->SetEvent(this);
	m_pCustomizeUIVideoMgr->CreateCustomVideoContainer(m_pCustomUIMgr, m_hOwnerHwnd, rc);
	m_pCustomizeUIVideoMgr->Show();
	m_bUIIsReady = true;
	return true;
}

bool CCustomizeInMeetingUIMgr::InitCustomShareRender()
{
	m_bUIIsReady = false;
	if(!m_pCustomizeShareMgr)
		m_pCustomizeShareMgr = new CCustomizeUIShareMgr(this);

	if (NULL == m_pCustomizeShareMgr)
		return false;
	m_pCustomizeShareMgr->Init();
	m_pCustomizeShareMgr->SetEvent(this);
	m_pCustomizeShareMgr->CreateCustomShareRender(m_pCustomUIMgr);
	m_bUIIsReady = true;;
	return true;
}

void CCustomizeInMeetingUIMgr::Start()
{
	do 
	{
		if (m_bUIIsReady)
			break;
		ZOOM_SDK_NAMESPACE::CreateCustomizedUIMgr(&m_pCustomUIMgr);

		if (NULL == m_pCustomUIMgr || ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != m_pCustomUIMgr->HasLicense())
			break;
	
		m_pCustomUIMgr->SetEvent(this);

		create_owner_hwnd(this, Custom_MeetingUI_Width, Custom_MeetingUI_Height);
		if (NULL == m_hOwnerHwnd || !::IsWindow(m_hOwnerHwnd))
			break;
		
		if(!InitCustomizeUIVideoMgr())
			break;

		m_bUIIsReady = true;
	} while (false);

	if (!m_bUIIsReady)
	{
		if (m_pCustomUIMgr)
		{			
			if (m_pCustomizeUIVideoMgr)
			{
				m_pCustomizeUIVideoMgr->uninit();
				m_pCustomizeUIVideoMgr = NULL;
			}

			if (m_pCustomizeShareMgr)
			{
				m_pCustomizeShareMgr->uninit();
				m_pCustomizeShareMgr = NULL;
			}
		}
	}
}

void CCustomizeInMeetingUIMgr::Stop()
{

	if (m_bUIIsReady && m_pCustomUIMgr)
	{
		m_bShowGalleryView = false;
		m_bInMeeting = false;
		m_bNeedCallEndMeeting = false;
		m_pCustomUIMgr->DestroyAllVideoContainer();
		m_pCustomizeShareMgr->DestroyAllShareWindows();
		m_pCustomUIMgr->DestroyAllShareRender();
		DestroyAllSubWindow();
		Reset();
		ZOOM_SDK_NAMESPACE::DestroyCustomizedUIMgr(m_pCustomUIMgr);
		destroy_owner_wnd();
	}
}

void CCustomizeInMeetingUIMgr::ShowPreview()
{
	if (m_bUIIsReady && m_pCustomizeUIVideoMgr)
	{
		::GetClientRect(m_hOwnerHwnd, &m_rcVideo);
		m_pCustomizeUIVideoMgr->ShowPreviewVideo(m_rcVideo);
	}
}

void CCustomizeInMeetingUIMgr::StopPreview()
{
	if (m_bUIIsReady && m_pCustomizeUIVideoMgr)
	{
		m_pCustomizeUIVideoMgr->HidePreviewVideo();
	}
}

void CCustomizeInMeetingUIMgr::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult /*= 0*/)
{
	switch (status)
	{
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_CONNECTING:
		{
			if (!m_bUIIsReady)
				Start();

			ShowPreview();
		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_RECONNECTING:
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_DISCONNECTING:
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_ENDED:
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_FAILED:
		{
			if (m_bUIIsReady)
			{
				Stop();
			}
		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_INMEETING:
		{
			HandleInMeeting();
		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_IN_WAITING_ROOM:
		HandleMoveToWaitingRoom();
		break;
	default:
		break;
	}
}

void CCustomizeInMeetingUIMgr::SetSDKMeetingService(ZOOM_SDK_NAMESPACE::IMeetingService* meeting_service_)
{
	m_pMeetingService = meeting_service_;
	// to do
	/*
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationControllerEvent* anno_ctrl_cb = NULL;
	if (meeting_service_)
	{
		anno_ctrl_cb = this;
	}
	if (_meeting_service->GetAnnotationController()
		&& _meeting_service->GetAnnotationController()->GetCustomizedAnnotationController())
		_meeting_service->GetAnnotationController()->GetCustomizedAnnotationController()->SetEvent(anno_ctrl_cb);
	*/
}

void CCustomizeInMeetingUIMgr::HandleInMeeting()
{
	InitCustomShareRender();
	m_bInMeeting = true;
	if (NULL == m_pCustomizeUIVideoMgr || NULL == m_pCustomizeShareMgr)
		return;

	CreateArrowWindow();
	m_pCustomizeUIVideoMgr->CalulateViewRect();
	m_pCustomizeUIVideoMgr->ShowActiveViewVideo();
	
	m_pCustomizeShareMgr->ShowSharedContent();
	ShowToolbar();
	UpdateToolbarButtons();
	DoLayout();
	UpdateUserList();
	UpdateMeetingTitle();
}

void CCustomizeInMeetingUIMgr::HandleMoveToWaitingRoom()
{
	if (m_pCustomUIMgr)
	{
		DestroyAllSubWindow();
		//we can do better here
		if(m_pCustomizeUIVideoMgr)
			m_pCustomizeUIVideoMgr->uninit();
		InitCustomizeUIVideoMgr();

		if(m_bUIIsReady)
			ShowPreview();
		UpdateMeetingTitle(true);
	}
}

void CCustomizeInMeetingUIMgr::ShowToolbar()
{
	//if show toolbar, resize the container
	RECT rc ={0};
	::GetClientRect(m_hOwnerHwnd, &rc);
	rc.bottom = rc.bottom - DEFAULT_TOOLBAR_HEIGHT;
	
	if(m_pCustomizeUIVideoMgr)
		m_pCustomizeUIVideoMgr->HandleSizeChanged(rc);

	m_pToolbarMgr.SetEvent(m_pAppEvent);
	m_pToolbarMgr.SetParentWnd(m_hOwnerHwnd);
	m_pToolbarMgr.ShowToolbarBottom();
}

void CCustomizeInMeetingUIMgr::UpdateToolbarButtons()
{
	if(m_customUIWorkFlow.IsVideoOn())
	{
		m_pToolbarMgr.UpdateButton(Toolbar_Button_Video, Button_UnMuted);
	}
	else
	{
		m_pToolbarMgr.UpdateButton(Toolbar_Button_Video, Button_Muted);
	}
	if(m_customUIWorkFlow.IsAudioOn())
	{
		m_pToolbarMgr.UpdateButton(Toolbar_Button_Audio, Button_UnMuted);
	}
	else
	{
		m_pToolbarMgr.UpdateButton(Toolbar_Button_Audio, Button_Muted);
	}
	if(m_pCustomizeShareMgr)
	{
		if(m_pCustomizeShareMgr->IsInSendShareMode())
			m_pToolbarMgr.UpdateButton(Toolbar_Button_Share, Button_Muted);
		else
			m_pToolbarMgr.UpdateButton(Toolbar_Button_Share, Button_UnMuted);
	}
}

void CCustomizeInMeetingUIMgr::DoLayout()
{
	if(m_pCustomizeUIVideoMgr)
	{
		m_pCustomizeUIVideoMgr->CalulateViewRect();
	}
	DoLayoutActiveVideo();
	DoLayoutNormalVideo();
}

void CCustomizeInMeetingUIMgr::DoLayoutActiveVideo()
{
	if(m_pCustomizeUIVideoMgr)
		m_pCustomizeUIVideoMgr->ShowActiveViewVideo();
}

void CCustomizeInMeetingUIMgr::DoLayoutNormalVideo()
{
	if(m_pCustomizeUIVideoMgr)
	{
		if(m_bShowGalleryView)
			m_pCustomizeUIVideoMgr->ShowGalleryViewVideo();
		else
			m_pCustomizeUIVideoMgr->HideGalleryViewVideo();
	}
}

void CCustomizeInMeetingUIMgr::onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId)
{
	m_pCustomizeShareMgr->onRemoteControlStatus(status, userId);
}

void CCustomizeInMeetingUIMgr::onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId)
{
	if(m_pCustomizeShareMgr)
		m_pCustomizeShareMgr->HandleSharingStatus(status, userId);
}	

void CCustomizeInMeetingUIMgr::onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList /*= NULL*/)
{
	if (!m_bInMeeting || NULL == lstUserID)
		return;

	if(NULL == m_pMeetingService || NULL == m_pUserList)
		return;
	int count = lstUserID->GetCount();
	for (int i = 0; i < count; i++)
	{
		int userId = lstUserID->GetItem(i);
		ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = m_pMeetingService->GetMeetingParticipantsController()->GetUserByUserID(userId);
		if(pUserInfo)
			m_pUserList->AddItem(pUserInfo);
	}
	if(m_pCustomizeUIVideoMgr)
	{
		m_pCustomizeUIVideoMgr->HandleUserChanged();
	}
	if(m_pChatUIMgr)
	{
		m_pChatUIMgr->HandleUserChanged();
	}
	if(m_pParticipantUIMgr)
	{
		m_pParticipantUIMgr->HandleUserChanged(SDK_USER_JOIN);
	}
	if(m_pCustomizeShareMgr)
	{
		m_pCustomizeShareMgr->HandleUserChanged();
	}
	if (m_more_menu_ui)
	{
		m_more_menu_ui->HandleUserChange();
	}
	
}

void CCustomizeInMeetingUIMgr::onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList /*= NULL*/)
{
	if (!m_bInMeeting || NULL == lstUserID)
		return;
	if(NULL == m_pMeetingService || NULL == m_pUserList)
		return;
	int count = lstUserID->GetCount();
	for (int i = 0; i < count; i++)
	{
		int userId = lstUserID->GetItem(i);
		m_pUserList->RemoveItemByID(userId);
	}
	if(m_pCustomizeUIVideoMgr)
	{
		m_pCustomizeUIVideoMgr->HandleUserChanged();
	}
	if(m_pChatUIMgr)
	{
		m_pChatUIMgr->HandleUserChanged();
	}
	if(m_pParticipantUIMgr)
	{
		m_pParticipantUIMgr->HandleUserChanged(SDK_USER_LEFT);
	}
	if (m_more_menu_ui)
	{
		m_more_menu_ui->HandleUserChange();
	}
}

void CCustomizeInMeetingUIMgr::onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList)
{
	if(m_pParticipantUIMgr)
	{
		m_pParticipantUIMgr->HandleUserChanged(SDK_USER_UPDATE);
	}

	ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->GetUserByUserID(0);
	if (pUserInfo)
	{
		bool bMuted = pUserInfo->IsAudioMuted();
		if (bMuted)
		{
			m_pToolbarMgr.UpdateButton(Toolbar_Button_Audio, Button_Muted);
		}
		else
		{
			m_pToolbarMgr.UpdateButton(Toolbar_Button_Audio, Button_UnMuted);
		}
	}
	
}

void CCustomizeInMeetingUIMgr::onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status)
{
	if(m_pParticipantUIMgr)
	{
		m_pParticipantUIMgr->HandleUserChanged(SDK_USER_UPDATE);
	}

	ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->GetUserByUserID(0);
	if (pUserInfo)
	{
		bool bMuted = pUserInfo->IsVideoOn();
		if (bMuted)
		{
			m_pToolbarMgr.UpdateButton(Toolbar_Button_Video, Button_UnMuted);
		}
		else
		{
			m_pToolbarMgr.UpdateButton(Toolbar_Button_Video, Button_Muted);
		}
	}
}

void CCustomizeInMeetingUIMgr::AnnotationSnapshot()
{
	//to do
}

void CCustomizeInMeetingUIMgr::ShowHideGalleryViewWindow()
{
	m_bShowGalleryView = !m_bShowGalleryView;
	m_pToolbarMgr.SetGalleryViewStatus(m_bShowGalleryView);
	m_pCustomizeUIVideoMgr->SetGalleryViewStatus(m_bShowGalleryView);
	DoLayout();
	
	if(m_bShowGalleryView)
	{
		//show the gallery view window here
		if(NULL == m_upArrowWindow && NULL == m_downArrowWindow)
		{
			CreateArrowWindow();
			//m_downArrowWindow->EnableUsingButton(Arrow_button_down);
		}
		DoLayoutArrowWindow();
	}
	else
	{
		if(m_upArrowWindow && m_upArrowWindow->GetHWND() &&::IsWindow(m_upArrowWindow->GetHWND())
			&& m_downArrowWindow && m_downArrowWindow->GetHWND() &&::IsWindow(m_downArrowWindow->GetHWND()))
		{
			m_upArrowWindow->ShowWindow(false);
			m_downArrowWindow->ShowWindow(false);
		}
	}
}

void CCustomizeInMeetingUIMgr::ShowHideChatWindow()
{
	if(NULL == m_pChatUIMgr)
	{
		CreateChatWindow();
		if(NULL == m_pChatUIMgr)
			return;
	}
	m_bInChat = !m_bInChat;
	if(m_bInChat)
	{
		m_pChatUIMgr->ShowWindow(true);
		HWND hwnd = m_pChatUIMgr->GetHWND();
		ActiveWindowToTop(hwnd);
	}
	else
	{
		m_pChatUIMgr->ShowWindow(false);
	}
	m_pToolbarMgr.SetChatUIStatus(m_bInChat);
}

void CCustomizeInMeetingUIMgr::ShowHideCameraControlWindow()
{
	if(NULL == m_pCameraControlWin)
	{
		CreateCameraControlWindow();
		if(NULL == m_pCameraControlWin)
			return;
	}
	m_bInCameraControl = !m_bInCameraControl;
	if(m_bInCameraControl)
	{
		m_pCameraControlWin->ShowWindow(true);
		HWND hwnd = m_pCameraControlWin->GetHWND();
		ActiveWindowToTop(hwnd);
	}
	else
	{
		m_pCameraControlWin->ShowWindow(false);
	}
}

void CCustomizeInMeetingUIMgr::ShowShareWindow()
{
	if(NULL == m_pCustomizeShareMgr)
	{
		return;
	}
	m_pCustomizeShareMgr->ShowSelectShareUI();
	UpdateShareButtonStatus();
}

void CCustomizeInMeetingUIMgr::UpdateShareButtonStatus()
{
	if(m_pCustomizeShareMgr)
	{
		bool bOn = false;
		if(m_pCustomizeShareMgr->IsInSendShareMode())
			bOn =  true;
		m_pToolbarMgr.SetShareUIStatus(bOn);
	}
	UpdateToolbarButtons();
}

void CCustomizeInMeetingUIMgr::ShowHideParticipantWindow()
{
	if(NULL == m_pParticipantUIMgr)
	{
		CreateParticipantWindow();
		if(NULL == m_pParticipantUIMgr)
			return;
	}
	m_bInShowParticipant = !m_bInShowParticipant;
	if(m_bInShowParticipant)
	{
		DoLayoutParticipantsWindow();;
	}
	else
	{
		m_pParticipantUIMgr->ShowWindow(false);
	}
	
	m_pToolbarMgr.SetParticipantUIStatus(m_bInShowParticipant);
}

void CCustomizeInMeetingUIMgr::PageButtonClick(ArrowButtonType btnType)
{
	if(m_pCustomizeUIVideoMgr){
		m_pCustomizeUIVideoMgr->HandleSwitchGalleryPage(btnType);
		DoLayoutArrowWindow();
	}
}

void CCustomizeInMeetingUIMgr::DoLayoutArrowWindow()
{
	
	if(!m_bShowGalleryView)
		return;

	if(NULL == m_pCustomizeUIVideoMgr)
		return;
	
	if(!m_upArrowWindow || !m_upArrowWindow->GetHWND() || !::IsWindow(m_upArrowWindow->GetHWND()) 
		|| !m_downArrowWindow || !m_downArrowWindow->GetHWND() || !::IsWindow(m_downArrowWindow->GetHWND()))
		return;

	
	RECT rcArrow = m_pCustomizeUIVideoMgr->GetCurrentGalleryViewRect();
	rcArrow.top = 0;
	rcArrow.bottom = rcArrow.top + DEFAULT_ARROW_HEIGHT;
	::MoveWindow(m_upArrowWindow->GetHWND(), rcArrow.left, rcArrow.top, rcArrow.right-rcArrow.left,DEFAULT_ARROW_HEIGHT , true);

	rcArrow = m_pCustomizeUIVideoMgr->GetCurrentGalleryViewRect();
	rcArrow.top = rcArrow.bottom - DEFAULT_ARROW_HEIGHT;
	::MoveWindow(m_downArrowWindow->GetHWND(), rcArrow.left, rcArrow.top, rcArrow.right-rcArrow.left,DEFAULT_ARROW_HEIGHT , true);

	int iTotalPage = m_pCustomizeUIVideoMgr->getVideoGalleryPage();
	int iCurrentPage = m_pCustomizeUIVideoMgr->getVideoGalleryCurrPage();
	//following 2 lines uses to test arrow button
	//m_downArrowWindow->EnableUsingButton(Arrow_button_down, true);
	//m_upArrowWindow->EnableUsingButton(Arrow_button_up, true);
	
	if((iTotalPage - iCurrentPage) > 0)
	{
		m_downArrowWindow->EnableUsingButton(Arrow_button_down, true);
		m_downArrowWindow->ShowWindow(true);
	}
	else
	{
		m_downArrowWindow->EnableUsingButton(Arrow_button_down, false);
		m_downArrowWindow->ShowWindow(false);
	}

	if(iCurrentPage > 1)
	{
		m_upArrowWindow->EnableUsingButton(Arrow_button_up, true);
		m_upArrowWindow->ShowWindow(true);
	}
	else
	{
		m_upArrowWindow->EnableUsingButton(Arrow_button_up, false);
		m_upArrowWindow->ShowWindow(false);
	}
	/*
	m_upArrowWindow->ShowWindow(true);
	m_downArrowWindow->ShowWindow(true);
	*/
}

void CCustomizeInMeetingUIMgr::DoLayoutParticipantsWindow()
{
	if(NULL == m_pParticipantUIMgr || !m_bInShowParticipant)
		return;

	HWND hWndParticipant = m_pParticipantUIMgr->GetHWND();
	if(!::IsWindow(hWndParticipant))
		return;
	if(!m_pCustomizeUIVideoMgr)
		return;
	
	m_pParticipantUIMgr->InitListUI();
	RECT rcParticipant = m_pCustomizeUIVideoMgr->GetCurrentAcviteViewRect();
	int nWidth = rcParticipant.right - rcParticipant.left;
	int nHeight = rcParticipant.bottom - rcParticipant.top;
	rcParticipant.top = 0;
	rcParticipant.left = 0;
	rcParticipant.right = min(nWidth, DEFAULT_PARTICIPANT_WIDTH);
	rcParticipant.bottom = min(nHeight, DEFAULT_PARTICIPANT_HEIGHT);
	::MoveWindow(hWndParticipant, rcParticipant.left, rcParticipant.top, rcParticipant.right,rcParticipant.bottom , true);

	m_pParticipantUIMgr->ShowWindow(true);
}

void CCustomizeInMeetingUIMgr::UpdateMeetingTitle(bool bInWaitingRoom)
{
	unsigned __int64 iMeetingID = m_customUIWorkFlow.GetMeetingID();
	TCHAR strTitle[64] = {0};
	if(m_hOwnerHwnd && IsWindow(m_hOwnerHwnd))
	{
		if(bInWaitingRoom)
			wsprintf(strTitle,_T("zoom_sdk_demo_ui -- You are in waiting room now"));
		else if(0 != iMeetingID)
			wsprintf(strTitle,_T("zoom_sdk_demo_ui -- meeting ID %u"), iMeetingID);
		else
			wsprintf(strTitle,_T("zoom_sdk_demo_ui"));
		bool BRet = ::SetWindowText(m_hOwnerHwnd, strTitle);
	}
}

void CCustomizeInMeetingUIMgr::ShowHideMoreMenuWindow(int x, int y)
{
	if (m_more_menu_ui == NULL)
	{
		int posx = x;
		int posy = y;

		m_more_menu_ui = new CMoreMenuUIMgr(x, y, this);
		m_more_menu_ui->Create(m_hOwnerHwnd, _T("Windows app using zoom win sdk"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE|WS_EX_TOOLWINDOW);
		m_more_menu_ui->SetIcon(IDI_ICON_LOGO);
	}
	else
	{
		if (HideMenuWhenMenuVisible())
		{
			
		}
		else
		{
			m_more_menu_ui->RepaintClient(x, y);
		}
		
	}

}

void CCustomizeInMeetingUIMgr::DestroyMoreMenuWindow()
{
	if (m_more_menu_ui)
	{
		DestroyWindow(m_more_menu_ui->GetHWND());
		delete m_more_menu_ui;
		m_more_menu_ui = NULL;
	}
}

void CCustomizeInMeetingUIMgr::onMove()
{
	HideMenuWhenMenuVisible();
	if (m_display_cc_ui)
	{
		m_display_cc_ui->HandleSizeChanged(m_hOwnerHwnd);
	}
	if (m_more_menu_ui)
	{
		m_more_menu_ui->HandleMoveAndResize();
	}
}

bool CCustomizeInMeetingUIMgr::HideMenuWhenMenuVisible()
{
	if (m_more_menu_ui)
	{
		if (IsWindowVisible(m_more_menu_ui->GetHWND()))
		{
			m_more_menu_ui->ShowWindow(false);
			return true;
		}
	}
	return false;
}

HWND CCustomizeInMeetingUIMgr::GetHWND()
{
	return m_hOwnerHwnd;
}

ClosedCaptionDisplayUI* CCustomizeInMeetingUIMgr::CreateDisplayCCWnd()
{

	RECT rc = {0};
	GetWindowRect(m_hOwnerHwnd, &rc);
	int posx = (rc.left+rc.right-400)/2;
	int posy = rc.bottom-140;
	if ( NULL == m_display_cc_ui)
	{
		m_display_cc_ui = new ClosedCaptionDisplayUI(posx, posy);
	}
	#define WND_STYLE (WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
	if (m_display_cc_ui)
	{
		m_display_cc_ui->Create(m_hOwnerHwnd, _T("ClosedCaption Display"), WND_STYLE, WS_EX_WINDOWEDGE|WS_EX_LAYERED);
		//m_display_cc_ui->ShowWindow(true);
	}
	return m_display_cc_ui;
	
}

void CCustomizeInMeetingUIMgr::DestroyDisplayCCWnd()
{
	if (m_display_cc_ui)
	{
		if (IsWindow(m_display_cc_ui->GetHWND()))
		{
			DestroyWindow(m_display_cc_ui->GetHWND());
		}
	}
	m_display_cc_ui = NULL;
}

HWND CCustomizeInMeetingUIMgr::GetRootWindowHwnd()
{
	return m_hOwnerHwnd;
}

void CCustomizeInMeetingUIMgr::UpdateParticipantsWindow()
{
	//DoLayoutParticipantsWindow();
	if (m_pParticipantUIMgr)
	{
		m_pParticipantUIMgr->InitListUI();
	}
}

void CCustomizeInMeetingUIMgr::onUserNameChanged( unsigned int userId, const wchar_t* userName )
{
	UpdateParticipantsWindow();
}