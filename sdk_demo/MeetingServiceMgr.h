#pragma once

#include <windows.h>
#include <string>
#include "zoom_sdk.h"
#include "meeting_service_interface.h"
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
};

class CMeetingServiceMgr : public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent
{
public:
	CMeetingServiceMgr();
	CMeetingServiceMgr(IMeetingserviceMgrEvent* pSkin);
	virtual ~CMeetingServiceMgr();
	bool IsInMeeting(ZOOM_SDK_NAMESPACE::MeetingStatus status);

public:
	bool Init();
	bool UnInit();
	bool Start(ZOOM_SDK_NAMESPACE::StartParam& startParam);
	bool Join(ZOOM_SDK_NAMESPACE::JoinParam& joinParam);
	bool Leave();
	bool End();
	bool StartMonitorShare(const wchar_t* monitorID);
	bool StartAppShare(HWND hwndSharedApp);
	bool StopShare();
	bool MuteVideo();
	bool UnmuteVideo();
	bool PinVideo(bool bPin, bool bFirstView, unsigned int userid);
	bool MuteAudio(unsigned int userid);
	bool UnMuteAudio(unsigned int userid);
	ZOOM_SDK_NAMESPACE::IUserInfo* GetUserByUserID(unsigned int userid);

public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);

	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath);

	virtual void onRecording2MP4Processing(int iPercentage);

	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL);

	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL);

	virtual void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId);

	virtual void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId);
	virtual void onLockShareStatus(bool bLocked);

	virtual void onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL);

	virtual void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status);

	virtual void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc);
	virtual void onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status);
	virtual void onHostChangeNotification(unsigned int userId){};
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid){};
	virtual void onRecordPriviligeChanged(bool bCanRec){};
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid){}

private:
	IMeetingserviceMgrEvent* m_pSink;
	ZOOM_SDK_NAMESPACE::IMeetingService* m_pMeetingService;
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	std::wstring m_strCamera;
	bool m_bInited;
};