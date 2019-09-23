#include "MeetingServiceMgr.h"


CMeetingServiceMgr::CMeetingServiceMgr()
{
	m_pSink = NULL;
	m_strCamera = _T("");
	m_bInited = false;
}

CMeetingServiceMgr::CMeetingServiceMgr(IMeetingserviceMgrEvent* pSink)
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
	if (m_pSink)
	{
		m_pSink->onMeetingStatusChanged(status, iResult);
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
	if (m_pSink)
	{
		m_pSink->onUserJoin(lstUserID, strUserList);
	}
}

void CMeetingServiceMgr::onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList)
{
	if (m_pSink)
	{
		m_pSink->onUserJoin(lstUserID, strUserList);
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
}

void CMeetingServiceMgr::onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList)
{	
}
void CMeetingServiceMgr::onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status)
{

}

void CMeetingServiceMgr::onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status)
{

}

void CMeetingServiceMgr::onLockShareStatus(bool bLocked)
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

ZOOM_SDK_NAMESPACE::IUserInfo* CMeetingServiceMgr::GetUserByUserID(unsigned int userid)
{
	if (m_pMeetingService)
	{
		return m_pMeetingService->GetUserByUserID(userid);
	}

	return NULL;
}
