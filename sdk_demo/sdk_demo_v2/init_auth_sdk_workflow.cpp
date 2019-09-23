#include "stdafx.h"
#include "init_auth_sdk_workflow.h"
#include "sdk_util.h"

CInitSDKWorkFlow::CInitSDKWorkFlow()
{
	m_pInitUIEvent = NULL;
}

CInitSDKWorkFlow::~CInitSDKWorkFlow()
{

}

bool CInitSDKWorkFlow::InitSDK(ZOOM_SDK_NAMESPACE::InitParam& param, bool need_waiting_proxy_detecting)
{
	ZOOM_SDK_NAMESPACE::SDKError err = SDKInterfaceWrap::GetInst().Init(param);
	if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != err)
	{
		if (m_pInitUIEvent)
		{
			m_pInitUIEvent->onSDKInited(err);
		}
	}
	else
	{
		if (need_waiting_proxy_detecting)
		{
			if (SDKInterfaceWrap::GetInst().GetNetworkConnectionHelper())
			{
				SDKInterfaceWrap::GetInst().GetNetworkConnectionHelper()->RegisterNetworkConnectionHandler(this);
			}
		}
		else if (m_pInitUIEvent)
		{
			m_pInitUIEvent->onSDKInited(err);
		}
	}
	

	return ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err ? true : false;
}

bool CInitSDKWorkFlow::CleanupSDK()
{
	if (SDKInterfaceWrap::GetInst().GetNetworkConnectionHelper())
	{
		SDKInterfaceWrap::GetInst().GetNetworkConnectionHelper()->RegisterNetworkConnectionHandler(this);
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == SDKInterfaceWrap::GetInst().Cleanup() ? true : false;
}

void CInitSDKWorkFlow::SetUIEvent(CInitSDKWorkFlowUIEvent* event_)
{
	m_pInitUIEvent = event_;
}

void CInitSDKWorkFlow::onProxyDetectComplete()
{
	static bool doOnce = true;
	if (m_pInitUIEvent && doOnce)
	{
		doOnce = false;
		m_pInitUIEvent->onSDKInited(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS);
	}
}
void CInitSDKWorkFlow::onProxySettingNotification(ZOOM_SDK_NAMESPACE::IProxySettingHandler* handler)
{
	//todo
}
void CInitSDKWorkFlow::onSSLCertVerifyNotification(ZOOM_SDK_NAMESPACE::ISSLCertVerificationHandler* handler)
{
	//todo
}

/////////////////////////

CAuthSDKWorkFlow::CAuthSDKWorkFlow()
{
	m_pAuthUIEvent = NULL;
	m_pAuthService = NULL;
}

CAuthSDKWorkFlow::~CAuthSDKWorkFlow()
{
	m_pAuthUIEvent = NULL;
	m_pAuthService = NULL;
	SDKInterfaceWrap::GetInst().UnListenAuthServiceEvent(this);
}

bool CAuthSDKWorkFlow::Auth(ZOOM_SDK_NAMESPACE::AuthParam& param)
{
	if (NULL == m_pAuthService)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
		SDKInterfaceWrap::GetInst().ListenAuthServiceEvent(this);
	}
	if (m_pAuthService)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = m_pAuthService->SDKAuth(param);
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}

	return false;
}

void CAuthSDKWorkFlow::SetUIEvent(CAuthSDKWorkFlowUIEvent* event_)
{
	m_pAuthUIEvent = event_;
}

void CAuthSDKWorkFlow::onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
	if (m_pAuthUIEvent)
	{
		m_pAuthUIEvent->onSDKAuthed(ret);
	}
}