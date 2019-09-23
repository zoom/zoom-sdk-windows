#include "stdafx.h"
#include "SETTINGS_audio_workflow.h"
CSDKAudioSettingsWorkFlow::CSDKAudioSettingsWorkFlow()
{
	m_pAudioSettingsUIEvent = NULL;
	m_pSettingService = NULL;
	m_pAudioSettingContext = NULL;
	m_pTestAudioDeviceHelper = NULL;
	Init();
}
CSDKAudioSettingsWorkFlow::~CSDKAudioSettingsWorkFlow()
{
	m_pAudioSettingsUIEvent = NULL;
	m_pSettingService = NULL;
	m_pAudioSettingContext = NULL;
	m_pTestAudioDeviceHelper = NULL;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::Init()
{
	if(NULL == m_pSettingService)
	{
		m_pSettingService = SDKInterfaceWrap::GetInst().GetSettingService();
	}
	if(m_pSettingService)
	{
		m_pAudioSettingContext = m_pSettingService->GetAudioSettings();
		if(m_pAudioSettingContext)
		{
			ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
			err = m_pAudioSettingContext->SetAudioDeviceEvent(this);
			if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != err)
			{
				return err;
			}
		}
	}
	if(m_pAudioSettingContext)
	{
		m_pTestAudioDeviceHelper = m_pAudioSettingContext->GetTestAudioDeviceHelper();
		if(m_pTestAudioDeviceHelper)
		{
			ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
			err = m_pTestAudioDeviceHelper->SetEvent(this);
			return err;
		}
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
void CSDKAudioSettingsWorkFlow::SetUIEvent(CSDKAudioSettingsUIEvent* event_)
{
	m_pAudioSettingsUIEvent = event_;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::EnableAlwaysMuteMicWhenJoinVoip(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableAlwaysMuteMicWhenJoinVoip(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::EnableAutoAdjustMic(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableAutoAdjustMic(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::EnableAutoJoinAudio(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableAutoJoinAudio(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::EnableHoldSpaceKeyToSpeak(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableHoldSpaceKeyToSpeak(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::EnableMicOriginalInput(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableMicOriginalInput(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::EnableStereoAudio(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableStereoAudio(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::EnableSuppressAudioNotify(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableSuppressAudioNotify(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IMicInfo* >* CSDKAudioSettingsWorkFlow::GetMicList()
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IMicInfo* >* list;
		list = m_pAudioSettingContext->GetMicList();
		if(NULL != list)
		{
			return list;
		}
	}
	return NULL;
}
ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ISpeakerInfo* >* CSDKAudioSettingsWorkFlow::GetSpeakerList()
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ISpeakerInfo* >* list;
		list = m_pAudioSettingContext->GetSpeakerList();
		if(NULL != list)
		{
			return list;
		}
	}
	return NULL;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::SetMicVol(FLOAT& value)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->SetMicVol(value);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::GetMicVol(FLOAT& value)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->GetMicVol(value);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::SetSpeakerVol(FLOAT& value)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->SetSpeakerVol(value);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::GetSpeakerVol(FLOAT& value)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->GetSpeakerVol(value);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::SelectMic(const wchar_t* deviceId, const wchar_t* deviceName)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->SelectMic(deviceId,deviceName);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::SelectSpeaker(const wchar_t* deviceId, const wchar_t* deviceName)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->SelectSpeaker(deviceId,deviceName);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
bool CSDKAudioSettingsWorkFlow::IsAutoJoinAudioEnabled()
{
	if(m_pAudioSettingContext)
	{
		bool bChecked = m_pAudioSettingContext->IsAutoJoinAudioEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::IsAutoAdjustMicEnabled()
{
	if(m_pAudioSettingContext)
	{
		bool bChecked = m_pAudioSettingContext->IsAutoAdjustMicEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::IsStereoAudioEnable()
{
	if(m_pAudioSettingContext)
	{
		bool bChecked = m_pAudioSettingContext->IsStereoAudioEnable();
		return bChecked;
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::IsMicOriginalInputEnable()
{
	if(m_pAudioSettingContext)
	{
		bool bChecked = m_pAudioSettingContext->IsMicOriginalInputEnable();
		return bChecked;
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::IsHoldSpaceKeyToSpeakEnabled()
{
	if(m_pAudioSettingContext)
	{
		bool bChecked = m_pAudioSettingContext->IsHoldSpaceKeyToSpeakEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::IsAlwaysMuteMicWhenJoinVoipEnabled()
{
	if(m_pAudioSettingContext)
	{
		bool bChecked = m_pAudioSettingContext->IsAlwaysMuteMicWhenJoinVoipEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::IsSuppressAudioNotifyEnabled()
{
	if(m_pAudioSettingContext)
	{
		bool bChecked = m_pAudioSettingContext->IsSuppressAudioNotifyEnabled();
		return bChecked;
	}
	return false;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::TestMicStartRecording(const wchar_t* deviceID /* = NULL */)
{
	if(m_pTestAudioDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestAudioDeviceHelper->TestMicStartRecording(deviceID);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::TestMicStopTesting()
{
	if(m_pTestAudioDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestAudioDeviceHelper->TestMicStopTesting();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::TestMicPlayRecording()
{
	if(m_pTestAudioDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestAudioDeviceHelper->TestMicPlayRecording();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::TestSpeakerStartPlaying(const wchar_t* deviceID /* = NULL */)
{
	if(m_pTestAudioDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestAudioDeviceHelper->TestSpeakerStartPlaying(deviceID);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::TestSpeakerStopPlaying()
{
	if(m_pTestAudioDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestAudioDeviceHelper->TestSpeakerStopPlaying();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::SetTimerInterval(unsigned int timerInterval)
{
	if(m_pTestAudioDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestAudioDeviceHelper->SetTimerInterval(timerInterval);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
void CSDKAudioSettingsWorkFlow::onComputerMicDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IMicInfo *>* pNewMicList)
{
	if(m_pAudioSettingsUIEvent)
	{
		m_pAudioSettingsUIEvent->OnComputerMicDeviceChanged(pNewMicList);
	}
}
void CSDKAudioSettingsWorkFlow::onComputerSpeakerDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ISpeakerInfo *>* pNewSpeakerList)
{
	if(m_pAudioSettingsUIEvent)
	{
		m_pAudioSettingsUIEvent->OnComputerSpeakerDeviceChanged(pNewSpeakerList);
	}
}
void CSDKAudioSettingsWorkFlow::OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume)
{
	if(m_pAudioSettingsUIEvent)
	{
		m_pAudioSettingsUIEvent->OnMicSpkVolumnChanged(MicVolume,SpkVolume);
	}
}
void CSDKAudioSettingsWorkFlow::OnNoAudioDeviceIsUseful(bool bMicOrSpk)
{
	if(m_pAudioSettingsUIEvent)
	{
		m_pAudioSettingsUIEvent->OnNoAudioDeviceIsUseful(bMicOrSpk);
	}
}
void CSDKAudioSettingsWorkFlow::OnSelectedAudioDeviceIsChanged()
{
	if(m_pAudioSettingsUIEvent)
	{
		m_pAudioSettingsUIEvent->OnSelectedAudioDeviceIsChanged();
	}
}
void CSDKAudioSettingsWorkFlow::OnTestMicStatusChanged(ZOOM_SDK_NAMESPACE::SDK_TESTMIC_STATUS status,bool& bHandled)
{
	if(m_pAudioSettingsUIEvent)
	{
		m_pAudioSettingsUIEvent->OnTestMicStatusChanged(status,bHandled);
	}
}

ZOOM_SDK_NAMESPACE::SDKError CSDKAudioSettingsWorkFlow::EnableEchoCancellation(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableEchoCancellation(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
bool CSDKAudioSettingsWorkFlow::IsEchoCancellationEnabled()
{
	if(m_pAudioSettingContext)
	{
		bool bChecked = m_pAudioSettingContext->IsEchoCancellationEnabled();
		return bChecked;
	}
	return false;
}
