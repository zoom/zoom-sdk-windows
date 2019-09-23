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
	virtual void onDefaultMicDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) = 0;
	virtual void onDefaultSpeakerDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) = 0;
};
class CSDKAudioSettingsWorkFlow:public ZOOM_SDK_NAMESPACE::ITestAudioDeviceHelperEvent,public ZOOM_SDK_NAMESPACE::IAudioSettingContextEvent
{
public:
	CSDKAudioSettingsWorkFlow();
	virtual ~CSDKAudioSettingsWorkFlow();
	ZOOM_SDK_NAMESPACE::SDKError Init();
	void Cleanup() {}
	void SetUIEvent(CSDKAudioSettingsUIEvent* event_);
	////audio setting context
	ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IMicInfo* >*  GetMicList();
	ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ISpeakerInfo* >* GetSpeakerList();
	ZOOM_SDK_NAMESPACE::SDKError EnableAutoJoinAudio(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableAutoAdjustMic(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableStereoAudio(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableMicOriginalInput(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableHoldSpaceKeyToSpeak(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableAlwaysMuteMicWhenJoinVoip(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableSuppressAudioNotify(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError SetMicVol(FLOAT& value);
	ZOOM_SDK_NAMESPACE::SDKError GetMicVol(FLOAT& value);
	ZOOM_SDK_NAMESPACE::SDKError SetSpeakerVol(FLOAT& value);
	ZOOM_SDK_NAMESPACE::SDKError GetSpeakerVol(FLOAT& value);
	ZOOM_SDK_NAMESPACE::SDKError SelectMic(const wchar_t* deviceId, const wchar_t* deviceName);
	ZOOM_SDK_NAMESPACE::SDKError SelectSpeaker(const wchar_t* deviceId, const wchar_t* deviceName);
	bool IsAutoJoinAudioEnabled();
	bool IsAutoAdjustMicEnabled();
	bool IsStereoAudioEnable();
	bool IsMicOriginalInputEnable();
	bool IsHoldSpaceKeyToSpeakEnabled();
	bool IsAlwaysMuteMicWhenJoinVoipEnabled();
	bool IsSuppressAudioNotifyEnabled();
	
	ZOOM_SDK_NAMESPACE::SDKError EnableEchoCancellation(bool bEnable);
	bool IsEchoCancellationEnabled();
	
	///test audio device
	ZOOM_SDK_NAMESPACE::SDKError TestMicStartRecording(const wchar_t* deviceID = NULL);
	ZOOM_SDK_NAMESPACE::SDKError TestMicStopTesting();
	ZOOM_SDK_NAMESPACE::SDKError TestMicPlayRecording();
	ZOOM_SDK_NAMESPACE::SDKError TestSpeakerStartPlaying(const wchar_t* deviceID = NULL);
	ZOOM_SDK_NAMESPACE::SDKError TestSpeakerStopPlaying();
	ZOOM_SDK_NAMESPACE::SDKError SetTimerInterval(unsigned int timerInterval);
	virtual void OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume);
	virtual void OnNoAudioDeviceIsUseful(bool bMicOrSpk); 
	virtual void OnTestMicStatusChanged(ZOOM_SDK_NAMESPACE::SDK_TESTMIC_STATUS status,bool& bHandled); 
	virtual void OnSelectedAudioDeviceIsChanged();
	virtual void onComputerMicDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IMicInfo*>* pNewMicList);
	virtual void onComputerSpeakerDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ISpeakerInfo*>* pNewSpeakerList);
	virtual void onDefaultMicDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) {}
	virtual void onDefaultSpeakerDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) {}

private:
	CSDKAudioSettingsUIEvent* m_pAudioSettingsUIEvent;
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	ZOOM_SDK_NAMESPACE::IAudioSettingContext* m_pAudioSettingContext;
	ZOOM_SDK_NAMESPACE::ITestAudioDeviceHelper* m_pTestAudioDeviceHelper;
};