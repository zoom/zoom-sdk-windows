#pragma once

#include "sdk_util.h"

class CSDKSheduleMeetingUIEvent
{
public:
	virtual void onListMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, ZOOM_SDK_NAMESPACE::IList<UINT64 >* lstMeetingList) = 0;	
	virtual void onScheduleOrEditMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, UINT64 meetingUniqueID) = 0;
	virtual void onDeleteMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result) = 0;
};

class CSDKSheduleMeetingUIWorkFlow:public ZOOM_SDK_NAMESPACE::IPreMeetingServiceEvent
{
public:
	CSDKSheduleMeetingUIWorkFlow();
	virtual ~CSDKSheduleMeetingUIWorkFlow();
	void SetEvent(CSDKSheduleMeetingUIEvent* pSink);

public:
	virtual void onListMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, ZOOM_SDK_NAMESPACE::IList<UINT64 >* lstMeetingList);
	virtual void onScheduleOrEditMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, UINT64 meetingUniqueID);
	virtual void onDeleteMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result);

public:
	bool Init();
	ZOOM_SDK_NAMESPACE::SDKError ScheduleMeeting();
	ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* GetScheduleMeetingItem();
	ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* GetEditMeetingItem(UINT64 meetingUniqueID);
	ZOOM_SDK_NAMESPACE::IMeetingItemInfo* GetMeeingItem(UINT64 meetingUniqueID);
	ZOOM_SDK_NAMESPACE::SDKError EditMeeting();
	ZOOM_SDK_NAMESPACE::SDKError DeleteMeeting(UINT64 meetingUniqueID);
	ZOOM_SDK_NAMESPACE::SDKError ListMeeting();
	bool Uninit();


protected:
	ZOOM_SDK_NAMESPACE::IPreMeetingService* m_pPreMeetingService;
	ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* m_pScheduleMeetingItem;
	ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* m_pEditMeetingItem;
	CSDKSheduleMeetingUIEvent* m_pSink;


};