/*!
* \file meeting_service_interface.h
* \brief Meeting Service Interface
* 
*/
#ifndef _MEETING_SERVICE_INTERFACE_H_
#define _MEETING_SERVICE_INTERFACE_H_
#include "zoom_sdk_def.h"
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum MeetingStatus
    \brief Meeting status code.
    A more detailed struct description.
*/
enum MeetingStatus
{
	MEETING_STATUS_IDLE,///< Idle status, no meeting running
	MEETING_STATUS_CONNECTING,///< Connecting meeting server status
	MEETING_STATUS_WAITINGFORHOST,///< Waiting for host to start meeting
	MEETING_STATUS_INMEETING,///< Meeting is ready, in meeting status
	MEETING_STATUS_DISCONNECTING,///< Disconnecting meeting server status
	MEETING_STATUS_RECONNECTING,///< Reconnecting meeting server status
	MEETING_STATUS_FAILED,///< Meeting connection error
	MEETING_STATUS_ENDED,///< Meeting is ended
	MEETING_STATUS_UNKNOW,
	MEETING_STATUS_LOCKED,
	MEETING_STATUS_UNLOCKED,
	MEETING_STATUS_IN_WAITING_ROOM,
	MEETING_STATUS_WEBINAR_PROMOTE,
	MEETING_STATUS_WEBINAR_DEPROMOTE,
	MEETING_STATUS_JOIN_BREAKOUT_ROOM,
	MEETING_STATUS_LEAVE_BREAKOUT_ROOM,
	MEETING_STATUS_WAITING_EXTERNAL_SESSION_KEY,
};

/*! \enum MeetingFailCode
    \brief Meeting fail code.
    A more detailed struct description.
*/
enum MeetingFailCode
{
	MEETING_SUCCESS							= 0,
	MEETING_FAIL_NETWORK_ERR				= 1,
	MEETING_FAIL_RECONNECT_ERR				= 2,
	MEETING_FAIL_MMR_ERR					= 3,
	MEETING_FAIL_PASSWORD_ERR				= 4,
	MEETING_FAIL_SESSION_ERR				= 5,
	MEETING_FAIL_MEETING_OVER				= 6,
	MEETING_FAIL_MEETING_NOT_START			= 7,
	MEETING_FAIL_MEETING_NOT_EXIST			= 8,
	MEETING_FAIL_MEETING_USER_FULL			= 9,
	MEETING_FAIL_CLIENT_INCOMPATIBLE		= 10,///< RESULT_ZC_INCOMPATIBLE
	MEETING_FAIL_NO_MMR						= 11,
	MEETING_FAIL_CONFLOCKED					= 12,
	MEETING_FAIL_MEETING_RESTRICTED			= 13,
	MEETING_FAIL_MEETING_RESTRICTED_JBH		= 14,
	MEETING_FAIL_CANNOT_EMIT_WEBREQUEST		= 15,
	MEETING_FAIL_CANNOT_START_TOKENEXPIRE	= 16,
	SESSION_VIDEO_ERR						= 17,
	SESSION_AUDIO_AUTOSTARTERR				= 18,
	MEETING_FAIL_REGISTERWEBINAR_FULL		= 19,
	MEETING_FAIL_REGISTERWEBINAR_HOSTREGISTER		= 20,
	MEETING_FAIL_REGISTERWEBINAR_PANELISTREGISTER	= 21,
	MEETING_FAIL_REGISTERWEBINAR_DENIED_EMAIL		= 22,
	MEETING_FAIL_ENFORCE_LOGIN		= 23,
	MEETING_FAIL_WRITE_CONFIG_FILE			= 50,	///< Failed to write configure file
	MEETING_FAIL_FORBID_TO_JOIN_INTERNAL_MEETING = 60,
};  

/*! \enum MeetingType
    \brief Meeting type.
    A more detailed struct description.
*/
enum MeetingType
{
	MEETING_TYPE_NONE,
	MEETING_TYPE_NORMAL,
	MEETING_TYPE_WEBINAR,
	MEETING_TYPE_BREAKOUTROOM,
};

/*! \enum LeaveMeetingCmd
    \brief Leave Meeting command.
    A more detailed struct description.
*/
enum LeaveMeetingCmd
{
	LEAVE_MEETING,///< Leave meeting
	END_MEETING,///< End meeting
};

/*! \enum SDKUserType
    \brief SDK User Type.
    A more detailed struct description.
*/
enum SDKUserType
{
	SDK_UT_APIUSER     = 99,///< API User type
	SDK_UT_NORMALUSER = 100,///< Normal user type
};

/*! \struct tagJoinParam4APIUser
    \brief Join meeting Parameter for API user.
    A more detailed struct description.
*/
typedef struct tagJoinParam4APIUser
{
	UINT64		   meetingNumber;///< Meeting's number
	const wchar_t* userName;///< User Name in meeting
	const wchar_t* psw;///< Meeting's password
	HWND		   hDirectShareAppWnd;///< share application directly
	const wchar_t* toke4enfrocelogin;///< enforce login when join meeting
	const wchar_t* participantId;///< for meeting participant report list, need web backend enable.
	const wchar_t* webinarToken;///< webinar token.
	bool		   isDirectShareDesktop;///< share desktop directly
	bool		   isVideoOff;
	bool		   isAudioOff;
}JoinParam4APIUser;

/*! \struct tagJoinParam4APIUser
    \brief Join meeting Parameter for API user.
    A more detailed struct description.
*/
typedef struct tagJoinParam4NormalUser
{
	UINT64		   meetingNumber;///< Meeting's number
	const wchar_t* userName;///< User Name in meeting
	const wchar_t* psw;///< Meeting's password
	HWND		   hDirectShareAppWnd;///< share application directly
	const wchar_t* participantId;///< for meeting participant report list, need web backend enable.
	const wchar_t* webinarToken;///< webinar token.
	bool		   isVideoOff;
	bool		   isAudioOff;
	bool		   isDirectShareDesktop;///< share desktop directly
}JoinParam4NormalUser;

/*! \struct tagJoinParam
    \brief Join meeting Parameter for API user.
    A more detailed struct description.
*/
typedef struct tagJoinParam
{
	SDKUserType userType;///< User type
	union 
	{
		JoinParam4APIUser apiuserJoin;
		JoinParam4NormalUser normaluserJoin;
	} param;    
	tagJoinParam()
	{
		userType = SDK_UT_APIUSER;
		memset(&param, 0, sizeof(param));
	}
}JoinParam;

/*! \struct tagStartParam4APIUser
    \brief Start meeting Parameter.
    A more detailed struct description.
*/
typedef struct tagStartParam4APIUser
{
	const wchar_t* userID;///< User Id
	const wchar_t* userToken;///< User token
	const wchar_t* userName;///< User name
	UINT64		   meetingNumber;///< Meeting's number
	HWND		   hDirectShareAppWnd;///< share application directly
	const wchar_t* participantId;///< for meeting participant report list, need web backend enable.
	bool		   isDirectShareDesktop;///< share desktop directly
}StartParam4APIUser;

/*! \struct tagStartParam4NormalUser
    \brief Start meeting Parameter.
    A more detailed struct description.
*/
typedef struct tagStartParam4NormalUser
{
	UINT64			meetingNumber;///< Meeting's number
	HWND			hDirectShareAppWnd;///< share application directly
	const wchar_t*  participantId;///< for meeting participant report list, need web backend enable.
	bool		    isVideoOff;///< only instance meeting take effect
	bool		    isAudioOff;///< only instance meeting take effect
	bool		    isDirectShareDesktop;///< share desktop directly
}StartParam4NormalUser;


/*! \struct tagJoinParam
    \brief Join meeting Parameter for API user.
    A more detailed struct description.
*/
typedef struct tagStartParam
{
	SDKUserType userType;///< User type
	union 
	{
		StartParam4APIUser apiuserStart;
		StartParam4NormalUser normaluserStart;
	} param;    
	tagStartParam()
	{
		userType = SDK_UT_APIUSER;
		memset(&param, 0, sizeof(param));
	}
}StartParam;

/*! \enum ConnectionQuality
    \brief Connection quality.
    A more detailed struct description.
*/
enum ConnectionQuality 
{
	Conn_Quality_Unknow,
	Conn_Quality_Very_Bad,
	Conn_Quality_Bad,
	Conn_Quality_Not_Good,
	Conn_Quality_Normal,
	Conn_Quality_Good,
	Conn_Quality_Excellent,
};

/*! \enum SDKViewType
    \brief SDK View Type, first monitor and second monitor.
    A more detailed struct description.
*/
enum SDKViewType
{
	SDK_FIRST_VIEW,
	SDK_SECOND_VIEW,
};

/*! \enum MeetingConnType
    \brief Meeting Connect Type
    A more detailed struct description.
*/
enum MeetingConnType
{
	Meeting_Conn_None,
	Meeting_Conn_Normal,
	Meeting_Conn_FailOver,
};

/// \brief Meeting information Interface
///
class IMeetingInfo
{
public:
	/// \brief Get meeting number
	/// \return the return value is current meeting number.
	virtual UINT64 GetMeetingNumber() = 0;

	/// \brief Get meeting id
	/// \return the return value is current meeting id.
	virtual const wchar_t* GetMeetingID() = 0;

	/// \brief Get meeting topic
	/// \return the return value is current meeting topic.
	virtual const wchar_t* GetMeetingTopic() = 0;

	/// \brief Get meeting type
	/// \return the return value is current meeting type.To get extended error information, refer to MeetingType enum
	virtual MeetingType GetMeetingType() = 0;

	/// \brief Get meeting invitation E-mail template.
	/// \return If the function succeeds, the return value is meeting invitation E-mail template.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetInviteEmailTeamplate() = 0;

	/// \brief Get meeting invitation E-mail title.
	/// \return If the function succeeds, the return value is meeting invitation E-mail title.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetInviteEmailTitle() = 0;

	/// \brief Get meeting invitation join url.
	/// \return If the function succeeds, the return value is meeting invitation join url.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetJoinMeetingUrl() = 0;

	/// \brief Get the tag of meeting host.
	/// \return If the function succeeds, the return value is the tag of meeting host.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetMeetingHostTag() = 0;

	/// \brief meeting is internal or not.
	/// \return if meeting is internal or not.
	virtual bool IsInternalMeeting() = 0;

	/// \brief Get meeting connect type.
	/// \return Meeting connect type
	virtual MeetingConnType GetMeetingConnType() = 0;

	virtual ~IMeetingInfo(){};
};

/// \brief Meeting external secure key handler
///
class IMeetingExternalSecureKeyHandler
{
public:
	/// \brief Set new secure key and iv of Chat session
	virtual void SetChatSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;
	
	/// \brief Set new secure key and iv of FileTransfer session
	virtual void SetFileTransferSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \brief Set new secure key and iv of Audio session
	virtual void SetAudioSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \brief Set new secure key and iv of Video session
	virtual void SetVideoSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \brief Set new secure key and iv of Share session
	virtual void SetShareSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \brief leave meeting
	virtual void Cancel() = 0;

	/// \brief continue to join/start meeting
	virtual void Confirm() = 0;

	virtual ~IMeetingExternalSecureKeyHandler() {};
};

/*! \enum StatisticsWarningType
    \brief Meeting statistics warning type.
    A more detailed struct description.
*/
enum StatisticsWarningType
{
	Statistics_Warning_None,
	Statistics_Warning_Network_Quality_Bad,
};

/// \brief Meeting Service Callback Event
///
class IMeetingServiceEvent
{
public:
	/// \brief Meeting status changed callback
	/// \param status Meeting status value.
	/// \param iResult details reason for special meeting status.
	/// if status is MEETING_STATUS_FAILED, the value of iResult is one of MeetingFailCode enum. 
	virtual void onMeetingStatusChanged(MeetingStatus status, int iResult = 0) = 0;

	/// \brief Meeting statistics warning notification callback
	/// \param type The type of meeting statistics warning.
	virtual void onMeetingStatisticsWarningNotification(StatisticsWarningType type) = 0;
	
	/// \brief Meeting secure key notification, need to web backend and special account type support.
	/// \param key the secure key of current meeting.
	/// \param len the length of secure key.
	/// \param pHandler the handler to set external secure key or leave meeting.
	virtual void onMeetingSecureKeyNotification(const char* key, int len, IMeetingExternalSecureKeyHandler* pHandler) = 0;
};

class IAnnotationController;
class IMeetingAudioController;
class IMeetingBreakoutRoomsController;
class IMeetingChatController;
class IMeetingConfiguration;
class IMeetingH323Helper;
class IMeetingParticipantsController;
class IMeetingPhoneHelper;
class IMeetingRecordingController;
class IMeetingRemoteController;
class IMeetingShareController;
class IMeetingUIController;
class IMeetingVideoController;
class IMeetingWaitingRoomController;
/// \brief Meeting Service Interface
///
class IMeetingService
{
public:
	/// \brief Set meeting service callback event
	/// \param pEvent A pointer to a IMeetingServiceEvent* that receives meeting event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingServiceEvent* pEvent) = 0;

	/// \brief Join meeting
	/// \param joinParam The parameter to be used for join meeting, refer to JoinParam. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Join(JoinParam& joinParam) = 0;

	/// \brief Start meeting
	/// \param startParam The parameter to be used for start meeting, refer to StartParam. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Start(StartParam& startParam) = 0;

	/// \brief Leave meeting
	/// \param leaveCmd Leave meeting command, refer to LeaveMeetingCmd. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Leave(LeaveMeetingCmd leaveCmd) = 0;

	/// \brief Get meeting status
	/// \return the return value is current meeting status.To get extended error information, refer to MeetingStatus enum
	virtual MeetingStatus GetMeetingStatus() = 0;
	/// \brief Lock current meeting
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LockMeeting() = 0;

	/// \brief Unlock current meeting
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError UnlockMeeting() = 0;

	/// \brief Get meeting locked status
	/// \return locked status of current meeting.
	virtual bool IsMeetingLocked() = 0;

	// \brief Get meeting information.
	/// \return If the function succeeds, the return value is the meeting information, otherwise is NULL.
	virtual IMeetingInfo* GetMeetingInfo() = 0;

	/// \brief Get sharing connection quality.
	/// \param bSending if true, will return sending status, otherwise, will return receiving status.
	/// \return If the function succeeds, the return value is ConnectionQuality enum value.
	/// \if you don't in meeting, will return Conn_Quality_Unknow
	virtual ConnectionQuality GetSharingConnQuality(bool bSending = true) = 0;

	/// \brief Get video connection quality.
	/// \param bSending if true, will return sending status, otherwise, will return receiving status.
	/// \return If the function succeeds, the return value is ConnectionQuality enum value.
	/// \if you don't in meeting, will return Conn_Quality_Unknow
	virtual ConnectionQuality GetVideoConnQuality(bool bSending = true) = 0;

	/// \brief Get audio connection quality.
	/// \param bSending if true, will return sending status, otherwise, will return receiving status.
	/// \return If the function succeeds, the return value is ConnectionQuality enum value.
	/// \if you don't in meeting, will return Conn_Quality_Unknow
	virtual ConnectionQuality GetAudioConnQuality(bool bSending = true) = 0;

	/// \brief Get meeting configuration interface.
	/// \return If the function succeeds, the return value is meeting configuration interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingConfiguration* GetMeetingConfiguration() = 0;

	/// \brief Get meeting UI controller
	/// \return If the function succeeds, the return value is meeting ui controller interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingUIController* GetUIController() = 0;

	/// \brief Get annotation controller
	/// \return If the function succeeds, the return value is annotation controller interface.
	///If the function fails, the return value is NULL.
	virtual IAnnotationController* GetAnnotationController() = 0;

	/// \brief Get video controller
	/// \return If the function succeeds, the return value is video controller interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingVideoController* GetMeetingVideoController() = 0;

	/// \brief Get remote controller object
	/// \return If the function succeeds, the return value is remote controller interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingRemoteController* GetMeetingRemoteController() = 0;

	/// \brief Get share controller
	/// \return If the function succeeds, the return value is remote controller interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingShareController* GetMeetingShareController() = 0;

	/// \brief Get audio controller
	/// \return If the function succeeds, the return value is audio controller interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingAudioController* GetMeetingAudioController() = 0;

	/// \brief Get recording controller
	/// \return If the function succeeds, the return value is audio controller interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingRecordingController* GetMeetingRecordingController() = 0;

	/// \brief Get chat controller
	/// \return If the function succeeds, the return value is audio controller interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingChatController* GetMeetingChatController() = 0;

	/// \brief Get waiting room controller
	/// \return If the function succeeds, the return value is audio controller interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingWaitingRoomController* GetMeetingWaitingRoomController() = 0;
	
	/// \brief Get meeting H323 helper
	/// \return If the function succeeds, the return value is meeting H323 helper interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingH323Helper* GetH323Helper() = 0;

	/// \brief Get meeting phone helper
	/// \return If the function succeeds, the return value is meeting phone helper interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingPhoneHelper* GetMeetingPhoneHelper() = 0;

	/// \brief Get Breakout Rooms controller
	/// \return If the function succeeds, the return value is Breakout Rooms controller interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingBreakoutRoomsController* GetMeetingBreakoutRoomsController() = 0;

	/// \brief Get Participants controller
	/// \return If the function succeeds, the return value is participants controller interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingParticipantsController* GetMeetingParticipantsController() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif