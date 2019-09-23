#pragma once
#define PROXY_DETECT_LOGIC
#include "UIlib.h"
#include "resource.h"
#include "AuthServiceMgr.h"
#include "MeetingServiceMgr.h"
#include "zoom_sdk.h"
#include "network_connection_handler_interface.h"
#include "CustomizedUI.h"

using namespace DuiLib;

#define ERROR_AUTH		_T("Auth failed!")
#define ERROR_LOGIN		_T("Login failed!")
#define ERROR_START		_T("Start or join meeting failed!")
#define ERROR_JOINT		_T("Join failed!")
#define ERROR_END		_T("End failed!")

class CAuthServiceMgr;
class CPreMeetingServiceMgr;
class CMeetingServiceMgr;
class CMessageWnd;

enum UIPageType
{
	UIPAGE_AUTH		= 0,
	UIPAGE_USER		= 1,
	UIPAGE_LOGIN	= 2,
	UIPAGE_PT		= 3,
	UIPAGE_START	= 4,
	UIPAGE_JOIN		= 5,
	UIPAGE_MEETING	= 6,
};

enum UIApiType
{
	UIAPI_SHARE		= 0,
	UIAPI_VIDEO		= 1,
	UIAPI_AUDIO		= 2,
};

class CDemoUI : 
	 public CWindowWnd, 
	 public INotifyUI,
	 public IAuthServiceMgrEvent,
	 public IMeetingserviceMgrEvent
{
public:
	CDemoUI();
	virtual ~CDemoUI();

public:
	virtual LPCTSTR		GetWindowClassName() const   {   return _T("DemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	//virtual CDuiString	GetSkinFile()                {   return _T("DemoUI.xml");  }
	//virtual CDuiString	GetSkinFolder()              {   return _T("");  }
	virtual UINT		GetSkinRes()				 {	 return IDXML_DEMO_UI; }
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND /*hWnd*/) { /*delete this;*/ }
	
	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);	

public:
	void SwitchUIPageByType(UIPageType emPageType = UIPAGE_AUTH);
	void ShowStatus(UIPageType emUIPageType, std::wstring strStatus);
	void UpdateUserList(int nIndex, std::wstring strUserName, std::wstring strUserId, bool bAdd = true);
	void CleanUpUserList();
	void ShowWaiting(bool bWaiting, bool bShowLeave = false);

public:
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	//
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);
	virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS status, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo);
	virtual void onLogout();

	//
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath){};
	virtual void onRecording2MP4Processing(int iPercentage){};
	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL);
	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL);
	virtual void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId);
	virtual void onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL){};
	virtual void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status){};
	virtual void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc){};
	virtual void onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status){};
	virtual void onHostChangeNotification(unsigned int userId){};
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid){};
	virtual void onRecordPriviligeChanged(bool bCanRec){};
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid){};
	virtual void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId);
	virtual void onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper);

private:
	void InitAllControls();
	void ResetAllControls();
	void ShowMeetingApiByType(UIApiType emApiType = UIAPI_SHARE);
	void PopUpList();
	void InitMessageWnd(std::wstring strLabelText = _T("User ID:"));
	void UnInitMessageWnd();

	void ProcAuthPage();
	bool SDKInit();
	bool SDKAuth();	
	bool Login();
	bool Start();	
	bool NormalUserStart();
	bool APIUserStart();
	bool Join();
	bool NormalUserJoin();
	bool APIUserJoin();
	bool Leave();
	bool End();
	bool StartMonitorShare();
	bool StartWhiteBoardShare();
	bool StartAppShare();
	bool StopShare();
	bool MuteVideo();
	bool UnmuteVideo();
	bool PinVideo();
	bool UnpinVideo();
	bool MuteAudio();
	bool UnMuteAudio();

protected:
	CPaintManagerUI m_PaintManager;

private:
	CContainerUI*			m_containerAuthUI;
	CContainerUI*			m_containerUserUI;
	CContainerUI*			m_containerLoginUI;
	CContainerUI*			m_containerPTApi;
	CContainerUI*			m_containerStart;
	CContainerUI*			m_containerMeetingApi;
	CVerticalLayoutUI*		m_containerShareApi;
	CVerticalLayoutUI*		m_containerVideoApi;
	CVerticalLayoutUI*		m_containerAudioApi;
	CRichEditUI*			m_editWebDomain;
	CRichEditUI*			m_editKey;
	CRichEditUI*			m_editSecret;
	CRichEditUI*			m_editEmail;
	CRichEditUI*			m_editPassword;
	CRichEditUI*			m_editMeetingNumber;
	CRichEditUI*			m_editUserId;
	CRichEditUI*			m_editUserToken;
	CRichEditUI*			m_editAccessToken;
	CRichEditUI*			m_editUserName;
	CCheckBoxUI*			m_chkRememberMe;
	CLabelUI*				m_lableAuthError;
	CLabelUI*				m_lableLoginError;
	CLabelUI*				m_lableUserId;
	CLabelUI*				m_lableUserToken;
	CLabelUI*				m_lableAccessToken;
	CLabelUI*				m_lableUserName;
	CLabelUI*				m_lableMeetingAPIStatus;
	CLabelUI*				m_lableSDKKey;
	CLabelUI*				m_lableSDKSerect;
	CLabelUI*				m_lableDomain;
	CControlUI*             m_ctrl_edit_web_domain;
	CControlUI*             m_ctrl_lb_SDKkey;
	CControlUI*             m_ctrl_ctrl_edit_key;
	CControlUI*             m_ctrl_lb_SDKSecret;
	CControlUI*             m_ctrl_edit_secret;
	CControlUI*				m_ctrl_zoom_logo;
	
	CButtonUI*				m_btnAuth;	
	CButtonUI*				m_btnNormal;
	CButtonUI*				m_btnApi;
	CButtonUI*				m_btnNextVideoPage;
	CButtonUI*				m_btnLogin;
	CButtonUI*				m_btnStart;
	CButtonUI*				m_btnJoin;
	CButtonUI*				m_btnStartOk;
	CButtonUI*				m_btnEnd;
	CButtonUI*				m_btnLeave;
	CButtonUI*				m_btnCancel;
	CButtonUI*				m_btnStartMonitorShare;
	CButtonUI*				m_btnStartWBShare;
	CButtonUI*				m_btnStartAppShare;
	CButtonUI*				m_btnStopShare;
	CButtonUI*				m_btnMuteVideo;
	CButtonUI*				m_btnUnmuteVideo;
	CButtonUI*				m_btnPingVideo;
	CButtonUI*				m_btnUnpingVideo;
	CButtonUI*				m_btnMuteAudio;
	CButtonUI*				m_btnUnmuteAudio;
	CButtonUI*				m_btnShareApi;
	CButtonUI*				m_btnVideoApi;
	CButtonUI*				m_btnAudioApi;
	CButtonUI*				m_btnLeaveWhenConnecting;
	CButtonUI*				m_btnAnnotationSnapshot;
	CListUI*				m_listUsers;

	CContainerUI*			m_containerWaitingUI;
	CGifAnimUI*				m_gifWaiting;

	CAuthServiceMgr*		m_pAuthServiceMgr;
	CPreMeetingServiceMgr*	m_preMeetingServiceMgr;
	CMeetingServiceMgr*		m_pMeetingServiceMgr;
	bool					m_bNormalUser;
	bool					m_bStar;
	CMessageWnd*			m_pMessageWnd;
	bool					m_bSDKInit;
	ZOOM_SDK_NAMESPACE::INetworkConnectionHelper* m_pNetworkConnectionHelper;

#if (defined ENABLE_CUSTOMIZED_UI)
	CustomizeInMeetingUI m_inMeetingUI;
#endif
};