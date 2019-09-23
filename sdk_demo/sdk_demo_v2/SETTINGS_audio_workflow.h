#pragma once
#include "sdk_util.h"
#include "stdafx.h"
#include "setting_service_interface.h"
class CSDKAudioSettingsUIEvent
{
public:
	virtual void OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume) = 0;
	virtual void OnNoAudioDeviceIsUseful(bool bMicOrSpk) = 0; 
	virtual void OnTestMicStatusChanged(ZOOM_SDK_NAMESPACE::SDK_TESTMIC_STATUS status,bool& bHandled) = 0; 
	virtual void OnSelectedAudioDeviceIsChanged() = 0;
	virtual void OnComputerMicDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IMicInfo*>* pNewMicList) = 0;
	virtual void OnComputerSpeakerDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ISpeakerInfo*>* pNewSpeakerList) = 0;
};
class CSDKAudioSettingsWorkFlow:public ZOOM_SDK_NAMESPACE::ITestAudioDeviceHelperEvent,public ZOOM_SDK_NAMESPACE::IAudioSettingContextEvent
{
public:
	CSDKAudioSettingsWorkFlow();
	virtual ~CSDKAudioSettingsWorkFlow();
	bool Init();
	void Cleanup() {}
	void SetUIEvent(CSDKAudioSettingsUIEvent* event_);
	////audio setting context
	ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IMicInfo* >*  GetMicList();
	ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ISpeakerInfo* >* GetSpeakerList();
	bool EnableAutoJoinAudio(bool bEnable);
	bool EnableAutoAdjustMic(bool bEnable);
	bool EnableStereoAudio(bool bEnable);
	bool EnableMicOriginalInput(bool bEnable);
	bool EnableHoldSpaceKeyToSpeak(bool bEnable);
	bool EnableAlwaysMuteMicWhenJoinVoip(bool bEnable);
	bool EnableSuppressAudioNotify(bool bEnable);
	bool SetMicVol(FLOAT& value);
	FLOAT GetMicVol(FLOAT& value);
	bool SetSpeakerVol(FLOAT& value);
	FLOAT GetSpeakerVol(FLOAT& value);
	bool SelectMic(const wchar_t* deviceId, const wchar_t* deviceName);
	bool SelectSpeaker(const wchar_t* deviceId, const wchar_t* deviceName);
	bool IsAutoJoinAudioEnabled();
	bool IsAutoAdjustMicEnabled();
	bool IsStereoAudioEnable();
	bool IsMicOriginalInputEnable();
	bool IsHoldSpaceKeyToSpeakEnabled();
	bool IsAlwaysMuteMicWhenJoinVoipEnabled();
	bool IsSuppressAudioNotifyEnabled();
	///test audio device
	bool TestMicStartRecording(const wchar_t* deviceID = NULL);
	bool TestMicStopTesting();
	bool TestMicPlayRecording();
	bool TestSpeakerStartPlaying(const wchar_t* deviceID = NULL);
	bool TestSpeakerStopPlaying();
	bool SetTimerInterval(unsigned int timerInterval);
	virtual void OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume);
	virtual void OnNoAudioDeviceIsUseful(bool bMicOrSpk); 
	virtual void OnTestMicStatusChanged(ZOOM_SDK_NAMESPACE::SDK_TESTMIC_STATUS status,bool& bHandled); 
	virtual void OnSelectedAudioDeviceIsChanged();
	virtual void onComputerMicDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IMicInfo*>* pNewMicList);
	virtual void onComputerSpeakerDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ISpeakerInfo*>* pNewSpeakerList);

private:
	CSDKAudioSettingsUIEvent* m_pAudioSettingsUIEvent;
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	ZOOM_SDK_NAMESPACE::IAudioSettingContext* m_pAudioSettingContext;
	ZOOM_SDK_NAMESPACE::ITestAudioDeviceHelper* m_pTestAudioDeviceHelper;
};