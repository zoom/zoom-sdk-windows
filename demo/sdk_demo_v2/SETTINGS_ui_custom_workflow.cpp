#include "stdafx.h"
#include "SETTINGS_ui_custom_workflow.h"
CSDKUICustomSettingsWorkFlow::CSDKUICustomSettingsWorkFlow()
{
	m_pMeetingService = NULL;
	m_pMeetingConfiguration = NULL;
	m_pMeetingUIController = NULL;
	Init();
}
CSDKUICustomSettingsWorkFlow::~CSDKUICustomSettingsWorkFlow()
{
	m_pMeetingService = NULL;
	m_pMeetingConfiguration = NULL;
	m_pMeetingUIController = NULL;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKUICustomSettingsWorkFlow::Init()
{
	if(NULL == m_pMeetingService)
	{
		m_pMeetingService = SDKInterfaceWrap::GetInst().GetMeetingService();
	}
	if(m_pMeetingService)
	{
		m_pMeetingConfiguration = m_pMeetingService->GetMeetingConfiguration();
		m_pMeetingUIController = m_pMeetingService->GetUIController();
	}
	if(m_pMeetingConfiguration && m_pMeetingUIController)
	{
		return ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
void CSDKUICustomSettingsWorkFlow::SetSharingToolbarVisibility(bool bShow)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->SetSharingToolbarVisibility(bShow);
	}
}
void CSDKUICustomSettingsWorkFlow::SetBottomFloatToolbarWndVisibility(bool bShow)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->SetBottomFloatToolbarWndVisibility(bShow);
	}
}

void CSDKUICustomSettingsWorkFlow::EnableApproveRemoteControlDlg(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableApproveRemoteControlDlg(bEnable);
	}
}
void CSDKUICustomSettingsWorkFlow::EnableDeclineRemoteControlResponseDlg(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableDeclineRemoteControlResponseDlg(bEnable);
	}
}
void CSDKUICustomSettingsWorkFlow::EnableLeaveMeetingOptionForHost(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableLeaveMeetingOptionForHost(bEnable);
	}
}
void CSDKUICustomSettingsWorkFlow::EnableInviteButtonOnMeetingUI(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableInviteButtonOnMeetingUI(bEnable);
	}
}
void CSDKUICustomSettingsWorkFlow::EnableEnterAndExitFullScreenButtonOnMeetingUI(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableEnterAndExitFullScreenButtonOnMeetingUI(bEnable);
	}
}
void CSDKUICustomSettingsWorkFlow::SetFloatVideoWndVisibility(bool bShow)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->SetFloatVideoWndVisibility(bShow);
	}
}
void CSDKUICustomSettingsWorkFlow::EnableToolTipsShow(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableToolTipsShow(bEnable);
	}
}
void CSDKUICustomSettingsWorkFlow::EnableAirplayInstructionWindow(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableAirplayInstructionWindow(bEnable);
	}
}
void CSDKUICustomSettingsWorkFlow::EnableAutoHideJoinAudioDialog(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableAutoHideJoinAudioDialog(bEnable);
	}
}
void CSDKUICustomSettingsWorkFlow::AlwaysShowIconOnTaskBar(bool bAlwaysShow)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->AlwaysShowIconOnTaskBar(bAlwaysShow);
	}
}
void CSDKUICustomSettingsWorkFlow::SetShowAudioUseComputerSoundChkbox(bool bShow)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->SetShowAudioUseComputerSoundChkbox(bShow);
	}
}
void CSDKUICustomSettingsWorkFlow::SetShowVideoOptimizeChkbox(bool bShow)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->SetShowVideoOptimizeChkbox(bShow);
	}
}
void CSDKUICustomSettingsWorkFlow::SetShowCallInTab(bool bShow)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->SetShowCallInTab(bShow);
	}
}
void CSDKUICustomSettingsWorkFlow::SetShowCallMeTab(bool bShow)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->SetShowCallMeTab(bShow);
	}
}

ZOOM_SDK_NAMESPACE::SDKError CSDKUICustomSettingsWorkFlow::DisableTopMostAttr4SettingDialog(bool bDisable)
{
	if(m_pMeetingConfiguration)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingConfiguration->DisableTopMostAttr4SettingDialog(bDisable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
void CSDKUICustomSettingsWorkFlow::EnableShowShareSwitchMultiToSingleConfirmDlg(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableShowShareSwitchMultiToSingleConfirmDlg(bEnable);
	}
}
void CSDKUICustomSettingsWorkFlow::DisableFreeMeetingRemainTimeNotify(bool bDisable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->DisableFreeMeetingRemainTimeNotify(bDisable);
	}
}
void CSDKUICustomSettingsWorkFlow::HideChatItemOnMeetingUI(bool bHide)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->HideChatItemOnMeetingUI(bHide);
	}
}
void CSDKUICustomSettingsWorkFlow::HideReactionItemOnMeetingUI(bool bHide)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->HideReactionsOnMeetingUI(bHide);
	}
}
void CSDKUICustomSettingsWorkFlow::HideMeetingInfoItemOnMeetingUI(bool bHide)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->HideMeetingInfoOnMeetingUI(bHide);
	}
}
void CSDKUICustomSettingsWorkFlow::HideRecordItemOnMeetingUI(bool bHide)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->HideRecordItemOnMeetingUI(bHide);
	}
}
void CSDKUICustomSettingsWorkFlow::HideUpgradeFreeMeetingButton(bool bHide)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->HideUpgradeFreeMeetingButton(bHide);
	}
}
void CSDKUICustomSettingsWorkFlow::SetShowInviteDlgTabPage(ZOOM_SDK_NAMESPACE::SDKInviteDlgTabPage tabPage, bool bShow)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->SetShowInviteDlgTabPage(tabPage,bShow);
	}
}
void CSDKUICustomSettingsWorkFlow::SetShowH323SubTabPage(ZOOM_SDK_NAMESPACE::SDKH323TabPage tabPage, bool bShow)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->SetShowH323SubTabPage(tabPage,bShow);
	}
}
void CSDKUICustomSettingsWorkFlow::DisablePopupMeetingWrongPSWDlg(bool bDisable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->DisablePopupMeetingWrongPSWDlg(bDisable);
	}
}
void CSDKUICustomSettingsWorkFlow::DisableWaitingForHostDialog(bool bDisable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->DisableWaitingForHostDialog(bDisable);
	}
}
void CSDKUICustomSettingsWorkFlow::EnableInputMeetingPasswordDlg(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableInputMeetingPasswordDlg(bEnable);
	}
}
void CSDKUICustomSettingsWorkFlow::EnableInputMeetingScreenNameDlg(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableInputMeetingScreenNameDlg(bEnable);
	}
}
void CSDKUICustomSettingsWorkFlow::DisableAutoShowSelectJoinAudioDlgWhenJoinMeeting(bool bDisable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->DisableAutoShowSelectJoinAudioDlgWhenJoinMeeting(bDisable);
	}
}
void CSDKUICustomSettingsWorkFlow::EnableHideFullPhoneNumber4PureCallinUser(bool bHide)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableHideFullPhoneNumber4PureCallinUser(bHide);
	}
}
ZOOM_SDK_NAMESPACE::SDKError CSDKUICustomSettingsWorkFlow::ShowSharingToolbar(bool bShow)
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->ShowSharingToolbar(bShow);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKUICustomSettingsWorkFlow::ChangeFloatoActiveSpkVideoSize(ZOOM_SDK_NAMESPACE::SDKFloatVideoType type)
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->ChangeFloatoActiveSpkVideoSize(type);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE; 
}
ZOOM_SDK_NAMESPACE::SDKError CSDKUICustomSettingsWorkFlow::ShowSharingFrameWindows(bool bShow)
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->ShowSharingFrameWindows(bShow);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE; 
}
