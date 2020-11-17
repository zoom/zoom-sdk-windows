# CHANGELOG

## Note

1.   Starting from 5.2.41727.0928, the Windows SDK requires building with Visual Studio 2019.
2.   If you would like to run the Windows SDK demo app directly, you may install the VS2019 runtime library:
     * https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads

3. **Starting from 4.6.15798.0403, all DLL files(\*.dll) and EXE files(\*.exe) cannot be re-signed. Please DO NOT re-sign or assign new digital signature to those files as assigning new digital signature on these files could lead to fatal errors.**

4. Our Zoom SDK and Zoom Client share some common resources in the OS, in order to allow Zoom client and Zoom client SDK app work at the same time, since v4.4.56616.1028, we renamed the filename of the following shared resources:
* `CptHost.exe` -> `zcscpthost.exe`
* `airhost.exe` -> `zcsairhost.exe`
* `CptService.exe` -> `zCSCptService.exe`

5. If you are using SDK versions before 4.6.15798.0403, kindly advise that **please do not re-sign / assign new digital signature to** the following files as assigning new digital signature on these files could lead to fatal errors:
   * **CptControl.exe**
   * **CptInstall.exe**
   * **CptHost.exe** / **zcscpthost.exe**
   * **airhost.exe** / **zcsairhost.exe**
   * **CptService.exe** / **zCSCptService.exe**
   * **CptShare.dll**
   * **zzhost.dll**
   * **zzplugin.dll**(Deprecated since v4.6.15074.0203)
   * **aomhost64.exe**
   * **zCrashReport.dll**
   * **libeay32.dll**
   * **ssleay32.dll**

6. SDK file structure has changed

**In order to further optimize the size of our SDK package, starting from this version, Zoom Windows SDK removes the installation package of `Microsoft VC90 runtime`. Please visit Microsoft's website to download and install the `Microsoft VC90 runtime` on your machine. Please also kindly consider adding the `Microsoft VC90 runtime` installation packages in your installation package when you publish your applications developed using Zoom Windows SDK.**

### New SDK Initialization method: Using JWT token
Introducing new SDK initialization method -- JWT token, which is more secure, more convenient, and more versatile.

* How to compose JWT token for SDK initialization

You may generate your JWT token using the online tool https://jwt.io/. **It is highly recommended to generate your JWT token in your backend server.**

JWT is generated with three core parts: Header, Payload, and Signature. When combined, these parts are separated by a period to form a token: aaaaa.bbbbb.cccc.

Please follow this template to compose your payload for SDK initialization:

** Header
```
{
  "alg": "HS256",
  "typ": "JWT"
}
```
** Payload
```
{
	       "appKey": "string", // Your SDK key
         "iat": long, // access token issue timestamp
         "exp": long, // access token expire timestamp, max: iat + 2 days
         "tokenExp": long // token expire timestamp, MIN:30 minutes
}
```
**The minimum value of `tokenExp` should be at least 30 minutes, otherwise, SDK will reject the authentication request.**
** Signature
```
HMACSHA256(
  base64UrlEncode(header) + "." +
  base64UrlEncode(payload),
  "Your SDK secret here"
)
```
You do not need to secret base64 encoded your signature. Once the JWT token is generated, please do not reveal it or publish it. **It is highly recommended to handle your SDK key and secret and generate JWT in a backend server to be consumed by your application. Do not generate JWT in a production application.**

## 2020-11-17 @ v5.2.42037.1112

## Added:
* Added new feature for supporting language interpreters within meetings. For more information regarding this feature, please visit https://support.zoom.us/hc/en-us/articles/360034919791-Language-interpretation-in-meetings-and-webinars  
The new interfaces can be found in `meeting_interpretation_interface.h`:
  * `IMeetingService.GetMeetingInterpretationController()`

* Added new interfaces to add/remove a video file as the virtual background.
  * `IVirtualBGSettingContext.IsAllowToAddNewVBItem`
  * `IVirtualBGSettingContext.isAllowToRemoveVBItem`
  * `IVirtualBGSettingContext.AddBGVideo(const wchar_t* file_path)`
  * `IVirtualBGSettingContext.RemoveBGVideo(IVirtualBGImageInfo* pRemoveVideo)`
  * `IVirtualBGSettingContext.GetBGVideoList`
  * `IVirtualBGSettingContext.UseBGVideo(IVirtualBGImageInfo* pImage)`
  * `IVirtualBGSettingContextEvent.OnVideoThumbReady(const wchar_t* file_path)`
  * `IVirtualBGSettingContextEvent.OnVideoThumbError(const wchar_t* file_path, VBVideoError error)`
  * `IVirtualBGSettingContextEvent.OnVideoPlayError(const wchar_t* file_path, VBVideoError error)`

* Added new interfaces to configure video settings.
  * `IVideoSettingContext.EnableHardwareEncode(bool bEnable, VIDEO_HARDWARE_ENCODE_TYPE encodeType)`
  * `IVideoSettingContext.IsHardwareEncodeEnabled(VIDEO_HARDWARE_ENCODE_TYPE encodeType)`
  * `IVideoSettingContext.GetFaceBeautyStrengthValue()`
  * `IVideoSettingContext.SetFaceBeautyStrengthValue(unsigned int beautyStrengthValue)`
  * `IVideoSettingContext.EnableLightAdaption(bool bEnable, VIDEO_LIGHT_ADAPTION_TYPE lightAdaptionType, double manualValue)`
  * `IVideoSettingContext.IsLightAdaptionEnabled()`
  * `IVideoSettingContext.GetLightAdaptionType()`
  * `IVideoSettingContext.GetLightAdaptionManualValue()`

* Added new interfaces to configure audio settings.
  * `IAudioSettingContext.GetSuppressBackgroundNoiseLevel()`
  * `IAudioSettingContext.SetSuppressBackgroundNoiseLevel(Suppress_Background_Noise_Level level)`
  * `IAudioSettingContext.EnableSyncButtonsOnHeadset(bool bEnable)`
  * `IAudioSettingContext.IsSyncButtonsOnHeadsetEnabled()`

* Added a new interface to allow user to use the video filter feature.
  * `ISettingService.GetVideoFilterSettings()`

* Added new callback to notify the end-user that their video subscription failed when using Custom Meeting UI
  * `ICustomizedVideoContainerEvent.onVideoRenderElementDestroyed(IVideoRenderElement* pElement)`

## Changed & Fixed:
* Fixed an issue that the `IMeetingChatController.SetParticipantsChatPriviledge` is not working properly.
* Fixed an issue that unable to send a chat to webinar using `IMeetingChatController.SendChat4WebinarMeeting`

## 2020-10-09 @ v5.2.41727.0928

## Added
* Upgraded Zoom default UI to match Zoom client 5.2.1.
* Added new video status to represent the case when the user is being asked to mute/unmute by the host/co-host.
```
enum VideoStatus
{
Video_ON, ///<Video is on.
Video_OFF, ///<Video is off.
Video_Mute_ByHost, ///<Video is muted by host.
};
```
* Added a new interface in IUserInfo to retrieve participantID
  * `IUserInfo.GetParticipantID()`
* Added Vietnamese and Italian language support.
```
enum SDK_LANGUAGE_ID
{
LANGUAGE_Unknow = 0,///<For initialization.
LANGUAGE_English,///<In English.
LANGUAGE_Chinese_Simplified,///<In simplified Chinese.
LANGUAGE_Chinese_Traditional,///<In traditional Chinese.
LANGUAGE_Japanese,///<In Japanese.
LANGUAGE_Spanish,///<In Spanish.
LANGUAGE_German,///<In German.
LANGUAGE_French,///<In French.
LANGUAGE_Portuguese,///<In Portuguese.
LANGUAGE_Russian,///<In Russian.
LANGUAGE_Korean,///<In Korean.
LANGUAGE_Vietnamese,///<In Vietnamese.
LANGUAGE_Italian,///<In Italian.
};
```
* Added a new interface for the feature "Allow participants to rename Themselves".
  * `IMeetingParticipantsController.AllowParticipantsToRename`
* Added a new interface for the feature "Allow participants to unmute Themselves".
  * `IMeetingParticipantsController.AllowParticipantsToUnmuteSelf`
* Added a new interface for the feature "Allow participants to chat".
  * `IMeetingChatController.SetParticipantsChatPriviledge(SDKChatPriviledge priviledge)`
* Added a new interface to allow the host/co-host to ask to unmute all participant's audio.
  * `IMeetingParticipantsController.AskAllToUnmute()`
* Added new interfaces to delete questions and answers in the webinar Q&A.
  * `IMeetingQAController.DeleteQuestion(const wchar_t* questionID)`
  * `IMeetingQAController.DeleteAnswer(const wchar_t* answerID)`
  * `IMeetingQAControllerEvent.OnDeleteQuestion(IList<const wchar_t*>* lstQuestionID, bool bSuccess)`
  * `IMeetingQAControllerEvent.OnDeleteAnswer(IList<const wchar_t*>* lstAnswerID, bool bSuccess)`
* Added new parameters in the initParam object to specify the video rendering mode.
  * `tagInitParam.videoRenderMode`
* Added a new interface to allow users to set the suppress background noise level.
  * `IAudioSettingContext.GetSuppressBackgroundNoiseLevel()`
  * `IAudioSettingContext.SetSuppressBackgroundNoiseLevel(Suppress_Background_Noise_Level level)`
* Added a new interface isH323User in IUser to check whether the user is an H.323 user.
  * `IUserInfo.IsH323User()`

## Changed & Fixed
* Refined the breakout room interfaces
  * `IMeetingBOControllerEvent.OnNewBroadcastMessageReceived(const wchar_t* strMsg)`
  * `IBOAttendee.SetEvent(IBOAttendeeEvent* pEvent)`
  * `IBOAttendee.RequestForHelp()`
  * `IBOAttendee.IsHostInThisBO()`
  * `IBOAdmin.SetEvent(IBOAdminEvent* pEvent)`
  * `IBOAdmin.JoinBOByUserRequest(const wchar_t* strUserID)`
  * `IBOAdmin.IgnoreUserHelpRequest(const wchar_t* strUserID)`
  * `IBOAdmin.BroadcastMessage(const wchar_t* strMsg)`
  * `IBOData.IsBOUserMyself(const wchar_t* strUserID)`
  * `IBOData.GetCurrentBoName()`
* Fixed an issue that passing the password and username with special characters results in error.
* Fixed an issue that passing NULL as the parameter of StartAppShare and StartMonitorShare in Custom UI results in error.
* Fixed an issue that using the customized xml file to customize the language may force SDK to use English as the default language.
* Fixed an issue that the password dialog cannot be shown correctly.
* Fixed an issue that the watermark is shown in the incorrect position after resizing the video view size.

## Deprecated & Removed:
* Removed `IMeetingWebinarController.AllowAttendeeChat()`
* Removed `IMeetingWebinarController.DisallowAttendeeChat()`

## 2020-06-30 @ v5.0.24433.0616

## Added
* Upgraded Zoom default UI to match Zoom client 5.0.
* Optimized the status of H.323 call out.
* Added new interfaces to allow the host to send messages to the attendees in the waiting room.
* Added a new interface to modify the 'meeting topic' in the 'meeting information' page.
  * `IMeetingUIController.SetMeetingTopic(const wchar_t* meetingtopic)`
* Added a new interface to hide the share button
  * `IMeetingUIElemConfiguration.HideShareButtonOnMeetingUI(bool bHide)`
* Added new interfaces to pause/resume the recording.
  * `IMeetingRecordingController.PauseRecording()`
  * `IMeetingRecordingController.ResumeRecording()`
  * `IMeetingRecordingController.PauseCloudRecording()`
  * `IMeetingRecordingController.ResumeCloudRecording()`
* Added new interfaces related to setting 'Always show video preview when joining a video meeting' feature.
  * `IVideoSettingContext.EnableVideoPreviewDialog(bool bEnable)`
  * `IVideoSettingContext.IsVideoPreviewDialogEnabled()`
* Added new interfaces to check whether the PMI option is enabled on the account.
  * `IQueryMeetingItemMeetingOptionHelper.isDisabledPMI()`


## Changed & Fixed

* Disable the "Remember Screen Name" feature.
* Fixed an issue that the “hide meeting information” interface does not work for the audio-only meeting.
* Fixed an issue that the `ChangeUserName` interface does not work for webinar attendee.
* Temporary remove the "Unmute all" interfaces.
  * Calling `IMeetingAudioController.UnMuteAudio(0)` won't unmute all.

## Deprecated & Removed
* `tagStartParam4APIUser` - Please use `tagStartParam4WithoutLogin`
* `tagStartParam4WithoutLogin.userToken`
* `tagStartParam.apiuserStart`
* `IMeetingUIElemConfiguration.HideMeetingInfoFromMeetingUITitle(bool bHide)`
* `IMeetingUIElemConfiguration.SetMeetingIDForMeetingUITitle(UINT64 meetingNumber)`
* `IMeetingUIElemConfiguration.SetAlwaysShowMeetingIDOnTitle(bool bAlwaysShow)`

## 2020-04-28 @ v4.6.21666.0428

## Added:
* Added support for AES 256-bit GCM encryption.
  * **Please plan to upgrade your SDK accordingly. See the announcement in [README](https://github.com/zoom/zoom-sdk-windows) for more information**

## Changed & Fixed:
* Upgraded OpenSSL to version 1.1.1e

## Deprecated
* Deprecated the interface to get user's email: `IUserInfo.GetEmail()`


## 2020-04-04 @ v4.6.15798.0403

## Added:
* Add a new interface to center the setting dialog
  * `ShowSettingDlgParam.bCenter`
* Add a new interface to enable the green border while performing screen sharing for Zoom UI and Custom UI
  * `IGeneralSettingContext.EnableGreenBorderWhenShare(bool bEnable)`
* Add new interfaces for the `Limit FPS when share` feature in the setting dialog
  * `IGeneralSettingContext.IsLimitFPSEnabledWhenShare()`
  * `IGeneralSettingContext.EnableLimitFPSWhenShare(bool bEnable)`
  * `IGeneralSettingContext.GetLimitFPSValueWhenShare()`
  * `IGeneralSettingContext.SetLimitFPSValueWhenShare(LimitFPSValue value)`
* Add a new interface to hide the "Find problem? Send report" button
  * `IMeetingConfiguration.HideSendingStatisticInfoReport(bool bHide)`
* Add new interfaces for customizing [breakout room](https://support.zoom.us/hc/en-us/articles/206476093-Getting-Started-with-Breakout-Rooms)
  * Interfaces can be found in `meeting_breakout_rooms_interface_v2.h`

* Add new callbacks for breakout room button events
  * `IMeetingUIElemConfiguration.RedirectClickBreakoutRoomButtonEvent(bool bRedirect)`
  * `IMeetingUIControllerEvent.onBreakoutRoomBtnClicked()`
* Add new interfaces and options for schedule meeting
  * New interfaces can be found in `premeeting_service_interface.h`

* Add new fields in `initParam`
  * `initParam.locale`
  * `initParam.log_file_size`
* Add a new interface to hide the Reaction button
  * `IMeetingUIElemConfiguration.HideReactionsOnMeetingUI(bool bHide)`
* Add a new interface to hide the meeting info button
  * `IMeetingUIElemConfiguration.HideMeetingInfoOnMeetingUI(bool bHide)`
* Add a new interface to check whether a user is talking or not
  * `IUserInfo.IsTalking()`
* Add a new interface `disableToolbarInviteButtonClickOriginAction`


## Changed & Fixed:
* Fixed the UNC link issue
* Fixed an issue that user could not join a meeting with vanityID
* Fixed an issue that certain features could still be available via short-cuts even if the corresponding button has hidden


## 2020-02-10 @ v4.6.15074.0203

## Added:
* Add new features in Zoom default UI
  * Allow Call-In Attendees to unmute in the webinar
  * Closed captioning in breakout sessions
  * View all participants' video in gallery view while screen sharing
  * Fully minimize toolbar when screen sharing
  * Notification when no sound is detected from the microphone
  * Annotation enhancements
  * Do not disturb automatically enabled when screen sharing
  * Reduced volume for entering/exiting chime
  * Rename meeting hosted with personal meeting ID
  * Rename webinar attendees
  * Send a message to participants in a waiting room
  * Merge participant's video and Audio
  * Option to select keyboard layout during remote control
  * Advanced noise suppression
  * Virtual background selection within video preview
  * Meeting reactions
  * View other participant's audio status
* Add support for the Korean language.
* Add support for the share page and the keyboard shortcut page under the setting tab.

## Changed & Fixed:
* Enhanced security and upgraded OpenSSL to 1.0.2u.
* Fixed an issue where the webinar chat was freezing for some users when the webinar had a large number of attendees.
* Fixed an issue where copy/paste was not working consistently for some users on Windows 10.

## 2019-12-16 @ v4.4.57220.1211

## Added:
* Add new interfaces for SDK initialization with JWT token.
  * `IAuthService.SDKAuth(AuthContext& authContext)`
* Add new interfaces for the Q&A feature in webinar.
  * `IMeetingService.GetMeetingQAController()`
  * `class IMeetingQAController`
* Add new interfaces to access virtual background.
  * `ISettingService.GetVirtualBGSettings()`
  * `class IVirtualBGSettingContext`
* Add a new interface to hide the audio button
  * `IMeetingUIElemConfiguration.EnableAudioButtonOnMeetingUI(bool bEnable)`
* Add new callbacks for the event when the audio button/menu is clicked.
  * `IMeetingUIControllerEvent.onAudioMenuBtnClicked()`
  * `IMeetingUIControllerEvent.onAudioBtnClicked(AudioBtnClickedCallbackInfo info)`
* Add a new interface to disable the show join meeting window
  * `IMeetingConfiguration.DisableShowJoinMeetingWnd(bool bDisable)`

## Changed & Fixed:
* Fixed an issue that the meeting restarts for a few times after pressing the end meeting button.

## 2019-11-04 @ v4.4.56616.1028

## Added
* Add a new interface to determine whether the user can do annotation in Custom UI
    * `ICustomizedAnnotationObj.CanDoAnnotation(bool& bCan)`
* Add a new interface to determine whether the annotation is disable in Custom UI   
    * `ICustomizedAnnotationObj.IsAnnoataionDisable()`
* Add a new interface to hide the key-pad-button on the meeting window
    * `IMeetingConfiguration.HideKeypadButtonOnMeetingWindow(bool bHide)`
* Add a new interface to hide the copy-url-button on invite window
    * `IMeetingConfiguration.HideCopyUrlOnInviteWindow(bool bHide)`
* Add a new interface to hide the copy-invitation-button on the invite window
    * `IMeetingConfiguration.HideCopyInvitationOnInviteWindow(bool bHide)`
* Add a new interface to show/hide Q&A on the meeting window
    * `IMeetingUIElemConfiguration.HideQAOnMeetingUI(bool bHide)`
* Add a new interface to show/hide poll on the meeting window
    * `IMeetingUIElemConfiguration.HidePollOnMeetingUI(bool bHide)`
* Add a new interface to config external proxy
    * `INetworkConnectionHelper.ConfigureProxy(ProxySettings& proxy_setting)`
* Add a new interface to hide the remote control button on the meeting window
    * `IMeetingConfiguration.HideRemoteControlOnMeetingUI(bool bHide)`
* Add a default parameter to `GetCustomizedAnnotationController(ICustomizedShareRender* pShareRender = NULL)`
  * `IAnnotationController.GetCustomizedAnnotationController(ICustomizedShareRender* pShareRender = NULL)`

## 2019-09-04 @ v4.4.55968.0904

## Added
*  Add a new interface to hide switch-camera-button on `ShareCameraWindow`
* `IMeetingConfiguration.HideSwitchCameraButton(bool bHide)`
*  Add a new interface to switch share to next camera when sharing the camera
* `IMeetingShareController.SwitchToShareNextCamera();`
*  Add a new interface to determine whether the user can switch to next camera when sharing the camera
* `IMeetingShareController.CanSwitchToShareNextCamera(bool& bCan);`
*  Add new interfaces in `IMeetingUIController` to allow swapping the position of the video view and the sharing view:
* `virtual SDKError SwapToShowShareViewOrVideo(bool bToDisplayShare) = 0;`
* `virtual SDKError IsDisplayingShareViewOrVideo(bool& bIsShare) = 0;`
* `virtual SDKError CanSwapToShowShareViewOrVideo(bool& bCan) = 0;`
*  Add a new interface to redirect the warning messages (e.g:"Resource Insufficient") and to trigger the callback `IMeetingServiceEvent.onMeetingStatisticsWarningNotification()`
* `IMeetingUIElemConfiguration.RedirectMeetingWarningMsg(RedirectWarningMsgOption redirectOption)`
*  Add a new interface `IMeetingAudioCtrlEvent.onHostRequestStartAudio()` and a new class `IRequestStartAudioHandler` to notify attendee when the host is requesting to enable microphone.
*  Add new callbacks for default devices(mic/speaker/camera) when they are selected or have changes:
* `IVideoSettingContextEvent.onDefaultCamDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName)`
* `IAudioSettingContextEvent.onDefaultMicDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName)`
* `IAudioSettingContextEvent.onDefaultSpeakerDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName)`
*  Add a parameter to the interface `IsAnnoataionDisable()` with a default value.
* `IAnnotationController.IsAnnoataionDisable(SDKViewType viewtype = SDK_FIRST_VIEW)`

## Changed & Fixed
*  Fixed an issue that the schedule meeting dialog is not shown
*  Fixed an issue that the video is turned off by default when starting a meeting with ZAK
*  Fixed an issue that replacing the Zoom icon in the main meeting window is not success
*  Fixed an issue that sharing with pairing code does not show the UI controls
*  Fixed an issue that the meeting ends right after starting a meeting
*  Optimized the `IMeetingAudioCtrlEvent.onUserActiveAudioChange()` callback so it will be triggered less frequent
*  Optimized the SDK initialization process by reducing the call to `newfitpanel:initallcontrol()`
*  Optimized the performance of `MuteAudio()` interface
*  Changed to hide the "Pause/Stop" buttons when the auto-recording feature is turned on


## 2019-07-15 @ v4.4.55130.0712

**Note**

Some default behavior in Zoom meeting has changed:
1. The sharing toolbar will be shown by default. If you want to hide the sharing toolbar, please call `IMeetingUIElemConfiguration.SetSharingToolbarVisibility(false)` explicitly in your app.
2. Once the local recording content is converting, the converting progress dialog will be shown by default. If you don't want to show this progress dialog, please call `IMeetingUIElemConfiguration.EnableLocalRecordingConvertProgressBarDialog(false)` explicitly in your app.

**Added**

* Introduced new Zoom meeting UI
* Added new interfaces for setting items
  * `IGeneralSettingContext.EnableDisplayReminderWindowWhenExit(bool bEnable)`
  * `IGeneralSettingContext.IsDisplayReminderWindowWhenExitEnabled()`
  * `IGeneralSettingContext.EnableShowMyMeetingElapseTime(bool bEnable)`
  * `IGeneralSettingContext.IsShowMyMeetingElapseTimeEnabled()`
  * `IGeneralSettingContext.IsCurrentOSSupportAccelerateGPUWhenShare()`
  * `IGeneralSettingContext.EnableAccelerateGPUWhenShare(bool& bEnable)`
  * `IGeneralSettingContext.IsAccelerateGPUWhenShareEnabled()`
  * `IGeneralSettingContext.EnableRemoteControlAllApplications(bool bEnable)`
  * `IGeneralSettingContext.IsRemoteControlAllApplicationsEnabled()`
  * `IAudioSettingContext.EnableEchoCancellation(bool bEnable)`
  * `IAudioSettingContext.IsEchoCancellationEnabled()`
  * `IRecordingSettingContextEvent.onCloudRecordingStorageInfo(INT64 storage_total_size, INT64 storage_used_size, bool allow_exceed_storage)`
  * `IRecordingSettingContext.SetRecordingSettingEvent(IRecordingSettingContextEvent* pEvent)`
  * `IRecordingSettingContext.CanGetCloudRecordingStorageInfo()`
  * `IRecordingSettingContext.GetCloudRecordingStorageInfo()`
  * `IRecordingSettingContext.GetRecordingManagementURL()`
  * `IRecordingSettingContext.CanGetRecordingManagementURL(bool& bEnable)`
  * `IRecordingSettingContext.EnableSelectRecordFileLocationAfterMeeting(bool bEnable)`
  * `IRecordingSettingContext.IsSelectRecordFileLocationAfterMeetingEnabled()`
  * `IRecordingSettingContext.EnableMultiAudioStreamRecord(bool bEnable)`
  * `IRecordingSettingContext.IsMultiAudioStreamRecordEnabled()`
  * `IRecordingSettingContext.EnableAddTimestampWatermark(bool bEnable)`
  * `IRecordingSettingContext.IsAddTimestampWatermarkEnabled()`
  * `IRecordingSettingContext.EnableOptimizeFor3rdPartyVideoEditor(bool bEnable)`
  * `IRecordingSettingContext.IsOptimizeFor3rdPartyVideoEditorEnabled()`
  * `IRecordingSettingContext.EnableShowVideoThumbnailWhenShare(bool bEnable)`
  * `IRecordingSettingContext.IsShowVideoThumbnailWhenShareEnabled()`
  * `IRecordingSettingContext.EnablePlaceVideoNextToShareInRecord(bool bEnable)`
  * `IRecordingSettingContext.IsPlaceVideoNextToShareInRecordEnabled()`
  * `IAccessibilitySettingContext.EnableAlwaysShowMeetingControls(bool bEnable)`
  * `IAccessibilitySettingContext.IsAlwaysShowMeetingControlsEnable(bool& bEnable)`
  * `ISettingService.GetAccessibilitySettings()`
* Added a new interface to hide the “Upgrade to Pro” text from the free meeting reminder message
  * `IMeetingUIElemConfiguration.HideUpgradeFreeMeetingButton(bool bHide)`
* Add a new parameter to the SDK initialization method to customize the log size, the range is from 1MB to 50MB per log file, and by default is 5MB. The maximum number of the log file is 5.
  * `tagInitParam.uiLogFileSize`
* Added a new interface to redirect bad network warning message
  * `IMeetingUIElemConfiguration.RedirectMeetingWarningMsg(RedirectWarningMsgOption redirectOption)`
* Added a new interface to show/hide the tabs in the setting dialog
  * `ISettingUIStrategy.ConfSettingDialogShownTabPage(SettingDlgShowTabPageOption showOption)`
* Added a new interface to show/hide video button
  * `IMeetingUIElemConfiguration.EnableVideoButtonOnMeetingUI(bool bEnable)`
* Redefined the return values of ZOOM_SDK_NAMESPACE::AuthResult. Added 2 new values:
  * `AUTHRET_OVERTIME`
  * `AUTHRET_NETWORKISSUE`
* Added a new interface to switch between the active video view and the sharing content view
  * `IMeetingUIController.SwitchVideoASView()`
* Added new examples in sdk_demo_v2

**Changed & Fixed**

* Modified to allow editing or deleting recurring meetings via SDK
* Hide the “End Other Meeting” dialog when the `redirectEndOtherMeeting(true)` is called
* Fixed an issue that when sharing specific window the desktop is shared
* Fixed an issue that when disabling the chat feature the message alert still pops up
* Fixed an issue that sometimes the Windows Electron SDK failed to load zzhost.dll
* Fixed an issue that the user’s info showed up as a string of random characters
* Fixed an issue that the meeting is ended at an unexpected time while only 1 user is in the meeting
* Fixed an issue that 3 black borders appear after calling `SetBottomFloatToolbarWndVisibility`

**Deprecated**

* IMeetingShareController.LockShare()
* IMeetingShareController.UnLockShare()
* IScheduleForUser.GetEmail()




## 2019-03-25 @ v4.3.1.47204.0325

**Added**

* A new refactorized demo project that provides clear instructions on how to implement major features
* Introduce new Zoom meeting UI
* Add new interfaces to control share viewer’s annotate privilege
* Add 1080p video support
* Add new interfaces to customize the sub-tab pages in H323 invite page and customize all tab pages in the invite dialog
* Add new interfaces to show/hide ‘chat’,’record’ buttons
* Add new EndMeeting reasons for IMeetingServiceEvent.onMeetingStatusChanged
* Add support audio/video option on start meeting with API User
* Add customize labels/logos/texts in the in-meeting UI

**Changed & Fixed**

* Fix an issue that the user is unable to show chat window when assigning the window to its parent window
* Fix an issue that the user is unable to get window handle when calling showParticipantListWnd
* FIx an issue that the Windows SDK crashes with "Out of Memory" error
* Remove remaining 10 minutes tooltips and support callback
* Fix an issue that the participant’s video is blur and shaken

**Deprecated**

* IFreeMeetingEndingReminderHandler
* IMeetingConfigurationFreeMeetingEvent.onFreeMeetingEndingReminderNotification
* SetUICustomizedString

## 2019-01-23 @ v4.3.0.30730.0118

**Added**
*	Support for closed caption
*	Support for multi-share setting
*	Support for controlling the device camera
*	New feature to customize the title of meeting UI
*	New feature to handle meeting reminder. The user can hide the reminder tooltip button and customize the reminder message
*	New logging feature that stores logs with the maximum size of 5MB.
*	New options to turn on/off the video and audio for API user.
*	A new method to join/start meeting directly via url, such as zoommtg://zoom.us/join?action=....

**Changed & Fixed**
*	An issue that the screen sharing set to 1 FPS when another API is called
*	An issue that cannot move floating video window to screen edge
*	An issue that cannot use chat under donet framework
*	An issue that IMeetingConfiguration::EnableAutoEndOtherMeetingWhenStartMeeting doesn’t work

**Coming in the future releases**
*	A new refactorized demo project that provides clear instructions on how to implement major features will come in the next release

## 2018-10-29 @ v4.1.30384.1029

* Support advanced share at API level
1. Share a selected area of desktop
2. Share only the computer audio
3. Share the camera

* Add more meeting configurations

* Bug fixes


## 2018-09-11 @ v4.1.31872.0905

* Support to direct share with ultrasonic

* Support to integrate with Outlook plugin

* Support Zoom meeting invite dialog by default

* Bug fixes

## 2018-08-20 @ v4.1.30420.0817

* Custom Meeting UI (support basic meeting function, except for Webinar and Breakout Session)

Meeting Service

meeting_webinar_interface.h
```
support common feature of webinar meeting in sdk layer
```

meeting_annotation_interface.h
```
add new interface to get customized annotation controller
```

meeting_chat_interface.h
```
1.add new callback  event for chat status changed.
onChatStautsChangedNotification
2.add new interface to send chat for webinar meeting.
SendChat4WebinarMeeting
3.add new interface to get current privilege status of chat session.
 GetChatStatus
```

meeting_configuration_interface.h
```
support redirect click evnet of custom live stream menu.
ClickCustomLiveStreamMenuEvent
```

meeting_recording_interface.h
```
1.add callback event for customized ui local recroding source changed
onCustomizedLocalRecordingSourceNotification
2.add new interface to request customized local recording source notification.
RequestCustomizedLocalRecordingSource
```

Setting Service
```
1.add more audio settings interface
IAudioSettingContext
2.add more video settings interface
IVideoSettingContext
3.support test audio mic and speaker
4.support video device preview
```

Customized UI support
```
./h/customized_ui
1.support customized video ui
2.support customized share ui
3.support local recording for customized ui
4.support customized annotation ui
5.support customized remote control
6.now don't support Q&A
7.now don't support Polling
```

## 2018-07-26 @ v4.1.28966.0727

The start meeting logic for API users has changed. Please read below before upgrading to this version.

### Added
Auth Service
```
add new callback event for zoom access token expired
ZOOM_SDK_NAMESPACE.IAuthServiceEvent.onZoomIdentityExpired
once received this event, you need to re-login again
```

Meeting Service

meeting_service_interface.h
```
1.support start or join meeting with meeting's vanity ID
2.add new start meeting method for without login user to replace old api user start meeting method
StartParam.StartParam4WithoutLogin
3.add new interface to get meeting password
ZOOM_SDK_NAMESPACE.IMeetingInfo.GetMeetingPassword
4.add new callback event for meeting parameter notification
ZOOM_SDK_NAMESPACE.IMeetingServiceEvent.onMeetingParameterNotification
```

meeting_configuration_interface.h
```
1. add callback event for webinar register notification
ZOOM_SDK_NAMESPACE.IMeetingConfigurationEvent.onWebinarNeedRegisterNotification
2.add callback event for end other meeting notification
ZOOM_SDK_NAMESPACE.IMeetingConfigurationEvent.onEndOtherMeetingToJoinMeetingNotification
3.add callback event for end other meeting notification
ZOOM_SDK_NAMESPACE.IMeetingConfigurationEvent.onFreeMeetingEndingReminderNotification
4. add new interfaces of meeting configuration
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.EnableInputMeetingScreenNameDlg
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.RedirectWebinarNeedRegister
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.RedirectEndOtherMeeting
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.EnableShareIOSDevice
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.EnableShareWhiteBoard
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.AlwaysShowIconOnTaskBar
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.RedirectFreeMeetingEndingReminderDlg
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.SetShowAudioUseComputerSoundChkbox
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.SetShowVideoOptimizeChkbox
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.SetShowCallInTab
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.SetShowCallMeTab
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.ForceDisableMultiShare
ZOOM_SDK_NAMESPACE.IMeetingConfiguration.SetAlwaysShowMeetingIDOnTitle
```

meeting_live_stream_interface.h
```
support live stream in sdk layer
```

meeting_participants_ctrl_interface.h
```
1. add new interfaces of meeting participants control
ZOOM_SDK_NAMESPACE.IMeetingParticipantsController.LowerHand
ZOOM_SDK_NAMESPACE.IMeetingParticipantsController.RaiseHand
ZOOM_SDK_NAMESPACE.IMeetingParticipantsController.MakeHost
ZOOM_SDK_NAMESPACE.IMeetingParticipantsController.CanbeCohost
ZOOM_SDK_NAMESPACE.IMeetingParticipantsController.AssignCoHost
ZOOM_SDK_NAMESPACE.IMeetingParticipantsController.RevokeCoHost
ZOOM_SDK_NAMESPACE.IMeetingParticipantsController.ExpelUser
ZOOM_SDK_NAMESPACE.IMeetingParticipantsController.CanReclaimHost
ZOOM_SDK_NAMESPACE.IMeetingParticipantsController.ReclaimHost
ZOOM_SDK_NAMESPACE.IMeetingParticipantsController.ReclaimHostByHostKey
2.add callback event for cohost change notification
ZOOM_SDK_NAMESPACE.IMeetingParticipantsCtrlEvent.onCoHostChangeNotification
```

meeting_recording_interface.h
```
1. add new interfaces of meeting recording control
ZOOM_SDK_NAMESPACE.IMeetingRecordingController.CanStartRecording
ZOOM_SDK_NAMESPACE.IMeetingRecordingController.CanAllowDisAllowLocalRecording
ZOOM_SDK_NAMESPACE.IMeetingRecordingController.StartCloudRecording
ZOOM_SDK_NAMESPACE.IMeetingRecordingController.StopCloudRecording
ZOOM_SDK_NAMESPACE.IMeetingRecordingController.IsSupportLocalRecording
ZOOM_SDK_NAMESPACE.IMeetingRecordingController.AllowLocalRecording
ZOOM_SDK_NAMESPACE.IMeetingRecordingController.DisAllowLocalRecording
2.add callback event for cloud recording status notification
ZOOM_SDK_NAMESPACE.IMeetingRecordingCtrlEvent.onCloudRecordingStatus
```

meeting_remote_ctrl_interface.h
```
add new interfaces of meeting recording control
ZOOM_SDK_NAMESPACE.IMeetingRemoteController.CanRequestControl
ZOOM_SDK_NAMESPACE.IMeetingRemoteController.IsHaveRemoteControlRight
ZOOM_SDK_NAMESPACE.IMeetingRemoteController.IsInRemoteControllingStatus
ZOOM_SDK_NAMESPACE.IMeetingRemoteController.EnterRemoteControllingStatus
ZOOM_SDK_NAMESPACE.IMeetingRemoteController.LeaveRemoteControllingStatus
```

meeting_sharing_interface.h
```
add new interfaces of meeting share control
ZOOM_SDK_NAMESPACE.IMeetingShareController.StartWhiteBoardShare
```

meeting_video_interface.h
```
1.add new interfaces of meeting video control
ZOOM_SDK_NAMESPACE.IMeetingVideoController.CanAskAttendeeToStartVideo
ZOOM_SDK_NAMESPACE.IMeetingVideoController.AskAttendeeToStartVideo
ZOOM_SDK_NAMESPACE.IMeetingVideoController.CanStopAttendeeVideo
ZOOM_SDK_NAMESPACE.IMeetingVideoController.StopAttendeeVideo
2.add callback event for host request to start video notification
ZOOM_SDK_NAMESPACE.IMeetingVideoCtrlEvent.onHostRequestStartVideo
```


## 2018-05-22 @ v4.1.25013.0522
### Added
1.c++ sdk
a> Configuration of Meeting Service Interface

support to config DSCP for audio video session

support to redirect click event of participant list button

support to disable copy and paste feature when remote control

support to disable UI elements of split screen mode

support to auto hide join audio dialog when it shown

support to enable hide the full phone number for pure call in user
b> H323 helper interface

support to get h323 device for current meeting

change the CallOutH323 interface

c> Sharing of Meeting Service Interface

support to block window form screen share without change windows's style

d>Meeting Service Interface

support to get meeting connect type

e> Setting Service Interface

support to enable or disable auto enter full screen video mode when view share

support to enable or disable always show name on video

support to enable or disable turn off video when join meeting

support to enable or disable original input of mic

support to enable or disable stereo audio

add new interface for statistic setting

f>L10n

add new language support(Italian Portuguese Russian)

2.c# sdk

add new c++ interface wrap

## 2017-12-25 @ v4.1.18127.1225
### Added

1.c++ sdk
    a> setting service

add SettingTabPage option in ShowSettingDlgParam

add EnableHDVideo and IsHDVideoEnabled interface in IVideoSettingContext

b> meeting service

add IsMeetingLocked interface in IMeetingService

rename GetMeetingConnQuality to GetSharingConnQuality in IMeetingService

support to get sending and receiving connection quality of audio/video/share session

b> meeting audio controller

fix onUserActiveAudioChange does not worked bugs in IMeetingAudioCtrlEvent

c>meeting configuration

add RedirectClickEndMeetingBTNEvent interface in IMeetingConfiguration

add EnableClaimHostFeature interface in IMeetingConfiguration

d> meeting share controller

add ShowSharingAppSelectWnd interface in IMeetingShareController

add share computer sound interface

IsSupportEnableShareComputerSound

EnableShareComputerSound

add optimize for full screen video clip interface:

IsSupportEnableOptimizeForFullScreenVideoClip

EnableOptimizeForFullScreenVideoClip

e>meeting ui controller

add onEndMeetingBtnClicked callback event in IMeetingUIControllerEvent

2.c# sdk

a>wrap new c++ interface and callback event

b>fix callback event does not worked issue


## 2017-11-01 @ v4.1.12147.1101

### Added

1.add two new callback events in IMeetingServiceEvent

a>onMeetingStatisticsWarningNotification :  Meeting statistics warning notification callback

b>onMeetingSecureKeyNotification : Meeting secure key notification, need to web backend and special account type support.

2.fix crash bug of sdk cleanup

3.minor bug fix

## 2017-10-10 @ v4.1.9658.1010

### Added

01.Interface refactoring

for details, please visit: https://developer.zoom.us/docs/windows/windows-sdk-refactor-details/

02.New interface of change inmeeting display user name and notification of inmeeting display user name changed

03.New interface of hide/show sharing frame window

04.Notification of active speaker

05.Support L10N customized

06.Notification of current sharing type

07.New interface of get current meeting id

08.New interface of hide video thumnails

09.New interface of pre-populate register email and user name when join webinar

10.Support select sharing app window customized

11.Notification of meeting ui action

12.New interface of change the main window to no video mode.

13.Notification of proxy detect complete

14.New interface of get call-in number list

15.Add more interface to get user information

16.Add more interface of meeting settings

17.New interface of split screen mode

18.New interface of schedule/edit meeting dialog, same as zoom windows client.

19.Support Airhost dialog customized

20.bug fix

## 2017-06-08 @ v4.0.35674.0608

### Added

1. Lock share status notify

2. Support switch video wall to next page feature

3. Support join leave VoIP feature

4. Support get meeting type feature

5. Support get user role feature

6. Breakout room feature enhancement

7. Webinar feature enhancement

8. Waiting room feature enhancement

9. More settings support:
    1> Support disable input meeting password dialog
    2> Allow or disallow "can unmute by self if mute by host" flag
    3> Support hide enter and exit full screen button

10. Bug fix

## 2017-04-12 @ v4.0.29637.0413

### Added

1. Webinar promote and depromote meeting status change notify

2. Join and leave Breakout room meeting status change notify

3. Show or hide invite button in meeting ui and callback invite button click message support

4. Add new interface for H323 password

5. Bug Fix

## 2017-03-10 @ 4.0.26042.0307

### Added

1. Add host change callback

2. Add spotlight video change callback

3. Add self record privilige change callback

4. Add Low Or Raise Hand Status change callback

5. Bug Fix

## 2017-03-02 @ v4.0.22918.0213

### Added

1. Enhancement of proxy
   zoom_sdk.h
    - New interface:
		SDK_API SDKError CreateNetworkConnectionHelper(INetworkConnectio Helper** ppNetworkHelper);
        network_connection_handler_interface.h
    - New callback event:
        virtual void onProxySettingNotification(IProxySettingHandler* handler) = 0;

2. Enhancement of SSL cert Verification
   zoom_sdk.h
    - New interface:
    	SDK_API SDKError CreateNetworkConnectionHelper(INetworkConnectionHelper** ppNetworkHelper);
    	network_connection_handler_interface.h
    - New callback event:
    	virtual void onSSLCertVerifyNotification(ISSLCertVerificationHandler* handler    ) = 0;

3. Video/Audio session connection quality API
    meeting_service_interface.h
    - New interface:
       virtual ConnectionQuality GetAudioConnQuality() = 0;
       virtual ConnectionQuality GetVideoConnQuality() = 0;

4. Bugs fix

## 2017-02-10 @ v4.0.21754.0118

### Added

1. Support waiting room

2. Support embedded browser feature

3. Refine the sdk demo project, add VS2015 support

5. Bug Fix

## 2017-01-20 @ v3.6.12148.1115

### Added

1. Support to join Webinar meeting with as Panelist Support to pin/spotlight video

2. Support to pause/resume screen sharing Support H.323/SIP callout directly

3. Support invite by Phone andCall Medirectly

4. Add watermark - Powered by Zoom

5. Support to start/join meeting without audio

6. Support to start/join meeting without video

7. Support Multi-share

8. New interface in ISettingService

9. New interface in IMeetingConfiguration

10. Refine IMeetingService interface

## 2016-11-15

### Added

1. Add new interface for get windows handle

2. Fix branding issue in setting dialog, whiteboard and airhost window

3. Fix participant id don't take effect when start/join meeting

## 2016-10-05

### Added

1. fix leave meeting wnd cut off issue

## 2016-06-05

### Added

1. Support login zoom user
