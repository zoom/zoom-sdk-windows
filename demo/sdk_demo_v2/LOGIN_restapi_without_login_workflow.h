#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "resource.h"
#include "sdk_demo_app_common.h"
#include "LOGIN_login_with_email_workflow.h"

class CSDKRestAPIUserUIEvent
{
public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0) = 0;
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type) = 0;
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler) = 0;
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param) = 0;
};

class CSDKRestAPIUserWorkFlow : public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent
{
public:
	CSDKRestAPIUserWorkFlow();
	virtual ~CSDKRestAPIUserWorkFlow();
	void Cleanup(){};
	ZOOM_SDK_NAMESPACE::SDKError RestAPIStartMeeting(ZOOM_SDK_NAMESPACE::StartParam& startParam);
	void SetUIEvent(CSDKRestAPIUserUIEvent* event_);
	bool IsMeetingServiceReady();
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type);
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler);
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param);
	
protected:
	CSDKRestAPIUserUIEvent* m_pRestAPIUserUIEvent;
	ZOOM_SDK_NAMESPACE::IMeetingService *m_pMeetingService;
};
