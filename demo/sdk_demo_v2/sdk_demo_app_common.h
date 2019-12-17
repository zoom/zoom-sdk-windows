#pragma once
#include "sdk_util.h"

enum GalleryViewSubscribeType
{
	GalleryView_Subscribe_CurrentPage = 0,
	GalleryView_Subscribe_PrePage,
	GalleryView_Subscribe_NextPage
};

enum ArrowButtonType
{
	Arrow_button_up = 0,
	Arrow_button_down,
};
enum ToolbarButtonType
{
	Button_All_Buttons = 0,
	Toolbar_Button_Audio,
	Toolbar_Button_Video,
	Toolbar_Button_Invite,
	Toolbar_Button_Chat,
	Toolbar_Button_Participant,
	Toolbar_Button_Share,
	Toolbar_Button_Leave,
	Toolbar_Button_ThumbnailVideo,
};
enum buttonStatusType
{
	Button_Enabled = 0,
	Button_Disabled,
	Button_HasUnreadMessage,
	Button_Muted,
	Button_UnMuted,
};

enum LoggedIn_MeetingUI_type
{
	Demo_Meeting_RestAPI_Start = 0,
	Demo_Meeting_RestAPI_Join_Meeting,
	Demo_Meeting_Join_Only,
	Demo_Really_LoggedIn,
	Demo_Leave_Meeting,
	//if needed, other types goes here
};
enum SettingsUI_page
{
	Setting_General_Page = 0,
	Setting_Audio_Page,
	Setting_Video_Page,
	Setting_VirtualBG_page,
	Setting_Recording_Page,
	Setting_UI_Custom_Page,
	Setting_Feature_Custom_Page,
};

enum SwitchToLoginUIType 
{
	SwitchToLoginUIType_AUTHDONE,
	SwitchToLoginUIType_MeetingEND,
	SwitchToLoginUIType_LOGOUT,
	SwitchToLoginUIType_LOGINFAILED,
	SwitchToLoginUIType_MEETINGFAILED,
};

enum SDKShareType
{
	SDK_SHARE_DESKTOP = 0,
	SDK_SHARE_WHITEBOARD,
	SDK_SHARE_APP,
};

inline bool IsInMeeting(ZOOM_SDK_NAMESPACE::MeetingStatus status)
{
	bool bInMeeting(true);
	if (status == ZOOM_SDK_NAMESPACE::MEETING_STATUS_IDLE ||
		status == ZOOM_SDK_NAMESPACE::MEETING_STATUS_ENDED ||
		status == ZOOM_SDK_NAMESPACE::MEETING_STATUS_FAILED)
	{
		bInMeeting = false;
	}

	return bInMeeting;
}

class CSDKDemoAppEvent
{
public:
	virtual void onSwitchToLoginUI(SwitchToLoginUIType type_) = 0;
	virtual void onQuitApp() = 0;
	virtual void onShowLoggedInUI(LoggedIn_MeetingUI_type nType_ = Demo_Really_LoggedIn) = 0;
	virtual void onLoginFailed() = 0;
	virtual void onJoinFailed() = 0;
	virtual void onShowSettingsUI(SettingsUI_page nPage = Setting_General_Page) = 0;
	virtual void onSwitchToScheduleMeetingUI() = 0;
	virtual void onSwitchToJoinMeetingForLoginUserUI() = 0;
	virtual void onShowChatWindow() = 0;
	virtual void onShowShareWindow() = 0;
	virtual void onShowGalleryViewWindow() = 0;
	virtual void onShowParticipantWindow() = 0;
	virtual void InitCustomizedUI() = 0;
	virtual void ActivateCustomizedUI() = 0;
	virtual void onShowMoreMenuWindow(int x, int y) = 0;
	virtual void onShowCameraControlWindow() = 0;
};
