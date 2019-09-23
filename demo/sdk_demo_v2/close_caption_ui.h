#pragma once
#include "Resource.h"
#include "UIlib.h"
#include "close_caption_workflow.h"
#include "sdk_util.h"
#include "display_cc_ui.h"
#include "mess_info.h"

using namespace DuiLib;

class CSDKUserList;
class CCustomizeInMeetingUIMgr;
class CCloseCaptionUIMgr:
	public CWindowWnd,
	public INotifyUI,
	public IClosedCaptionWorkflowEvent
{
public:
	CCloseCaptionUIMgr(CCustomizeInMeetingUIMgr* _main_frame);
	virtual ~CCloseCaptionUIMgr();
	
	void Notify(TNotifyUI& msg);

	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_MEETING_CLOSE_CAPTION_UI; }	
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }
	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND)   {}
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	void onAssignedToSendCC(bool bAssigned);
	void onClosedCaptionMsgReceived(const wchar_t* ccMsg, time_t time);

public:
	bool IsHost();
	void HideAssignLayout();
	void UpdateListCombox();
	bool GetAssignedStatus();

private:
	void Init();
	void DoClickAssignedBtn();
	void DoClickCopyBtn();
	void DoClickEnterBtn();
	void DoClickSaveBtn();
	void ShowErrorsMsg(const wchar_t* msg);

protected:
	CPaintManagerUI m_PaintManager;
	CCloseCaptionWorkflow m_closed_caption_workflow;
	CSDKUserList* m_user_list;


	CHorizontalLayoutUI* m_assign_layout;
	CButtonUI* m_assign_btn;
	CButtonUI* m_copy_link_btn;
	CComboUI*   m_assign_list_combox;
	CRichEditUI* m_input_cc;
	CRichEditUI* m_show_cc;
	CHorizontalLayoutUI* m_save_cc_layout;
	CButtonUI* m_save_cc_btn;

	ClosedCaptionDisplayUI* m_pCCDisplayUI;
	CCustomizeInMeetingUIMgr* m_main_frame;

	bool m_bAssigned;
};