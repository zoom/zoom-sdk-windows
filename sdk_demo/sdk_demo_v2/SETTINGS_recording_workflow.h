#pragma once
#include "sdk_util.h"
#include "stdafx.h"
#include "setting_service_interface.h"

class CSDKRecordingSettingsWorkFlow
{
public:
	CSDKRecordingSettingsWorkFlow();
	virtual ~CSDKRecordingSettingsWorkFlow();
	bool Init();
	void Cleanup(){}
	bool SetRecordingPath(const wchar_t* szPath);
	const wchar_t* GetRecordingPath();
private:
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	ZOOM_SDK_NAMESPACE::IRecordingSettingContext* m_pRecordingSettingContext;
};