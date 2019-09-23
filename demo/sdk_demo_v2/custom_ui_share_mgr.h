#pragma once
#include "sdk_util.h"
#include "custom_ui_mgr.h"
#include "custom_ui_share_flow.h"

#define APPLIST_TEXT_APPNAME 0
#define APPLIST_TEXT_APPHWND 1

#define Default_Share_Window_Height 600
#define Default_Share_Window_Width 800

class CCustomizeInMeetingUIMgr;
class CCustomizeUIShareMgr;
class ViewOptionsWindow;
class ShareToolbarWindow;

class CCustomizeUIShareRenderUI:
	public ICutomizedUIOwnWndInterface
{
public:
	CCustomizeUIShareRenderUI(CCustomizeUIShareMgr* pCustomizeShareUIMgr);
	~CCustomizeUIShareRenderUI();

	virtual void onSize(RECT& rc);
	virtual void onDestroyed();
	virtual void onMove();
	
	void InitWindow();
	void SetDefaultRenderPos();

	void HandleDestroyWindow();
	HWND GetWindowHandle();
	void ShowMe();
	void HideMe();
	
private:
	CCustomizeUIShareMgr* m_pCustomizeShareUIMgr;
	
};

class CCustomizeUIShareSelectUI:
		public CWindowWnd, 
		public INotifyUI
{
public:
	CCustomizeUIShareSelectUI(CCustomizeUIShareMgr* pCustomizeShareUIMgr);
	~CCustomizeUIShareSelectUI();

	virtual void Notify( TNotifyUI& msg);
	bool DestroyWindow();

	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_CHILD | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_SHARE_SELECTAPP_UI; }	
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }
	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND)   {}
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void EnumAllWindows();
	void InitAppList();
	void AddToAppList(HWND hwndAdd);
private:
	void DoShareButtonClick(SDKShareType shareType);
	void AdjustListUIPos();
	
private:
	CCustomizeUIShareMgr* m_pCustomizeShareUIMgr;
	CPaintManagerUI m_PaintManager;
	CListUI* m_pAppList;
	CButtonUI* m_btnShareDesktop;
	CButtonUI* m_btnShareWhiteBoard;
	CButtonUI* m_btnShareSelectApp;
	HWND m_hwndSelectedApp;
	HWND m_hParentWnd;
	int	m_iAppCountToList;
};


class CCustomizeUIShareMgr
{
public:
	CCustomizeUIShareMgr(CCustomizeInMeetingUIMgr* pMainUI);
	~CCustomizeUIShareMgr();
	void SetEvent(ZOOM_SDK_NAMESPACE::ICustomizedShareRenderEvent* pEvent);

	void HandleShareRenderDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* pRender);
	void HandleSharingShareAnnotationStatusChanged(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_);
	void HandleShareRenderWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void HandleSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId);

	void Init();
	void uninit();
	void Show();
	void ShowSelectShareUI();
	bool IsInSendShareMode();

	void CreateCustomShareRender(ZOOM_SDK_NAMESPACE::ICustomizedUIMgr* pUIMgr);
	void DestroyCustomShareRender();

	void ShowSharedContent();
	void StartShare(SDKShareType shareType, HWND hwndShared = NULL);
	void StopShare();
	void onSelectShareUIClosed();

	void HandleSizeChanged(RECT& rc);
	void HandleWindowMoveMsg();
	void HandleRenderUIDestroyed();

	void ShowShareToolbarWindow(bool bShow);
	void ShowViewOptionsWindow(bool bShow);
	void DestroyShareToolbarWindow();
	void DestroyViewOptionsWindow();
	void DestroyAllShareWindows(); 
	void HandleUserChanged();

	void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId);
private:
	void HandleSharingShareAnnotationStatusChanged4ViewShare(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_) {};
	void HandleSharingShareAnnotationStatusChanged4SendingShare(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_) {};

	void CreateSelectShareUI();
	void DestroySelectShareUI();

	void CreateShareRenderUI();
	void DestroyShareRenderUI();

	unsigned int GetShareContentSender();
	void ShowNextShareContent(unsigned int userId);
private:
	CCustomizeUIShareFlow m_pCustomizeUIShareFlow;
	CCustomizeInMeetingUIMgr* m_pMainUI;
	ZOOM_SDK_NAMESPACE::ICustomizedShareRender* m_pCustomizedShareRender;
	CCustomizeUIShareSelectUI* m_pSelectShareUI;
	CCustomizeUIShareRenderUI* m_pShareRenderUI;
	ShareToolbarWindow* m_pShareToolbarWin;
	ViewOptionsWindow* m_pViewOptionsWindow;
	bool m_bInSendShare;
	bool m_bInViewShare;
	bool m_bNeedDeleteShareUIInstance;
};