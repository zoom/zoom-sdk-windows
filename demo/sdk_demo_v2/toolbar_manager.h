#pragma once
#include "sdk_util.h"
#include "sdk_demo_app_common.h"
#include "toolbar_bottom_ui.h"
#define MEETING_BOTTOM_TOOLBAR_TITLE _T("Zoom SDK bottom toolbar")

class CToolbarBottom;
class CToolbarMgr
{
public:
	static CToolbarMgr& GetInstance();
	CToolbarMgr();
	~CToolbarMgr();
	
	void SetEvent(CSDKDemoAppEvent* pAppEvent);

	void Init();
	void UnInit();
	bool SetParentWnd(HWND hParent);
	HWND GetParentWnd();

	bool ShowToolbarBottom();
	bool HideToolbarBottom();

	void UpdateButton(ToolbarButtonType btnNeedUpdate, buttonStatusType btnStatus);
	void ResizeToolbarBottom();
	void ShowGalleryViewWindow();
	void ShowParticipantWindow();
	void ShowChatWindow();
	void ShowShareWindow();
	void EndMeeting();
	void ShowMoreMenuWindow(int x,int y);

	void SetGalleryViewStatus(bool bOn);
	void SetChatUIStatus(bool bOn);
	void SetParticipantUIStatus(bool bOn);
	void SetShareUIStatus(bool bOn);
	bool IsHost();
	//void PageButtonClick(bool bNextBtnClicked);
private:
	bool IsMeetingServiceReady();
	bool GetToolbarBottom();
	bool GetMeetingType();

private:
	CToolbarBottom* m_ToolbarBottom;
	CSDKDemoAppEvent* m_pAppEvent;
	HWND m_hParentWnd;
	ZOOM_SDK_NAMESPACE::IMeetingService* m_pMeetingService;
	ZOOM_SDK_NAMESPACE::MeetingType m_meetingType;
	//here need a member of class something like CUser
};