#pragma once
#include "sdk_util.h"
#include "stdafx.h"
#include "setting_service_interface.h"

class CSDKGeneralSettingsWorkFlow
{
public:
	CSDKGeneralSettingsWorkFlow();
	virtual ~CSDKGeneralSettingsWorkFlow();
	bool Init();
	void Cleanup(){}
	bool EnableDualScreenMode(bool m_bEnable);
	bool TurnOffAeroModeInSharing(bool m_bTurnoff);
	bool EnableAutoFitToWindowWhenViewSharing(bool m_bEnable);
	bool EnableAutoFullScreenVideoWhenJoinMeeting(bool m_bEnable);
	bool EnableAutoFullScreenVideoWhenViewShare(bool m_bEnable);
	bool EnableSplitScreenMode(bool m_bEnable);
	bool IsDualScreenModeEnabled();
	bool IsAeroModeInSharingTurnOff();
	bool IsAutoFitToWindowWhenViewSharingEnabled();
	bool IsAutoFullScreenVideoWhenJoinMeetingEnabled();
	bool IsAutoFullScreenVideoWhenViewShareEnabled();
	bool IsSplitScreenModeEnabled();
private:
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	ZOOM_SDK_NAMESPACE::IGeneralSettingContext* m_pGeneralSettingContext;

};