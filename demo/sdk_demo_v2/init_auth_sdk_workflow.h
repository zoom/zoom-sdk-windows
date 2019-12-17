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
	
	ZOOM_SDK_NAMESPACE::SDKError InitSDK(ZOOM_SDK_NAMESPACE::InitParam& param, bool need_waiting_proxy_detecting);
	ZOOM_SDK_NAMESPACE::SDKError CleanupSDK();
	void SetUIEvent(CInitSDKWorkFlowUIEvent* event_);

	void CustomizeDemoResource();
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

	ZOOM_SDK_NAMESPACE::SDKError Auth(ZOOM_SDK_NAMESPACE::AuthParam& param);
	ZOOM_SDK_NAMESPACE::SDKError Auth(ZOOM_SDK_NAMESPACE::AuthContext& param);
	void Cleanup(){}
	void SetUIEvent(CAuthSDKWorkFlowUIEvent* event_);
	
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);
	virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo){};
	virtual void onLogout(){};
	virtual void onZoomIdentityExpired(){};
	virtual void onZoomAuthIdentityExpired() {}

protected:
	CAuthSDKWorkFlowUIEvent* m_pAuthUIEvent;
	ZOOM_SDK_NAMESPACE::IAuthService* m_pAuthService;
};