/*!
* \file meeting_service_interface.h
* \brief Meeting Service Interface
* 
*/
#ifndef _MEETING_SERVICE_INTERFACE_H_
#define _MEETING_SERVICE_INTERFACE_H_
#include "zoom_sdk_def.h"
#include <time.h>
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
	UINT64 meetingNumber;///< Meeting's number
	const wchar_t* userName;///< User Name in meeting
	const wchar_t* psw;///< Meeting's password
	bool		   isDirectShareDesktop;///< share desktop directly
	HWND		hDirectShareAppWnd;///< share application directly
	const wchar_t* toke4enfrocelogin;///< enforce login when join meeting
	const wchar_t* participantId;///< for meeting participant report list, need web backend enable.
}JoinParam4APIUser;

/*! \struct tagJoinParam4APIUser
    \brief Join meeting Parameter for API user.
    A more detailed struct description.
*/
typedef struct tagJoinParam4NormalUser
{
	UINT64 meetingNumber;///< Meeting's number
	const wchar_t* userName;///< User Name in meeting
	const wchar_t* psw;///< Meeting's password
	bool		   isDirectShareDesktop;///< share desktop directly
	HWND		hDirectShareAppWnd;///< share application directly
	const wchar_t* participantId;///< for meeting participant report list, need web backend enable.
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
	UINT64		meetingNumber;///< Meeting's number
	bool		isDirectShareDesktop;///< share desktop directly
	HWND		hDirectShareAppWnd;///< share application directly
	const wchar_t* participantId;///< for meeting participant report list, need web backend enable.
}StartParam4APIUser;

/*! \struct tagStartParam4NormalUser
    \brief Start meeting Parameter.
    A more detailed struct description.
*/
typedef struct tagStartParam4NormalUser
{
	UINT64		meetingNumber;///< Meeting's number
	bool		isDirectShareDesktop;///< share desktop directly
	HWND		hDirectShareAppWnd;///< share application directly
	const wchar_t* participantId;///< for meeting participant report list, need web backend enable.
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

/*! \struct tagShowChatDlgParam
    \brief Show meeting chat dialog Parameter.
    A more detailed struct description.
*/
typedef struct tagShowChatDlgParam
{
	HWND hParent;///< Parent window handle
	RECT rect;///< chat dialog position
	HWND hChatWnd;///< return chat windows handle
	tagShowChatDlgParam()
	{
		hParent = NULL;
		hChatWnd = NULL;
 		rect.top = 0;
 		rect.bottom = 0;
 		rect.left = 0;
 		rect.right = 0;
	}
}ShowChatDlgParam;


/*! \enum RemoteControlStatus
    \brief Remote Control Status.
    A more detailed struct description.
*/
enum RemoteControlStatus
{
	Remote_Control_None,
	Remote_Control_Can_Request,///< you can request other screen remote control right
	Remote_Control_Decline,///< other decline the remote control request
	Remote_Control_Accept,///< other accept the remote control request
	Remote_Control_Giveup,///< you give up the remote control right of other's screen 
	Remote_Control_Request,///< you receive the remote control request
};


/*! \enum SharingStatus
    \brief Sharing status.
    A more detailed struct description.
*/
enum SharingStatus
{
	Sharing_Begin,
	Sharing_End,
};

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

/*! \enum AudioStatus
    \brief Audio status.
    A more detailed struct description.
*/
enum AudioStatus
{
	Audio_None,
	Audio_Muted,
	Audio_UnMuted,
	Audio_Muted_ByHost,
	Audio_UnMuted_ByHost,
	Audio_MutedAll_ByHost,
	Audio_UnMutedAll_ByHost,
};

/*! \enum RecordingStatus
    \brief Recording status.
    A more detailed struct description.
*/
enum RecordingStatus
{
	Recording_Start,
	Recording_Stop,
	Recording_DiskFull,
};

class IUserAudioStatus
{
public:
	virtual unsigned int GetUserId() = 0;
	virtual AudioStatus GetStatus() = 0;
};

/// \brief Chat message information Interface
///
class IChatMsgInfo
{
public:
	/// \brief Get sender user id
	/// \return If the function succeeds, the return value is sender user id.
	///If the function fails, the return value is -1.
	virtual unsigned int GetSenderUserId() = 0;

	/// \brief Get sender user display name
	/// \return If the function succeeds, the return value is sender user display name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetSenderDisplayName() = 0;

	/// \brief Get receiver user id
	/// \return If the function succeeds, the return value is receiver user id.
	///if return value is 0, this message is send to everyone
	///If the function fails, the return value is -1.
	virtual unsigned int GetReceiverUserId() = 0;

	/// \brief Get receiver user display name
	/// \return If the function succeeds, the return value is receiver user display name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetReceiverDisplayName() = 0;

	/// \brief Get chat message content
	/// \return If the function succeeds, the return value is chat message content.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetContent() = 0;

	/// \brief Get chat message timestamp
	/// \return If the function succeeds, the return value is chat message timestamp.
	virtual time_t GetTimeStamp() = 0;
};

/// \brief Meeting Service Callback Event
///
class IMeetingServiceEvent
{
public:
	/// \brief Meeting status changed callback
	/// \param status Meeting status value.
	/// \param iResult details for special meeting status. 
	virtual void onMeetingStatusChanged(MeetingStatus status, int iResult = 0) = 0;

	/// \brief Once the mp4 conversion is complete, call back 
	/// \param bsuccess Success or not.
	/// \param iResult Details for error code if failed.
	/// \param szPath if success, will return the recording file path, Otherwise is NULL. 
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath) = 0;

	/// \brief Notify the mp4 conversion processing
	/// \param iPercentage conversion process's percentage.
	virtual void onRecording2MP4Processing(int iPercentage) = 0;

	/// \brief Self Recording status notify callback
	/// \param status Recording status value.
	virtual void onRecordingStatus(RecordingStatus status) = 0;

	/// \brief New user join notify callback
	/// \param lstUserID List of new user.
	/// \param strUserList User list in json format,Reserved.
	virtual void onUserJoin(IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;

	/// \brief User left meeting notify callback
	/// \param lstUserID List of the user left.
	/// \param strUserList User list in json format,Reserved.
	virtual void onUserLeft(IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;

	/// \brief Remote Control status notify callback
	/// \param status Remote control status value.
	/// \param userId Remote control user id.
	virtual void onRemoteControlStatus(RemoteControlStatus status, unsigned int userId) = 0;

	/// \brief Sharing status notify callback
	/// \param status Sharing status value.
	/// \param userId Sharing user id.
	virtual void onSharingStatus(SharingStatus status, unsigned int userId) = 0;

	/// \brief User's audio status change callback
	/// \param lstAudioStatusChange List of status changed user. This param will invalid after this function call end.
	/// \param strAudioStatusList Audio status change list in json format,Reserved.
	virtual void onUserAudioStatusChange(IList<IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL) = 0;

	/// \brief chat message callback
	/// \param chatMsg chat message object. This param will invalid after this function call end.
	/// \param content chat message in json format,Reserved.
	virtual void onChatMsgNotifcation(IChatMsgInfo* chatMsg, const wchar_t* content = NULL) = 0;
};

/// \brief Meeting UI Controller Interface
///
class IMeetingUIController
{
public:
	/// \brief Show meeting chat dialog
	/// \param param Specifies how to show chat dialog.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowChatDlg(ShowChatDlgParam& param) = 0;

	/// \brief Hide meeting chat dialog
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError HideChatDlg() = 0;

	/// \brief Enter full screen mode
	/// \param firstView Specifies the first monitor enter full screen mode or not.
	/// \param secondView Specifies the second monitor enter full screen mode or not, if enable dual monitor mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnterFullScreen(bool firstView, bool secondView) = 0;
	
	/// \brief Exit full screen mode
	/// \param firstView Specifies the first monitor exit full screen mode or not.
	/// \param secondView Specifies the second monitor exit full screen mode or not, if enable dual monitor mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ExitFullScreen(bool firstView, bool secondView) = 0;

	/// \brief Switch to video wall view
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwitchToVideoWall() = 0;
	
	/// \brief Switch to active speaker view
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwtichToAcitveSpeaker() = 0;

	/// \brief Move Float Video window
	/// \param left Specifies The left position of the Float Video window.
	/// \param top Specifies The top position of the Float Video window.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError MoveFloatVideoWnd(int left, int top) = 0;

	/// \brief Show sharing float toolbar
	/// \param bShow Specifies the sharing float toolbar show or not
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowSharingToolbar(bool bShow) = 0;

	/// \brief Switch float video bar to active speaker view
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwitchFloatVideoToActiveSpkMod() = 0;
	
	/// \brief Change float active speaker video bar size
	/// \param bMax if true, change video bar to maximum size, otherwise change to minimum size.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ChangeFloatoActiveSpkVideoSize(bool bMax) = 0;

	/// \brief Switch float video bar to gallery view
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwitchFloatVideoToGalleryMod() = 0;

	/// \brief Show Participants List window
	/// \param bShow Specifies the participants List Window show or not
	/// \param hParticipantsListWnd if bShow is true,and api call success, will return the handle of the participants List window
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowParticipantsListWnd(bool bShow, HWND& hParticipantsListWnd) = 0;

	/// \brief Show bottom float toolbar window
	/// \param bShow Specifies the bottom float toolbar window show or not
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowBottomFloatToolbarWnd(bool bShow) = 0;

	/// \brief Retrieves the handle of the meeting UI window
	/// \param hFirstView the variable where the first view handle of the meeting UI window is returned.
	/// \param hSecondView the variable where the second view handle of the meeting UI window is returned.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GetMeetingUIWnd(HWND& hFirstView, HWND& hSecondView) = 0;

	/// \brief Show join audio dialog
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowJoinAudioDlg() = 0;

	/// \brief Hide join audio dialog
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError HideJoinAudioDlg() = 0;
};

/// \brief User information Interface
///
class IUserInfo
{
public:
	/// \brief Get user name
	/// \return If the function succeeds, the return value is user name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetUserName() = 0;

	/// \brief Get user email
	/// \return If the function succeeds, the return value is user email.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetEmail() = 0;

	/// \brief Is host or not
	/// \return host or not
	virtual bool IsHost() = 0;

	/// \brief Get user ID
	/// \return If the function succeeds, the return value is user ID.
	///If the function fails, the return value is 0.
	virtual unsigned int GetUserID() = 0;
	
	/// \brief Is video on or off 
	/// \return video on or off
	virtual bool IsVideoOn() = 0;

	/// \brief Is audio Muted or UnMuted 
	/// \return audio Muted or UnMuted 
	virtual bool IsAudioMuted() = 0;
};

/*! \enum AnnotationToolType
    \brief Annotation Tool Type.
    A more detailed struct description.
*/
enum AnnotationToolType
{
	ANNOTOOL_NONE_DRAWING,///<switch to mouse 

	ANNOTOOL_PEN,
	ANNOTOOL_HIGHLIGHTER,
	ANNOTOOL_AUTO_LINE,
	ANNOTOOL_AUTO_RECTANGLE,
	ANNOTOOL_AUTO_ELLIPSE,
	ANNOTOOL_AUTO_ARROW,
	ANNOTOOL_AUTO_RECTANGLE_FILL,
	ANNOTOOL_AUTO_ELLIPSE_FILL,

	ANNOTOOL_SPOTLIGHT,
	ANNOTOOL_ARROW,

	ANNOTOOL_ERASER,///<earser
};

/*! \enum AnnotationClearType
    \brief Annotation Clear Type.
    A more detailed struct description.
*/
enum AnnotationClearType
{
	ANNOCLEAR_ALL,
	ANNOCLEAR_SELF,
	ANNOCLEAR_OTHER,
};
/// \brief Meeting Annotation Controller Interface
///
class IAnnotationController
{
public:
	/// \brief The Annotation of the current meeting is disabled or not.
	/// \return Disabled or not.
	virtual bool IsAnnoataionDisable() = 0;

	/// \brief start annotation
	/// \param left Specifies The left position of the annotation bar.
	/// \param top Specifies The top position of the annotation bar.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StartAnnotation(int left, int top) = 0;

	/// \brief Stop current annotation
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StopAnnotation() = 0;

	/// \brief Set Annotation Tool
	/// \param type The parameter to be used for annotation tool type, refer to AnnotationToolType. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetTool(AnnotationToolType type) = 0;

	/// \brief Clear Annotation
	/// \param type The parameter to be used for annotation earse operator type, refer to AnnotationClearType. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Clear(AnnotationClearType type) = 0;


	/// \brief Set Annotation Color
	/// \param color The parameter to be used for annotation color, ABGR formats. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetColor(unsigned long color) = 0;

	/// \brief Set Annotation Line Width
	/// \param lineWidth The parameter to be used for annotation line width. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetLineWidth(long lineWidth) = 0;
	
	/// \brief Undo Annotation
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Undo() = 0;
	
	/// \brief Redo Annotation
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Redo() = 0;
};

/// \brief Meeting Configuration Interface
///
class IMeetingConfiguration
{
public:
	/// \brief Reset meeting configuration
	virtual void Reset() = 0;

	/// \brief Set float video panel position
	/// \param pos Specifies where float video panel show.
	virtual void SetFloatVideoPos(WndPosition pos) = 0;

	/// \brief Set sharing toolbar visibility flag
	/// \param bShow Specifies float tool bar show or not during sharing.
	virtual void SetSharingToolbarVisibility(bool bShow) = 0;

	/// \brief Set bottom float toolbar visibility flag
	/// \param bShow Specifies bottom float toolbar show or not during sharing.
	virtual void SetBottomFloatToolbarWndVisibility(bool bShow) = 0;

	/// \brief Set the monitor id for direct share.
	/// \param monitorID Specifies which the monitor is to be shared.Using EnumDisplayMonitors System api to get this value.
	/// refer to szDevice in MONITORINFOEX struct. 
	virtual void SetDirectShareMonitorID(const wchar_t* monitorID) = 0;

	/// \brief Set meeting UI position
	/// \param pos Specifies where meeting UI show.
	virtual void SetMeetingUIPos(WndPosition pos) = 0;

	/// \brief Disable waiting for host dialog
	/// \param bDisable Specifies waiting for host dialog show or not.
	virtual void DisableWaitingForHostDialog(bool bDisable) = 0;

	/// \brief Hide the meeting information from meeting UI
	/// \param bHide Specifies the meeting information of meeting UI hide or not.
	virtual void HideMeetingInfoFromMeetingUITitle(bool bHide) = 0;

	/// \brief Set the meeting ID to be showed in meeting ui title
	/// \param meetingNumber Specifies the meeting ID to be showed in meeting ui title.
	virtual void SetMeetingIDForMeetingUITitle(UINT64 meetingNumber) = 0;
	
	/// \brief Disable wrong password error dialog when join meeting.
	/// \param bDisable Specifies wrong password error dialog disable or not, if disable, you will get the MEETING_FAIL_PASSWORD_ERR meeting failed error.
	virtual void DisablePopupMeetingWrongPSWDlg(bool bDisable) = 0;

	/// \brief Enable auto end other meeting when you start a new meeting.
	/// \param bEnable Specifies auto end other meeting enable or not.
	virtual void EnableAutoEndOtherMeetingWhenStartMeeting(bool bEnable) = 0;
};

/// \brief Meeting Service Interface
///
class IMeetingService
{
public:
	/// \brief Set meeting service callback event
	/// \param pEvent A pointer to a IMeetingService* that receives meeting event. 
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

	/// \brief Get meeting participants list
	/// \return the return value is current meeting all participants list.if not in meeting, return NULL.
	virtual IList<unsigned int >* GetParticipantsList() = 0;

	/// \brief Get meeting topic
	/// \return the return value is current meeting topic.
	virtual const wchar_t* GetMeetingTopic() = 0;

	/// \brief Send chat message to somebody or All
	/// \param receiver the chat message receiver. if this parameter is zero, this message send to all
	/// \param content	the chat message content.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SendChatTo(unsigned int receiver, wchar_t* content) = 0;

	/// \brief Start recording
	/// \param startTimestamp Start recording timestamp. 
	/// \param recPath Specifies where the recording is to be saved, if the path is not exist, return SDKERR_INVALID_PARAMETER error code.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StartRecording(time_t& startTimestamp, wchar_t* recPath) = 0;

	/// \brief Stop recording
	/// \param stopTimestamp Stop recording timestamp.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StopRecording(time_t& stopTimestamp) = 0;

	/// \brief Mute video
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError MuteVideo() = 0;

	/// \brief Unmute video
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError UnmuteVideo() = 0;

	/// \brief Mute audio
	/// \param userId Specifies which the user's audio to mute.if is zero, mute all of users
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError MuteAudio(unsigned int userid) = 0;

	/// \brief Unmute audio
	/// \param userId Specifies which the user's audio to unmute.if is zero, unmute all of users
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError UnMuteAudio(unsigned int userid) = 0;

	/// \brief Start application share
	/// \param hwndSharedApp Specifies which the window is to be shared.
	///if hwndSharedApp can't be shared, return SDKERR_INVALID_PARAMETER error code.if hwndSharedApp is NULL, will show select application dialog.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StartAppShare(HWND hwndSharedApp) = 0;

	/// \brief Start monitor share
	/// \param monitorID Specifies which the monitor is to be shared.Using EnumDisplayMonitors System api to get this value.
	/// refer to szDevice in MONITORINFOEX struct. if monitorID is NULL, will show select application dialog. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StartMonitorShare(const wchar_t* monitorID) = 0;

	/// \brief Stop current sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StopShare() = 0;

	/// \brief Block window form screen share. 
	///This api will change the window's property.we don't suggest to use.
	///After call this api, you need to redraw this window to take effect.
	/// \param bBlock block window from screen share or not.
	/// \param hWnd Specifies which window to be blocked.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError BlockWindowFromScreenshare(bool bBlock, HWND hWnd) = 0;

	/// \brief Lock current meeting
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LockMeeting() = 0;

	/// \brief Unlock current meeting
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError UnlockMeeting() = 0;

	/// \brief Get meeting UI controller
	/// \return If the function succeeds, the return value is meeting ui controller interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingUIController* GetUIController() = 0;

	/// \brief Get user information via user id
	/// \param userId Specifies which the user's information to get.if zero,to get current user information.
	/// \return If the function succeeds, the return value is user information interface.
	///If the function fails, the return value is NULL.
	virtual IUserInfo* GetUserByUserID(unsigned int userid) = 0;

	/// \brief Get annotation controller
	/// \return If the function succeeds, the return value is annotation controller interface.
	///If the function fails, the return value is NULL.
	virtual IAnnotationController* GetAnnotationController() = 0;

	/// \brief Request meeting Remote control
	/// \return If the function succeeds, the return value is meeting ui controller interface.
	///If the function fails, the return value is NULL.
	virtual SDKError RequestRemoteControl() = 0;

	/// \brief Give up meeting Remote control
	/// \return If the function succeeds, the return value is meeting ui controller interface.
	///If the function fails, the return value is NULL.
	virtual SDKError GiveupRemoteControl() = 0;

	/// \brief Give meeting Remote control right to other attendee
	/// \param userId Specifies which the user to control your screen.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GiveRemoteControlTo(unsigned int userId) = 0;

	/// \brief Decline meeting Remote control request
	/// \param userId Specifies which the user can't to control your screen.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DeclineRemoteControlRequest(unsigned int userId) = 0;

	/// \brief Revoke Current Remote Controller's right
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError RevokeRemoteControl() = 0;

	/// \brief Get meeting current remote controller
	/// \param userId Store the current remote controller userid, if zero, now meeting don't have remote controller.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GetCurrentRemoteController(unsigned int& userId) = 0;

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

	/// \brief Get meeting configuration interface.
	/// \return If the function succeeds, the return value is meeting configuration interface.
	///If the function fails, the return value is NULL.
	virtual IMeetingConfiguration* GetMeetingConfiguration() = 0;

	/// \brief Get meeting connection quality.
	/// \return If the function succeeds, the return value is ConnectionQuality enum value.
	/// \if you don't in meeting, will return Conn_Quality_Unknow
	virtual ConnectionQuality GetMeetingConnQuality() = 0;

	/// \brief Lock current meeting's sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LockShare() = 0;

	/// \brief Lock current meeting's sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError UnlockShare() = 0;

	/// \brief Enable mute on entry feature when User join meeting
	/// \param bEnable Specifies mute on entry feature enable or disable.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableMuteOnEntry(bool bEnable) = 0;

	/// \brief Enable play chime feature when user join or leave meeting.
	/// \param bEnable Specifies play chime feature when user join or leave meeting, enable or disable.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnablePlayChimeWhenEnterOrExit(bool bEnable) = 0;

	/// \brief Lower all attendee hands in meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LowerAllHands() = 0;

	/// \brief Switch the sharing view window to fit window mode when view sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwitchToFitWindowModeWhenViewShare() = 0;

	/// \brief Switch the sharing view window to original size mode when view sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwitchToOriginalSizeModeWhenViewShare() = 0;

	/// \brief Hide or show no video user on video wall mode
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError HideOrShowNoVideoUserOnVideoWall(bool bHide) = 0;

};
END_ZOOM_SDK_NAMESPACE
#endif