#include "stdafx.h"
#include "custom_ui_share_flow.h"


BOOL CALLBACK MyInfoEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	MONITORINFOEX iMonitor;
	iMonitor.cbSize = sizeof(MONITORINFOEX);
	GetMonitorInfo(hMonitor, &iMonitor);

	if (iMonitor.dwFlags == DISPLAY_DEVICE_MIRRORING_DRIVER)
	{
		return true;
	}
	else
	{
		reinterpret_cast< std::vector<std::wstring>* >(dwData)->push_back(iMonitor.szDevice);
		return true;
	}
}

CCustomizeUIShareFlow::CCustomizeUIShareFlow()
{
	m_pShareRender = NULL;
	m_pMeetingService = NULL;
}

CCustomizeUIShareFlow::~CCustomizeUIShareFlow()
{
	m_pShareRender = NULL;
	m_pMeetingService = NULL;
}

void CCustomizeUIShareFlow::SetShareRender(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* pRender)
{
	m_pShareRender = pRender;
}

void CCustomizeUIShareFlow::Reset()
{
	m_pShareRender = NULL;
	m_pMeetingService = NULL;
}
ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIShareFlow::StopShare()
{
	ZOOM_SDK_NAMESPACE::SDKError ret(ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE);
	do 
	{
		if(IsMeetingServiceReady())
		{
			if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
				break;

			ZOOM_SDK_NAMESPACE::IMeetingConfiguration* pConfCtrl = m_pMeetingService->GetMeetingConfiguration();
			if(!pConfCtrl)
				break;

			ZOOM_SDK_NAMESPACE::IMeetingShareController* pShareCtrl = m_pMeetingService->GetMeetingShareController();
			if (pShareCtrl == NULL)
				break;

			ret = pShareCtrl->StopShare();
		}
	} while (0);
	return ret;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIShareFlow::StartShare(SDKShareType shareType, HWND hwndShared)
{
	ZOOM_SDK_NAMESPACE::SDKError ret(ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE);
	do 
	{
		if(IsMeetingServiceReady())
		{
			if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
				break;

			ZOOM_SDK_NAMESPACE::IMeetingConfiguration* pConfCtrl = m_pMeetingService->GetMeetingConfiguration();
			if(!pConfCtrl)
				break;
			
			ZOOM_SDK_NAMESPACE::IMeetingShareController* pShareCtrl = m_pMeetingService->GetMeetingShareController();
			if (pShareCtrl == NULL)
				break;

			pConfCtrl->SetSharingToolbarVisibility(true);
			if(pShareCtrl->CanStartShare())
			{
				switch(shareType)
				{
				case SDK_SHARE_APP:
					{
						if(hwndShared && ::IsWindow(hwndShared))
						{
							if(::IsIconic(hwndShared))
								::ShowWindow(hwndShared, SW_RESTORE);
							::SetWindowPos(hwndShared, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
							ret = pShareCtrl->StartAppShare(hwndShared);
						}
					}
					break;
				case SDK_SHARE_DESKTOP:
					{
						std::vector<std::wstring> vecMonitorArray;
						EnumDisplayMonitors(NULL, NULL, &MyInfoEnumProc, reinterpret_cast<LPARAM>(&vecMonitorArray));

						std::wstring strMonitorId;
						if (vecMonitorArray.size() <= 0)
							strMonitorId = _T("");
						else
							strMonitorId = vecMonitorArray[0];
						ret = pShareCtrl->StartMonitorShare(strMonitorId.c_str());
					}
					break;
				case SDK_SHARE_WHITEBOARD:
					{
						ret = pShareCtrl->StartWhiteBoardShare();
					}
					break;
				default:
					break;
				}
			}
		}
	} while (0);
	return ret;
}

void CCustomizeUIShareFlow::HandleSizeChanged(RECT newRC)
{
	//to do
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIShareFlow::SetEvent(ZOOM_SDK_NAMESPACE::ICustomizedShareRenderEvent* pEvent)
{
	if(m_pShareRender)
	{
		return m_pShareRender->SetEvent(pEvent);
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIShareFlow::Show()
{
	if(m_pShareRender)
	{
		return m_pShareRender->Show();
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIShareFlow::Hide()
{
	if(m_pShareRender)
	{
		return m_pShareRender->Hide();
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIShareFlow::SetUserID(unsigned int userid)
{
	if(m_pShareRender)
	{
		return m_pShareRender->SetUserID(userid);
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

unsigned int CCustomizeUIShareFlow::GetUserID()
{
	if(m_pShareRender)
	{
		return m_pShareRender->GetUserID();
	}
	return 0;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIShareFlow::Resize(RECT rc)
{
	if(m_pShareRender)
	{
		return m_pShareRender->Resize(rc);
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIShareFlow::SetViewMode(ZOOM_SDK_NAMESPACE::CustomizedViewShareMode mode)
{
	if(m_pShareRender)
	{
		return m_pShareRender->SetViewMode(mode);
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

HWND CCustomizeUIShareFlow::GetOwnerWnd()
{
	if(m_pShareRender)
	{
		return m_pShareRender->GetOwnerWnd();
	}
	return NULL;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIShareFlow::HandleWindowsMoveMsg()
{
	if(m_pShareRender)
	{
		return m_pShareRender->HandleWindowsMoveMsg();
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

bool CCustomizeUIShareFlow::IsMeetingServiceReady()
{
	if (NULL == m_pMeetingService)
	{
		m_pMeetingService = SDKInterfaceWrap::GetInst().GetMeetingService();
		if(NULL == m_pMeetingService)
			return false;
	}
	return true;
}

ZOOM_SDK_NAMESPACE::IMeetingShareController* CCustomizeUIShareFlow::GetMeetingShareController()
{
	if(IsMeetingServiceReady())
		return m_pMeetingService->GetMeetingShareController();
	return NULL;
}