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
bool CSDKAudioSettingsWorkFlow::Init()
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
				return false;
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
			if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			{
				return true;
			}
		}
	}
	return false;
}
void CSDKAudioSettingsWorkFlow::SetUIEvent(CSDKAudioSettingsUIEvent* event_)
{
	m_pAudioSettingsUIEvent = event_;
}
bool CSDKAudioSettingsWorkFlow::EnableAlwaysMuteMicWhenJoinVoip(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableAlwaysMuteMicWhenJoinVoip(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::EnableAutoAdjustMic(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableAutoAdjustMic(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::EnableAutoJoinAudio(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableAutoJoinAudio(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::EnableHoldSpaceKeyToSpeak(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableHoldSpaceKeyToSpeak(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::EnableMicOriginalInput(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableMicOriginalInput(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::EnableStereoAudio(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableStereoAudio(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::EnableSuppressAudioNotify(bool bEnable)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->EnableSuppressAudioNotify(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
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
bool CSDKAudioSettingsWorkFlow::SetMicVol(FLOAT& value)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->SetMicVol(value);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
FLOAT CSDKAudioSettingsWorkFlow::GetMicVol(FLOAT& value)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->GetMicVol(value);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return value;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::SetSpeakerVol(FLOAT& value)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->SetSpeakerVol(value);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
FLOAT CSDKAudioSettingsWorkFlow::GetSpeakerVol(FLOAT& value)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->GetSpeakerVol(value);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return value;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::SelectMic(const wchar_t* deviceId, const wchar_t* deviceName)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->SelectMic(deviceId,deviceName);
		if(err == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		{
			return true;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::SelectSpeaker(const wchar_t* deviceId, const wchar_t* deviceName)
{
	if(m_pAudioSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAudioSettingContext->SelectSpeaker(deviceId,deviceName);
		if(err == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		{
			return true;
		}
	}
	return false;
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
bool CSDKAudioSettingsWorkFlow::TestMicStartRecording(const wchar_t* deviceID /* = NULL */)
{
	if(m_pTestAudioDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestAudioDeviceHelper->TestMicStartRecording(deviceID);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::TestMicStopTesting()
{
	if(m_pTestAudioDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestAudioDeviceHelper->TestMicStopTesting();
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::TestMicPlayRecording()
{
	if(m_pTestAudioDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestAudioDeviceHelper->TestMicPlayRecording();
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::TestSpeakerStartPlaying(const wchar_t* deviceID /* = NULL */)
{
	if(m_pTestAudioDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestAudioDeviceHelper->TestSpeakerStartPlaying(deviceID);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::TestSpeakerStopPlaying()
{
	if(m_pTestAudioDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestAudioDeviceHelper->TestSpeakerStopPlaying();
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKAudioSettingsWorkFlow::SetTimerInterval(unsigned int timerInterval)
{
	if(m_pTestAudioDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestAudioDeviceHelper->SetTimerInterval(timerInterval);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
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