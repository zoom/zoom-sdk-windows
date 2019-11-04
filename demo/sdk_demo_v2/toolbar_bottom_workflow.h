#pragma once
#include "sdk_util.h"
#include "sdk_demo_app_common.h"

class CToolbarBottomWorkFlowUIEvent
{
public:
	virtual void onBtnClickedResult(ToolbarButtonType btnType, ZOOM_SDK_NAMESPACE::SDKError ret, bool bOn) = 0;
};

class CToolbarBottomWorkFlow
{
public:
	CToolbarBottomWorkFlow();
	virtual ~CToolbarBottomWorkFlow();
	void SetUIEvent(CToolbarBottomWorkFlowUIEvent* event_);
	
	void AudioButtonClicked();
	void VideoButtonClicked();
	void ShareButtonClicked();
	void LeaveButtonClicked();

protected:
	void NotifyUIClickedResult(ToolbarButtonType btnType, ZOOM_SDK_NAMESPACE::SDKError ret, bool bOn = false);
	bool IsMeetingServiceReady();
protected:
	CToolbarBottomWorkFlowUIEvent* m_pToobarBottomUIEvent;
	ZOOM_SDK_NAMESPACE::IMeetingService* m_pMeetingService;
};
