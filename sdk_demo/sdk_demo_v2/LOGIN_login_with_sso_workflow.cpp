#include "stdafx.h"
#include "LOGIN_login_with_sso_workflow.h"

CSDKLoginWithSSOFlow::CSDKLoginWithSSOFlow()
{
	m_pAuthService = NULL;

}
CSDKLoginWithSSOFlow::~CSDKLoginWithSSOFlow()
{
	m_pAuthService = NULL;
}
bool CSDKLoginWithSSOFlow::Login(ZOOM_SDK_NAMESPACE::LoginParam& param)
{
	if (NULL == m_pAuthService)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
	}
	if (m_pAuthService)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = m_pAuthService->Login(param);
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS== err)
		{
			return true;
		}
	}
	return false;
}

bool CSDKLoginWithSSOFlow::LogOut()
{
	ZOOM_SDK_NAMESPACE::SDKError err;
	if (m_pAuthService == NULL)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
	}
	if (m_pAuthService)
	{
		err = m_pAuthService->LogOut();
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			return true;
	}
	return false;
}