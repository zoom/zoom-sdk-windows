#pragma once
#include "Resource.h"
#include "sdk_util.h"
#include "UIlib.h"
using namespace DuiLib;

class CSDKSheduleMeetingUIGroup;
class CDialInCountryUIMgr:
	public CWindowWnd,
	public INotifyUI
{
public:
	CDialInCountryUIMgr(CSDKSheduleMeetingUIGroup* _main, ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* _meeting_item);
	~CDialInCountryUIMgr();

	void Notify(TNotifyUI& msg);

	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_SCHEDULE_EDIT_DIAL_IN_COUNTRY_UI; }	
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }
	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND)   {}
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	ZOOM_SDK_NAMESPACE::IList<const wchar_t* >* GetSelectedDialinCountryCode();
	
private:
	void InitCountryListUI();
	void AddElement(LPCTSTR name);
	void DoClickSaveChangeBtn();
	void UpdateShowList();
	CControlUI* FindElement(LPCTSTR name);

private:
	CPaintManagerUI m_PaintManager;
	CVerticalLayoutUI* m_country_list;
	CRichEditUI* m_show_country_edit;
	CButtonUI* m_save_change_btn;
	CCheckBoxUI* m_inlude_free_num;

	ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* m_pScheduleMeetingItem;
	ZOOM_SDK_NAMESPACE::IQueryMeetingItemTelAudioInfoHelper* m_audio_helper;
	CSDKSheduleMeetingUIGroup* m_main_ptr;
};