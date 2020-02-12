#include "stdafx.h"
#include "LOGIN_join_meeting_only_workflow.h"

CSDKWithoutLoginStartJoinMeetingFlow::CSDKWithoutLoginStartJoinMeetingFlow()
{
	m_pCSDKJoinMeetingOnlyFlowUIEvent = NULL;
	m_pAuthService = NULL;
	m_pMeetingService = NULL;
}

CSDKWithoutLoginStartJoinMeetingFlow::~CSDKWithoutLoginStartJoinMeetingFlow()
{
	m_pAuthService = NULL;
	m_pMeetingService = NULL;
	SDKInterfaceWrap::GetInst().UnListenMeetingServiceEvent(this);
}

void CSDKWithoutLoginStartJoinMeetingFlow::SetUIEvent(CSDKJoinMeetingOnlyFlowUIEvent *event_)
{
	m_pCSDKJoinMeetingOnlyFlowUIEvent = event_;
}

bool CSDKWithoutLoginStartJoinMeetingFlow::IsMeetingServiceReady()
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
ZOOM_SDK_NAMESPACE::SDKError CSDKWithoutLoginStartJoinMeetingFlow::JoinMeeting(ZOOM_SDK_NAMESPACE::JoinParam& paramJoinMeeting)
{
	if(m_pAuthService == NULL)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
		//SDKInterfaceWrap::GetInst().ListenAuthServiceEvent(this);
	}
	if(m_pAuthService)
	{
		if(IsMeetingServiceReady())
		{
			/*some configurations about the meeting should be called here*/
			if (m_pMeetingService->GetMeetingConfiguration())
			{
				m_pMeetingService->GetMeetingConfiguration()->SetSharingToolbarVisibility(true);
			}
			ZOOM_SDK_NAMESPACE::ISettingService* pSettingService = SDKInterfaceWrap::GetInst().GetSettingService();
			if(pSettingService)
			{
				ZOOM_SDK_NAMESPACE::IAudioSettingContext* pAudioContext = pSettingService->GetAudioSettings();
				if(pAudioContext)
				{
					pAudioContext->EnableAutoJoinAudio(true);
				}
			}
			ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
			err = m_pMeetingService->Join(paramJoinMeeting);
			return err;
		}
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}


void CSDKWithoutLoginStartJoinMeetingFlow::onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo)
{
	//todo
}

void CSDKWithoutLoginStartJoinMeetingFlow::onLogout()
{
	//todo
}

void CSDKWithoutLoginStartJoinMeetingFlow::onZoomIdentityExpired()
{
	//todo
}

void CSDKWithoutLoginStartJoinMeetingFlow::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult)
{
 	if(NULL != m_pCSDKJoinMeetingOnlyFlowUIEvent)
 		m_pCSDKJoinMeetingOnlyFlowUIEvent->onMeetingStatusChanged(status, iResult);
 }

void CSDKWithoutLoginStartJoinMeetingFlow::onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type)
{
	//todo
}

void CSDKWithoutLoginStartJoinMeetingFlow::onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler)
{
	//todo
}

void CSDKWithoutLoginStartJoinMeetingFlow::onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param)
{
	//todo
}