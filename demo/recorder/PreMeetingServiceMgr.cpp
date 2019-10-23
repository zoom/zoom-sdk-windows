#include "PreMeetingServiceMgr.h"


CPreMeetingServiceMgr::CPreMeetingServiceMgr()
{
	m_pSink = NULL;
	m_pPreMeetingService = NULL;
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
	if (ZOOM_SDK_NAMESPACE::PREMETAPIRET_SUCCESS == result)
	{
		OutputMeetingListInfo(lstMeetingList);
	}
}

void CPreMeetingServiceMgr::onScheduleOrEditMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, UINT64 meetingUniqueID)
{
	if (ZOOM_SDK_NAMESPACE::PREMETAPIRET_SUCCESS == result)
	{
		OutputMeetingListInfo(meetingUniqueID);
	}
}

void CPreMeetingServiceMgr::onDeleteMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result)
{
	if (m_pPreMeetingService)
		m_pPreMeetingService->ListMeeting();
}

void CPreMeetingServiceMgr::OutputMeetingListInfo(ZOOM_SDK_NAMESPACE::IList<UINT64 >* lstMeetingList)
{
	if (lstMeetingList)
	{
		int count = lstMeetingList->GetCount();
		for (int index = 0; index < count; index++)
		{
			UINT64 meetingUniqueID = lstMeetingList->GetItem(index);
			OutputMeetingListInfo(meetingUniqueID);
		}
	}
}

void AppendToString(const wchar_t* str_name, UINT64 number_, std::wstring& out_put_str)
{
	if (str_name)
	{
		out_put_str += str_name;
		out_put_str += L"-->\n";
	}
	wchar_t tmp[64] = { 0 };
	wsprintf(tmp, L"%I64u\n", number_);
	out_put_str += tmp;
}

void AppendToString(const wchar_t* str_name, const wchar_t* str_, std::wstring& out_put_str)
{
	if (str_name)
	{
		out_put_str += str_name;
		out_put_str += L"-->\n";
	}

	if (str_)
	{
		out_put_str += str_;
		out_put_str += L"\n";
	}
}
#define __ST(x)   _T(#x)
#define APPEND_TO(key_) \
	AppendToString(__ST(key_), meeting_item_info->key_(), out_put_str);
#define APPEND_TO_WITH_PARAM(key_, param_) \
	AppendToString(__ST(key_), meeting_item_info->key_(param_), out_put_str);
#define APPEND_TO_WITH_PARAM2(key_, param_, param_2) \
	AppendToString(__ST(key_), meeting_item_info->key_(param_, param_2), out_put_str);
void CPreMeetingServiceMgr::OutputMeetingListInfo(UINT64 meetingUniqueID)
{
	if (m_pPreMeetingService)
	{
		ZOOM_SDK_NAMESPACE::IMeetingItemInfo* meeting_item_info = m_pPreMeetingService->GetMeeingItem(meetingUniqueID);
		if (meeting_item_info)
		{
			OutputDebugString(L"meeting item information begin:\n");
			OutputMeetingListInfo(meeting_item_info);
			OutputDebugString(L"meeting item information end:\n");
		}
	}
}

void CPreMeetingServiceMgr::OutputMeetingListInfo(ZOOM_SDK_NAMESPACE::IMeetingItemInfo* meeting_item_info)
{
	bool can_change = false;
	std::wstring out_put_str;
	if (meeting_item_info)
	{
		APPEND_TO(GetUniqueMeetingID)
		APPEND_TO(GetMeetingID)
		APPEND_TO(IsPMI)
		APPEND_TO(IsWebinar)
		APPEND_TO(GetMeetingTopic)
		APPEND_TO(GetInviteEmailContent)
		APPEND_TO(GetInviteEmailSubject)
		APPEND_TO(GetJoinMeetingUrl)
		if (!meeting_item_info->IsPMI() && !meeting_item_info->IsWebinar())
		{
			APPEND_TO(GetCurrentStartTime) 
			APPEND_TO(GetDurationInMinutes)
			APPEND_TO(IsRecurringMeetingSelected)
			APPEND_TO_WITH_PARAM(IsScheduleWithPmiEnabled, can_change)
			AppendToString(L"IsScheduleWithPmiEnabled-canchang", can_change, out_put_str);
		}
	}

	APPEND_TO(IsHostVideoOnOrOff)
	APPEND_TO(IsAttendeeVideoOnOrOff)
	ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE type(ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_none);
	if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == 
		meeting_item_info->GetSelectedAudioType(type))
	{
		AppendToString(L"GetSelectedAudioType:", type, out_put_str);	
	}
	APPEND_TO_WITH_PARAM(IsMeetingPasswordEnabled, can_change)
	AppendToString(L"IsMeetingPasswordEnabled-canchang", can_change, out_put_str);
	if (meeting_item_info->IsMeetingPasswordEnabled(can_change))
	{
		APPEND_TO(GetMeetingPassword)
	}
	int support_rec_type(0);
	APPEND_TO_WITH_PARAM2(IsAutoRecordEnabled, can_change, support_rec_type)
	AppendToString(L"IsAutoRecordEnabled-canchang", can_change, out_put_str);
	AppendToString(L"IsAutoRecordEnabled-support_rec_type", support_rec_type, out_put_str);
	if (meeting_item_info->IsAutoRecordEnabled(can_change, support_rec_type))
	{
		APPEND_TO(GetSelectedAutoRecordType)
	}
	if (meeting_item_info->IsMeetingPasswordEnabled(can_change))
	{
		APPEND_TO(GetMeetingPassword)
	}

	APPEND_TO_WITH_PARAM(IsJoinBeforeHostEnabled, can_change)
	AppendToString(L"IsJoinBeforeHostEnabled-canchang", can_change, out_put_str);
	APPEND_TO_WITH_PARAM(IsMuteUponEntryEnabled, can_change)
	AppendToString(L"IsMuteUponEntryEnabled-canchang", can_change, out_put_str);
	APPEND_TO_WITH_PARAM(IsHostInChinaEnabled, can_change)
	AppendToString(L"IsHostInChinaEnabled-canchang", can_change, out_put_str);

	ZOOM_SDK_NAMESPACE::IQueryMeetingItemTelAudioInfoHelper* meeting_item_tel = meeting_item_info->GetQueryTelAudioInfoHelper();
	if (meeting_item_tel)
	{
		ZOOM_SDK_NAMESPACE::IList<const wchar_t* >* lst_support_tel = meeting_item_tel->GetAvailableDialinCountryCode();
		if (lst_support_tel)
		{
			int count = lst_support_tel->GetCount();
			for (int index = 0; index < count; index++)
			{
				const wchar_t* country_code = lst_support_tel->GetItem(index);
				AppendToString(L"support:", country_code, out_put_str);
			}
		}
		ZOOM_SDK_NAMESPACE::IList<const wchar_t* >* lst_select_tel = meeting_item_tel->GetSelectedDialinCountryCode();
		if (lst_select_tel)
		{
			int count = lst_select_tel->GetCount();
			for (int index = 0; index < count; index++)
			{
				const wchar_t* country_code = lst_select_tel->GetItem(index);
				AppendToString(L"select:", country_code, out_put_str);
			}
		}

		AppendToString(L"is include tollfree:", meeting_item_tel->IsIncludeTollFree(), out_put_str);
	}

	OutputDebugString(out_put_str.c_str());
}

void CPreMeetingServiceMgr::TestScheduleMeeting()
{
	if (m_pPreMeetingService)
	{
		ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* schedule_meeting_item = m_pPreMeetingService->CreateScheduleMeetingItem();
		if (schedule_meeting_item)
		{
			OutputDebugString(L"Schedule meeting default vaule begin:\n");
			OutputMeetingListInfo(dynamic_cast<ZOOM_SDK_NAMESPACE::IMeetingItemInfo* >(schedule_meeting_item));
			OutputDebugString(L"Schedule meeting default vaule end:\n");
			
			//meeting opt
			if (!schedule_meeting_item->IsPMI())
				schedule_meeting_item->SetMeetingTopic(L"zoom test schedule");
			bool can_change(false);
			if (!schedule_meeting_item->IsMeetingPasswordEnabled(can_change) && can_change)
			{
				schedule_meeting_item->EnableMeetingPassword(true);
				schedule_meeting_item->SetMeetingPassword(L"Test@123");
			}

			if (!schedule_meeting_item->IsJoinBeforeHostEnabled(can_change) && can_change)
			{
				schedule_meeting_item->EnableJoinBeforeHost(true);
			}

			if (!schedule_meeting_item->IsMuteUponEntryEnabled(can_change) && can_change)
			{
				schedule_meeting_item->EnableMuteUponEntry(true);
			}

			if (!schedule_meeting_item->IsScheduleWithPmiEnabled(can_change) && can_change)
			{
				schedule_meeting_item->EnableScheduleWithPmi(true);
			}

			if (!schedule_meeting_item->IsHostInChinaEnabled(can_change) && can_change)
			{
				schedule_meeting_item->EnableHostInChina(true);
			}

			int support_rec_type = 0;
			if (!schedule_meeting_item->IsAutoRecordEnabled(can_change, support_rec_type) && can_change)
			{
				schedule_meeting_item->EnableAutoRecord(true);
			}
			//

			//video opt
			if (!schedule_meeting_item->IsPMI())
			{
				schedule_meeting_item->SelectHostVideoOnOrOff(true);
				schedule_meeting_item->SelectAttendeeVideoOnOrOff(true);
			}

			//audio opt
			//

			m_pPreMeetingService->ScheduleMeeting(schedule_meeting_item);

			m_pPreMeetingService->DestoryScheduleMeetingItem(schedule_meeting_item);
		}
	}
}
