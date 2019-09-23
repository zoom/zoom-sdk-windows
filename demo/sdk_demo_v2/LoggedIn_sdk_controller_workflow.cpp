#include "stdafx.h"
#include "LoggedIn_sdk_controller_workflow.h"

CSDKLoggedInUIWorkFlow::CSDKLoggedInUIWorkFlow()
{
	m_pLoggedInFlowUIEvent = NULL;
	m_pMeetingService = NULL;
	m_pSettingService = NULL;
	m_pDirectShareService = NULL;
}

CSDKLoggedInUIWorkFlow::~CSDKLoggedInUIWorkFlow()
{
	m_pMeetingService = NULL;
	m_pSettingService = NULL;
	m_pDirectShareService = NULL;
	SDKInterfaceWrap::GetInst().UnListenMeetingServiceEvent(this);
}

void CSDKLoggedInUIWorkFlow::SetUIEvent(CSDKLoggedInFlowUIEvent* event_)
{
	m_pLoggedInFlowUIEvent = event_;
}

bool CSDKLoggedInUIWorkFlow::IsMeetingServiceReady()
{
	if(NULL == m_pMeetingService)
	{
		m_pMeetingService = SDKInterfaceWrap::GetInst().GetMeetingService();
		if( NULL == m_pMeetingService)
			return false;
		SDKInterfaceWrap::GetInst().ListenMeetingServiceEvent(this);
	}
	return true;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKLoggedInUIWorkFlow::StartMeeting(ZOOM_SDK_NAMESPACE::StartParam& paramStartMeeting)
{
	if(IsMeetingServiceReady())
	{
		/*some configurations about the meeting should be called here*/
		if (m_pMeetingService->GetMeetingConfiguration())
		{
			m_pMeetingService->GetMeetingConfiguration()->SetSharingToolbarVisibility(true);
		}
		return m_pMeetingService->Start(paramStartMeeting);
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKLoggedInUIWorkFlow::EndMeeting()
{
	if(IsMeetingServiceReady())
	{
		if(IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		{
			return m_pMeetingService->Leave(ZOOM_SDK_NAMESPACE::END_MEETING);
		}
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKLoggedInUIWorkFlow::LeaveMeeting()
{
	if(IsMeetingServiceReady())
	{
		if(IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		{
			return m_pMeetingService->Leave(ZOOM_SDK_NAMESPACE::LEAVE_MEETING);
		}
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKLoggedInUIWorkFlow::BringMeetingToFront()
{
	ZOOM_SDK_NAMESPACE::SDKError err(ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE);
	if(IsMeetingServiceReady())
	{
		ZOOM_SDK_NAMESPACE::IMeetingUIController* pUICtrl = m_pMeetingService->GetUIController();
		if(pUICtrl)
			err = pUICtrl->BackToMeeting();
	}
	return err;
}

////more codes come later to handle the logic
void CSDKLoggedInUIWorkFlow::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult)
{
	//to do
	if(NULL != m_pLoggedInFlowUIEvent)
		m_pLoggedInFlowUIEvent->onMeetingStatusChanged(status, iResult);
}

void CSDKLoggedInUIWorkFlow::onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type)
{
	//to do
	if(NULL != m_pLoggedInFlowUIEvent)
		m_pLoggedInFlowUIEvent->onMeetingStatisticsWarningNotification(type);
}

void CSDKLoggedInUIWorkFlow::onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler)
{
	//to do
	if(NULL != m_pLoggedInFlowUIEvent)
		m_pLoggedInFlowUIEvent->onMeetingSecureKeyNotification(key, len, pHandler);
}

void CSDKLoggedInUIWorkFlow::onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param)
{
	//to do
	if(NULL != m_pLoggedInFlowUIEvent)
		m_pLoggedInFlowUIEvent->onMeetingParameterNotification(meeting_param);
}

ZOOM_SDK_NAMESPACE::SDKError CSDKLoggedInUIWorkFlow::DirectShare()
{
	if (NULL == m_pDirectShareService)
	{
		m_pDirectShareService = SDKInterfaceWrap::GetInst().GetAuthService()->GetDirectShareServiceHeler();
	}
	bool bCanDirectShare(false);
	if (m_pDirectShareService)
	{
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == m_pDirectShareService->CanStartDirectShare())
			bCanDirectShare = true;
	}
	ZOOM_SDK_NAMESPACE::SDKError err;
	if (bCanDirectShare)
	{
		m_pDirectShareService->SetEvent(this);
		err = m_pDirectShareService->StartDirectShare();
	}
	return err;
}

void CSDKLoggedInUIWorkFlow::OnDirectShareStatusUpdate( ZOOM_SDK_NAMESPACE::DirectShareStatus status, ZOOM_SDK_NAMESPACE::IDirectShareViaMeetingIDOrPairingCodeHandler* handler )
{
	if (NULL != m_pLoggedInFlowUIEvent)
	{
		m_pLoggedInFlowUIEvent->OnDirectShareStatusUpdate(status, handler);
	}
}