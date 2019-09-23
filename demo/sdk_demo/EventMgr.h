#pragma once

#include <windows.h>
#include "stdio.h"
#include <string>
#include "zoom_sdk.h"
#include "meeting_service_interface.h"
#include "auth_service_interface.h"
#include "setting_service_interface.h"
#include "premeeting_service_interface.h"
#include "meeting_phone_helper_interface.h"
#include "DemoUI.h"

class CDemoUISink
{
public:
	CDemoUISink();
	~CDemoUISink();
	void SetSink(CDemoUI* pSink);

public:
	CDemoUI* m_pSink;
};

class CMeetingPhoneHelperEvent : public ZOOM_SDK_NAMESPACE::IMeetingPhoneHelperEvent, public CDemoUISink
{
public:
	virtual void onInviteCallOutUserStatus(ZOOM_SDK_NAMESPACE::PhoneStatus status, ZOOM_SDK_NAMESPACE::PhoneFailedReason reason);

	virtual void onCallMeStatus(ZOOM_SDK_NAMESPACE::PhoneStatus status, ZOOM_SDK_NAMESPACE::PhoneFailedReason reason);
};

class CAuthServiceEvent : public ZOOM_SDK_NAMESPACE::IAuthServiceEvent, public CDemoUISink
{
public:
	/// \brief Authentication Result callback
	/// \param ret Authentication Result value. 
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);

	virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS status, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo);

	virtual void onLogout();
};

class CPreMeetingServiceEvent : public ZOOM_SDK_NAMESPACE::IPreMeetingServiceEvent, public CDemoUISink
{
public:
	virtual void onListMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, ZOOM_SDK_NAMESPACE::IList<UINT64 >* lstMeetingList);

	virtual void onScheduleOrEditMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, UINT64 meetingUniqueID);

	virtual void onDeleteMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result);
};

class CMeetingServiceEvent : public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent, public CDemoUISink
{
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
};

