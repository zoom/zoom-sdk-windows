#pragma once
#include "Resource.h"
#include "UIlib.h"

#include "close_caption_ui.h"
#include "invitation_ui.h"
#include "more_features_ui.h"
using namespace DuiLib;

#define DEFAULT_MENU_OPTION_WIDTH 122
#define DEFAULT_MENU_OPYION_HEIGHT 25
#define DEFAULT_MENU_HEIGHT		200

class CCustomizeInMeetingUIMgr;
class CMoreMenuUIMgr:
	public CWindowWnd,
	public INotifyUI
{
public:
	CMoreMenuUIMgr();
	CMoreMenuUIMgr(int X, int Y, CCustomizeInMeetingUIMgr* main_frame);
	~CMoreMenuUIMgr();

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
	bool RepaintClient(int X, int Y);
	bool AddElement(LPCTSTR textDisplay);
	CControlUI* FindElementByName(LPCTSTR ElementName);
	bool RemoveElement(CControlUI* pElement);

	int GetWindowWidth();
	int GetWindowHeight();

	void HandleUserChange();
	void HandleMoveAndResize();
private:
	void DoClickClosedCaptionBtn();
	void DoClickInviteBtn();
	void DoClickMoreFeaturesBtn();
	void DestroyClosedCaptionWnd();
	void DestroyInvitationWnd();
	void DestroyMoreFeaturesWnd();
protected:
	CPaintManagerUI m_PaintManager;
	CListUI* m_ListMenu;
	int posX;
	int posY;
	int cx;//window size
	int cy;
	CCustomizeInMeetingUIMgr* m_main_frame;
	CCloseCaptionUIMgr* m_cc_frame;
	CInvitationUIMgr* m_invite_frame;
	CMoreFeaturesUIMgr* m_more_features_frame;
	CListLabelElementUI* m_pListElementLocalRecord;
	CListLabelElementUI* m_pListElementCloudRecord;
	CListLabelElementUI* m_pListElementStopRecord;
	CListLabelElementUI* m_pListElementStopCMR;
};
