#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "resource.h"
#include "sdk_demo_app_common.h"
#include "LOGIN_login_with_email_workflow.h"
/////////////////////////
class CSDKLoginFlowUIEvent;
class CSDKLoginWithSSOFlow 
{
public:
	CSDKLoginWithSSOFlow();
	virtual ~CSDKLoginWithSSOFlow();

	ZOOM_SDK_NAMESPACE::SDKError Login(ZOOM_SDK_NAMESPACE::LoginParam& param);
	ZOOM_SDK_NAMESPACE::SDKError LogOut();
	void Cleanup(){}

protected:
	ZOOM_SDK_NAMESPACE::IAuthService* m_pAuthService;
};