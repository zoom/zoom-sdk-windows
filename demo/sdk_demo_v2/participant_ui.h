#pragma once
#include "sdk_util.h"
#include "sdk_demo_app_common.h"
#include "chat_controller_ui.h"
#include "custom_ui_mgr.h"
#include "user_manager.h"

#define DEFAULT_PARTICIPANT_HEIGHT 720
#define DEFAULT_PARTICIPANT_WIDTH 240	
#define PARTICIPANT_UI_TITLE _T("Participants")
#define PITEM_HEIGHT		41
#define DUILIB_PUSERITEM_UI (_T("PUserItem"))
enum SDKUserChangedType
{
	SDK_USER_JOIN = 0,
	SDK_USER_UPDATE,
	SDK_USER_LEFT,
};

class CSDKUserList;
class CCustomizeInMeetingUIMgr;
class CParticipantUIMgr;
class ParticipantPopMenu;

class CPUserItemEx : public DuiLib::CListContainerElementUI
{
public:
	CPUserItemEx();
	~CPUserItemEx();

	void InitControls();

	bool IsSelected() const;
	bool Select(bool bSelect);
	unsigned int GetUserID();
	void SetUserID(unsigned int userID);
	void UpdateName();
	void UpdateUserAudioStatus();
	void UpdateUserVideoStatus();
	void UpdateUserLowerHandStatus();
	void UpdateUserInfo();
	void ResetItemInfo();
	void UpdateItemInfo();

	void SetUIMgr(CParticipantUIMgr* pParticipantUIMgr);
private:
	bool OnSelfItemSize(void* pParam);

private:
	CParticipantUIMgr* m_pParticipantUIMgr;
	ZOOM_SDK_NAMESPACE::IUserInfo* m_pUser;
	unsigned int m_userId;
	CHorizontalLayoutUI* m_winUserInfo;
	CLabelUI* m_lbName;
	CLabelUI* m_lbHostInfo;
	CLabelUI* m_lbVideo;
	CLabelUI* m_lbAudio;
	CControlUI* m_ctrlBottomLine;
	CLabelUI* m_lbLowerHand;
};


class CParticipantUIMgr : 
	public CWindowWnd, 
	public INotifyUI,
	public DuiLib::IDialogBuilderCallback
{
public:
	CParticipantUIMgr(CCustomizeInMeetingUIMgr* pCustomizeUI);
	~CParticipantUIMgr();

	virtual CControlUI* CreateControl(LPCTSTR pstrClass); 
	virtual void Notify( TNotifyUI& msg);
	bool IsWindow();
	bool DestroyWindow();
	HWND GetParent() {return m_hParentWnd;}
	void SetParent(HWND hParentWnd);

	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_CHILD | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_MEETING_PARTICIPANT_WINDOW; }	
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }
	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND)   {}
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void HandleUserChanged(SDKUserChangedType changedType);
	void GetUserList();
	void InitListUI();
	ZOOM_SDK_NAMESPACE::IUserInfo* GetUserByID(unsigned int uID);
private:
	void RemoveListItem();
	void UpdateListItem();
	void ResetWindowTitle();

private:
	CCustomizeInMeetingUIMgr* m_pCustomizeUI;
	CPaintManagerUI m_PaintManager;
	CHorizontalLayoutUI* m_containerBottomButtons;
	CSDKUserList* m_pUserList;
	//just for compile. Need to find a right control to handle this list
	CListUI* m_pUserListUI;
	HWND m_hParentWnd;
	ParticipantPopMenu* m_pPopMenu;
	
};