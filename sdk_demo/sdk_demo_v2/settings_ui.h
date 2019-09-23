#pragma once
#include "sdk_util.h"
#include "resource.h"
#include "UIlib.h"
#include "sdk_demo_app_common.h"
#include "SETTINGS_general_workflow.h"
#include "SETTINGS_audio_workflow.h"
#include "SETTINGS_video_workflow.h"
#include "SETTINGS_recording_workflow.h"
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
class CSDKRecordingSettingsUIGroup
{
public:
	CSDKRecordingSettingsUIGroup();
	virtual ~CSDKRecordingSettingsUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_);
	void UninitWindow();
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
private:
	CVerticalLayoutUI* m_settingsRecordingPage;
	CSDKRecordingSettingsWorkFlow m_recordingSettingsWorkFlow;
	CSDKSettingsUIMgr* m_parentFrame;
	CButtonUI* m_btnOpen;
	CButtonUI* m_btnChangeSaveLocation;
	CLabelUI* m_labRecordingFileAddress;
	const wchar_t* m_pGetRecordingPath;
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

protected:
	CPaintManagerUI m_PaintManager;
	CSDKGeneralSettingsUIGroup m_GeneralSettingsUIGroup;
	CSDKAudioSettingsUIGroup m_AudioSettingsUIGroup;
	CSDKVideoSettingsUIGroup m_VideoSettingsUIGroup;
	CSDKRecordingSettingsUIGroup m_RecordingSettingsUIGroup;
	CVerticalLayoutUI* m_currentPage;

	COptionUI* m_btnGeneralSettings;
	COptionUI* m_btnAudioSettings;
	COptionUI* m_btnVideoSettings;
	COptionUI* m_btnRecordingSettings;
	CVerticalLayoutUI* m_panel_tab_main;
	CVerticalLayoutUI* m_general_settings_page;
	CVerticalLayoutUI* m_audio_settings_page;
	CVerticalLayoutUI* m_video_settings_page;
	CVerticalLayoutUI* m_recording_settings_page;

};