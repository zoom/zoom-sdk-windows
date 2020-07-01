#pragma once
#include "sdk_util.h"
#include "stdafx.h"

class CSDKUICustomSettingsWorkFlow
{
public:
	CSDKUICustomSettingsWorkFlow();
	virtual ~CSDKUICustomSettingsWorkFlow();
	ZOOM_SDK_NAMESPACE::SDKError Init();
	void Cleanup(){}
	///meeting_configuration_interface.h
	void SetSharingToolbarVisibility(bool bShow);
	void SetBottomFloatToolbarWndVisibility(bool bShow);
	void EnableApproveRemoteControlDlg(bool bEnable);
	void EnableDeclineRemoteControlResponseDlg(bool bEnable);
	void EnableLeaveMeetingOptionForHost(bool bEnable);
	void EnableInviteButtonOnMeetingUI(bool bEnable);
	void EnableEnterAndExitFullScreenButtonOnMeetingUI(bool bEnable);
	void SetFloatVideoWndVisibility(bool bShow);
	void EnableToolTipsShow(bool bEnable);
	void EnableAirplayInstructionWindow(bool bEnable);
	void EnableAutoHideJoinAudioDialog(bool bEnable);
	void AlwaysShowIconOnTaskBar(bool bAlwaysShow);
	void SetShowAudioUseComputerSoundChkbox(bool bShow);
	void SetShowVideoOptimizeChkbox(bool bShow);
	void SetShowCallInTab(bool bShow);
	void SetShowCallMeTab(bool bShow);
	ZOOM_SDK_NAMESPACE::SDKError DisableTopMostAttr4SettingDialog(bool bDisable);
	void EnableShowShareSwitchMultiToSingleConfirmDlg(bool bEnable);
	void DisableFreeMeetingRemainTimeNotify(bool bDisable);
	void HideChatItemOnMeetingUI(bool bHide);
	void HideReactionItemOnMeetingUI(bool bHide);
	void HideMeetingInfoItemOnMeetingUI(bool bHide);
	void HideRecordItemOnMeetingUI(bool bHide);
	void HideUpgradeFreeMeetingButton(bool bHide);
	void SetShowInviteDlgTabPage(ZOOM_SDK_NAMESPACE::SDKInviteDlgTabPage tabPage, bool bShow);
	void SetShowH323SubTabPage(ZOOM_SDK_NAMESPACE::SDKH323TabPage tabPage, bool bShow);
	void DisablePopupMeetingWrongPSWDlg(bool bDisable);
	void DisableWaitingForHostDialog(bool bDisable);
	void EnableInputMeetingPasswordDlg(bool bEnable);
	void EnableInputMeetingScreenNameDlg(bool bEnable);
	void DisableAutoShowSelectJoinAudioDlgWhenJoinMeeting(bool bDisable);
	void EnableHideFullPhoneNumber4PureCallinUser(bool bHide);
	///meeting_ui_ctrl_interface.h
	ZOOM_SDK_NAMESPACE::SDKError ShowSharingToolbar(bool bShow);
	ZOOM_SDK_NAMESPACE::SDKError ChangeFloatoActiveSpkVideoSize(ZOOM_SDK_NAMESPACE::SDKFloatVideoType type);
	ZOOM_SDK_NAMESPACE::SDKError ShowSharingFrameWindows(bool bShow);

private:
	ZOOM_SDK_NAMESPACE::IMeetingService* m_pMeetingService;
	ZOOM_SDK_NAMESPACE::IMeetingConfiguration* m_pMeetingConfiguration;
	ZOOM_SDK_NAMESPACE::IMeetingUIController* m_pMeetingUIController;

};