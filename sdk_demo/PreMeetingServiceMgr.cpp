#include "PreMeetingServiceMgr.h"


CPreMeetingServiceMgr::CPreMeetingServiceMgr()
{
	m_pSink = NULL;
}

CPreMeetingServiceMgr::CPreMeetingServiceMgr(CDemoUI* pSink)
{
	m_pSink = pSink;
}

CPreMeetingServiceMgr::~CPreMeetingServiceMgr()
{

}

bool CPreMeetingServiceMgr::Init()
{
	if (ZOOM_SDK_NAMESPACE::CreatePreMeetingService(&m_pPreMeetingService) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	if (m_pPreMeetingService == NULL)
		return false;

	if (m_pPreMeetingService->SetEvent(this) != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

bool CPreMeetingServiceMgr::ListMeeting()
{
	if (m_pPreMeetingService == NULL)
		return false;
	
	if (m_pPreMeetingService->ListMeeting() != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		return false;

	return true;
}

void CPreMeetingServiceMgr::onListMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, ZOOM_SDK_NAMESPACE::IList<UINT64 >* lstMeetingList)
{
	
}

void CPreMeetingServiceMgr::onScheduleOrEditMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, UINT64 meetingUniqueID)
{

}

void CPreMeetingServiceMgr::onDeleteMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result)
{

}
