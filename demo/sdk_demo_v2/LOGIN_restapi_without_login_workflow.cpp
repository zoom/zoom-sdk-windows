#include "stdafx.h"
#include "LOGIN_restapi_without_login_workflow.h"



CSDKRestAPIUserWorkFlow::CSDKRestAPIUserWorkFlow()
{
	m_pRestAPIUserUIEvent = NULL;
	m_pMeetingService = NULL;
}

CSDKRestAPIUserWorkFlow::~CSDKRestAPIUserWorkFlow()
{
	m_pMeetingService = NULL;
	m_pRestAPIUserUIEvent = NULL;
	SDKInterfaceWrap::GetInst().UnListenMeetingServiceEvent(this);
}

void CSDKRestAPIUserWorkFlow::SetUIEvent(CSDKRestAPIUserUIEvent *event_)
{
	m_pRestAPIUserUIEvent = event_;
}

bool CSDKRestAPIUserWorkFlow::IsMeetingServiceReady()
{
	if(NULL == m_pMeetingService)
	{
		m_pMeetingService = SDKInterfaceWrap::GetInst().GetMeetingService();
		if(NULL ==m_pMeetingService)
			return false;
		SDKInterfaceWrap::GetInst().ListenMeetingServiceEvent(this);
	}
	return true;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKRestAPIUserWorkFlow::RestAPIStartMeeting(ZOOM_SDK_NAMESPACE::StartParam& startParam)
{
	ZOOM_SDK_NAMESPACE::SDKError err(ZOOM_SDK_NAMESPACE::SDKERR_SERVICE_FAILED);
	if(IsMeetingServiceReady())
	{
		if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		{	
			/*some configurations about the meeting should be called here*/
			if (m_pMeetingService->GetMeetingConfiguration())
			{
				m_pMeetingService->GetMeetingConfiguration()->SetSharingToolbarVisibility(true);
			}
			
			err = m_pMeetingService->Start(startParam);
			return err;
		}

		return ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

void CSDKRestAPIUserWorkFlow::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult)
{
	if(NULL != m_pRestAPIUserUIEvent)
		m_pRestAPIUserUIEvent->onMeetingStatusChanged(status, iResult);
}

void CSDKRestAPIUserWorkFlow::onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type)
{
	if(NULL != m_pRestAPIUserUIEvent)
		m_pRestAPIUserUIEvent->onMeetingStatisticsWarningNotification(type);
}

void CSDKRestAPIUserWorkFlow::onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler)
{
	if(NULL != m_pRestAPIUserUIEvent)
		m_pRestAPIUserUIEvent->onMeetingSecureKeyNotification(key, len, pHandler);
}

void CSDKRestAPIUserWorkFlow::onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param)
{
	if(NULL != m_pRestAPIUserUIEvent)
		m_pRestAPIUserUIEvent->onMeetingParameterNotification(meeting_param);
}


