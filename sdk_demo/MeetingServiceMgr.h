#pragma once

#include <windows.h>
#include <string>
#include "zoom_sdk.h"
#include "meeting_service_interface.h"
#include "setting_service_interface.h"
#include "DemoUI.h"
#include "PreMeetingServiceMgr.h"


class CMeetingServiceMgr : public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent
{
public:
	CMeetingServiceMgr();
	CMeetingServiceMgr(CDemoUI* pSkin);
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

public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);

	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath);

	virtual void onRecording2MP4Processing(int iPercentage);

	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL);

	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL);

	void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId);

	void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId);

	void onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL);

	void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status);

	void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc);
	void onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status);

private:
	CDemoUI* m_pSink;
	ZOOM_SDK_NAMESPACE::IMeetingService* m_pMeetingService;
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	std::wstring m_strCamera;
	bool m_bInited;
};