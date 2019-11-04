#pragma once
#include <Windows.h>
#include "sdk_util.h"
#include "invitation_workflow.h"
#include "Resource.h"
#include "UIlib.h"
using namespace DuiLib;

class CInvitationUIMgr:
	public CWindowWnd,
	public INotifyUI
{
public:
	CInvitationUIMgr();
	~CInvitationUIMgr();

public:
	virtual void Notify( TNotifyUI& msg);
	virtual LPCTSTR GetWindowClassName() const { return _T("CSDKDemoUI"); }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_MEETING_INVITATION_UI; }	
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }
	virtual void		OnFinalMessage(HWND)   {}
	virtual LRESULT	HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	void InitWindow();
	void DoClickCopyLinkBtn();
	void DoClickCopyInviteInfoBtn();

private:
	CPaintManagerUI m_PaintManager;
	CInvitationWorkflow m_invite_workflow;
	CButtonUI* m_copy_invite_link_btn;
	CButtonUI* m_copy_invite_info_btn;
	CLabelUI* m_notify_lb;
	
};
