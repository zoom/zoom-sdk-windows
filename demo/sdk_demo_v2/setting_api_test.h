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
#include <shellapi.h>
#include "Shlobj.h"
#include <fstream>

class CSDKSettingApiTest
{
  public:
	  CSDKSettingApiTest();
	 ~CSDKSettingApiTest();

  private:
	  void WriteLogToFile( std::string &sLog);
	  void DoAllTest();
	  void Write(std::string &FuncName,ZOOM_SDK_NAMESPACE::SDKError &err);
      string GetSystemTime();

  private:
	  ofstream m_examplefile;
	  CSDKGeneralSettingsWorkFlow m_general_setting_workflow;
	  CSDKAudioSettingsWorkFlow m_audio_setting_workflow;
	  CSDKVideoSettingsWorkFlow m_video_setting_workflow;
	  CSDKRecordingSettingsWorkFlow m_recording_setting_workflow;
	  CSDKUICustomSettingsWorkFlow m_uicustom_setting_workflow;
	  CSDKFeatureCustomSettingsWorkFlow m_featurecustom_setting_workflow;
	  string StrTemp;
	  ZOOM_SDK_NAMESPACE::SDKError err;
};