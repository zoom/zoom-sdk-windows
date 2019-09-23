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
bool CSDKLoginWithEmailFlow::Login(ZOOM_SDK_NAMESPACE::LoginParam& param)
{
	if (NULL == m_pAuthService)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
	}
	if (m_pAuthService)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAuthService->Login(param);
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err )
		{
			return true;
		}
	}
	return false;
}

bool CSDKLoginWithEmailFlow::LogOut()
{
	ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
	if (NULL == m_pAuthService)
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