#include "stdafx.h"
#include "LOGIN_login_with_email_workflow.h"

CSDKLoginWithEmailFlow::CSDKLoginWithEmailFlow()
{
	m_pAuthService = NULL;

}
CSDKLoginWithEmailFlow::~CSDKLoginWithEmailFlow()
{
	m_pAuthService = NULL;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKLoginWithEmailFlow::Login(ZOOM_SDK_NAMESPACE::LoginParam& param)
{
	if (NULL == m_pAuthService)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
	}
	if (m_pAuthService)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAuthService->Login(param);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKLoginWithEmailFlow::LogOut()
{
	ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
	if (NULL == m_pAuthService)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
	}
	if (m_pAuthService)
	{
		err = m_pAuthService->LogOut();
	    return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}