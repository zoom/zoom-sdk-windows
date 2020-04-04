#pragma once
#include "sdk_util.h"
#include "resource.h"
#include "UIlib.h"
#include "sdk_demo_app_common.h"
#include "SETTINGS_general_workflow.h"
#include "SETTINGS_audio_workflow.h"
#include "SETTINGS_video_workflow.h"
#include "SETTINGS_recording_workflow.h"
#include "SETTINGS_ui_custom_workflow.h"
#include "SETTINGS_feature_custom_workflow.h"
#include "SETTINGS_virtualBG_workflow.h"
#ifdef _ONE_CLICK_TEST_
#include "setting_api_test.h"
#endif
#include <shellapi.h>
#include "Shlobj.h"

enum settingsAudioTestingType
{
	audio_speaker_test = 0,
	audio_speaker_stop,
	audio_mic_test,
	audio_mic_recording,
	audio_mic_playing,
};
enum SettingsUICustom_page
{
	UICustom_Meeting_Window_Page = 0,
	UICustom_Share_Page,
	UICustom_Join_Meeting_Page,
	UICustom_Invite_Page,
	UICustom_Others_Page,
};
enum SettingsFeatureCustom_page
{
	FeatureCustom_Meeting_Window_Page = 0,
	FeatureCustom_Share_Page,
	FeatureCustom_Audio_Page,
	FeatureCustom_Video_Page,
	FeatureCustom_Other_Functions_Page,
};
class CSDKSettingsUIMgr;
class CSDKGeneralSettingsUIGroup
{
public:
	CSDKGeneralSettingsUIGroup();
	virtual ~CSDKGeneralSettingsUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_);
	void UninitWindow();
	void GetGeneralSettingsFlags();
	void Show();
	void Hide();
	bool IsVisable()
	{
		if (m_settingsGeneralPage)
		{
			return m_settingsGeneralPage->IsVisible();
		}
		return false;
	}
	void Notify( TNotifyUI&  msg);

	void DoDualScreenModeChkClick();
	void DoTurnOffAeroModeInSharingChkClick();
	void DoAutoFitToWindowWhenViewSharingChkClik();
	void DoAutoFullScreenVideoWhenJoinMeetingChkClick();
	void DoAutoFullScreenVideoWhenViewShareChkClick();
	void DoSplitScreenModeChkClick();
	
	void DoDisplayReminderWindowWhenExitChkClick();
	void DoShowMyMeetingElapseTimeChkClick();
	void DoAccelerateGPUWhenShareChkClick();
	void DoRemoteControlAllApplicationsChkClick();
	

protected:
	CVerticalLayoutUI* m_settingsGeneralPage;
	CSDKGeneralSettingsWorkFlow m_generalSettingsWorkFlow;
	CSDKSettingsUIMgr*	 m_parentFrame;
	CCheckBoxUI*  m_chkDualScreenMode;
	CCheckBoxUI*  m_chkAutoFullScreenVideoWhenJoinMeeting;
	CCheckBoxUI*  m_chkAutoFullScreenVideoWhenViewShare;
	CCheckBoxUI*  m_chkAutoFitToWindowWhenViewSharing;
	CCheckBoxUI*  m_chkTurnOffAeroModeInSharing;
	CCheckBoxUI*  m_chkSplitScreenMode;
	
	CCheckBoxUI*  m_chkUseDisplayReminderWindowWhenExit;
	CCheckBoxUI*  m_chkShowMyMeetingElapseTime;
	CCheckBoxUI*  m_chkAccelerateGPUWhenShare;
	CCheckBoxUI*  m_chkEnableRomoteControllAllApplications;
	
};

class CSDKAudioSettingsUIGroup : public CSDKAudioSettingsUIEvent
{
public:
	CSDKAudioSettingsUIGroup();
	virtual ~CSDKAudioSettingsUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_);
	void UninitWindow();
	void GetAudioSettingsFlags();
	void Show();
	void Hide();
	bool IsVisable()
	{
		if (m_settingsAudioPage)
		{
			return m_settingsAudioPage->IsVisible();
		}
		return false;
	}
	void Notify( TNotifyUI& msg);

	void DoAutoJoinAudioChkClick();
	void DoAutoAdjustMicChkClick();
	void DoStereoAudioChkClick();
	void DoMicOriginalInputChkClick();
	void DoHoldSpaceKeyToSpeakChkClick();
	void DoAlwaysMuteMicWhenJoinVoipChkClick();
	void DoSuppressAudioNotifyChkClick();
	
	void DoEchoCancellationChkClick();
	
	void DoTestSpeakerButtonClick();
	void DoStopSpeakerButtonClick();
	void DoTestMicButtonClick();
	void DoRecordingMicButtonClick();
	void DoPlayingMicButtonClick();
	void DoSetSpeakerVol();
	void DoSetMicVol();
	void UpdateSpeakerList();
	void UpdateMicList();
	void UpdateUI(settingsAudioTestingType type);
	void StopAudioTest();
	const wchar_t* SelectSpeaker();
	const wchar_t* SelectMic();

	virtual void OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume);
	virtual void OnNoAudioDeviceIsUseful(bool bMicOrSpk); 
	virtual void OnTestMicStatusChanged(ZOOM_SDK_NAMESPACE::SDK_TESTMIC_STATUS status,bool& bHandled); 
	virtual void OnSelectedAudioDeviceIsChanged();
	virtual void OnComputerMicDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IMicInfo*>* pNewMicList);
	virtual void OnComputerSpeakerDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ISpeakerInfo*>* pNewSpeakerList);
	virtual void onDefaultMicDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) {}
	virtual void onDefaultSpeakerDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) {}

protected:
	ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ISpeakerInfo*>* m_lstTestSpeaker;
	ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IMicInfo*>* m_lstTestMic;
	ZOOM_SDK_NAMESPACE::ISpeakerInfo* m_pSpeakerInfo;
	ZOOM_SDK_NAMESPACE::IMicInfo* m_pMicInfo;
	CListLabelElementUI* m_pSpeakerListElement;
	CListLabelElementUI* m_pMicListElement;
	CVerticalLayoutUI* m_settingsAudioPage;
	CSDKAudioSettingsWorkFlow m_audioSettingsWorkFlow;
	CSDKSettingsUIMgr* m_parentFrame;
	CCheckBoxUI* m_chkAutoJoinAudio;
	CCheckBoxUI* m_chkAutoAdjustMic;
	CCheckBoxUI* m_chkStereoAudio;
	CCheckBoxUI* m_chkMicOriginalInput;
	CCheckBoxUI* m_chkHoldSpaceKeyToSpeak;
	CCheckBoxUI* m_chkAlwaysMuteMicWhenJoinVoip;
	CCheckBoxUI* m_chkSuppressAudioNotify;

	CCheckBoxUI* m_chkEchoCancellation;
	
	CComboUI*  m_comboTestSpeaker;
	CComboUI* m_comboTestMic;
	CButtonUI* m_btnTestSpeaker;
	CButtonUI* m_btnStopSpeaker;
	CButtonUI* m_btnTestMic;
	CButtonUI* m_btnRecordingMic;
	CButtonUI* m_btnPlayingMic;
	CSliderUI* m_sldSpeakerVolume;
	CSliderUI* m_sldMicVolume;
	CProgressUI* m_progressSpeakerOutLevel;
	CProgressUI* m_progressMicInLevel;
};

class CSDKVideoSettingsUIGroup : public CSDKVideoSettingsUIEvent
{
public:
	CSDKVideoSettingsUIGroup();
	virtual ~CSDKVideoSettingsUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_);
	void UninitWindow();
	void GetVideoSettingsFlags();
	void Show();
	void Hide();
	bool IsVisable()
	{
		if (m_settingsVideoPage)
		{
			return m_settingsVideoPage->IsVisible();
		}
		return false;
	}
	void Notify( TNotifyUI& msg);

	void DoVideoMirrorEffectChkClick();
	void DoFaceBeautyEffectChkClick();
	void DoHDVideoChkClick();
	void DoAlwaysShowNameOnVideoChkClick();
	void DoAutoTurnOffVideoWhenJoinMeetingChkClick();
	void DoAlwaysUse16v9ChkClick();
	void DoOriginalSizeChkClick();
	void DoSpotlightSelfChkClick();
	void DoHardwareEncodeChkClick();
	void Do49VideoesInGallaryViewChkClick();
	void DoHideNoVideoUsersOnWallViewChkClick();
	void UpdateCameraList();
	void SetVideoPreviewParentWnd();
	void StartTestVideo();
	void StopTestVideo();
	void DoTestVideoRotate();

	virtual void OnNoVideoDeviceIsUseful();
	virtual void OnSelectedVideoDeviceIsChanged(); 
	virtual void OnNoWindowToShowPreview();
	virtual void OnComputerCamDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo*>* pNewCameraList);
	virtual void onDefaultCamDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) {}
private:
	CSDKVideoSettingsWorkFlow m_videoSettingsWorkFlow;
	CVerticalLayoutUI* m_settingsVideoPage;
	CSDKSettingsUIMgr* m_parentFrame;
	ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo*>* m_lstTestCamera;
	ZOOM_SDK_NAMESPACE::ICameraInfo* m_pCameraInfo;
	CListLabelElementUI* m_pCameraListElement;
	CComboUI* m_comboTestCamera;
	CCheckBoxUI* m_chkVideoMirrorEffect;
	CCheckBoxUI* m_chkFaceBeautyEffect;
	CCheckBoxUI* m_chkHDVideo;
	CCheckBoxUI* m_chkAlwaysShowNameOnVideo;
	CCheckBoxUI* m_chkAutoTurnOffVideoWhenJoinMeeting;
	CCheckBoxUI* m_chkAlwaysUse16v9;
	CCheckBoxUI* m_chkOriginalSize;
	CCheckBoxUI* m_chkSpotlightSelf;
	CCheckBoxUI* m_chkHardwareEncode;
	CCheckBoxUI* m_chk49VideoesInGallaryView;
	CCheckBoxUI* m_chkHideNoVideoUsersOnWallView;
	CButtonUI* m_btnTestVideoRotate;
	HWND hwnd;
};

class CSDKVBGImageList
{
public:
	CSDKVBGImageList();
	virtual ~CSDKVBGImageList();
public:
	int GetCount();
	ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* GetItem(unsigned int index);
	void AddItem(ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* elem);
	ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* GetImageInfoByName(std::wstring imageName);
	void RemoveItem(ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* elem);
	void ClearAll();
protected:
	std::vector<ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo*> m_pImageList;
};

class CSDKVirtualBGSettingsUIGroup : public CSDKVirtualBGUIEvent
{
public:
	CSDKVirtualBGSettingsUIGroup();
	virtual ~CSDKVirtualBGSettingsUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_);
	void UninitWindow();
	void GetVirtualBGSettingsFlags();

	virtual void onVBImageDidDownloaded();
	virtual void onGreenVBDidUpdateWithReplaceColor(DWORD selectedColor);
	virtual void onSelectedVBImageChanged();

	void Show();
	void Hide();
	bool IsVisable()
	{
		if (m_settingsVBGPage)
		{
			return m_settingsVBGPage->IsVisible();
		}
		return false;
	}
	void Notify( TNotifyUI&  msg);

	void DoAddImageBtnClick();
	void DoRemoveImageBtnClick();
	void DoPickColorBtnClick();
	void DoHasVirtualBGChkClick();
	void SetVideoPreviewParentWnd();
	void StartTestVideo();
	void StopTestVideo();

	void UpdateListUI();
	void GetImageList();
protected:
	void UseSelectedImageAsVBG();
private:
	CVerticalLayoutUI* m_settingsVBGPage;
	CSDKVirtualBGSettingsWorkFlow m_vbgSettingsWorkFlow;
	CSDKSettingsUIMgr* m_parentFrame;
	CButtonUI* m_btnAddImage;
	CButtonUI* m_btnRemoveImage;
	CButtonUI* m_btnPickColor;
	DWORD	m_dwPickedColor;
	bool	m_bCanUncheckGreenBG;
	CCheckBoxUI* m_chkVbgHasGreenBackground;
	HWND	m_hPreviewWnd;
	CSDKVBGImageList* m_pVBGImageList;
	CListUI* m_pImageListUI;
};

class CSDKRecordingSettingsUIGroup
{
public:
	CSDKRecordingSettingsUIGroup();
	virtual ~CSDKRecordingSettingsUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_);
	void UninitWindow();
	
	void GetRecrodingSettingsFlags();
	
	void Show();
	void Hide();
	bool IsVisable()
	{
		if (m_settingsRecordingPage)
		{
			return m_settingsRecordingPage->IsVisible();
		}
		return false;
	}
	void Notify( TNotifyUI&  msg);

	void DoOpenBtnClick();
	void DoChangeSaveLocationBtnClick();
	void ShowSaveLocation();
	
	void DoGetRecordingManagementURLBtnClick();
	void DoSelectRecordFileLocationAfterMeetingChkClick();
	void DoMultiAudioStreamRecordChkClick();
	void DoAddTimestampWatermarkChkClick();
	void DoOptimizeForThirdpartyVideoEditorChkClick();
	void DoShowVideoThumbnailWhenShareChkClick();
	void DoPlaceVideoNextToShareInRecordChkClick();
	
private:
	CVerticalLayoutUI* m_settingsRecordingPage;
	CSDKRecordingSettingsWorkFlow m_recordingSettingsWorkFlow;
	CSDKSettingsUIMgr* m_parentFrame;
	CButtonUI* m_btnOpen;
	CButtonUI* m_btnChangeSaveLocation;
	
	CButtonUI* m_btnGetRecordingManagementURL;
	const wchar_t* m_pGetRecordingManagementURL;
	CCheckBoxUI* m_chkSelectRecordFileLocationAfterMeeting;
	CCheckBoxUI* m_chkMultiAudioStreamRecord;
	CCheckBoxUI* m_chkAddTimestampWatermark;
	CCheckBoxUI* m_chkOptimizeForThirdpartyVideoEditor;
	CCheckBoxUI* m_chkShowVideoThumbnailWhenShare;
	CCheckBoxUI* m_chkPlaceVideoNextToShareInRecord;
	
	CLabelUI* m_labRecordingFileAddress;
	const wchar_t* m_pGetRecordingPath;
};
class CSDKUICustomSettingsUIGroup
{
public:
	CSDKUICustomSettingsUIGroup();
	virtual ~CSDKUICustomSettingsUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_);
	void UninitWindow();
	void Show();
	void Hide();
	bool IsVisable()
	{
		if (m_settingsUICustomPage)
		{
			return m_settingsUICustomPage->IsVisible();
		}
		return false;
	}
	void Notify( TNotifyUI&  msg);
	void SetUICustomSettingsFlags();
	void SwitchToUICustomPage(SettingsUICustom_page nPage);
	void SetUICustomCurrentPage(CVerticalLayoutUI* current_) {m_UICustomCurrentPage = current_;}
    void ShowMeetingWindowPage();
	void ShowSharePage();
	void ShowJoinMeetingPage();
	void ShowInvitePage();
	void ShowOthersPage();

	void DoBottomToolbarChkClick();
	void DoTitlebarMeetingIDChkClick();
	void DoAlwaysDisplayTitleMeetingIDChkClick();
	void DoLeaveMeetingButtonChkClick();
	void DoEnterOrExitTheFullScreenButtonsChkClick();
	void DoAlwaysDisplayTaskbarIconChkClick();
	void DoToolTipChkClick();
	void DoChatAndMenuChkClick();
	void DoRecordAndMenuChkClick();
	void DoInviteButtonChkClick();
	void DoSharingToolbarChkClick();
	void DoFloatingVideoWindowChkClick();
	void DoAirplayInstructionWindowChkClick();
	void DoShareComputerSoundChkClick();
	void DoOptimizeForFullScreenVideoClipChkClick();
	void DoSwitchToSingleParticipantShareDlgChkClick();
	void DoFloatingSharingToolbarChkClick();
	void DoGreenFrameWhenSharingChkClick();
	void DoApproveRemoteControlDlgChkClick();
	void DoDeclineRemoteControlResponseDlgChkClick();
	void DoMeetingWrongPswDlgChkClick();
	void DoWaitingForHostDlgChkClick();
	void DoInputMeetingPswDlgChkClick();
	void DoInputMeetingScreenNameDlgChkClick();
	void DoSelectJoinAudioDlgChkClick();
	void DoPhoneCallTabChkClick();
	void DoCallMeTabChkClick();
	void DoInviteByEmailTabChkClick();
	void DoInviteByPhoneTabChkClick();
	void DoInviteARoomSystemTabChkClick();
	void DoDialInSubTabChkClick();
	void DoCallOutSubTabChkClick();
	void DoUpgradeFreeMeetingButtonChkClick();
	void DoRemainingMeetingTimeButtonChkClick();
	void DoSettingDlgTopmostAttributeChkClick();
	void DoFullPhoneNumberChkClick();
	void DoReactionChkClick();
	void DoMeetingInfoChkClick();
protected:
	CVerticalLayoutUI* m_UICustomCurrentPage;
	CVerticalLayoutUI* m_settingsUICustomPage;
	CVerticalLayoutUI* m_UICustomMeetingWindowPage;
	CVerticalLayoutUI* m_UICustomSharePage;
	CVerticalLayoutUI* m_UICustomJoinMeetingPage;
	CVerticalLayoutUI* m_UICustomInvitePage;
	CVerticalLayoutUI* m_UICustomOthersPage;
	CSDKUICustomSettingsWorkFlow m_UICustomSettingsWorkFlow;
	CSDKSettingsUIMgr* m_parentFrame;
	COptionUI* m_btnMeetingWindow;
	COptionUI* m_btnShare;
	COptionUI* m_btnJoinMeeting;
	COptionUI* m_btnInvite;
	COptionUI* m_btnOthers;
	CCheckBoxUI* m_chkBottomToolbar;
	CCheckBoxUI* m_chkTitlebarMeetingID;
	CCheckBoxUI* m_chkAlwaysDisplayTitleMeetingID;
	CCheckBoxUI* m_chkLeaveMeetingButton;
	CCheckBoxUI* m_chkEnterOrExitTheFullScreenButtons;
	CCheckBoxUI* m_chkAlwaysDisplayTaskbarIcon;
	CCheckBoxUI* m_chkToolTip;
	CCheckBoxUI* m_chkChatAndMenu;
	CCheckBoxUI* m_chkRecordAndMenu;
	CCheckBoxUI* m_chkInviteButton;
	CCheckBoxUI* m_chkSharingToolbar;
	CCheckBoxUI* m_chkFloatingVideoWindow;
	CCheckBoxUI* m_chkAirplayInstructionWindow;
	CCheckBoxUI* m_chkShareComputerSoundChkbox;
	CCheckBoxUI* m_chkOptimizeForFullScreenVideoClipChkbox;
	CCheckBoxUI* m_chkSwitchToSingleParticipantShareDlg;
	CCheckBoxUI* m_chkFloatingSharingToolbar;
	CCheckBoxUI* m_chkGreenFrameWhenSharing;
	CCheckBoxUI* m_chkApproveRemoteControlDlg;
	CCheckBoxUI* m_chkDeclineRemoteControlResponseDlg;
	CCheckBoxUI* m_chkMeetingWrongPswDlg;
	CCheckBoxUI* m_chkWaitingForHostDlg;
	CCheckBoxUI* m_chkInputMeetingPswDlg;
	CCheckBoxUI* m_chkInputMeetingScreenNameDlg;
	CCheckBoxUI* m_chkSelectJoinAudioDlg;
	CCheckBoxUI* m_chkPhoneCallTab;
	CCheckBoxUI* m_chkCallMeTab;
	CCheckBoxUI* m_chkInviteByEmailTab;
	CCheckBoxUI* m_chkInviteByPhoneTab;
	CCheckBoxUI* m_chkInviteARoomSystemTab;
	CCheckBoxUI* m_chkDialInSubTab;
	CCheckBoxUI* m_chkCallOutSubTab;
	CCheckBoxUI* m_chkUpgradeFreeMeetingButton;
	CCheckBoxUI* m_chkRemainingMeetingTimeButton;
	CCheckBoxUI* m_chkSettingDlgTopmostAttribute;
	CCheckBoxUI* m_chkFullPhoneNumber;
	CCheckBoxUI* m_chkReaction;
	CCheckBoxUI* m_chkMeetingInfo;
};
class CSDKFeatureCustomSettingsUIGroup
{
public:
	CSDKFeatureCustomSettingsUIGroup();
	virtual ~CSDKFeatureCustomSettingsUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_);
	void UninitWindow();
	void Show();
	void Hide();
	bool IsVisable()
	{
		if (m_settingsFeatureCustomPage)
		{
			return m_settingsFeatureCustomPage->IsVisible();
		}
		return false;
	}
	void Notify(TNotifyUI& msg);
	void SetFeatureCustomSettingsFlags();
	void SwitchToFeatureCustomPage(SettingsFeatureCustom_page nPage);
	void SetFeatureCustomCurrentPage(CVerticalLayoutUI* current_) {m_FeatureCustomCurrentPage = current_;}
	void ShowMeetingWindowPage();
	void ShowSharePage();
	void ShowAudioPage();
	void ShowVideoPage();
	void ShowOtherFunctionsPage();

	void DoBackToMeetingBtnClick();
	void DoConfirmMoveFloatingVideoWndPosBtnClick();
	void DoConfirmMeetingWndPosBtnClick();
	void DoConfirmSharingFloatingVideoWndPosBtnClick();
	void DoConfirmMeetingIDBtnClick();
	void DoConfirmVideoWallModeBtnClick();
	void DoCurrentSpeakerModeBtnClick();
	void DoSwitchToPreviousPageBtnClick();
	void DoSwitchToNextPageBtnClick();
	void DoDoubleClick4SwitchFullScreenModeChkClick();
	void DoGrabShareWithoutPromptChkClick();
	void DoShareIOSDeviceChkClick();
	void DoShareWhiteBoardChkClick();
	void DoMultiShareChkClick();
	void DoRemoteControlCopyAndPasteChkClick();
	void DoAutoAdjustSpeakerVolumeChkClick();
	void DoAutoAdjustMicVolumeChkClick();
	void DoForceToEnableVideoWhenJoinChkClick();
	void DoForceToTurnOffVideoWhenJoinChkClick();
	void DoParticipantsListChkClick();
	void DoChatDialogChkClick();
	void DoClaimHostChkClick();
	void DoSplitScreenAbilityChkClick();
	void DoSwitchSplitScreenChkClick();
	void DoEnterFullScreenForFirstViewChkClick();
	void DoEnterFullScreenForSecondViewChkClick();
	void DoExitFullScreenForFirstViewChkClick();
	void DoExitFullScreenForSecondViewChkClick();
	void DoAutoEndOtherMeetingWhenStartMeetingChkClick();
	void DoConfirmPreSetInformationBtnClick();
private:
	CVerticalLayoutUI* m_FeatureCustomCurrentPage;
	CVerticalLayoutUI* m_settingsFeatureCustomPage;
	CVerticalLayoutUI* m_FeatureCustomMeetingWindowPage;
	CVerticalLayoutUI* m_FeatureCustomSharePage;
	CVerticalLayoutUI* m_FeatureCustomAudioPage;
	CVerticalLayoutUI* m_FeatureCustomVideoPage;
	CVerticalLayoutUI* m_FeatureCustomOtherFunctionsPage;
	CSDKFeatureCustomSettingsWorkFlow m_FeatureCustomSettingsWorkFlow;
	CSDKSettingsUIMgr* m_parentFrame;
	COptionUI* m_btnMeetingWindow;
	COptionUI* m_btnShare;
	COptionUI* m_btnAudio;
	COptionUI* m_btnVideo;
	COptionUI* m_btnOtherFunctions;
	CRichEditUI* m_editMeetingWndLeft;
	CRichEditUI* m_editMeetingWndTop;
	CRichEditUI* m_editSharingMeetingWndLeft;
	CRichEditUI* m_editSharingMeetingWndTop;
	CRichEditUI* m_editSetMeetingID;
	CRichEditUI* m_editFloatingVideoWndLeft;
	CRichEditUI* m_editFloatingVideoWndTop;
	CRichEditUI* m_editPreSetEmail;
	CRichEditUI* m_editPreSetUsername;
	CButtonUI* m_btnBackToMeeting;
	CButtonUI* m_btnConfirmMeetingWndPos;
	CButtonUI* m_btnConfirmSharingFloatingVideoWndPos;
	CButtonUI* m_btnConfirmMeetingID;
	CButtonUI* m_btnConfirmMoveFloatingVideoWndPos;
	CButtonUI* m_btnConfirmVideoWallMode;
	CButtonUI* m_btnCurrentSpeakerMode;
	CButtonUI* m_btnSwitchToPreviousPage;
	CButtonUI* m_btnSwitchToNextPage;
	CButtonUI* m_btnConfirmPreSetInformation;
	CCheckBoxUI* m_chkDoubleClick4SwitchFullScreenMode;
	CCheckBoxUI* m_chkGrabShareWithoutPrompt;
	CCheckBoxUI* m_chkShareIOSDevice;
	CCheckBoxUI* m_chkShareWhiteBoard;
	CCheckBoxUI* m_chkMultiShare;
	CCheckBoxUI* m_chkRemoteControlCopyAndPaste;
	CCheckBoxUI* m_chkAutoAdjustSpeakerVolume;
	CCheckBoxUI* m_chkAutoAdjustMicVolume;
	CCheckBoxUI* m_chkForceToEnableVideoWhenJoin;
	CCheckBoxUI* m_chkForceToTurnOffVideoWhenJoin;
	CCheckBoxUI* m_chkParticipantsList;
	CCheckBoxUI* m_chkChatDialog;
	CCheckBoxUI* m_chkClaimHost;
	CCheckBoxUI* m_chkSplitScreenAbility;
	CCheckBoxUI* m_chkSwitchToSplitScreen;
	CCheckBoxUI* m_chkEnterFullScreenForFirstView;
	CCheckBoxUI* m_chkEnterFullScreenForSecondView;
	CCheckBoxUI* m_chkExitFullScreenForFirstView;
	CCheckBoxUI* m_chkExitFullScreenForSecondView;
	CCheckBoxUI* m_chkAutoEndOtherMeetingWhenStartMeeting;

};
class CSDKSettingsUIMgr:
	public CWindowWnd,
	public INotifyUI
{
public:
	CSDKSettingsUIMgr();
	virtual ~CSDKSettingsUIMgr();

public:
	virtual LPCTSTR  GetWindowClassName() const {  return  _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	virtual UINT   GetSkinRes()      {return IDXML_SETTINGSFRAME_UI;}
	UILIB_RESOURCETYPE GetResourceType() const {return UILIB_RESOURCE;}

	virtual void InitWindow();
	virtual void OnFinalMessage(HWND)  {}

	virtual void Notify( TNotifyUI& msg );
	virtual LRESULT  HandleMessage(UINT uMsg,WPARAM wParam,LPARAM IParam);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void SwitchToPage(SettingsUI_page nPage);
	void SetCurrentPage(CVerticalLayoutUI* current_) {m_currentPage = current_;}
	void ShowErrorMessage(const wchar_t* error_message);

protected:
	CPaintManagerUI m_PaintManager;
	CSDKGeneralSettingsUIGroup m_GeneralSettingsUIGroup;
	CSDKAudioSettingsUIGroup m_AudioSettingsUIGroup;
	CSDKVideoSettingsUIGroup m_VideoSettingsUIGroup;
	CSDKVirtualBGSettingsUIGroup m_virtualBGSettingUIGroup;
	CSDKRecordingSettingsUIGroup m_RecordingSettingsUIGroup;
	CSDKUICustomSettingsUIGroup m_UICustomSettingsUIGroup;
	CSDKFeatureCustomSettingsUIGroup m_FeatureCustomSettingsUIGroup;
	CVerticalLayoutUI* m_currentPage;

	COptionUI* m_btnGeneralSettings;
	COptionUI* m_btnAudioSettings;
	COptionUI* m_btnVideoSettings;
	COptionUI* m_btnVirtualBGSettings;
	COptionUI* m_btnRecordingSettings;
	COptionUI* m_btnUICustomSettings;
	COptionUI* m_btnFeatureCustomSettings;
	CVerticalLayoutUI* m_panel_tab_main;
	CVerticalLayoutUI* m_general_settings_page;
	CVerticalLayoutUI* m_audio_settings_page;
	CVerticalLayoutUI* m_video_settings_page;
	CVerticalLayoutUI* m_recording_settings_page;
	CVerticalLayoutUI* m_ui_custom_settings_page;
	CVerticalLayoutUI* m_feature_custom_settings_page;
	CVerticalLayoutUI* m_virtualBG_settings_page;

};