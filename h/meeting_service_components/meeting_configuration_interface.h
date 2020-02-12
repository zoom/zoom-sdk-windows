/*!
* \file meeting_configuration_interface.h
* \brief Meeting Service Configuration Interface.
* Valid only for ZOOM style user interface mode.
*/
#ifndef _MEETING_Configuration_INTERFACE_H_
#define _MEETING_Configuration_INTERFACE_H_
#include "..\zoom_sdk_def.h"
#include "..\customized_resource_helper_interface.h"

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
		REQUIRED_INFO_TYPE_MeetingIDAndScreenName,///<The user needs to enter the screen name and the meeting id,via the InputMeetingMeetingIDAndScreenName() to specify the necessary information.
	};

	/// \brief Get the type of required information to be completed.
	/// \return If the function succeeds, the return is enumerated in RequiredInfoType enum.
	virtual RequiredInfoType GetRequiredInfoType() = 0;
 
	/// \brief Complete the password and screen name information.
	/// \remarks The SDK will destroy the object instance after calling this function. Supplement with the correct information.
	virtual bool InputMeetingPasswordAndScreenName(const wchar_t* meetingPassword, const wchar_t* screenName) = 0;

	/// \brief Complete the meeting id and screen name information.
	/// \remarks The SDK will destroy the object instance after calling this function. Supplement with the correct information.
	virtual bool InputMeetingIDAndScreenName(const wchar_t* meetingID, const wchar_t* screenName) = 0;

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


/// \deprecated This interface will be deprecated, please stop using it. 
/// \brief Reminder handler of ending free meeting.
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

enum SDKInviteDlgTabPage
{
	SDK_INVITEDLG_TAB_EMAILCONTACT = 0, ///<'Invite by Email' tab page
	SDK_INVITEDLG_TAB_PHONECONTACT, ///<'Invite by Phone' tab pag
	SDK_INVITEDLG_TAB_ROOMSYSTEM, ///<'Invite a Room System' tab page
};

enum SDKH323TabPage
{
	SDK_INVITEDLG_H323_DIALIN = 0, ///<'Dial In' sub-tab page under Room System invitation tab page
	SDK_INVITEDLG_H323_CALLOUT, ///<'Call Out' sub-tab page under Room System invitation tab page
};
/// \brief Free meeting event handler.
///
class IMeetingConfigurationFreeMeetingEvent
{

public:
	/*! \enum FreeMeetingNeedUpgradeType
		\brief Upgrade types of free meeting.
		Here are more detailed structural descriptions. 
	*/		
	enum FreeMeetingNeedUpgradeType
	{
		FreeMeetingNeedUpgradeType_NONE,///<Initialization.
		FreeMeetingNeedUpgradeType_BY_ADMIN,///<It is necessary for administrator to upgrade the free meeting.
		FreeMeetingNeedUpgradeType_BY_GIFTURL,///<Upgrade the free meeting by the gift link.
	};
	/// \brief The SDK will trigger this callback event during the free meeting to inform the user how much time is left for a free meeting.
	/// \param leftTime The left time of meeting calculated in seconds.
	virtual void onFreeMeetingRemainTime(unsigned int leftTime) = 0;
	/// \brief The callback of free meeting stops the countdown. 
	virtual void onFreeMeetingRemainTimeStopCountDown() = 0;

	/// \deprecated The backend design is changed and the function will be deleted.
	virtual void onFreeMeetingEndingReminderNotification(IFreeMeetingEndingReminderHandler* handler_) = 0;

	/// \brief The callback of upgrading the free meeting.
	/// \param type_ Type of upgrading the free meeting, see \link FreeMeetingNeedUpgradeType \endlink enum.
	/// \param gift_url Upgrade the free meeting by the gift link. When and only when the value of type_ is FreeMeetingNeedUpgradeType_BY_GIFTURL, this parameter is meaningful.
	virtual void onFreeMeetingNeedToUpgrade(FreeMeetingNeedUpgradeType type_, const wchar_t* gift_url) =0;
	
	/// \brief Callback function of starting to upgrade the free meeting by the gift link.
	virtual void onFreeMeetingUpgradeToGiftFreeTrialStart() = 0;
	
	/// \brief Callback function of ending upgrade the free meeting by the gift link.
	virtual void onFreeMeetingUpgradeToGiftFreeTrialStop() = 0;
	
	/// \brief Callback function of free meting upgrades successfully.
	virtual void onFreeMeetingUpgradeToProMeeting() = 0;
};
/// \brief Meeting configuration event callback.
///

class IMeetingConfigurationEvent : public IMeetingConfigurationFreeMeetingEvent
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
};

/*! \struct tagRedirectWarningMsgOption
    \brief Determine if the user handles the corresponding type of the warning message with user's own program.
    Here are more detailed structural descriptions.
*/
typedef struct tagRedirectWarningMsgOption
{
	bool bRedirectBadNetwork;///<TRUE indicates the user will handle the warning message of bad network with its own program.
	bool bRedirectWarnHighCPU;///<TRUE indicates the user will handle the warning message of high cpu with its own program.
	tagRedirectWarningMsgOption()
	{
		bRedirectBadNetwork = false;
		bRedirectWarnHighCPU = false;
	}

}RedirectWarningMsgOption;

/// \brief Meeting user configuration interface.
///
class IMeetingUIElemConfiguration
{
public:
	/// \brief Set the position of the primary view meeting window.
	/// \param pos Specify the position of the primary view meeting window. The coordinates of the window are those of the screen.
	virtual void SetMeetingUIPos(WndPosition pos) = 0;

	/// \brief Set the position of the floating video window when sharing. 	/// \param pos Specify the position of the floating video window when sharing.	/// \remarks The value shall be set before the sharing begins. If you set the value during the process of share, the function will not be valid until the next share.
	virtual void SetFloatVideoPos(WndPosition pos) = 0;

	/// \brief Set the visibility of the sharing toolbar. Default value: TRUE. 
	/// \param bShow TRUE means to enable the display sharing toolbar. Otherwise not.
	/// \remarks This function works only before the meeting or the sharing starts. 
	virtual void SetSharingToolbarVisibility(bool bShow) = 0;

	/// \brief Set the visibility of the toolbar at the bottom of the meeting window. Default value: TRUE.
	/// \param bShow TRUE means to enable the feature to display always the toolbar at the bottom. Otherwise not. 
	virtual void SetBottomFloatToolbarWndVisibility(bool bShow) = 0;

	/// \brief Set the visibility of the meeting ID in the title-bar. Default value: FALSE.
	/// \param bHide FALSE means to display the content. Otherwise not.
	virtual void HideMeetingInfoFromMeetingUITitle(bool bHide) = 0;

	/// \brief Set the meeting ID in the title-bar of the meeting window. 
	/// \param meetingNumber Specify the meeting ID in the title-bar of the meeting window.
	virtual void SetMeetingIDForMeetingUITitle(UINT64 meetingNumber) = 0;

	/// \brief Set the visibility of the dialog box when receiving the request of remote control during the meeting. Default value: TRUE.
	/// \param bEnable TRUE indicates to display the dialog box. FALSE not.
	///If it is FALSE, the user can deal with this request in the IMeetingRemoteCtrlEvent::onRemoteControlStatus() callback event sent by SDK when receiving the request of the remote control and then enters the sharing status at the end of callback event.
	virtual void EnableApproveRemoteControlDlg(bool bEnable) = 0;

	/// \brief Set the visibility of the dialog box when the request of the remote control is refused. Default value: TRUE.
	/// \param bEnable TRUE indicates to display the dialog box. FALSE not.
	///If it is FALSE, the user can deal with this request in the IMeetingRemoteCtrlEvent::onRemoteControlStatus() callback event sent by SDK when receiving the decline request of the remote control and then exists the sharing status at the end of callback event.
	virtual void EnableDeclineRemoteControlResponseDlg(bool bEnable) = 0;

	/// \brief Set the visibility of the LEAVE MEETING button on the pop-up dialogue box when the host leaves the meeting. Default value: TRUE.	/// \param bEnable TRUE indicates to display the button. Otherwise not.
	virtual void EnableLeaveMeetingOptionForHost(bool bEnable) = 0;

	/// \brief Set the visibility of the INVITE button in the toolbar during the meeting. Default value: TRUE.
	/// \param bEnable TRUE indicates to display the button. Otherwise not.
	/// \remarks The user will receive the IMeetingUIControllerEvent::onInviteBtnClicked() callback event when he clicks the INVITE button. If the callback event is not handled, the SDK will pop up a ZOOM custom invitation dialog.
	///The user will receive the IMeetingUIControllerEvent::onZoomInviteDialogFailed() callback event if the dialog box is failed to display.
	virtual void EnableInviteButtonOnMeetingUI(bool bEnable) = 0;

	/// \brief Set the visibility of the Video button in the toolbar during the meeting. Default value: TRUE.
	/// \param bEnable TRUE indicates to display the button. Otherwise not.
	virtual void EnableVideoButtonOnMeetingUI(bool bEnable) = 0;

	/// \brief Set the visibility of the Audio button in the toolbar during the meeting. Default value: TRUE.
	/// \param bEnable TRUE indicates to display the button. Otherwise not.
	virtual void EnableAudioButtonOnMeetingUI(bool bEnable) = 0;

	/// \brief Set the visibility of the buttons to enter or exit the full screen in the meeting window. Default value: TRUE.
	/// \param bEnable TRUE indicates to display the button. Otherwise not.
	virtual void EnableEnterAndExitFullScreenButtonOnMeetingUI(bool bEnable) = 0;

	/// \brief Set if it is able to switch between the full screen mode and normal mode by double-click. Default value: TRUE.
	/// \param bEnable TRUE indicates to switch. FALSE not.
	virtual void EnableLButtonDBClick4SwitchFullScreenMode(bool bEnable) = 0;

	/// \brief Set the visibility of the floating video window when sharing in the meeting. Default value: TRUE.
	/// \param bShow TRUE indicates to display the floating video window. FALSE not.
	virtual void SetFloatVideoWndVisibility(bool bShow) = 0;

	/// \brief Set if it is able to handle the event with user's own program by clicking START SHARE button in the meeting. Default value: FALSE.
	/// \param bRedirect TRUE indicates to deal with the event with user's own program. FALSE not.
	/// \remarks The SDK won't enable the share if the user calls this function and sets to convert. The user will deal with the subsequent logic after receiving the IMeetingUIControllerEvent::onStartShareBtnClicked() callback event. 
	virtual void RedirectClickShareBTNEvent(bool bRedirect) = 0;

	/// \brief Set if it is able to handle the event with user's own program by clicking END MEETING button in the meeting. Default value: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks The SDK won't end the meeting if the user calls this function and set to convert. The user will deal with the subsequent logic after receiving the IMeetingUIControllerEvent::onEndMeetingBtnClicked() callback event.
	virtual void RedirectClickEndMeetingBTNEvent(bool bRedirect) = 0;

	/// \brief An upgrade dialog box will pop up when the free meeting is over. Use this function to set if it is able to handle the reminder message with user's own program. Default value: FALSE. 
	/// \param bRedirect TRUE indicates to handle the reminder message with user's own program. FALSE not.
	/// \remarks The SDK will trigger the IMeetingConfigurationEvent::onFreeMeetingEndingReminderNotification() callback event when the meeting is over if the user calls this function to set the conversion.
	virtual void RedirectFreeMeetingEndingReminderDlg(bool bRedirect) = 0;

	/// \brief Set if it is able to handle the event with SDK user's own program by clicking CUSTOM LIVE STREAM button in the meeting. Default value: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks If the user calls this function to convert, the SDK will trigger the IMeetingUIControllerEvent::onCustomLiveStreamMenuClicked() instead of jumping to the live video page when clicking on the custom live stream, then deal with the subsequent logic.
	virtual void RedirectClickCustomLiveStreamMenuEvent(bool bRedirect) = 0;

	/// \brief Set if it is able to handle the event with SDK user's own program by clicking PARTICIPANT LIST button in the meeting. Default value: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks The list won't unfold by clicking participant list button if the user calls this function to set to convert. The SDK will trigger the IMeetingUIControllerEvent::onParticipantListBtnClicked(), and the user shall deal with the subsequent logic himself.	
	virtual void RedirectClickParticipantListBTNEvent(bool bRedirect) = 0;

	/// \brief Set if it is able to handle the event with SDK user's own program by clicking Closed Caption button in the meeting. Default value: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks If the user calls this function to convert, the SDK will trigger the IMeetingUIControllerEvent::onCCBTNClicked(), and the user shall deal with the subsequent logic himself.
	virtual void RedirectClickCCBTNEvent(bool bRedirect) = 0;

	/// \brief Set if it is able to handle the warning message with SDK user's own program in the meeting. Default value: None.
	/// \param redirectOption The parameter indicates the warning messages to be handled with user's own program.
	/// \remarks If the user calls this function to convert, the SDK will trigger the IMeetingServiceEvent::onMeetingStatisticsWarningNotification(), and the user shall deal with the subsequent logic himself.
	virtual void RedirectMeetingWarningMsg(RedirectWarningMsgOption redirectOption) = 0;

	/// \brief Set if it is able to temporarily show tooltip of the button in the toolbar of the meeting and user can close it by click the "x". Default value: TRUE. 
	/// \param bEnable TRUE indicates to enable to show the tooltip in the meeting. FALSE not.
	virtual void EnableToolTipsShow(bool bEnable) = 0;

	/// \brief Set the visibility of the introduction window when sharing on the iOS device. Default value: TRUE.
	/// \param bEnable TRUE indicates to display the introduction window when sharing on the iOS device. FALSE not.
	///	\remarks The SDK will trigger the IMeetingConfigurationEvent::onAirPlayInstructionWndNotification() callback event if the user calls this function to set to false, he shall deal with the subsequent logic himself.
	 virtual void EnableAirplayInstructionWindow(bool bEnable) = 0;

	/// \brief Set if it is able to retrieve the permission of host (when the original host gives up the host permission). Default value: TRUE.
	/// \param bEnable TRUE indicates that he can retrieve the permission of host. FALSE not.
	 /// \remarks The original host can always claim host and is not affected by this API.
	virtual void EnableClaimHostFeature(bool bEnable) = 0;

	/// \brief Set the visibility of the dialog box of choosing audio when joining the meeting. Default value: FALSE.
	/// \param bEnable TRUE indicates to hide the dialog box of choosing audio when joining the meeting. FALSE not.
	virtual void EnableAutoHideJoinAudioDialog(bool bEnable) = 0;

	/// \brief Set if it is able to display the preview window of the Meeting Controls on the task bar during sharing. Default value: FALSE.
	/// \param bAlwaysShow TRUE indicates to display always the icon on the task-bar. 
	virtual void AlwaysShowIconOnTaskBar(bool bAlwaysShow) = 0;

	/// \brief Set if it is able to enable split screen during the meeting. Default value: FALSE.
	/// \param bDisable TRUE indicates to disable the split screen. FALSE not.
	/// \remarks This function is valid only on the primary screen. Set the value to FALSE does not mean to enable the split screen due to other restrictions.
	virtual void DisableSplitScreenModeUIElements(bool bDisable) = 0;

	/// \brief Set the visibility of the SHARE COMPUTER SOUND check-box in the sharing window. Default value: TRUE.
	/// \param bShow TRUE indicates to display. FALSE not.
	virtual void SetShowAudioUseComputerSoundChkbox(bool bShow) = 0;

	/// \brief Set the visibility of the OPTIMIZE FOR FULL SCREEN VIDEO CLIP check-box in the sharing window. Default value: TRUE.
	/// \param bShow TRUE indicates to display. FALSE not.
	virtual void SetShowVideoOptimizeChkbox(bool bShow) = 0;

	/// \brief Set the visibility of PHONE CALL tab in the audio dialog box when joining the meeting. Default value: TRUE.
	/// \param bShow TRUE indicates to display the tab. FALSE not.
	virtual void SetShowCallInTab(bool bShow) = 0;

	/// \brief Set the visibility of CALL ME tab in the audio dialog box when joining the meeting. Default value: TRUE.
	/// \param bShow TRUE indicates to display the tab. FALSE not.
	virtual void SetShowCallMeTab(bool bShow) = 0;

	/// \brief Set if it is able to display always the meeting ID on the title bar of the window during the meeting. Default: False.
	/// \param bAlwaysShow TRUE indicates to display always the meeting ID. FALSE not.
	/// \remarks If it is FALSE, the program will execute ZOOM's default logic.
	virtual void SetAlwaysShowMeetingIDOnTitle(bool bAlwaysShow) = 0;
	
	///	\deprecated This function will be deprecated, please use ICustomizedResourceHelper.AddCustomizedStringResouce() instead.
	/// \brief Use the custom string to replace the specified menu item.
	/// \param customizedType Specify the menu item type. For more information, see \link SDKCustomizedStringType \endlink enum.
	/// \param customizedString Specify the custom string. You can set it to NULL to remove the custom string for the specified item.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If customizedString is not NULL with length zero(0), the return value is SDKERR_INVALID_PARAMETER.
	virtual SDKError SetUICustomizedString(SDKCustomizedStringType customizedType, const wchar_t* customizedString) = 0;

	/// \brief Whether to remove the topmost attribute of setting dialog. Default is not removed.
	/// \param bDisable TRUE indicates to remove. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError DisableTopMostAttr4SettingDialog(bool bDisable) = 0;

	/// \brief Set whether to close the current sharing of another user without prompt and directly beginning a new sharing content by the closer. Default value: FALSE(prompt).
	/// \param bEnable TRUE indicates no prompt. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableGrabShareWithoutReminder(bool bEnable) = 0;
	
	/// \brief Set the visibility of the SWITCH TO SINGLE PARTICIPANT SHARE dialog box when multiple participants are sharing and the user try to change the setting to single share. Default: TURE. 
	/// \param bEnable TRUE indicates to show dialog box if the multishare option is changed. FALSE not.
	/// \remarks If the dialog is disabled to show, you will retrieve IMeetingShareCtrlEvent::onMultiShareSwitchToSingleShareNeedConfirm callback event.
	virtual void EnableShowShareSwitchMultiToSingleConfirmDlg(bool bEnable) = 0;

	/// \brief Set the visibility of the REMAINING MEETING TIME button in the meeting. Default: FALSE. 
	/// \param bDisable TRUE indicates to hide the button when the free meeting need be reminded. FALSE not.
	/// \remarks If the button is disabled to show, you will retrieve IMeetingConfigurationEvent::onFreeMeetingRemainTime callback event.
	virtual void DisableFreeMeetingRemainTimeNotify(bool bDisable) = 0;

	/// \brief Set whether to display the button CHAT and menu item. Default is displaying.
	/// \param [in] bHide TRUE means hiding, otherwise not.
	virtual void HideChatItemOnMeetingUI(bool bHide) = 0;

	/// \brief Set whether to display the button RECORD and menu item. Default is displaying.
	/// \param [in] bHide TRUE means hiding, otherwise not.
	virtual void HideRecordItemOnMeetingUI(bool bHide) = 0;

	/// \brief Set whether to display the button UPGRADE when prompt the tooltip of free meeting counts down. Default is displaying.
	/// \param [in] bHide TRUE means hiding, otherwise not.
	virtual void HideUpgradeFreeMeetingButton(bool bHide) = 0;

	/// \brief Set the visibility of some specified tabs in the invite dialog. Default: Show all the content.
	/// \param tabPage Specify a tab page, see \link SDKInviteDlgTabPage \endlink enum.
	/// \param bShow TRUE indicates to display the tab. FALSE not.
	virtual void SetShowInviteDlgTabPage(SDKInviteDlgTabPage tabPage, bool bShow) = 0;

	/// \brief Set the visibility of some specified tabs in the Room System invitation dialog. Default: show all the content.Default: show all the content.
	/// \param tabPage Specify a tab, see \link SDKH323TabPage \endlink enum.
	/// \param bShow TRUE indicates to display the tab. FALSE not.
	virtual void SetShowH323SubTabPage(SDKH323TabPage tabPage, bool bShow) = 0;

	/// \brief Set the visibility of upgrade warning message for free user when the user schedules a meeting. Default: FALSE.
	/// \param bHide TRUE indicates to hide the warning message.FALSE not.
	virtual void HideUpgradeWarningMsgForFreeUserWhenSchedule(bool bHide) = 0;

	// \brief Set the visibility of the local recording convert progress bar dialog. Default: TRUE. 
	/// \param bShow TRUE indicates to show the dialog box. FALSE not.
	virtual void EnableLocalRecordingConvertProgressBarDialog(bool bShow) = 0;

	// \brief Set the visibility of Switch Camera button on 2nd camera share window,Default: TRUE. 
	/// \param bHide TRUE indicates to hide the Switch Camera button. FALSE not.
	virtual void HideSwitchCameraButton(bool bHide) = 0;

	// \brief Set the visibility of CopyURL button on invite window, Default: TRUE. 
	/// \param bHide TRUE indicates to hide, FALSE not.
	virtual void HideCopyUrlOnInviteWindow(bool bHide) = 0;

	// \brief Set the visibility of CopyInvitation button on invite window, Default: TRUE. 
	/// \param bHide TRUE indicates to hide, FALSE not.
	virtual void HideCopyInvitationOnInviteWindow(bool bHide) = 0;

	// \brief Set the visibility of Keypad button on meeting window, Default: TRUE. 
	/// \param bHide TRUE indicates to hide, FALSE not.
	virtual void HideKeypadButtonOnMeetingWindow(bool bHide) = 0;

	/// \brief Set whether to display the button REMOTE CONTROL and menu item. Default is displaying.
	/// \param [in] bHide TRUE means hiding, otherwise not.
	/// \remarks If the calling of API with parameter TRUE is successful, SDK will call EnableApproveRemoteControlDlg(false) by default.
	virtual void HideRemoteControlOnMeetingUI(bool bHide) = 0;
	
	/// \brief Set the visibility of Q&A on meeting UI. Default is displaying.
	/// \param [in] bHide TRUE means hiding, otherwise not.
	virtual void HideQAOnMeetingUI(bool bHide) = 0;

	/// \brief Set the visibility of poll on meeting UI. Default is displaying.
	/// \param [in] bHide TRUE means hiding, otherwise not.
	virtual void HidePollOnMeetingUI(bool bHide) = 0;

	/// \brief Set the ability to control the audio device in the meeting. Default is having the ability.
	/// \param [in] bDisable TRUE means having no ability, otherwise not.
	/// \This API is not recommended to call because once the bDsialbe is true, Zoom meeting may lose the control of the audio devices.
	virtual void DisableAdvanceAudioDeivceCtrl(bool bDisable) = 0;

	/// \brief Set if it is able to handle the event with SDK user's own program by clicking Audio button in the meeting. Default value: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks If the user calls this function to convert, the SDK will trigger the IMeetingUIControllerEvent::onAudioBtnClicked(AudioBtnClickedCallbackInfo info), and the user shall deal with the subsequent logic himself.
	virtual void RedirectClickAudioBTNEvent(bool bRedirect) = 0;

	/// \brief Set if it is able to handle the event with SDK user's own program by clicking Audio Menu button in the meeting. Default value: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks If the user calls this function to convert, the SDK will trigger the IMeetingUIControllerEvent::onAudioMenuBtnClicked(), and the user shall deal with the subsequent logic himself.
	virtual void RedirectClickAudioMenuBTNEvent(bool bRedirect) = 0;
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

	/// \brief Set the visibility of the dialog box of waiting for the host after joining the meeting. Only invalidate when the host is not in the meeting. Default: FALSE.
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
	
	/// \brief Force to enable the video when join meeting.	/// \param bEnable TRUE indicates to force to start video.	/// \remarks The default behavior depends on the configuration of the meeting.
	virtual void EnableForceAutoStartMyVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \brief Force to turn off video when joining the meeting.	/// \param bEnable TRUE indicates to force to turn off the video.	/// \remarks The default behavior depends on the configuration of the meeting.
	virtual void EnableForceAutoStopMyVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \brief Set the visibility of the dialog  SELECT JOIN AUDIO when joining meeting. Default: FALSE.
	/// \param bDisable TRUE indicates to hide the dialog box.
	virtual void DisableAutoShowSelectJoinAudioDlgWhenJoinMeeting(bool bDisable) = 0;

	/// \brief Set the visibility of the dialog box of joining a meeting. Default: FALSE.
	/// \param bDisable TRUE indicates to hide the dialog box. FALSE not.
	virtual void DisableShowJoinMeetingWnd(bool bDisable) = 0;
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
	/// Also, The meeting ID will be displayed as it is (not formatted).
	virtual void EnableLengthLimitationOfMeetingNumber(bool bEnable) = 0;

	/// \brief Set if it is able to share IOS device. Default: FALSE.
	/// \param bEnable TRUE indicates to enable to share. FALSE not.
	virtual void EnableShareIOSDevice(bool bEnable) = 0;

	/// \brief Set if it is able to share white board. Default: TRUE.
	/// \param bEnable TRUE indicates to enable to share on the white board. FALSE not.
	virtual void EnableShareWhiteBoard(bool bEnable) = 0;

	/// \brief Set whether to forbid multi-share. Default: FALSE.
	/// \param bDisable TRUE indicates to forbid multi-share. FALSE not.
	virtual void ForceDisableMultiShare(bool bDisable) = 0;

	/// \brief Set the maximum duration of the meeting when there is no attendee in the meeting. Default: 24*60.
	/// \param nDuration Specify the maximum duration in minutes.
	virtual void SetMaxDurationForOnlyHostInMeeting(int nDuration) = 0;

	/// \brief Set if it is able to leave the meeting when the screen is locked or the screen saver is shown. Default: TRUE.
	/// \param bEnable TRUE indicates to enable to share on the white board. FALSE not.
	/// \remarks No matter what value you set for API, the callback IMeetingServiceEvent::onOSSessionChangedNotification will be triggered.
	virtual void EnableLeaveMeetingWhenScreenLocked(bool bEnable) = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif