#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "sdk_init_auth_ui.h"
#include "LOGIN_sdk_login_UI.h"
#include "LoggedIn_sdk_controller_ui.h"
#include "sdk_demo_app_common.h"
#include "schedule_meeting_ui.h"
#include "settings_ui.h"
#include "Join_meeting_for_login_user_ui.h"
#include "custom_ui_mgr.h"
#include "more_menu_ui.h"
class CSDKDemoApp : public CSDKDemoAppEvent
{
public:
	CSDKDemoApp();
	virtual ~CSDKDemoApp();

	void Run(HINSTANCE hInstance);
	void Stop();
	virtual void onSwitchToLoginUI(SwitchToLoginUIType type_);
	virtual void onShowLoggedInUI(LoggedIn_MeetingUI_type nType_= Demo_Really_LoggedIn);
	virtual void onQuitApp();
	virtual void onLoginFailed();
	virtual void onJoinFailed();
	virtual void onShowSettingsUI(SettingsUI_page nPage = Setting_General_Page);
	virtual void onSwitchToScheduleMeetingUI();
	virtual void onSwitchToJoinMeetingForLoginUserUI();
	virtual void InitCustomizedUI(); 
	virtual void ActivateCustomizedUI();	
	virtual void onShowChatWindow();
	virtual void onShowShareWindow();
	virtual void onShowGalleryViewWindow();
	virtual void onShowParticipantWindow();
	virtual void onPageButtonClick(ArrowButtonType btnType);
	virtual void onShowMoreMenuWindow(int x, int y);
	virtual void onShowCameraControlWindow();


private:
	CSDKInitAuthUIMgr* m_sdk_init_auth_ui;
	CSDKLoginUIMgr* m_sdk_login_ui_mgr;
	CSDKLoggedInUIMgr* m_sdk_loggedIn_ui_mgr;
	CSDKSheduleMeetingUIMgr* m_schedule_meeting_ui_mgr;
	CSDKSettingsUIMgr* m_sdk_settings_ui_mgr;
	CSDKJoinMeetingForLoginUserUIMgr* m_sdk_join_meeting_for_login_user_ui_mgr;
	CCustomizeInMeetingUIMgr* m_customizedMeetingUI;
	CMoreMenuUIMgr* m_more_menu_ui;
};