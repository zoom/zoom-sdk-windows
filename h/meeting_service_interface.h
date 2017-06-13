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
	MEETING_STATUS_IN_WAITING_ROOM,
	MEETING_STATUS_WEBINAR_PROMOTE,
	MEETING_STATUS_WEBINAR_DEPROMOTE,
	MEETING_STATUS_JOIN_BREAKOUT_ROOM,
	MEETING_STATUS_LEAVE_BREAKOUT_ROOM,
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

/*! \enum SDKViewType
    \brief SDK View Type, first monitor and second monitor.
    A more detailed struct description.
*/
enum SDKViewType
{
	SDK_FIRST_VIEW,
	SDK_SECOND_VIEW,
};

enum SDKMeetingUIType
{
	SDK_Meeting_UI_None,
	SDK_Meeting_UI_VideoWall_Mode,
	SDK_Meeting_UI_ActiveRender_Mode,
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

typedef struct tagVideoWallPageInfoParam
{
	int nCurrentPage;
	int nTotalPages;
}VideoWallPageInfoParam;

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
	Remote_Control_I_Can_Request_Control_Who,

	Remote_Control_I_Can_Control_Who_Begin,
	Remote_Control_I_Can_Control_Who_End,

	Remote_Control_I_Control_Who_Begin,
	Remote_Control_I_Control_Who_End,

	Remote_Control_Who_Control_Me,
	Remote_Control_I_Recv_Decline_Msg,
	Remote_Control_I_Recv_Request_Msg,
};


/*! \enum SharingStatus
    \brief Sharing status.
    A more detailed struct description.
*/
enum SharingStatus
{
	Sharing_Self_Send_Begin,
	Sharing_Self_Send_End,
	Sharing_Other_Share_Begin,
	Sharing_Other_Share_End,
	Sharing_View_Other_Sharing,
	Sharing_Pause,
	Sharing_Resume,
};

enum VideoStatus
{
	Video_ON,
	Video_OFF,
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
	/// \param iResult details reason for special meeting status.
	/// if status is MEETING_STATUS_FAILED, the value of iResult is one of MeetingFailCode enum. 
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

	/// \brief lock share status notify call back 
	/// \param bLocked specify if sharing is locked.
	virtual void onLockShareStatus(bool bLocked) = 0;

	/// \brief User's audio status change callback
	/// \param lstAudioStatusChange List of status changed user. This param will invalid after this function call end.
	/// \param strAudioStatusList Audio status change list in json format,Reserved.
	virtual void onUserAudioStatusChange(IList<IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL) = 0;

	/// \brief chat message callback
	/// \param chatMsg chat message object. This param will invalid after this function call end.
	/// \param content chat message in json format,Reserved.
	virtual void onChatMsgNotifcation(IChatMsgInfo* chatMsg, const wchar_t* content = NULL) = 0;

	/// \brief User's video status change callback
	/// \param userId 
	/// \param status
	virtual void onUserVideoStatusChange(unsigned int userId, VideoStatus status) = 0;

	/// \brief host change callback
	/// \param userId 
	virtual void onHostChangeNotification(unsigned int userId) = 0;

	/// \brief spotlight video change callback
	/// \param userId 
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid) = 0;

	/// \brief self record privilige change callback
	/// \param bCanRec 
	virtual void onRecordPriviligeChanged(bool bCanRec) = 0;

	/// \brief Low Or Raise Hand Status change callback
	/// \param bLow
	/// \param userid 
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid) = 0;
};

enum SDKFloatVideoType
{
	FLOATVIDEO_List,
	FLOATVIDEO_Small,
	FLOATVIDEO_Large,
	FLOATVIDEO_Minimize,
};

/// \brief Meeting UI Controller Callback Event
///
class IMeetingUIControllerEvent
{
public:
	virtual void onInviteBtnClicked() = 0;
};

/// \brief Meeting UI Controller Interface
///
class IMeetingUIController
{
public:
	/// \brief Set meeting ui controller callback event
	/// \param pEvent A pointer to a IMeetingUIControllerEvent* that receives meeting ui event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingUIControllerEvent* pEvent) = 0;

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
	/// \param type Specifies the float video panel view type.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ChangeFloatoActiveSpkVideoSize(SDKFloatVideoType type) = 0;

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

	/// \brief get page info on video wall mode.
	/// \param videoWallPageInfoParam store current page index and total pages.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GetWallViewPageInfo(VideoWallPageInfoParam& videoWallPageInfoParam) = 0;

	/// \brief show previous or next page video user on video wall mode.
	/// \param bPageUp specifies previous or next page.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowPreOrNextPageVideo(bool bPageUp) = 0;
};

enum AudioType
{
	AUDIOTYPE_NONE,
	AUDIOTYPE_VOIP,
	AUDIOTYPE_PHONE,
	AUDIOTYPE_UNKNOW,
};

/*! \enum UserRole
    \brief User role.
    A more detailed struct description.
*/
enum UserRole
{
	USERROLE_NONE,
	USERROLE_HOST,
	USERROLE_COHOST,
	USERROLE_PANELIST,
	USERROLE_BREAKOUTROOM_MODERATOR,
	USERROLE_ATTENDEE,
};

class IBreakoutRoomsInfo
{
public:
	virtual ~IBreakoutRoomsInfo() {};
	/// \brief Get Breakout Room ID
	/// \return If the function succeeds, the return value is Breakout Room ID.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetBID() = 0;

	/// \brief Get Breakout Room name
	/// \return If the function succeeds, the return value is Breakout Room name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetBreakoutRoomName() = 0;
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

	/// \brief Audio type
	/// \return Audio join type
	virtual AudioType GetAudioJoinType() = 0;

	/// \brief Is me or not
	/// \return me or not
	virtual bool IsMySelf() = 0;

	/// \brief Is in waiting room or not
	/// \return in waiting room or not 
	virtual bool IsInWaitingRoom() = 0;

	/// \brief Is raise hand or not
	/// \return Is raise hand or not
	virtual bool IsRaiseHand() = 0;

	/// \brief User Role
	/// \return User Role
	virtual UserRole GetUserRole() = 0;
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
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \param left Specifies The left position of the annotation bar.
	/// \param top Specifies The top position of the annotation bar.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StartAnnotation(SDKViewType viewtype, int left, int top) = 0;

	/// \brief Stop current annotation
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StopAnnotation(SDKViewType viewtype) = 0;

	/// \brief Set Annotation Tool
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \param type The parameter to be used for annotation tool type, refer to AnnotationToolType. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetTool(SDKViewType viewtype, AnnotationToolType type) = 0;

	/// \brief Clear Annotation
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \param type The parameter to be used for annotation earse operator type, refer to AnnotationClearType. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Clear(SDKViewType viewtype, AnnotationClearType type) = 0;


	/// \brief Set Annotation Color
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \param color The parameter to be used for annotation color, ABGR formats. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetColor(SDKViewType viewtype, unsigned long color) = 0;

	/// \brief Set Annotation Line Width
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \param lineWidth The parameter to be used for annotation line width. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetLineWidth(SDKViewType viewtype, long lineWidth) = 0;
	
	/// \brief Undo Annotation
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Undo(SDKViewType viewtype) = 0;
	
	/// \brief Redo Annotation
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Redo(SDKViewType viewtype) = 0;
};

/// \brief Meeting Password And Screen Name Handler
///
class IMeetingPasswordAndScreenNameHandler
{
public:
	enum RequiredInfoType
	{
		REQUIRED_INFO_TYPE_NONE,
		REQUIRED_INFO_TYPE_Password, ///< if you want to join meeting, you need input password
		REQUIRED_INFO_TYPE_Password4WrongPassword,///< you input a wrong password, please input again
		REQUIRED_INFO_TYPE_PasswordAndScreenName,///< if you want to join meeting, you need input password and screen name
	};

	/// \brief get the required information you need to input.
	virtual RequiredInfoType GetRequiredInfoType() = 0;

	/// \brief Input the meeting password and screen name.
	virtual bool InputMeetingPasswordAndScreenName(const wchar_t* meetingPassword, const wchar_t* screenName) = 0;

	// \brief cancel to input the meeting password and screen name.
	virtual void Cancel() = 0;
};

/// \brief Meeting Configuration Event callback
///
class IMeetingConfigurationEvent
{
public:
	/// \brief meeting need password or screen name callback
	/// \param pHandler which will be invoked for when this message type is received.
	virtual void onInputMeetingPasswordAndScreenNameNotification(IMeetingPasswordAndScreenNameHandler* pHandler) = 0;
};

/// \brief Meeting Configuration Interface
///
class IMeetingConfiguration
{
public:
	/// \brief set a handler for meeting configuration notification.
	/// \param pEvent which will be invoked for when this message type is received.
	virtual void SetEvent(IMeetingConfigurationEvent* pEvent) = 0;

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

	/// \brief Enable auto adjust the volume of the speaker when you join audio.
	/// \param bEnable Specifies auto adjust the volume of the speaker enable or not, default is enable.
	virtual void EnableAutoAdjustSpeakerVolumeWhenJoinAudio(bool bEnable) = 0;

	/// \brief Enable auto adjust the volume of the mic when you join audio.
	/// \param bEnable Specifies auto adjust the volume of the mic enable or not, default is enable.
	virtual void EnableAutoAdjustMicVolumeWhenJoinAudio(bool bEnable) = 0;

	/// \brief Enable approve remote control dialog when you get other's remote control request.
	/// \param bEnable Specifies approve remote control dialog will show when you get other's remote control request, default is enable,
	/// if you disable this, please handle the onRemoteControlStatus callback event.
	virtual void EnableApproveRemoteControlDlg(bool bEnable) = 0;

	/// \brief Enable decline remote control response dialog 
	/// \param bEnable Specifies decline remote control response dialog will show when you get other's decline message, default is enable,
	/// if you disable this, please handle the onRemoteControlStatus callback event.
	virtual void EnableDeclineRemoteControlResponseDlg(bool bEnable) = 0;

	/// \brief Enable leave meeting button in leave meeting window for host
	/// \param bEnable Specifies leave meeting button show or not in host leave meeting window, default is enable,
	virtual void EnableLeaveMeetingOptionForHost(bool bEnable) = 0;

	/// \brief Enable invite button in meeting window
	/// \param bEnable Specifies invite button show or not in meeting window, default is disable,
	/// if enable this feature, you need to handle onInviteBtnClicked event callback
	virtual void EnableInviteButtonOnMeetingUI(bool bEnable) = 0;

	/// \brief config hide or show input meeting password dialog
	/// \param bEnable specify hide or show input meeting password dialog, default is enable.
	/// if disable this option, you need to handle onInputMeetingPasswordAndScreenNameNotification event callback.
	virtual void EnableInputMeetingPasswordDlg(bool bEnable) = 0;

	// \brief Enable enter and exit full screen button on meeting ui. 
	/// \param bEnable Specifies enter and exit full screen button show or not in meeting window, default is enable.
	virtual void EnableEnterAndExitFullScreenButtonOnMeetingUI(bool bEnable) = 0;

	// \brief Enable left button double click for enter and exit full screen feature. 
	/// \param bEnable Specifies Enable or disable switch full screen mode via left button double click, default is enable.
	virtual void EnableLButtonDBClick4SwitchFullScreenMode(bool bEnable) = 0;
};

/// \brief Meeting video controller interface
///
class IMeetingVideoController
{
public:
	/// \brief Mute video
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError MuteVideo() = 0;

	/// \brief Unmute video
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError UnmuteVideo() = 0;

	/// \brief Pin or Unpin video
	/// \param bPin pin or unpin video
	/// \param bFirstView first screen or not to pin the video.
	/// \param userid Specifies which the user is to be pinned.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError PinVideo(bool bPin, bool bFirstView, unsigned int userid) = 0;

	/// \brief Spotlight video
	/// \param bSpotlight spotlight video or not
	/// \param userid Specifies which the user is to be spotlighted.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SpotlightVideo(bool bSpotlight, unsigned int userid) = 0;

	/// \brief Hide or show no video user on video wall mode
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError HideOrShowNoVideoUserOnVideoWall(bool bHide) = 0;
};

/// \brief Meeting remote controller interface
///
class IMeetingRemoteController
{
public:
	/// \brief Request meeting Remote control
	/// \param userId Specifies which the user you want to remote control.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError RequestRemoteControl(unsigned int userId) = 0;

	/// \brief Give up meeting Remote control
	/// \param userId Specifies which the user you want to give up the remote control right.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GiveupRemoteControl(unsigned int userId) = 0;

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
};

/*! \struct tagViewableShareSource
    \brief Viewable share source info.
    A more detailed struct description.
*/
typedef struct tagViewableShareSource
{
	unsigned int userid;
	bool isShowingInFirstView;
	bool isShowingInSecondView;
	bool isCanBeRemoteControl;
	tagViewableShareSource()
	{
		userid = 0;
		isShowingInFirstView = false;
		isShowingInSecondView = false;
		isCanBeRemoteControl = false;
	}
}ViewableShareSource;

/// \brief Meeting share controller interface
///
class IMeetingShareController
{
public:
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

	/// \brief Lock current meeting's sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LockShare() = 0;

	/// \brief Lock current meeting's sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError UnlockShare() = 0;

	/// \brief Switch the sharing view window to fit window mode when view sharing.
	/// \param type Specifies which view you want to set, first monitor or second monitor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwitchToFitWindowModeWhenViewShare(SDKViewType type) = 0;

	/// \brief Switch the sharing view window to original size mode when view sharing.
	/// \param type Specifies which view you want to set, first monitor or second monitor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwitchToOriginalSizeModeWhenViewShare(SDKViewType type) = 0;

	/// \brief Pause current sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError PauseCurrentSharing() = 0;
	
	/// \brief Resume current sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ResumeCurrentSharing() = 0;

	/// \brief get current viewable share source list.
	/// \return If the function succeeds, the return value is the viewable share source user id list.
	///If the function fails, the return value is NULL.
	virtual IList<unsigned int >* GetViewableShareSourceList() = 0;

	/// \brief get viewable share source by userid.
	/// \param userid Specifies which viewable share source info you want to get.
	/// \param shareSource store the viewable share source info
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GetViewabltShareSourceByUserID(unsigned int userid, ViewableShareSource& shareSource) = 0;

	/// \brief view share by userid.
	/// \param userid Specifies who you want to view.
	/// \param type Specifies which view you want to view the sharing, first monitor or second monitor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ViewShare(unsigned int userid, SDKViewType type) = 0;

	/// \brief show share option dialog.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowShareOptionDialog() = 0;

	/// \brief can start share or not.
	/// \return can start share or not.
	virtual bool CanStartShare() = 0;

	/// \brief query if sharing is locked.
	/// \param bLocked store if sharing is locked.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError IsShareLocked(bool& bLocked) = 0;
};

/// \brief Meeting audio controller interface
///
class IMeetingAudioController
{
public:
	/// \brief Join Voip audio
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError JoinVoip() = 0;

	/// \brief Leave Voip audio
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LeaveVoip() = 0;

	/// \brief Mute audio
	/// \param userId Specifies which the user's audio to mute.if is zero, mute all of users
	/// \param allowUnmuteBySelf Specifies can unmute by self or not when mute all.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError MuteAudio(unsigned int userid, bool allowUnmuteBySelf = true) = 0;

	/// \brief Unmute audio
	/// \param userId Specifies which the user's audio to unmute.if is zero, unmute all of users
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError UnMuteAudio(unsigned int userid) = 0;

	/// \brief Can unmute by self?
	/// \return Can unmute by self or not
	virtual bool CanUnMuteBySelf() = 0;

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
};

class IMeetingBreakoutRoomsEvent
{
public:
	//////////////////Callback for ATTENDEES///////////////////
	//Receive join BO request

	/// \brief host open Breakout Rooms callback
	/// \param stBID Specifies Breakout Room id.
	virtual void OnBreakoutRoomsStartedNotification(const wchar_t* stBID) = 0;
};

/// \brief Breakout Rooms controller interface
///
class IMeetingBreakoutRoomsController
{
public:
	/// \brief set a handler for IBreakoutRoomsEvent notification.
	/// \param pEvent which will be invoked for when this message type is received.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingBreakoutRoomsEvent* pEvent) = 0;

	/// \brief Join Breakout Room
	/// \param stBID Specifies Breakout Room id.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError JoinBreakoutRoom(const wchar_t* stBID) = 0;

	/// \brief Leave Breakout Room
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LeaveBreakoutRoom() = 0;

	/// \brief Get Breakout Room list which can join
	/// \return If the function succeeds, the return value is Breakout Room list.
	///If the function fails, the return value is NULL.
	virtual IList<IBreakoutRoomsInfo* >* GetBreakoutRoomsInfoList() = 0;
};

/// \brief Meeting recording controller interface
///
class IMeetingRecordingController
{
public:
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
};

/// \brief Meeting chat controller interface
///
class IMeetingChatController
{
public:
	/// \brief Send chat message to somebody or All
	/// \param receiver the chat message receiver. if this parameter is zero, this message send to all
	/// \param content	the chat message content.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SendChatTo(unsigned int receiver, wchar_t* content) = 0;
};

/// \brief Meeting Waiting Room Callback Event
///
class IMeetingWaitingRoomEvent
{
public:
	/// \brief User join waiting room notify callback
	/// \param userID ID of the user join waiting room.
	virtual void onWatingRoomUserJoin(unsigned int userID) = 0;

	/// \brief User left waiting room notify callback
	/// \param userID ID of the user left waiting room.
	virtual void onWatingRoomUserLeft(unsigned int userID) = 0;

};
/// \brief Meeting waiting room controller interface
///
class IMeetingWaitingRoomController
{
public:
	/// \brief Set meeting waiting room callback event
	/// \param pEvent A pointer to a IMeetingWaitingRoomEvent* that receives waiting room event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingWaitingRoomEvent* pEvent) = 0;
	
	/// \brief Current meeting support waiting room or not.
	/// \return true, support waiting room.
	virtual bool IsSupportWaitingRoom() = 0;

	/// \brief Get the flag of put attendee in waiting room on entry for the current meeting.
	/// \return true, enabled.
	virtual bool IsWaitingRoomOnEntryFlagOn() = 0;

	/// \brief Enable the flag of put attendee in waiting room on entry for the current meeting.
	/// \param bEnable enable waiting room or not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableWaitingRoomOnEntry(bool bEnable) = 0;

	/// \brief Get meeting participants list in the waiting room
	/// \return the return value is current meeting all waiting room participants list.if not in meeting, return NULL.
	virtual IList<unsigned int >* GetWaitingRoomLst() = 0;

	/// \brief Get waiting room user information via user id
	/// \param userId Specifies which the user's information to get.
	/// \return If the function succeeds, the return value is user information interface.
	///If the function fails, the return value is NULL.
	virtual IUserInfo* GetWaitingRoomUserInfoByID(unsigned int userid) = 0;

	/// \brief Admit user to the meeting
	/// \param userId Specifies which the user to admitted.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError AdmitToMeeting(unsigned int userid) = 0;

	/// \brief Put user into the waiting room
	/// \param userId Specifies which the user to put in.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError PutInWaitingRoom(unsigned int userid) = 0;
};


class IMeetingH323Helper;
class IMeetingPhoneHelper;
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

	/// \brief Get meeting participants list
	/// \return the return value is current meeting all participants list.if not in meeting, return NULL.
	virtual IList<unsigned int >* GetParticipantsList() = 0;

	/// \brief Get meeting topic
	/// \return the return value is current meeting topic.
	virtual const wchar_t* GetMeetingTopic() = 0;

	/// \brief Get meeting type
	/// \return the return value is current meeting type.To get extended error information, refer to MeetingType enum
	virtual MeetingType GetMeetingType() = 0;

	/// \brief Lock current meeting
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LockMeeting() = 0;

	/// \brief Unlock current meeting
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError UnlockMeeting() = 0;

	/// \brief Lower all attendee hands in meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LowerAllHands() = 0;

	/// \brief Get user information via user id
	/// \param userId Specifies which the user's information to get.if zero,to get current user information.
	/// \return If the function succeeds, the return value is user information interface.
	///If the function fails, the return value is NULL.
	virtual IUserInfo* GetUserByUserID(unsigned int userid) = 0;

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

	/// \brief Get meeting connection quality.
	/// \return If the function succeeds, the return value is ConnectionQuality enum value.
	/// \if you don't in meeting, will return Conn_Quality_Unknow
	virtual ConnectionQuality GetMeetingConnQuality() = 0;

	/// \brief Get video connection quality.
	/// \return If the function succeeds, the return value is ConnectionQuality enum value.
	/// \if you don't in meeting, will return Conn_Quality_Unknow
	virtual ConnectionQuality GetVideoConnQuality() = 0;

	/// \brief Get audio connection quality.
	/// \return If the function succeeds, the return value is ConnectionQuality enum value.
	/// \if you don't in meeting, will return Conn_Quality_Unknow
	virtual ConnectionQuality GetAudioConnQuality() = 0;

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
};
END_ZOOM_SDK_NAMESPACE
#endif