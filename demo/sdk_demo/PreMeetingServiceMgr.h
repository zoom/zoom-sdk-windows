#pragma once

#include <windows.h>
#include <string>
#include "zoom_sdk.h"
#include "premeeting_service_interface.h"
#include "DemoUI.h"

class CPreMeetingServiceMgr : public ZOOM_SDK_NAMESPACE::IPreMeetingServiceEvent
{
public:
	CPreMeetingServiceMgr();
	CPreMeetingServiceMgr(CDemoUI* pSink);
	virtual ~CPreMeetingServiceMgr();


public:
	bool Init();
	bool ListMeeting();
	//ZOOM_SDK_NAMESPACE::IPreMeetingService* GetPreMeetingService();
	void TestScheduleMeeting();
public:
	virtual void onListMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, ZOOM_SDK_NAMESPACE::IList<UINT64 >* lstMeetingList);
	virtual void onScheduleOrEditMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, UINT64 meetingUniqueID);
	virtual void onDeleteMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result);

private:
	void OutputMeetingListInfo(ZOOM_SDK_NAMESPACE::IList<UINT64 >* lstMeetingList);
	void OutputMeetingListInfo(UINT64 meetingUniqueID);
	void OutputMeetingListInfo(ZOOM_SDK_NAMESPACE::IMeetingItemInfo* meeting_item_info);

private:
	CDemoUI* m_pSink;
	ZOOM_SDK_NAMESPACE::IPreMeetingService* m_pPreMeetingService;
};