#include "stdafx.h"
#include "mess_info.h"

CSDKMessInfo::CSDKMessInfo()
{
	m_pZoomLastError = NULL;
	m_pErrorDescription = NULL;
	m_pErrorMessInfo = NULL;
	Init();
}
CSDKMessInfo::~CSDKMessInfo()
{
	Cleanup();
	m_pZoomLastError = NULL;
	m_pErrorDescription = NULL;
	m_pErrorMessInfo = NULL;
}
bool CSDKMessInfo::Init()
{
	if (m_pZoomLastError == NULL)
	{
		m_pZoomLastError = SDKInterfaceWrap::GetInst().GetLastError();
	}
	if (m_pErrorMessInfo == NULL)
	{
		m_pErrorMessInfo = new wchar_t[1024];
	}
	if (m_pZoomLastError && m_pErrorMessInfo)
	{
		return true;
	} 
	else
	{
		return false;
	}	
}
void CSDKMessInfo::Cleanup()
{
	if (m_pErrorMessInfo)
	{
		delete m_pErrorMessInfo;
		m_pErrorMessInfo = NULL;
	}
}
CSDKMessInfo& CSDKMessInfo::GetInst()
{
	static CSDKMessInfo s_inst;
	return s_inst;
}
const wchar_t* CSDKMessInfo::GetErrorDescription()
{
	if (m_pZoomLastError == NULL)
	{
		Init();
	}
	if (m_pZoomLastError)
	{
		m_pErrorDescription = m_pZoomLastError->GetErrorDescription();
	}
	else
		m_pErrorDescription = NULL;
	return m_pErrorDescription;	
}
int CSDKMessInfo::GetErrorCode()
{
	if (m_pZoomLastError == NULL)
	{
		Init();
	}
	if (m_pZoomLastError)
	{
		m_nErrorCode = m_pZoomLastError->GetErrorCode();
	}
	return m_nErrorCode;	
}
const wchar_t* CSDKMessInfo::GetErrorType()
{
	
	if (m_pZoomLastError == NULL)
	{
		Init();
	}
	if (m_pZoomLastError)
	{
		ZOOM_SDK_NAMESPACE::LastErrorType errorType = m_pZoomLastError->GetErrorType();
		switch(errorType)
		{
		case ZOOM_SDK_NAMESPACE::LastErrorType_Auth:
			{
				m_sErrorType = _T("LastErrorType_Auth");
			}
			break;
		case ZOOM_SDK_NAMESPACE::LastErrorType_Login:
			{
				m_sErrorType = _T("LastErrorType_Login");
			}
			break;
		case ZOOM_SDK_NAMESPACE::LastErrorType_Meeting:
			{
				m_sErrorType = _T("LastErrorType_Meeting");
			}
			break;
		case ZOOM_SDK_NAMESPACE::LastErrorType_System:
			{
				m_sErrorType = _T("LastErrorType_System");
			}
			break;
		default:
			break;
			
		}
		
	}
	return m_sErrorType.c_str();
}
wchar_t* CSDKMessInfo::GetErrorMessInfo()
{
	if (m_pZoomLastError == NULL)
	{
		Init();
	}
	if (m_pZoomLastError)
	{
		wsprintf(m_pErrorMessInfo, L"Error Type: %s\nError Code: %d\nError Description: %s", GetErrorType(), GetErrorCode(), GetErrorDescription());
	}
	else
	{
		wsprintf(m_pErrorMessInfo,L"There is an unknown error.");
	}
	return m_pErrorMessInfo;
}