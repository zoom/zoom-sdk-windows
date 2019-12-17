#pragma once

#include <windows.h>
#include <string>
#include "zoom_sdk.h"
#include "auth_service_interface.h"

class CSDKHelper
{
public:
	static bool Init(ZOOM_SDK_NAMESPACE::InitParam& initParam);
	static bool UnInit();
};
class IAuthServiceMgrEvent
{
public:
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret) = 0;
	virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS status, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo) = 0;
	virtual void onLogout() = 0;
};

class CAuthServiceMgr : public ZOOM_SDK_NAMESPACE::IAuthServiceEvent
{
public:
	CAuthServiceMgr();
	CAuthServiceMgr(IAuthServiceMgrEvent* pSkin);
	virtual ~CAuthServiceMgr();

public:
	bool Init();
	bool UnInit();
	bool SDKAuth(ZOOM_SDK_NAMESPACE::AuthParam& authParam);
	bool Login(ZOOM_SDK_NAMESPACE::LoginParam& param);
	bool LogOut();
	ZOOM_SDK_NAMESPACE::IAuthService* GetAuthService() {return m_pAuthService;} //to test direct share

public:
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);
	virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS status, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo);
	virtual void onLogout();
	virtual void onZoomIdentityExpired(){}
	virtual void onZoomAuthIdentityExpired() {}

private:
	IAuthServiceMgrEvent* m_pSink;
	ZOOM_SDK_NAMESPACE::IAuthService* m_pAuthService;
	bool m_bInited;
	bool m_bLogined;
};