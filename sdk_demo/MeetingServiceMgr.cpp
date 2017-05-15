#include "MeetingServiceMgr.h"


CMeetingServiceMgr::CMeetingServiceMgr()
{
	m_pSink = NULL;
	m_strCamera = _T("");
	m_bInited = false;
}

CMeetingServiceMgr::CMeetingServiceMgr(CDemoUI* pSink)
{
	m_pSink = pSink;
	m_strCamera = _T("");
	m_bInited = false;
}

CMeetingServiceMgr::~CMeetingServiceMgr()
{
	m_bInited = false;
}

bool CMeetingServiceMgr::IsInMeeting(ZOOM_SDK_NAMESPACE::MeetingStatus status)
{
	bool bInMeeting(true);
	if (status == ZOOM_SDK_NAMESPACE::MEETING_STATUS_IDLE ||
		status == ZOOM_SDK_NAMESPACE::MEETING_STATUS_ENDED)
	{
		bInMeeting = false;
	}

	return bInMeeting;
}

bool CMeetingServiceMgr::Init()
{
	if (m_bInited)
		return true;

	if (ZOOM_SDK_NAMESPACE::CreateMeetingService(&m_pMeetingService) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	if (m_pMeetingService == NULL)
		return false;

	if (m_pMeetingService->SetEvent(this) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	if (ZOOM_SDK_NAMESPACE::CreateSettingService(&m_pSettingService) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	if (m_pSettingService == NULL)
		return false;

	m_bInited = true;

	return true;
}

bool CMeetingServiceMgr::UnInit()
{
	if (!m_bInited)
		return true;

	m_bInited = false;

	if (ZOOM_SDK_NAMESPACE::DestroyMeetingService(m_pMeetingService) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	if (ZOOM_SDK_NAMESPACE::DestroySettingService(m_pSettingService) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

bool CMeetingServiceMgr::Start(ZOOM_SDK_NAMESPACE::StartParam& startParam)
{
	if (m_pMeetingService == NULL)
		return false;

	if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
	{	
		if (m_pMeetingService->Start(startParam) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
			return false;
	}

	return true;
}

bool CMeetingServiceMgr::Join(ZOOM_SDK_NAMESPACE::JoinParam& joinParam)
{
	if (m_pMeetingService == NULL)
		return false;

	if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
	{	
		if (m_pMeetingService->Join(joinParam) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
			return false;
	}

	return true;
}

bool CMeetingServiceMgr::Leave()
{
	if (m_pMeetingService == NULL)
		return false;

	if (IsInMeeting(m_pMeetingService->GetMeetingStatus()))
	{
		if (m_pMeetingService->Leave(ZOOM_SDK_NAMESPACE::LEAVE_MEETING) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
			return false;
	}

	return true;
}

bool CMeetingServiceMgr::End()
{
	if (m_pMeetingService == NULL)
		return false;

	if (IsInMeeting(m_pMeetingService->GetMeetingStatus()))
	{
		if (m_pMeetingService->Leave(ZOOM_SDK_NAMESPACE::END_MEETING) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
			return false;
	}

	return true;
}

bool CMeetingServiceMgr::StartMonitorShare(const wchar_t* monitorID)
{
	if (m_pMeetingService == NULL)
		return false;

	if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		return false;

	ZOOM_SDK_NAMESPACE::IMeetingShareController* pCtrl = m_pMeetingService->GetMeetingShareController();
	if (pCtrl == NULL)
		return false;

	if (pCtrl->StartMonitorShare(monitorID) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

bool CMeetingServiceMgr::StartAppShare(HWND hwndSharedApp)
{
	if (m_pMeetingService == NULL)
		return false;

	if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		return false;

	ZOOM_SDK_NAMESPACE::IMeetingShareController* pCtrl = m_pMeetingService->GetMeetingShareController();
	if (pCtrl == NULL)
		return false;

	if (pCtrl->StartAppShare(hwndSharedApp) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

bool CMeetingServiceMgr::StopShare()
{
	if (m_pMeetingService == NULL)
		return false;

	if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		return false;

	ZOOM_SDK_NAMESPACE::IMeetingShareController* pCtrl = m_pMeetingService->GetMeetingShareController();
	if (pCtrl == NULL)
		return false;

	if (pCtrl->StopShare() != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

bool CMeetingServiceMgr::MuteVideo()
{
	if (m_pMeetingService == NULL)
		return false;

	if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		return false;

	ZOOM_SDK_NAMESPACE::IMeetingVideoController* pCtrl = m_pMeetingService->GetMeetingVideoController();
	if (pCtrl == NULL)
		return false;

	if (pCtrl->MuteVideo() != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

bool CMeetingServiceMgr::UnmuteVideo()
{
	if (m_pMeetingService == NULL)
		return false;

	if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		return false;

	ZOOM_SDK_NAMESPACE::IMeetingVideoController* pCtrl = m_pMeetingService->GetMeetingVideoController();
	if (pCtrl == NULL)
		return false;

	if (pCtrl->UnmuteVideo() != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

bool CMeetingServiceMgr::PinVideo(bool bPin, bool bFirstView, unsigned int userid)
{
	if (m_pMeetingService == NULL)
		return false;

	if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		return false;

	ZOOM_SDK_NAMESPACE::IMeetingVideoController* pCtrl = m_pMeetingService->GetMeetingVideoController();
	if (pCtrl == NULL)
		return false;

	if (pCtrl->PinVideo(bPin, bFirstView, userid) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

bool CMeetingServiceMgr::MuteAudio(unsigned int userid)
{
	if (m_pMeetingService == NULL)
		return false;

	if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		return false;

	ZOOM_SDK_NAMESPACE::IMeetingAudioController* pCtrl = m_pMeetingService->GetMeetingAudioController();
	if (pCtrl == NULL)
		return false;

	if (pCtrl->MuteAudio(userid) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

bool CMeetingServiceMgr::UnMuteAudio(unsigned int userid)
{
	if (m_pMeetingService == NULL)
		return false;

	if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		return false;

	ZOOM_SDK_NAMESPACE::IMeetingAudioController* pCtrl = m_pMeetingService->GetMeetingAudioController();
	if (pCtrl == NULL)
		return false;

	if (pCtrl->UnMuteAudio(userid) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

void CMeetingServiceMgr::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult)
{
	TCHAR szLog[MAX_PATH] = { 0 };
	wsprintf(szLog, _T("meeting status:%d, details result:%d\r\n"), status, iResult);
	OutputDebugString(szLog);

	if (m_pSink == NULL)
		return;

	if (status == ZOOM_SDK_NAMESPACE::MEETING_STATUS_ENDED || status == ZOOM_SDK_NAMESPACE::MEETING_STATUS_FAILED)
	{
		m_pSink->CleanUpUserList();
		m_pSink->SwitchUIPageByType(UIPAGE_PT);
	}
}

void CMeetingServiceMgr::onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath)
{
}

void CMeetingServiceMgr::onRecording2MP4Processing(int iPercentage)
{
}

void CMeetingServiceMgr::onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList)
{
	if (m_pSink == NULL)
		return;

	if (lstUserID && m_pMeetingService)
	{
		int count = lstUserID->GetCount();
		for (int i = 0; i < count; i++)
		{
			int userId = lstUserID->GetItem(i);
			ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = m_pMeetingService->GetUserByUserID(userId);
			if (pUserInfo)
			{
				TCHAR szUserID[MAX_PATH] = {0};
				wsprintf(szUserID, _T("%d"), pUserInfo->GetUserID());
				m_pSink->UpdateUserList(i, pUserInfo->GetUserName(), szUserID, true);

				TCHAR szLog[MAX_PATH] = { 0 };
				wsprintf(szUserID, _T("onUserJoin:User (%s) join meeting, userid(%d), Is host(%d), Video is on(%d)\r\n"), pUserInfo->GetUserName(), pUserInfo->GetUserID(), pUserInfo->IsHost(), pUserInfo->IsVideoOn());
				OutputDebugString(szLog);
			}
		}

		m_pSink->SwitchUIPageByType(UIPAGE_MEETING);
	}
	else
		m_pSink->ShowStatus(UIPAGE_START, ERROR_START);
		
}

void CMeetingServiceMgr::onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList)
{
	if (lstUserID && m_pMeetingService)
	{
		int count = lstUserID->GetCount();
		for (int i = 0; i < count; i++)
		{
			TCHAR szUserID[MAX_PATH] = {0};
			wsprintf(szUserID, _T("%d"), lstUserID->GetItem(i));
			m_pSink->UpdateUserList(i, _T(""), szUserID, false);

			TCHAR szLog[MAX_PATH] = {0};
			wsprintf(szLog, _T("onUserLeft:userid (%d) left the meeting\r\n"), lstUserID->GetItem(i));
			OutputDebugString(szLog);
		}
	}
}

void CMeetingServiceMgr::onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId)
{
}

void CMeetingServiceMgr::onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId)
{
	TCHAR szLog[MAX_PATH] = { 0 };
	wsprintf(szLog, _T("onSharingStatus:status=%d, userid=%d\r\n"), status, userId);
	OutputDebugString(szLog);

	if (m_pSink == NULL)
		return;

	std::wstring strStatus = _T("Share failed!");
	
	if (status == ZOOM_SDK_NAMESPACE::Sharing_Self_Send_Begin)
		strStatus = _T("Sharing_Self_Send_Begin");
	else if (status == ZOOM_SDK_NAMESPACE::Sharing_Self_Send_End)
		strStatus = _T("Sharing_Self_Send_End");
	else if (status == ZOOM_SDK_NAMESPACE::Sharing_Other_Share_Begin)
		strStatus = _T("Sharing_Other_Share_Begin");
	else if (status == ZOOM_SDK_NAMESPACE::Sharing_Other_Share_End)
		strStatus = _T("Sharing_Other_Share_End");
	else if (status == ZOOM_SDK_NAMESPACE::Sharing_View_Other_Sharing)
		strStatus = _T("Sharing_View_Other_Sharing");
	else if (status == ZOOM_SDK_NAMESPACE::Sharing_Pause)
		strStatus = _T("Sharing_Pause");
	else if (status == ZOOM_SDK_NAMESPACE::Sharing_Resume)
		strStatus = _T("Sharing_Resume");

	m_pSink->ShowStatus(UIPAGE_MEETING, strStatus);
}

void CMeetingServiceMgr::onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList)
{
	std::wstring strStatus = _T("Audio failed!");
	int count = lstAudioStatusChange->GetCount();
	for (int i = 0; i < count; i ++)
	{
		ZOOM_SDK_NAMESPACE::IUserAudioStatus* audioStatus = lstAudioStatusChange->GetItem(i);
		
		if (audioStatus->GetStatus() == ZOOM_SDK_NAMESPACE::Audio_None)
			strStatus = _T("Audio_None");
		else if (audioStatus->GetStatus() == ZOOM_SDK_NAMESPACE::Audio_Muted)
			strStatus = _T("Audio_Muted");
		else if (audioStatus->GetStatus() == ZOOM_SDK_NAMESPACE::Audio_UnMuted)
			strStatus = _T("Audio_UnMuted");
		else if (audioStatus->GetStatus() == ZOOM_SDK_NAMESPACE::Audio_Muted_ByHost)
			strStatus = _T("Audio_Muted_ByHost");
		else if (audioStatus->GetStatus() == ZOOM_SDK_NAMESPACE::Audio_UnMuted_ByHost)
			strStatus = _T("Audio_UnMuted_ByHost");
		else if (audioStatus->GetStatus() == ZOOM_SDK_NAMESPACE::Audio_MutedAll_ByHost)
			strStatus = _T("Audio_MutedAll_ByHost");
		else if (audioStatus->GetStatus() == ZOOM_SDK_NAMESPACE::Audio_UnMutedAll_ByHost)
			strStatus = _T("Audio_UnMutedAll_ByHost");

		m_pSink->ShowStatus(UIPAGE_MEETING, strStatus);
	}	
}
void CMeetingServiceMgr::onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status)
{

}

void CMeetingServiceMgr::onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status)
{

}

void CMeetingServiceMgr::onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc)
{
	if (NULL == chatMsg)
		return;

	TCHAR szLog[MAX_PATH] = { 0 };
	wsprintf(szLog, _T("%d:%s-->%d:%s:%s\r\n"), chatMsg->GetSenderUserId(), chatMsg->GetSenderDisplayName(),
		chatMsg->GetReceiverUserId(), chatMsg->GetReceiverDisplayName(), chatMsg->GetContent());
	OutputDebugString(szLog);
}
