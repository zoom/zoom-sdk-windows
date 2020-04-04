/*!
* \file meeting_service_interface.h
* \brief Meeting Service Interface
* 
*/
#ifndef _MEETING_SERVICE_INTERFACE_H_
#define _MEETING_SERVICE_INTERFACE_H_
#include "zoom_sdk_def.h"
class IZoomRealNameAuthMeetingHelper;

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum MeetingStatus
    \brief Meeting status.
    Here are more detailed structural descriptions.
*/
enum MeetingStatus
{
	MEETING_STATUS_IDLE,///<No meeting is running.
	MEETING_STATUS_CONNECTING,///<Connect to the meeting server status.
	MEETING_STATUS_WAITINGFORHOST,///<Waiting for the host to start the meeting.
	MEETING_STATUS_INMEETING,///<Meeting is ready, in meeting status.
	MEETING_STATUS_DISCONNECTING,///<Disconnect the meeting server, leave meeting status.
	MEETING_STATUS_RECONNECTING,///<Reconnecting meeting server status.
	MEETING_STATUS_FAILED,///<Failed to connect the meeting server.
	MEETING_STATUS_ENDED,///<Meeting ends.
	MEETING_STATUS_UNKNOW,///<Unknown status.
	MEETING_STATUS_LOCKED,///<Meeting is locked to prevent the further participants to join the meeting.
	MEETING_STATUS_UNLOCKED,///<Meeting is open and participants can join the meeting. 
	MEETING_STATUS_IN_WAITING_ROOM,///<Participants who join the meeting before the start are in the waiting room.
	MEETING_STATUS_WEBINAR_PROMOTE,///<Upgrade the attendees to panelist in webinar.
	MEETING_STATUS_WEBINAR_DEPROMOTE,///<Downgrade the attendees from the panelist.
	MEETING_STATUS_JOIN_BREAKOUT_ROOM,///<Join the breakout room.
	MEETING_STATUS_LEAVE_BREAKOUT_ROOM,///<Leave the breakout room.
	MEETING_STATUS_WAITING_EXTERNAL_SESSION_KEY,///<Waiting for the additional secret key.
};

/*! \enum MeetingFailCode.
    \brief Meeting failure code.
    Here are more detailed structural descriptions.
*/
enum MeetingFailCode
{
	MEETING_SUCCESS							= 0,///<Start meeting successfully.
	MEETING_FAIL_NETWORK_ERR				= 1,///<Network error.
	MEETING_FAIL_RECONNECT_ERR				= 2,///<Reconnect error.
	MEETING_FAIL_MMR_ERR					= 3,///<Multi-media Router error.
	MEETING_FAIL_PASSWORD_ERR				= 4,///<Password is wrong.
	MEETING_FAIL_SESSION_ERR				= 5,///<Session error.
	MEETING_FAIL_MEETING_OVER				= 6,///<Meeting is over.
	MEETING_FAIL_MEETING_NOT_START			= 7,///<Meeting has not begun.
	MEETING_FAIL_MEETING_NOT_EXIST			= 8,///<Meeting does not exist.
	MEETING_FAIL_MEETING_USER_FULL			= 9,///<The capacity of meeting is full.
	MEETING_FAIL_CLIENT_INCOMPATIBLE		= 10,///<The client is incompatible.
	MEETING_FAIL_NO_MMR						= 11,///<The Multi-media router is not founded. 
	MEETING_FAIL_CONFLOCKED					= 12,///<The meeting is locked.
	MEETING_FAIL_MEETING_RESTRICTED			= 13,///<The meeting is failed because of the restriction by the same account.
	MEETING_FAIL_MEETING_RESTRICTED_JBH		= 14,///<The meeting is restricted by the same account while the attendee is allowed to join before the host.
	MEETING_FAIL_CANNOT_EMIT_WEBREQUEST		= 15,///<Unable to send web request.
	MEETING_FAIL_CANNOT_START_TOKENEXPIRE	= 16,///The token is expired.
	SESSION_VIDEO_ERR						= 17,///<Video hardware or software error.
	SESSION_AUDIO_AUTOSTARTERR				= 18,///<Audio autostart error.
	MEETING_FAIL_REGISTERWEBINAR_FULL		= 19,///<The number of webinar registered has reached the upper limit.
	MEETING_FAIL_REGISTERWEBINAR_HOSTREGISTER		= 20,///<Register webinar with the role of webinar host.
	MEETING_FAIL_REGISTERWEBINAR_PANELISTREGISTER	= 21,///<Register webinar with the role of panelist member.
	MEETING_FAIL_REGISTERWEBINAR_DENIED_EMAIL		= 22,///<Register webinar with the denied email.
	MEETING_FAIL_ENFORCE_LOGIN		= 23,///<Webinar request to login.
	CONF_FAIL_ZC_CERTIFICATE_CHANGED		= 24,  ///<Invalid for Windows SDK.
	CONF_FAIL_VANITY_NOT_EXIST				= 27, ///<Vanity conference ID does not exist.
	CONF_FAIL_JOIN_WEBINAR_WITHSAMEEMAIL		= 28, ///<Join webinar with the same email.
	CONF_FAIL_DISALLOW_HOST_MEETING		= 29, ///<Meeting settings is not allowed to start a meeting.
	MEETING_FAIL_WRITE_CONFIG_FILE			= 50,	///<Disabled to write the configure file.
	MEETING_FAIL_FORBID_TO_JOIN_INTERNAL_MEETING = 60, ///<Forbidden to join the internal meeting.
	CONF_FAIL_REMOVED_BY_HOST = 61, ///<Removed by the host. 
};  

/*! \enum MeetingEndReason
    \brief Meeting end reason.
    Here are more detailed structural descriptions.
*/
enum MeetingEndReason
{
	EndMeetingReason_None = 0,///<For initialization.
	EndMeetingReason_KickByHost = 1,///<Kicked by host.
	EndMeetingReason_EndByHost = 2,///<Ended by host.
	EndMeetingReason_JBHTimeOut = 3,///<JBH times out.
	EndMeetingReason_NoAttendee = 4,///<No attendee.
	EndMeetingReason_HostStartAnotherMeeting = 5,///<Host starts another meeting.
	EndMeetingReason_FreeMeetingTimeOut = 6,///<Free meeting times out.
	EndMeetingReason_NetworkBroken,///<Network is broken.
};

/*! \enum MeetingType
    \brief Meeting type.
    Here are more detailed structural descriptions.
*/
enum MeetingType
{
	MEETING_TYPE_NONE,///<For initialization.
	MEETING_TYPE_NORMAL,///<Ordinary meeting.
	MEETING_TYPE_WEBINAR,///<Webinar.
	MEETING_TYPE_BREAKOUTROOM,///<Breakout meeting.
};

/*! \enum LeaveMeetingCmd
    \brief Leave meeting command.
    Here are more detailed structural descriptions.
*/
enum LeaveMeetingCmd
{
	LEAVE_MEETING,///<Leave meeting
	END_MEETING,///<End meeting
};

/*! \enum SDKUserType
    \brief SDK user type.
    Here are more detailed structural descriptions.
*/
enum SDKUserType
{
	SDK_UT_APIUSER     = 99,///<API user type, quits later.
	SDK_UT_NORMALUSER = 100,///<Type of ordinary user who needs to login.
	SDK_UT_WITHOUT_LOGIN,///<Start meeting without login.
};

/*! \struct tagJoinParam4APIUser
    \brief The parameter of API user when joins the meeting.
    Here are more detailed structural descriptions.
*/
typedef struct tagJoinParam4APIUser
{
	UINT64		   meetingNumber;///< Meeting number.
	const wchar_t* vanityID;///<Meeting vanity ID
	const wchar_t* userName;///<Username when logged in the meeting.
	const wchar_t* psw;///<Meeting password.
	HWND		   hDirectShareAppWnd;///<The window handle of the direct Sharing application.
	const wchar_t* toke4enfrocelogin;///<Use the token if the meeting requests to login.
	const wchar_t* participantId;///<The ID of attendees. The SDK will set this value when the associated settings are turned on.
	const wchar_t* webinarToken;///<Webinar token.
	bool		   isDirectShareDesktop;///<Share the desktop directly or not. True indicates to Share.
	bool		   isVideoOff;///<Turn off the video of not. True indicates to turn off. In addition, this flag is affected by meeting attributes.
	bool		   isAudioOff;///<Turn off the audio or not. True indicates to turn off. In addition, this flag is affected by meeting attributes.
}JoinParam4APIUser;

/*! \struct tagJoinParam4WithoutLogin
    \brief The parameters of non-login user when joins the meeting.
    Here are more detailed structural descriptions.
*/
typedef struct tagJoinParam4WithoutLogin : public tagJoinParam4APIUser
{
}JoinParam4WithoutLogin;

/*! \struct tagJoinParam4APIUser
    \brief The parameter of ordinary logged-in user.
    Here are more detailed structural descriptions.
*/
typedef struct tagJoinParam4NormalUser
{
	UINT64		   meetingNumber;///<Meeting number.
	const wchar_t* vanityID;///<Meeting vanity ID.
	const wchar_t* userName;///<Username when logged in the meeting.
	const wchar_t* psw;///<Meeting password.
	HWND		   hDirectShareAppWnd;///<The window handle of the direct sharing application.
	const wchar_t* participantId;///<The ID of attendees. The SDK will set this value when the associated settings are turned on.
	const wchar_t* webinarToken;///<Webinar token.
	bool		   isVideoOff;///<Turn off the video or not. True indicates to turn off. In addition, this flag is affected by meeting attributes.
	bool		   isAudioOff;///<Turn off the audio or not. True indicates to turn off. In addition, this flag is affected by meeting attributes.
	bool		   isDirectShareDesktop;///<Share the desktop directly or not. True indicates to Share.
}JoinParam4NormalUser;

/*! \struct tagJoinParam
    \brief The way and the parameter of the users when join the meeting.
    Here are more detailed structural descriptions.
*/
typedef struct tagJoinParam
{
	SDKUserType userType;///<User type. For more details, see \link SDKUserType \endlink enum.
	union 
	{
		JoinParam4APIUser apiuserJoin;///<The parameter of API user when joins the meeting.
		JoinParam4NormalUser normaluserJoin;///<The parameter of ordinary user when joins the meeting.
		JoinParam4WithoutLogin withoutloginuserJoin;///<The parameters of unlogged-in user when joins the meeting.
	} param;    
	tagJoinParam()
	{
		userType = SDK_UT_APIUSER;
		memset(&param, 0, sizeof(param));
	}
}JoinParam;

/*! \struct tagStartParam4APIUser
    \brief The parameter used by API user when starts the meeting.
    Here are more detailed structural descriptions.
*/
typedef struct tagStartParam4APIUser
{
	const wchar_t* userID;///<User ID.
	const wchar_t* userToken;///<User token
	const wchar_t* userName;///<Username when logged in.
	UINT64		   meetingNumber;///<Meeting number.
	const wchar_t* vanityID;///<Meeting vanity ID.
	HWND		   hDirectShareAppWnd;///<The window handle of the direct sharing application.
	const wchar_t* participantId;///<The ID of attendees. The SDK will set this value when the associated settings are turned on.
	bool		   isDirectShareDesktop;///<Share the desktop directly or not. True indicates to Share.
	bool		   isVideoOff;///<Turn off the video or not. True indicates to turn off. In addition, this flag is affected by meeting attributes.
	bool		   isAudioOff;///<Turn off the audio or not. True indicates to turn off. In addition, this flag is affected by meeting attributes.
}StartParam4APIUser;


/*! \enum ZoomUserType
    \brief SDK user type.
    Here are more detailed structural descriptions.
*/
enum ZoomUserType
{
	ZoomUserType_APIUSER,///<API user.
	ZoomUserType_EMAIL_LOGIN,///<User logged in with email.
	ZoomUserType_FACEBOOK,///<User logged in with Facebook.
	ZoomUserType_GoogleOAuth,///<User logged in with Google.
	ZoomUserType_SSO,///<User logged in with SSO.
	ZoomUserType_Unknown,///<User of unknown type.
};

/*! \struct tagStartParam4WithoutLogin
    \brief The parameter used by unlogged-in user when starts the meeting.
    Here are more detailed structural descriptions.
*/
typedef struct tagStartParam4WithoutLogin
{
	const wchar_t* userID;///<User ID.
	const wchar_t* userToken;///<User token.
	const wchar_t* userZAK;///<ZOOM access token.
	const wchar_t* userName;///<Username when logged in the meeting.
	ZoomUserType   zoomuserType;///<User type.
	UINT64		   meetingNumber;///<Meeting number.
	const wchar_t* vanityID;///< Meeting vanity ID
	HWND		   hDirectShareAppWnd;///<The window handle of the direct sharing application.
	const wchar_t* participantId;///<The ID of attendees. The SDK will set this value when the associated settings are turned on.
	bool		   isDirectShareDesktop;///<Share the desktop directly or not. True indicates to share.
	bool		   isVideoOff;///<Turn off the video or not. True indicates to turn off. In addition, this flag is affected by meeting attributes.
	bool		   isAudioOff;///<Turn off the audio or not. True indicates to turn off. In addition, this flag is affected by meeting attributes.
}StartParam4WithoutLogin;

/*! \struct tagStartParam4NormalUser
    \brief The parameter of ordinary user when starts meeting.
    Here are more detailed structural descriptions.
*/
typedef struct tagStartParam4NormalUser
{
	UINT64			meetingNumber;///<Meeting number.
	const wchar_t*  vanityID;///<Meeting vanity ID. Generate a ZOOM access token via REST API.
	HWND			hDirectShareAppWnd;///<The window handle of the direct sharing application.
	const wchar_t*  participantId;///<The ID of attendees. The SDK will set this value when the associated settings are turned on.
	bool		    isVideoOff;///<Turn off video or not. True indicates to turn off. In addition, this flag is affected by meeting attributes.
	bool		    isAudioOff;///<Turn off audio or not. True indicates to turn off. In addition, this flag is affected by meeting attributes.
	bool		    isDirectShareDesktop;///<Share the desktop directly or not. True indicates to Share.
}StartParam4NormalUser;


/*! \struct tagJoinParam
    \brief The way and the parameter for meeting start.
    Here are more detailed structural descriptions.
*/
typedef struct tagStartParam
{
	SDKUserType userType;///<User type.
	union 
	{
		StartParam4APIUser apiuserStart;///<The parameter for API user when starts the meeting.
		StartParam4NormalUser normaluserStart;///<The parameter for ordinary user when starts the meeting.
	StartParam4WithoutLogin withoutloginStart;///<The parameter for unlogged-in user when starts the meeting. 
	}param;    
	tagStartParam()
	{
		userType = SDK_UT_APIUSER;
		memset(&param, 0, sizeof(param));
	}
}StartParam;

/*! \enum ConnectionQuality
    \brief Connection quality.
    Here are more detailed structural descriptions.
*/
enum ConnectionQuality 
{
	Conn_Quality_Unknow,///<Unknown connection status
	Conn_Quality_Very_Bad,///<The connection quality is very poor.
	Conn_Quality_Bad,///<The connection quality is poor. 
	Conn_Quality_Not_Good,///<The connection quality is not good.
	Conn_Quality_Normal,///<The connection quality is normal.
	Conn_Quality_Good,///<The connection quality is good.
	Conn_Quality_Excellent,///<The connection quality is excellent.
};

/*! \enum SDKViewType
    \brief SDK View Type, primary displayer and secondary displayer.
    Here are more detailed structural descriptions.
*/
enum SDKViewType
{
	SDK_FIRST_VIEW,///Primary displayer.
	SDK_SECOND_VIEW,///<Secondary displayer.
};

/*! \enum MeetingConnType
    \brief Meeting connection type.
    Here are more detailed structural descriptions.
*/
enum MeetingConnType
{
	Meeting_Conn_None,///<Disconnection.
	Meeting_Conn_Normal,///<Normal connection.
	Meeting_Conn_FailOver,///<Failure and reconnection.
};

/// \brief Meeting information Interface.
///
class IMeetingInfo
{
public:
	/// \brief Get the current meeting number.
	/// \return If the function succeeds, the return value is the current meeting number. Otherwise returns ZERO(0).
	virtual UINT64 GetMeetingNumber() = 0;

	/// \brief Get the current meeting ID.
	/// \return If the function succeeds, the return value is the current meeting ID. Otherwise returns an empty string of length ZERO(0).
	virtual const wchar_t* GetMeetingID() = 0;
	
	/// \brief Get the meeting topic.
	/// \return If the function succeeds, the return value is the current meeting topic. Otherwise returns an empty string of length ZERO(0)
	virtual const wchar_t* GetMeetingTopic() = 0;

	/// \brief Get the meeting password.
	/// \return If the function succeeds, the return value is the current meeting password. Otherwise returns an empty string of length ZERO(0)
	virtual const wchar_t* GetMeetingPassword() = 0;

	/// \brief Get the meeting type.
	/// \return If the function succeeds, the return value is the current meeting type. To get extended error information, see \link MeetingType \endlink enum.
	virtual MeetingType GetMeetingType() = 0;

	/// \brief Get the email invitation template for the current meeting.
	/// \return If the function succeeds, the return value is the email invitation template. Otherwise returns NULL.
	virtual const wchar_t* GetInviteEmailTeamplate() = 0;

	/// \brief Get the meeting title in the email invitation template.
	/// \return If the function succeeds, the return value is the meeting title. Otherwise returns NULL.
	virtual const wchar_t* GetInviteEmailTitle() = 0;

	/// \brief Get the URL of invitation to join the meeting.
	/// \return If the function succeeds, the return value is the URL of invitation. Otherwise returns NULL.
	virtual const wchar_t* GetJoinMeetingUrl() = 0;

	/// \brief Get the host tag of the current meeting.
	/// \return If the function succeeds, the return value is the host tag. Otherwise returns NULL.
	virtual const wchar_t* GetMeetingHostTag() = 0;

	/// \brief Determine whether the current meeting is internal or not.
	/// \return TRUE indicates that the current meeting is internal.
	virtual bool IsInternalMeeting() = 0;

	/// \brief Get the connection type of the current meeting.
	/// \return The connection type. For more details, see \link MeetingConnType \endlink enum.
	virtual MeetingConnType GetMeetingConnType() = 0;

	virtual ~IMeetingInfo(){};
};

/*! \struct tagMeetingParameter
    \brief Meeting parameter.
    Here are more detailed structural descriptions.
*/
typedef struct tagMeetingParameter
{
	MeetingType meeting_type;///<Meeting type.
	bool is_view_only;///<View only or not. True indicates to view only.
	UINT64 meeting_number;///<Meeting number.
	const wchar_t* meeting_topic;///<Meeting topic.
	const wchar_t* meeting_host;///<Meeting host.
	tagMeetingParameter()
	{
		meeting_type = MEETING_TYPE_NONE;
		is_view_only = true;
		meeting_number = 0;
		meeting_topic = NULL;
		meeting_host = NULL;
	}

	~tagMeetingParameter()
	{
		if (meeting_host)
		{
			delete[] meeting_host;
			meeting_host = NULL;
		}
		if (meeting_topic)
		{
			delete[] meeting_topic;
			meeting_topic = NULL;
		}
	}
}MeetingParameter;

/// \brief Meeting external secure key handler.
///
class IMeetingExternalSecureKeyHandler
{
public:
	/// \brief Set a new secure key and IV for Chat session.
	/// \param key The new secure key.
	/// \param key_len The length of the key.
	/// \param iv The new iv.
	/// \param iv_len The length of IV.
	virtual void SetChatSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;
	
	/// \brief Set a new secure key and IV for FileTransfer session.
	/// \param key The new secure key.
	/// \param key_len The length of the key.
	/// \param iv The new IV.
	/// \param iv_len The length of IV. 
	virtual void SetFileTransferSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \brief Set a new secure key and IV for Audio session.
	/// \param key The new secure key.
	/// \param key_len The length of the key.
	/// \param iv The new IV.
	/// \param iv_len The length of IV.
	virtual void SetAudioSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \brief Set a new secure key and IV for Video session.
	/// \param key The new secure key.
	/// \param key_len The length of the key.
	/// \param iv The new IV.
	/// \param iv_len The length of IV.
	virtual void SetVideoSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \brief Set a new secure key and IV for Sharing session.
	/// \param key The new secure key.
	/// \param key_len The length of the key.
	/// \param iv The new IV.
	/// \param iv_len The length of IV.
	virtual void SetShareSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \brief Leave meeting without setting the new secure key or IV.
	virtual void Cancel() = 0;

	/// \brief Re-verify with the new secure key.
	virtual void Confirm() = 0;

	virtual ~IMeetingExternalSecureKeyHandler() {};
};

/*! \enum StatisticsWarningType
    \brief Meeting statistics warning type.
    Here are more detailed structural descriptions.
*/
enum StatisticsWarningType
{
	Statistics_Warning_None,///<No warning.
	Statistics_Warning_Network_Quality_Bad,///<The network connection quality is bad.
	Statistics_Warning_Busy_System,///<The system is busy.
};

/*! \enum OSSessionType
    \brief OS session type.
    Here are more detailed structural descriptions.
*/
enum OSSessionType
{
	OS_SessionType_NotHandle = 0,
	OS_SessionType_Lock, ///<equals to WTS_SESSION_LOCK
	OS_SessionType_Logoff,///<equals to WTS_SESSION_LOGOFF
	OS_SessionType_Remote_DISCONNECT,///<equals to WTS_REMOTE_DISCONNECT
};
/// \brief Meeting service callback event.
///
class IMeetingServiceEvent
{
public:
	/// \brief Meeting status changed callback.
	/// \param status The value of meeting. For more details, see \link MeetingStatus \endlink.
	/// \param iResult Detailed reasons for special meeting status.
	///If the status is MEETING_STATUS_FAILED, the value of iResult is one of those listed in MeetingFailCode enum. 
	///If the status is MEETING_STATUS_ENDED, the value of iResult is one of those listed in MeetingEndReason.
	virtual void onMeetingStatusChanged(MeetingStatus status, int iResult = 0) = 0;

	/// \brief Meeting statistics warning notification callback.
	/// \param type The warning type of the meeting statistics. For more details, see \link StatisticsWarningType \endlink.
	virtual void onMeetingStatisticsWarningNotification(StatisticsWarningType type) = 0;
	
	/// \brief Callback notification of meeting secure key, supported only by special account.
	/// \param key The secure key of current meeting.
	/// \param len The length of secure key.
	/// \param pHandler The handler used to set the external secure key or leave meeting.
	/// \remarks The pHandler will be destroyed by the SDK once the function calls end.
	virtual void onMeetingSecureKeyNotification(const char* key, int len, IMeetingExternalSecureKeyHandler* pHandler) = 0;

	/// \brief Meeting parameter notification callback.
	/// \param meeting_param Meeting parameter. For more details, see \link MeetingParameter \endlink.
	/// \remarks The callback will be triggered right before the meeting starts. The meeting_param will be destroyed once the function calls end.
	virtual void onMeetingParameterNotification(const MeetingParameter* meeting_param) = 0;
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
class IMeetingLiveStreamController;
class IMeetingWebinarController;
class IClosedCaptionController;
class IMeetingQAController;
class IMeetingBOController;
/// \brief Meeting Service Interface
///
class IMeetingService
{
public:
	/// \brief Set meeting service callback event handler.
	/// \param pEvent A pointer to the IMeetingServiceEvent that receives the meeting service callback event.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingServiceEvent* pEvent) = 0;

	/// \brief Join meeting with web uri
	/// \param protocol_action Specifies the web uri
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError HandleZoomWebUriProtocolAction(const wchar_t* protocol_action) = 0;

	/// \brief Join the meeting.
	/// \param joinParam The parameter is used to join meeting. For more details, see \link JoinParam \endlink structure. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Join(JoinParam& joinParam) = 0;

	/// \brief Start meeting.
	/// \param startParam The parameter is used to start meeting. For more details, see \link StartParam \endlink structure. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Start(StartParam& startParam) = 0;

	/// \brief Leave meeting.
	/// \param leaveCmd Leave meeting command. For more details, see \link LeaveMeetingCmd \endlink enum. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Leave(LeaveMeetingCmd leaveCmd) = 0;

	/// \brief Get meeting status.
	/// \return If the function succeeds, the return value is the current meeting status. 
	///Otherwise failed. To get extended error information, see \link MeetingStatus \endlink enum.
	virtual MeetingStatus GetMeetingStatus() = 0;
	
	/// \brief Lock the current meeting.
	/// \return If the function succeeds, the return value is the SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError LockMeeting() = 0;

	/// \brief Unlock the current meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError UnlockMeeting() = 0;

	/// \brief Determine if the meeting is locked.
	/// \return TRUE indicates the meeting status is locked.
	virtual bool IsMeetingLocked() = 0;

	/// \brief Get meeting information.
	/// \return If the function succeeds, the return value is the meeting information. Otherwise returns NULL. For more details, see \link IMeetingInfo \endlink.
	virtual IMeetingInfo* GetMeetingInfo() = 0;

	/// \brief Get the quality of Internet connection when sharing.
	/// \param bSending TRUE indicates to get the connection quality of sending the sharing statistics. FALSE indicates to get the connection quality of receiving the sharing statistics.
	/// \return If the function succeeds, the return is one of those enumerated in ConnectionQuality enum.
	/// \remarks If you are not in the meeting, the Conn_Quality_Unknow will be returned.
	virtual ConnectionQuality GetSharingConnQuality(bool bSending = true) = 0;

	/// \brief Get the Internet connection quality of video.
	/// \param bSending TRUE indicates to get the connection quality of sending the video. FALSE indicates to get the connection quality of receiving the video.
	/// \return If the function succeeds, the return is one of those enumerated in ConnectionQuality enum.
	/// \remarks If you are not in the meeting, the Conn_Quality_Unknow will be returned.
	virtual ConnectionQuality GetVideoConnQuality(bool bSending = true) = 0;

	/// \brief Get the Internet connection quality of audio.
	/// \param bSending TRUE indicates to get the connection quality of sending the audio. FALSE indicates to get the connection quality of receiving the audio.
	/// \return If the function succeeds, the return value is one of those enumerated in ConnectionQuality enum.
	/// \remarks If you are not in the meeting, the Conn_Quality_Unknow will be returned.
	virtual ConnectionQuality GetAudioConnQuality(bool bSending = true) = 0;

	/// \brief Get the meeting configuration interface.
	/// \return If the function succeeds, the return value is the meeting configuration interface. Otherwise returns NULL.
	virtual IMeetingConfiguration* GetMeetingConfiguration() = 0;

	/// \brief Get the meeting UI controller interface.
	/// \return If the function succeeds, the return value is a pointer to the IMeetingConfiguration. Otherwise returns NULL.
	virtual IMeetingUIController* GetUIController() = 0;

	/// \brief Get the annotation controller interface.
	/// \return If the function succeeds, the return value is a pointer of IAnnotationController. Otherwise returns NULL.
	virtual IAnnotationController* GetAnnotationController() = 0;

	/// \brief Get video controller interface.
	/// \return If the function succeeds, the return value is a pointer to IMeetingVideoController. Otherwise returns NULL.
	virtual IMeetingVideoController* GetMeetingVideoController() = 0;

	/// \brief Get the remote controller interface.
	/// \return If the function succeeds, the return value is a pointer of IMeetingVideoController. Otherwise returns NULL.
	virtual IMeetingRemoteController* GetMeetingRemoteController() = 0;

	/// \brief Get the sharing controller interface.
	/// \return If the function succeeds, the return value is a pointer to IMeetingVideoController. Otherwise returns NULL.
	virtual IMeetingShareController* GetMeetingShareController() = 0;

	/// \brief Get the audio controller interface.
	/// \return If the function succeeds, the return value is a pointer to IMeetingAudioController. Otherwise returns NULL.
	virtual IMeetingAudioController* GetMeetingAudioController() = 0;

	/// \brief Get the recording controller interface.
	/// \return If the function succeeds, the return value is a pointer to IMeetingRecordingController. Otherwise returns NULL.
	virtual IMeetingRecordingController* GetMeetingRecordingController() = 0;

	/// \brief Get the chat controller interface.
	/// \return If the function succeeds, the return value is a pointer to IMeetingChatController. Otherwise returns NULL.
	virtual IMeetingChatController* GetMeetingChatController() = 0;

	/// \brief Get the waiting room controller interface.
	/// \return If the function succeeds, the return value is a pointer to IMeetingWaitingRoomController. Otherwise returns NULL.
	virtual IMeetingWaitingRoomController* GetMeetingWaitingRoomController() = 0;
	
	/// \brief Get the meeting H.323 helper interface.
	/// \return If the function succeeds, the return value is a pointer to IMeetingH323Helper. Otherwise returns NULL.
	virtual IMeetingH323Helper* GetH323Helper() = 0;

	/// \brief Get the meeting phone helper interface.
	/// \return If the function succeeds, the return value is a pointer of IMeetingPhoneHelper. Otherwise returns NULL.
	virtual IMeetingPhoneHelper* GetMeetingPhoneHelper() = 0;

	/// \brief Get the breakout rooms controller interface.
	/// \return If the function succeeds, the return value is a pointer to IMeetingBreakoutRoomsController. Otherwise returns NULL.
	virtual IMeetingBreakoutRoomsController* GetMeetingBreakoutRoomsController() = 0;

	/// \brief Get the participants controller interface.
	/// \return If the function succeeds, the return value is a pointer to IMeetingParticipantsController. Otherwise returns NULL.
	virtual IMeetingParticipantsController* GetMeetingParticipantsController() = 0;

	/// \brief Get the live stream controller interface.
	/// \return If the function succeeds, the return value is a pointer to IMeetingLiveStreamController. Otherwise returns NULL.
	virtual IMeetingLiveStreamController* GetMeetingLiveStreamController() = 0;

	/// \brief Get the webinar controller interface.
	/// \return If the function succeeds, the return value is a pointer to IMeetingWebinarController. Otherwise returns NULL.
	virtual IMeetingWebinarController* GetMeetingWebinarController() = 0;

	/// \brief Get the Closed Caption controller interface.
	/// \return If the function succeeds, the return value is a pointer to IMeetingWebinarController. Otherwise returns NULL.
	virtual IClosedCaptionController* GetMeetingClosedCaptionController() = 0;

	/// \brief Get the real name auth controller interface.
	/// \return If the function succeeds, the return value is a pointer to IZoomRealNameAuthMeetingHelper. Otherwise returns NULL.
	virtual IZoomRealNameAuthMeetingHelper* GetMeetingRealNameAuthController() = 0;

	/// \brief Get the Q&A controller.
	/// \return If the function succeeds, the return value is a pointer to IMeetingQAController. Otherwise returns NULL.
	virtual IMeetingQAController* GetMeetingQAController() = 0;

	/// \brief Get the Breakout Room controller.
	/// \return If the function succeeds, the return value is a pointer to IMeetingBOController. Otherwise returns NULL.
	virtual IMeetingBOController* GetMeetingBOController() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif