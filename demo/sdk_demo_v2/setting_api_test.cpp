#include "stdafx.h"
#include "setting_api_test.h"
#include "settings_ui.h"
#include <fstream>

CSDKSettingApiTest::CSDKSettingApiTest()
{
   //MessageBox(NULL,(LPCWSTR)L"一键测试所有接口",(LPCWSTR)L"测试",MB_DEFBUTTON1);
   //m_examplefile.open("D:\\Auto_TestAllFunction_Log.txt",ios::app);
   DoAllTest();
}

CSDKSettingApiTest::~CSDKSettingApiTest()
{
   if (m_examplefile.is_open())
   {
	   m_examplefile.close();
   }
	
}

string CSDKSettingApiTest::GetSystemTime()
{
    SYSTEMTIME m_time;
	GetLocalTime(&m_time);
	char szDateTime[100] = { 0 };
	sprintf(szDateTime, "%02d-%02d-%02d %02d:%02d:%02d", m_time.wYear, m_time.wMonth,
		m_time.wDay, m_time.wHour, m_time.wMinute, m_time.wSecond);
	string time(szDateTime);
	return time;
}

void CSDKSettingApiTest::WriteLogToFile(std::string &sLog)
{
	m_examplefile.open("D:\\Auto_TestAllFunction_Log.txt",ios::app);
	if (m_examplefile.is_open())
	{
		m_examplefile <<sLog.c_str()<<"\n";		
		m_examplefile.close();		
	}	
}
void CSDKSettingApiTest::DoAllTest()
{
	//setting_general---->FunctionTest

	err = m_general_setting_workflow.EnableDualScreenMode(true);
    StrTemp="m_general_setting_workflow.EnableDualScreenMode";
	Write(StrTemp,err);
	err = m_general_setting_workflow.EnableSplitScreenMode(true);
	StrTemp="m_general_setting_workflow.EnableSplitScreenMode";	
	Write(StrTemp,err);
	err = m_general_setting_workflow.TurnOffAeroModeInSharing(true);
	StrTemp="m_general_setting_workflow.TurnOffAeroModeInSharing";	
	Write(StrTemp,err);
	err = m_general_setting_workflow.EnableAutoFitToWindowWhenViewSharing(true);
	StrTemp="m_general_setting_workflow.EnableAutoFitToWindowWhenViewSharing";	
	Write(StrTemp,err);
	err = m_general_setting_workflow.EnableAutoFullScreenVideoWhenJoinMeeting(true);
	StrTemp="m_general_setting_workflow.EnableAutoFullScreenVideoWhenJoinMeeting";	
	Write(StrTemp,err);
	err = m_general_setting_workflow.EnableAutoFullScreenVideoWhenViewShare(true);
	StrTemp="m_general_setting_workflow.EnableAutoFullScreenVideoWhenViewShare";	
	Write(StrTemp,err);
	err = m_general_setting_workflow.EnableDisplayReminderWindowWhenExit(true);
	StrTemp="m_general_setting_workflow.EnableDisplayReminderWindowWhenExit";	
	Write(StrTemp,err);
	err = m_general_setting_workflow.EnableShowMyMeetingElapseTime(true);
	StrTemp="m_general_setting_workflow.EnableShowMyMeetingElapseTime";	
	Write(StrTemp,err);
	err = m_general_setting_workflow.EnableAccelerateGPUWhenShare(true);
	StrTemp="m_general_setting_workflow.EnableAccelerateGPUWhenShare";	
	Write(StrTemp,err);
	err = m_general_setting_workflow.EnableRemoteControlAllApplications(true);
	StrTemp="m_general_setting_workflow.EnableRemoteControlAllApplications";	
	Write(StrTemp,err);
	err = m_general_setting_workflow.EnableRemoteControlAllApplications(true);
	StrTemp="m_general_setting_workflow.EnableRemoteControlAllApplications";	
	Write(StrTemp,err);

	//setting_audio---->FunctionTest
    err = m_audio_setting_workflow.EnableAlwaysMuteMicWhenJoinVoip(true);
	StrTemp="m_audio_setting_workflow.EnableAlwaysMuteMicWhenJoinVoip";	
	Write(StrTemp,err);
	err = m_audio_setting_workflow.EnableAutoAdjustMic(true);
	StrTemp="m_audio_setting_workflow.EnableAutoAdjustMic";	
	Write(StrTemp,err);
    err = m_audio_setting_workflow.EnableAutoJoinAudio(true);
	StrTemp="m_audio_setting_workflow.EnableAutoAdjustMic";	
	Write(StrTemp,err);
	err = m_audio_setting_workflow.EnableHoldSpaceKeyToSpeak(true);
	StrTemp="m_audio_setting_workflow.EnableHoldSpaceKeyToSpeak";	
	Write(StrTemp,err);
	err = m_audio_setting_workflow.EnableMicOriginalInput(true);
	StrTemp="m_audio_setting_workflow.EnableMicOriginalInput";	
	Write(StrTemp,err);
	err = m_audio_setting_workflow.EnableStereoAudio(true);
	StrTemp="m_audio_setting_workflow.EnableStereoAudio";	
	Write(StrTemp,err);
    err = m_audio_setting_workflow.EnableSuppressAudioNotify(true);
	StrTemp="m_audio_setting_workflow.EnableSuppressAudioNotify";	
	Write(StrTemp,err);

	float volume=100; 
	err = m_audio_setting_workflow.SetMicVol(volume);
	StrTemp="m_audio_setting_workflow.SetMicVol";	
	Write(StrTemp,err);
    err = m_audio_setting_workflow.GetMicVol(volume);
	StrTemp="m_audio_setting_workflow.GetMicVol";	
	Write(StrTemp,err);
	err = m_audio_setting_workflow.SetSpeakerVol(volume);
	StrTemp="m_audio_setting_workflow.SetSpeakerVol";	
	Write(StrTemp,err);
	err = m_audio_setting_workflow.GetSpeakerVol(volume);
	StrTemp="m_audio_setting_workflow.GetSpeakerVol";	
	Write(StrTemp,err);
	err = m_audio_setting_workflow.EnableEchoCancellation(true);
	StrTemp="m_audio_setting_workflow.EnableEchoCancellation";	
	Write(StrTemp,err);

	//setting_vedio---->FunctionTest
	err = m_video_setting_workflow.EnableVideoMirrorEffect(true);
	StrTemp="m_video_setting_workflow.EnableVideoMirrorEffect";	
	Write(StrTemp,err);
	err = m_video_setting_workflow.EnableFaceBeautyEffect(true);
	StrTemp="m_video_setting_workflow.EnableFaceBeautyEffect";	
	Write(StrTemp,err);
	err = m_video_setting_workflow.EnableHDVideo(true);
	StrTemp="m_video_setting_workflow.EnableHDVideo";	
	Write(StrTemp,err);
	err = m_video_setting_workflow.EnableAlwaysShowNameOnVideo(true);
	StrTemp="m_video_setting_workflow.EnableAlwaysShowNameOnVideo";	
	Write(StrTemp,err);
	err = m_video_setting_workflow.EnableAutoTurnOffVideoWhenJoinMeeting(true);
	StrTemp="m_video_setting_workflow.EnableAutoTurnOffVideoWhenJoinMeeting";	
	Write(StrTemp,err);
	err = m_video_setting_workflow.EnableAlwaysUse16v9(true);
	StrTemp="m_video_setting_workflow.EnableAlwaysUse16v9";	
	Write(StrTemp,err);
	err = m_video_setting_workflow.EnableSpotlightSelf(true);
	StrTemp="m_video_setting_workflow.EnableSpotlightSelf";	
	Write(StrTemp,err);
	err = m_video_setting_workflow.EnableHardwareEncode(true);
	StrTemp="m_video_setting_workflow.EnableHardwareEncode";	
	Write(StrTemp,err);
	err = m_video_setting_workflow.Enable49VideoesInGallaryView(true);
	StrTemp="m_video_setting_workflow.Enable49VideoesInGallaryView";	
	Write(StrTemp,err);
	err = m_video_setting_workflow.EnableHideNoVideoUsersOnWallView(true);
	StrTemp="m_video_setting_workflow.EnableHideNoVideoUsersOnWallView";	
	Write(StrTemp,err);

	//setting_recording---->FunctionTest
	bool m_bEnable=true;
	err = m_recording_setting_workflow.CanGetRecordingManagementURL(m_bEnable);
	StrTemp="m_recording_setting_workflow.CanGetRecordingManagementURL";	
	Write(StrTemp,err);
	err = m_recording_setting_workflow.EnableSelectRecordFileLocationAfterMeeting(true);
	StrTemp="m_recording_setting_workflow.EnableSelectRecordFileLocationAfterMeeting";	
	Write(StrTemp,err);
	err = m_recording_setting_workflow.EnableMultiAudioStreamRecord(true);
	StrTemp="m_recording_setting_workflow.EnableMultiAudioStreamRecord";	
	Write(StrTemp,err);
	err = m_recording_setting_workflow.EnableAddTimestampWatermark(true);
	StrTemp="m_recording_setting_workflow.EnableAddTimestampWatermark";	
	Write(StrTemp,err);
	err = m_recording_setting_workflow.EnableOptimizeFor3rdPartyVideoEditor(true);
	StrTemp="m_recording_setting_workflow.EnableOptimizeFor3rdPartyVideoEditor";	
	Write(StrTemp,err);
	err = m_recording_setting_workflow.EnableShowVideoThumbnailWhenShare(true);
	StrTemp="m_recording_setting_workflow.EnableShowVideoThumbnailWhenShare";	
	Write(StrTemp,err);
	err = m_recording_setting_workflow.EnablePlaceVideoNextToShareInRecord(true);
	StrTemp="m_recording_setting_workflow.EnablePlaceVideoNextToShareInRecord";	
	Write(StrTemp,err);

	//setting_UICustom---->FunctionTest
	err = m_uicustom_setting_workflow.DisableTopMostAttr4SettingDialog(true);
	StrTemp="m_uicustom_setting_workflow.DisableTopMostAttr4SettingDialog";	
	Write(StrTemp,err);
	err = m_uicustom_setting_workflow.ShowSharingToolbar(true);
	StrTemp="m_uicustom_setting_workflow.ShowSharingToolbar";	
	Write(StrTemp,err);	
	err = m_uicustom_setting_workflow.ShowSharingFrameWindows(true);
	StrTemp="m_uicustom_setting_workflow.ShowSharingFrameWindows";	
	Write(StrTemp,err);

	//setting_FeatureCustom---->FunctionTest
    err = m_featurecustom_setting_workflow.EnableGrabShareWithoutReminder(true);	      
	StrTemp="m_featurecustom_setting_workflow.EnableGrabShareWithoutReminder";	
	Write(StrTemp,err);
	err = m_featurecustom_setting_workflow.ShowPreOrNextPageVideo(true);	      
	StrTemp="m_featurecustom_setting_workflow.ShowPreOrNextPageVideo";	
	Write(StrTemp,err);
	err = m_featurecustom_setting_workflow.SwitchSplitScreenMode(true);	      
	StrTemp="m_featurecustom_setting_workflow.SwitchSplitScreenMode";	
	Write(StrTemp,err);



}
void CSDKSettingApiTest::Write(std::string &FuncName,ZOOM_SDK_NAMESPACE::SDKError &err)
{
	string funcname=FuncName;
	string s_err;
	switch (err)
	{	//todo add more case
		case ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS : 
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_NO_IMPL:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_NO_IMPL";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_WRONG_USEAGE:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_WRONG_USEAGE";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_INVALID_PARAMETER:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_INVALID_PARAMETER";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_MODULE_LOAD_FAILED: 
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_MODULE_LOAD_FAILED";
            break;		
		case ZOOM_SDK_NAMESPACE::SDKERR_MEMORY_FAILED:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_MEMORY_FAILED";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_SERVICE_FAILED:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_SERVICE_FAILED";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_UNAUTHENTICATION:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_UNAUTHENTICATION";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_NORECORDINGINPROCESS:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_NORECORDINGINPROCESS";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_TRANSCODER_NOFOUND:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_TRANSCODER_NOFOUND";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_VIDEO_NOTREADY:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_VIDEO_NOTREADY";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_NO_PERMISSION:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_NO_PERMISSION";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_OTHER_SDK_INSTANCE_RUNNING:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_OTHER_SDK_INSTANCE_RUNNING";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_INTELNAL_ERROR:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_INTELNAL_ERROR";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_NO_AUDIODEVICE_ISFOUND:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_NO_AUDIODEVICE_ISFOUND";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_NO_VIDEODEVICE_ISFOUND:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_NO_VIDEODEVICE_ISFOUND";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_TOO_FREQUENT_CALL:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_TOO_FREQUENT_CALL";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_FAIL_ASSIGN_USER_PRIVILEGE:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_FAIL_ASSIGN_USER_PRIVILEGE";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_MEETING_DONT_SUPPORT_FEATURE:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_MEETING_DONT_SUPPORT_FEATURE";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_MEETING_NOT_SHARE_SENDER:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_MEETING_NOT_SHARE_SENDER";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_MEETING_YOU_HAVE_NO_SHARE:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_MEETING_YOU_HAVE_NO_SHARE";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_MEETING_VIEWTYPE_PARAMETER_IS_WRONG:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_MEETING_VIEWTYPE_PARAMETER_IS_WRONG";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_MEETING_ANNOTATION_IS_OFF:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_MEETING_ANNOTATION_IS_OFF";
			break;
		case ZOOM_SDK_NAMESPACE::SDKERR_SETTING_OS_DONT_SUPPORT:
			s_err = "ZOOM_SDK_NAMESPACE::SDKERR_SETTING_OS_DONT_SUPPORT";
			break;
 	}
	char Log[MAX_PATH] = {0};	
	sprintf(Log,"时间：%s----->函数名：%s------>传入参数true ------>返回值: %s",GetSystemTime().c_str(),funcname.c_str(),s_err.c_str());
	string s_Log = Log;
	WriteLogToFile(s_Log);
}