#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "resource.h"
#include "sdk_demo_app_common.h"

class CSDKLoggedInFlowUIEvent
{
public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0) = 0;
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type) = 0;
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler) = 0;
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param) = 0;
	virtual void OnDirectShareStatusUpdate(ZOOM_SDK_NAMESPACE::DirectShareStatus status, ZOOM_SDK_NAMESPACE::IDirectShareViaMeetingIDOrPairingCodeHandler* handler) = 0;
};

class CSDKLoggedInUIWorkFlow : public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent,public ZOOM_SDK_NAMESPACE::IDirectShareServiceHelperEvent
{
public:
	CSDKLoggedInUIWorkFlow();
	virtual ~CSDKLoggedInUIWorkFlow();

	void SetUIEvent(CSDKLoggedInFlowUIEvent* event_);

	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type);
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler);
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param);

	virtual void OnDirectShareStatusUpdate(ZOOM_SDK_NAMESPACE::DirectShareStatus status, ZOOM_SDK_NAMESPACE::IDirectShareViaMeetingIDOrPairingCodeHandler* handler);


public:
	bool IsMeetingServiceReady();
	ZOOM_SDK_NAMESPACE::SDKError StartMeeting(ZOOM_SDK_NAMESPACE::StartParam& paramStartMeeting);
	ZOOM_SDK_NAMESPACE::SDKError EndMeeting();
	ZOOM_SDK_NAMESPACE::SDKError LeaveMeeting();
	ZOOM_SDK_NAMESPACE::SDKError BringMeetingToFront();
	ZOOM_SDK_NAMESPACE::SDKError DirectShare();

protected:
	CSDKLoggedInFlowUIEvent* m_pLoggedInFlowUIEvent;
	ZOOM_SDK_NAMESPACE::IMeetingService* m_pMeetingService;
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	ZOOM_SDK_NAMESPACE::IDirectShareServiceHelper* m_pDirectShareService;
};
