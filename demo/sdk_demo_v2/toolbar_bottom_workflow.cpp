#include "stdafx.h"
#include "toolbar_bottom_workflow.h"

CToolbarBottomWorkFlow::CToolbarBottomWorkFlow()
{
	m_pToobarBottomUIEvent = NULL;
	m_pMeetingService = NULL;
}

CToolbarBottomWorkFlow::~CToolbarBottomWorkFlow()
{
	m_pToobarBottomUIEvent = NULL;
	m_pMeetingService = NULL;
}

void CToolbarBottomWorkFlow::SetUIEvent(CToolbarBottomWorkFlowUIEvent* event_)
{
	m_pToobarBottomUIEvent = event_;
}

bool CToolbarBottomWorkFlow::IsMeetingServiceReady()
{
	if (NULL == m_pMeetingService)
	{
		m_pMeetingService = SDKInterfaceWrap::GetInst().GetMeetingService();
		if(NULL == m_pMeetingService)
			return false;
	}
	return true;
}

void CToolbarBottomWorkFlow::AudioButtonClicked()
{
	ZOOM_SDK_NAMESPACE::SDKError ret(ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE);
	do 
	{
		if(IsMeetingServiceReady())
		{
			if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
				break;

			ZOOM_SDK_NAMESPACE::IMeetingParticipantsController* pUserCtrl = m_pMeetingService->GetMeetingParticipantsController();
			if(!pUserCtrl)
				break;

			ZOOM_SDK_NAMESPACE::IUserInfo* pUserMe = pUserCtrl->GetUserByUserID(0);
			if(!pUserMe)
				break;

			ZOOM_SDK_NAMESPACE::IMeetingAudioController* pAudioCtrl = m_pMeetingService->GetMeetingAudioController();
			if (pAudioCtrl == NULL)
				break;
			if(pUserMe->IsAudioMuted())
			{
				ret = pAudioCtrl->UnMuteAudio(pUserMe->GetUserID());
				NotifyUIClickedResult(Toolbar_Button_Audio, ret, true);
			}
			else
			{
				ret = pAudioCtrl->MuteAudio(pUserMe->GetUserID());
				NotifyUIClickedResult(Toolbar_Button_Audio, ret, false);
			}
			return;
		}
	} while (0);
	NotifyUIClickedResult(Toolbar_Button_Audio, ret);
}

void CToolbarBottomWorkFlow::VideoButtonClicked()
{
	ZOOM_SDK_NAMESPACE::SDKError ret(ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE);
	do 
	{
		if(IsMeetingServiceReady())
		{
			if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
				break;

			ZOOM_SDK_NAMESPACE::IMeetingParticipantsController* pUserCtrl = m_pMeetingService->GetMeetingParticipantsController();
			if(!pUserCtrl)
				break;

			ZOOM_SDK_NAMESPACE::IUserInfo* pUserMe = pUserCtrl->GetUserByUserID(0);
			if(!pUserMe)
				break;

			ZOOM_SDK_NAMESPACE::IMeetingVideoController* pVideoCtrl = m_pMeetingService->GetMeetingVideoController();
			if (pVideoCtrl == NULL)
				break;

			if(pUserMe->IsVideoOn())
			{
				ret = pVideoCtrl->MuteVideo();
				NotifyUIClickedResult(Toolbar_Button_Video, ret, false);
			}
			else
			{
				ret = pVideoCtrl->UnmuteVideo();
				NotifyUIClickedResult(Toolbar_Button_Video, ret, true);
			}
			return;
		}
	} while (0);
	NotifyUIClickedResult(Toolbar_Button_Video, ret);
}

void CToolbarBottomWorkFlow::ShareButtonClicked()
{
	return;
	//do not handle this logic here
	/*
	ZOOM_SDK_NAMESPACE::SDKError ret(ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE);
	
	//show a window for user to select an app or stop the share
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
			

			if(pShareCtrl->CanStartShare())
			{
				std::vector<std::wstring> vecMonitorArray;
				EnumDisplayMonitors(NULL, NULL, &MyInfoEnumProc, reinterpret_cast<LPARAM>(&vecMonitorArray));

				std::wstring strMonitorId;
				if (vecMonitorArray.size() <= 0)
					strMonitorId = _T("");
				else
					strMonitorId = vecMonitorArray[0];

				pShareCtrl->StartMonitorShare(strMonitorId.c_str());
				NotifyUIClickedResult(Toolbar_Button_Video, ret, false);
			}
			else
			{
				NotifyUIClickedResult(Toolbar_Button_Video, ret, true);
			}
			return;
		}
	} while (0);
	NotifyUIClickedResult(Toolbar_Button_Share, ret);
	*/
}

void CToolbarBottomWorkFlow::LeaveButtonClicked()
{
	ZOOM_SDK_NAMESPACE::SDKError ret(ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE);
	do 
	{
		if(IsMeetingServiceReady())
		{
			if (!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
				break;

			ZOOM_SDK_NAMESPACE::IMeetingParticipantsController* pUserCtrl = m_pMeetingService->GetMeetingParticipantsController();
			ZOOM_SDK_NAMESPACE::IUserInfo* pUserMe = NULL;
			if(pUserCtrl)
				pUserMe = pUserCtrl->GetUserByUserID(0);

			if(pUserMe && pUserMe->IsHost())
				ret = m_pMeetingService->Leave(ZOOM_SDK_NAMESPACE::END_MEETING);
			else
				ret = m_pMeetingService->Leave(ZOOM_SDK_NAMESPACE::LEAVE_MEETING);
			return;
		}
	} while (0);
	//NotifyUIClickedResult(Toolbar_Button_Leave, ret);
}

void CToolbarBottomWorkFlow::NotifyUIClickedResult(ToolbarButtonType btnType, ZOOM_SDK_NAMESPACE::SDKError ret, bool bOn)
{
	if(m_pToobarBottomUIEvent)
	{
		m_pToobarBottomUIEvent->onBtnClickedResult(btnType, ret, bOn);
	}
}