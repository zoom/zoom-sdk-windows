#include "EventMgr.h"

//ZOOM_SDK_NAMESPACE::IAuthService* pAuthService;
ZOOM_SDK_NAMESPACE::IPreMeetingService* g_preMeeting;
ZOOM_SDK_NAMESPACE::IMeetingService* g_pMeetService;
ZOOM_SDK_NAMESPACE::ISettingService* g_pSettingService;

std::wstring g_defCamera;
std::wstring g_lstCamera;
HWND	 g_hAppWnd = NULL;
HWND     g_demoWnd = NULL;
CMeetingPhoneHelperEvent phoneEvent;
CAuthServiceEvent authEvent;
CPreMeetingServiceEvent premeetingEvent;
CMeetingServiceEvent g_meetingEvent;
//CAuthServiceEvent authEvent;

/************************************************************************/
/*               CDemoUISkink			                                */
/************************************************************************/
CDemoUISink::CDemoUISink()
{

}

CDemoUISink::~CDemoUISink()
{

}

void CDemoUISink::SetSink(CDemoUI* pSink)
{
	m_pSink = pSink;
}

/************************************************************************/
/*               CMeetingPhoneHelperEvent                               */
/************************************************************************/
void CMeetingPhoneHelperEvent::onInviteCallOutUserStatus(ZOOM_SDK_NAMESPACE::PhoneStatus status, ZOOM_SDK_NAMESPACE::PhoneFailedReason reason)
{
	char szTmp[100] = { 0 };
	sprintf(szTmp, "onInviteCallOutUserStatus status-%d-reason-%d\r\n", status, reason);
	OutputDebugStringA(szTmp);
}

void CMeetingPhoneHelperEvent::onCallMeStatus(ZOOM_SDK_NAMESPACE::PhoneStatus status, ZOOM_SDK_NAMESPACE::PhoneFailedReason reason)
{
	char szTmp[100] = { 0 };
	sprintf(szTmp, "onCallMeStatus status-%d-reason-%d\r\n", status, reason);
	OutputDebugStringA(szTmp);
}

/************************************************************************/
/*               CAuthServiceEvent		                                */
/************************************************************************/
void CAuthServiceEvent::onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
	//char szLog[MAX_PATH] = { 0 };
	//sprintf(szLog, "onAuthenticationReturn:%d\r\n", ret);
	//OutputDebugStringA(szLog);
	//MessageBoxA(NULL, szLog, "Authentication", MB_OK);

	if (ZOOM_SDK_NAMESPACE::AUTHRET_SUCCESS == ret)
		m_pSink->SwitchUIPage(UIPAGE_USER);
}


void CAuthServiceEvent::onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS status, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo)
{
	char szLog[MAX_PATH] = { 0 };
	sprintf(szLog, "onLoginRet:%d\r\n", status);
	OutputDebugStringA(szLog);
	MessageBoxA(NULL, szLog, "onLoginRet", MB_OK);
	if (ZOOM_SDK_NAMESPACE::LOGIN_SUCCESS == status)
	{
		ZOOM_SDK_NAMESPACE::CreatePreMeetingService(&g_preMeeting);
		if (g_preMeeting)
		{
			g_preMeeting->SetEvent(&premeetingEvent);
			g_preMeeting->ListMeeting();
		}
	}

}

void CAuthServiceEvent::onLogout()
{

}

/************************************************************************/
/*               CPreMeetingServiceEvent                                */
/************************************************************************/
void CPreMeetingServiceEvent::onListMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, ZOOM_SDK_NAMESPACE::IList<UINT64 >* lstMeetingList)
{
	if (ZOOM_SDK_NAMESPACE::PREMETAPIRET_SUCCESS == result)
	{
		static bool doOnce(true);
		if (doOnce && g_preMeeting)
		{
			doOnce = false;
			if (lstMeetingList)
			{
				int count = lstMeetingList->GetCount();
				for (int i = 0; i < count; i ++)
				{
					UINT64 meetingid = lstMeetingList->GetItem(i);
					ZOOM_SDK_NAMESPACE::IMyMeetingItem* item = g_preMeeting->GetMeeingItem(meetingid);

					if (item && item->IsPersonalMeeting())
					{
						ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* editItem = g_preMeeting->CreateScheduleMeetingItem();
						if (editItem)
						{
							editItem->SetMeetingPassword(L"test");
							g_preMeeting->EditMeeting(meetingid, editItem);
							g_preMeeting->DestoryScheduleMeetingItem(editItem);
						}
					}

					/*
					if (item && 
						!item->IsPersonalMeeting()
						&& !item->IsWebinarMeeting()
						&& !item->IsRecurringMeeting())
					{

						const wchar_t* psw = item->GetMeetingPassword();
						
					}
					*/
				}
			}
		}
	}
}

void CPreMeetingServiceEvent::onScheduleOrEditMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, UINT64 meetingUniqueID)
{

}

void CPreMeetingServiceEvent::onDeleteMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result)
{

}

/************************************************************************/
/*               CPreMeetingServiceEvent                                */
/************************************************************************/
void CMeetingServiceEvent::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult)
{
	char szLog[MAX_PATH] = { 0 };
	sprintf(szLog, "meeting status:%d, details result:%d\r\n", status, iResult);
	OutputDebugStringA(szLog);

	if (ZOOM_SDK_NAMESPACE::MEETING_STATUS_INMEETING != status) 
	{
		g_lstCamera = L"";
		InvalidateRect(g_demoWnd, NULL, TRUE);
	}
	else if (g_pMeetService->GetMeetingPhoneHelper())
	{
		g_pMeetService->GetMeetingPhoneHelper()->SetEvent(&phoneEvent);
	}
}

void CMeetingServiceEvent::onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath)
{
	char szLog[MAX_PATH] = { 0 };
	sprintf(szLog, "recording to mp4:%d, details result:%d%s\r\n", bsuccess, iResult);
	OutputDebugStringA(szLog);
	OutputDebugStringW(szPath);
}

void CMeetingServiceEvent::onRecording2MP4Processing(int iPercentage)
{
	char szLog[MAX_PATH] = { 0 };
	sprintf(szLog, "recording to mp4 processing:%d%%\r\n", iPercentage);
	OutputDebugStringA(szLog);
}

void CMeetingServiceEvent::onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList)
{
	if (lstUserID && g_pMeetService)
	{
		int count = lstUserID->GetCount();
		for (int i = 0; i < count; i++)
		{
			int userId = lstUserID->GetItem(i);
			ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = g_pMeetService->GetUserByUserID(userId);
			if (pUserInfo)
			{
				OutputDebugStringA("new user join:\r\n");
				OutputDebugStringW(pUserInfo->GetUserName());
				OutputDebugStringA("\r\n");
				char szUserID[MAX_PATH] = { 0 };
				sprintf(szUserID, "%d-ishost:%d-videoon:%d\r\n", pUserInfo->GetUserID(), pUserInfo->IsHost(), pUserInfo->IsVideoOn());
				OutputDebugStringA(szUserID);
			}
		}
	}
}

void CMeetingServiceEvent::onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList)
{
	if (lstUserID && g_pMeetService)
	{
		int count = lstUserID->GetCount();
		for (int i = 0; i < count; i++)
		{
			int userId = lstUserID->GetItem(i);
			{
				char szTmp[MAX_PATH] = { 0 };
				sprintf(szTmp, "user(id:%d) left the meeting\r\n", userId);
				OutputDebugStringA(szTmp);
			}
		}
	}
}

void CMeetingServiceEvent::onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId)
{
	char szLog[MAX_PATH] = { 0 };
	sprintf(szLog, "onRemoteControlStatus:status=%d, userid=%d\r\n", status, userId);
	OutputDebugStringA(szLog);

	// 		if (ZOOM_SDK_NAMESPACE::Remote_Control_Request == status)
	// 		{
	// 			if (g_pMeetService)
	// 			{
	// 				ZOOM_SDK_NAMESPACE::IMeetingRemoteController* pCtrl = g_pMeetService->GetMeetingRemoteController();
	// 				if (pCtrl)
	// 				{
	// 					pCtrl->GiveRemoteControlTo(userId);
	// 				}
	// 
	// 			}
	// 		}
}

void CMeetingServiceEvent::onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId)
{
	char szLog[MAX_PATH] = { 0 };
	sprintf(szLog, "onSharingStatus:status=%d, userid=%d\r\n", status, userId);
	OutputDebugStringA(szLog);
}

void CMeetingServiceEvent::onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList)
{
	int count = lstAudioStatusChange->GetCount();
	for (int i = 0; i < count; i ++)
	{
		ZOOM_SDK_NAMESPACE::IUserAudioStatus* audioStatus = lstAudioStatusChange->GetItem(i);
		char sz[MAX_PATH] = { 0 };
		sprintf(sz, "userid:%d, status:%d\r\n", audioStatus->GetUserId(), audioStatus->GetStatus());
		OutputDebugStringA(sz);
	}
}

void CMeetingServiceEvent::onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status)
{

}

void CMeetingServiceEvent::onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc)
{
	if (NULL == chatMsg)
		return;

	wchar_t szTmp[1024] = { 0 };
	wsprintf(szTmp, _T("%d:%s-->%d:%s::::%s\r\n"), chatMsg->GetSenderUserId(), chatMsg->GetSenderDisplayName(),
		chatMsg->GetReceiverUserId(), chatMsg->GetReceiverDisplayName(), chatMsg->GetContent());
	OutputDebugStringW(szTmp);
}