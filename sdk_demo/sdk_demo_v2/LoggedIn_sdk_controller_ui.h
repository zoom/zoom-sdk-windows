#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "resource.h"
#include "LoggedIn_sdk_controller_workflow.h"
#include "sdk_demo_app_common.h"
#include "settings_ui.h"
/////////////////////////
enum demoMeetingType
{
	demo_meetingType_None = 0,
	demo_meetingType_Video_Meeting,
	demo_meetingType_NoVideo_Meeting,
	demo_meetingType_Join_Meeting,
	demo_meetingType_Direct_Share,
	demo_meetingType_RestAPI_Start_Meeting,
	demo_meetingType_RestAPI_Join_meeting,
};
class CSDKLoggedInFlowUIEvent;

class CSDKLoggedInUIMgr : 
	public CWindowWnd, 
	public INotifyUI,
	public CSDKLoggedInFlowUIEvent
{
public:
	CSDKLoggedInUIMgr();
	virtual ~CSDKLoggedInUIMgr();
	void SetEvent(CSDKDemoAppEvent* pAppEvent);
public:
	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_LOGINUSER_METTINGFRAME_UI; }
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND) {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	CSDKDemoAppEvent* GetAppEvent();
	void SetCurrentPage(CVerticalLayoutUI* current_) {m_currentPage = current_;}
	void ShowUI(LoggedIn_MeetingUI_type nType_);

	//CSDKLoginFlowUIEvent
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type);
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler);
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param);
	virtual void OnDirectShareStatusUpdate(ZOOM_SDK_NAMESPACE::DirectShareStatus status, ZOOM_SDK_NAMESPACE::IDirectShareViaMeetingIDOrPairingCodeHandler* handler);

public:
	void ShowErrorMessage(const wchar_t* error_message);
	
protected:
	bool IsMeetingServiceReady();
	void updateUI();

	void DisableMeetingButton();
	void ShowBackToMeetingButton();

	void DoStartMeetingBtnClick(bool bHasVideo);
	void DoJoinMeetingBtnClick();
	void DoLogoutBtnClick();
	void DoBackToMeetingBtnClick();
	void DoStopDirectShareBtnClick();
	void DoStartDirectShareBtnClick();
	void DoScheduleBtnClick();
	void DoConfigureBtnClick();
protected:
	CPaintManagerUI m_PaintManager;
	CSDKDemoAppEvent* m_pAppEvent;
	CVerticalLayoutUI* m_currentPage;

	CVerticalLayoutUI* m_pageBackToMeeting_Video;
	CVerticalLayoutUI* m_pageBackToMeeting_Audio;
	CVerticalLayoutUI* m_pageBackToMeeting_JoinOnly;
	CVerticalLayoutUI* m_pageStopDirectShare;
	CVerticalLayoutUI* m_pageStartVideoMeeting;
	CVerticalLayoutUI* m_pageStartAudioOnlyMeeting;
	CVerticalLayoutUI* m_pageJoinMeeting;
	CVerticalLayoutUI* m_pageStartDirectShare;

	CButtonUI* m_btnStartVideoMeeting;
	CButtonUI* m_btnStartAudioOnlyMeeting;
	CButtonUI* m_btnJoinMeeting;
	CButtonUI* m_btnSchedule;
	CButtonUI* m_btnConfigure;
	CButtonUI* m_btnStartDirectShare;
	CButtonUI* m_btnLogout;
	CButtonUI* m_btnBackToMeeting_Video;
	CButtonUI* m_btnBackToMeeting_Audio;
	CButtonUI* m_btnBackToMeeting_JoinOnly;
	CButtonUI* m_btnStopDirectShare;
	
	CSDKLoggedInUIWorkFlow m_loggedInUIWorkFlow;
	
	demoMeetingType m_demoMeetingType;
	bool m_bInMeeting;
	bool m_bConnectToMeeting;
	bool m_bReallyLoggedIn;					
};
