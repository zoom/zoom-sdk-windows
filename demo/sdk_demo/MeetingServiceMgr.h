#pragma once

#include <windows.h>
#include <string>
#include "zoom_sdk.h"
#include "meeting_service_interface.h"
#include "meeting_service_components/meeting_annotation_interface.h"
#include "meeting_service_components/meeting_audio_interface.h"
#include "meeting_service_components/meeting_breakout_rooms_interface.h"
#include "meeting_service_components/meeting_chat_interface.h"
#include "meeting_service_components/meeting_configuration_interface.h"
#include "meeting_service_components/meeting_h323_helper_interface.h"
#include "meeting_service_components/meeting_participants_ctrl_interface.h"
#include "meeting_service_components/meeting_phone_helper_interface.h"
#include "meeting_service_components/meeting_recording_interface.h"
#include "meeting_service_components/meeting_remote_ctrl_interface.h"
#include "meeting_service_components/meeting_sharing_interface.h"
#include "meeting_service_components/meeting_ui_ctrl_interface.h"
#include "meeting_service_components/meeting_video_interface.h"
#include "meeting_service_components/meeting_waiting_room_interface.h"
#include "customized_ui/customized_local_recording.h"
#include "setting_service_interface.h"

class IMeetingserviceMgrEvent
{
public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0) = 0;
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath) = 0;
	virtual void onRecording2MP4Processing(int iPercentage) = 0;
	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;
	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;
	virtual void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId) = 0;
	virtual void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId) = 0;
	virtual void onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL) = 0;
	virtual void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status) = 0;
	virtual void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc) = 0;
	virtual void onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status) = 0;
	virtual void onHostChangeNotification(unsigned int userId) = 0;
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid) = 0;
	virtual void onRecordPriviligeChanged(bool bCanRec) = 0;
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid) = 0;
	virtual void onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper) = 0;
};

class CMeetingServiceMgr : 
public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent,
public ZOOM_SDK_NAMESPACE::IMeetingAudioCtrlEvent,
public ZOOM_SDK_NAMESPACE::IMeetingChatCtrlEvent,
public ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent,
public ZOOM_SDK_NAMESPACE::IMeetingRecordingCtrlEvent,
public ZOOM_SDK_NAMESPACE::IMeetingRemoteCtrlEvent,
public ZOOM_SDK_NAMESPACE::IMeetingShareCtrlEvent,
public ZOOM_SDK_NAMESPACE::IMeetingVideoCtrlEvent,
public ZOOM_SDK_NAMESPACE::IMeetingUIControllerEvent
{
public:
	CMeetingServiceMgr();
	CMeetingServiceMgr(IMeetingserviceMgrEvent* pSkin);
	virtual ~CMeetingServiceMgr();
	bool IsInMeeting(ZOOM_SDK_NAMESPACE::MeetingStatus status);

	ZOOM_SDK_NAMESPACE::IMeetingService* GetSDKObj() { return m_pMeetingService; }

public:
	bool Init();
	bool UnInit();
	bool Start(ZOOM_SDK_NAMESPACE::StartParam& startParam);
	bool Join(ZOOM_SDK_NAMESPACE::JoinParam& joinParam);
	bool Leave();
	bool End();
	bool StartMonitorShare(const wchar_t* monitorID);
	bool StartWhiteBoardShare();
	bool StartAppShare(HWND hwndSharedApp);
	bool StopShare();
	bool MuteVideo();
	bool UnmuteVideo();
	bool PinVideo(bool bPin, bool bFirstView, unsigned int userid);
	bool MuteAudio(unsigned int userid);
	bool UnMuteAudio(unsigned int userid);
	ZOOM_SDK_NAMESPACE::IUserInfo* GetUserByUserID(unsigned int userid);

public:
	//IMeetingServiceEvent
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type){}
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler);
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param);

	//IMeetingParticipantsCtrlEvent
	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL);
	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL);
	virtual void onHostChangeNotification(unsigned int userId);
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid);
	virtual void onUserNameChanged(unsigned int userId, const wchar_t* userName);
	virtual void onCoHostChangeNotification(unsigned int userId, bool isCoHost){};

	//IMeetingRecordingCtrlEvent
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath);
	virtual void onRecording2MP4Processing(int iPercentage);
	virtual void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status);
	virtual void onCloudRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status){}
	virtual void onRecordPriviligeChanged(bool bCanRec);
	virtual void onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper);

	//IMeetingVideoCtrlEvent
	virtual void onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status);
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid);
	virtual void onHostRequestStartVideo(ZOOM_SDK_NAMESPACE::IRequestStartVideoHandler* handler_);
	virtual void onActiveSpeakerVideoUserChanged(unsigned int userid){};
	virtual void onActiveVideoUserChanged(unsigned int userid){};

	//IMeetingAudioCtrlEvent
	virtual void onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL);
	virtual void onUserActiveAudioChange(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstActiveAudioUser);
	virtual void onHostRequestStartAudio(ZOOM_SDK_NAMESPACE::IRequestStartAudioHandler* handler_) {}

	//IMeetingChatCtrlEvent
	virtual void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc);
	virtual void onChatStautsChangedNotification(ZOOM_SDK_NAMESPACE::ChatStatus* status_){}

	//IMeetingRemoteCtrlEvent
	virtual void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId);

	//IMeetingShareCtrlEvent
	virtual void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId);
	virtual void onLockShareStatus(bool bLocked);
	virtual void onShareContentNotification(ZOOM_SDK_NAMESPACE::ShareInfo& shareInfo);
	virtual void onMultiShareSwitchToSingleShareNeedConfirm(ZOOM_SDK_NAMESPACE::IShareSwitchMultiToSingleConfirmHandler* handler_);


	//IMeetingUIControllerEvent
	virtual void onInviteBtnClicked(bool& bHandled);
	virtual void onZoomInviteDialogFailed();
	virtual void onStartShareBtnClicked();
	virtual void onEndMeetingBtnClicked();
	virtual void onParticipantListBtnClicked();
	virtual void onCustomLiveStreamMenuClicked();
	virtual void onCCBTNClicked(){}
	virtual void onAudioBtnClicked(ZOOM_SDK_NAMESPACE::AudioBtnClickedCallbackInfo info) {}
	virtual void onAudioMenuBtnClicked() {}

private:
	IMeetingserviceMgrEvent* m_pSink;
	ZOOM_SDK_NAMESPACE::IMeetingService* m_pMeetingService;
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	std::wstring m_strCamera;
	bool m_bInited;
	ZOOM_SDK_NAMESPACE::IMeetingAudioController* m_pAudioCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingChatController* m_pChatCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingParticipantsController* m_pUserCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingRecordingController* m_pRecCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingRemoteController* m_pRemoteCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingShareController* m_pShareCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingVideoController* m_pVideoCtrl;
};