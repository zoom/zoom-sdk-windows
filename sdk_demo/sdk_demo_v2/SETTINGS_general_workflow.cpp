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
bool CSDKGeneralSettingsWorkFlow::Init()
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
		return false;
	}
	return true;
}
bool CSDKGeneralSettingsWorkFlow::EnableDualScreenMode(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableDualScreenMode(m_bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::EnableSplitScreenMode(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableSplitScreenMode(m_bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::TurnOffAeroModeInSharing( bool m_bTurnoff)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->TurnOffAeroModeInSharing(m_bTurnoff);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::EnableAutoFitToWindowWhenViewSharing(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableAutoFitToWindowWhenViewSharing(m_bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::EnableAutoFullScreenVideoWhenJoinMeeting(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableAutoFullScreenVideoWhenJoinMeeting(m_bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKGeneralSettingsWorkFlow::EnableAutoFullScreenVideoWhenViewShare(bool m_bEnable)
{
	if(m_pGeneralSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pGeneralSettingContext->EnableAutoFullScreenVideoWhenViewShare(m_bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
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