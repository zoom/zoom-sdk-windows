#pragma once

#include "Resource.h"
#include "more_features_workflow.h"
#include "mess_info.h"
//#include "meeting_service_components/meeting_video_interface.h"
#include "UIlib.h"
using namespace DuiLib;

enum FEATURE_TYPE
{
	TypeNone,
	PinVideo,
	SpotlightVideo,
	StopAttendeeVideo,
	StartAttendeeVideo,
	MuteAudio,
	UnMuteAudio,
	ExpelUser,
	MakeHost,
	ReclaimHost,
	AssignCoHost,
	RevokeCoHost,
	LowerHand,
	ChangeUserName,

};

class CSDKUserList;
class CCustomizeInMeetingUIMgr;
class CUtilWnd:
	public CWindowWnd,
	public INotifyUI,
	ZOOM_SDK_NAMESPACE::IMeetingVideoCtrlEvent
{
public:
	CUtilWnd( CCustomizeInMeetingUIMgr* main_frame);
	~CUtilWnd();

public:
	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_CHILD | CS_DBLCLKS ; };
	//virtual UINT		GetSkinRes()				 {	 return IDXML_MORE_BUTTON_MENU_UI; }	
	//UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }
	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND)   {}
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void Notify( TNotifyUI& msg);

	void SetType(FEATURE_TYPE _type);
	void UpdateUserList();

	void onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status);
	void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid);
	void onHostRequestStartVideo(ZOOM_SDK_NAMESPACE::IRequestStartVideoHandler* handler_);
	void onActiveSpeakerVideoUserChanged(unsigned int userid);
	void onActiveVideoUserChanged(unsigned int userid);
private:
	void InitControl();
	
	void DoClickOkBtn();
	void ShowErrorMsg(const wchar_t* msg);
	void AddChangeUserNameCtrs(bool bAdd = true);


private:
	CPaintManagerUI m_PaintManager;
	CMoreFeaturesWorkflow m_more_feature_workflow;
	CCustomizeInMeetingUIMgr* m_main_frame;
	CSDKUserList* m_user_list;
	FEATURE_TYPE m_type;


	CHorizontalLayoutUI* m_hLayout;
	CComboUI* m_user_list_combo;
	CButtonUI* m_ok;
	CLabelUI* m_lb_changeto;
	CRichEditUI* m_user_name;
	CHorizontalLayoutUI* m_change_user_name;

	ZOOM_SDK_NAMESPACE::VideoStatus m_last_video_status;
	unsigned int m_last_user_id;


};