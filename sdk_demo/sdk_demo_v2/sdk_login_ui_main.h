#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "resource.h"
#include "sdk_login_with_email_workflow.h"
#include "sdk_login_with_restAPI_workflow.h"
#include "sdk_login_with_sso_workflow.h"
#include "sdk_demo_app_common.h"
/////////////////////////

class CSDKLoginUIGroup : public CSDKLoginFlowUIEvent
{
public:
	CSDKLoginUIGroup();
	virtual ~CSDKLoginUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKInitAuthUIMgr* main_frame_);
	void UninitWindow();
	void Show();
	void Hide();
	void Notify( TNotifyUI& msg );

	void DoLoginBtnClick();
	virtual void onSDKLoginReturn(ZOOM_SDK_NAMESPACE::SDKError err);
protected:

};
