#pragma once
#include "sdk_util.h"
#include <vector>
#include <map>
#include "chat_controller_workflow.h"
#include "sdk_demo_app_common.h"
#include "resource.h"
#include "UIlib.h"
#include "custom_ui_mgr.h"
#include "user_manager.h"


class CSDKMeetingChatUIMgr:
	public CWindowWnd ,
	public INotifyUI,
	public IMeetingChatCtrlEventWrap
{
public:
	CSDKMeetingChatUIMgr(CCustomizeInMeetingUIMgr* pMainUI);
	virtual ~CSDKMeetingChatUIMgr();
public:
	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_MEETING_CHAT_FRAME_UI; }
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND) {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//IMeetingChatCtrlEventWrap
	virtual void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc);
	virtual void onChatStautsChangedNotification(ZOOM_SDK_NAMESPACE::ChatStatus* status_);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void HandleUserChanged();
	bool DestroyWindow();
private:
	void DoPressEnterKey();
	void GetUserList();
	void UpdateUserListCombox();
	bool SendChatMsg( unsigned int receiver, wchar_t* content );

protected:

	CPaintManagerUI m_PaintManager;
	CCustomizeInMeetingUIMgr* m_pMainUI;
	CSDKChatControllerWorkFlow m_chat_controller_workflow;
	CSDKUserList* m_pUserList;

	CComboUI* m_pUserListCombox;
	CRichEditUI* m_input_content;
	CRichEditUI* m_show_chat_info;
};