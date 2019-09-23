#pragma once
#include "sdk_util.h"
#include "stdafx.h"

class CSDKFeatureCustomSettingsWorkFlow
{
public:
	CSDKFeatureCustomSettingsWorkFlow();
	virtual ~CSDKFeatureCustomSettingsWorkFlow();
	ZOOM_SDK_NAMESPACE::SDKError Init();
	void CleanUp(){}
	void SetMeetingUIPos(ZOOM_SDK_NAMESPACE::WndPosition pos);
	void SetFloatVideoPos(ZOOM_SDK_NAMESPACE::WndPosition pos);
	void SetMeetingIDForMeetingUITitle(UINT64 meetingNumber);
	void EnableLButtonDBClick4SwitchFullScreenMode(bool bEnable);
	void EnableShareIOSDevice(bool bEnable);
	void EnableShareWhiteBoard(bool bEnable);
	void ForceDisableMultiShare(bool bDisable);
	void DisableRemoteCtrlCopyPasteFeature(bool bDisable);
	void EnableForceAutoStartMyVideoWhenJoinMeeting(bool bEnable);
	void EnableForceAutoStopMyVideoWhenJoinMeeting(bool bEnable);
	void EnableAutoAdjustSpeakerVolumeWhenJoinAudio(bool bEnable);
	void EnableAutoAdjustMicVolumeWhenJoinAudio(bool bEnable);
	void EnableClaimHostFeature(bool bEnable);
	void DisableSplitScreenModeUIElements(bool bDisable);
	void EnableAutoEndOtherMeetingWhenStartMeeting(bool bEnable);
	void PrePopulateWebinarRegistrationInfo(const wchar_t* email, const wchar_t* username);
	ZOOM_SDK_NAMESPACE::SDKError EnableGrabShareWithoutReminder(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError BackToMeeting();
	ZOOM_SDK_NAMESPACE::SDKError EnterFullScreen(bool firstView, bool secondView);
	ZOOM_SDK_NAMESPACE::SDKError ExitFullScreen(bool firstView, bool secondView);
	ZOOM_SDK_NAMESPACE::SDKError MoveFloatVideoWnd(int left, int top);
	ZOOM_SDK_NAMESPACE::SDKError SwitchFloatVideoToActiveSpkMod();
	ZOOM_SDK_NAMESPACE::SDKError SwitchFloatVideoToGalleryMod();
	ZOOM_SDK_NAMESPACE::SDKError SwitchToVideoWall();
	ZOOM_SDK_NAMESPACE::SDKError ShowPreOrNextPageVideo(bool bPageUp);
	ZOOM_SDK_NAMESPACE::SDKError SwtichToAcitveSpeaker();
	ZOOM_SDK_NAMESPACE::SDKError ShowParticipantsListWnd(bool bShow, HWND& hParticipantsListWnd);
	ZOOM_SDK_NAMESPACE::SDKError ShowChatDlg(ZOOM_SDK_NAMESPACE::ShowChatDlgParam& param);
	ZOOM_SDK_NAMESPACE::SDKError HideChatDlg();
	ZOOM_SDK_NAMESPACE::SDKError SwitchSplitScreenMode(bool bSplit);
private:
	ZOOM_SDK_NAMESPACE::IMeetingService* m_pMeetingService;
	ZOOM_SDK_NAMESPACE::IMeetingConfiguration* m_pMeetingConfiguration;
	ZOOM_SDK_NAMESPACE::IMeetingUIController* m_pMeetingUIController;
};