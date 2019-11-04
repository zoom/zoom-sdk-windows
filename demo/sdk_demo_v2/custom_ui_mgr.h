#pragma once
#include "sdk_util.h"

#include <string>
#include <map>
#include "resource.h"
#include "custom_ui_base.h"
#include "custom_ui_mgr_flow.h"
#include "custom_ui_video_mgr.h"
#include "custom_ui_share_mgr.h"
#include "toolbar_manager.h"
#include "arrow_window.h"
#include "chat_controller_ui.h"
#include "participant_ui.h"
#include "user_manager.h"
#include "more_menu_ui.h"
#include "display_cc_ui.h"
#include "CameraControlWindow.h"

#define Custom_Smallest_UI_Height 280
#define Custom_Smallest_UI_Weight 700

class CSDKUserList;
class CArrowWindow;
class CCustomizeUIVideoMgr;
class CCustomizeUIShareMgr;
class CSDKMeetingChatUIMgr;
class CParticipantUIMgr;

class CCustomizeInMeetingUIMgr : 
	//public IUIShareRender, 
	//public IUIVideoContanier,
	public ICutomizedUIOwnWndInterface,
	public ZOOM_SDK_NAMESPACE::ICustomizedUIMgrEvent,
	public ZOOM_SDK_NAMESPACE::ICustomizedVideoContainerEvent,
	public ZOOM_SDK_NAMESPACE::ICustomizedShareRenderEvent,
	public ISDKInMeetingServiceCustomUIEvent
{
public:
	//if need, all the virtual function should be modified later
	//ICustomizedUIMgrEvent
	virtual void onVideoContainerDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer* pContainer);
	virtual void onShareRenderDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* pRender);
	virtual void onWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam) {onVideoContainerWindowMsgNotification(uMsg, wParam, lParam);}

	virtual void onSize(RECT& rc);
	virtual void onDestroyed();
	virtual void onMove();
	virtual void onRenderUserChanged(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement, unsigned int userid);
	virtual void onRenderDataTypeChanged(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement, ZOOM_SDK_NAMESPACE::VideoRenderDataType dataType);
	virtual void onLayoutNotification(RECT wnd_client_rect);
	virtual void onVideoRenderElementDestroyed(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement);
	virtual void onVideoContainerWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual void onSharingContentStartRecving();
	virtual void onSharingSourceUserIDNotification(unsigned int userid);
	virtual void onShareRenderWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void onSharingShareAnnotationStatusChanged(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_);
	virtual void onCustomizedAnnotationObjDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* obj_){}

	virtual void onUserNameChanged(unsigned int userId, const wchar_t* userName);


	CCustomizeInMeetingUIMgr();
	void Init();
	void ActivateUI();
	//ISDKInMeetingServiceCustomUIEvent
	virtual void SetSDKMeetingService(ZOOM_SDK_NAMESPACE::IMeetingService* meeting_service_);

	//ISDKInMeetingServiceCustomUIEvent
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult /*= 0*/);
	virtual void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId);
	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList /*= NULL*/);
	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList /*= NULL*/);
	virtual void onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL);
	virtual void onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status);
	virtual void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId);
	virtual void onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper);

	void AnnotationSnapshot();


public:
	ZOOM_SDK_NAMESPACE::ICustomizedUIMgr* GetCustomizedMgr();
	void SetEvent(CSDKDemoAppEvent* pAppEvent);
	
	void ShowHideGalleryViewWindow();
	void ShowHideChatWindow();
	void ShowShareWindow();
	void ShowHideParticipantWindow();
	void ShowHideCameraControlWindow();
	void PageButtonClick(ArrowButtonType btnType);
	void ShowHideMoreMenuWindow(int x, int y);
	bool HideMenuWhenMenuVisible();

	CSDKUserList* GetUserList();
	void HandleChatWindowBeClosed();
	
	void UpdateShareButtonStatus();
	void UpdateToolbarButtons();
	HWND GetHWND();
	ClosedCaptionDisplayUI* CreateDisplayCCWnd();
	void DestroyDisplayCCWnd();
	void UpdateParticipantsWindow();
	
	HWND GetRootWindowHwnd();
	
private:
	void DestroyAllSubWindow();
	void CreateParticipantWindow();
	void DestroyParticipantWindow();
	void CreateChatWindow();
	void DestroyChatWindow();
	void DestroyArrowWindow();
	void CreateArrowWindow();
	void CreateCameraControlWindow();
	void DestroyCameraControlWindow();
	void InitUserList();
	void UninitUserList();
	void UpdateUserList();
	void DestroyMoreMenuWindow();

	void Reset();

	void Start();
	void Stop();

	void ShowPreview();
	void StopPreview();
	

	void ShowToolbar();
	void HandleInMeeting();
	void HandleMoveToWaitingRoom();
	void DoLayout();
	void DoLayoutActiveVideo();
	void DoLayoutNormalVideo();
	void DoLayoutArrowWindow();
	void DoLayoutParticipantsWindow();
	void AutoUpdateNormalElemUser(bool switch_to_next);
	void AutoReSubscribeNormalElemUser();
	void UpdateMeetingTitle(bool bInWaitingRoom = false);
	

	bool InitCustomizeUIVideoMgr();
	bool InitCustomShareRender();

	
private:
	ZOOM_SDK_NAMESPACE::IMeetingService* m_pMeetingService;
	CSDKDemoAppEvent* m_pAppEvent;
	CSDKCustomUIWorkFlow m_customUIWorkFlow;
	ZOOM_SDK_NAMESPACE::ICustomizedUIMgr* m_pCustomUIMgr;
	CCustomizeUIVideoMgr* m_pCustomizeUIVideoMgr;
	CCustomizeUIShareMgr* m_pCustomizeShareMgr;
	CSDKMeetingChatUIMgr* m_pChatUIMgr;
	CameraControlWindow* m_pCameraControlWin;
	CMoreMenuUIMgr* m_more_menu_ui;
	ClosedCaptionDisplayUI* m_display_cc_ui;

	CToolbarMgr m_pToolbarMgr;
	CParticipantUIMgr* m_pParticipantUIMgr;
	CArrowWindow* m_upArrowWindow;
	CArrowWindow* m_downArrowWindow;	
	CSDKUserList* m_pUserList;
	bool m_bShowGalleryView;
	bool m_bInMeeting;
	bool m_bUIIsReady;
	bool m_bInChat;
	bool m_bInShowParticipant;
	bool m_bNeedCallEndMeeting;
	bool m_bInCameraControl;
	RECT m_rcVideo;
	//other control component go here
};

