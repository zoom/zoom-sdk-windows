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
	
	m_chkUseDisplayReminderWindowWhenExit = NULL;
	m_chkShowMyMeetingElapseTime = NULL;
	m_chkAccelerateGPUWhenShare = NULL;
	m_chkEnableRomoteControllAllApplications = NULL;
	
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
	
	m_chkUseDisplayReminderWindowWhenExit = NULL;
	m_chkShowMyMeetingElapseTime = NULL;
	m_chkAccelerateGPUWhenShare = NULL;
	m_chkEnableRomoteControllAllApplications = NULL;
	
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
	
	m_chkUseDisplayReminderWindowWhenExit = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_use_display_reminder_window_when_exit")));
	m_chkShowMyMeetingElapseTime = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_show_my_meeting_elapse_time")));
	m_chkAccelerateGPUWhenShare = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_accelerate_GPU_when_share")));
	m_chkEnableRomoteControllAllApplications = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_enable_romote_controll_all_applications")));
	
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
	
	bChecked = m_generalSettingsWorkFlow.IsDisplayReminderWindowWhenExitEnabled();
	if(m_chkUseDisplayReminderWindowWhenExit)
	{
		m_chkUseDisplayReminderWindowWhenExit->SetCheck(bChecked);
	}
	bChecked = m_generalSettingsWorkFlow.IsShowMyMeetingElapseTimeEnabled();
	if(m_chkShowMyMeetingElapseTime)
	{
		m_chkShowMyMeetingElapseTime->SetCheck(bChecked);
	}
	
	bool testbool = false;
	bChecked = m_generalSettingsWorkFlow.IsAccelerateGPUWhenShareEnabled(testbool);
	if(m_chkAccelerateGPUWhenShare)
	{
		m_chkAccelerateGPUWhenShare->SetCheck(bChecked);
	}
	
	bChecked = m_generalSettingsWorkFlow.IsRemoteControlAllApplicationsEnabled();
	if(m_chkEnableRomoteControllAllApplications)
	{
		m_chkEnableRomoteControllAllApplications->SetCheck(bChecked);
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
		else if(msg.pSender == m_chkUseDisplayReminderWindowWhenExit)
		{
			DoDisplayReminderWindowWhenExitChkClick();
		}
		else if(msg.pSender == m_chkShowMyMeetingElapseTime)
		{
			DoShowMyMeetingElapseTimeChkClick();
		}
		else if(msg.pSender == m_chkAccelerateGPUWhenShare)
		{
			DoAccelerateGPUWhenShareChkClick();
		}
		else if(msg.pSender == m_chkEnableRomoteControllAllApplications)
		{
			DoRemoteControlAllApplicationsChkClick();
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

void CSDKGeneralSettingsUIGroup::DoDisplayReminderWindowWhenExitChkClick()
{
	if(NULL == m_chkUseDisplayReminderWindowWhenExit)
		return;
	bool bChecked = !m_chkUseDisplayReminderWindowWhenExit->GetCheck();
	m_generalSettingsWorkFlow.EnableDisplayReminderWindowWhenExit(bChecked);

}
void CSDKGeneralSettingsUIGroup::DoShowMyMeetingElapseTimeChkClick()
{
	if(NULL == m_chkShowMyMeetingElapseTime)
		return;
	bool bChecked = !m_chkShowMyMeetingElapseTime->GetCheck();
	m_generalSettingsWorkFlow.EnableShowMyMeetingElapseTime(bChecked);
}
void CSDKGeneralSettingsUIGroup::DoAccelerateGPUWhenShareChkClick()
{
	if(NULL == m_chkAccelerateGPUWhenShare)
		return;
	bool bChecked = !m_chkAccelerateGPUWhenShare->GetCheck();
	m_generalSettingsWorkFlow.EnableAccelerateGPUWhenShare(bChecked);
}
void CSDKGeneralSettingsUIGroup::DoRemoteControlAllApplicationsChkClick()
{
	if(NULL == m_chkEnableRomoteControllAllApplications)
		return;
	bool bChecked = !m_chkEnableRomoteControllAllApplications->GetCheck();
	m_generalSettingsWorkFlow.EnableRemoteControlAllApplications(bChecked);
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
	
	m_chkEchoCancellation = NULL;
	
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
	
	m_chkEchoCancellation = NULL;
	
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
	
	m_chkEchoCancellation = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_echo_cancellation")));
	
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
	bool bVisiableOfEcho = m_audioSettingsWorkFlow.IsMicOriginalInputEnable();
	bChecked = m_audioSettingsWorkFlow.IsEchoCancellationEnabled();
	if(m_chkEchoCancellation)
	{
		m_chkEchoCancellation->SetVisible(bVisiableOfEcho);
		m_chkEchoCancellation->SetCheck(bChecked);
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
		
		else if(msg.pSender == m_chkEchoCancellation)
		{
			DoEchoCancellationChkClick();
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
	
	if (bChecked)
	{
		m_chkEchoCancellation->SetVisible(true);
		bool bChked = m_audioSettingsWorkFlow.IsEchoCancellationEnabled();
		if(m_chkEchoCancellation)
		{
			m_chkEchoCancellation->SetCheck(bChked);
		}
	}
	else
	{
		m_chkEchoCancellation->SetVisible(false);
	}
	
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

void CSDKAudioSettingsUIGroup::DoEchoCancellationChkClick()
{
	if(NULL == m_chkEchoCancellation)
		return;
	bool bChecked = !m_chkEchoCancellation->GetCheck();
	m_audioSettingsWorkFlow.EnableEchoCancellation(bChecked);
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
	if(bMicOrSpk)
	{
		if(m_parentFrame)
		{
			m_parentFrame->ShowErrorMessage(_T("No mic is found!"));
		}
	}
	else
	{
		if(m_parentFrame)
		{
			m_parentFrame->ShowErrorMessage(_T("No speaker is found!"));
		}
	}
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
			if(m_parentFrame)
			{
				m_parentFrame->ShowErrorMessage(_T("Now you can play the recorded sound! or stop testing!"));
			}
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
	StopTestVideo();
	StartTestVideo();
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
	if(m_parentFrame)
	{
		m_parentFrame->ShowErrorMessage(_T("Video device is changed!"));
	}
}
void CSDKVideoSettingsUIGroup::OnNoWindowToShowPreview()
{
	if(m_parentFrame)
	{
		m_parentFrame->ShowErrorMessage(_T("No Window is used to show video preview!"));
	}
}
void CSDKVideoSettingsUIGroup::OnNoVideoDeviceIsUseful()
{
	if(m_parentFrame)
	{
		m_parentFrame->ShowErrorMessage(_T("No camera is found!"));
	}
	UpdateCameraList();
}
void CSDKVideoSettingsUIGroup::OnComputerCamDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo *>* pNewCameraList)
{
	StopTestVideo();
	UpdateCameraList();
}

//////////////////////////////////////////////////////////////////////////
///class CSDKVBGImageList
CSDKVBGImageList::CSDKVBGImageList()
{

}

CSDKVBGImageList::~CSDKVBGImageList()
{
	ClearAll();
}

int CSDKVBGImageList::GetCount()
{
	return m_pImageList.size();
}

ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* CSDKVBGImageList::GetItem( unsigned int index )
{
	if(index >= 0 && index < m_pImageList.size())
		return m_pImageList[index];
	else
		return NULL;
}

void CSDKVBGImageList::AddItem( ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* elem )
{
	if(m_pImageList.capacity() < m_pImageList.max_size())
	{
		if (NULL == elem)
			return;
		m_pImageList.push_back(elem);
	}
}

void CSDKVBGImageList::RemoveItem(ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* elem)
{
	if(NULL == elem)
		return;

	std::vector<ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo*>::iterator iter_ = m_pImageList.begin();
	for (;m_pImageList.end() != iter_; iter_++)
	{
		if ((*iter_) == elem)
		{
			m_pImageList.erase(iter_);
			return;
		}
	}
}

void CSDKVBGImageList::ClearAll()
{
	if(!m_pImageList.empty())
		m_pImageList.clear();
}


ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* CSDKVBGImageList::GetImageInfoByName( std::wstring imageName )
{
	int nCount = GetCount();
	for(int i = 0; i<nCount; ++i)
	{
		const wchar_t* image_name = m_pImageList[i]->GetImageName();
		if( StrCmpCW(imageName.c_str(), image_name) == 0)
			return m_pImageList[i];
	}
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///class CSDKVRecordingSettingsUIGroup
CSDKVirtualBGSettingsUIGroup::CSDKVirtualBGSettingsUIGroup()
{
	m_settingsVBGPage = NULL;
	m_parentFrame = NULL;
	m_btnAddImage = NULL;
	m_btnRemoveImage = NULL;
	m_btnPickColor = NULL;
	m_dwPickedColor = 0;
	m_chkVbgHasGreenBackground = NULL;
	m_hPreviewWnd = NULL;
	m_pImageListUI = NULL;
	m_pVBGImageList = NULL;
}

CSDKVirtualBGSettingsUIGroup::~CSDKVirtualBGSettingsUIGroup()
{
	m_settingsVBGPage = NULL;
	m_parentFrame = NULL;
	m_btnAddImage = NULL;
	m_btnRemoveImage = NULL;
	m_btnPickColor = NULL;
	m_dwPickedColor = 0;
	m_chkVbgHasGreenBackground = NULL;
	m_hPreviewWnd = NULL;
	
}

void CSDKVirtualBGSettingsUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_)
{
	m_parentFrame = main_frame_;
	m_settingsVBGPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_Virtual_background_Settings")));
	m_btnAddImage = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_AddImage")));
	m_btnRemoveImage = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_RemoveImage")));
	m_btnPickColor = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_PickColor")));
	m_pImageListUI = static_cast<CListUI* >(ui_mgr.FindControl(_T("lst_VBGImages")));
	m_chkVbgHasGreenBackground = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_have_green_background")));
	GetVirtualBGSettingsFlags();
	m_hPreviewWnd = ui_mgr.GetPaintWindow();
	if(m_pImageListUI)
	{
		m_pImageListUI->SetContextMenuUsed(false);
	}
}

void CSDKVirtualBGSettingsUIGroup::UninitWindow()
{
	if(m_pVBGImageList)
	{
		m_pVBGImageList->ClearAll();
		delete m_pVBGImageList;
		m_pVBGImageList = NULL;
	}

}

void CSDKVirtualBGSettingsUIGroup::UpdateListUI()
{
	if(!m_pImageListUI)
		return;
	if(NULL == m_pVBGImageList)
		m_pVBGImageList = new CSDKVBGImageList();
	else
		m_pVBGImageList->ClearAll();

	GetImageList();

	m_pImageListUI->RemoveAll();
	if (m_pVBGImageList)
	{
		int nCount = m_pVBGImageList->GetCount();
		for (int i=0; i<nCount; i++)
		{
			CDialogBuilder builder;
			STRINGorID xml(IDXML_MEETING_PARTICIPANT_LIST_UI);
			ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* pImageInfo = m_pVBGImageList->GetItem(i);
			if(pImageInfo == NULL) 
				continue;
			CListTextElementUI* pListElement = new CListTextElementUI;
			if(NULL == pListElement)
				continue;

			m_pImageListUI->Add(pListElement);
			std::wstring strName = pImageInfo->GetImageName();
			std::wstring strPath = pImageInfo->GetImageFilePath();
			if(strName == _T(""))
			{
				strName = _T("None");
				strPath = _T("No file is used");
			}
			pListElement->SetText(0, strName.c_str());// later can can add file path to the list. Wilmer: to do
			pListElement->SetText(1, strPath.c_str());
		}
	}
}

void CSDKVirtualBGSettingsUIGroup::GetImageList()
{
	ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* >* lst_Image = m_vbgSettingsWorkFlow.GetBGImageList();
	m_pVBGImageList->ClearAll();
	int nCount = lst_Image->GetCount();
	for(int i=0; i<nCount; i++)
	{
		ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* pItem = lst_Image->GetItem(i);
		if(NULL != pItem)
			m_pVBGImageList->AddItem(pItem);
	}
}

void CSDKVirtualBGSettingsUIGroup::GetVirtualBGSettingsFlags()
{
	m_bCanUncheckGreenBG = m_vbgSettingsWorkFlow.IsSupportSmartVirtualBG();
	bool bChecked = false;	
	bChecked = m_vbgSettingsWorkFlow.IsUsingGreenScreenOn();
	if(m_chkVbgHasGreenBackground)
	{
		m_chkVbgHasGreenBackground->SetCheck(bChecked);
	}
}

void CSDKVirtualBGSettingsUIGroup::Show()
{
	if(m_settingsVBGPage)
	{
		m_settingsVBGPage->SetVisible(true);
		if(m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_settingsVBGPage);
		}
	}
	UpdateListUI();
	StartTestVideo();
}

void CSDKVirtualBGSettingsUIGroup::SetVideoPreviewParentWnd()
{
	RECT rc={155,0,635,270};
	m_vbgSettingsWorkFlow.SetVideoPreviewParentWnd(m_hPreviewWnd,rc);
}
void CSDKVirtualBGSettingsUIGroup::Hide()
{
	if(m_settingsVBGPage)
	{
		m_settingsVBGPage->SetVisible(false);
	}
	StopTestVideo();
}
void CSDKVirtualBGSettingsUIGroup::Notify(TNotifyUI& msg)
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnAddImage)
		{
			DoAddImageBtnClick();
		}
		else if(msg.pSender == m_btnRemoveImage)
		{
			DoRemoveImageBtnClick();
		}
		else if(msg.pSender == m_btnPickColor)
		{
			DoPickColorBtnClick();
		}
		else if(msg.pSender == m_chkVbgHasGreenBackground)
		{
			DoHasVirtualBGChkClick();
		}
	}
	else if (msg.sType == _T("itemselect"))
	{
		if (msg.pSender == m_pImageListUI)
		{
			UseSelectedImageAsVBG();
		}
	}
}

void CSDKVirtualBGSettingsUIGroup::StartTestVideo()
{
	SetVideoPreviewParentWnd();
	m_vbgSettingsWorkFlow.TestVideoStartPreview(NULL);
}
void CSDKVirtualBGSettingsUIGroup::StopTestVideo()
{
	m_vbgSettingsWorkFlow.TestVideoStopPreview();
}

void CSDKVirtualBGSettingsUIGroup::DoAddImageBtnClick()
{
	//open select file dialog and select an image file, then pass the file path...
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH] = {0};

	// Initialize OPENFILENAME
	SecureZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_parentFrame->GetHWND();
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';

	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = _T("Picture files\0*.bmp;*.png;*.jpg;*.jpe;*.jpeg\0PNG(*.png)\0*.png\0JPEG(*.jpg; *.jpe; *.jpeg)\0*.jpg;*.jpe;*.jpeg\0BMP(*.bmp)\0*.bmp\0\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	std::wstring strTitle = _T("Choose a background image");
	ofn.lpstrTitle = strTitle.c_str();

	if (GetOpenFileName(&ofn))
	{
		if(wcsnlen_s(szFile, _countof(szFile)) > 0)
		{
			if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == m_vbgSettingsWorkFlow.AddBGImage(szFile))
				UpdateListUI();
		}
	}
}
void CSDKVirtualBGSettingsUIGroup::DoRemoveImageBtnClick()
{
	if(m_pVBGImageList && m_pImageListUI)
	{
		int index = m_pImageListUI->GetCurSel();
		if(0 == index)
			return;
		ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* pImageInfo = m_pVBGImageList->GetItem(index);
		if(pImageInfo)
		{
			m_vbgSettingsWorkFlow.RemoveBGImage(pImageInfo);
		}
	}
}
void CSDKVirtualBGSettingsUIGroup::DoPickColorBtnClick()
{
	m_vbgSettingsWorkFlow.BeginSelectReplaceVBColor();
}
void CSDKVirtualBGSettingsUIGroup::DoHasVirtualBGChkClick()
{
	if(NULL == m_chkVbgHasGreenBackground)
		return;
	bool old_status = m_chkVbgHasGreenBackground->GetCheck();
	if(m_bCanUncheckGreenBG)
	{
		//m_chkVbgHasGreenBackground->SetCheck(!old_status);
		m_vbgSettingsWorkFlow.SetUsingGreenScreen(!old_status);
	}
	else
	{
		m_chkVbgHasGreenBackground->SetCheck(old_status);
	}
}
void CSDKVirtualBGSettingsUIGroup::onVBImageDidDownloaded()
{
	//to do
}
void CSDKVirtualBGSettingsUIGroup::onGreenVBDidUpdateWithReplaceColor(DWORD selectedColor)
{
	//to do
	m_dwPickedColor = selectedColor;
}
void CSDKVirtualBGSettingsUIGroup::onSelectedVBImageChanged()
{
	//to do
}
void CSDKVirtualBGSettingsUIGroup::UseSelectedImageAsVBG()
{
	if(m_pImageListUI && m_pVBGImageList)
	{
		int index = m_pImageListUI->GetCurSel();
		ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* pImageInfo = m_pVBGImageList->GetItem(index);
		if(pImageInfo)
		{
			m_vbgSettingsWorkFlow.UseBGImage(pImageInfo);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///class CSDKVRecordingSettingsUIGroup
CSDKRecordingSettingsUIGroup::CSDKRecordingSettingsUIGroup()
{
	m_settingsRecordingPage = NULL;
	m_parentFrame = NULL;
	m_btnOpen = NULL;
	m_btnChangeSaveLocation = NULL;
	
	m_btnGetRecordingManagementURL = NULL;
	m_pGetRecordingManagementURL = NULL;
	m_chkSelectRecordFileLocationAfterMeeting = NULL;
	m_chkMultiAudioStreamRecord = NULL;
	m_chkAddTimestampWatermark = NULL;
	m_chkOptimizeForThirdpartyVideoEditor = NULL;
	m_chkShowVideoThumbnailWhenShare = NULL;
	m_chkPlaceVideoNextToShareInRecord = NULL;
	
	m_labRecordingFileAddress = NULL;
	m_pGetRecordingPath = NULL;
}
CSDKRecordingSettingsUIGroup::~CSDKRecordingSettingsUIGroup()
{
	m_settingsRecordingPage = NULL;
	m_parentFrame = NULL;
	m_btnOpen = NULL;
	m_btnChangeSaveLocation = NULL;
	
	m_btnGetRecordingManagementURL = NULL;
	m_pGetRecordingManagementURL = NULL;
	m_chkSelectRecordFileLocationAfterMeeting = NULL;
	m_chkMultiAudioStreamRecord = NULL;
	m_chkAddTimestampWatermark = NULL;
	m_chkOptimizeForThirdpartyVideoEditor = NULL;
	m_chkShowVideoThumbnailWhenShare = NULL;
	m_chkPlaceVideoNextToShareInRecord = NULL;
	
	m_labRecordingFileAddress = NULL;
	m_pGetRecordingPath = NULL;
}
void CSDKRecordingSettingsUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_)
{
	m_settingsRecordingPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_Recording_Settings")));
	m_btnOpen = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_open")));
	m_btnChangeSaveLocation = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_change_save_location")));
	m_labRecordingFileAddress = static_cast<CLabelUI*>(ui_mgr.FindControl(_T("text_recording_file_address")));
	
	m_btnGetRecordingManagementURL = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_cloud_recording")));
	m_chkSelectRecordFileLocationAfterMeeting = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_select_record_file_location_after_meeting")));
	m_chkMultiAudioStreamRecord = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_multi_audio_stream_record")));
	m_chkAddTimestampWatermark = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_add_timestamp_watermark")));
	m_chkOptimizeForThirdpartyVideoEditor = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_optimize_for_3rd_party_video_editor")));
	m_chkShowVideoThumbnailWhenShare = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_show_video_thumbnail_when_share")));
	m_chkPlaceVideoNextToShareInRecord = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_place_video_next_to_share_in_record")));
	
	m_parentFrame = main_frame_;
	
	GetRecrodingSettingsFlags();
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
		
		else if(msg.pSender == m_btnGetRecordingManagementURL)
		{
			DoGetRecordingManagementURLBtnClick();
		}
		else if(msg.pSender == m_chkSelectRecordFileLocationAfterMeeting)
		{
			DoSelectRecordFileLocationAfterMeetingChkClick();
		}
		else if(msg.pSender == m_chkMultiAudioStreamRecord)
		{
			DoMultiAudioStreamRecordChkClick();
		}
		else if(msg.pSender == m_chkAddTimestampWatermark)
		{
			DoAddTimestampWatermarkChkClick();
		}
		else if(msg.pSender == m_chkOptimizeForThirdpartyVideoEditor)
		{
			DoOptimizeForThirdpartyVideoEditorChkClick();
		}
		else if(msg.pSender == m_chkShowVideoThumbnailWhenShare)
		{
			DoShowVideoThumbnailWhenShareChkClick();
		}
		else if(msg.pSender == m_chkPlaceVideoNextToShareInRecord)
		{
			DoPlaceVideoNextToShareInRecordChkClick();
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
void CSDKRecordingSettingsUIGroup::DoGetRecordingManagementURLBtnClick()
{
	m_pGetRecordingManagementURL = m_recordingSettingsWorkFlow.GetRecordingManagementURL();
	if(m_pGetRecordingManagementURL)
	{
		ShellExecute(NULL, _T("open"), m_pGetRecordingManagementURL, _T(""), _T(""), SW_SHOW);
	}
}
void CSDKRecordingSettingsUIGroup::DoSelectRecordFileLocationAfterMeetingChkClick()
{
	if(NULL == m_chkSelectRecordFileLocationAfterMeeting)
		return;
	bool bChecked = !m_chkSelectRecordFileLocationAfterMeeting->GetCheck();
	m_recordingSettingsWorkFlow.EnableSelectRecordFileLocationAfterMeeting(bChecked);
}
void CSDKRecordingSettingsUIGroup::DoMultiAudioStreamRecordChkClick()
{
	if(NULL == m_chkMultiAudioStreamRecord)
		return;
	bool bChecked = !m_chkMultiAudioStreamRecord->GetCheck();
	m_recordingSettingsWorkFlow.EnableMultiAudioStreamRecord(bChecked);
}
void CSDKRecordingSettingsUIGroup::DoAddTimestampWatermarkChkClick()
{
	if(NULL == m_chkAddTimestampWatermark)
		return;
	bool bChecked = !m_chkAddTimestampWatermark->GetCheck();
	m_recordingSettingsWorkFlow.EnableAddTimestampWatermark(bChecked);
}
void CSDKRecordingSettingsUIGroup::DoOptimizeForThirdpartyVideoEditorChkClick()
{
	if(NULL == m_chkOptimizeForThirdpartyVideoEditor)
		return;
	bool bChecked = !m_chkOptimizeForThirdpartyVideoEditor->GetCheck();
	m_recordingSettingsWorkFlow.EnableOptimizeFor3rdPartyVideoEditor(bChecked);
}
void CSDKRecordingSettingsUIGroup::DoShowVideoThumbnailWhenShareChkClick()
{
	if(NULL == m_chkShowVideoThumbnailWhenShare)
		return;
	bool bChecked = !m_chkShowVideoThumbnailWhenShare->GetCheck();
	m_recordingSettingsWorkFlow.EnableShowVideoThumbnailWhenShare(bChecked);
	if (bChecked)
	{
		m_chkPlaceVideoNextToShareInRecord->SetVisible(true);
	}
	else
	{
		bool bChked = m_recordingSettingsWorkFlow.IsPlaceVideoNextToShareInRecordEnabled();
		if (bChked)
		{
			m_recordingSettingsWorkFlow.EnablePlaceVideoNextToShareInRecord(!bChked);
			m_chkPlaceVideoNextToShareInRecord->SetCheck(!bChked);
		}
		m_chkPlaceVideoNextToShareInRecord->SetVisible(false);
	}
}
void CSDKRecordingSettingsUIGroup::DoPlaceVideoNextToShareInRecordChkClick()
{
	if(NULL == m_chkPlaceVideoNextToShareInRecord)
		return;
	bool bChecked = !m_chkPlaceVideoNextToShareInRecord->GetCheck();
	m_recordingSettingsWorkFlow.EnablePlaceVideoNextToShareInRecord(bChecked);
}
void CSDKRecordingSettingsUIGroup::GetRecrodingSettingsFlags()
{
	bool bChecked = false;
	bChecked = m_recordingSettingsWorkFlow.IsMultiAudioStreamRecordEnabled();
	if(m_chkMultiAudioStreamRecord)
	{
		m_chkMultiAudioStreamRecord->SetCheck(bChecked);
	}
	bChecked = m_recordingSettingsWorkFlow.IsAddTimestampWatermarkEnabled();
	if(m_chkAddTimestampWatermark)
	{
		m_chkAddTimestampWatermark->SetCheck(bChecked);
	}
	bChecked = m_recordingSettingsWorkFlow.IsOptimizeFor3rdPartyVideoEditorEnabled();
	if(m_chkOptimizeForThirdpartyVideoEditor)
	{
		m_chkOptimizeForThirdpartyVideoEditor->SetCheck(bChecked);
	}
	bChecked = m_recordingSettingsWorkFlow.IsShowVideoThumbnailWhenShareEnabled();
	if(m_chkShowVideoThumbnailWhenShare)
	{
		m_chkShowVideoThumbnailWhenShare->SetCheck(bChecked);
	}
	bChecked = m_recordingSettingsWorkFlow.IsShowVideoThumbnailWhenShareEnabled();
	if (m_chkPlaceVideoNextToShareInRecord)
	{
		m_chkPlaceVideoNextToShareInRecord->SetVisible(bChecked);
	}

	bChecked = m_recordingSettingsWorkFlow.IsPlaceVideoNextToShareInRecordEnabled();
	if(m_chkPlaceVideoNextToShareInRecord)
	{
		m_chkPlaceVideoNextToShareInRecord->SetCheck(bChecked);
	}
	bChecked = m_recordingSettingsWorkFlow.IsSelectRecordFileLocationAfterMeetingEnabled();
	if(m_chkSelectRecordFileLocationAfterMeeting)
	{
		m_chkSelectRecordFileLocationAfterMeeting->SetCheck(bChecked);
	}
	bool testbool = false;
	ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
	err = m_recordingSettingsWorkFlow.CanGetRecordingManagementURL(testbool);
	bChecked = (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err) ? testbool : false;
	if(m_btnGetRecordingManagementURL)
	{
		m_btnGetRecordingManagementURL->SetEnabled(bChecked);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///class CSDKUICustomSettingsUIGroup
CSDKUICustomSettingsUIGroup::CSDKUICustomSettingsUIGroup()
{
	m_UICustomCurrentPage = NULL;
	m_settingsUICustomPage = NULL;
	m_UICustomMeetingWindowPage = NULL;
	m_UICustomSharePage = NULL;
	m_UICustomJoinMeetingPage = NULL;
	m_UICustomInvitePage = NULL;
	m_UICustomOthersPage = NULL;
	m_parentFrame = NULL;
	m_btnMeetingWindow = NULL;
	m_btnShare = NULL;
	m_btnJoinMeeting = NULL;
	m_btnInvite = NULL;
	m_btnOthers = NULL;
	m_chkBottomToolbar = NULL;
	m_chkTitlebarMeetingID = NULL;
	m_chkAlwaysDisplayTitleMeetingID = NULL;
	m_chkLeaveMeetingButton = NULL;
	m_chkEnterOrExitTheFullScreenButtons = NULL;
	m_chkAlwaysDisplayTaskbarIcon = NULL;
	m_chkToolTip = NULL;
	m_chkChatAndMenu = NULL;
	m_chkRecordAndMenu = NULL;
	m_chkInviteButton = NULL;
	m_chkSharingToolbar = NULL;
	m_chkFloatingVideoWindow = NULL;
	m_chkAirplayInstructionWindow = NULL;
	m_chkShareComputerSoundChkbox = NULL;
	m_chkOptimizeForFullScreenVideoClipChkbox = NULL;
	m_chkSwitchToSingleParticipantShareDlg = NULL;
	m_chkFloatingSharingToolbar = NULL;
	m_chkGreenFrameWhenSharing = NULL;
	m_chkApproveRemoteControlDlg = NULL;
	m_chkDeclineRemoteControlResponseDlg = NULL;
	m_chkMeetingWrongPswDlg = NULL;
	m_chkWaitingForHostDlg = NULL;
	m_chkInputMeetingPswDlg = NULL;
	m_chkInputMeetingScreenNameDlg = NULL;
	m_chkSelectJoinAudioDlg = NULL;
	m_chkPhoneCallTab = NULL;
	m_chkCallMeTab = NULL;
	m_chkInviteByEmailTab = NULL;
	m_chkInviteByPhoneTab = NULL;
	m_chkInviteARoomSystemTab = NULL;
	m_chkDialInSubTab = NULL;
	m_chkCallOutSubTab = NULL;
	m_chkUpgradeFreeMeetingButton = NULL;
	m_chkRemainingMeetingTimeButton = NULL;
	m_chkSettingDlgTopmostAttribute = NULL;
	m_chkFullPhoneNumber = NULL;
	m_chkReaction = NULL;
	m_chkMeetingInfo = NULL;
}
CSDKUICustomSettingsUIGroup::~CSDKUICustomSettingsUIGroup()
{
	m_UICustomCurrentPage = NULL;
	m_settingsUICustomPage = NULL;
	m_UICustomMeetingWindowPage = NULL;
	m_UICustomSharePage = NULL;
	m_UICustomJoinMeetingPage = NULL;
	m_UICustomInvitePage = NULL;
	m_UICustomOthersPage = NULL;
	m_parentFrame = NULL;
	m_btnMeetingWindow = NULL;
	m_btnShare = NULL;
	m_btnJoinMeeting = NULL;
	m_btnInvite = NULL;
	m_btnOthers = NULL;
	m_chkBottomToolbar = NULL;
	m_chkTitlebarMeetingID = NULL;
	m_chkAlwaysDisplayTitleMeetingID = NULL;
	m_chkLeaveMeetingButton = NULL;
	m_chkEnterOrExitTheFullScreenButtons = NULL;
	m_chkAlwaysDisplayTaskbarIcon = NULL;
	m_chkToolTip = NULL;
	m_chkChatAndMenu = NULL;
	m_chkRecordAndMenu = NULL;
	m_chkInviteButton = NULL;
	m_chkSharingToolbar = NULL;
	m_chkFloatingVideoWindow = NULL;
	m_chkAirplayInstructionWindow = NULL;
	m_chkShareComputerSoundChkbox = NULL;
	m_chkOptimizeForFullScreenVideoClipChkbox = NULL;
	m_chkSwitchToSingleParticipantShareDlg = NULL;
	m_chkFloatingSharingToolbar = NULL;
	m_chkGreenFrameWhenSharing = NULL;
	m_chkApproveRemoteControlDlg = NULL;
	m_chkDeclineRemoteControlResponseDlg = NULL;
	m_chkMeetingWrongPswDlg = NULL;
	m_chkWaitingForHostDlg = NULL;
	m_chkInputMeetingPswDlg = NULL;
	m_chkInputMeetingScreenNameDlg = NULL;
	m_chkSelectJoinAudioDlg = NULL;
	m_chkPhoneCallTab = NULL;
	m_chkCallMeTab = NULL;
	m_chkInviteByEmailTab = NULL;
	m_chkInviteByPhoneTab = NULL;
	m_chkInviteARoomSystemTab = NULL;
	m_chkDialInSubTab = NULL;
	m_chkCallOutSubTab = NULL;
	m_chkUpgradeFreeMeetingButton = NULL;
	m_chkRemainingMeetingTimeButton = NULL;
	m_chkSettingDlgTopmostAttribute = NULL;
	m_chkFullPhoneNumber = NULL;
	m_chkReaction = NULL;
	m_chkMeetingInfo = NULL;
}
void CSDKUICustomSettingsUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_)
{
	m_settingsUICustomPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_UI_Custom_Settings")));
	m_UICustomMeetingWindowPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_UI_Meeting_Window")));
	m_UICustomSharePage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_UI_Share")));
	m_UICustomJoinMeetingPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_UI_Join_Meeting")));
	m_UICustomInvitePage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_UI_Invite")));
	m_UICustomOthersPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_UI_Others")));
	m_btnMeetingWindow = static_cast<COptionUI*>(ui_mgr.FindControl(_T("tabbtn_UI_Meeting_Window")));
	m_btnShare = static_cast<COptionUI*>(ui_mgr.FindControl(_T("tabbtn_UI_Share")));
	m_btnJoinMeeting = static_cast<COptionUI*>(ui_mgr.FindControl(_T("tabbtn_UI_Join_Meeting")));
	m_btnInvite = static_cast<COptionUI*>(ui_mgr.FindControl(_T("tabbtn_UI_Invite")));
	m_btnOthers = static_cast<COptionUI*>(ui_mgr.FindControl(_T("tabbtn_UI_Others")));
	m_chkBottomToolbar = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_bottom_toolbar")));
	m_chkTitlebarMeetingID = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_title-bar_meeting_ID")));
	m_chkAlwaysDisplayTitleMeetingID = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_always_display_title_meeting_ID")));
	m_chkLeaveMeetingButton = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_leave_meeting_button")));
	m_chkEnterOrExitTheFullScreenButtons = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_enter_or_exit_the_full_screen_buttons")));
	m_chkAlwaysDisplayTaskbarIcon = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_always_display_task-bar_icon")));
	m_chkToolTip = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_tool-tip")));
	m_chkChatAndMenu = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_chat_button_and_menu_item")));
	m_chkRecordAndMenu = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_record_button_and_menu_item")));
	m_chkInviteButton = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_invite_button")));
	m_chkSharingToolbar = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_sharing_toolbar")));
	m_chkFloatingVideoWindow = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_floating_video_window")));
	m_chkAirplayInstructionWindow = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_ios_device_introduction_window")));
	m_chkShareComputerSoundChkbox = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_share_computer_sound_check-box")));
	m_chkOptimizeForFullScreenVideoClipChkbox = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_optimize_for_full_screen_video_clip_check-box")));
	m_chkSwitchToSingleParticipantShareDlg = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_switch_to_single_participant_share_dialog_box")));
	m_chkFloatingSharingToolbar = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_floating_sharing_toolbar")));
	m_chkGreenFrameWhenSharing = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_green_frame_when_sharing")));
	m_chkApproveRemoteControlDlg = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_approve_remote_control_dlg")));
	m_chkDeclineRemoteControlResponseDlg = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_decline_remote_control_response_dlg")));
	m_chkMeetingWrongPswDlg = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_meeting_wrong_password_dialog")));
	m_chkWaitingForHostDlg = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_waiting_for_host_dialog")));
	m_chkInputMeetingPswDlg = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_input_meeting_password_dialog")));
	m_chkInputMeetingScreenNameDlg = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_input_meeting_screen_name_dialog")));
	m_chkSelectJoinAudioDlg =static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_select_join_audio_dialog")));
	m_chkPhoneCallTab = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_phone_call_tab")));
	m_chkCallMeTab = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_call_me_tab")));
	m_chkInviteByEmailTab = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_invite_by_email_tab")));
	m_chkInviteByPhoneTab = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_invite_by_phone_tab")));
	m_chkInviteARoomSystemTab = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_invite_a_room_system_tab")));
	m_chkDialInSubTab = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_dial_in_sub-tab")));
	m_chkCallOutSubTab = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_call_out_sub-tab")));
	m_chkUpgradeFreeMeetingButton = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_upgrade_free_meeting_button")));
	m_chkRemainingMeetingTimeButton = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_remaining_meeting_time_button")));
	m_chkSettingDlgTopmostAttribute = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_setting_dialog_topmost_attribute")));
	m_chkFullPhoneNumber = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_full_phone_number_for_phone_user")));
	m_chkReaction = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_recation_button")));
	m_chkMeetingInfo = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_meetinginfo_button")));
	m_parentFrame = main_frame_;
	SetUICustomSettingsFlags();
}
void CSDKUICustomSettingsUIGroup::UninitWindow()
{
	m_UICustomSettingsWorkFlow.Cleanup();
}
void CSDKUICustomSettingsUIGroup::SetUICustomSettingsFlags()
{
	if(m_chkBottomToolbar)
	{
		m_chkBottomToolbar->SetCheck(false);
	}
	if(m_chkTitlebarMeetingID)
	{
		m_chkTitlebarMeetingID->SetCheck(false);
	}
	if(m_chkAlwaysDisplayTitleMeetingID)
	{
		m_chkAlwaysDisplayTitleMeetingID->SetCheck(false);
	}
	if(m_chkLeaveMeetingButton)
	{
		m_chkLeaveMeetingButton->SetCheck(true);
	}
	if(m_chkEnterOrExitTheFullScreenButtons)
	{
		m_chkEnterOrExitTheFullScreenButtons->SetCheck(true);
	}
	if(m_chkAlwaysDisplayTaskbarIcon)
	{
		m_chkAlwaysDisplayTaskbarIcon->SetCheck(false);
	}
	if(m_chkToolTip)
	{
		m_chkToolTip->SetCheck(true);
	}
	if(m_chkChatAndMenu)
	{
		m_chkChatAndMenu->SetCheck(false);
	}
	if(m_chkRecordAndMenu)
	{
		m_chkRecordAndMenu->SetCheck(false);
	}
	if(m_chkInviteButton)
	{
		m_chkInviteButton->SetCheck(true);
	}
	if(m_chkSharingToolbar)
	{
		m_chkSharingToolbar->SetCheck(false);
	}
	if(m_chkFloatingVideoWindow)
	{
		m_chkFloatingVideoWindow->SetCheck(true);
	}
	if(m_chkAirplayInstructionWindow)
	{
		m_chkAirplayInstructionWindow->SetCheck(true);
	}
	if(m_chkShareComputerSoundChkbox)
	{
		m_chkShareComputerSoundChkbox->SetCheck(true);
	}
	if(m_chkOptimizeForFullScreenVideoClipChkbox)
	{
		m_chkOptimizeForFullScreenVideoClipChkbox->SetCheck(true);
	}
	if(m_chkSwitchToSingleParticipantShareDlg)
	{
		m_chkSwitchToSingleParticipantShareDlg->SetCheck(true);
	}
	if(m_chkFloatingSharingToolbar)
	{
		m_chkFloatingSharingToolbar->SetCheck(false);
	}
	if(m_chkGreenFrameWhenSharing)
	{
		m_chkGreenFrameWhenSharing->SetCheck(true);
	}
	if(m_chkApproveRemoteControlDlg)
	{
		m_chkApproveRemoteControlDlg->SetCheck(true);
	}
	if(m_chkDeclineRemoteControlResponseDlg)
	{
		m_chkDeclineRemoteControlResponseDlg->SetCheck(true);
	}
	if(m_chkMeetingWrongPswDlg)
	{
		m_chkMeetingWrongPswDlg->SetCheck(false);
	}
	if(m_chkWaitingForHostDlg)
	{
		m_chkWaitingForHostDlg->SetCheck(false);
	}
	if(m_chkInputMeetingPswDlg)
	{
		m_chkInputMeetingPswDlg->SetCheck(true);
	}
	if(m_chkInputMeetingScreenNameDlg)
	{
		m_chkInputMeetingScreenNameDlg->SetCheck(true);
	}
	if(m_chkSelectJoinAudioDlg)
	{
		m_chkSelectJoinAudioDlg->SetCheck(false);
	}
	if(m_chkPhoneCallTab)
	{
		m_chkPhoneCallTab->SetCheck(true);
	}
	if(m_chkCallMeTab)
	{
		m_chkCallMeTab->SetCheck(true);
	}
	if(m_chkInviteByEmailTab)
	{
		m_chkInviteByEmailTab->SetCheck(true);
	}
	if(m_chkInviteByPhoneTab)
	{
		m_chkInviteByPhoneTab->SetCheck(true);
	}
	if(m_chkInviteARoomSystemTab)
	{
		m_chkInviteARoomSystemTab->SetCheck(true);
	}
	if(m_chkDialInSubTab)
	{
		m_chkDialInSubTab->SetCheck(true);
	}
	if(m_chkCallOutSubTab)
	{
		m_chkCallOutSubTab->SetCheck(true);
	}
	if(m_chkUpgradeFreeMeetingButton)
	{
		m_chkUpgradeFreeMeetingButton->SetCheck(false);
	}
	if(m_chkRemainingMeetingTimeButton)
	{
		m_chkRemainingMeetingTimeButton->SetCheck(false);
	}
	if(m_chkSettingDlgTopmostAttribute)
	{
		m_chkSettingDlgTopmostAttribute->SetCheck(false);
	}
	if(m_chkFullPhoneNumber)
	{
		m_chkFullPhoneNumber->SetCheck(false);
	}
	if(m_chkReaction)
	{
		m_chkReaction->SetCheck(false);
	}
	if(m_chkMeetingInfo)
	{
		m_chkMeetingInfo->SetCheck(false);
	}
}
void CSDKUICustomSettingsUIGroup::Show()
{
	if(m_settingsUICustomPage)
	{
		m_settingsUICustomPage->SetVisible(true);
		if(m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_settingsUICustomPage);
		}
	}
 	if(NULL == m_UICustomCurrentPage)
 	{
 		ShowMeetingWindowPage();
 	}
}
void CSDKUICustomSettingsUIGroup::Hide()
{
	if(m_settingsUICustomPage)
	{
		m_settingsUICustomPage->SetVisible(false);
	}
}
void CSDKUICustomSettingsUIGroup::ShowMeetingWindowPage()
{
	if(m_UICustomMeetingWindowPage)
	{
		m_UICustomMeetingWindowPage->SetVisible(true);
		SetUICustomCurrentPage(m_UICustomMeetingWindowPage);
	}
}
void CSDKUICustomSettingsUIGroup::ShowSharePage()
{
	if(m_UICustomSharePage)
	{
		m_UICustomSharePage->SetVisible(true);
		SetUICustomCurrentPage(m_UICustomSharePage);
	}
}
void CSDKUICustomSettingsUIGroup::ShowJoinMeetingPage()
{
	if(m_UICustomJoinMeetingPage)
	{
		m_UICustomJoinMeetingPage->SetVisible(true);
		SetUICustomCurrentPage(m_UICustomJoinMeetingPage);
	}
}
void CSDKUICustomSettingsUIGroup::ShowInvitePage()
{
	if(m_UICustomInvitePage)
	{
		m_UICustomInvitePage->SetVisible(true);
		SetUICustomCurrentPage(m_UICustomInvitePage);
	}
}
void CSDKUICustomSettingsUIGroup::ShowOthersPage()
{
	if(m_UICustomOthersPage)
	{
		m_UICustomOthersPage->SetVisible(true);
		SetUICustomCurrentPage(m_UICustomOthersPage);
	}
}
void CSDKUICustomSettingsUIGroup::Notify(TNotifyUI& msg)
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnMeetingWindow && m_UICustomCurrentPage != m_UICustomMeetingWindowPage)
		{
			SwitchToUICustomPage(UICustom_Meeting_Window_Page);
		}
		else if(msg.pSender == m_btnShare && m_UICustomCurrentPage != m_UICustomSharePage)
		{
			SwitchToUICustomPage(UICustom_Share_Page);
		}
		else if(msg.pSender == m_btnJoinMeeting && m_UICustomCurrentPage != m_UICustomJoinMeetingPage)
		{
			SwitchToUICustomPage(UICustom_Join_Meeting_Page);
		}
		else if(msg.pSender == m_btnInvite && m_UICustomCurrentPage != m_UICustomInvitePage)
		{
			SwitchToUICustomPage(UICustom_Invite_Page);
		}
		else if(msg.pSender == m_btnOthers && m_UICustomCurrentPage != m_UICustomOthersPage)
		{
			SwitchToUICustomPage(UICustom_Others_Page);
		}
		else if(msg.pSender == m_chkBottomToolbar)
		{
			DoBottomToolbarChkClick();
		}
		else if(msg.pSender == m_chkTitlebarMeetingID)
		{
			DoTitlebarMeetingIDChkClick();
		}
		else if(msg.pSender == m_chkAlwaysDisplayTitleMeetingID)
		{
			DoAlwaysDisplayTitleMeetingIDChkClick();
		}
		else if(msg.pSender == m_chkLeaveMeetingButton)
		{
			DoLeaveMeetingButtonChkClick();
		}
		else if(msg.pSender == m_chkEnterOrExitTheFullScreenButtons)
		{
			DoEnterOrExitTheFullScreenButtonsChkClick();
		}
		else if(msg.pSender == m_chkAlwaysDisplayTaskbarIcon)
		{
			DoAlwaysDisplayTaskbarIconChkClick();
		}
		else if(msg.pSender == m_chkToolTip)
		{
			DoToolTipChkClick();
		}
		else if(msg.pSender == m_chkChatAndMenu)
		{
			DoChatAndMenuChkClick();
		}
		else if(msg.pSender == m_chkRecordAndMenu)
		{
			DoRecordAndMenuChkClick();
		}
		else if(msg.pSender == m_chkInviteButton)
		{
			DoInviteButtonChkClick();
		}
		else if(msg.pSender == m_chkSharingToolbar)
		{
			DoSharingToolbarChkClick();
		}
		else if(msg.pSender == m_chkFloatingVideoWindow)
		{
			DoFloatingVideoWindowChkClick();
		}
		else if(msg.pSender == m_chkAirplayInstructionWindow)
		{
			DoAirplayInstructionWindowChkClick();
		}
		else if(msg.pSender == m_chkShareComputerSoundChkbox)
		{
			DoShareComputerSoundChkClick();
		}
		else if(msg.pSender == m_chkOptimizeForFullScreenVideoClipChkbox)
		{
			DoOptimizeForFullScreenVideoClipChkClick();
		}
		else if(msg.pSender == m_chkSwitchToSingleParticipantShareDlg)
		{
			DoSwitchToSingleParticipantShareDlgChkClick();
		}
		else if(msg.pSender == m_chkFloatingSharingToolbar)
		{
			DoFloatingSharingToolbarChkClick();
		}
		else if(msg.pSender == m_chkGreenFrameWhenSharing)
		{
			DoGreenFrameWhenSharingChkClick();
		}
		else if(msg.pSender == m_chkApproveRemoteControlDlg)
		{
			DoApproveRemoteControlDlgChkClick();
		}
		else if(msg.pSender == m_chkDeclineRemoteControlResponseDlg)
		{
			DoDeclineRemoteControlResponseDlgChkClick();
		}
		else if(msg.pSender == m_chkMeetingWrongPswDlg)
		{
			DoMeetingWrongPswDlgChkClick();
		}
		else if(msg.pSender == m_chkWaitingForHostDlg)
		{
			DoWaitingForHostDlgChkClick();
		}
		else if(msg.pSender == m_chkInputMeetingPswDlg)
		{
			DoInputMeetingPswDlgChkClick();
		}
		else if(msg.pSender == m_chkInputMeetingScreenNameDlg)
		{
			DoInputMeetingScreenNameDlgChkClick();
		}
		else if(msg.pSender == m_chkSelectJoinAudioDlg)
		{
			DoSelectJoinAudioDlgChkClick();
		}
		else if(msg.pSender == m_chkPhoneCallTab)
		{
			DoPhoneCallTabChkClick();
		}
		else if(msg.pSender == m_chkCallMeTab)
		{
			DoCallMeTabChkClick();
		}
		else if(msg.pSender == m_chkInviteByEmailTab)
		{
			DoInviteByEmailTabChkClick();
		}
		else if(msg.pSender == m_chkInviteByPhoneTab)
		{
			DoInviteByPhoneTabChkClick();
		}
		else if(msg.pSender == m_chkInviteARoomSystemTab)
		{
			DoInviteARoomSystemTabChkClick();
		}
		else if(msg.pSender == m_chkDialInSubTab)
		{
			DoDialInSubTabChkClick();
		}
		else if(msg.pSender == m_chkCallOutSubTab)
		{
			DoCallOutSubTabChkClick();
		}
		else if(msg.pSender == m_chkUpgradeFreeMeetingButton)
		{
			DoUpgradeFreeMeetingButtonChkClick();
		}
		else if(msg.pSender == m_chkRemainingMeetingTimeButton)
		{
			DoRemainingMeetingTimeButtonChkClick();
		}
		else if(msg.pSender == m_chkSettingDlgTopmostAttribute)
		{
			DoSettingDlgTopmostAttributeChkClick();
		}
		else if(msg.pSender == m_chkFullPhoneNumber)
		{
			DoFullPhoneNumberChkClick();
		}
		else if(msg.pSender == m_chkReaction)
		{
			DoReactionChkClick();
		}
		else if(msg.pSender == m_chkMeetingInfo)
		{
			DoMeetingInfoChkClick();
		}
	}
}
void CSDKUICustomSettingsUIGroup::DoBottomToolbarChkClick()
{
	if(NULL == m_chkBottomToolbar)
		return;
	bool bChecked = m_chkBottomToolbar->GetCheck();
	m_UICustomSettingsWorkFlow.SetBottomFloatToolbarWndVisibility(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoTitlebarMeetingIDChkClick()
{
	if(NULL == m_chkTitlebarMeetingID)
		return;
	bool bChecked = !m_chkTitlebarMeetingID->GetCheck();
	m_UICustomSettingsWorkFlow.HideMeetingInfoFromMeetingUITitle(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoAlwaysDisplayTitleMeetingIDChkClick()
{
	if(NULL == m_chkAlwaysDisplayTitleMeetingID)
		return;
	bool bChecked = !m_chkAlwaysDisplayTitleMeetingID->GetCheck();
	m_UICustomSettingsWorkFlow.SetAlwaysShowMeetingIDOnTitle(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoLeaveMeetingButtonChkClick()
{
	if(NULL == m_chkLeaveMeetingButton)
		return;
	bool bChecked = !m_chkLeaveMeetingButton->GetCheck();
	m_UICustomSettingsWorkFlow.EnableLeaveMeetingOptionForHost(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoEnterOrExitTheFullScreenButtonsChkClick()
{
	if(NULL == m_chkEnterOrExitTheFullScreenButtons)
		return;
	bool bChecked = !m_chkEnterOrExitTheFullScreenButtons->GetCheck();
	m_UICustomSettingsWorkFlow.EnableEnterAndExitFullScreenButtonOnMeetingUI(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoAlwaysDisplayTaskbarIconChkClick()
{
	if(NULL == m_chkAlwaysDisplayTaskbarIcon)
		return;
	bool bChecked = !m_chkAlwaysDisplayTaskbarIcon->GetCheck();
	m_UICustomSettingsWorkFlow.AlwaysShowIconOnTaskBar(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoToolTipChkClick()
{
	if(NULL == m_chkToolTip)
		return;
	bool bChecked = !m_chkToolTip->GetCheck();
	m_UICustomSettingsWorkFlow.EnableToolTipsShow(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoChatAndMenuChkClick()
{
	if(NULL == m_chkChatAndMenu)
		return;
	bool bChecked = !m_chkChatAndMenu->GetCheck();
	m_UICustomSettingsWorkFlow.HideChatItemOnMeetingUI(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoReactionChkClick()
{
	if(NULL == m_chkReaction)
		return;
	bool bChecked = !m_chkReaction->GetCheck();
	m_UICustomSettingsWorkFlow.HideReactionItemOnMeetingUI(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoMeetingInfoChkClick()
{
	if(NULL == m_chkMeetingInfo)
		return;
	bool bChecked = !m_chkMeetingInfo->GetCheck();
	m_UICustomSettingsWorkFlow.HideMeetingInfoItemOnMeetingUI(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoRecordAndMenuChkClick()
{
	if(NULL == m_chkRecordAndMenu)
		return;
	bool bChecked = !m_chkRecordAndMenu->GetCheck();
	m_UICustomSettingsWorkFlow.HideRecordItemOnMeetingUI(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoInviteButtonChkClick()
{
	if(NULL == m_chkInviteButton)
		return;
	bool bChecked = !m_chkInviteButton->GetCheck();
	m_UICustomSettingsWorkFlow.EnableInviteButtonOnMeetingUI(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoSharingToolbarChkClick()
{
	if(NULL == m_chkSharingToolbar)
		return;
	bool bChecked = !m_chkSharingToolbar->GetCheck();
	m_UICustomSettingsWorkFlow.SetSharingToolbarVisibility(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoFloatingVideoWindowChkClick()
{
	if(NULL == m_chkFloatingVideoWindow)
		return;
	bool bChecked = !m_chkFloatingVideoWindow->GetCheck();
	m_UICustomSettingsWorkFlow.SetFloatVideoWndVisibility(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoAirplayInstructionWindowChkClick()
{
	if(NULL == m_chkAirplayInstructionWindow)
		return;
	bool bChecked = !m_chkAirplayInstructionWindow->GetCheck();
	m_UICustomSettingsWorkFlow.EnableAirplayInstructionWindow(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoShareComputerSoundChkClick()
{
	if(NULL == m_chkShareComputerSoundChkbox)
		return;
	bool bChecked = !m_chkShareComputerSoundChkbox->GetCheck();
	m_UICustomSettingsWorkFlow.SetShowAudioUseComputerSoundChkbox(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoOptimizeForFullScreenVideoClipChkClick()
{
	if(NULL == m_chkOptimizeForFullScreenVideoClipChkbox)
		return;
	bool bChecked = !m_chkOptimizeForFullScreenVideoClipChkbox->GetCheck();
	m_UICustomSettingsWorkFlow.SetShowVideoOptimizeChkbox(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoSwitchToSingleParticipantShareDlgChkClick()
{
	if(NULL == m_chkSwitchToSingleParticipantShareDlg)
		return;
	bool bChecked = !m_chkSwitchToSingleParticipantShareDlg->GetCheck();
	m_UICustomSettingsWorkFlow.EnableShowShareSwitchMultiToSingleConfirmDlg(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoFloatingSharingToolbarChkClick()
{
	if(NULL == m_chkFloatingSharingToolbar)
		return;
	bool bChecked = !m_chkFloatingSharingToolbar->GetCheck();
	m_UICustomSettingsWorkFlow.ShowSharingToolbar(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoGreenFrameWhenSharingChkClick()
{
	if(NULL == m_chkGreenFrameWhenSharing)
		return;
	bool bChecked = !m_chkGreenFrameWhenSharing->GetCheck();
	m_UICustomSettingsWorkFlow.ShowSharingFrameWindows(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoApproveRemoteControlDlgChkClick()
{
	if(NULL == m_chkApproveRemoteControlDlg)
		return;
	bool bChecked = !m_chkApproveRemoteControlDlg->GetCheck();
	m_UICustomSettingsWorkFlow.EnableApproveRemoteControlDlg(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoDeclineRemoteControlResponseDlgChkClick()
{
	if(NULL == m_chkDeclineRemoteControlResponseDlg)
		return;
	bool bChecked = !m_chkDeclineRemoteControlResponseDlg->GetCheck();
	m_UICustomSettingsWorkFlow.EnableDeclineRemoteControlResponseDlg(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoMeetingWrongPswDlgChkClick()
{
	if(NULL == m_chkMeetingWrongPswDlg)
		return;
	bool bChecked = !m_chkMeetingWrongPswDlg->GetCheck();
	m_UICustomSettingsWorkFlow.DisablePopupMeetingWrongPSWDlg(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoWaitingForHostDlgChkClick()
{
	if(NULL == m_chkWaitingForHostDlg)
		return;
	bool bChecked = !m_chkWaitingForHostDlg->GetCheck();
	m_UICustomSettingsWorkFlow.DisableWaitingForHostDialog(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoInputMeetingPswDlgChkClick()
{
	if(NULL == m_chkInputMeetingPswDlg)
		return;
	bool bChecked = !m_chkInputMeetingPswDlg->GetCheck();
	m_UICustomSettingsWorkFlow.EnableInputMeetingPasswordDlg(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoInputMeetingScreenNameDlgChkClick()
{
	if(NULL == m_chkInputMeetingScreenNameDlg)
		return;
	bool bChecked = !m_chkInputMeetingScreenNameDlg->GetCheck();
	m_UICustomSettingsWorkFlow.EnableInputMeetingScreenNameDlg(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoInviteByEmailTabChkClick()
{
	if(NULL == m_chkInviteByEmailTab)
		return;
	bool bChecked = !m_chkInviteByEmailTab->GetCheck();
	m_UICustomSettingsWorkFlow.SetShowInviteDlgTabPage(ZOOM_SDK_NAMESPACE::SDK_INVITEDLG_TAB_EMAILCONTACT,bChecked);
}
void CSDKUICustomSettingsUIGroup::DoInviteByPhoneTabChkClick()
{
	if(NULL == m_chkInviteByPhoneTab)
		return;
	bool bChecked = !m_chkInviteByPhoneTab->GetCheck();
	m_UICustomSettingsWorkFlow.SetShowInviteDlgTabPage(ZOOM_SDK_NAMESPACE::SDK_INVITEDLG_TAB_PHONECONTACT,bChecked);
}
void CSDKUICustomSettingsUIGroup::DoInviteARoomSystemTabChkClick()
{
	if(NULL == m_chkInviteARoomSystemTab)
		return;
	bool bChecked = !m_chkInviteARoomSystemTab->GetCheck();
	m_UICustomSettingsWorkFlow.SetShowInviteDlgTabPage(ZOOM_SDK_NAMESPACE::SDK_INVITEDLG_TAB_ROOMSYSTEM,bChecked);
}
void CSDKUICustomSettingsUIGroup::DoDialInSubTabChkClick()
{
	if(NULL == m_chkDialInSubTab)
		return;
	bool bChecked = !m_chkDialInSubTab->GetCheck();
	m_UICustomSettingsWorkFlow.SetShowH323SubTabPage(ZOOM_SDK_NAMESPACE::SDK_INVITEDLG_H323_DIALIN,bChecked);
}
void CSDKUICustomSettingsUIGroup::DoCallOutSubTabChkClick()
{
	if(NULL == m_chkCallOutSubTab)
		return;
	bool bChecked = !m_chkCallOutSubTab->GetCheck();
	m_UICustomSettingsWorkFlow.SetShowH323SubTabPage(ZOOM_SDK_NAMESPACE::SDK_INVITEDLG_H323_CALLOUT,bChecked);
}
void CSDKUICustomSettingsUIGroup::DoSelectJoinAudioDlgChkClick()
{
	if(NULL == m_chkSelectJoinAudioDlg)
		return;
	bool bChecked = !m_chkSelectJoinAudioDlg->GetCheck();
	m_UICustomSettingsWorkFlow.DisableAutoShowSelectJoinAudioDlgWhenJoinMeeting(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoPhoneCallTabChkClick()
{
	if(NULL == m_chkPhoneCallTab)
		return;
	bool bChecked = !m_chkPhoneCallTab->GetCheck();
	m_UICustomSettingsWorkFlow.SetShowCallInTab(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoCallMeTabChkClick()
{
	if(NULL == m_chkCallMeTab)
		return;
	bool bChecked = !m_chkCallMeTab->GetCheck();
	m_UICustomSettingsWorkFlow.SetShowCallMeTab(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoUpgradeFreeMeetingButtonChkClick()
{
	if(NULL == m_chkUpgradeFreeMeetingButton)
		return;
	bool bChecked = !m_chkUpgradeFreeMeetingButton->GetCheck();
	m_UICustomSettingsWorkFlow.HideUpgradeFreeMeetingButton(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoRemainingMeetingTimeButtonChkClick()
{
	if(NULL == m_chkRemainingMeetingTimeButton)
		return;
	bool bChecked = !m_chkRemainingMeetingTimeButton->GetCheck();
	m_UICustomSettingsWorkFlow.DisableFreeMeetingRemainTimeNotify(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoSettingDlgTopmostAttributeChkClick()
{
	if(NULL == m_chkSettingDlgTopmostAttribute)
		return;
	bool bChecked = !m_chkSettingDlgTopmostAttribute->GetCheck();
	m_UICustomSettingsWorkFlow.DisableTopMostAttr4SettingDialog(bChecked);
}
void CSDKUICustomSettingsUIGroup::DoFullPhoneNumberChkClick()
{
	if(NULL == m_chkFullPhoneNumber)
		return;
	bool bChecked = !m_chkFullPhoneNumber->GetCheck();
	m_UICustomSettingsWorkFlow.EnableHideFullPhoneNumber4PureCallinUser(bChecked);
}
void CSDKUICustomSettingsUIGroup::SwitchToUICustomPage(SettingsUICustom_page nPage)
{
	m_UICustomMeetingWindowPage->SetVisible(false);
	m_UICustomSharePage->SetVisible(false);
	m_UICustomJoinMeetingPage->SetVisible(false);
	m_UICustomInvitePage->SetVisible(false);
	m_UICustomOthersPage->SetVisible(false);
	switch(nPage)
	{
	case UICustom_Meeting_Window_Page:
		ShowMeetingWindowPage();
		break;
	case UICustom_Share_Page:
		ShowSharePage();
		break;
	case UICustom_Join_Meeting_Page:
		ShowJoinMeetingPage();
		break;
	case UICustom_Invite_Page:
		ShowInvitePage();
		break;
	case UICustom_Others_Page:
		ShowOthersPage();
		break;
	default:
		break;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///class CSDKFeatureCustomSettingsUIGroup
CSDKFeatureCustomSettingsUIGroup::CSDKFeatureCustomSettingsUIGroup()
{
	m_FeatureCustomCurrentPage = NULL;
	m_settingsFeatureCustomPage = NULL;
	m_FeatureCustomMeetingWindowPage = NULL;
	m_FeatureCustomSharePage = NULL;
	m_FeatureCustomAudioPage = NULL;
	m_FeatureCustomVideoPage = NULL;
	m_FeatureCustomOtherFunctionsPage = NULL;
	m_parentFrame = NULL;
	m_btnMeetingWindow = NULL;
	m_btnShare = NULL;
	m_btnAudio = NULL;
	m_btnVideo = NULL;
	m_btnOtherFunctions = NULL;
	m_editMeetingWndLeft = NULL;
	m_editMeetingWndTop = NULL;
	m_editSharingMeetingWndLeft = NULL;
	m_editSharingMeetingWndTop = NULL;
	m_editSetMeetingID = NULL;
	m_editFloatingVideoWndLeft = NULL;
	m_editFloatingVideoWndTop = NULL;
	m_editPreSetEmail = NULL;
	m_editPreSetUsername = NULL;
	m_btnBackToMeeting = NULL;
	m_btnConfirmMeetingWndPos = NULL;
	m_btnConfirmSharingFloatingVideoWndPos = NULL;
	m_btnConfirmMeetingID = NULL;
	m_btnConfirmMoveFloatingVideoWndPos = NULL;
	m_btnConfirmVideoWallMode = NULL;
	m_btnCurrentSpeakerMode = NULL;
	m_btnSwitchToPreviousPage = NULL;
	m_btnSwitchToNextPage = NULL;
	m_btnConfirmPreSetInformation = NULL;
	m_chkDoubleClick4SwitchFullScreenMode = NULL;
	m_chkGrabShareWithoutPrompt = NULL;
	m_chkShareIOSDevice = NULL;
	m_chkShareWhiteBoard = NULL;
	m_chkMultiShare = NULL;
	m_chkRemoteControlCopyAndPaste = NULL;
	m_chkAutoAdjustSpeakerVolume = NULL;
	m_chkAutoAdjustMicVolume = NULL;
	m_chkForceToEnableVideoWhenJoin = NULL;
	m_chkForceToTurnOffVideoWhenJoin = NULL;
	m_chkParticipantsList = NULL;
	m_chkChatDialog = NULL;
	m_chkClaimHost = NULL;
	m_chkSplitScreenAbility = NULL;
	m_chkSwitchToSplitScreen = NULL;
	m_chkEnterFullScreenForFirstView = NULL;
	m_chkEnterFullScreenForSecondView = NULL;
	m_chkExitFullScreenForFirstView = NULL;
	m_chkExitFullScreenForSecondView = NULL;
	m_chkAutoEndOtherMeetingWhenStartMeeting = NULL;
}
CSDKFeatureCustomSettingsUIGroup::~CSDKFeatureCustomSettingsUIGroup()
{
	m_FeatureCustomCurrentPage = NULL;
	m_settingsFeatureCustomPage = NULL;
	m_FeatureCustomMeetingWindowPage = NULL;
	m_FeatureCustomSharePage = NULL;
	m_FeatureCustomAudioPage = NULL;
	m_FeatureCustomVideoPage = NULL;
	m_FeatureCustomOtherFunctionsPage = NULL;
	m_parentFrame = NULL;
	m_btnMeetingWindow = NULL;
	m_btnShare = NULL;
	m_btnAudio = NULL;
	m_btnVideo = NULL;
	m_btnOtherFunctions = NULL;
	m_editMeetingWndLeft = NULL;
	m_editMeetingWndTop = NULL;
	m_editSharingMeetingWndLeft = NULL;
	m_editSharingMeetingWndTop = NULL;
	m_editSetMeetingID = NULL;
	m_editFloatingVideoWndLeft = NULL;
	m_editFloatingVideoWndTop = NULL;
	m_editPreSetEmail = NULL;
	m_editPreSetUsername = NULL;
	m_btnBackToMeeting = NULL;
	m_btnConfirmMeetingWndPos = NULL;
	m_btnConfirmSharingFloatingVideoWndPos = NULL;
	m_btnConfirmMeetingID = NULL;
	m_btnConfirmMoveFloatingVideoWndPos = NULL;
	m_btnConfirmVideoWallMode = NULL;
	m_btnCurrentSpeakerMode = NULL;
	m_btnSwitchToPreviousPage = NULL;
	m_btnSwitchToNextPage = NULL;
	m_btnConfirmPreSetInformation = NULL;
	m_chkDoubleClick4SwitchFullScreenMode = NULL;
	m_chkGrabShareWithoutPrompt = NULL;
	m_chkShareIOSDevice = NULL;
	m_chkShareWhiteBoard = NULL;
	m_chkMultiShare = NULL;
	m_chkRemoteControlCopyAndPaste = NULL;
	m_chkAutoAdjustSpeakerVolume = NULL;
	m_chkAutoAdjustMicVolume = NULL;
	m_chkForceToEnableVideoWhenJoin = NULL;
	m_chkForceToTurnOffVideoWhenJoin = NULL;
	m_chkParticipantsList = NULL;
	m_chkChatDialog = NULL;
	m_chkClaimHost = NULL;
	m_chkSplitScreenAbility = NULL;
	m_chkSwitchToSplitScreen = NULL;
	m_chkEnterFullScreenForFirstView = NULL;
	m_chkEnterFullScreenForSecondView = NULL;
	m_chkExitFullScreenForFirstView = NULL;
	m_chkExitFullScreenForSecondView = NULL;
	m_chkAutoEndOtherMeetingWhenStartMeeting = NULL;
}
void CSDKFeatureCustomSettingsUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKSettingsUIMgr* main_frame_)
{
	m_settingsFeatureCustomPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_Feature_Custom_Settings")));
	m_FeatureCustomMeetingWindowPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_Feature_Meeting_Window")));
	m_FeatureCustomSharePage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_Feature_Share")));
	m_FeatureCustomAudioPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_Feature_Audio")));
	m_FeatureCustomVideoPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_Feature_Video")));
	m_FeatureCustomOtherFunctionsPage = static_cast<CVerticalLayoutUI*>(ui_mgr.FindControl(_T("panel_Feature_Other_Functions")));
	m_btnMeetingWindow = static_cast<COptionUI*>(ui_mgr.FindControl(_T("tabbtn_Feature_Meeting_Window")));
	m_btnShare = static_cast<COptionUI*>(ui_mgr.FindControl(_T("tabbtn_Feature_Share")));
	m_btnAudio = static_cast<COptionUI*>(ui_mgr.FindControl(_T("tabbtn_Feature_Audio")));
	m_btnVideo = static_cast<COptionUI*>(ui_mgr.FindControl(_T("tabbtn_Feature_Video")));
	m_btnOtherFunctions = static_cast<COptionUI*>(ui_mgr.FindControl(_T("tabbtn_Feature_Other_Functions")));
	m_editMeetingWndLeft = static_cast<CRichEditUI*>(ui_mgr.FindControl(_T("edit_window_left")));
	m_editMeetingWndTop = static_cast<CRichEditUI*>(ui_mgr.FindControl(_T("edit_window_top")));
	m_editSharingMeetingWndLeft = static_cast<CRichEditUI*>(ui_mgr.FindControl(_T("edit_sharing_window_left")));
	m_editSharingMeetingWndTop = static_cast<CRichEditUI*>(ui_mgr.FindControl(_T("edit_sharing_window_top")));
	m_editSetMeetingID = static_cast<CRichEditUI*>(ui_mgr.FindControl(_T("edit_set_meeting_ID")));
	m_editFloatingVideoWndLeft = static_cast<CRichEditUI*>(ui_mgr.FindControl(_T("edit_floating_video_window_left")));
	m_editFloatingVideoWndTop = static_cast<CRichEditUI*>(ui_mgr.FindControl(_T("edit_floating_video_window_top")));
	m_editPreSetEmail = static_cast<CRichEditUI*>(ui_mgr.FindControl(_T("edit_pre_set_email")));
	m_editPreSetUsername = static_cast<CRichEditUI*>(ui_mgr.FindControl(_T("edit_pre_set_username")));
	m_btnBackToMeeting = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_confirm_back_to_meeting")));
	m_btnConfirmMeetingWndPos = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_confirm_meeting_window_pos")));
	m_btnConfirmSharingFloatingVideoWndPos = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_confirm_sharing_floating_video_window_pos")));
	m_btnConfirmMeetingID = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_confirm_meeting_ID")));
	m_btnConfirmMoveFloatingVideoWndPos = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_confirm_move_floating_video_window_pos")));
	m_btnConfirmVideoWallMode = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_confirm_video_wall_mode")));
	m_btnCurrentSpeakerMode = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_current_speaker_mode")));
	m_btnSwitchToPreviousPage = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_switch_to_previous_page")));
	m_btnSwitchToNextPage = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_switch_to_next_page")));
	m_btnConfirmPreSetInformation = static_cast<CButtonUI*>(ui_mgr.FindControl(_T("btn_confirm_pre_set_information")));
	m_chkDoubleClick4SwitchFullScreenMode = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_double-click_switch_full_screen_mode")));
	m_chkGrabShareWithoutPrompt = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_grab_share_without_prompt")));
	m_chkShareIOSDevice =static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_share_IOS_device")));
	m_chkShareWhiteBoard = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_share_white_board")));
	m_chkMultiShare = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_multi_share")));
	m_chkRemoteControlCopyAndPaste = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_remote_control_copy_and_paste")));
	m_chkAutoAdjustSpeakerVolume = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_auto_adjust_speaker_volume")));
	m_chkAutoAdjustMicVolume = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_auto_adjust_mic_volume")));
	m_chkForceToEnableVideoWhenJoin = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_force_to_enable_video_when_join")));
	m_chkForceToTurnOffVideoWhenJoin = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_force_to_turn_off_video_when_join")));
	m_chkParticipantsList = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_participants_list")));
	m_chkChatDialog = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_chat_dialog")));
	m_chkClaimHost = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_claim_host")));
	m_chkSplitScreenAbility = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_split_screen_ability")));
	m_chkSwitchToSplitScreen = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_switch_split_screen")));
	m_chkEnterFullScreenForFirstView = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_enter_full_screen_for_first_view")));
	m_chkEnterFullScreenForSecondView = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_enter_full_screen_for_second_view")));
	m_chkExitFullScreenForFirstView = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_exit_full_screen_for_first_view")));
	m_chkExitFullScreenForSecondView = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_exit_full_screen_for_second_view")));
	m_chkAutoEndOtherMeetingWhenStartMeeting = static_cast<CCheckBoxUI*>(ui_mgr.FindControl(_T("chk_auto_end_other_meeting_when_start_meeting")));
	m_parentFrame = main_frame_;
	SetFeatureCustomSettingsFlags();
}
void CSDKFeatureCustomSettingsUIGroup::UninitWindow()
{
	m_FeatureCustomSettingsWorkFlow.CleanUp();
}
void CSDKFeatureCustomSettingsUIGroup::Show()
{
	if(m_settingsFeatureCustomPage)
	{
		m_settingsFeatureCustomPage->SetVisible(true);
		if(m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_settingsFeatureCustomPage);
		}
	}
	if(NULL == m_FeatureCustomCurrentPage)
	{
		ShowMeetingWindowPage();
	}
}
void CSDKFeatureCustomSettingsUIGroup::SetFeatureCustomSettingsFlags()
{
	if(m_chkDoubleClick4SwitchFullScreenMode)
	{
		m_chkDoubleClick4SwitchFullScreenMode->SetCheck(true);
	}
	if(m_chkGrabShareWithoutPrompt)
	{
		m_chkGrabShareWithoutPrompt->SetCheck(false);
	}
	if(m_chkShareIOSDevice)
	{
		m_chkShareIOSDevice->SetCheck(false);
	}
	if(m_chkShareWhiteBoard)
	{
		m_chkShareWhiteBoard->SetCheck(true);
	}
	if(m_chkMultiShare)
	{
		m_chkMultiShare->SetCheck(true);
	}
	if(m_chkRemoteControlCopyAndPaste)
	{
		m_chkRemoteControlCopyAndPaste->SetCheck(false);
	}
	if(m_editSetMeetingID)
	{
		m_editSetMeetingID->SetLimitText(19);
	}
	if(m_chkAutoAdjustSpeakerVolume)
	{
		m_chkAutoAdjustSpeakerVolume->SetCheck(true);
	}
	if(m_chkAutoAdjustMicVolume)
	{
		m_chkAutoAdjustMicVolume->SetCheck(true);
	}
	if(m_chkForceToEnableVideoWhenJoin)  
	{
		m_chkForceToEnableVideoWhenJoin->SetCheck(false);
	}
	if(m_chkForceToTurnOffVideoWhenJoin)  
	{
		m_chkForceToTurnOffVideoWhenJoin->SetCheck(false);
	}
	if(m_chkParticipantsList)
	{
		m_chkParticipantsList->SetCheck(false);
	}
	if(m_chkChatDialog)
	{
		m_chkChatDialog->SetCheck(false);
	}
	if(m_chkClaimHost)
	{
		m_chkClaimHost->SetCheck(true);
	}
	if(m_chkSwitchToSplitScreen)
	{
		m_chkSwitchToSplitScreen->SetCheck(false);
	}
	if(m_chkSplitScreenAbility)
	{
		m_chkSplitScreenAbility->SetCheck(false);
		m_chkSwitchToSplitScreen->SetEnabled(false);
	}
	if(m_chkAutoEndOtherMeetingWhenStartMeeting)
	{
		m_chkAutoEndOtherMeetingWhenStartMeeting->SetCheck(false);
	}
}
void CSDKFeatureCustomSettingsUIGroup::Hide()
{
	if(m_settingsFeatureCustomPage)
	{
		m_settingsFeatureCustomPage->SetVisible(false);
	}
}
void CSDKFeatureCustomSettingsUIGroup::ShowMeetingWindowPage()
{
	if(m_FeatureCustomMeetingWindowPage)
	{
		m_FeatureCustomMeetingWindowPage->SetVisible(true);
		SetFeatureCustomCurrentPage(m_FeatureCustomMeetingWindowPage);
	}
}
void CSDKFeatureCustomSettingsUIGroup::ShowSharePage()
{
	if(m_FeatureCustomSharePage)
	{
		m_FeatureCustomSharePage->SetVisible(true);
		SetFeatureCustomCurrentPage(m_FeatureCustomSharePage);
	}
}
void CSDKFeatureCustomSettingsUIGroup::ShowAudioPage()
{
	if(m_FeatureCustomAudioPage)
	{
		m_FeatureCustomAudioPage->SetVisible(true);
		SetFeatureCustomCurrentPage(m_FeatureCustomAudioPage);
	}
}
void CSDKFeatureCustomSettingsUIGroup::ShowVideoPage()
{
	if(m_FeatureCustomVideoPage)
	{
		m_FeatureCustomVideoPage->SetVisible(true);
		SetFeatureCustomCurrentPage(m_FeatureCustomVideoPage);
	}
}
void CSDKFeatureCustomSettingsUIGroup::ShowOtherFunctionsPage()
{
	if(m_FeatureCustomOtherFunctionsPage)
	{
		m_FeatureCustomOtherFunctionsPage->SetVisible(true);
		SetFeatureCustomCurrentPage(m_FeatureCustomOtherFunctionsPage);
	}
}
void CSDKFeatureCustomSettingsUIGroup::Notify(TNotifyUI& msg)
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnMeetingWindow && m_FeatureCustomCurrentPage != m_FeatureCustomMeetingWindowPage)
		{
			SwitchToFeatureCustomPage(FeatureCustom_Meeting_Window_Page);
		}
		else if(msg.pSender == m_btnShare && m_FeatureCustomCurrentPage != m_FeatureCustomSharePage)
		{
			SwitchToFeatureCustomPage(FeatureCustom_Share_Page);
		}
		else if(msg.pSender == m_btnAudio && m_FeatureCustomCurrentPage != m_FeatureCustomAudioPage)
		{
			SwitchToFeatureCustomPage(FeatureCustom_Audio_Page);
		}
		else if(msg.pSender == m_btnVideo && m_FeatureCustomCurrentPage != m_FeatureCustomVideoPage)
		{
			SwitchToFeatureCustomPage(FeatureCustom_Video_Page);
		}
		else if(msg.pSender == m_btnOtherFunctions && m_FeatureCustomCurrentPage != m_FeatureCustomOtherFunctionsPage)
		{
			SwitchToFeatureCustomPage(FeatureCustom_Other_Functions_Page);
		}
		else if(msg.pSender == m_btnBackToMeeting)
		{
			DoBackToMeetingBtnClick();
		}
		else if(msg.pSender == m_btnConfirmMeetingWndPos)
		{
			DoConfirmMeetingWndPosBtnClick();
		}
		else if(msg.pSender == m_btnConfirmSharingFloatingVideoWndPos)
		{
			DoConfirmSharingFloatingVideoWndPosBtnClick();
		}
		else if(msg.pSender == m_btnConfirmMeetingID)
		{
			DoConfirmMeetingIDBtnClick();
		}
		else if(msg.pSender == m_btnConfirmMoveFloatingVideoWndPos)
		{
			DoConfirmMoveFloatingVideoWndPosBtnClick();
		}
		else if(msg.pSender == m_btnConfirmVideoWallMode)
		{
			DoConfirmVideoWallModeBtnClick();
		}
		else if(msg.pSender == m_btnCurrentSpeakerMode)
		{
			DoCurrentSpeakerModeBtnClick();
		}
		else if(msg.pSender == m_btnSwitchToPreviousPage)
		{
			DoSwitchToPreviousPageBtnClick();
		}
		else if(msg.pSender == m_btnSwitchToNextPage)
		{
			DoSwitchToNextPageBtnClick();
		}
		else if(msg.pSender == m_btnConfirmPreSetInformation)
		{
			DoConfirmPreSetInformationBtnClick();
		}
		else if(msg.pSender == m_chkDoubleClick4SwitchFullScreenMode)
		{
			DoDoubleClick4SwitchFullScreenModeChkClick();
		}
		else if(msg.pSender == m_chkGrabShareWithoutPrompt)
		{
			DoGrabShareWithoutPromptChkClick();
		}
		else if(msg.pSender == m_chkShareIOSDevice)
		{
			DoShareIOSDeviceChkClick();
		}
		else if(msg.pSender == m_chkShareWhiteBoard)
		{
			DoShareWhiteBoardChkClick();
		}
		else if(msg.pSender == m_chkMultiShare)
		{
			DoMultiShareChkClick();
		}
		else if(msg.pSender == m_chkRemoteControlCopyAndPaste)
		{
			DoRemoteControlCopyAndPasteChkClick();
		}
		else if(msg.pSender == m_chkAutoAdjustSpeakerVolume)
		{
			DoAutoAdjustSpeakerVolumeChkClick();
		}
		else if(msg.pSender == m_chkAutoAdjustMicVolume)
		{
			DoAutoAdjustMicVolumeChkClick();
		}
		else if(msg.pSender == m_chkForceToEnableVideoWhenJoin)
		{
			DoForceToEnableVideoWhenJoinChkClick();
		}
		else if(msg.pSender == m_chkForceToTurnOffVideoWhenJoin)
		{
			DoForceToTurnOffVideoWhenJoinChkClick();
		}
		else if(msg.pSender == m_chkParticipantsList)
		{
			DoParticipantsListChkClick();
		}
		else if(msg.pSender == m_chkChatDialog)
		{
			DoChatDialogChkClick();
		}
		else if(msg.pSender == m_chkClaimHost)
		{
			DoClaimHostChkClick();
		}
		else if(msg.pSender == m_chkSplitScreenAbility)
		{
			DoSplitScreenAbilityChkClick();
		}
		else if(msg.pSender == m_chkSwitchToSplitScreen)
		{
			DoSwitchSplitScreenChkClick();
		}
		else if(msg.pSender == m_chkEnterFullScreenForFirstView)
		{
			DoEnterFullScreenForFirstViewChkClick();
		}
		else if(msg.pSender == m_chkEnterFullScreenForSecondView)
		{
			DoEnterFullScreenForSecondViewChkClick();
		}
		else if(msg.pSender == m_chkExitFullScreenForFirstView )
		{
			DoExitFullScreenForFirstViewChkClick();
		}
		else if(msg.pSender == m_chkExitFullScreenForSecondView)
		{
			DoExitFullScreenForSecondViewChkClick();
		}
		else if(msg.pSender == m_chkAutoEndOtherMeetingWhenStartMeeting)
		{
			DoAutoEndOtherMeetingWhenStartMeetingChkClick();
		}
		else if(msg.pSender == m_btnConfirmPreSetInformation)
		{
			DoConfirmPreSetInformationBtnClick();
		}
	}
}
void CSDKFeatureCustomSettingsUIGroup::DoBackToMeetingBtnClick()
{
	if(NULL == m_btnBackToMeeting)
		return;
	m_FeatureCustomSettingsWorkFlow.BackToMeeting();
}
void CSDKFeatureCustomSettingsUIGroup::DoConfirmMeetingWndPosBtnClick()
{
	if(NULL == m_editMeetingWndLeft || NULL == m_editMeetingWndTop)
		return;
	std::wstring windowLeft = m_editMeetingWndLeft->GetText().GetData();
	std::wstring windowTop = m_editMeetingWndTop->GetText().GetData();
	ZOOM_SDK_NAMESPACE::WndPosition pos;
	pos.left = _wtoi(windowLeft.c_str());
	pos.top = _wtoi(windowTop.c_str());
	m_FeatureCustomSettingsWorkFlow.SetMeetingUIPos(pos);
}
void CSDKFeatureCustomSettingsUIGroup::DoConfirmSharingFloatingVideoWndPosBtnClick()
{
	if(NULL == m_editSharingMeetingWndLeft || NULL == m_editSharingMeetingWndTop)
		return;
	std::wstring windowLeft = m_editSharingMeetingWndLeft->GetText().GetData();
	std::wstring windowTop = m_editSharingMeetingWndTop->GetText().GetData();
	ZOOM_SDK_NAMESPACE::WndPosition pos;
	pos.left = _wtoi(windowLeft.c_str());
	pos.top = _wtoi(windowTop.c_str());
	m_FeatureCustomSettingsWorkFlow.SetFloatVideoPos(pos);
}
void CSDKFeatureCustomSettingsUIGroup::DoConfirmMeetingIDBtnClick()
{
	if(NULL == m_editSetMeetingID)
		return;
	std::wstring meetingID = m_editSetMeetingID->GetText().GetData();
	UINT64 meetingNumber = _wtoi64(meetingID.c_str());
	m_FeatureCustomSettingsWorkFlow.SetMeetingIDForMeetingUITitle(meetingNumber);
}
void CSDKFeatureCustomSettingsUIGroup::DoConfirmMoveFloatingVideoWndPosBtnClick()
{
	if(NULL == m_editFloatingVideoWndLeft || NULL == m_editFloatingVideoWndTop)
		return;
	std::wstring windowLeft = m_editFloatingVideoWndLeft->GetText().GetData();
	std::wstring windowTop = m_editFloatingVideoWndTop->GetText().GetData();
	int left = _wtoi(windowLeft.c_str());
	int top = _wtoi(windowTop.c_str());
	m_FeatureCustomSettingsWorkFlow.MoveFloatVideoWnd(left,top);
}
void CSDKFeatureCustomSettingsUIGroup::DoDoubleClick4SwitchFullScreenModeChkClick()
{
	if(NULL == m_chkDoubleClick4SwitchFullScreenMode)
		return;
	bool bChecked = !m_chkDoubleClick4SwitchFullScreenMode->GetCheck();
	m_FeatureCustomSettingsWorkFlow.EnableLButtonDBClick4SwitchFullScreenMode(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoGrabShareWithoutPromptChkClick()
{
	if(NULL == m_chkGrabShareWithoutPrompt)
		return;
	bool bChecked = !m_chkGrabShareWithoutPrompt->GetCheck();
	m_FeatureCustomSettingsWorkFlow.EnableGrabShareWithoutReminder(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoShareIOSDeviceChkClick()
{
	if(NULL == m_chkShareIOSDevice)
		return;
	bool bChecked = !m_chkShareIOSDevice->GetCheck();
	m_FeatureCustomSettingsWorkFlow.EnableShareIOSDevice(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoShareWhiteBoardChkClick()
{
	if(NULL == m_chkShareWhiteBoard)
		return;
	bool bChecked = !m_chkShareWhiteBoard->GetCheck();
	m_FeatureCustomSettingsWorkFlow.EnableShareWhiteBoard(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoMultiShareChkClick()
{
	if(NULL == m_chkMultiShare)
		return;
	bool bChecked = !m_chkMultiShare->GetCheck();
	m_FeatureCustomSettingsWorkFlow.ForceDisableMultiShare(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoRemoteControlCopyAndPasteChkClick()
{
	if(NULL == m_chkRemoteControlCopyAndPaste)
		return;
	bool bChecked = !m_chkRemoteControlCopyAndPaste->GetCheck();
	m_FeatureCustomSettingsWorkFlow.DisableRemoteCtrlCopyPasteFeature(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoConfirmVideoWallModeBtnClick()
{
	m_FeatureCustomSettingsWorkFlow.SwitchToVideoWall();
}
void CSDKFeatureCustomSettingsUIGroup::DoCurrentSpeakerModeBtnClick()
{
	m_FeatureCustomSettingsWorkFlow.SwtichToAcitveSpeaker();
}
void CSDKFeatureCustomSettingsUIGroup::DoSwitchToPreviousPageBtnClick()
{
	m_FeatureCustomSettingsWorkFlow.ShowPreOrNextPageVideo(true);
}
void CSDKFeatureCustomSettingsUIGroup::DoSwitchToNextPageBtnClick()
{
	m_FeatureCustomSettingsWorkFlow.ShowPreOrNextPageVideo(false);
}
void CSDKFeatureCustomSettingsUIGroup::DoAutoAdjustSpeakerVolumeChkClick()
{
	if(NULL == m_chkAutoAdjustSpeakerVolume)
		return;
	bool bChecked = !m_chkAutoAdjustSpeakerVolume->GetCheck();
	m_FeatureCustomSettingsWorkFlow.EnableAutoAdjustSpeakerVolumeWhenJoinAudio(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoAutoAdjustMicVolumeChkClick()
{
	if(NULL == m_chkAutoAdjustMicVolume)
		return;
	bool bChecked = !m_chkAutoAdjustMicVolume->GetCheck();
	m_FeatureCustomSettingsWorkFlow.EnableAutoAdjustMicVolumeWhenJoinAudio(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoForceToEnableVideoWhenJoinChkClick()
{
	if(NULL == m_chkForceToEnableVideoWhenJoin)
		return;
	bool bChecked = !m_chkForceToEnableVideoWhenJoin->GetCheck();
	m_FeatureCustomSettingsWorkFlow.EnableForceAutoStartMyVideoWhenJoinMeeting(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoForceToTurnOffVideoWhenJoinChkClick()
{
	if(NULL == m_chkForceToTurnOffVideoWhenJoin)
		return;
	bool bChecked = !m_chkForceToTurnOffVideoWhenJoin->GetCheck();
	m_FeatureCustomSettingsWorkFlow.EnableForceAutoStopMyVideoWhenJoinMeeting(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoParticipantsListChkClick()
{
	if(NULL == m_chkParticipantsList)
		return;
	bool bChecked = !m_chkParticipantsList->GetCheck();
	HWND hParticipantsListWnd;
	m_FeatureCustomSettingsWorkFlow.ShowParticipantsListWnd(bChecked,hParticipantsListWnd);
}
void CSDKFeatureCustomSettingsUIGroup::DoChatDialogChkClick()
{
	if(NULL == m_chkChatDialog)
		return;
	bool bChecked = !m_chkChatDialog->GetCheck();
	if(bChecked)
	{
		ZOOM_SDK_NAMESPACE::ShowChatDlgParam param;
		m_FeatureCustomSettingsWorkFlow.ShowChatDlg(param);
	}
	else
	{
		m_FeatureCustomSettingsWorkFlow.HideChatDlg();
	}
}
void CSDKFeatureCustomSettingsUIGroup::DoClaimHostChkClick()
{
	if(NULL == m_chkClaimHost)
		return;
	bool bChecked = !m_chkClaimHost->GetCheck();
	m_FeatureCustomSettingsWorkFlow.EnableClaimHostFeature(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoSplitScreenAbilityChkClick()
{
	if(NULL == m_chkSplitScreenAbility)
		return;
	bool bChecked = !m_chkSplitScreenAbility->GetCheck();
	m_chkSwitchToSplitScreen->SetEnabled(bChecked);
	m_FeatureCustomSettingsWorkFlow.DisableSplitScreenModeUIElements(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoSwitchSplitScreenChkClick()
{
	if(NULL == m_chkSwitchToSplitScreen)
		return;
	bool bChecked = !m_chkSwitchToSplitScreen->GetCheck();
	m_FeatureCustomSettingsWorkFlow.SwitchSplitScreenMode(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoEnterFullScreenForFirstViewChkClick()
{
	if(NULL == m_chkEnterFullScreenForFirstView || NULL == m_chkEnterFullScreenForSecondView)
		return;
	bool bChecked = !m_chkEnterFullScreenForFirstView->GetCheck();
	bool bChecked2 = m_chkEnterFullScreenForSecondView->GetCheck();
	m_FeatureCustomSettingsWorkFlow.EnterFullScreen(bChecked,bChecked2);
}
void CSDKFeatureCustomSettingsUIGroup::DoEnterFullScreenForSecondViewChkClick()
{
	if(NULL == m_chkEnterFullScreenForFirstView || NULL == m_chkEnterFullScreenForSecondView)
		return;
	bool bChecked = m_chkEnterFullScreenForFirstView->GetCheck();
	bool bChecked2 = !m_chkEnterFullScreenForSecondView->GetCheck();
	m_FeatureCustomSettingsWorkFlow.EnterFullScreen(bChecked,bChecked2);
}
void CSDKFeatureCustomSettingsUIGroup::DoExitFullScreenForFirstViewChkClick()
{
	if(NULL == m_chkExitFullScreenForFirstView || NULL == m_chkExitFullScreenForSecondView)
		return;
	bool bChecked = !m_chkExitFullScreenForFirstView->GetCheck();
	bool bChecked2 = m_chkExitFullScreenForSecondView->GetCheck();
	m_FeatureCustomSettingsWorkFlow.ExitFullScreen(bChecked,bChecked2);
}
void CSDKFeatureCustomSettingsUIGroup::DoExitFullScreenForSecondViewChkClick()
{
	if(NULL == m_chkExitFullScreenForFirstView || NULL == m_chkExitFullScreenForSecondView)
		return;
	bool bChecked = m_chkExitFullScreenForFirstView->GetCheck();
	bool bChecked2 = !m_chkExitFullScreenForSecondView->GetCheck();
	m_FeatureCustomSettingsWorkFlow.ExitFullScreen(bChecked,bChecked2);
}
void CSDKFeatureCustomSettingsUIGroup::DoAutoEndOtherMeetingWhenStartMeetingChkClick()
{
	if(NULL == m_chkAutoEndOtherMeetingWhenStartMeeting)
		return;
	bool bChecked = !m_chkAutoEndOtherMeetingWhenStartMeeting->GetCheck();
	m_FeatureCustomSettingsWorkFlow.EnableAutoEndOtherMeetingWhenStartMeeting(bChecked);
}
void CSDKFeatureCustomSettingsUIGroup::DoConfirmPreSetInformationBtnClick()
{
	if(NULL == m_editPreSetEmail || NULL == m_editPreSetUsername)
		return;
	std::wstring preEmail = m_editPreSetEmail->GetText().GetData();
	std::wstring preUsername = m_editPreSetUsername->GetText().GetData();
	m_FeatureCustomSettingsWorkFlow.PrePopulateWebinarRegistrationInfo(preEmail.c_str(),preUsername.c_str());
}
void CSDKFeatureCustomSettingsUIGroup::SwitchToFeatureCustomPage(SettingsFeatureCustom_page nPage)
{
	m_FeatureCustomMeetingWindowPage->SetVisible(false);
	m_FeatureCustomSharePage->SetVisible(false);
	m_FeatureCustomAudioPage->SetVisible(false);
	m_FeatureCustomVideoPage->SetVisible(false);
	m_FeatureCustomOtherFunctionsPage->SetVisible(false);
	switch(nPage)
	{
	case FeatureCustom_Meeting_Window_Page:
		ShowMeetingWindowPage();
		break;
	case FeatureCustom_Share_Page:
		ShowSharePage();
		break;
	case FeatureCustom_Audio_Page:
		ShowAudioPage();
		break;
	case FeatureCustom_Video_Page:
		ShowVideoPage();
		break;
	case FeatureCustom_Other_Functions_Page:
		ShowOtherFunctionsPage();
		break;
	default:
		break;
	}	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///class CSDKSettingsUIMgr
CSDKSettingsUIMgr::CSDKSettingsUIMgr()
{
	m_currentPage = NULL;
	m_btnGeneralSettings = NULL;
	m_btnAudioSettings = NULL;
	m_btnVideoSettings = NULL;
	m_btnVirtualBGSettings = NULL;
	m_btnRecordingSettings = NULL; 
	m_btnUICustomSettings = NULL;
	m_btnFeatureCustomSettings = NULL;
	m_panel_tab_main = NULL;
	m_general_settings_page = NULL;
	m_audio_settings_page = NULL;
	m_video_settings_page = NULL;
	m_recording_settings_page = NULL;
	m_ui_custom_settings_page = NULL;
	m_feature_custom_settings_page = NULL;
}
CSDKSettingsUIMgr::~CSDKSettingsUIMgr()
{
	m_currentPage = NULL;
	m_btnGeneralSettings = NULL;
	m_btnAudioSettings = NULL;
	m_btnVideoSettings = NULL;
	m_btnVirtualBGSettings = NULL;
	m_btnRecordingSettings = NULL; 
	m_btnUICustomSettings = NULL;
	m_btnFeatureCustomSettings = NULL;
	m_panel_tab_main = NULL;
	m_general_settings_page = NULL;
	m_audio_settings_page = NULL;
	m_video_settings_page = NULL;
	m_recording_settings_page = NULL;
	m_ui_custom_settings_page = NULL;
	m_feature_custom_settings_page = NULL;
}
void CSDKSettingsUIMgr::InitWindow()
{
#ifdef _ONE_CLICK_TEST_
    //click 'Configure' button to test almost all the APIs. The test result file Auto_TestAllFunction_Log.txt locates d:\
    CSDKSettingApiTest *testapi =new CSDKSettingApiTest();
	delete testapi;
#endif

	m_GeneralSettingsUIGroup.InitWindow(m_PaintManager,this);
	m_AudioSettingsUIGroup.InitWindow(m_PaintManager,this);
	m_VideoSettingsUIGroup.InitWindow(m_PaintManager,this);
	m_virtualBGSettingUIGroup.InitWindow(m_PaintManager,this);
	m_RecordingSettingsUIGroup.InitWindow(m_PaintManager,this);
	m_UICustomSettingsUIGroup.InitWindow(m_PaintManager,this);
	m_FeatureCustomSettingsUIGroup.InitWindow(m_PaintManager,this);
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
	m_virtualBG_settings_page = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("panel_Virtual_background_Settings")));
	m_btnVirtualBGSettings = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("tabbtn_virtualBG_settings")));
	m_video_settings_page = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("panel_Video_Settings")));
	m_btnRecordingSettings = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("tabbtn_recording_settings")));
	m_recording_settings_page = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("panel_Recording_Settings")));
	m_btnUICustomSettings = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("tabbtn_ui_custom")));
	m_ui_custom_settings_page = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("panel_UI_Custom_Settings")));
	m_btnFeatureCustomSettings = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("tabbtn_feature_custom")));
	m_feature_custom_settings_page = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("panel_Feature_Custom_Settings")));
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
		else if(msg.pSender == m_btnVirtualBGSettings && m_currentPage != m_virtualBG_settings_page)
		{
			SwitchToPage(Setting_VirtualBG_page);
		}
		else if(msg.pSender == m_btnRecordingSettings && m_currentPage != m_recording_settings_page)
		{
			SwitchToPage(Setting_Recording_Page);
		}
		else if(msg.pSender == m_btnUICustomSettings && m_currentPage != m_ui_custom_settings_page)
		{
			SwitchToPage(Setting_UI_Custom_Page);
		}
		else if(msg.pSender == m_btnFeatureCustomSettings && m_currentPage != m_feature_custom_settings_page)
		{
			SwitchToPage(Setting_Feature_Custom_Page);
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
		else if(m_currentPage == m_virtualBG_settings_page)
		{
			m_virtualBGSettingUIGroup.Notify(msg);
		}
		else if(m_currentPage == m_recording_settings_page)
		{
			m_RecordingSettingsUIGroup.Notify(msg);
		}
		else if(m_currentPage == m_ui_custom_settings_page)
		{
			m_UICustomSettingsUIGroup.Notify(msg);
		}
		else if(m_currentPage == m_feature_custom_settings_page)
		{
			m_FeatureCustomSettingsUIGroup.Notify(msg);
		}
	}
	else
	{
		m_GeneralSettingsUIGroup.Notify(msg);
		m_AudioSettingsUIGroup.Notify(msg);
		m_VideoSettingsUIGroup.Notify(msg);
		m_RecordingSettingsUIGroup.Notify(msg);
		m_UICustomSettingsUIGroup.Notify(msg);
		m_FeatureCustomSettingsUIGroup.Notify(msg);
		m_virtualBGSettingUIGroup.Notify(msg);
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
	if(m_GeneralSettingsUIGroup.IsVisable())
		m_GeneralSettingsUIGroup.Hide();
	if(m_AudioSettingsUIGroup.IsVisable())
		m_AudioSettingsUIGroup.Hide();
	if(m_VideoSettingsUIGroup.IsVisable())
		m_VideoSettingsUIGroup.Hide();
	if(m_RecordingSettingsUIGroup.IsVisable())
		m_RecordingSettingsUIGroup.Hide();
	if(m_UICustomSettingsUIGroup.IsVisable())
		m_UICustomSettingsUIGroup.Hide();
	if(m_FeatureCustomSettingsUIGroup.IsVisable())
		m_FeatureCustomSettingsUIGroup.Hide();
	if(m_virtualBGSettingUIGroup.IsVisable())
		m_virtualBGSettingUIGroup.Hide();
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
	case Setting_VirtualBG_page:
		m_virtualBGSettingUIGroup.Show();
		break;
	case Setting_Recording_Page:
		m_RecordingSettingsUIGroup.Show();
		break;
	case Setting_UI_Custom_Page:
		m_UICustomSettingsUIGroup.Show();
		break;
	case Setting_Feature_Custom_Page:
		m_FeatureCustomSettingsUIGroup.Show();
		break;
	default:
		break;
	}
}
void CSDKSettingsUIMgr::ShowErrorMessage(const wchar_t* error_message)
{
	if (error_message)
		::MessageBox(NULL, error_message, L"error", MB_OK);
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
	m_UICustomSettingsUIGroup.UninitWindow();
	m_FeatureCustomSettingsUIGroup.UninitWindow();
	m_virtualBGSettingUIGroup.UninitWindow();
	return 0;
}