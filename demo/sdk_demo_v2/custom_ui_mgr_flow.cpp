#include "stdafx.h"
#include "custom_ui_mgr_flow.h"
CSDKCustomUIWorkFlow::CSDKCustomUIWorkFlow()
{
	m_pAudioCtrl = NULL;
	m_pChatCtrl = NULL;
	m_pUserCtrl = NULL;
	m_pRecCtrl = NULL;
	m_pRemoteCtrl = NULL;
	m_pShareCtrl = NULL;
	m_pVideoCtrl = NULL;
	m_pMeetingUICtrl = NULL;
	m_pMeetingService = NULL;
	m_pCustomAnnoCtrl = NULL;
}

CSDKCustomUIWorkFlow::~CSDKCustomUIWorkFlow()
{
	Uninit();
}

void CSDKCustomUIWorkFlow::Uninit()
{
	if(m_pMeetingService && IsInMeeting(m_pMeetingService->GetMeetingStatus()))
	{
		//m_pMeetingService->Leave(ZOOM_SDK_NAMESPACE::END_MEETING);
		SDKInterfaceWrap::GetInst().UnListenInMeetingServiceMgrEvent(this);
		if(m_pAudioCtrl)
			m_pAudioCtrl->SetEvent(NULL);
		if(m_pVideoCtrl)
			m_pVideoCtrl->SetEvent(NULL);
		if(m_pShareCtrl)
			m_pShareCtrl->SetEvent(NULL);
	}
	m_pMeetingService = NULL;
}

void CSDKCustomUIWorkFlow::Init(ISDKInMeetingServiceCustomUIEvent* pEvent_)
{
	m_pCustomUIEvent = pEvent_;
	if(IsMeetingServiceReady())
		InitMeetingService();
}

void CSDKCustomUIWorkFlow::InitMeetingService()
{
	GetServiceControls();
	SDKInterfaceWrap::GetInst().ListenInMeetingServiceMgrEvent(this);
	if(m_pAudioCtrl)
		m_pAudioCtrl->SetEvent(this);
	if(m_pVideoCtrl)
		m_pVideoCtrl->SetEvent(this);
	if(m_pShareCtrl)
		m_pShareCtrl->SetEvent(this);
	if(m_pRemoteCtrl)
		m_pRemoteCtrl->SetEvent(this);
	if (m_pCustomAnnoCtrl)
		m_pCustomAnnoCtrl->SetEvent(this);

	if(m_pCustomUIEvent)
		m_pCustomUIEvent->SetSDKMeetingService(m_pMeetingService);
}

bool CSDKCustomUIWorkFlow::IsMeetingServiceReady()
{
	if(NULL == m_pMeetingService)
	{
		m_pMeetingService = SDKInterfaceWrap::GetInst().GetMeetingService();
		if( NULL == m_pMeetingService)
			return false;
	}
	return true;
}

void CSDKCustomUIWorkFlow::GetServiceControls()
{
	if(m_pMeetingService)
	{
		m_pAudioCtrl = m_pMeetingService->GetMeetingAudioController();
		m_pChatCtrl = m_pMeetingService->GetMeetingChatController();
		m_pUserCtrl = m_pMeetingService->GetMeetingParticipantsController();
		m_pRecCtrl = m_pMeetingService->GetMeetingRecordingController();
		m_pRemoteCtrl = m_pMeetingService->GetMeetingRemoteController();
		m_pShareCtrl = m_pMeetingService->GetMeetingShareController();
		m_pVideoCtrl = m_pMeetingService->GetMeetingVideoController();
		m_pMeetingUICtrl = m_pMeetingService->GetUIController();
		m_pSettingService = SDKInterfaceWrap::GetInst().GetSettingService();
		m_pCustomAnnoCtrl = m_pMeetingService->GetAnnotationController()->GetCustomizedAnnotationController();
	}
}

ZOOM_SDK_NAMESPACE::IUserInfo* CSDKCustomUIWorkFlow::GetUserByUserID(unsigned int userid)
{
	if (m_pUserCtrl)
	{
		return m_pUserCtrl->GetUserByUserID(userid);
	}

	return NULL;
}

bool CSDKCustomUIWorkFlow::IsAudioOn()
{
	bool ret(false);
	do 
	{
		if(!m_pUserCtrl)
			break;
		
		ZOOM_SDK_NAMESPACE::IUserInfo* pMe = m_pUserCtrl->GetUserByUserID(0);
		if(!pMe)
			break;

		ret = !pMe->IsAudioMuted();
	} while (0);

	return ret;
}

bool CSDKCustomUIWorkFlow::IsVideoOn()
{
	bool ret(false);
	do 
	{
		if(!m_pUserCtrl)
			break;

		ZOOM_SDK_NAMESPACE::IUserInfo* pMe = m_pUserCtrl->GetUserByUserID(0);
		if(!pMe)
			break;

		ret = pMe->IsVideoOn();
	} while (0);

	return ret;
}

unsigned __int64 CSDKCustomUIWorkFlow::GetMeetingID()
{
	if(m_pMeetingService)
	{
		ZOOM_SDK_NAMESPACE::IMeetingInfo* pInfo = m_pMeetingService->GetMeetingInfo();
		if(pInfo)
		{
			return pInfo->GetMeetingNumber();
		}
	}
	return 0;
}
void CSDKCustomUIWorkFlow::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult /*= 0*/)
{
	if(m_pCustomUIEvent)
		m_pCustomUIEvent->onMeetingStatusChanged(status, iResult);
}

void CSDKCustomUIWorkFlow::onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId)
{
	if(m_pCustomUIEvent)
		m_pCustomUIEvent->onRemoteControlStatus(status, userId);
}

void CSDKCustomUIWorkFlow::onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList)
{
	if(m_pCustomUIEvent)
		m_pCustomUIEvent->onUserJoin(lstUserID, strUserList);
}

void CSDKCustomUIWorkFlow::onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList)
{
	if(m_pCustomUIEvent)
		m_pCustomUIEvent->onUserLeft(lstUserID, strUserList);
}

void CSDKCustomUIWorkFlow::onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId)
{
	if(m_pCustomUIEvent)
		m_pCustomUIEvent->onSharingStatus(status, userId);
}

void CSDKCustomUIWorkFlow::onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper)
{
	if(m_pCustomUIEvent)
		m_pCustomUIEvent->onCustomizedLocalRecordingSourceNotification(layout_helper);
}

void CSDKCustomUIWorkFlow::onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList)
{
	if(m_pCustomUIEvent)
		m_pCustomUIEvent->onUserAudioStatusChange(lstAudioStatusChange, strAudioStatusList);
}

void CSDKCustomUIWorkFlow::onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status)
{
	if(m_pCustomUIEvent)
		m_pCustomUIEvent->onUserVideoStatusChange(userId, status);
}

void CSDKCustomUIWorkFlow::onCustomizedAnnotationObjDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* obj_)
{
	if (m_pCustomUIEvent){
		m_pCustomUIEvent->onCustomizedAnnotationObjDestroyed(obj_);
	}
}

void CSDKCustomUIWorkFlow::onSharingShareAnnotationStatusChanged(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_)
{
	if (m_pCustomUIEvent){
		m_pCustomUIEvent->onSharingShareAnnotationStatusChanged(share_render_, status_);
	}
}

void CSDKCustomUIWorkFlow::onUserNameChanged( unsigned int userId, const wchar_t* userName )
{
	if (m_pCustomUIEvent)
	{
		m_pCustomUIEvent->onUserNameChanged(userId, userName);
	}
}