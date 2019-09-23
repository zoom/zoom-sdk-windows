#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "Resource.h"
#include "toolbar_bottom_workflow.h"
#include "toolbar_manager.h"
#define DEFAULT_TOOLBAR_HEIGHT  53



class CToolbarMgr;
class CToolbarBottom : 
	public CWindowWnd, 
	public INotifyUI,
	public CToolbarBottomWorkFlowUIEvent
{
public:
	CToolbarBottom(CToolbarMgr* pToolbarMgr);
	~CToolbarBottom();

	virtual void Notify( TNotifyUI& msg);
	CButtonUI* GetButton(ToolbarButtonType buttonType);

	bool IsWindow();
	bool DestroyWindow();
	HWND GetParent() {return m_hParentWnd;}
	void SetParent(HWND hParentWnd);

	//CWindowWnd -- modified later if needs
	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_CHILD | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_TOOLBAR_BOTTOM_UI; }	
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }
	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND)   {}
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual void onBtnClickedResult(ToolbarButtonType btnType, ZOOM_SDK_NAMESPACE::SDKError ret, bool bOn);
	//void ProcUpdateButtonImage(ToolbarButtonType btnType, bool bOn);
	void UpdateButton(ToolbarButtonType btnNeedUpdate, buttonStatusType btnStatus);
	void UpdateButtonImage(void* pbutton, wchar_t* strImage, int& nImageRight, int nImageWidth = 30);
	void EndMeeting()
	{
		DoLeaveButtonClick();
	}

	void SetGalleryViewStatus(bool bOn);
	void SetChatUIStatus(bool bOn);
	void SetParticipantUIStatus(bool bOn);
	void SetShareUIStatus(bool bOn);
private:
	void DoAudioButtonClick();
	void DoVideoButtonClick();
	void DoParticipantButtonClick();
	void DoChatButtonClick();
	void DoShareButtonClick();
	void DoLeaveButtonClick();
	void DoThumbnailVideoClick();
	void DoMoreMenuClick();
private:
	CToolbarMgr* m_pToolbarMgr;
	CPaintManagerUI m_PaintManager;
	CHorizontalLayoutUI* m_containerBottomButtons;
	CButtonUI* m_btnParticipant;
	CButtonUI* m_btnAudio;
	CButtonUI* m_btnVideo;
	CButtonUI* m_btnThumbnailVideo;
	CButtonUI* m_btnChat;
	CButtonUI* m_btnShare;
	CButtonUI* m_btnLeave;
	CButtonUI* m_btnMore;
	bool m_bInChat;
	bool m_bInParticipant;
	bool m_bInGalleryView;
	bool m_bInShare;
	HWND m_hParentWnd;
	CToolbarBottomWorkFlow m_ToolbarBottomWorkFlow;
};