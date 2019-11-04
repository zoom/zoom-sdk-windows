#include "AuthServiceMgr.h"
#include "zoom_sdk_def.h"

bool CSDKHelper::Init(ZOOM_SDK_NAMESPACE::InitParam& initParam)
{
	if (ZOOM_SDK_NAMESPACE::InitSDK(initParam) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

bool CSDKHelper::UnInit()
{
	if (ZOOM_SDK_NAMESPACE::CleanUPSDK() != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

CAuthServiceMgr::CAuthServiceMgr()
{
	m_pSink = NULL;
	m_bInited = false;
	m_bLogined = false;
	m_pAuthService = NULL;
}

CAuthServiceMgr::CAuthServiceMgr(IAuthServiceMgrEvent* pSink)
{
	m_pSink = pSink;
	m_bInited = false;
	m_bLogined = false;
	m_pAuthService = NULL;
}

CAuthServiceMgr::~CAuthServiceMgr()
{
	m_bInited = false;
	m_bLogined = false;
}

bool CAuthServiceMgr::Init()
{
	if (m_bInited)
		return true;

	if (ZOOM_SDK_NAMESPACE::CreateAuthService(&m_pAuthService) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	if (m_pAuthService == NULL)
		return false;

	if (m_pAuthService->SetEvent(this) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	m_bInited = true;

	return true;
}

bool CAuthServiceMgr::UnInit()
{
	if (!m_bInited)
		return true;

	m_bInited = false;

	if (ZOOM_SDK_NAMESPACE::DestroyAuthService(m_pAuthService) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

bool CAuthServiceMgr::SDKAuth(ZOOM_SDK_NAMESPACE::AuthParam& authParam)
{
	if (m_pAuthService == NULL)
		return false;

	if (m_pAuthService->SDKAuth(authParam) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;	
}

bool CAuthServiceMgr::Login(ZOOM_SDK_NAMESPACE::LoginParam& param)
{
	if (!m_pAuthService)
		return false;

	if (m_pAuthService->Login(param) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;
	
	return true;
}

bool CAuthServiceMgr::LogOut()
{
	if (!m_bLogined)
		return true;

	if (!m_pAuthService)
		return false;

	if (m_pAuthService->LogOut() != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

void CAuthServiceMgr::onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
	if (m_pSink)
	{
		m_pSink->onAuthenticationReturn(ret);
	}
}


void CAuthServiceMgr::onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS status, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo)
{
	m_bLogined = (ZOOM_SDK_NAMESPACE::LOGIN_SUCCESS == status) ? true : false;
	if (m_pSink)
	{
		m_pSink->onLoginRet(status, pAccountInfo);
	}

}

void CAuthServiceMgr::onLogout()
{
	if (m_pSink)
	{
		m_pSink->onLogout();
	}
}
