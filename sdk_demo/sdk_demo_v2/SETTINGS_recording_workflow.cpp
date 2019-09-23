#include "stdafx.h"
#include "SETTINGS_recording_workflow.h"
CSDKRecordingSettingsWorkFlow::CSDKRecordingSettingsWorkFlow()
{
	m_pSettingService = NULL;
	m_pRecordingSettingContext = NULL;
	Init();
}
CSDKRecordingSettingsWorkFlow::~CSDKRecordingSettingsWorkFlow()
{
	m_pSettingService = NULL;
	m_pRecordingSettingContext = NULL;
}
bool CSDKRecordingSettingsWorkFlow::Init()
{
	if(NULL == m_pSettingService)
	{
		m_pSettingService = SDKInterfaceWrap::GetInst().GetSettingService();
	}
	if(m_pSettingService)
	{
		m_pRecordingSettingContext = m_pSettingService->GetRecordingSettings();
	}
	if(NULL == m_pRecordingSettingContext)
	{
		return false;
	}
	return true;
}
bool CSDKRecordingSettingsWorkFlow::SetRecordingPath(const wchar_t* szPath)
{
	if(m_pRecordingSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pRecordingSettingContext->SetRecordingPath(szPath);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
const wchar_t* CSDKRecordingSettingsWorkFlow::GetRecordingPath()
{
	if(m_pRecordingSettingContext)
	{
		const wchar_t* Path = m_pRecordingSettingContext->GetRecordingPath();
		if(Path != NULL)
		{
			return Path;
		}
	}
	return NULL;
}