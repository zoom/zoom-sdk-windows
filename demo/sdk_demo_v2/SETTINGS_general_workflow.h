#pragma once
#include "sdk_util.h"
#include "stdafx.h"
#include "setting_service_interface.h"

class CSDKGeneralSettingsWorkFlow
{
public:
	CSDKGeneralSettingsWorkFlow();
	virtual ~CSDKGeneralSettingsWorkFlow();
	ZOOM_SDK_NAMESPACE::SDKError Init();
	void Cleanup(){}
	ZOOM_SDK_NAMESPACE::SDKError EnableDualScreenMode(bool m_bEnable);
	ZOOM_SDK_NAMESPACE::SDKError TurnOffAeroModeInSharing(bool m_bTurnoff);
	ZOOM_SDK_NAMESPACE::SDKError EnableAutoFitToWindowWhenViewSharing(bool m_bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool m_bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableAutoFullScreenVideoWhenViewShare(bool m_bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableSplitScreenMode(bool m_bEnable);
	bool IsDualScreenModeEnabled();
	bool IsAeroModeInSharingTurnOff();
	bool IsAutoFitToWindowWhenViewSharingEnabled();
	bool IsAutoFullScreenVideoWhenJoinMeetingEnabled();
	bool IsAutoFullScreenVideoWhenViewShareEnabled();
	bool IsSplitScreenModeEnabled();
	
	ZOOM_SDK_NAMESPACE::SDKError EnableDisplayReminderWindowWhenExit(bool m_bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableShowMyMeetingElapseTime(bool m_bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableAccelerateGPUWhenShare(bool m_bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableRemoteControlAllApplications(bool m_bEnable);
	bool IsDisplayReminderWindowWhenExitEnabled();
	bool IsShowMyMeetingElapseTimeEnabled();
	bool IsAccelerateGPUWhenShareEnabled(bool& m_bEnable);
	bool IsRemoteControlAllApplicationsEnabled();
	
private:
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	ZOOM_SDK_NAMESPACE::IGeneralSettingContext* m_pGeneralSettingContext;

};