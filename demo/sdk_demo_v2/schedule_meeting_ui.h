#pragma once

#include "schedule_meeting_workflow.h"
#include "UIlib.h"
#include "sdk_demo_app_common.h"
#include "resource.h"
#include "mess_info.h"
#include "dial_in_country_ui.h"
#include <sstream>

enum ErrorMessageType
{
	NoThisMeeting = 0,
	CanNotDeletePMI,
	ScheduleMeetingFailed,
	DeleteMeetingFailed,
	EditMeetingFailed,
	CanNotScheduleMeeting,
	NotSupportEditPMI,
	PwdIsEmpty,
	CanNotSetPwd,
	ApiUnknowErr,
	LeaveEditMeeting,
	InterpreterEmailIsEmpty,

};
enum PreMeetingPageType
{
	ScheduleMeetingPage,
	EditMeetingPage,
	ShowScheduleMeetingInfoPage,
	EditAndDeleteMeetingPage,
	WaitingPage,
};
class CSDKSheduleMeetingUIMgr;
class CSDKSheduleMeetingUIGroup:public CSDKSheduleMeetingUIEvent
{
public:
	CSDKSheduleMeetingUIGroup();
	virtual ~CSDKSheduleMeetingUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKSheduleMeetingUIMgr* main_frame_);
	void UninitWindow();
	void ShowLocaltime();
	void Show();
	void Hide();
	void Notify( TNotifyUI& msg );
	void DoClickScheduleBtn();
	void DoClickBackBtn();
	void DoClickEditMeetingBtn();
	void DoClickDeleteMeetingBtn();
	void SetNotBeEditMeeting();
	bool GetEditMeetingStatus();
	void UpdateRecurringMeetingUI();
	void DoClickEditDialInCountryBtn();
	void DoClickViewPublicListBtn();
	void InitDialInCountry();
	void DoSchedule();
	void DoEdit();

public:
	virtual void onListMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, ZOOM_SDK_NAMESPACE::IList<UINT64 >* lstMeetingList);
	virtual void onScheduleOrEditMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, UINT64 meetingUniqueID);
	virtual void onDeleteMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result);

protected:
	CSDKSheduleMeetingUIMgr* m_main_frame;
	CSDKSheduleMeetingUIWorkFlow m_shedule_meeting_workflow;
	CDialInCountryUIMgr* m_dial_in_country;
	ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* m_pScheduelMeetingItem;
	ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* m_pEditMeetingItem;

	CRichEditUI* m_topic;
	CButtonUI* m_btn_schedule;
	CButtonUI* m_btn_back;
	CRichEditUI* m_start_time;
	CRichEditUI* m_schedule_meeting_info;
	CLabelUI* m_schedule_or_edit_success;

	CListUI* m_meeting_id_list;
	CButtonUI* m_edit_meeting;
	CButtonUI* m_delete_meeting;
	UINT64 m_edit_or_delete_meeting_id;
	bool m_bedit_meeting;

	CComboUI* m_duration_hours;
	CComboUI* m_duration_mins;
	COptionUI* m_host_open;
	COptionUI* m_host_close;
	COptionUI* m_attendee_open;
	COptionUI* m_attendee_close;
	COptionUI* m_audio_telphone;
	COptionUI* m_audio_voip;
	COptionUI* m_audio_both;
	CCheckBoxUI* m_set_meeting_pwd;
	CCheckBoxUI* m_enable_join_before_host;
	CCheckBoxUI* m_mute_meeting;
	CCheckBoxUI* m_use_pmi;
	CCheckBoxUI* m_record_auto;
	CRichEditUI* m_input_meeting_pwd;
	CRichEditUI* m_input_meeting_id;
	CLabelUI* m_dial_in_country_lb;
	CButtonUI* m_edit_dial_in_btn;

	CCheckBoxUI* m_select_recurring_meeting;
	CVerticalLayoutUI* m_start_time_layout;
	CHorizontalLayoutUI* m_recurring_meeting_notice;

	CCheckBoxUI* m_enable_waiting_room;
	CCheckBoxUI* m_enable_meeting_to_public;
	CButtonUI* m_get_public_event_list_url_btn;
	const wchar_t* m_pPublicEventListURL;
	CCheckBoxUI* m_enable_language_interpreter;
	CRichEditUI* m_input_interpreter_email;
	CComboUI*  m_combo_first_language;
	CComboUI*  m_combo_second_language;
	CLabelUI* m_interpreter_to;
	CRichEditUI* m_input_alter_hosts;

	UINT64 m_pmi;
	
};


class CSDKSheduleMeetingUIMgr:
	public CWindowWnd, 
	public INotifyUI
{
public:
	CSDKSheduleMeetingUIMgr();
	virtual ~CSDKSheduleMeetingUIMgr();
	void SetEvent(CSDKDemoAppEvent* pAppEvent);
public:
	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_SCHEDULE_MEETINGFRAME_UI; }	
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND)   {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	CSDKDemoAppEvent* GetAppEvent();
	void SetCurrentPage(CVerticalLayoutUI* _current_page);
	void SwitchToPage(PreMeetingPageType _page_type);
	void ShowErrorMessage(ErrorMessageType _type);
	void ShowWaitingGif(bool bShow);
	void ShowErrorMessage(const wchar_t* msg);

protected:
	CPaintManagerUI m_PaintManager;
	CSDKDemoAppEvent* m_pAppEvent;
	CSDKSheduleMeetingUIGroup m_SheduleMeetingGroup;
	CVerticalLayoutUI* m_current_page;

	CVerticalLayoutUI* m_schedule_meeting_page;
	CVerticalLayoutUI* m_show_schedule_meeting_info_page;
	CVerticalLayoutUI* m_edit_delete_meeting_page;
	COptionUI* m_schedule_meeting;
	COptionUI* m_edit_meeting;
	CButtonUI* m_btn_schedule;
	CGifAnimUI*	m_gifWaiting;
	CVerticalLayoutUI* m_waiting_page;
};

class TInterpreterInfo : public ZOOM_SDK_NAMESPACE::IInterpreterInfo
{
public:
	TInterpreterInfo(){
		firstlanguageinfo = ZOOM_SDK_NAMESPACE::LANGUAGEINFO_NONE;
		secondlanguageinfo = ZOOM_SDK_NAMESPACE::LANGUAGEINFO_NONE;
	};
	virtual ~TInterpreterInfo(){};
	virtual const wchar_t* GetEmail(){return email.c_str();};

	virtual ZOOM_SDK_NAMESPACE::InterpreteLanguageInfo GetFirstLanguageInfo(){return firstlanguageinfo;};

	virtual ZOOM_SDK_NAMESPACE::InterpreteLanguageInfo GetSecendLanguageInfo(){return secondlanguageinfo;};

public:
	std::wstring email;
	ZOOM_SDK_NAMESPACE::InterpreteLanguageInfo firstlanguageinfo;
	ZOOM_SDK_NAMESPACE::InterpreteLanguageInfo secondlanguageinfo;
};
class TAlternativeHostInfo : public ZOOM_SDK_NAMESPACE::IAlternativeHostInfo
{
public:
	TAlternativeHostInfo(){};
	virtual ~TAlternativeHostInfo(){};

	virtual const wchar_t* GetEmail(){return m_email.c_str();};

public:
	std::wstring m_email;	
};
template<class T>
void GetDefaultValueT(T& tmp)
{
}
template<class T>
class TListImpl : public ZOOM_SDK_NAMESPACE::IList<T >
{
public:
	TListImpl()
	{

	}

	virtual ~TListImpl()
	{
	}

	virtual int GetCount()
	{
		return m_List.size();
	}

	virtual T  GetItem(int index)
	{
		T elem;
		GetDefaultValueT<T>(elem);
		if (index >= 0 
			&& index < (int)m_List.size())
		{
			elem = m_List[index];
		}

		return elem;
	}

	void Clear()
	{
		m_List.clear();
	}

public:
	std::vector<T > m_List;
};