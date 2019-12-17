#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "resource.h"
#include "sdk_demo_app_common.h"
//#include "LOGIN_login_with_email_workflow.h"
class CSDKJoinMeetingOnlyFlowUIEvent
{
 public:
	 virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0) = 0;
	 virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type) = 0;
	 virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler) = 0;
	 virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param) = 0;
	 
};
class CSDKWithoutLoginStartJoinMeetingFlow:public ZOOM_SDK_NAMESPACE::IAuthServiceEvent,public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent
{
public:
	CSDKWithoutLoginStartJoinMeetingFlow();
	virtual ~CSDKWithoutLoginStartJoinMeetingFlow();
    bool IsMeetingServiceReady();
	ZOOM_SDK_NAMESPACE::SDKError JoinMeeting(ZOOM_SDK_NAMESPACE::JoinParam& paramJoinMeeting);
	void Cleanup() {}
    void SetUIEvent(CSDKJoinMeetingOnlyFlowUIEvent *event_);

	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret) {};
	virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo);
	virtual void onLogout();
	virtual void onZoomIdentityExpired();
	virtual void onZoomAuthIdentityExpired() {}

	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type);
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler);
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param);


private:
	CSDKJoinMeetingOnlyFlowUIEvent *m_pCSDKJoinMeetingOnlyFlowUIEvent;
	ZOOM_SDK_NAMESPACE::IAuthService *m_pAuthService;
	ZOOM_SDK_NAMESPACE::IMeetingService *m_pMeetingService;
};