#pragma once

#include <windows.h>
#include <string>
#include "zoom_sdk.h"
#include "auth_service_interface.h"
#include "DemoUI.h"

class CAuthServiceMgr : public ZOOM_SDK_NAMESPACE::IAuthServiceEvent
{
public:
	CAuthServiceMgr();
	CAuthServiceMgr(CDemoUI* pSkin);
	virtual ~CAuthServiceMgr();


public:
	bool Init(ZOOM_SDK_NAMESPACE::InitParam& initParam);
	bool UnInit();
	bool SDKAuth(ZOOM_SDK_NAMESPACE::AuthParam& authParam);
	bool Login(ZOOM_SDK_NAMESPACE::LoginParam& param);
	bool LogOut();

public:
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);
	virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS status, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo);
	virtual void onLogout();

private:
	CDemoUI* m_pSink;
	ZOOM_SDK_NAMESPACE::IAuthService* m_pAuthService;
	bool m_bInited;
	bool m_bLogined;
};