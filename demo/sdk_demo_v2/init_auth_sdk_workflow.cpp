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


void CInitSDKWorkFlow::CustomizeDemoResource()
{
	//following calls of sdk interfaces ONLY work when they are called before ZOOM_SDK_NAMESPACE::InitSDK()
	//Open it if you want to custom your own resource
	/*
	ZOOM_SDK_NAMESPACE::ICustomizedResourceHelper* pCustomizeResHelper = NULL;
	ZOOM_SDK_NAMESPACE::RetrieveCustomizedResourceHelper(&pCustomizeResHelper);
	if(&pCustomizeResHelper && NULL != pCustomizeResHelper)
	{
		std::wstring strPNGID = _T("G_LOGO_ZOOM.SVG"); //**** Refer for zWinRes.dll for the id of the icon you want to customize 
		std::wstring strFileName = _T("D:\\test.svg"); //**** You should modify this value to make sure the file specified is a real png/svg file !!!
		std::wstring strCopyURL = _T("Click me to copy live stream URL(by ******)");
		pCustomizeResHelper->AddCustomizedPictureResource(strPNGID.c_str(), strFileName.c_str());
		pCustomizeResHelper->AddCustomizedStringResource(ZOOM_SDK_NAMESPACE::SDK_Customized_LiveStream_MenuString_CopyURL_String, strCopyURL.c_str());
		pCustomizeResHelper->AddCustomizedURLResource(ZOOM_SDK_NAMESPACE::SDKCustomizedURL_SUPPORTURL, L"www.******.support");
		pCustomizeResHelper->AddCustomizedURLResource(ZOOM_SDK_NAMESPACE::SDKCustomizedURL_VITRULBG_HELP, L"www.*******.help");
		pCustomizeResHelper->AddCustomizedURLResource(ZOOM_SDK_NAMESPACE::SDKCustomizedURL_VITRULBG_LEARN_MORE, L"www.*******.learn");
	}
	*/
}

ZOOM_SDK_NAMESPACE::SDKError CInitSDKWorkFlow::InitSDK(ZOOM_SDK_NAMESPACE::InitParam& param, bool need_waiting_proxy_detecting)
{
	CustomizeDemoResource();

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
	

	return err;
}

ZOOM_SDK_NAMESPACE::SDKError CInitSDKWorkFlow::CleanupSDK()
{
	if (SDKInterfaceWrap::GetInst().GetNetworkConnectionHelper())
	{
		SDKInterfaceWrap::GetInst().GetNetworkConnectionHelper()->UnRegisterNetworkConnectionHandler();
	}
	return SDKInterfaceWrap::GetInst().Cleanup();
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

ZOOM_SDK_NAMESPACE::SDKError CAuthSDKWorkFlow::Auth(ZOOM_SDK_NAMESPACE::AuthParam& param)
{
	if (NULL == m_pAuthService)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
		SDKInterfaceWrap::GetInst().ListenAuthServiceEvent(this);
	}
	if (m_pAuthService)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = m_pAuthService->SDKAuth(param);
		return err;
	}

	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CAuthSDKWorkFlow::Auth(ZOOM_SDK_NAMESPACE::AuthContext& param)
{
	if (NULL == m_pAuthService)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
		SDKInterfaceWrap::GetInst().ListenAuthServiceEvent(this);
	}
	if (m_pAuthService)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = m_pAuthService->SDKAuth(param);
		return err;
	}

	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
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