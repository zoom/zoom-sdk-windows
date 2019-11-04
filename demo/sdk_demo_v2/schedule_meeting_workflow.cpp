#include "stdafx.h"
#include "schedule_meeting_workflow.h"

CSDKSheduleMeetingUIWorkFlow::CSDKSheduleMeetingUIWorkFlow()
{
	m_pPreMeetingService = NULL;
	m_pScheduleMeetingItem = NULL;
	m_pEditMeetingItem = NULL;
	m_pSink = NULL;
	Init();
}

CSDKSheduleMeetingUIWorkFlow::~CSDKSheduleMeetingUIWorkFlow()
{
	SDKInterfaceWrap::GetInst().UnListenPremeetingServiceEvent(this);
	Uninit();
}

void CSDKSheduleMeetingUIWorkFlow::SetEvent( CSDKSheduleMeetingUIEvent* pSink )
{
	m_pSink = pSink;
}

void CSDKSheduleMeetingUIWorkFlow::onListMeeting( ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, ZOOM_SDK_NAMESPACE::IList<UINT64 >* lstMeetingList )
{
	if (m_pSink)
	{
		m_pSink->onListMeeting(result, lstMeetingList);
	}
}

void CSDKSheduleMeetingUIWorkFlow::onScheduleOrEditMeeting( ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, UINT64 meetingUniqueID )
{
	if (m_pSink)
	{
		m_pSink->onScheduleOrEditMeeting(result, meetingUniqueID);
	}
}

void CSDKSheduleMeetingUIWorkFlow::onDeleteMeeting( ZOOM_SDK_NAMESPACE::PremeetingAPIResult result )
{
	if (m_pSink)
	{
		m_pSink->onDeleteMeeting(result); 
	}
}

bool CSDKSheduleMeetingUIWorkFlow::Init()
{
	if (NULL == m_pPreMeetingService)
	{
		m_pPreMeetingService = SDKInterfaceWrap::GetInst().GetPreMeetingService();
	}
	if (m_pPreMeetingService)
	{
		m_pScheduleMeetingItem = m_pPreMeetingService->CreateScheduleMeetingItem();
		SDKInterfaceWrap::GetInst().ListenPremeetingServiceEvent(this);
	}
	if (NULL == m_pScheduleMeetingItem)
	{
		SDKInterfaceWrap::GetInst().UnListenPremeetingServiceEvent(this);
		return false;
	}
	return true;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKSheduleMeetingUIWorkFlow::ScheduleMeeting()
{
	if (m_pPreMeetingService)
	{
		ZOOM_SDK_NAMESPACE::SDKError err;
		err = m_pPreMeetingService->ScheduleMeeting(m_pScheduleMeetingItem);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

bool CSDKSheduleMeetingUIWorkFlow::Uninit()
{
	if(m_pPreMeetingService == NULL)
		return false;
	if (m_pScheduleMeetingItem)
	{
		m_pPreMeetingService->DestoryScheduleMeetingItem(m_pScheduleMeetingItem);
		m_pScheduleMeetingItem = NULL;
	}
	if (m_pEditMeetingItem)
	{
		m_pPreMeetingService->DestoryEditMeetingItem(m_pEditMeetingItem);
		m_pEditMeetingItem = NULL;
	}
	if (m_pSink)
	{
		m_pSink = NULL;
	}
	return true;
}

ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* CSDKSheduleMeetingUIWorkFlow::GetScheduleMeetingItem()
{
	if (m_pScheduleMeetingItem)
	{
		if(m_pPreMeetingService)
			m_pPreMeetingService->DestoryScheduleMeetingItem(m_pScheduleMeetingItem);
		m_pScheduleMeetingItem = NULL;
	}

	if ( NULL == m_pScheduleMeetingItem)
	{
		if(m_pPreMeetingService)
			m_pScheduleMeetingItem = m_pPreMeetingService->CreateScheduleMeetingItem();
	}
	return m_pScheduleMeetingItem; 
}

ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* CSDKSheduleMeetingUIWorkFlow::GetEditMeetingItem( UINT64 meetingUniqueID )
{
	if(m_pEditMeetingItem)
	{
		if(m_pPreMeetingService)
			m_pPreMeetingService->DestoryEditMeetingItem(m_pEditMeetingItem);
		m_pEditMeetingItem = NULL;
	}
	if (NULL == m_pEditMeetingItem)
	{
		m_pEditMeetingItem = m_pPreMeetingService->CreateEditMeetingItem(meetingUniqueID);
	}
	return m_pEditMeetingItem;
}

ZOOM_SDK_NAMESPACE::IMeetingItemInfo* CSDKSheduleMeetingUIWorkFlow::GetMeeingItem( UINT64 meetingUniqueID )
{
	if (m_pPreMeetingService)
	{
		return m_pPreMeetingService->GetMeeingItem(meetingUniqueID);
	}
	return NULL;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKSheduleMeetingUIWorkFlow::DeleteMeeting(UINT64 meetingUniqueID)
{
	if (m_pPreMeetingService)
	{
		ZOOM_SDK_NAMESPACE::SDKError err;
		err = m_pPreMeetingService->DeleteMeeting(meetingUniqueID);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKSheduleMeetingUIWorkFlow::ListMeeting()
{
	if (m_pPreMeetingService)
	{
		ZOOM_SDK_NAMESPACE::SDKError err;
		err = m_pPreMeetingService->ListMeeting();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKSheduleMeetingUIWorkFlow::EditMeeting()
{
	if (m_pEditMeetingItem&&m_pPreMeetingService)
	{
		ZOOM_SDK_NAMESPACE::SDKError err;
		err =m_pPreMeetingService->EditMeeting(m_pEditMeetingItem);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}