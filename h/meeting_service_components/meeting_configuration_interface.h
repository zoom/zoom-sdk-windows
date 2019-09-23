/*!
* \file meeting_configuration_interface.h
* \brief Meeting Service Configuration Interface.
* Valid only for ZOOM style user interface mode.
*/
#ifndef _MEETING_Configuration_INTERFACE_H_
#define _MEETING_Configuration_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Meeting screen name and password handler.
/// \remarks If the user information is not completed, the SDK will take the instance of this class as a reference to remind the user to complete the information via IMeetingConfigurationEvent::onInputMeetingPasswordAndScreenNameNotification()callback.
class IMeetingPasswordAndScreenNameHandler
{
public:
	/*! \enum RequiredInfoType
		\brief Type of necessary information to join the meeting.
		Here are more detailed structural descriptions.
	*/
	enum RequiredInfoType
	{
		REQUIRED_INFO_TYPE_NONE,///<Initialization.
		REQUIRED_INFO_TYPE_Password, ///<The user needs to enter the password when joins the meeting. Via the InputMeetingPasswordAndScreenName() to specify the password information.
		REQUIRED_INFO_TYPE_Password4WrongPassword,///<If the password is invalid, the user needs to re-enter it. Via the InputMeetingPasswordAndScreenName() to specify the password information. 
		REQUIRED_INFO_TYPE_PasswordAndScreenName,///<The user needs to enter the screen name and the password,via the InputMeetingPasswordAndScreenName() to specify the necessary information.
		REQUIRED_INFO_TYPE_ScreenName,///<The user needs to enter the screen name. Via the InputMeetingPasswordAndScreenName() to specify the screen name information.
	};

	/// \brief Get the type of required information to be completed.
	/// \return If the function succeeds, the return is enumerated in RequiredInfoType enum.
	virtual RequiredInfoType GetRequiredInfoType() = 0;
 
	/// \brief Complete the password and screen name information.
	/// \remarks The SDK will destroy the object instance after calling this function. Supplement with the correct information.
	virtual bool InputMeetingPasswordAndScreenName(const wchar_t* meetingPassword, const wchar_t* screenName) = 0;

	/// \brief Complete the screen name.
	/// \remarks The SDK will destroy this object instance after calling this function. Complete the information by the correct function.
	virtual bool InputMeetingScreenName(const wchar_t* screenName) = 0;

	/// \brief Ignore the prompt of completing the information.
	/// \remarks The SDK will destroy this object instance after calling this function. 
	virtual void Cancel() = 0;
	virtual ~IMeetingPasswordAndScreenNameHandler() {};
};

/// \brief Webinar register handler.
///
class IWebinarNeedRegisterHandler
{
public:
	/*! \enum WebinarNeedRegisterType
		\brief Register type of webinar.
		Here are more detailed structural descriptions.
	*/
	enum WebinarNeedRegisterType
	{
		WebinarReg_NONE,///<Initialization.
		WebinarReg_By_Register_Url,///<Register webinar account by URL.
		WebinarReg_By_Email_and_DisplayName,///<Register webinar account by email and the screen name.
	};

	/// \brief Get the type to register. For more details, see \link WebinarNeedRegisterType \endlink enum.
	virtual WebinarNeedRegisterType GetWebinarNeedRegisterType() = 0;
	virtual ~IWebinarNeedRegisterHandler() {};
};

/// \brief Register webinar with URL Handler
///
class IWebinarNeedRegisterHandlerByUrl : public IWebinarNeedRegisterHandler
{
public:
	/// \brief Get the URL to register webinar.
	/// \return If the function succeeds, the return value is an URL.
	virtual const wchar_t* GetWebinarRegisterUrl() = 0;

	/// \brief Release object.
	virtual void Release() = 0;
	virtual ~IWebinarNeedRegisterHandlerByUrl() {};
};

/// \brief Webinar register with email and screen name Handler.
///
class IWebinarNeedRegisterHandlerByEmail : public IWebinarNeedRegisterHandler
{
public:
	/// \brief Configure the information of email and screen name.
	/// \remarks The SDK will destroy this object instance after calling this function. Supplement with the correct information.
	virtual SDKError InputWebinarRegisterEmailAndScreenName(const wchar_t* email, const wchar_t* screenName) = 0;

	/// \brief Ignore the prompt of the register.
	/// \remarks The SDK will destroy this object instance after calling this function.
	virtual void Cancel() = 0;
	virtual ~IWebinarNeedRegisterHandlerByEmail() {};
};

/// \brief End other meeting to join the new meeting Handler.
///
class IEndOtherMeetingToJoinMeetingHandler
{
public:
	/// \brief Close another ongoing meeting.
	/// \return TRUE indicates that the another ongoing meeting is closed successfully, and the instance will be destroyed. Otherwise not. 
	virtual bool EndOtherMeeting() = 0;
	
	/// \brief Ignore the prompt of closing another ongoing meeting.
	/// \remarks The SDK will destroy this object instance after calling this function.
	virtual void Cancel() = 0;
	virtual ~IEndOtherMeetingToJoinMeetingHandler() {};
};


/// \brief Reminder handler of ending free meeting.
///
class IFreeMeetingEndingReminderHandler
{
public:
	/*! \enum FreeMeetingEndingReminderType
		\brief Reminder type at the end of free meeting.
		Here are more detailed structural descriptions.
	*/
	enum FreeMeetingEndingReminderType
	{
		FreeMeetingEndingReminder_NONE,///<Initialization.
		FreeMeetingEndingReminder_Can_UpgradeMeeting_ToPro_Once,///<Upgrade to the priority meeting at once. 
		FreeMeetingEndingReminder_Can_UpgradeAccount,///<Upgrade the account.
		FreeMeetingEndingReminder_Reminder,///<Remind to pay.
		FreeMeetingEndingReminder_UpgradeMeeting_ToPro_Failed,///<Upgrade failed.
		FreeMeetingEndingReminder_UpgradeMeeting_ToPro_Success,///<Upgrade successfully.
	};

	/// \brief Get the reminder type of ending free meeting.
	virtual FreeMeetingEndingReminderType GetType() = 0;

	/// \brief Upgrade the meeting if the notification is the FreeMeetingEndingReminder_Can_UpgradeMeeting_ToPro_Once.
	/// \remarks The SDK will destroy this object instance after calling this function.
	virtual SDKError UpgradeMeeting() = 0;

	/// \brief Upgrade the account if the notification is the FreeMeetingEndingReminder_Can_UpgradeAccount.
	/// \remarks The SDK will destroy this object instance after calling this function.
	virtual SDKError UpgradeAccount() = 0;

	/// \brief Ignore the current notification.
	/// \remarks The SDK will destroy this object instance after calling this function.
	virtual SDKError Cancel() = 0;
	virtual ~IFreeMeetingEndingReminderHandler() {};
};

/*! \enum SDKCustomizedStringType
	\brief Custom string type.
	Here are more detailed structural descriptions.
	\remark Read the description of the each type carefully. You must follow the format to custom your own string. Wrong usage may cause unpredictable crash.
*/
enum SDKCustomizedStringType
{
	SDK_Customized_LiveStream_MenuString_LiveOn_String = 0,///<The new string must end up with "%s" so that the menu item can show correctly. This type is used to define a string to replace the menu item ON %S on live streaming. 
	SDK_Customized_LiveStream_MenuString_LiveView_String,///<The new string must end up with "%s" so that the menu item can show correctly. This type is used to define a string to replace the menu item VIEW STREAM ON %S on live streaming.
	SDK_Customized_LiveStream_MenuString_LiveStop_String,///<The new string must be a pure string so that it can show correctly. This type is used to define a string to replace the menu item STOP LIVE STREAM on live streaming.
	SDK_Customized_LiveStream_MenuString_CopyURL_String,///<The new string must be a pure string so that it can show correctly. This type is used to define a string to replace the menu item COPY STREAMING LINK on live streaming.
	SDK_Customized_Title_App,	///<The new string must be a pure string so that it can show correctly. This type is used to define a string to replace the title of the meeting video UI.
	SDK_Customized_Title_ZoomVideo,  ///<The new string must has the same format as "Zoom Participant ID: %s   Meeting ID: %s" so that it can show correctly. This type is used to define a string to replace the title of the meeting video UI.
	SDK_Customized_Title_FreeZoomVideo, ///<The new string must has the same format as "Zoom Participant ID: %s  %d-Minutes Meeting ID:%s" so that it can show correctly. This type is used to define a string to replace the title of the meeting video UI when the user is free user and in view-only status. 
	SDK_Customized_Title_ViewOnly_ZoomVideo, ///<The new string must end up with "%s" so that it can show correctly. This type is used to define a string to replace the title of the meeting video UI.
	SDK_Customized_Title_ViewOnly_FreeZoomVideo, ///<The new string must has the same format as "Zoom %d-Minutes Meeting ID: %s" so that it can show correctly. This type is used to define a string to replace the title of the meeting video UI when the user is free user and in view-only status. 
};
/// \brief Meeting configuration event callback.
///
class IMeetingConfigurationEvent
{
public:
	/// \brief The SDK will trigger the callback event if the password or screen name is required.
	/// \param pHandler A pointer to the instance, the user may use this object to operate. For more details, see \link IMeetingPasswordAndScreenNameHandler \endlink.
	virtual void onInputMeetingPasswordAndScreenNameNotification(IMeetingPasswordAndScreenNameHandler* pHandler) = 0;

	/// \brief This callback event may be triggered when the user enables the AirPlay introduction.
	/// \param bShow Show or hide the AirPlay instruction window. 
	/// \param airhostName The air-host name displayed on IOS device.
	virtual void onAirPlayInstructionWndNotification(bool bShow, const wchar_t* airhostName) = 0;

	/// \brief During the webinar, this callback event will be triggered if the user needs to register.
	/// \param handler_ An object pointer used by user to complete all the related operations. For more details, see \link IWebinarNeedRegisterHandler \endlink.
	virtual void onWebinarNeedRegisterNotification(IWebinarNeedRegisterHandler* handler_) = 0;

	/// \brief The user will receive this callback event if the user wants to join the new meeting while the ongoing meeting is not ended.
	/// \param handler_ An object pointer used by user to complete all the related operations. For more details, see \link IEndOtherMeetingToJoinMeetingHandler \endlink.
	virtual void onEndOtherMeetingToJoinMeetingNotification(IEndOtherMeetingToJoinMeetingHandler* handler_) = 0;

	/// \brief The SDK will trigger this callback event at the end of the free meeting to inform the user if he wants to upgrade the meeting.
	/// \param handler_ An object pointer used by user to complete all the related operations. For more details, see \link IFreeMeetingEndingReminderHandler \endlink.
	virtual void onFreeMeetingEndingReminderNotification(IFreeMeetingEndingReminderHandler* handler_) = 0;

	/// \brief The SDK will trigger this callback event during the free meeting to inform the user how many free time is left.
	/// \param leftTime The time left in seconds of the meeting.
	virtual void onFreeMeetingRemainTime(unsigned int leftTime) = 0;
};

/// \brief Meeting user configuration interface.
///
class IMeetingUIElemConfiguration
{
public:
	/// \brief Set the position of the primary view meeting window.
	/// \param pos Specify the position of the primary view meeting window. The coordinates of the window are those of the screen.
	virtual void SetMeetingUIPos(WndPosition pos) = 0;

	/// \brief Set the position of meeting window when the sharing begins. 
	/// \param pos Specify the position of meeting window when the sharing begins.
	/// \remarks The value shall be set before the sharing begins. If you set the value during the process of share, the function will not be valid until the next share.
	virtual void SetFloatVideoPos(WndPosition pos) = 0;

	/// \brief Set the visibility of the sharing toolbar. Default: FALSE. 
	/// \param bShow TRUE indicates enable to display the sharing toolbar. FALSE not. 
	virtual void SetSharingToolbarVisibility(bool bShow) = 0;

	/// \brief Set the visibility of the toolbar at the bottom of the meeting window. Default: TRUE.
	/// \param bShow TRUE indicates enable to display always the toolbar at the bottom. FALSE not. 
	virtual void SetBottomFloatToolbarWndVisibility(bool bShow) = 0;

	/// \brief Set the visibility of the meeting ID in the title bar. Default: FALSE.
	/// \param bHide False indicates to display the content. True no.
	virtual void HideMeetingInfoFromMeetingUITitle(bool bHide) = 0;

	/// \brief Set the meeting ID in the title bar of the meeting window. 
	/// \param meetingNumber Specify the meeting ID in the title bar of the meeting window.
	virtual void SetMeetingIDForMeetingUITitle(UINT64 meetingNumber) = 0;

	/// \brief Set the visibility of the dialog box when receiving the request of remote control during the meeting. Default: TRUE.
	/// \param bEnable TRUE indicates to display the dialog box. FALSE not.
	///If it is FALSE, the user can deal with this request in the IMeetingRemoteCtrlEvent::onRemoteControlStatus() callback event sent by SDK when receiving the request of the remote control and then enters the sharing status at the end of callback event.
	virtual void EnableApproveRemoteControlDlg(bool bEnable) = 0;

	/// \brief Set the visibility of the dialog box when the request of the remote control is refused. Default: TRUE.
	/// \param bEnable TRUE indicates to display the dialog box. FALSE not.
	///If it is FALSE, the user can deal with this request in the IMeetingRemoteCtrlEvent::onRemoteControlStatus() callback event sent by SDK when receiving the decline request of the remote control and then exists the sharing status at the end of callback event.
	virtual void EnableDeclineRemoteControlResponseDlg(bool bEnable) = 0;

	/// \brief Set the visibility of the LEAVE MEETING button when the host leaves the meeting. Default: TRUE.
	/// \param bEnable TRUE indicates to display the button. FALSE not.
	virtual void EnableLeaveMeetingOptionForHost(bool bEnable) = 0;

	/// \brief Set the visibility of the INVITE button in the toolbar during the meeting. Default value: TRUE.
	/// \param bEnable True indicates to display the button. FALSE not.
	/// \remarks The user will receive the IMeetingUIControllerEvent::onInviteBtnClicked() callback event when he clicks the INVITE button. If the callback event is not handled, the SDK will pop up a ZOOM custom invitation dialog.
	///The user will receive the IMeetingUIControllerEvent::onZoomInviteDialogFailed() callback event if the dialog box is failed to display.
	virtual void EnableInviteButtonOnMeetingUI(bool bEnable) = 0;

	/// \brief Set the visibility of the buttons to enter or exit the full screen in the meeting window. Default: TRUE.
	/// \param bEnable TRUE indicates to display the button. FALSE not.
	virtual void EnableEnterAndExitFullScreenButtonOnMeetingUI(bool bEnable) = 0;

	/// \brief Set if it is able to switch between the full screen mode and normal mode by double-click. Default: TRUE.
	/// \param bEnable TRUE indicates to switch. FALSE not.
	virtual void EnableLButtonDBClick4SwitchFullScreenMode(bool bEnable) = 0;

	/// \brief Set the visibility of the floating video window when sharing in the meeting. Default: TRUE.
	/// \param bShow TRUE indicates to display the floating video window. FALSE not.
	virtual void SetFloatVideoWndVisibility(bool bShow) = 0;

	/// \brief Set if it is able to handle the event with user's own program by clicking START SHARE button in the meeting. Default: FALSE.
	/// \param bRedirect TRUE indicates to deal with the event with user's own program. FALSE not.
	/// \remarks The SDK won't enable the share if the user calls this function and sets to convert. The user will deal with the subsequent logic after receiving the IMeetingUIControllerEvent::onStartShareBtnClicked() callback event. 
	virtual void RedirectClickShareBTNEvent(bool bRedirect) = 0;

	/// \brief Set if it is able to handle the event with user's own program by clicking END MEETING button in the meeting. Default: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks The SDK won't end the meeting if the user calls this function and set to convert. The user will deal with the subsequent logic after receiving the IMeetingUIControllerEvent::onEndMeetingBtnClicked() callback event.
	virtual void RedirectClickEndMeetingBTNEvent(bool bRedirect) = 0;

	/// \brief An upgrade dialog box will pop up when the free meeting is over. Use this function to set if it is able to handle the reminder message with user's own program. Default: FALSE. 
	/// \param bRedirect TRUE indicates to handle the reminder message with  user's own program. FALSE not.
	/// \remarks The SDK will trigger the IMeetingConfigurationEvent::onFreeMeetingEndingReminderNotification() callback event when the meeting is over if the user calls this function to set the conversion.
	virtual void RedirectFreeMeetingEndingReminderDlg(bool bRedirect) = 0;

	/// \brief Set if it is able to handle the event with SDK user's own program by clicking CUSTOM LIVE STREAM button in the meeting. Default: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks If the user calls this function to convert, the SDK will trigger the IMeetingUIControllerEvent::onCustomLiveStreamMenuClicked() instead of jumping to the live video page when clicking on the custom live stream, then deal with the subsequent logic.
	virtual void RedirectClickCustomLiveStreamMenuEvent(bool bRedirect) = 0;

	/// \brief Set if it is able to handle the event with SDK user's own program by clicking PARTICIPANT LIST button in the meeting. Default: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks The list won't unfold by clicking participant list button if the user calls this function to set to convert. The SDK will trigger the IMeetingUIControllerEvent::onParticipantListBtnClicked(), and the user shall deal with the subsequent logic himself.	
	virtual void RedirectClickParticipantListBTNEvent(bool bRedirect) = 0;

	/// \brief Set if it is able to handle the event with SDK user's own program by clicking Closed Caption button in the meeting. Default: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks If the user calls this function to convert, the SDK will trigger the IMeetingUIControllerEvent::onCCBTNClicked(), and the user shall deal with the subsequent logic himself.
	virtual void RedirectClickCCBTNEvent(bool bRedirect) = 0;

	/// \brief Set if it is able to show tool-tip in the meeting. Default: TRUE. 
	/// \param bEnable TRUE indicates to enable the tool-tip in the meeting.
	virtual void EnableToolTipsShow(bool bEnable) = 0;

	/// \brief Set the visibility of the introduction window when sharing on the IOS device. Default: TRUE.
	/// \param bEnable TRUE indicates to display the introduction window when sharing on the IOS device. FALSE not.
	///	\remarks The SDK will trigger the IMeetingConfigurationEvent::onAirPlayInstructionWndNotification() callback event if the user calls this function to set to false, he shall deal with the subsequent logic himself.
	 virtual void EnableAirplayInstructionWindow(bool bEnable) = 0;

	/// \brief Set if it is able to claim host. Default: TRUE.
	/// \param bEnable TRUE indicates to claim host. FALSE not.
	virtual void EnableClaimHostFeature(bool bEnable) = 0;

	/// \brief Set the visibility of the audio choose dialog box when joining the meeting. Default: FALSE.
	/// \param bEnable TRUE indicates to hide the audio choose dialog box when join the meeting. FALSE not.
	virtual void EnableAutoHideJoinAudioDialog(bool bEnable) = 0;

	/// \brief Set if it is able to display always the icon on the task-bar. Default: FALSE.
	/// \param bAlwaysShow TRUE indicates to display always the icon on the task-bar. 
	virtual void AlwaysShowIconOnTaskBar(bool bAlwaysShow) = 0;

	/// \brief Set if it is able to enable split screen during the meeting. Default: FALSE.
	/// \param bDisable TRUE indicates to disable the split screen. FALSE not.
	/// \remarks This function is valid only on the primary screen. Set the value to FALSE does not mean to enable the split screen due to other restrictions.
	virtual void DisableSplitScreenModeUIElements(bool bDisable) = 0;

	/// \brief Set the visibility of the SHARE COMPUTER SOUND check-box in the sharing window. Default: TRUE.
	/// \param bShow TRUE indicates to display. FALSE not.
	virtual void SetShowAudioUseComputerSoundChkbox(bool bShow) = 0;

	/// \brief Set the visibility of the OPTIMIZE FOR FULL SCREEN VIDEO CLIP check-box in the sharing window. Default: TRUE.
	/// \param bShow TRUE indicates to display. FALSE not.
	virtual void SetShowVideoOptimizeChkbox(bool bShow) = 0;

	/// \brief Set the visibility of PHONE CALL tab in the audio dialog box when join the meeting. Default value: TRUE.
	/// \param bShow TRUE indicates to display the tab. FALSE not.
	virtual void SetShowCallInTab(bool bShow) = 0;

	/// \brief Set the visibility of CALL ME tab in the audio dialog box when join the meeting. Default value: TRUE.
	/// \param bShow TRUE indicates to display the tab. FALSE not.
	virtual void SetShowCallMeTab(bool bShow) = 0;

	/// \brief Set if it is able to display always the meeting ID on the title bar of the window during the meeting. Default: False.
	/// \param bAlwaysShow TRUE indicates to display always the meeting ID. FALSE not.
	/// \remarks If it is false, the program will operate ZOOM's default logic.
	virtual void SetAlwaysShowMeetingIDOnTitle(bool bAlwaysShow) = 0;
	
	/// \brief Use the custom string to replace the specified menu item.
	/// \param customizedType Specify the menu item type. For more information, see \link SDKCustomizedStringType \endlink enum.
	/// \param customizedString Specify the custom string. You can set it to NULL to remove the custom string for the specified item.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If customizedString is not NULL with length zero(0), the return value is SDKERR_INVALID_PARAMETER.
	virtual SDKError SetUICustomizedString(SDKCustomizedStringType customizedType, const wchar_t* customizedString) = 0;

	virtual SDKError DisableTopMostAttr4SettingDialog(bool bDisable) = 0;

	virtual SDKError EnableGrabShareWithoutReminder(bool bEnable) = 0;
	
	/// \brief Set the visibility of the SWITCH TO SINGLE PARTICIPANT SHARE dialog box when multiple participants are sharing and the user try to change the setting to single share. Default: TURE. 
	/// \param bEnable TRUE indicates to show dialog box when join the meeting. FALSE not.
	/// \remarks If the dialog is disabled to show, you will retrieve IMeetingShareCtrlEvent::onMultiShareSwitchToSingleShareNeedConfirm callback event.
	virtual void EnableShowShareSwitchMultiToSingleConfirmDlg(bool bEnable) = 0;

	/// \brief Set the visibility of the REMAINING MEETING TIME button in the meeting. Default: FALSE. 
	/// \param bEnable TRUE indicates to hide the button when the free meeting need be reminded. FALSE not.
	/// \remarks If the button is disabled to show, you will retrieve IMeetingConfigurationEvent::onFreeMeetingRemainTime callback event.
	virtual void DisableFreeMeetingRemainTimeNotify(bool bDisable) = 0;
};

/// \brief Meeting connect configuration Interface
///
class IJoinMeetingBehaviorConfiguration
{
public:
	/// \brief Set the visibility of the dialog box if the password is wrong when join the meeting. Default: FALSE.
	/// \param bDisable TRUE indicates to hide the dialog box of wrong password.
	/// \remarks If it is disabled to display the dialog box of wrong password, the system will directly exit the state of trying to join the meeting.
	virtual void DisablePopupMeetingWrongPSWDlg(bool bDisable) = 0;

	/// \brief Set the visibility of the dialog box of waiting for the host after joining the meeting. Default: TRUE.
	/// \param bDisable TRUE indicates to hide the dialog box. FALSE not.
	virtual void DisableWaitingForHostDialog(bool bDisable) = 0;

	/// \brief Set if it is able to end automatically another ongoing meeting when joining a new meeting. Default: FALSE.
	/// \param bEnable TRUE indicates to end the other ongoing meetings. FALSE not.
	virtual void EnableAutoEndOtherMeetingWhenStartMeeting(bool bEnable) = 0;

	/// \brief Set the visibility of the dialog box to input the password. Default: TRUE.
	/// \param bEnable TRUE indicates to display the dialog box to input password. FALSE not.
	/// \remarks If it is disabled, the SDK will trigger IMeetingConfigurationEvent::onInputMeetingPasswordAndScreenNameNotification()callback event when the user is asked to re-enter the password, then the user shall deal with the subsequent logic. For more details, see \link IMeetingConfigurationEvent::onInputMeetingPasswordAndScreenNameNotification() \endlink.
	virtual void EnableInputMeetingPasswordDlg(bool bEnable) = 0;

	/// \brief Set the visibility of the dialog box to input the screen name. Default: TRUE.
	/// \param bEnable TRUE indicates to display the dialog box to input the screen name which is to be displayed in the meeting. FALSE not.
	/// \remarks If it is false, the SDK will trigger IMeetingConfigurationEvent::onInputMeetingPasswordAndScreenNameNotification()callback event when the user is asked to re-enter the screen name, then the user shall deal with the subsequent logic. For more details, see \link IMeetingConfigurationEvent::onInputMeetingPasswordAndScreenNameNotification() \endlink.
	virtual void EnableInputMeetingScreenNameDlg(bool bEnable) = 0;

	/// \brief Set if it is able to handle the webinar register process with user's own program in the meeting. Default: FALSE.
	/// \param bRedirect TRUE indicates to redirect. FALSE not. 
	/// \remarks If it is true, the SDK will trigger the IMeetingConfigurationEvent::onWebinarNeedRegisterNotification()callback event. For more details, see \link IMeetingConfigurationEvent::onWebinarNeedRegisterNotification() \endlink.
	virtual void RedirectWebinarNeedRegister(bool bRedirect) = 0;

	/// \brief Pre-set email and username information before joining the webinar.
	/// \param email Configure the default email.
	/// \param username Configure default username.
	virtual void PrePopulateWebinarRegistrationInfo(const wchar_t* email, const wchar_t* username) = 0;

	/// \brief Set if it is able to redirect the process to end another meeting by user's own program. Default: FALSE. 
	/// \param bRedirect TRUE indicates to redirect. FALSE not. If it is TRUE, the SDK will trigger the  IMeetingConfigurationEvent::onEndOtherMeetingToJoinMeetingNotification().
	/// \remarks This function doesn't work if the IJoinMeetingBehaviorConfiguration::EnableAutoEndOtherMeetingWhenStartMeeting(true) is also called. If redirect successfully, the SDK will trigger the IMeetingConfigurationEvent::onEndOtherMeetingToJoinMeetingNotification() callback event. For more details, see \link IMeetingConfigurationEvent::onEndOtherMeetingToJoinMeetingNotification() \endlink.
	virtual void RedirectEndOtherMeeting(bool bRedirect) = 0;
	/// \brief Set if it is able to force participants to start video when joining the meeting.
	/// \param bEnable TRUE indicates to force participants to start video.
	/// \remarks The default behavior depends on the configuration of the meeting.
	virtual void EnableForceAutoStartMyVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \brief Set if it is able to force participants to turn off video when joining the meeting.
	/// \param bEnable TRUE indicates to force participants to turn off video.
	/// \remarks The default behavior depends on the configuration of the meeting.
	virtual void EnableForceAutoStopMyVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \brief Set the visibility of the dialog  SELECT JOIN AUDIO when joining meeting. Default: FALSE.
	/// \param bDisable TRUE indicates to hide the dialog box.
	virtual void DisableAutoShowSelectJoinAudioDlgWhenJoinMeeting(bool bDisable) = 0;
};

/// \brief Meeting configuration interface.
///
class IMeetingConfiguration : 
public IMeetingUIElemConfiguration, 
public IJoinMeetingBehaviorConfiguration
{
public:
	/// \brief Set meeting configuration controller callback event handler.
	/// \param pEvent A pointer to the IMeetingConfigurationEvent that receives the configuration controller event. For more details, see \link IMeetingConfigurationEvent \endlink.
	virtual void SetEvent(IMeetingConfigurationEvent* pEvent) = 0;

	/// \brief Reset the meeting configuration and back to the default state.
	virtual void Reset() = 0;

	/// \brief Set the shared device ID when sharing directly.
	/// \param monitorID Specify the device ID to be shared. You may get the device ID by the system API EnumDisplayMonitors().
	virtual void SetDirectShareMonitorID(const wchar_t* monitorID) = 0;

	/// \brief Set if it is able to auto-adjust the volume of the speaker when joining the meeting. Default: TRUE.
	/// \param bEnable TRUE indicates to auto-adjust the volume of the speaker. FALSE not.
	/// \remarks If it is TRUE, the SDK will adjust the speaker volume automatically. It will unmute if the speaker was muted.
	virtual void EnableAutoAdjustSpeakerVolumeWhenJoinAudio(bool bEnable) = 0;

	/// \brief Set if it is able to auto-adjust the volume of the mic when joining the meeting. Default: TRUE.
	/// \param bEnable TRUE indicates to auto-adjust the volume of the mic. FALSE not.
	/// \remarks If it is TRUE, the SDK will adjust the mic volume automatically. It will unmute if the mic was muted.
	virtual void EnableAutoAdjustMicVolumeWhenJoinAudio(bool bEnable) = 0;

	/// \brief Configure DSCP(Differential services code point) values.  
	/// \param dscpAudio Configure DSCP value for audio.
	/// \param dscpVideo Configure DSCP value for video.
	/// \param bReset Reset DSCP values.
	/// \remarks This interface satisfies some users who have other requirements. It is not recommended to configure it. Contact the support engineer for more details.   
	virtual void ConfigDSCP(int dscpAudio, int dscpVideo, bool bReset) = 0;

	/// \brief Set if it is able to copy and paste for remote control. Default: FALSE.
	/// \param bDisable TRUE indicates that it is disabled to copy or paste. FALSE not.
	virtual void DisableRemoteCtrlCopyPasteFeature(bool bDisable) = 0;

	/// \brief Set if it is able to display the full phone number for the user who joins the meeting with phone. Default: FALSE.
	/// \param bHide TRUE indicates to hide the partial phone number. FALSE not. 
	/// \remarks If it is false, some figures of the number will be replaced by asterisk(*).
	virtual void EnableHideFullPhoneNumber4PureCallinUser(bool bHide) = 0;

	/// \brief Set if it is able to limit the length of meeting ID. Default: FALSE.
	/// \param bEnable TRUE indicates to limit the length of meeting ID. FALSE not.
	/// \remarks If it is enabled, the length of the meeting ID depends on the ID type. The ID shall be more than nine(9) figures or five(5) letters.
	virtual void EnableLengthLimitationOfMeetingNumber(bool bEnable) = 0;

	/// \brief Set if it is able to share IOS device. Default: FALSE.
	/// \param bEnable TRUE indicates to enable to share. FALSE not.
	virtual void EnableShareIOSDevice(bool bEnable) = 0;

	/// \brief Set if it is able to share white board. Default: TRUE.
	/// \param bEnable TRUE indicates to enable to share on the white board. FALSE not.
	virtual void EnableShareWhiteBoard(bool bEnable) = 0;

	/// \brief Set whether to forbid multi-share. Default: TRUE.
	/// \param bDisable TRUE indicates to forbid multi-share. FALSE not.
	virtual void ForceDisableMultiShare(bool bDisable) = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif