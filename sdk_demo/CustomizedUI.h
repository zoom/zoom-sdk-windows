#pragma once
#if (defined ENABLE_CUSTOMIZED_UI)
#include <windows.h>
#include "zoom_sdk.h"
#include "meeting_service_interface.h"
#include "meeting_service_components/meeting_annotation_interface.h"
#include "meeting_service_components/meeting_audio_interface.h"
#include "meeting_service_components/meeting_breakout_rooms_interface.h"
#include "meeting_service_components/meeting_chat_interface.h"
#include "meeting_service_components/meeting_configuration_interface.h"
#include "meeting_service_components/meeting_h323_helper_interface.h"
#include "meeting_service_components/meeting_participants_ctrl_interface.h"
#include "meeting_service_components/meeting_phone_helper_interface.h"
#include "meeting_service_components/meeting_recording_interface.h"
#include "meeting_service_components/meeting_remote_ctrl_interface.h"
#include "meeting_service_components/meeting_sharing_interface.h"
#include "meeting_service_components/meeting_ui_ctrl_interface.h"
#include "meeting_service_components/meeting_video_interface.h"
#include "meeting_service_components/meeting_waiting_room_interface.h"

#include "setting_service_interface.h"

#include "customized_ui/customized_ui_mgr.h"
#include "customized_ui/customized_video_container.h"
#include "customized_ui/zoom_customized_ui.h"
#include "customized_ui/customized_share_render.h"
#include "customized_ui/customized_annotation.h"
#include "customized_ui/customized_local_recording.h"

#include <string>
#include <map>
#include "resource.h"
class IUIVideoContanier
{
public:
	virtual void onVideoContanierDestroy() = 0;
};

class IUIShareRender
{
public:
	virtual void onShareRenderDestroy() = 0;
};
class CustomizedUIMgrWrap : public ZOOM_SDK_NAMESPACE::ICustomizedUIMgrEvent
{
public:
	static CustomizedUIMgrWrap& GetInst()
	{
		static CustomizedUIMgrWrap inst_;
		return inst_;
	}

	void Init()
	{
		ZOOM_SDK_NAMESPACE::CreateCustomizedUIMgr(&_ui_mgr);
		if (_ui_mgr)
			_ui_mgr->SetEvent(this);
	}

	void Uninit()
	{
		ZOOM_SDK_NAMESPACE::DestroyCustomizedUIMgr(_ui_mgr);
	}

	ZOOM_SDK_NAMESPACE::ICustomizedUIMgr* GetSDKObj()
	{
		return _ui_mgr;
	}

	void MapUIShareRender2SDKObj(IUIShareRender* ui_obj_, ZOOM_SDK_NAMESPACE::ICustomizedShareRender* sdk_obj_)
	{
		_map_share_obj.insert(std::make_pair(sdk_obj_, ui_obj_));
	}

	void MapUIVideoContainer2SDKObj(IUIVideoContanier* ui_obj_, ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer* sdk_obj_)
	{
		_map_video_obj.insert(std::make_pair(sdk_obj_, ui_obj_));
	}

	virtual void onVideoContainerDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer* pContainer)
	{
		std::map<ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer*, IUIVideoContanier* >::iterator iter = _map_video_obj.find(pContainer);
		if (_map_video_obj.end() != iter && iter->second)
		{
			iter->second->onVideoContanierDestroy();
			_map_video_obj.erase(iter);
		}

	}

	virtual void onShareRenderDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* pRender)
	{
		std::map<ZOOM_SDK_NAMESPACE::ICustomizedShareRender*, IUIShareRender* >::iterator iter = _map_share_obj.find(pRender);
		if (_map_share_obj.end() != iter && iter->second)
		{
			iter->second->onShareRenderDestroy();
			_map_share_obj.erase(iter);
		}
	}
private:
	CustomizedUIMgrWrap()
	{
		_ui_mgr = NULL;
	}

	ZOOM_SDK_NAMESPACE::ICustomizedUIMgr* _ui_mgr;
	std::map<ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer*, IUIVideoContanier* > _map_video_obj;
	std::map<ZOOM_SDK_NAMESPACE::ICustomizedShareRender*, IUIShareRender* > _map_share_obj;
};

class ICutomizedUIOwnWndInterface
{
protected:
	ICutomizedUIOwnWndInterface()
	{
		m_hOwnerHwnd = NULL;
	}

	virtual void onSize(RECT& rc) = 0;
	virtual void onDestroyed() = 0;
	virtual void onMove() = 0;

	static LRESULT _stdcall my_wnd_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (WM_SIZE == uMsg)
		{
			ICutomizedUIOwnWndInterface* cb_ = (ICutomizedUIOwnWndInterface*)::GetProp(hwnd, _T("resize_cb"));
			if (cb_)
			{
				RECT rc_;
				::GetClientRect(hwnd, &rc_);
				cb_->onSize(rc_);
			}
		}
		else if (WM_DESTROY == uMsg)
		{
			ICutomizedUIOwnWndInterface* cb_ = (ICutomizedUIOwnWndInterface*)::GetProp(hwnd, _T("resize_cb"));
			if (cb_)
			{
				cb_->onDestroyed();
			}
		}
		else if (WM_MOVE == uMsg)
		{
			ICutomizedUIOwnWndInterface* cb_ = (ICutomizedUIOwnWndInterface*)::GetProp(hwnd, _T("resize_cb"));
			if (cb_)
			{
				cb_->onMove();
			}
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

#define MAIN_WND_BK_COLOR (RGB(51, 88, 168))
	BOOL register_window_class(HINSTANCE hInstance)
	{
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= my_wnd_proc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_LOGO));
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= CreateSolidBrush(MAIN_WND_BK_COLOR);//(HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName = _T("zoom_sdk_demo_ui");
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON_LOGO));
		BOOL ret = 0 != RegisterClassEx(&wcex) ? TRUE : FALSE;;
		return ret;
	}

	void adjust_wnd_pos(int width, int height, HWND hwnd)
	{
		RECT rc;
		rc.left = 0;
		rc.right = width;
		rc.top = 0;
		rc.bottom = height;
		DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
		DWORD dwExStyle = ::GetWindowLong(hwnd, GWL_EXSTYLE);
		::AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);
		int cx = rc.right - rc.left;
		int cy = rc.bottom - rc.top;
		int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		::SetWindowPos(hwnd, NULL, (nScreenWidth-cx)/2, (nScreenHeight-cy)/2, cx, cy, SWP_NOZORDER|SWP_NOOWNERZORDER);
	}

	HWND create_owner_hwnd(ICutomizedUIOwnWndInterface* cb_, int width_, int height_)
	{
		DWORD dwStyle = WS_OVERLAPPEDWINDOW;
		dwStyle &= (~WS_MAXIMIZEBOX);
		//dwStyle &= (~WS_THICKFRAME);
		if (NULL == m_hOwnerHwnd || !::IsWindow(m_hOwnerHwnd))
		{
			HINSTANCE hmod = GetModuleHandle(NULL);
			register_window_class(hmod);
			m_hOwnerHwnd = CreateWindowEx( 
				0,     
				_T("zoom_sdk_demo_ui"),
				_T("zoom_sdk_demo_ui"), 
				dwStyle,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				GetDesktopWindow(),
				NULL,
				hmod,
				NULL 
				);
		}

		if (NULL == m_hOwnerHwnd)
		{
			DWORD err = GetLastError();
			return NULL;
		}

		::SetProp(m_hOwnerHwnd, _T("resize_cb"), cb_);
		::SetWindowLong(m_hOwnerHwnd, GWL_STYLE, dwStyle);
		adjust_wnd_pos(width_, height_, m_hOwnerHwnd);
		ShowWindow(m_hOwnerHwnd, SW_SHOW);

		return m_hOwnerHwnd;
	}

	void destroy_owner_wnd()
	{
		if (::IsWindow(m_hOwnerHwnd))
			::DestroyWindow(m_hOwnerHwnd);

		m_hOwnerHwnd = NULL;
	}

protected:
	HWND m_hOwnerHwnd;
};

class IWrapCustomizedVideoContainerEvent : public ZOOM_SDK_NAMESPACE::ICustomizedVideoContainerEvent
{
public:
	virtual void onVideoContainerWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
private:
	void onWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		onVideoContainerWindowMsgNotification(uMsg, wParam, lParam);
	}
};
class IWrapCustomizedShareRenderEvent : public ZOOM_SDK_NAMESPACE::ICustomizedShareRenderEvent
{
public:
	virtual void onShareRenderWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
private:
	void onWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		onShareRenderWindowMsgNotification(uMsg, wParam, lParam);
	}
};

#define Normal_Video_Elem_Count 6
class CustomizeInMeetingUI : 
	public IUIShareRender, 
	public IUIVideoContanier,
	public ICutomizedUIOwnWndInterface,
	public IWrapCustomizedVideoContainerEvent,
	public IWrapCustomizedShareRenderEvent,
	public ZOOM_SDK_NAMESPACE::ICustomizedAnnotationControllerEvent

{
public:
	virtual void onVideoContanierDestroy();
	virtual void onShareRenderDestroy();

	virtual void onSize(RECT& rc);
	virtual void onDestroyed()
	{
		Stop();
	}

	virtual void onMove()
	{
 		if (_share_render)
 		{
 			_share_render->HandleWindowsMoveMsg();
 		}
	}

	virtual void onRenderUserChanged(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement, unsigned int userid);
	virtual void onRenderDataTypeChanged(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement, ZOOM_SDK_NAMESPACE::VideoRenderDataType dataType);
	virtual void onLayoutNotification(RECT wnd_client_rect);
	virtual void onVideoRenderElementDestroyed(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement);
	virtual void onVideoContainerWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam);


	virtual void onSharingContentStartRecving();
	virtual void onSharingSourceUserIDNotification(unsigned int userid);
	virtual void onShareRenderWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void onSharingShareAnnotationStatusChanged(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_);
	virtual void onCustomizedAnnotationObjDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* obj_){}

	CustomizeInMeetingUI();
	void Init() {Reset();}
	void Uninit();
	void SetSDKMeetingService(ZOOM_SDK_NAMESPACE::IMeetingService* meeting_service_);
	void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult /*= 0*/);
	void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId);
	void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList /*= NULL*/);
	void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList /*= NULL*/);
	void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId);

	void SwitchToNextPage() { AutoUpdateNormalElemUser(true);}
	void AnnotationSnapshot();


	void HandleSharingShareAnnotationStatusChanged4ViewShare(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_);
	void HandleSharingShareAnnotationStatusChanged4SendingShare(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_);

	void HandleCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper);
private:
	void Start();
	void Stop();

	void ShowPreview();
	void StopPreview();
	void Reset();
	void CalcTotalPage();

	void HandleInMeeting();
	void DoLayout();
	void DoLayoutActiveVideo();
	void DoLayoutNormalVideo();
	void DoLayoutShareRender(RECT rc);
	void AutoUpdateNormalElemUser(bool switch_to_next);
	POINT _default_video_size;//left(320*180*3)+center(960*540)+right(320*180*3)=1600*540
	POINT _default_video_share_size;//top(video 1600*540)+bottom(480*270)=1600*810
	bool _in_view_sharing;
	bool _is_valid;

	ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer* _video_container;
	ZOOM_SDK_NAMESPACE::IActiveVideoRenderElement* _active_elem;
	ZOOM_SDK_NAMESPACE::IPreviewVideoRenderElement* _preview_elem;
	ZOOM_SDK_NAMESPACE::ICustomizedShareRender* _share_render;
	ZOOM_SDK_NAMESPACE::IMeetingService* _meeting_service;
	ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* _normal_elem[Normal_Video_Elem_Count];

	int _total_page;
	int _current_page;
	bool _in_meeting;
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* _anno_obj;
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* _sending_sharing_anno_obj;
};
#endif