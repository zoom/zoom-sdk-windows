#include "stdafx.h"
#include "sdk_util.h"

SDKInterfaceWrap& SDKInterfaceWrap::GetInst()
{
	static SDKInterfaceWrap s_inst;
	return s_inst;
}

ZOOM_SDK_NAMESPACE::SDKError SDKInterfaceWrap::Init(ZOOM_SDK_NAMESPACE::InitParam& param_)
{
	ZOOM_SDK_NAMESPACE::SDKError err(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS);
	if (!_inited)
	{
		_customiezed_ui_mode = (ENABLE_CUSTOMIZED_UI_FLAG & param_.obConfigOpts.optionalFeatures) ? true : false;
		err = ZOOM_SDK_NAMESPACE::InitSDK(param_);
		_inited =  (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err) ? true : false;
	}

	return err;
}

ZOOM_SDK_NAMESPACE::SDKError SDKInterfaceWrap::Cleanup()
{
	if (_inited)
	{
		_customiezed_ui_mode = false;
		if (_auth_service)
		{
			ZOOM_SDK_NAMESPACE::DestroyAuthService(_auth_service);
			_auth_service = NULL;
		}

		if(_setting_service)
		{
			ZOOM_SDK_NAMESPACE::DestroySettingService(_setting_service);
			_setting_service = NULL;
		}

		if (_meeting_service)
		{
			ZOOM_SDK_NAMESPACE::DestroyMeetingService(_meeting_service);
			_meeting_service = NULL;
		}

		if (_network_connection_helper)
		{
			ZOOM_SDK_NAMESPACE::DestroyNetworkConnectionHelper(_network_connection_helper);
			_network_connection_helper = NULL;
		}
		if (_premeeting_service)
		{
			ZOOM_SDK_NAMESPACE::DestroyPreMeetingService(_premeeting_service);
			_premeeting_service = NULL;
		}
		ZOOM_SDK_NAMESPACE::CleanUPSDK();

		_inited = false;
		return ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_WRONG_USEAGE;
}

ZOOM_SDK_NAMESPACE::IAuthService* SDKInterfaceWrap::GetAuthService()
{
	if (_inited && NULL == _auth_service)
	{
		ZOOM_SDK_NAMESPACE::CreateAuthService(&_auth_service);
		if (_auth_service)
		{
			_auth_service->SetEvent(this);
		}
	}

	return _auth_service;
}

ZOOM_SDK_NAMESPACE::INetworkConnectionHelper* SDKInterfaceWrap::GetNetworkConnectionHelper()
{
	if (_inited && NULL == _network_connection_helper)
	{
		ZOOM_SDK_NAMESPACE::CreateNetworkConnectionHelper(&_network_connection_helper);
	}

	return _network_connection_helper;
}

void SDKInterfaceWrap::ListenAuthServiceEvent(ZOOM_SDK_NAMESPACE::IAuthServiceEvent* event_)
{
	if (NULL == _auth_service)
	{
		GetAuthService();
	}

	_auth_service_event_pool.AddListener(event_);
}

void SDKInterfaceWrap::UnListenAuthServiceEvent(ZOOM_SDK_NAMESPACE::IAuthServiceEvent* event_)
{
	_auth_service_event_pool.RemoveListener(event_);
}

ZOOM_SDK_NAMESPACE::IMeetingService* SDKInterfaceWrap::GetMeetingService()
{
	if (_inited && NULL == _meeting_service)
	{
		ZOOM_SDK_NAMESPACE::CreateMeetingService(&_meeting_service);
		if (_meeting_service)
		{
			_meeting_service->SetEvent(this);
			GetMeetingParticipantsController();
			GetMeetingChatController();
		}
	}

	return _meeting_service;
}

ZOOM_SDK_NAMESPACE::ISettingService* SDKInterfaceWrap::GetSettingService()
{
	if (_inited && NULL == _setting_service)
	{
		ZOOM_SDK_NAMESPACE::CreateSettingService(&_setting_service);
	}
	return  _setting_service;
}

void SDKInterfaceWrap::ListenMeetingServiceEvent(ZOOM_SDK_NAMESPACE::IMeetingServiceEvent* event_)
{
	_meeting_service_event_pool.AddListener(event_);
}

void SDKInterfaceWrap::UnListenMeetingServiceEvent(ZOOM_SDK_NAMESPACE::IMeetingServiceEvent* event_)
{
	_meeting_service_event_pool.RemoveListener(event_);
}

SDKInterfaceWrap::SDKInterfaceWrap()
{
	_inited = false;
	_auth_service = NULL;
	_meeting_service = NULL;
	_setting_service = NULL;
	_premeeting_service = NULL;
	_network_connection_helper = NULL;
	_meeting_chat_ctrl = NULL;
	_meeting_participants_ctrl = NULL;
	_customiezed_ui_mode = false;
}

SDKInterfaceWrap::~SDKInterfaceWrap()
{
	Cleanup();
}

void SDKInterfaceWrap::ListenPremeetingServiceEvent( ZOOM_SDK_NAMESPACE::IPreMeetingServiceEvent* event_ )
{
	_premeeting_service_event_pool.AddListener(event_);
}

void SDKInterfaceWrap::UnListenPremeetingServiceEvent( ZOOM_SDK_NAMESPACE::IPreMeetingServiceEvent* event_ )
{
	_premeeting_service_event_pool.RemoveListener(event_);
}

void SDKInterfaceWrap::ListenChatServiceMgrEvent(ZOOM_SDK_NAMESPACE::IMeetingChatCtrlEvent* event_)
{
	_chat_servic_event_pool.AddListener(event_);
}
void SDKInterfaceWrap::UnListenChatServiceMgrEvent(ZOOM_SDK_NAMESPACE::IMeetingChatCtrlEvent* event_)
{
	_chat_servic_event_pool.RemoveListener(event_);
}

ZOOM_SDK_NAMESPACE::IPreMeetingService* SDKInterfaceWrap::GetPreMeetingService()
{
	if (_inited && NULL == _premeeting_service)
	{
		ZOOM_SDK_NAMESPACE::CreatePreMeetingService(&_premeeting_service);
		if (_premeeting_service)
		{
			_premeeting_service->SetEvent(this);
		}
	}
	return _premeeting_service;
}

void SDKInterfaceWrap::ListenInMeetingServiceMgrEvent(ISDKInMeetingServiceMgrEvent* event_)
{
	_sdk_inmeeting_service_mgr_event_pool.AddListener(event_);

}

void SDKInterfaceWrap::UnListenInMeetingServiceMgrEvent(ISDKInMeetingServiceMgrEvent* event_)
{
	_sdk_inmeeting_service_mgr_event_pool.RemoveListener(event_);

}

ZOOM_SDK_NAMESPACE::IMeetingChatController* SDKInterfaceWrap::GetMeetingChatController()
{
	if (NULL == _meeting_chat_ctrl && _inited && _meeting_service)
	{
		_meeting_chat_ctrl = _meeting_service->GetMeetingChatController();
		
	}
	if(_meeting_chat_ctrl)
		_meeting_chat_ctrl->SetEvent(this);
	return _meeting_chat_ctrl;
}

ZOOM_SDK_NAMESPACE::IMeetingParticipantsController* SDKInterfaceWrap::GetMeetingParticipantsController()
{

	if (NULL == _meeting_participants_ctrl && _inited && _meeting_service)
	{
		_meeting_participants_ctrl = _meeting_service->GetMeetingParticipantsController();
	}
	if(_meeting_participants_ctrl)
		_meeting_participants_ctrl->SetEvent(this);
	return _meeting_participants_ctrl;
}

void ActiveWindowToTop(HWND hWnd, BOOL bGrabFocusByForce /*= FALSE*/)
{	
	if(hWnd == NULL) return;
	if(!::IsWindowVisible(hWnd)) return;
	if(GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD) return;
	if(::IsWindowVisible(hWnd) && ::IsIconic(hWnd))
	{
		::ShowWindow(hWnd, SW_RESTORE);
	}

	DWORD dwForeThreadId(0);
	HWND hWndForeground = ::GetForegroundWindow();
	if(hWndForeground != NULL)
	{
		dwForeThreadId = GetWindowThreadProcessId(hWndForeground, NULL);
	}

	DWORD dwCurrentThreadId = GetCurrentThreadId();

	if(dwForeThreadId == dwCurrentThreadId
		|| dwForeThreadId == 0)
	{
		::SetForegroundWindow(hWnd);
		::BringWindowToTop(hWnd);
	}
	else if(bGrabFocusByForce)
	{
		BOOL bAttached = AttachThreadInput(dwCurrentThreadId, dwForeThreadId, TRUE);
		::SetForegroundWindow(hWnd);
		::BringWindowToTop(hWnd);

		if(bAttached) 
			AttachThreadInput(dwCurrentThreadId, dwForeThreadId, FALSE);
	}
}