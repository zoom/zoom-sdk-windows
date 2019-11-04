#pragma once

#include "Resource.h"
#include "more_features_workflow.h"
#include "util_window.h"
#include "mess_info.h"
#include "UIlib.h"
using namespace DuiLib;

#define WND_DEFAULT_MENU_OPTION_WIDTH 160
#define WND_DEFAULT_MENU_OPYION_HEIGHT 20

class CCustomizeInMeetingUIMgr;
class CMoreFeaturesUIMgr:
	public CWindowWnd,
	public INotifyUI,
	public ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent
{
public:
	CMoreFeaturesUIMgr(int X, int Y, CCustomizeInMeetingUIMgr* _main_frame);
	~CMoreFeaturesUIMgr();

public:
	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_CHILD | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_MORE_BUTTON_MENU_UI; }	
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }
	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND)   {}
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void Notify( TNotifyUI& msg);

public:
	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL){}
	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL){}
	virtual void onHostChangeNotification(unsigned int userId);
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid);
	virtual void onUserNameChanged(unsigned int userId, const wchar_t* userName);
	virtual void onCoHostChangeNotification(unsigned int userId, bool isCoHost);

public:
	bool RepaintClient(int X, int Y);
	bool AddElement(LPCTSTR textDisplay);
	CControlUI* FindElementByName(LPCTSTR ElementName);
	bool RemoveElement(CControlUI* pElement);

private:
	void DoClickMuteAllBtn();
	void DoClickUnmuteAllBtn();
	void DoUtilWindowShow(const wchar_t* window_name, FEATURE_TYPE _type);
	void DestroyUtilWindow();
	void UpdateUI();
	void DoClickMuteOnEntry(bool bEnable = true);
	void DoClickLowerAllHandsBtn();
	void DoClickRaiseHandBtn();

	void ShowErrorMsg(const wchar_t* msg);

private:
	CPaintManagerUI m_PaintManager;
	CMoreFeaturesWorkflow m_more_features_workflow;
	CListUI* m_ListMenu;
	int posX;
	int posY;
	int cx;//window size
	int cy;

	CCustomizeInMeetingUIMgr* m_main_frame;
	CUtilWnd* m_util_wnd;
};