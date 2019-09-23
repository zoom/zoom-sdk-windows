#pragma once
#include "sdk_util.h"
#include "sdk_demo_app_common.h"

class CCustomizeUIShareFlow
{
public:
	CCustomizeUIShareFlow();
	~CCustomizeUIShareFlow();
	
	void SetShareRender(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* pContainer);
	void Reset();
	ZOOM_SDK_NAMESPACE::SDKError StartShare(SDKShareType shareType, HWND hwndShared = NULL);
	ZOOM_SDK_NAMESPACE::SDKError StopShare();
	void HandleSizeChanged(RECT newRC);

	ZOOM_SDK_NAMESPACE::SDKError SetEvent(ZOOM_SDK_NAMESPACE::ICustomizedShareRenderEvent* pEvent);
	ZOOM_SDK_NAMESPACE::SDKError Show();
	ZOOM_SDK_NAMESPACE::SDKError Hide();
	ZOOM_SDK_NAMESPACE::SDKError SetUserID(unsigned int userid);
	unsigned int GetUserID();
	ZOOM_SDK_NAMESPACE::SDKError Resize(RECT rc);
	ZOOM_SDK_NAMESPACE::SDKError SetViewMode(ZOOM_SDK_NAMESPACE::CustomizedViewShareMode mode);
	HWND GetOwnerWnd();
	ZOOM_SDK_NAMESPACE::SDKError HandleWindowsMoveMsg();
	
	ZOOM_SDK_NAMESPACE::IMeetingShareController* GetMeetingShareController();
private:
	bool IsMeetingServiceReady();
private:
	//IWrapCustomizedVideoContainerEvent* m_pCustomUIVideoEvent; //define this event class later
	ZOOM_SDK_NAMESPACE::ICustomizedShareRender* m_pShareRender;
	ZOOM_SDK_NAMESPACE::IMeetingService* m_pMeetingService;
};
