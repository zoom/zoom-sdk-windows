#include "stdafx.h"
#include "SETTINGS_general_workflow.h"
CSDKGeneralSettingsWorkFlow::CSDKGeneralSettingsWorkFlow()
{
	m_pSettingService = NULL;
	m_pGeneralSettingContext = NULL;
	Init();
}
CSDKGeneralSettingsWorkFlow::~CSDKGeneralSettingsWorkFlow()
{
	m_pSettingService = NULL;
	m_pGeneralSettingContext = NULL;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKGeneralSettingsWorkFlow::Init()
{
	if(NULL == m_pSettingService)
	{
		m_pSettingService = SDKInterfaceWrap::GetInst().GetSettingService();
	}
	if(m_pSettingService)
	{
		m_pGeneralSettingContext = m_pSettingService->GetGeneralSettings();
	}
	if(NULL == m_pGeneralSettingContext)
	{
		return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKGeneralSettingsWorkFlow::EnableDualScreenMode(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableDualScreenMode(m_bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKGeneralSettingsWorkFlow::EnableSplitScreenMode(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableSplitScreenMode(m_bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKGeneralSettingsWorkFlow::TurnOffAeroModeInSharing( bool m_bTurnoff)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->TurnOffAeroModeInSharing(m_bTurnoff);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKGeneralSettingsWorkFlow::EnableAutoFitToWindowWhenViewSharing(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableAutoFitToWindowWhenViewSharing(m_bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKGeneralSettingsWorkFlow::EnableAutoFullScreenVideoWhenJoinMeeting(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableAutoFullScreenVideoWhenJoinMeeting(m_bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKGeneralSettingsWorkFlow::EnableAutoFullScreenVideoWhenViewShare(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableAutoFullScreenVideoWhenViewShare(m_bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
bool CSDKGeneralSettingsWorkFlow::IsDualScreenModeEnabled()
{
	if(m_pGeneralSettingContext)
	{
		bool bChecked = m_pGeneralSettingContext->IsDualScreenModeEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::IsAeroModeInSharingTurnOff()
{
	if(m_pGeneralSettingContext)
	{
		bool bChecked = m_pGeneralSettingContext->IsAeroModeInSharingTurnOff();
		return bChecked;
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::IsAutoFitToWindowWhenViewSharingEnabled()
{
	if(m_pGeneralSettingContext)
	{
		bool bChecked = m_pGeneralSettingContext->IsAutoFitToWindowWhenViewSharingEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::IsAutoFullScreenVideoWhenJoinMeetingEnabled()
{
	if(m_pGeneralSettingContext)
	{
		bool bChecked = m_pGeneralSettingContext->IsAutoFullScreenVideoWhenJoinMeetingEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::IsAutoFullScreenVideoWhenViewShareEnabled()
{
	if(m_pGeneralSettingContext)
	{
		bool bChecked = m_pGeneralSettingContext->IsAutoFullScreenVideoWhenViewShareEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::IsSplitScreenModeEnabled()
{
	if(m_pGeneralSettingContext)
	{
		bool bChecked = m_pGeneralSettingContext->IsSplitScreenModeEnabled();
		return bChecked;
	}
	return false;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKGeneralSettingsWorkFlow::EnableDisplayReminderWindowWhenExit(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableDisplayReminderWindowWhenExit(m_bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKGeneralSettingsWorkFlow::EnableShowMyMeetingElapseTime(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableShowMyMeetingElapseTime(m_bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKGeneralSettingsWorkFlow::EnableAccelerateGPUWhenShare(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableAccelerateGPUWhenShare(m_bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKGeneralSettingsWorkFlow::EnableRemoteControlAllApplications(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableRemoteControlAllApplications(m_bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
bool CSDKGeneralSettingsWorkFlow::IsDisplayReminderWindowWhenExitEnabled()
{
	if(m_pGeneralSettingContext)
	{
		bool bChecked = m_pGeneralSettingContext->IsDisplayReminderWindowWhenExitEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::IsShowMyMeetingElapseTimeEnabled()
{
	if(m_pGeneralSettingContext)
	{
		bool bChecked = m_pGeneralSettingContext->IsShowMyMeetingElapseTimeEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::IsAccelerateGPUWhenShareEnabled(bool& m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->IsAccelerateGPUWhenShareEnabled(m_bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return m_bEnable ? true : false;
		}
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::IsRemoteControlAllApplicationsEnabled()
{
	if(m_pGeneralSettingContext)
	{
		bool bChecked = m_pGeneralSettingContext->IsRemoteControlAllApplicationsEnabled();
		return bChecked;
	}
	return false;
}
