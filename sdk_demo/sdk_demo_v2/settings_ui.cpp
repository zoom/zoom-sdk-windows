#include "stdafx.h"
#include "settings_ui.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///class CSDKGeneralSettingsUIGroup
CSDKGeneralSettingsUIGroup::CSDKGeneralSettingsUIGroup()
{
	m_settingsGeneralPage = NULL;
	m_parentFrame = NULL;
	m_chkDualScreenMode = NULL;
	m_chkAutoFullScreenVideoWhenJoinMeeting = NULL;
	m_chkAutoFullScreenVideoWhenViewShare = NULL;
	m_chkAutoFitToWindowWhenViewSharing = NULL;
	m_chkTurnOffAeroModeInSharing = NULL;
	m_chkSplitScreenMode = NULL;
}
CSDKGeneralSettingsUIGroup::~CSDKGeneralSettingsUIGroup()
{
	m_settingsGeneralPage = NULL;
	m_parentFrame = NULL;
	m_chkDualScreenMode = NULL;
	m_chkAutoFullScreenVideoWhenJoinMeeting = NULL;
	m_chkAutoFullScreenVideoWhenViewShare = NULL;
	m_chkAutoFitToWindowWhenViewSharing = NULL;
	m_chkTurnOffAeroModeInSharing = NULL;
	m_chkSplitScreenMode = NULL;
}
void CSDKGeneralSettingsUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_)
{
	m_settingsGeneralPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_General_Settings")));
	m_chkDualScreenMode = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_use_dual_screen")));
	m_chkAutoFullScreenVideoWhenJoinMeeting = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_full_screen_start_join_meeting")));
	m_chkAutoFullScreenVideoWhenViewShare = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_full_screen_when_sharing")));
	m_chkAutoFitToWindowWhenViewSharing = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_fit_window_when_sharing")));
	m_chkTurnOffAeroModeInSharing = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_use_aero_mode")));
	m_chkSplitScreenMode = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_use_split_screen_mode")));
	m_parentFrame = main_frame_;
	GetGeneralSettingsFlags();
}
void CSDKGeneralSettingsUIGroup::UninitWindow()
{
	m_generalSettingsWorkFlow.Cleanup();
}
void CSDKGeneralSettingsUIGroup::GetGeneralSettingsFlags()
{
	bool bChecked = false;
	bChecked = m_generalSettingsWorkFlow.IsDualScreenModeEnabled();
	if(m_chkDualScreenMode)
	{
		m_chkDualScreenMode->SetCheck(bChecked);
	}
	bChecked = m_generalSettingsWorkFlow.IsAeroModeInSharingTurnOff();
	if(m_chkTurnOffAeroModeInSharing)
	{
		m_chkTurnOffAeroModeInSharing->SetCheck(bChecked);
	}
	bChecked = m_generalSettingsWorkFlow.IsAutoFitToWindowWhenViewSharingEnabled();
	if(m_chkAutoFitToWindowWhenViewSharing)
	{
		m_chkAutoFitToWindowWhenViewSharing->SetCheck(bChecked);
	}
	bChecked = m_generalSettingsWorkFlow.IsAutoFullScreenVideoWhenJoinMeetingEnabled();
	if(m_chkAutoFullScreenVideoWhenJoinMeeting)
	{
		m_chkAutoFullScreenVideoWhenJoinMeeting->SetCheck(bChecked);
	}
	bChecked = m_generalSettingsWorkFlow.IsAutoFullScreenVideoWhenViewShareEnabled();
	if(m_chkAutoFullScreenVideoWhenViewShare)
	{
		m_chkAutoFullScreenVideoWhenViewShare->SetCheck(bChecked);
	}
	bChecked = m_generalSettingsWorkFlow.IsSplitScreenModeEnabled();
	if(m_chkSplitScreenMode)
	{
		m_chkSplitScreenMode->SetCheck(bChecked);
	}
}
void CSDKGeneralSettingsUIGroup::Show()
{
	if(m_settingsGeneralPage)
	{
		m_settingsGeneralPage->SetVisible(true);
		if(m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_settingsGeneralPage);
		}
	}
}
void CSDKGeneralSettingsUIGroup::Hide()
{
	if(m_settingsGeneralPage)
	{
		m_settingsGeneralPage->SetVisible(false);
	}
}
void CSDKGeneralSettingsUIGroup::Notify(TNotifyUI & msg)
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_chkDualScreenMode)
		{
			DoDualScreenModeChkClick();
		}
		else if(msg.pSender == m_chkTurnOffAeroModeInSharing)
		{
			DoTurnOffAeroModeInSharingChkClick();
		}
		else if(msg.pSender == m_chkAutoFitToWindowWhenViewSharing)
		{
			DoAutoFitToWindowWhenViewSharingChkClik();
		}
		else if(msg.pSender == m_chkAutoFullScreenVideoWhenJoinMeeting)
		{
			DoAutoFullScreenVideoWhenJoinMeetingChkClick();
		}
		else if(msg.pSender == m_chkAutoFullScreenVideoWhenViewShare)
		{
			DoAutoFullScreenVideoWhenViewShareChkClick();
		}
		else if(msg.pSender == m_chkSplitScreenMode)
		{
			DoSplitScreenModeChkClick();
		}
	}
}
void CSDKGeneralSettingsUIGroup::DoDualScreenModeChkClick()
{
	if(NULL == m_chkDualScreenMode)
		return;
	bool bChecked = !m_chkDualScreenMode->GetCheck();
	m_generalSettingsWorkFlow.EnableDualScreenMode(bChecked);
}
void CSDKGeneralSettingsUIGroup::DoTurnOffAeroModeInSharingChkClick()
{
	if(NULL == m_chkTurnOffAeroModeInSharing)
		return;
	bool bChecked = !m_chkTurnOffAeroModeInSharing->GetCheck();
	m_generalSettingsWorkFlow.TurnOffAeroModeInSharing(bChecked);
}
void CSDKGeneralSettingsUIGroup::DoAutoFitToWindowWhenViewSharingChkClik()
{
	if(NULL == m_chkAutoFitToWindowWhenViewSharing)
		return;
	bool bChecked = !m_chkAutoFitToWindowWhenViewSharing->GetCheck();
	m_generalSettingsWorkFlow.EnableAutoFitToWindowWhenViewSharing(bChecked);
}
void CSDKGeneralSettingsUIGroup::DoAutoFullScreenVideoWhenJoinMeetingChkClick()
{
	if(NULL == m_chkAutoFullScreenVideoWhenJoinMeeting)
		return;
	bool bChecked = !m_chkAutoFullScreenVideoWhenJoinMeeting->GetCheck();
	m_generalSettingsWorkFlow.EnableAutoFullScreenVideoWhenJoinMeeting(bChecked);
}
void CSDKGeneralSettingsUIGroup::DoAutoFullScreenVideoWhenViewShareChkClick()
{
	if(NULL == m_chkAutoFullScreenVideoWhenViewShare)
		return;
	bool bChecked = !m_chkAutoFullScreenVideoWhenViewShare->GetCheck();
	m_generalSettingsWorkFlow.EnableAutoFullScreenVideoWhenViewShare(bChecked);
}
void CSDKGeneralSettingsUIGroup::DoSplitScreenModeChkClick()
{
	if(NULL == m_chkSplitScreenMode)
		return;
	bool bChecked = !m_chkSplitScreenMode->GetCheck();
	m_generalSettingsWorkFlow.EnableSplitScreenMode(bChecked);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///class  CSDKAudioSettingsUIGroup
CSDKAudioSettingsUIGroup::CSDKAudioSettingsUIGroup()
{
	m_lstTestSpeaker = NULL;
	m_lstTestMic = NULL;
	m_pSpeakerInfo = NULL;
	m_pMicInfo = NULL;
	m_pSpeakerListElement = NULL;
	m_pMicListElement = NULL;
	m_settingsAudioPage = NULL;
	m_parentFrame = NULL;
	m_chkAutoJoinAudio = NULL;
	m_chkAutoAdjustMic = NULL;
	m_chkStereoAudio = NULL;
	m_chkMicOriginalInput = NULL;
	m_chkHoldSpaceKeyToSpeak = NULL;
	m_chkAlwaysMuteMicWhenJoinVoip = NULL;
	m_chkSuppressAudioNotify = NULL;
	m_comboTestSpeaker = NULL;
	m_comboTestMic = NULL;
	m_btnTestSpeaker = NULL;
	m_btnStopSpeaker = NULL;
	m_btnTestMic = NULL;
	m_btnRecordingMic = NULL;
	m_btnPlayingMic = NULL;
	m_sldSpeakerVolume = NULL;
	m_sldMicVolume = NULL;
	m_progressSpeakerOutLevel = NULL;
	m_progressMicInLevel = NULL;
}
CSDKAudioSettingsUIGroup::~CSDKAudioSettingsUIGroup()
{
	m_lstTestSpeaker = NULL;
	m_lstTestMic = NULL;
	m_pSpeakerInfo = NULL;
	m_pMicInfo = NULL;
	m_pSpeakerListElement = NULL;
	m_pMicListElement = NULL;
	m_settingsAudioPage = NULL;
	m_parentFrame = NULL;
	m_chkAutoJoinAudio = NULL;
	m_chkAutoAdjustMic = NULL;
	m_chkStereoAudio = NULL;
	m_chkMicOriginalInput = NULL;
	m_chkHoldSpaceKeyToSpeak = NULL;
	m_chkAlwaysMuteMicWhenJoinVoip = NULL;
	m_chkSuppressAudioNotify = NULL;
	m_comboTestSpeaker = NULL;
	m_comboTestMic = NULL;
	m_btnTestSpeaker = NULL;
	m_btnStopSpeaker = NULL;
	m_btnTestMic = NULL;
	m_btnRecordingMic = NULL;
	m_btnPlayingMic = NULL;
	m_sldSpeakerVolume = NULL;
	m_sldMicVolume = NULL;
	m_progressSpeakerOutLevel = NULL;
	m_progressMicInLevel = NULL;
}
void CSDKAudioSettingsUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_)
{
	m_settingsAudioPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_Audio_Settings")));
	m_chkAutoJoinAudio = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_auto_join_audio")));
	m_chkAutoAdjustMic = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_auto_adjust_mic")));
	m_chkStereoAudio = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_stereo_audio")));
	m_chkMicOriginalInput = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_mic_original_input")));
	m_chkHoldSpaceKeyToSpeak = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_hold_Space_key_to_speak")));
	m_chkAlwaysMuteMicWhenJoinVoip = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_mute_mic_when_join_voip")));
	m_chkSuppressAudioNotify = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_suppress_audio_notify")));
	m_comboTestSpeaker = static_cast<CComboUI*>(ui_mgr.FindControl(_T("combo_test_speaker")));
	m_comboTestMic = static_cast<CComboUI*>(ui_mgr.FindControl(_T("combo_test_mic")));
	m_btnTestSpeaker = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_test_speaker")));
	m_btnStopSpeaker = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_stop")));
	m_btnTestMic = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_test_mic")));
	m_btnRecordingMic = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_recording")));
	m_btnPlayingMic = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_playing")));
	m_sldSpeakerVolume = static_cast<CSliderUI*>(ui_mgr.FindControl(_T("slider_speaker_volume")));
	m_sldMicVolume = static_cast<CSliderUI*>(ui_mgr.FindControl(_T("slider_mic_volume")));
	m_progressSpeakerOutLevel = static_cast<CProgressUI*>(ui_mgr.FindControl(_T("progress_speaker_output_level")));
	m_progressMicInLevel = static_cast<CProgressUI*>(ui_mgr.FindControl(_T("progress_mic_input_level")));
	m_parentFrame = main_frame_;
	GetAudioSettingsFlags();
	m_audioSettingsWorkFlow.SetUIEvent(this);
}
void CSDKAudioSettingsUIGroup::GetAudioSettingsFlags()
{
	FLOAT value;
	m_audioSettingsWorkFlow.GetSpeakerVol(value);
	if(m_sldSpeakerVolume)
	{
		m_sldSpeakerVolume->SetValue(static_cast<int>(value));
	}
	m_audioSettingsWorkFlow.GetMicVol(value);
	if(m_sldMicVolume)
	{
		m_sldMicVolume->SetValue(static_cast<int>(value));
	}
    
	bool bChecked = false;
	bChecked = m_audioSettingsWorkFlow.IsAutoJoinAudioEnabled();
	if(m_chkAutoJoinAudio)
	{
		m_chkAutoJoinAudio->SetCheck(bChecked);
	}
	bChecked = m_audioSettingsWorkFlow.IsStereoAudioEnable();
	if(m_chkStereoAudio)
	{
		m_chkStereoAudio->SetCheck(bChecked);
	}
	bChecked = m_audioSettingsWorkFlow.IsMicOriginalInputEnable();
	if(m_chkMicOriginalInput)
	{
		m_chkMicOriginalInput->SetCheck(bChecked);
	}
	bChecked = m_audioSettingsWorkFlow.IsHoldSpaceKeyToSpeakEnabled();
	if(m_chkHoldSpaceKeyToSpeak)
	{
		m_chkHoldSpaceKeyToSpeak->SetCheck(bChecked);
	}
	bChecked = m_audioSettingsWorkFlow.IsAlwaysMuteMicWhenJoinVoipEnabled();
	if(m_chkAlwaysMuteMicWhenJoinVoip)
	{
		m_chkAlwaysMuteMicWhenJoinVoip->SetCheck(bChecked);
	}
	bChecked = m_audioSettingsWorkFlow.IsSuppressAudioNotifyEnabled();
	if(m_chkSuppressAudioNotify)
	{
		m_chkSuppressAudioNotify->SetCheck(bChecked);
	}
	bChecked = m_audioSettingsWorkFlow.IsAutoAdjustMicEnabled();
	if(m_chkAutoAdjustMic)
	{
		m_chkAutoAdjustMic->SetCheck(bChecked);
	}
	if(m_sldMicVolume)
	{
		m_sldMicVolume->SetEnabled(!bChecked);
	}
}
void CSDKAudioSettingsUIGroup::UpdateSpeakerList()
{
	if (NULL == m_comboTestSpeaker)
		return;

	int select_index = 0;
	m_comboTestSpeaker->RemoveAll();
	m_lstTestSpeaker = m_audioSettingsWorkFlow.GetSpeakerList();
	if(!m_lstTestSpeaker)
	{
		return;
	}
	else
	{
		int count = m_lstTestSpeaker->GetCount();
		for(int index=0;index<count;index++)
		{
			m_pSpeakerListElement = new CListLabelElementUI;
			if (NULL == m_pSpeakerListElement)
				continue;

			m_comboTestSpeaker->AddAt(m_pSpeakerListElement, index);
			m_pSpeakerInfo = m_lstTestSpeaker->GetItem(index);
			if (NULL == m_pSpeakerInfo)
				continue;

			const wchar_t* device_name = m_pSpeakerInfo->GetDeviceName();
			if (device_name)
				m_pSpeakerListElement->SetText(device_name);
			if (m_pSpeakerInfo->IsSelectedDevice())
			{
				select_index = index;
			}
		}
	}
	m_comboTestSpeaker->SelectItem(select_index, true, true);
}
void CSDKAudioSettingsUIGroup::UpdateMicList()
{
	if (NULL == m_comboTestMic)
		return;

	int select_index = 0;
	m_comboTestMic->RemoveAll();
	m_lstTestMic = m_audioSettingsWorkFlow.GetMicList();
	if(!m_lstTestMic)
	{
		return;
	}
	else
	{
		int count = m_lstTestMic->GetCount();
		for(int index=0;index<count;index++)
		{
			m_pMicListElement = new CListLabelElementUI;
			m_comboTestMic->AddAt(m_pMicListElement, index);
			m_pMicInfo= m_lstTestMic->GetItem(index);
			if (NULL == m_pMicInfo)
				continue;

			const wchar_t* device_name = m_pMicInfo->GetDeviceName();
			if (device_name)
			{
				m_pMicListElement->SetText(device_name);
			}
			if (m_pMicInfo->IsSelectedDevice())
			{
				select_index = index;
			}
		}
	}
	m_comboTestMic->SelectItem(select_index, true, true);
}
void CSDKAudioSettingsUIGroup::UninitWindow()
{
	m_audioSettingsWorkFlow.SetUIEvent(NULL);
	m_audioSettingsWorkFlow.Cleanup();
	StopAudioTest();
}
void CSDKAudioSettingsUIGroup::Show()
{
	if(m_settingsAudioPage)
	{
		m_settingsAudioPage->SetVisible(true);
		if(m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_settingsAudioPage);
		}
	}
	UpdateSpeakerList();
	UpdateMicList();
}
void CSDKAudioSettingsUIGroup::Hide()
{
	if(m_settingsAudioPage)
	{
		m_settingsAudioPage->SetVisible(false);
	}
	StopAudioTest();
}
void CSDKAudioSettingsUIGroup::Notify(TNotifyUI& msg)
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnTestSpeaker)
		{
			DoPlayingMicButtonClick();
			DoTestSpeakerButtonClick();
		}
		else if(msg.pSender == m_btnStopSpeaker)
		{
			DoStopSpeakerButtonClick();
		}
		else if(msg.pSender == m_btnTestMic)
		{
			DoStopSpeakerButtonClick();
			DoTestMicButtonClick();
		}
		else if(msg.pSender == m_btnRecordingMic)
		{
			DoRecordingMicButtonClick();
		}
		else if(msg.pSender == m_btnPlayingMic)
		{
			DoPlayingMicButtonClick();
		}
		else if(msg.pSender == m_pSpeakerListElement)
		{
			DoStopSpeakerButtonClick();
		}
		else if(msg.pSender == m_chkAutoJoinAudio)
		{
			DoAutoJoinAudioChkClick();
		}
		else if(msg.pSender == m_chkAutoAdjustMic)
		{
			DoAutoAdjustMicChkClick();
		}
		else if(msg.pSender == m_chkStereoAudio)
		{
			DoStereoAudioChkClick();
		}
		else if(msg.pSender == m_chkMicOriginalInput)
		{
			DoMicOriginalInputChkClick();
		}
		else if(msg.pSender == m_chkHoldSpaceKeyToSpeak)
		{
			DoHoldSpaceKeyToSpeakChkClick();
		}
		else if(msg.pSender == m_chkAlwaysMuteMicWhenJoinVoip)
		{
			DoAlwaysMuteMicWhenJoinVoipChkClick();
		}
		else if(msg.pSender == m_chkSuppressAudioNotify)
		{
			DoSuppressAudioNotifyChkClick();
		}
	}
	else if(msg.sType == _T("valuechanged"))
	{
		if(msg.pSender == m_sldSpeakerVolume)
		{
			DoSetSpeakerVol();
		}
		if(msg.pSender == m_sldMicVolume)
		{
			DoSetMicVol();
		}
	}
	else if(msg.sType == _T("itemselect"))
	{
		if(msg.pSender == m_comboTestSpeaker)
		{
			StopAudioTest();
			SelectSpeaker();
		}
		else if(msg.pSender == m_comboTestMic)
		{
			StopAudioTest();
			SelectMic();
		}
	}
}
const wchar_t* CSDKAudioSettingsUIGroup::SelectSpeaker()
{
	if(NULL == m_comboTestSpeaker)
		return NULL;
	int index = m_comboTestSpeaker->GetCurSel();
	m_lstTestSpeaker = m_audioSettingsWorkFlow.GetSpeakerList();
	if(NULL == m_lstTestSpeaker)
		return NULL;
	if(index < 0)
	{
		return NULL;
	}
	else
	{
		m_pSpeakerInfo = m_lstTestSpeaker->GetItem(index);
		if(NULL == m_pSpeakerInfo)
			return NULL;
		const wchar_t* deviceId = m_pSpeakerInfo->GetDeviceId();
		const wchar_t* deviceName = m_pSpeakerInfo->GetDeviceName();
		if(deviceId && deviceName)
		{
			m_audioSettingsWorkFlow.SelectSpeaker(deviceId,deviceName);
		}
		return deviceId;
	}	
}
const wchar_t* CSDKAudioSettingsUIGroup::SelectMic()
{
	if(NULL == m_comboTestMic)
		return NULL;
	int index = m_comboTestMic->GetCurSel();
	m_lstTestMic = m_audioSettingsWorkFlow.GetMicList();
	if(NULL == m_lstTestMic)
		return NULL;
	if(index<0)
	{
		return NULL;
	}
	else
	{
		m_pMicInfo = m_lstTestMic->GetItem(index);
		if(NULL == m_pMicInfo)
			return NULL;
		const wchar_t* deviceId = m_pMicInfo->GetDeviceId();
		const wchar_t* deviceName = m_pMicInfo->GetDeviceName();
		if(deviceId && deviceName)
		{
			m_audioSettingsWorkFlow.SelectMic(deviceId,deviceName);
		}
		return deviceId;
	}
}
void CSDKAudioSettingsUIGroup::DoSetSpeakerVol()
{
	if(NULL == m_sldSpeakerVolume)
		return;
	float volume = static_cast<float>(m_sldSpeakerVolume->GetValue());
	m_audioSettingsWorkFlow.SetSpeakerVol(volume);
}
void CSDKAudioSettingsUIGroup::DoSetMicVol()
{
	if(NULL == m_sldMicVolume)
		return;
	float volume = static_cast<float>(m_sldMicVolume->GetValue());
	m_audioSettingsWorkFlow.SetMicVol(volume);
}
void CSDKAudioSettingsUIGroup::UpdateUI(settingsAudioTestingType type)
{
	RECT rc;
	switch(type)
	{
	case audio_speaker_test:
		if(m_btnTestSpeaker && m_btnStopSpeaker)
		{
			rc = m_btnTestSpeaker->GetRelativePos();
			m_btnTestSpeaker->SetVisible(false);
			m_btnStopSpeaker->SetPos(rc);
			m_btnStopSpeaker->SetVisible(true);
		}
		break;
	case audio_speaker_stop:
		if(m_btnTestSpeaker && m_btnStopSpeaker && m_btnStopSpeaker->IsVisible())
		{
			rc = m_btnStopSpeaker->GetRelativePos();
			m_btnStopSpeaker->SetVisible(false);
			m_btnTestSpeaker->SetPos(rc);
			m_btnTestSpeaker->SetVisible(true);
		}
		break;
	case audio_mic_test:
		if(m_btnRecordingMic && m_btnTestMic && m_btnTestMic->IsVisible())
		{
			rc = m_btnTestMic->GetRelativePos();
			m_btnTestMic->SetVisible(false);
			m_btnRecordingMic->SetPos(rc);
			m_btnRecordingMic->SetVisible(true);
		}
		break;
	case audio_mic_recording:
		if(m_btnPlayingMic && m_btnRecordingMic && m_btnRecordingMic->IsVisible())
		{
			rc = m_btnRecordingMic->GetRelativePos();
			m_btnRecordingMic->SetVisible(false);
			m_btnPlayingMic->SetPos(rc);
			m_btnPlayingMic->SetVisible(true);
		}
		break;
	case audio_mic_playing:
		if(m_btnTestMic)
		{
			if(m_btnPlayingMic && m_btnPlayingMic->IsVisible())
				{
					rc = m_btnPlayingMic->GetRelativePos();
					m_btnPlayingMic->SetVisible(false);
					m_btnTestMic->SetPos(rc);
					m_btnTestMic->SetVisible(true);
				}
			else if(m_btnRecordingMic && m_btnRecordingMic->IsVisible())
				{
					rc = m_btnRecordingMic->GetRelativePos();
					m_btnRecordingMic->SetVisible(false);
					m_btnTestMic->SetPos(rc);
					m_btnTestMic->SetVisible(true);
				}
		}
		break;		
	}
}
void CSDKAudioSettingsUIGroup::DoTestSpeakerButtonClick()
{
	const wchar_t* deviceId = SelectSpeaker();
	m_audioSettingsWorkFlow.TestSpeakerStartPlaying(deviceId);
	UpdateUI(audio_speaker_test);
}
void CSDKAudioSettingsUIGroup::DoStopSpeakerButtonClick()
{
	m_audioSettingsWorkFlow.TestSpeakerStopPlaying();
	UpdateUI(audio_speaker_stop);
}
void CSDKAudioSettingsUIGroup::DoTestMicButtonClick()
{
	const wchar_t* deviceId = SelectMic();
	m_audioSettingsWorkFlow.TestMicStartRecording(deviceId);
	UpdateUI(audio_mic_test);
}
void CSDKAudioSettingsUIGroup::DoRecordingMicButtonClick()
{
	m_audioSettingsWorkFlow.TestMicPlayRecording();
	UpdateUI(audio_mic_recording);
}
void CSDKAudioSettingsUIGroup::DoPlayingMicButtonClick()
{
	m_audioSettingsWorkFlow.TestMicStopTesting();
	UpdateUI(audio_mic_playing);
}
void CSDKAudioSettingsUIGroup::StopAudioTest()
{
	DoStopSpeakerButtonClick();
	DoPlayingMicButtonClick();
}
void CSDKAudioSettingsUIGroup::DoAutoJoinAudioChkClick()
{
	if(NULL == m_chkAutoJoinAudio)
		return;
	bool bChecked = !m_chkAutoJoinAudio->GetCheck();
	m_audioSettingsWorkFlow.EnableAutoJoinAudio(bChecked);
}
void CSDKAudioSettingsUIGroup::DoAutoAdjustMicChkClick()
{
	if(NULL == m_chkAutoAdjustMic || NULL == m_sldMicVolume)
		return;
	bool bChecked = !m_chkAutoAdjustMic->GetCheck();
	m_sldMicVolume->SetEnabled(!bChecked);
	m_audioSettingsWorkFlow.EnableAutoAdjustMic(bChecked);
}
void CSDKAudioSettingsUIGroup::DoStereoAudioChkClick()
{
	if(NULL == m_chkStereoAudio)
		return;
	bool bChecked = !m_chkStereoAudio->GetCheck();
	m_audioSettingsWorkFlow.EnableStereoAudio(bChecked);
}
void CSDKAudioSettingsUIGroup::DoMicOriginalInputChkClick()
{
	if(NULL == m_chkMicOriginalInput)
		return;
	bool bChecked = !m_chkMicOriginalInput->GetCheck();
	m_audioSettingsWorkFlow.EnableMicOriginalInput(bChecked);
}
void CSDKAudioSettingsUIGroup::DoHoldSpaceKeyToSpeakChkClick()
{
	if(NULL == m_chkHoldSpaceKeyToSpeak)
		return;
	bool bChecked = !m_chkHoldSpaceKeyToSpeak->GetCheck();
	m_audioSettingsWorkFlow.EnableHoldSpaceKeyToSpeak(bChecked);
}
void CSDKAudioSettingsUIGroup::DoAlwaysMuteMicWhenJoinVoipChkClick()
{
	if(NULL == m_chkAlwaysMuteMicWhenJoinVoip)
		return;
	bool bChecked = !m_chkAlwaysMuteMicWhenJoinVoip->GetCheck();
	m_audioSettingsWorkFlow.EnableAlwaysMuteMicWhenJoinVoip(bChecked);
}
void CSDKAudioSettingsUIGroup::DoSuppressAudioNotifyChkClick()
{
	if(NULL == m_chkSuppressAudioNotify)
		return;
	bool bChecked = !m_chkSuppressAudioNotify->GetCheck();
	m_audioSettingsWorkFlow.EnableSuppressAudioNotify(bChecked);
}
void CSDKAudioSettingsUIGroup::OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume)
{
	wchar_t sMicVol[16];
	_itow_s(MicVolume, sMicVol, 10);
	int  micvolume = _wtoi(sMicVol);
	if(m_progressMicInLevel)
	{
		m_progressMicInLevel->SetValue(micvolume);
	}
	wchar_t sSpkVol[16];
	_itow_s(SpkVolume, sSpkVol, 10);
	int  spkvolume = _wtoi(sSpkVol);
	if(m_progressSpeakerOutLevel)
	{
		m_progressSpeakerOutLevel->SetValue(spkvolume);
	}
}
void CSDKAudioSettingsUIGroup::OnNoAudioDeviceIsUseful(bool bMicOrSpk)
{
	TCHAR szLog[MAX_PATH] = { 0 };
	wstring info;
	if(bMicOrSpk)
	{
		info = _T("No mic is found!");
		wsprintf(szLog, _T("no mice is found\n"));
	}
	else
	{
		info = _T("No speaker is found!");
		wsprintf(szLog, _T("No speaker is found!\n"));
	}
	OutputDebugString(szLog);
}
void CSDKAudioSettingsUIGroup::OnTestMicStatusChanged(ZOOM_SDK_NAMESPACE::SDK_TESTMIC_STATUS status,bool& bHandled)
{
	switch (status)
	{
	case ZOOM_SDK_NAMESPACE::enuCanTest:
		{
			if(NULL == m_btnTestMic)
				return;
			if(!m_btnTestMic->IsVisible())
			{
				UpdateUI(audio_mic_playing);
			}
		}
		break;
	case ZOOM_SDK_NAMESPACE::enuCanPlay:
		{
			DoRecordingMicButtonClick();			
		}
		break;
	case ZOOM_SDK_NAMESPACE::enuMicRecording:
		{
			::MessageBox(NULL, L"Now you can play the recorded sound! or stop testing!", L"error", MB_OK);
		}
	default:
		break;
	}
	bHandled = true;
}
void CSDKAudioSettingsUIGroup::OnSelectedAudioDeviceIsChanged()
{
	FLOAT volume;
	m_audioSettingsWorkFlow.GetSpeakerVol(volume);
	m_sldSpeakerVolume->SetValue(static_cast<int>(volume));
	m_audioSettingsWorkFlow.GetMicVol(volume);
	m_sldMicVolume->SetValue(static_cast<int>(volume));
}
void CSDKAudioSettingsUIGroup::OnComputerMicDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IMicInfo*>* pNewMicList)
{
	DoPlayingMicButtonClick();
	UpdateMicList();
}
void CSDKAudioSettingsUIGroup::OnComputerSpeakerDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ISpeakerInfo*>* pNewSpeakerList)
{
	DoStopSpeakerButtonClick();
	UpdateSpeakerList();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///class CSDKVideoSettingsUIGroup
CSDKVideoSettingsUIGroup::CSDKVideoSettingsUIGroup()
{
	m_settingsVideoPage = NULL;
	m_parentFrame = NULL;
	m_lstTestCamera = NULL;
	m_pCameraInfo = NULL;
	m_pCameraListElement = NULL;
	m_comboTestCamera = NULL;
	m_chkVideoMirrorEffect = NULL; 
	m_chkFaceBeautyEffect = NULL;
	m_chkHDVideo = NULL;
	m_chkAlwaysShowNameOnVideo = NULL;
	m_chkAutoTurnOffVideoWhenJoinMeeting = NULL;
	m_chkAlwaysUse16v9 = NULL;
	m_chkOriginalSize = NULL;
	m_chkSpotlightSelf = NULL;
	m_chkHardwareEncode = NULL;
	m_chk49VideoesInGallaryView = NULL;
	m_chkHideNoVideoUsersOnWallView = NULL;
	m_btnTestVideoRotate = NULL;
	hwnd  = NULL;	
}
CSDKVideoSettingsUIGroup::~CSDKVideoSettingsUIGroup()
{
	m_settingsVideoPage = NULL;
	m_parentFrame = NULL;
	m_lstTestCamera = NULL;
	m_pCameraInfo = NULL;
	m_pCameraListElement = NULL;
	m_comboTestCamera = NULL;
	m_chkVideoMirrorEffect = NULL; 
	m_chkFaceBeautyEffect = NULL;
	m_chkHDVideo = NULL;
	m_chkAlwaysShowNameOnVideo = NULL;
	m_chkAutoTurnOffVideoWhenJoinMeeting = NULL;
	m_chkAlwaysUse16v9 = NULL;
	m_chkOriginalSize = NULL;
	m_chkSpotlightSelf = NULL;
	m_chkHardwareEncode = NULL;
	m_chk49VideoesInGallaryView = NULL;
	m_chkHideNoVideoUsersOnWallView = NULL;
	m_btnTestVideoRotate = NULL;
	hwnd  = NULL;	
}
void CSDKVideoSettingsUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_)
{
	m_settingsVideoPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_Video_Settings")));
	m_comboTestCamera = static_cast<CComboUI*>(ui_mgr.FindControl(_T("combo_test_camera")));
	m_chkVideoMirrorEffect = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_video_mirror_effect")));
	m_chkFaceBeautyEffect = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_face_beauty_effect")));
	m_chkHDVideo = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_HD_video")));
	m_chkAlwaysShowNameOnVideo = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_always_show_name_on_video")));
	m_chkAutoTurnOffVideoWhenJoinMeeting = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_auto_turn_off_video_when_join")));
	m_chkAlwaysUse16v9 = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_16v9_video_mode")));
	m_chkOriginalSize = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_original_size")));
	m_chkSpotlightSelf = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_spotlight_self")));
	m_chkHardwareEncode = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_hardware_encode")));
	m_chk49VideoesInGallaryView = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_49videoes_in_gallary_view")));
	m_chkHideNoVideoUsersOnWallView = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_hide_no_video_users_on_wall_view")));
	m_btnTestVideoRotate = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_test_video_rotate")));
	m_parentFrame = main_frame_;
	hwnd = ui_mgr.GetPaintWindow();
	GetVideoSettingsFlags();
	m_videoSettingsWorkFlow.SetUIEvent(this);
}
void CSDKVideoSettingsUIGroup::UninitWindow()
{
	m_videoSettingsWorkFlow.SetUIEvent(NULL);
	m_videoSettingsWorkFlow.Cleanup();
	StopTestVideo();
}
void CSDKVideoSettingsUIGroup::GetVideoSettingsFlags()
{
	bool bChecked = false;
	bChecked = m_videoSettingsWorkFlow.IsVideoMirrorEffectEnabled();
	if(m_chkVideoMirrorEffect)
	{
		m_chkVideoMirrorEffect->SetCheck(bChecked);
	}
	bChecked = m_videoSettingsWorkFlow.IsFaceBeautyEffectEnabled();
	if(m_chkFaceBeautyEffect)
	{
		m_chkFaceBeautyEffect->SetCheck(bChecked);
	}
	bChecked = m_videoSettingsWorkFlow.IsAlwaysShowNameOnVideoEnabled();
	if(m_chkAlwaysShowNameOnVideo)
	{
		m_chkAlwaysShowNameOnVideo->SetCheck(bChecked);
	}
	bChecked = m_videoSettingsWorkFlow.IsAutoTurnOffVideoWhenJoinMeetingEnabled();
	if(m_chkAutoTurnOffVideoWhenJoinMeeting)
	{
		m_chkAutoTurnOffVideoWhenJoinMeeting->SetCheck(bChecked);
	}
	bChecked = m_videoSettingsWorkFlow.IsAlwaysUse16v9();
	if(m_chkAlwaysUse16v9)
	{
		m_chkAlwaysUse16v9->SetCheck(bChecked);
	}
	if(m_chkOriginalSize)
	{
		m_chkOriginalSize->SetCheck(!bChecked);
	}
	bChecked = m_videoSettingsWorkFlow.IsSpotlightSelfEnabled();
	if(m_chkSpotlightSelf)
	{
		m_chkSpotlightSelf->SetCheck(bChecked);
	}
	bChecked = m_videoSettingsWorkFlow.IsHardwareEncodeEnabled();
	if(m_chkHardwareEncode)
	{
		m_chkHardwareEncode->SetCheck(bChecked);
	}
	bChecked = m_videoSettingsWorkFlow.Is49VideoesInGallaryViewEnabled();
	if(m_chk49VideoesInGallaryView)
	{
		m_chk49VideoesInGallaryView->SetCheck(bChecked);
	}
	bChecked = m_videoSettingsWorkFlow.IsHideNoVideoUsersOnWallViewEnabled();
	if(m_chkHideNoVideoUsersOnWallView)
	{
		m_chkHideNoVideoUsersOnWallView->SetCheck(bChecked);
	}
	bChecked = m_videoSettingsWorkFlow.IsHDVideoEnabled();
	if(m_chkHDVideo)
	{
		m_chkHDVideo->SetCheck(bChecked);
	}
}
void CSDKVideoSettingsUIGroup::Show()
{
	if(m_settingsVideoPage)
	{
		m_settingsVideoPage->SetVisible(true);
		if(m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_settingsVideoPage);
		}
	}
	UpdateCameraList();
	SetVideoPreviewParentWnd();
	StartTestVideo();
}
void CSDKVideoSettingsUIGroup::Hide()
{
	if(m_settingsVideoPage)
	{
		m_settingsVideoPage->SetVisible(false);
	}
	StopTestVideo();
}
void CSDKVideoSettingsUIGroup::Notify(TNotifyUI& msg)
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_chkVideoMirrorEffect)
		{
			DoVideoMirrorEffectChkClick();
		}
		else if(msg.pSender == m_chkFaceBeautyEffect)
		{
			DoFaceBeautyEffectChkClick();
		}
		else if(msg.pSender == m_chkHDVideo)
		{
			DoHDVideoChkClick();
		}
		else if(msg.pSender == m_chkAlwaysShowNameOnVideo)
		{
			DoAlwaysShowNameOnVideoChkClick();
		}
		else if(msg.pSender == m_chkAutoTurnOffVideoWhenJoinMeeting)
		{
			DoAutoTurnOffVideoWhenJoinMeetingChkClick();
		}
		else if(msg.pSender == m_chkAlwaysUse16v9)
		{
			DoAlwaysUse16v9ChkClick();
		}
		else if(msg.pSender == m_chkOriginalSize)
		{
			DoOriginalSizeChkClick();
		}
		else if(msg.pSender == m_chkSpotlightSelf)
		{
			DoSpotlightSelfChkClick();
		}
		else if(msg.pSender == m_chkHardwareEncode)
		{
			DoHardwareEncodeChkClick();
		}
		else if(msg.pSender == m_chk49VideoesInGallaryView)
		{
			Do49VideoesInGallaryViewChkClick();
		}
		else if(msg.pSender == m_chkHideNoVideoUsersOnWallView)
		{
			DoHideNoVideoUsersOnWallViewChkClick();
		}
		else if(msg.pSender == m_btnTestVideoRotate)
		{
			DoTestVideoRotate();
		}
	}
	else if(msg.sType == _T("itemselect"))
	{
		if(msg.pSender == m_comboTestCamera)
		{
			StopTestVideo();
			StartTestVideo();
		}
	}
}
void CSDKVideoSettingsUIGroup::UpdateCameraList()
{
	if (NULL == m_comboTestCamera)
		return;

	int select_index = 0;
	m_comboTestCamera->RemoveAll();
	m_lstTestCamera = m_videoSettingsWorkFlow.GetCameraList();
	if(!m_lstTestCamera)
	{
		return;
	}
	else
	{
		int count = m_lstTestCamera->GetCount();
		for(int index=0;index<count;index++)
		{
			m_pCameraListElement = new CListLabelElementUI;
			if (NULL == m_pCameraListElement)
				continue;

			m_comboTestCamera->Add(m_pCameraListElement);
			m_pCameraInfo = m_lstTestCamera->GetItem(index);
			if (NULL == m_pCameraInfo)
				continue;

			const wchar_t* device_name = m_pCameraInfo->GetDeviceName();
			if (device_name)
				m_pCameraListElement->SetText(device_name);
			if (m_pCameraInfo->IsSelectedDevice())
			{
				select_index = index;
			}
		}
	}
	m_comboTestCamera->SelectItem(select_index);
}
void CSDKVideoSettingsUIGroup::DoVideoMirrorEffectChkClick()
{
	if(NULL == m_chkVideoMirrorEffect)
		return;
	bool bChecked = !m_chkVideoMirrorEffect->GetCheck();
	m_videoSettingsWorkFlow.EnableVideoMirrorEffect(bChecked);
}
void CSDKVideoSettingsUIGroup::DoFaceBeautyEffectChkClick()
{
	if(NULL == m_chkFaceBeautyEffect)
		return;
	bool bChecked = !m_chkFaceBeautyEffect->GetCheck();
	m_videoSettingsWorkFlow.EnableFaceBeautyEffect(bChecked);
}
void CSDKVideoSettingsUIGroup::DoHDVideoChkClick()
{
	if(NULL == m_chkHDVideo || NULL == m_chkAlwaysUse16v9)
		return;
	bool bChecked = !m_chkHDVideo->GetCheck();
	if(bChecked)
	{
		m_chkAlwaysUse16v9->SetCheck(bChecked);
		DoAlwaysUse16v9ChkClick();
	}
	m_videoSettingsWorkFlow.EnableHDVideo(bChecked);
}
void CSDKVideoSettingsUIGroup::DoAlwaysShowNameOnVideoChkClick()
{
	if(NULL == m_chkAlwaysShowNameOnVideo)
		return;
	bool bChecked = !m_chkAlwaysShowNameOnVideo->GetCheck();
	m_videoSettingsWorkFlow.EnableAlwaysShowNameOnVideo(bChecked);
}
void CSDKVideoSettingsUIGroup::DoAutoTurnOffVideoWhenJoinMeetingChkClick()
{
	if(NULL == m_chkAutoTurnOffVideoWhenJoinMeeting)
		return;
	bool bChecked = !m_chkAutoTurnOffVideoWhenJoinMeeting->GetCheck();
	m_videoSettingsWorkFlow.EnableAutoTurnOffVideoWhenJoinMeeting(bChecked);
}
void CSDKVideoSettingsUIGroup::DoAlwaysUse16v9ChkClick()
{
	m_videoSettingsWorkFlow.EnableAlwaysUse16v9(true);
}
void CSDKVideoSettingsUIGroup::DoOriginalSizeChkClick()
{
	m_videoSettingsWorkFlow.EnableAlwaysUse16v9(false);
}
void CSDKVideoSettingsUIGroup::DoSpotlightSelfChkClick()
{
	if(NULL == m_chkSpotlightSelf)
		return;
	bool bChecked = !m_chkSpotlightSelf->GetCheck();
	m_videoSettingsWorkFlow.EnableSpotlightSelf(bChecked);
}
void CSDKVideoSettingsUIGroup::DoHardwareEncodeChkClick()
{
	if(NULL == m_chkHardwareEncode)
		return;
	bool bChecked = !m_chkHardwareEncode->GetCheck();
	m_videoSettingsWorkFlow.EnableHardwareEncode(bChecked);
}
void CSDKVideoSettingsUIGroup::Do49VideoesInGallaryViewChkClick()
{
	if(NULL == m_chk49VideoesInGallaryView)
		return;
	bool bChecked = !m_chk49VideoesInGallaryView->GetCheck();
	m_videoSettingsWorkFlow.Enable49VideoesInGallaryView(bChecked);
}
void CSDKVideoSettingsUIGroup::DoHideNoVideoUsersOnWallViewChkClick()
{
	if(NULL == m_chkHideNoVideoUsersOnWallView)
		return;
	bool bChecked = !m_chkHideNoVideoUsersOnWallView->GetCheck();
	m_videoSettingsWorkFlow.EnableHideNoVideoUsersOnWallView(bChecked);
}
void CSDKVideoSettingsUIGroup::SetVideoPreviewParentWnd()
{
	RECT rc={155,0,635,270};
	m_videoSettingsWorkFlow.SetVideoPreviewParentWnd(hwnd,rc);
}
void CSDKVideoSettingsUIGroup::StartTestVideo()
{
	if(NULL == m_comboTestCamera)
		return;
	int index = m_comboTestCamera->GetCurSel();
	if(index<0)
	{
		m_videoSettingsWorkFlow.TestVideoStartPreview(NULL);
	}
	else
	{
		m_pCameraInfo = m_lstTestCamera->GetItem(index);
		if(NULL == m_pCameraInfo)
			return;
		const wchar_t* deviceId = m_pCameraInfo->GetDeviceId();
		if(deviceId)
		{
			m_videoSettingsWorkFlow.TestVideoStartPreview(deviceId);
		}
	}
}
void CSDKVideoSettingsUIGroup::StopTestVideo()
{
	m_videoSettingsWorkFlow.TestVideoStopPreview();
}
void CSDKVideoSettingsUIGroup::DoTestVideoRotate()
{
	m_videoSettingsWorkFlow.TestVideoRotate(ZOOM_SDK_NAMESPACE::PREVIEW_VIDEO_ROTATION_ACTION_CLOCK90);
}
void CSDKVideoSettingsUIGroup::OnSelectedVideoDeviceIsChanged()
{
	::MessageBox(NULL, _T("Video device is changed. All tests are stopped. Restart them mannully!"), L"error", MB_OK);
}
void CSDKVideoSettingsUIGroup::OnNoWindowToShowPreview()
{
	::MessageBox(NULL, _T("No Window is used to show video preview!"), L"error", MB_OK);
}
void CSDKVideoSettingsUIGroup::OnNoVideoDeviceIsUseful()
{
	::MessageBox(NULL, _T("No camera is found!"), L"error", MB_OK);
	UpdateCameraList();
}
void CSDKVideoSettingsUIGroup::OnComputerCamDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo *>* pNewCameraList)
{
	StopTestVideo();
	UpdateCameraList();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///class CSDKVRecordingSettingsUIGroup
CSDKRecordingSettingsUIGroup::CSDKRecordingSettingsUIGroup()
{
	m_settingsRecordingPage = NULL;
	m_parentFrame = NULL;
	m_btnOpen = NULL;
	m_btnChangeSaveLocation = NULL;
	m_labRecordingFileAddress = NULL;
	m_pGetRecordingPath = NULL;
}
CSDKRecordingSettingsUIGroup::~CSDKRecordingSettingsUIGroup()
{
	m_settingsRecordingPage = NULL;
	m_parentFrame = NULL;
	m_btnOpen = NULL;
	m_btnChangeSaveLocation = NULL;
	m_labRecordingFileAddress = NULL;
	m_pGetRecordingPath = NULL;
}
void CSDKRecordingSettingsUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_)
{
	m_settingsRecordingPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_Recording_Settings")));
	m_btnOpen = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_open")));
	m_btnChangeSaveLocation = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_change_save_location")));
	m_labRecordingFileAddress = static_cast<CLabelUI*>(ui_mgr.FindControl(_T("text_recording_file_address")));
	m_parentFrame = main_frame_;
	ShowSaveLocation();
}
void CSDKRecordingSettingsUIGroup::UninitWindow()
{
	m_recordingSettingsWorkFlow.Cleanup();
}
void CSDKRecordingSettingsUIGroup::Show()
{
	if(m_settingsRecordingPage)
	{
		m_settingsRecordingPage->SetVisible(true);
		if(m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_settingsRecordingPage);
		}
	}
}
void CSDKRecordingSettingsUIGroup::Hide()
{
	if(m_settingsRecordingPage)
	{
		m_settingsRecordingPage->SetVisible(false);
	}
}
void CSDKRecordingSettingsUIGroup::Notify(TNotifyUI& msg)
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnOpen)
		{
			DoOpenBtnClick();
		}
		else if(msg.pSender == m_btnChangeSaveLocation)
		{
			DoChangeSaveLocationBtnClick();
		}
	}
}
void CSDKRecordingSettingsUIGroup::ShowSaveLocation()
{
	m_pGetRecordingPath = m_recordingSettingsWorkFlow.GetRecordingPath();
	if(NULL == m_pGetRecordingPath)
		return;
	if(m_labRecordingFileAddress)
	{
		m_labRecordingFileAddress->SetText(m_pGetRecordingPath);
	}
}
void CSDKRecordingSettingsUIGroup::DoOpenBtnClick()
{
	if(m_pGetRecordingPath)
	{
		ShellExecute(NULL, _T("open"), m_pGetRecordingPath, _T(""), _T(""), SW_SHOW);
	}
}
void CSDKRecordingSettingsUIGroup::DoChangeSaveLocationBtnClick()
{
	if(NULL == m_btnChangeSaveLocation)
		return;
	TCHAR szBuffer[MAX_PATH] = {0};   
	BROWSEINFO bi;   
	ZeroMemory(&bi,sizeof(BROWSEINFO));   
	bi.hwndOwner = NULL;   
	bi.pszDisplayName = szBuffer;   
	bi.lpszTitle = _T("Select the folder directory from below:");   
	bi.ulFlags = BIF_RETURNFSANCESTORS;   
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);   
	if (NULL == idl)   
	{   
		return;   
	}   
	SHGetPathFromIDList(idl,szBuffer);   
	m_recordingSettingsWorkFlow.SetRecordingPath(szBuffer);
	ShowSaveLocation();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///class CSDKSettingsUIMgr
CSDKSettingsUIMgr::CSDKSettingsUIMgr()
{
	m_currentPage = NULL;
	m_btnGeneralSettings = NULL;
	m_btnAudioSettings = NULL;
	m_btnVideoSettings = NULL;
	m_btnRecordingSettings = NULL; 
	m_panel_tab_main = NULL;
	m_general_settings_page = NULL;
	m_audio_settings_page = NULL;
	m_video_settings_page = NULL;
	m_recording_settings_page = NULL;
}
CSDKSettingsUIMgr::~CSDKSettingsUIMgr()
{
	m_currentPage = NULL;
	m_btnGeneralSettings = NULL;
	m_btnAudioSettings = NULL;
	m_btnVideoSettings = NULL;
	m_btnRecordingSettings = NULL; 
	m_panel_tab_main = NULL;
	m_general_settings_page = NULL;
	m_audio_settings_page = NULL;
	m_video_settings_page = NULL;
	m_recording_settings_page = NULL;
}
void CSDKSettingsUIMgr::InitWindow()
{
	m_GeneralSettingsUIGroup.InitWindow(m_PaintManager,this);
	m_AudioSettingsUIGroup.InitWindow(m_PaintManager,this);
	m_VideoSettingsUIGroup.InitWindow(m_PaintManager,this);
	m_RecordingSettingsUIGroup.InitWindow(m_PaintManager,this);
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc)) return;
	rc.right = rc.left + 657;
	rc.bottom = rc.top + 654;
	if( !::AdjustWindowRectEx(&rc,GetWindowStyle(m_hWnd),(!(GetWindowStyle(m_hWnd) & WS_CHILD) && (::GetMenu(m_hWnd) != NULL)),GetWindowExStyle(m_hWnd)) ) return; 
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, NULL, (ScreenX - (rc.right - rc.left)) / 2, 
		(ScreenY - (rc.bottom - rc.top)) / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_SHOWWINDOW);

	m_panel_tab_main = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("panel_Tab_Main")));
	m_btnGeneralSettings = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("tabbtn_general_settings")));
	m_general_settings_page = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("panel_General_Settings")));
	m_btnAudioSettings = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("tabbtn_audio_settings")));
	m_audio_settings_page = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("panel_Audio_Settings")));
	m_btnVideoSettings = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("tabbtn_video_settings")));
	m_video_settings_page = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("panel_Video_Settings")));
	m_btnRecordingSettings = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("tabbtn_recording_settings")));
	m_recording_settings_page = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("panel_Recording_Settings")));
	m_currentPage = m_general_settings_page;

}
void CSDKSettingsUIMgr::Notify( TNotifyUI& msg )
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnGeneralSettings && m_currentPage != m_general_settings_page)
		{
			SwitchToPage(Setting_General_Page);
		}
		else if(msg.pSender == m_btnAudioSettings && m_currentPage != m_audio_settings_page)
		{
			SwitchToPage(Setting_Audio_Page);
		}
		else if(msg.pSender == m_btnVideoSettings && m_currentPage != m_video_settings_page)
		{
			SwitchToPage(Setting_Video_Page);
		}
		else if(msg.pSender == m_btnRecordingSettings && m_currentPage != m_recording_settings_page)
		{
			SwitchToPage(Setting_Recording_Page);
		}

		else if(m_currentPage == m_general_settings_page)
		{
			m_GeneralSettingsUIGroup.Notify(msg);
		}
		else if(m_currentPage == m_audio_settings_page)
		{
			m_AudioSettingsUIGroup.Notify(msg);
		}
		else if(m_currentPage == m_video_settings_page)
		{
			m_VideoSettingsUIGroup.Notify(msg);
		}
		else if(m_currentPage == m_recording_settings_page)
		{
			m_RecordingSettingsUIGroup.Notify(msg);
		}
	}
	else
	{
		m_GeneralSettingsUIGroup.Notify(msg);
		m_AudioSettingsUIGroup.Notify(msg);
		m_VideoSettingsUIGroup.Notify(msg);
		m_RecordingSettingsUIGroup.Notify(msg);
	}
}
LRESULT  CSDKSettingsUIMgr::HandleMessage(UINT uMsg,WPARAM wParam,LPARAM IParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	if( uMsg == WM_CREATE )
	{
		m_PaintManager.Init(m_hWnd);

		CDialogBuilder builder;
		STRINGorID xml(GetSkinRes());
		CControlUI* pRoot = builder.Create(xml,_T("xml"),0, &m_PaintManager);
		ASSERT(pRoot && "Failed to parse XML");

		m_PaintManager.AttachDialog(pRoot);
		m_PaintManager.AddNotifier(this);
		InitWindow(); 

		return lRes;
	}
	else if (uMsg == WM_CLOSE)
	{
		OnClose(uMsg, wParam, IParam, bHandled);		
	}
	else if (uMsg == WM_DESTROY)
	{
		OnDestroy(uMsg, wParam, IParam, bHandled);
		return lRes;
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, IParam, lRes) ) 
	{
		return lRes ;
	}

	return __super::HandleMessage(uMsg, wParam,IParam);
}
void CSDKSettingsUIMgr::SwitchToPage(SettingsUI_page nPage)
{
	if (m_GeneralSettingsUIGroup.IsVisable())
		m_GeneralSettingsUIGroup.Hide();
	if (m_AudioSettingsUIGroup.IsVisable())
		m_AudioSettingsUIGroup.Hide();
	if (m_VideoSettingsUIGroup.IsVisable())
		m_VideoSettingsUIGroup.Hide();
	if (m_RecordingSettingsUIGroup.IsVisable())
		m_RecordingSettingsUIGroup.Hide();
	switch(nPage)
	{
	case Setting_General_Page:
		m_GeneralSettingsUIGroup.Show();
		break;
	case Setting_Audio_Page:
		m_AudioSettingsUIGroup.Show();
		break;
	case Setting_Video_Page:
		m_VideoSettingsUIGroup.Show();
		break;
	case Setting_Recording_Page:
		m_RecordingSettingsUIGroup.Show();
		break;
	default:
		break;
	}
}
LRESULT  CSDKSettingsUIMgr::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 0;
}
LRESULT  CSDKSettingsUIMgr::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_GeneralSettingsUIGroup.UninitWindow();
	m_AudioSettingsUIGroup.UninitWindow();
	m_VideoSettingsUIGroup.UninitWindow();
	m_RecordingSettingsUIGroup.UninitWindow();
	return 0;
}