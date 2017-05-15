#include "AuthServiceMgr.h"
#include "zoom_sdk_def.h"


CAuthServiceMgr::CAuthServiceMgr()
{
	m_pSink = NULL;
	m_bInited = false;
	m_bLogined = false;
}

CAuthServiceMgr::CAuthServiceMgr(CDemoUI* pSink)
{
	m_pSink = pSink;
	m_bInited = false;
	m_bLogined = false;
}

CAuthServiceMgr::~CAuthServiceMgr()
{
	m_bInited = false;
	m_bLogined = false;
}

bool CAuthServiceMgr::Init(ZOOM_SDK_NAMESPACE::InitParam& initParam)
{
	if (m_bInited)
		return true;

	if (ZOOM_SDK_NAMESPACE::InitSDK(initParam) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

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

	if (ZOOM_SDK_NAMESPACE::CleanUPSDK() != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
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
	TCHAR szLog[MAX_PATH] = { 0 };
	wsprintf(szLog, _T("onAuthenticationReturn:ret=%d\r\n"), ret);
	OutputDebugString(szLog);

	if (m_pSink == NULL)
		return;

	if (ZOOM_SDK_NAMESPACE::AUTHRET_SUCCESS == ret)
		m_pSink->SwitchUIPageByType(UIPAGE_USER);
	else
	{
		m_pSink->ShowStatus(UIPAGE_AUTH, ERROR_AUTH);
	}
}


void CAuthServiceMgr::onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS status, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo)
{
	TCHAR szLog[MAX_PATH] = { 0 };
	wsprintf(szLog, _T("onLoginRet:status=%d\r\n"), status);
	OutputDebugString(szLog);

	if (m_pSink == NULL)
		return;

	if (status == ZOOM_SDK_NAMESPACE::LOGIN_SUCCESS)
	{
		m_pSink->SwitchUIPageByType(UIPAGE_PT);
		m_bLogined = true;
	}
	else if (status == ZOOM_SDK_NAMESPACE::LOGIN_IDLE)
		;
	else if (status == ZOOM_SDK_NAMESPACE::LOGIN_PROCESSING)
		;
	else
		m_pSink->ShowStatus(UIPAGE_LOGIN, ERROR_LOGIN);

}

void CAuthServiceMgr::onLogout()
{
	OutputDebugString(_T("onLogout successful!\r\n"));
}
