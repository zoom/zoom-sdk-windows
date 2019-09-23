/*!
* \file meeting_configuration_interface.h
* \brief Configuration of Meeting Service Interface
*/
#ifndef _MEETING_Configuration_INTERFACE_H_
#define _MEETING_Configuration_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Meeting Password And Screen Name Handler
///
class IMeetingPasswordAndScreenNameHandler
{
public:
	enum RequiredInfoType
	{
		REQUIRED_INFO_TYPE_NONE,
		REQUIRED_INFO_TYPE_Password, ///< if you want to join meeting, you need input password with api InputMeetingPasswordAndScreenName
		REQUIRED_INFO_TYPE_Password4WrongPassword,///< you input a wrong password, please input again with api InputMeetingPasswordAndScreenName
		REQUIRED_INFO_TYPE_PasswordAndScreenName,///< if you want to join meeting, you need input password and screen name with api InputMeetingPasswordAndScreenName
		REQUIRED_INFO_TYPE_ScreenName,///< if you want to join meeting, you need input screen name with api InputMeetingScreenName
	};

	/// \brief get the required information you need to input.
	virtual RequiredInfoType GetRequiredInfoType() = 0;

	/// \brief Input the meeting password and screen name, and release this object
	virtual bool InputMeetingPasswordAndScreenName(const wchar_t* meetingPassword, const wchar_t* screenName) = 0;

	/// \brief Input the meeting screen name, and release this object
	virtual bool InputMeetingScreenName(const wchar_t* screenName) = 0;

	// \brief cancel to input the meeting password and screen name, and release this object
	virtual void Cancel() = 0;
	virtual ~IMeetingPasswordAndScreenNameHandler() {};
};

/// \brief Register webinar Handler
///
class IWebinarNeedRegisterHandler
{
public:
	enum WebinarNeedRegisterType
	{
		WebinarReg_NONE,
		WebinarReg_By_Register_Url, //dynamic_cast to IWebinarNeedRegisterHandlerByUrl
		WebinarReg_By_Email_and_DisplayName,//dynamic_cast to IWebinarNeedRegisterHandlerByEmail
	};

	virtual WebinarNeedRegisterType GetWebinarNeedRegisterType() = 0;
	virtual ~IWebinarNeedRegisterHandler() {};
};

/// \brief Register webinar with url Handler
///
class IWebinarNeedRegisterHandlerByUrl : public IWebinarNeedRegisterHandler
{
public:
	/// \brief Get the webinar register url
	virtual const wchar_t* GetWebinarRegisterUrl() = 0;

	/// \brief Release object
	virtual void Release() = 0;
	virtual ~IWebinarNeedRegisterHandlerByUrl() {};
};

/// \brief Register webinar with email and screen name Handler
///
class IWebinarNeedRegisterHandlerByEmail : public IWebinarNeedRegisterHandler
{
public:
	/// \brief Input the register email and screen name, and release this object
	virtual SDKError InputWebinarRegisterEmailAndScreenName(const wchar_t* email, const wchar_t* screenName) = 0;

	// \brief cancel to input the the register email and screen name, and release this object
	virtual void Cancel() = 0;
	virtual ~IWebinarNeedRegisterHandlerByEmail() {};
};

/// \brief End other meeting to join the new meeting Handler
///
class IEndOtherMeetingToJoinMeetingHandler
{
public:
	virtual bool EndOtherMeeting() = 0;
	virtual void Cancel() = 0;
	virtual ~IEndOtherMeetingToJoinMeetingHandler() {};
};


/// \brief Free meeting ending reminder Handler
///
class IFreeMeetingEndingReminderHandler
{
public:
	enum FreeMeetingEndingReminderType
	{
		FreeMeetingEndingReminder_NONE,
		FreeMeetingEndingReminder_Can_UpgradeMeeting_ToPro_Once,
		FreeMeetingEndingReminder_Can_UpgradeAccount,
		FreeMeetingEndingReminder_Reminder,
		FreeMeetingEndingReminder_UpgradeMeeting_ToPro_Failed,
		FreeMeetingEndingReminder_UpgradeMeeting_ToPro_Success,
	};

	/// \brief get the reminder type.
	virtual FreeMeetingEndingReminderType GetType() = 0;

	/// \brief Upgrade meeting and release this object, only for FreeMeetingEndingReminder_Can_UpgradeMeeting_ToPro_Once
	virtual SDKError UpgradeMeeting() = 0;

	/// \brief Upgrade account and release this object, only for FreeMeetingEndingReminder_Can_UpgradeAccount
	virtual SDKError UpgradeAccount() = 0;

	// \brief cancel, and release this object
	virtual SDKError Cancel() = 0;
	virtual ~IFreeMeetingEndingReminderHandler() {};
};

/// \brief Meeting Configuration Event callback
///
class IMeetingConfigurationEvent
{
public:
	/// \brief meeting need password or screen name callback
	/// \param pHandler which will be invoked for when this message type is received.
	virtual void onInputMeetingPasswordAndScreenNameNotification(IMeetingPasswordAndScreenNameHandler* pHandler) = 0;

	/// \brief meeting need password or screen name callback
	/// \param bShow Specifies show or hide your own airplay instruction window.
	/// \param airhostName the airhost name displayed on ios device
	virtual void onAirPlayInstructionWndNotification(bool bShow, const wchar_t* airhostName) = 0;

	/// \brief webinar need register callback
	/// \param handler_ which will be invoked for when this message type is received.
	virtual void onWebinarNeedRegisterNotification(IWebinarNeedRegisterHandler* handler_) = 0;

	/// \brief meeting need to end other meeting to join this meeting callback
	/// \param handler_ which will be invoked for when this message type is received.
	virtual void onEndOtherMeetingToJoinMeetingNotification(IEndOtherMeetingToJoinMeetingHandler* handler_) = 0;

	/// \brief the notification of free meeting will ending callback
	/// \param handler_ which will be invoked for when this message type is received.
	virtual void onFreeMeetingEndingReminderNotification(IFreeMeetingEndingReminderHandler* handler_) = 0;
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

	/// \brief config hide or show input meeting screen name dialog
	/// \param bEnable specify hide or show input meeting screen name dialog, default is enable.
	/// if disable this option, you need to handle onInputMeetingPasswordAndScreenNameNotification event callback.
	virtual void EnableInputMeetingScreenNameDlg(bool bEnable) = 0;

	/// \brief Redirect webinar register logic to IMeetingConfigurationEvent
	/// \param bRedirect Redirect or not. if true, you will recv onWebinarNeedRegisterNotification in IMeetingConfigurationEvent
	/// \default is disable.
	virtual void RedirectWebinarNeedRegister(bool bRedirect) = 0;

	/// \brief Redirect end other to IMeetingConfigurationEvent
	/// \param bRedirect Redirect or not. if true, you will recv onEndOtherMeetingToJoinMeetingNotification in IMeetingConfigurationEvent
	/// \default is disable.
	virtual void RedirectEndOtherMeeting(bool bRedirect) = 0;

	// \brief Enable enter and exit full screen button on meeting ui. 
	/// \param bEnable Specifies enter and exit full screen button show or not in meeting window, default is enable.
	virtual void EnableEnterAndExitFullScreenButtonOnMeetingUI(bool bEnable) = 0;

	// \brief Enable left button double click for enter and exit full screen feature. 
	/// \param bEnable Specifies Enable or disable switch full screen mode via left button double click, default is enable.
	virtual void EnableLButtonDBClick4SwitchFullScreenMode(bool bEnable) = 0;

	/// \brief Set float video windows visibility flag
	/// \param bShow Specifies float video windows show or not during sharing.
	virtual void SetFloatVideoWndVisibility(bool bShow) = 0;

	/// \brief Pre-populate registration information of webinar
	/// \param email Specifies default email.
	/// \param username Specifies default username.
	virtual void PrePopulateWebinarRegistrationInfo(const wchar_t* email, const wchar_t* username) = 0;

	/// \brief Redirect click event of start share btn to IMeetingUIControllerEvent
	/// \param bRedirect Redirect or not. if true, you will recv onStartShareBtnClicked in IMeetingUIControllerEvent
	virtual void RedirectClickShareBTNEvent(bool bRedirect) = 0;

	/// \brief Redirect click event of end meeting btn to IMeetingUIControllerEvent
	/// \param bRedirect Redirect or not. if true, you will recv onEndMeetingBtnClicked in IMeetingUIControllerEvent
	virtual void RedirectClickEndMeetingBTNEvent(bool bRedirect) = 0;

	// \brief Enable tooltips popup window on meeting ui. 
	/// \param bEnable Specifies tooltips window show or not in meeting window, default is enable.
	virtual void EnableToolTipsShow(bool bEnable) = 0;

	/// \brief config hide or show the instruction window of IOS device sharing.
	/// \param bEnable specify hide or show the instruction window of IOS device sharing, default is enable.
	/// if disable this option, you need to handle onAirPlayInstructionWndNotification event callback to show or hide your own windows.
	virtual void EnableAirplayInstructionWindow(bool bEnable) = 0;

	/// \brief enable claim host feature.
	/// \param bEnable specify claim host feature enable or not, default is enable.
	virtual void EnableClaimHostFeature(bool bEnable) = 0;

	/// \brief Config DSCP.
	/// \param dscpAudio DSCP value for audio.
	/// \param dscpVideo DSCP value for video.
	/// \param bReset reset DSCP value.
	virtual void ConfigDSCP(int dscpAudio, int dscpVideo, bool bReset) = 0;

	/// \brief Redirect click event of participant list btn to IMeetingUIControllerEvent
	/// \param bRedirect Redirect or not. if true, you will recv onParticipantListBtnClicked in IMeetingUIControllerEvent
	virtual void RedirectClickParticipantListBTNEvent(bool bRedirect) = 0;

	/// \brief disable copy and paste feature when remote control.
	/// \param bDisable specify this feature disable or not, default is enable.
	virtual void DisableRemoteCtrlCopyPasteFeature(bool bDisable) = 0;

	/// \brief disable UI elements of split screen mode.
	/// \param bDisable specify this feature disable or not, default is enable.
	virtual void DisableSplitScreenModeUIElements(bool bDisable) = 0;

	/// \brief Enable auto hide join audio dialog when it shown
	/// \param bEnable specify this feature enable or not, default is disable.
	virtual void EnableAutoHideJoinAudioDialog(bool bEnable) = 0;

	/// \brief Enable hide the full phone number for pure call in user
	/// \param bHide specify this feature enable or not, default is not hide.
	virtual void EnableHideFullPhoneNumber4PureCallinUser(bool bHide) = 0;

	/// \brief Enable the length limitation of meeting number
	/// \param bEnable specify this feature enable or not, default is enable.
	virtual void EnableLengthLimitationOfMeetingNumber(bool bEnable) = 0;

	/// \brief Enable IOS device share
	/// \param bEnable specify this feature enable or not, default is enable.
	virtual void EnableShareIOSDevice(bool bEnable) = 0;

	/// \brief Enable White Board share
	/// \param bEnable specify this feature enable or not, default is enable.
	virtual void EnableShareWhiteBoard(bool bEnable) = 0;

	/// \brief Always show app icon on taskbar list
	/// \param bAlwaysShow specify always show or not, default is not.
	virtual void AlwaysShowIconOnTaskBar(bool bAlwaysShow) = 0;

	/// \brief Redirect free meeting will end message to IMeetingConfigurationEvent
	/// \param bRedirect Redirect or not. if true, you will recv onFreeMeetingEndingReminderNotification in IMeetingConfigurationEvent
	virtual void RedirectFreeMeetingEndingReminderDlg(bool bRedirect) = 0;

	/// \brief Show the 'Share computer sound' checkbox
	/// \param bShow specify to show the checkbox or not, default is true.
	virtual void SetShowAudioUseComputerSoundChkbox(bool bShow) = 0;

	/// \brief Show the 'Optimize for full screen video clip' checkbox
	/// \param bShow specify to show the checkbox or not, default is true.
	virtual void SetShowVideoOptimizeChkbox(bool bShow) = 0;
	
	/// \brief Show the 'Phone Call' tab
	/// \param bShow specify to hide the tab when it's value is false, default is true.
	virtual void SetShowCallInTab(bool bShow) = 0;

	/// \brief Show the 'Call Me' tab
	/// \param bShow specify to hide the tab when it's value is false, default is true.
	virtual void SetShowCallMeTab(bool bShow) = 0;

	/// \brief Force disable multiple share
	/// \param bDisable specify this feature disable or not, default is enable.
	virtual void ForceDisableMultiShare(bool bDisable) = 0;

	/// \brief Always show the Meeting ID information on the main video-window's title bar 
	/// \param bAlwaysShow specify to show the meeting id information on the windows's title bar always or not. If bAlwaysShow if false, the behavior will follow Zoom's default logic.Default is false.
	virtual void SetAlwaysShowMeetingIDOnTitle(bool bAlwaysShow) = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif