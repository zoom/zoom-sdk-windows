#pragma once
#include "sdk_util.h"
class CInitSDKWorkFlowUIEvent
{
public:
	virtual void onSDKInited(ZOOM_SDK_NAMESPACE::SDKError err) = 0;
};

class CInitSDKWorkFlow : public ZOOM_SDK_NAMESPACE::INetworkConnectionHandler
{
public:
	CInitSDKWorkFlow();
	virtual ~CInitSDKWorkFlow();
	
	bool InitSDK(ZOOM_SDK_NAMESPACE::InitParam& param, bool need_waiting_proxy_detecting);
	bool CleanupSDK();
	void SetUIEvent(CInitSDKWorkFlowUIEvent* event_);

	//
	virtual void onProxyDetectComplete();
	virtual void onProxySettingNotification(ZOOM_SDK_NAMESPACE::IProxySettingHandler* handler);
	virtual void onSSLCertVerifyNotification(ZOOM_SDK_NAMESPACE::ISSLCertVerificationHandler* handler);
protected:
	CInitSDKWorkFlowUIEvent* m_pInitUIEvent;
};

class CAuthSDKWorkFlowUIEvent
{
public:
	virtual void onSDKAuthed(ZOOM_SDK_NAMESPACE::AuthResult ret) = 0;
};

class CAuthSDKWorkFlow : public ZOOM_SDK_NAMESPACE::IAuthServiceEvent
{
public:
	CAuthSDKWorkFlow();
	virtual ~CAuthSDKWorkFlow();

	bool Auth(ZOOM_SDK_NAMESPACE::AuthParam& param);
	void Cleanup(){}
	void SetUIEvent(CAuthSDKWorkFlowUIEvent* event_);
	
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);
	virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo){};
	virtual void onLogout(){};
	virtual void onZoomIdentityExpired(){};

protected:
	CAuthSDKWorkFlowUIEvent* m_pAuthUIEvent;
	ZOOM_SDK_NAMESPACE::IAuthService* m_pAuthService;
};