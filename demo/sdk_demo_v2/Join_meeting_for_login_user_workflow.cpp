#include "stdafx.h"
#include "Join_meeting_for_login_user_workflow.h"
CSDKJoinMeetingForLoginUserFlow::CSDKJoinMeetingForLoginUserFlow()
{
	m_pJoinMeetingForLoginUserFlowUIEvent = NULL;
	m_pMeetingService =NULL;
}
CSDKJoinMeetingForLoginUserFlow::~CSDKJoinMeetingForLoginUserFlow()
{
	m_pJoinMeetingForLoginUserFlowUIEvent = NULL;
	m_pMeetingService = NULL;
	SDKInterfaceWrap::GetInst().UnListenMeetingServiceEvent(this);
}
void CSDKJoinMeetingForLoginUserFlow::SetUIEvent(CSDKJoinMeetingForLoginUserFlowUIEvent* event_)
{
	m_pJoinMeetingForLoginUserFlowUIEvent = event_;
}
bool CSDKJoinMeetingForLoginUserFlow::IsMeetingServiceReady()
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

ZOOM_SDK_NAMESPACE::SDKError CSDKJoinMeetingForLoginUserFlow::JoinMeeting(ZOOM_SDK_NAMESPACE::JoinParam& paramJoinMeeting)
{
	if(IsMeetingServiceReady())
	{
		if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		{	
			/*some configurations about the meeting should be called here*/
			if (m_pMeetingService->GetMeetingConfiguration())
			{
				m_pMeetingService->GetMeetingConfiguration()->SetSharingToolbarVisibility(true);
			}

			return m_pMeetingService->Join(paramJoinMeeting);
	
		}
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
void CSDKJoinMeetingForLoginUserFlow::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult)
{
	if(NULL != m_pJoinMeetingForLoginUserFlowUIEvent)
		m_pJoinMeetingForLoginUserFlowUIEvent->onMeetingStatusChanged(status, iResult);
}

void CSDKJoinMeetingForLoginUserFlow::onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type)
{
	//todo
}

void CSDKJoinMeetingForLoginUserFlow::onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler)
{
	//todo
}

void CSDKJoinMeetingForLoginUserFlow::onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param)
{
	//todo
}