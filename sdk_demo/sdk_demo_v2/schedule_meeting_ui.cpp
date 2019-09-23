#include "stdafx.h"
#include "schedule_meeting_ui.h"

CSDKSheduleMeetingUIGroup::CSDKSheduleMeetingUIGroup()
{
	m_main_frame = NULL;
	m_topic = NULL;
	m_btn_schedule = NULL;
	m_btn_back = NULL;
	m_start_time = NULL;
	m_schedule_meeting_info = NULL;
	m_schedule_or_edit_success = NULL;
	m_meeting_id_list = NULL;
	m_edit_meeting = NULL;
	m_delete_meeting = NULL;
	m_bedit_meeting = false;
	m_duration_hours = NULL;
	m_duration_mins = NULL;
	m_host_open = NULL;
	m_host_close = NULL;
	m_attendee_open = NULL;
	m_attendee_close = NULL;
	m_audio_telphone = NULL;
	m_audio_voip = NULL;
	m_audio_both = NULL;
	m_set_meeting_pwd = NULL;
	m_enable_join_before_host = NULL;
	m_mute_meeting = NULL;
	m_use_pmi = NULL;
	m_record_auto = NULL;
	m_input_meeting_pwd = NULL;
	m_input_meeting_id = NULL;
}

CSDKSheduleMeetingUIGroup::~CSDKSheduleMeetingUIGroup()
{
	m_main_frame = NULL;
	m_topic = NULL;
	m_btn_schedule = NULL;
	m_btn_back = NULL;
	m_start_time = NULL;
	m_schedule_meeting_info = NULL;
	m_schedule_or_edit_success = NULL;
	m_meeting_id_list = NULL;
	m_edit_meeting = NULL;
	m_delete_meeting = NULL;
	m_bedit_meeting = false;
	m_duration_hours = NULL;
	m_duration_mins = NULL;
	m_host_open = NULL;
	m_host_close = NULL;
	m_attendee_open = NULL;
	m_attendee_close = NULL;
	m_audio_telphone = NULL;
	m_audio_voip = NULL;
	m_audio_both = NULL;
	m_set_meeting_pwd = NULL;
	m_enable_join_before_host = NULL;
	m_mute_meeting = NULL;
	m_use_pmi = NULL;
	m_record_auto = NULL;
	m_input_meeting_pwd = NULL;
	m_input_meeting_id = NULL;
}

void CSDKSheduleMeetingUIGroup::InitWindow( CPaintManagerUI& ui_mgr, CSDKSheduleMeetingUIMgr* main_frame_ )
{
	m_topic = static_cast<CRichEditUI* >(ui_mgr.FindControl(L"topic_text"));
	m_btn_schedule = static_cast<CButtonUI* >(ui_mgr.FindControl(L"btn_schedule"));
	m_main_frame = main_frame_;
	m_shedule_meeting_workflow.SetEvent(this);
	m_shedule_meeting_workflow.ListMeeting();

	m_btn_back = static_cast<CButtonUI* >(ui_mgr.FindControl(L"back_to_schedule_meeting_page"));
	m_schedule_meeting_info = static_cast<CRichEditUI* >(ui_mgr.FindControl(L"schedule_meeting_info"));
	m_schedule_or_edit_success = static_cast<CLabelUI* >(ui_mgr.FindControl(L"schedule_or_edit_success"));

	m_meeting_id_list = static_cast<CListUI* >(ui_mgr.FindControl(L"meeting_id_list"));
	m_edit_meeting = static_cast<CButtonUI* >(ui_mgr.FindControl(L"btn_edit_meeting"));
	m_delete_meeting =static_cast<CButtonUI* >(ui_mgr.FindControl(L"btn_delete_meeting"));
	m_input_meeting_id = static_cast<CRichEditUI* >(ui_mgr.FindControl(L"input_meeting_id"));

	m_start_time = static_cast<CRichEditUI* >(ui_mgr.FindControl(L"start_time"));
	m_duration_hours = static_cast<CComboUI* >(ui_mgr.FindControl(L"duration_hours"));
	m_duration_mins = static_cast<CComboUI* >(ui_mgr.FindControl(L"duration_mins"));
	m_host_open = static_cast<COptionUI* >(ui_mgr.FindControl(L"option_host_open"));
	m_host_close = static_cast<COptionUI* >(ui_mgr.FindControl(L"option_host_close"));
	m_attendee_open =static_cast<COptionUI* >(ui_mgr.FindControl(L"option_attendee_open"));
	m_attendee_close = static_cast<COptionUI* >(ui_mgr.FindControl(L"option_attendee_close"));
	m_audio_telphone = static_cast<COptionUI* >(ui_mgr.FindControl(L"option_telephone"));
	m_audio_voip = static_cast<COptionUI* >(ui_mgr.FindControl(L"option_voip"));
	m_audio_both = static_cast<COptionUI* >(ui_mgr.FindControl(L"option_both"));
	m_set_meeting_pwd = static_cast<CCheckBoxUI* >(ui_mgr.FindControl(L"option_set_meeting_pwd"));
	m_enable_join_before_host = static_cast<CCheckBoxUI* >(ui_mgr.FindControl(L"option_enable_join_before_host"));
	m_mute_meeting = static_cast<CCheckBoxUI* >(ui_mgr.FindControl(L"option_mute_meeting"));
	m_use_pmi = static_cast<CCheckBoxUI* >(ui_mgr.FindControl(L"option_use_PMI"));
	m_record_auto = static_cast<CCheckBoxUI* >(ui_mgr.FindControl(L"option_record_auto"));
	m_input_meeting_pwd = static_cast<CRichEditUI* >(ui_mgr.FindControl(L"edit_set_meeting_pwd"));

	//set start time
	ShowLocaltime();

	// default topic
	m_topic->SetText(L"Zoom test meeting");
}

void CSDKSheduleMeetingUIGroup::UninitWindow()
{
	m_shedule_meeting_workflow.SetEvent(NULL);
	m_shedule_meeting_workflow.Uninit();
}


void CSDKSheduleMeetingUIGroup::ShowLocaltime()
{
	m_topic->SetText(L"Zoom test meeting");
	time_t now = time(0);
	struct tm* start_time = localtime(&now);
	TCHAR recieve_time[MAX_PATH] = {0};
	wcsftime(recieve_time, 80, L"%Y-%m-%d %H:%M:%S", start_time);
	m_start_time->SetText(recieve_time);
}

void CSDKSheduleMeetingUIGroup::Show()
{

}

void CSDKSheduleMeetingUIGroup::Hide()
{

}

void CSDKSheduleMeetingUIGroup::Notify( TNotifyUI& msg )
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_btn_schedule)
		{
			DoClickScheduleBtn();
		}
		else if (msg.pSender == m_btn_back)
		{
			DoClickBackBtn();
		}
		else if (msg.pSender == m_edit_meeting)
		{
			DoClickEditMeetingBtn();
		}
		else if (msg.pSender == m_delete_meeting)
		{
			DoClickDeleteMeetingBtn();
		}
		else if (msg.pSender == m_set_meeting_pwd)
		{
			if(m_set_meeting_pwd->GetCheck() == false)
				m_input_meeting_pwd->SetVisible(true);
			else
				m_input_meeting_pwd->SetVisible(false);
		}
	}
	else if (msg.sType == _T("itemselect"))
	{
		if (msg.pSender == m_meeting_id_list)
		{
			int index = m_meeting_id_list->GetCurSel();
			TCHAR meetingID[MAX_PATH] = {0};
			if (0 == index)
			{//pmi
				_i64tot_s(m_pmi, meetingID, 11, 10);
			}
			else
			{
				CListTextElementUI* pSelectedItem = static_cast<CListTextElementUI*>(m_meeting_id_list->GetItemAt(index));
				wsprintf(meetingID, L"%d", _wcstoui64(pSelectedItem->GetText(0),NULL,10));
			}
			m_input_meeting_id->SetText(meetingID);

		}
	}
}
time_t StringToDatetime(const wchar_t *str)
{
	tm tm_;
	int year, month, day, hour, minute,second;
	swscanf(str,L"%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	tm_.tm_year  = year-1900;
	tm_.tm_mon   = month-1;
	tm_.tm_mday  = day;
	tm_.tm_hour  = hour;
	tm_.tm_min   = minute;
	tm_.tm_sec   = second;
	tm_.tm_isdst = 0;

	time_t t_ = mktime(&tm_); 
	return t_; 
}
void CSDKSheduleMeetingUIGroup::DoClickScheduleBtn()
{	//todo schedule meeting

	bool bSuccess;
	if (!m_bedit_meeting)
	{
		ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* pScheduelMeetingItem = m_shedule_meeting_workflow.GetScheduleMeetingItem();
		if (NULL == pScheduelMeetingItem)
		{
			if(m_main_frame)
				m_main_frame->ShowErrorMessage(ScheduleMeetingFailed);
			return;
		}


		pScheduelMeetingItem->SetMeetingTopic(m_topic->GetText().GetData());
		//set start time
		if (m_start_time)
		{
			std::wstring s = m_start_time->GetText().GetData();
			pScheduelMeetingItem->SelectStartTime(StringToDatetime(s.c_str()));
		}

		//set duration
		if (m_duration_hours && m_duration_mins)
		{
			int mins = m_duration_hours->GetCurSel()*60+m_duration_mins->GetCurSel()*15;
			ZOOM_SDK_NAMESPACE::SDKError err = pScheduelMeetingItem->SetDurationInMinutes(mins);
		}

		//video options
		if (m_host_open && m_attendee_open )
		{
			if (m_host_open->IsSelected() == true)
				pScheduelMeetingItem->SelectHostVideoOnOrOff(true);
			else
				pScheduelMeetingItem->SelectHostVideoOnOrOff(false);

			if (m_attendee_open->IsSelected() == true)
				pScheduelMeetingItem->SelectAttendeeVideoOnOrOff(true);
			else
				pScheduelMeetingItem->SelectAttendeeVideoOnOrOff(false);
		}


		//audio options
		if (m_audio_telphone && m_audio_voip )
		{
			if (m_audio_telphone->IsSelected() == true)
			{
				if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == pScheduelMeetingItem->IsSupportAudioType(ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_telephony))
				{
					pScheduelMeetingItem->SelectAudioType(ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_telephony);
				}

			}
			else if (m_audio_voip->IsSelected() == true)
			{
				if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == pScheduelMeetingItem->IsSupportAudioType(ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_voip))
				{
					pScheduelMeetingItem->SelectAudioType(ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_voip);
				}

			}
			else
			{
				if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == pScheduelMeetingItem->IsSupportAudioType(ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_both))
				{
					ZOOM_SDK_NAMESPACE::SDKError err;
					err = pScheduelMeetingItem->SelectAudioType(ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_both);
				}

			}
		}

		//meeting options
		bool can_change(false);
		if (!pScheduelMeetingItem->IsMeetingPasswordEnabled(can_change) && can_change && m_set_meeting_pwd)
		{
			if (m_input_meeting_pwd  && m_set_meeting_pwd->IsSelected())
			{
				pScheduelMeetingItem->EnableMeetingPassword(true);
				std::wstring pwd = m_input_meeting_pwd->GetText().GetData();
				if (pwd.size()<=0)
				{
					if(m_main_frame)
						m_main_frame->ShowErrorMessage(PwdIsEmpty);
					return;
				}
				pScheduelMeetingItem->SetMeetingPassword(pwd.c_str());
			}
		}
		else
		{
			if (m_main_frame)
			{
				m_main_frame->ShowErrorMessage(CanNotSetPwd);
			}
		}

		if (m_enable_join_before_host && m_enable_join_before_host->IsSelected())
		{
			if (!pScheduelMeetingItem->IsJoinBeforeHostEnabled(can_change) && can_change)
			{
				pScheduelMeetingItem->EnableJoinBeforeHost(true);
			}
		}
		else
		{
			if (pScheduelMeetingItem->IsJoinBeforeHostEnabled(can_change) && can_change)
			{
				pScheduelMeetingItem->EnableJoinBeforeHost(false);
			}
		}

		if (m_mute_meeting && m_mute_meeting->IsSelected() )
		{
			if (!pScheduelMeetingItem->IsMuteUponEntryEnabled(can_change) && can_change)
			{
				pScheduelMeetingItem->EnableMuteUponEntry(true);
			}
		}
		else
		{
			if (pScheduelMeetingItem->IsMuteUponEntryEnabled(can_change) && can_change)
			{
				pScheduelMeetingItem->EnableMuteUponEntry(false);
			}
		}

		if (m_use_pmi && m_use_pmi->IsSelected())
		{
			if (!pScheduelMeetingItem->IsScheduleWithPmiEnabled(can_change) && can_change)
			{
				pScheduelMeetingItem->EnableScheduleWithPmi(true);
			}
		}
		else
		{
			if (pScheduelMeetingItem->IsScheduleWithPmiEnabled(can_change) && can_change)
			{
				pScheduelMeetingItem->EnableScheduleWithPmi(false);
			}
		}

		int support_rec_type = 0;
		if (m_record_auto && m_record_auto->IsSelected())
		{
			if (!pScheduelMeetingItem->IsAutoRecordEnabled(can_change, support_rec_type) && can_change)
			{
				pScheduelMeetingItem->EnableAutoRecord(true);
			}
		}
		else
		{
			if (pScheduelMeetingItem->IsAutoRecordEnabled(can_change, support_rec_type) && can_change)
			{
				pScheduelMeetingItem->EnableAutoRecord(false);
			}
		}

		bSuccess = m_shedule_meeting_workflow.ScheduleMeeting();
		if (!bSuccess && m_main_frame )
		{
			m_main_frame->ShowErrorMessage(ScheduleMeetingFailed);
		}
	}
	else
	{
		//to do edit meeting

		ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* pEditMeetingItem = m_shedule_meeting_workflow.GetEditMeetingItem(m_edit_or_delete_meeting_id);
		if (NULL == pEditMeetingItem )
		{
			if (m_main_frame)
			{
				m_main_frame->ShowErrorMessage(NoThisMeeting);
			}
			return;
		}
		//set topic
		const wchar_t* topic = pEditMeetingItem->GetMeetingTopic();
		m_topic->SetText(topic);
		//set start time
		if (m_start_time)
		{
			std::wstring s = m_start_time->GetText().GetData();
			pEditMeetingItem->SelectStartTime(StringToDatetime(s.c_str()));
		}

		//set duration
		if (m_duration_hours && m_duration_mins)
		{
			int mins = m_duration_hours->GetCurSel()*60+m_duration_mins->GetCurSel()*15;
			pEditMeetingItem->SetDurationInMinutes(mins);
		}

		//video options
		if ( m_host_open && m_attendee_open )
		{
			if (m_host_open->IsSelected() == true)
				pEditMeetingItem->SelectHostVideoOnOrOff(true);
			else
				pEditMeetingItem->SelectHostVideoOnOrOff(false);

			if (m_attendee_open->IsSelected() == true)
				pEditMeetingItem->SelectAttendeeVideoOnOrOff(true);
			else
				pEditMeetingItem->SelectAttendeeVideoOnOrOff(false);
		}

		//audio options
		if( m_audio_telphone && m_audio_voip )
		{
			if (m_audio_telphone->IsSelected() == true)
			{
				pEditMeetingItem->SelectAudioType(ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_telephony);
			}
			else if (m_audio_voip->IsSelected() == true)
			{
				pEditMeetingItem->SelectAudioType(ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_voip);
			}
			else
			{
				ZOOM_SDK_NAMESPACE::SDKError err;
				err = pEditMeetingItem->SelectAudioType(ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_both);
			}
		}

		//meeting options
		bool can_change(false);
		if (m_set_meeting_pwd && m_set_meeting_pwd->IsSelected())
		{
			if (!pEditMeetingItem->IsMeetingPasswordEnabled(can_change) && can_change && m_input_meeting_pwd)
			{
				pEditMeetingItem->EnableMeetingPassword(true);
				std::wstring pwd = m_input_meeting_pwd->GetText().GetData();
				if (pwd.size()<=0)
				{
					if(m_main_frame)
						m_main_frame->ShowErrorMessage(PwdIsEmpty);
					return;
				}
				pEditMeetingItem->SetMeetingPassword(pwd.c_str());
			}
		}
		else
		{
			if (pEditMeetingItem->IsMeetingPasswordEnabled(can_change) && can_change && m_input_meeting_pwd)
			{
				pEditMeetingItem->EnableMeetingPassword(false);
			}
		}


		if (m_enable_join_before_host && m_enable_join_before_host->IsSelected())
		{
			if (!pEditMeetingItem->IsJoinBeforeHostEnabled(can_change) && can_change)
			{
				pEditMeetingItem->EnableJoinBeforeHost(true);
			}
		}
		else
		{
			if (pEditMeetingItem->IsJoinBeforeHostEnabled(can_change) && can_change)
			{
				pEditMeetingItem->EnableJoinBeforeHost(false);
			}
		}

		if (m_mute_meeting && m_mute_meeting->IsSelected() )
		{
			if (!pEditMeetingItem->IsMuteUponEntryEnabled(can_change) && can_change)
			{
				pEditMeetingItem->EnableMuteUponEntry(true);
			}
		}
		else
		{
			if (pEditMeetingItem->IsMuteUponEntryEnabled(can_change) && can_change)
			{
				pEditMeetingItem->EnableMuteUponEntry(false);
			}
		}

		if (m_use_pmi && m_use_pmi->IsSelected())
		{
			if (!pEditMeetingItem->IsScheduleWithPmiEnabled(can_change) && can_change)
			{
				pEditMeetingItem->EnableScheduleWithPmi(true);
			}
		}
		else
		{
			if (pEditMeetingItem->IsScheduleWithPmiEnabled(can_change) && can_change)
			{
				pEditMeetingItem->EnableScheduleWithPmi(false);
			}
		}

		int support_rec_type = 0;
		if (m_record_auto && m_record_auto->IsSelected())
		{
			if (!pEditMeetingItem->IsAutoRecordEnabled(can_change, support_rec_type) && can_change)
			{
				pEditMeetingItem->EnableAutoRecord(true);
			}
		}
		else
		{
			if (pEditMeetingItem->IsAutoRecordEnabled(can_change, support_rec_type) && can_change)
			{
				pEditMeetingItem->EnableAutoRecord(false);
			}
		}

		bSuccess = m_shedule_meeting_workflow.EditMeeting();
		m_bedit_meeting = false;
		if (!bSuccess && m_main_frame)
		{
			m_main_frame->ShowErrorMessage(EditMeetingFailed);
		}

	}

	if (bSuccess&&m_main_frame)
	{
		m_main_frame->ShowWaitingGif(true);
	}

}


void CSDKSheduleMeetingUIGroup::DoClickBackBtn()
{
	if (m_main_frame)
	{
		m_main_frame->SwitchToPage(ScheduleMeetingPage);
	}
}

void CSDKSheduleMeetingUIGroup::DoClickEditMeetingBtn()
{
	m_edit_or_delete_meeting_id = _wcstoui64(m_input_meeting_id->GetText().GetData(),NULL,10);
	ZOOM_SDK_NAMESPACE::IMeetingItemInfo* pMeetingItemInfo = m_shedule_meeting_workflow.GetMeeingItem(m_edit_or_delete_meeting_id);
	if ( NULL == pMeetingItemInfo )
	{
		if(m_main_frame)
			m_main_frame->ShowErrorMessage(NoThisMeeting);
		return;
	}
	if(m_edit_or_delete_meeting_id != 0 && NULL != pMeetingItemInfo)
	{
		if (pMeetingItemInfo->IsPMI())
		{
			if (m_main_frame)
				m_main_frame->ShowErrorMessage(NotSupportEditPMI);
			return;
		}
		m_bedit_meeting = true;
		if(m_btn_schedule)
			m_btn_schedule->SetText(L"Save");
		//to update ui

		//set topic
		std::wstring topic;
		topic = pMeetingItemInfo->GetMeetingTopic();
		OutputDebugString(topic.c_str());
		if(m_topic)
			m_topic->SetText(topic.c_str());

		// set start time
		TCHAR format_time[MAX_PATH]={0};
		time_t start_time;
		start_time =pMeetingItemInfo->GetCurrentStartTime();
		struct tm *tmp_time;
		tmp_time = localtime(&start_time);
		wcsftime(format_time,80,L"%Y-%m-%d %H:%M:%S",tmp_time);
		if ( m_start_time )
		{
			m_start_time->SetText(format_time);	
		}

		//set duration
		int total_mins = pMeetingItemInfo->GetDurationInMinutes();
		int hours = total_mins/60;
		int mins = total_mins%60;
		if ( m_duration_hours && m_duration_mins)
		{
			m_duration_hours->SelectItem(hours);
			m_duration_mins->SelectItem(mins/15);
		}

		//set video options
		bool host_open = pMeetingItemInfo->IsHostVideoOnOrOff();
		if ( m_host_open && m_host_close )
		{
			if (host_open)
			{
				m_host_open->Selected(true);
			}
			else
				m_host_close->Selected(true);
		}


		bool attendee_open = pMeetingItemInfo->IsAttendeeVideoOnOrOff();
		if (m_attendee_open && m_attendee_close )
		{
			if (attendee_open)
			{
				m_attendee_open->Selected(true);
			}
			else
				m_attendee_close->Selected(true);
		}

		// set audio options
		ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE audio_type;
		pMeetingItemInfo->GetSelectedAudioType(audio_type);
		if ( m_audio_telphone && m_audio_voip && m_audio_both)
		{
			if (audio_type == ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_telephony)
				m_audio_telphone->Selected(true);
			else if (audio_type == ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_voip)
				m_audio_voip->Selected(true);
			else if(audio_type == ZOOM_SDK_NAMESPACE::SCHEDULEAUDIOTYPE_both)
				m_audio_both->Selected(true);
		}

		//test meeting options show out
		bool can_change(false);
		if (m_set_meeting_pwd && m_input_meeting_pwd)
		{
			if (pMeetingItemInfo->IsMeetingPasswordEnabled(can_change))
			{
				m_set_meeting_pwd->Selected(true);
				m_input_meeting_pwd->SetText(pMeetingItemInfo->GetMeetingPassword());
				m_input_meeting_pwd->SetVisible(true);
			}
			else
			{
				m_set_meeting_pwd->Selected(false);
				m_input_meeting_pwd->SetText(L"");
				m_input_meeting_pwd->SetVisible(false);
			}
		}

		if (m_enable_join_before_host)
		{
			if( pMeetingItemInfo->IsJoinBeforeHostEnabled(can_change) && m_enable_join_before_host)
			{
				m_enable_join_before_host->Selected(true);
			}
			else
			{
				m_enable_join_before_host->Selected(false);
			}
		}

		if (m_mute_meeting)
		{
			if (pMeetingItemInfo->IsMuteUponEntryEnabled(can_change))
			{
				m_mute_meeting->Selected(true);
			}
			else
			{
				m_mute_meeting->Selected(false);
			}
		}

		if (m_use_pmi)
		{
			if (pMeetingItemInfo->IsScheduleWithPmiEnabled(can_change))
			{
				m_use_pmi->Selected(true);
			}
			else
			{
				m_use_pmi->Selected(false);
			}
		}


		int support_rec_type = 0;
		if (m_record_auto)
		{
			if (pMeetingItemInfo->IsAutoRecordEnabled(can_change,support_rec_type))
			{
				m_record_auto->Selected(true);
			}
			else
			{
				m_record_auto->Selected(false);
			}
		}


		if (m_main_frame)
		{
			m_main_frame->SwitchToPage(EditMeetingPage);
		}

	}



}

void CSDKSheduleMeetingUIGroup::DoClickDeleteMeetingBtn()
{
	m_edit_or_delete_meeting_id = _wcstoui64(m_input_meeting_id->GetText().GetData(),NULL,10);
	ZOOM_SDK_NAMESPACE::IMeetingItemInfo* pMeetingItemInfo = m_shedule_meeting_workflow.GetMeeingItem(m_edit_or_delete_meeting_id);
	if (pMeetingItemInfo == NULL )
	{
		if (m_main_frame)
		{
			m_main_frame->ShowErrorMessage(NoThisMeeting);
		}
		return;
	}

	if (pMeetingItemInfo->IsPMI() && m_main_frame)
	{
		m_main_frame->ShowErrorMessage(CanNotDeletePMI);
		return;
	}
	bool bDeleteSuccess = m_shedule_meeting_workflow.DeleteMeeting(m_edit_or_delete_meeting_id);
	if (m_main_frame)
	{
		m_main_frame->ShowWaitingGif(true);
	}
	if (!bDeleteSuccess && m_main_frame)
	{
		m_main_frame->ShowErrorMessage(DeleteMeetingFailed);
	}
}

void CSDKSheduleMeetingUIGroup::onListMeeting( ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, ZOOM_SDK_NAMESPACE::IList<UINT64 >* lstMeetingList )
{
	if (ZOOM_SDK_NAMESPACE::PREMETAPIRET_SUCCESS == result)
	{
		if (m_meeting_id_list)
		{
			m_meeting_id_list->RemoveAll();
		}

		if (lstMeetingList)
		{
			int nCount = lstMeetingList->GetCount();
			for (int i=0;i<nCount;++i)
			{
				CListTextElementUI* pListElement = new CListTextElementUI;
				if(NULL == m_meeting_id_list|| NULL == pListElement)
					continue;

				m_meeting_id_list->Add(pListElement);

				UINT64 meeting_id = lstMeetingList->GetItem(i);
				TCHAR tmp[MAX_PATH]={0};
				ZOOM_SDK_NAMESPACE::IMeetingItemInfo* pMeetingItemInfo = m_shedule_meeting_workflow.GetMeeingItem(meeting_id);
				bool can_change(false);
				if( NULL == pMeetingItemInfo)
					continue;
				if (pMeetingItemInfo->IsPMI())
				{
					m_pmi = meeting_id;
					_i64tot_s(meeting_id, tmp,11,10);
					wsprintf(tmp,L"%s (PMI)",tmp);
				}
				else if (pMeetingItemInfo->IsScheduleWithPmiEnabled(can_change))
				{
					_i64tot_s(meeting_id, tmp,11,10);
					wsprintf(tmp,L"%s (use PMI)",tmp);
				}
				else
				{
					_i64tot_s(meeting_id, tmp,11,10);
				}
				if (pListElement)
				{
					pListElement->SetText(0,tmp);
				}

			}
		}
	}
	else
	{
		if (m_main_frame)
		{
			m_main_frame->ShowErrorMessage(ApiUnknowErr);
		}
	}
}

void CSDKSheduleMeetingUIGroup::onScheduleOrEditMeeting( ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, UINT64 meetingUniqueID )
{
	if (result == ZOOM_SDK_NAMESPACE::PREMETAPIRET_SUCCESS)
	{
		if(m_schedule_meeting_info)
		{
			m_schedule_meeting_info->SetText(L"");
		}
		
		ZOOM_SDK_NAMESPACE::IMeetingItemInfo* pMeetingItemInfo = m_shedule_meeting_workflow.GetMeeingItem(meetingUniqueID);

		std::wstring meeting_info;
		if (pMeetingItemInfo)
		{
			meeting_info = std::wstring(pMeetingItemInfo->GetMeetingTopic())+L"\n"
				+std::wstring( pMeetingItemInfo->GetInviteEmailSubject())+L"\n"
				+std::wstring(pMeetingItemInfo->GetInviteEmailContent());

			TCHAR tmp[MAX_PATH] = {0};
			wsprintf(tmp, L"%d", pMeetingItemInfo->GetMeetingID());
			OutputDebugString(tmp);
		}

		if (m_schedule_meeting_info)
		{
			m_schedule_meeting_info->SetText(meeting_info.c_str());
		}


		if (m_main_frame)
		{
			m_main_frame->ShowWaitingGif(false);
			m_main_frame->SwitchToPage(ShowScheduleMeetingInfoPage);
			if (m_btn_schedule)
			{
				m_btn_schedule->SetText(L"Schedule");
			}
		}

		if (m_schedule_or_edit_success)
		{
			m_schedule_or_edit_success->SetText(L"Schedule or edit meeting success !");
		}
	}
	else
	{
		if (m_schedule_or_edit_success)
		{
			m_schedule_or_edit_success->SetText(L"Schedule or edit meeting failed !");
		}
		if (m_main_frame)
		{
			m_main_frame->ShowWaitingGif(false);
		}
	}

}

void CSDKSheduleMeetingUIGroup::onDeleteMeeting( ZOOM_SDK_NAMESPACE::PremeetingAPIResult result )
{
	if (result == ZOOM_SDK_NAMESPACE::PREMETAPIRET_SUCCESS)
	{
		if (m_main_frame)
		{
			m_main_frame->ShowWaitingGif(false);
		}
		TCHAR szlog[MAX_PATH]={0};
		wsprintf(szlog,L"delete meeting success !\n");
		OutputDebugString(szlog);
	}
	else
	{
		if (m_main_frame)
		{
			m_main_frame->ShowErrorMessage(ApiUnknowErr);
		}
	}
}

void CSDKSheduleMeetingUIGroup::SetNotBeEditMeeting()
{
	m_bedit_meeting = false;
}

bool CSDKSheduleMeetingUIGroup::GetEditMeetingStatus()
{
	return m_bedit_meeting;
}
CSDKSheduleMeetingUIMgr::CSDKSheduleMeetingUIMgr()
{
	m_pAppEvent = NULL;
	m_current_page = NULL;
	m_schedule_meeting_page = NULL;
	m_show_schedule_meeting_info_page = NULL;
	m_edit_delete_meeting_page = NULL;
	m_schedule_meeting = NULL;
	m_edit_meeting = NULL;
	m_btn_schedule = NULL;
	m_gifWaiting = NULL;
	m_waiting_page = NULL;
}

CSDKSheduleMeetingUIMgr::~CSDKSheduleMeetingUIMgr()
{
	m_pAppEvent = NULL;
	m_current_page = NULL;
	m_schedule_meeting_page = NULL;
	m_show_schedule_meeting_info_page = NULL;
	m_edit_delete_meeting_page = NULL;
	m_schedule_meeting = NULL;
	m_edit_meeting = NULL;
	m_btn_schedule = NULL;
	m_gifWaiting = NULL;
	m_waiting_page = NULL;
}

void CSDKSheduleMeetingUIMgr::SetEvent( CSDKDemoAppEvent* pAppEvent )
{
	m_pAppEvent = pAppEvent;
}

void CSDKSheduleMeetingUIMgr::InitWindow()
{
	m_SheduleMeetingGroup.InitWindow(m_PaintManager,this);
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) return;
	rc.right = rc.left + 524;
	rc.bottom = rc.top + /*376*/700;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), (!(GetWindowStyle(m_hWnd) & WS_CHILD) && (::GetMenu(m_hWnd) != NULL)), GetWindowExStyle(m_hWnd)) ) return;
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, NULL, (ScreenX - (rc.right - rc.left)) / 2, 
		(ScreenY - (rc.bottom - rc.top)) / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_SHOWWINDOW);

	m_schedule_meeting_page = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(L"schedule_meeting_panel"));
	m_show_schedule_meeting_info_page = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(L"show_schedule_meeting_info"));
	m_edit_delete_meeting_page = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(L"edit_meeting_panel"));
	m_current_page = m_schedule_meeting_page;
	m_schedule_meeting = static_cast<COptionUI* >(m_PaintManager.FindControl(L"tabbtn_schedule_meeting"));
	m_edit_meeting = static_cast<COptionUI* >(m_PaintManager.FindControl(L"tabbtn_edit_meeting"));
	m_btn_schedule = static_cast<CButtonUI* >(m_PaintManager.FindControl(L"btn_schedule"));
	m_gifWaiting = static_cast<CGifAnimUI* >(m_PaintManager.FindControl(L"gif_waiting"));
	m_waiting_page = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(L"waiting_panel"));

}

void CSDKSheduleMeetingUIMgr::Notify( TNotifyUI& msg )
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_schedule_meeting)
		{
			if (m_SheduleMeetingGroup.GetEditMeetingStatus())//leave edit page notify
			{
				ShowErrorMessage(LeaveEditMeeting);
			}
			SwitchToPage(ScheduleMeetingPage);
			m_SheduleMeetingGroup.SetNotBeEditMeeting();
		}
		else if (msg.pSender == m_edit_meeting)
		{
			if (m_SheduleMeetingGroup.GetEditMeetingStatus())
			{
				ShowErrorMessage(LeaveEditMeeting);
			}
			SwitchToPage(EditAndDeleteMeetingPage);
			m_SheduleMeetingGroup.SetNotBeEditMeeting();
		}
		else
			m_SheduleMeetingGroup.Notify(msg);
	}
	else
		m_SheduleMeetingGroup.Notify(msg);
}

LRESULT CSDKSheduleMeetingUIMgr::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	if( uMsg == WM_CREATE )  
	{
		m_PaintManager.Init(m_hWnd);

		CDialogBuilder builder;
		STRINGorID xml(GetSkinRes());
		CControlUI* pRoot = builder.Create(xml, _T("xml"), 0, &m_PaintManager);
		ASSERT(pRoot && "Failed to parse XML");

		m_PaintManager.AttachDialog(pRoot);
		m_PaintManager.AddNotifier(this);
		InitWindow(); 

		return lRes;
	}
	else if (uMsg == WM_CLOSE)
	{
		OnClose(uMsg, wParam, lParam, bHandled);		
	}
	else if (uMsg == WM_DESTROY)
	{
		OnDestroy(uMsg, wParam, lParam, bHandled);		
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CSDKSheduleMeetingUIMgr::OnClose( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	//if (m_pAppEvent)
	//{
	//	m_pAppEvent->onQuitApp();
	//}

	return 0;
}

LRESULT CSDKSheduleMeetingUIMgr::OnDestroy( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	m_SheduleMeetingGroup.UninitWindow();
	return 0;
}

CSDKDemoAppEvent* CSDKSheduleMeetingUIMgr::GetAppEvent()
{
	return m_pAppEvent;
}

void CSDKSheduleMeetingUIMgr::SetCurrentPage( CVerticalLayoutUI* _current_page)
{
	m_current_page = _current_page;
}

void CSDKSheduleMeetingUIMgr::SwitchToPage( PreMeetingPageType _page_type )
{
	switch(_page_type)
	{
	case ScheduleMeetingPage:
		if (m_current_page && m_schedule_meeting_page && m_btn_schedule)
		{
			m_current_page->SetVisible(false);
			m_schedule_meeting_page->SetVisible(true);
			m_current_page = m_schedule_meeting_page;
			m_btn_schedule->SetText(L"Schedule");
			m_SheduleMeetingGroup.ShowLocaltime();
			m_schedule_meeting->Selected(true);
		}
		break;
	case EditMeetingPage:
		if (m_current_page && m_schedule_meeting_page )
		{
			m_current_page->SetVisible(false);
			m_schedule_meeting_page->SetVisible(true);
			m_current_page = m_schedule_meeting_page;
		}
		break;
	case ShowScheduleMeetingInfoPage:
		if (m_current_page && m_show_schedule_meeting_info_page)
		{
			m_current_page->SetVisible(false);
			m_show_schedule_meeting_info_page->SetVisible(true);
			m_current_page = m_show_schedule_meeting_info_page;
		}
		break;
	case EditAndDeleteMeetingPage:
		if (m_current_page && m_edit_delete_meeting_page)
		{
			m_current_page->SetVisible(false);
			m_edit_delete_meeting_page->SetVisible(true);
			m_current_page = m_edit_delete_meeting_page;
		}
		break;
	case WaitingPage:
		if (m_current_page && m_waiting_page)
		{
			m_current_page->SetVisible(false);
			m_waiting_page->SetVisible(true);
		}
		break;
	}
}

void CSDKSheduleMeetingUIMgr::ShowErrorMessage( ErrorMessageType _type )
{
	switch(_type)
	{
	case NoThisMeeting:
		::MessageBox(NULL, L"No this meeting !", L"error", MB_OK);
		break;
	case CanNotDeletePMI:
		::MessageBox(NULL, L"You can't delete PMI !", L"error", MB_OK);
		break;
	case ScheduleMeetingFailed:
		::MessageBox(NULL, L"Schedule meeting failed !", L"error", MB_OK);
		break;
	case EditMeetingFailed:
		::MessageBox(NULL, L"Edit meeting failed !", L"error", MB_OK);
		break;
	case DeleteMeetingFailed:
		::MessageBox(NULL, L"Delete meeting failed !", L"error", MB_OK);
		break;
	case CanNotScheduleMeeting:
		::MessageBox(NULL, L"Schedule or edit meeting meet unknow error !", L"error", MB_OK);
		break;
	case NotSupportEditPMI:
		::MessageBox(NULL, L"Don't support edit PMI !", L"error", MB_OK);
		break;
	case PwdIsEmpty:
		::MessageBox(NULL, L"Password is empty !", L"error", MB_OK);
		break;
	case CanNotSetPwd:
		::MessageBox(NULL, L"Can't set meeting password !", L"error", MB_OK);
		break;
	case ApiUnknowErr:
		::MessageBox(NULL, L"API return unknow error !", L"error", MB_OK);
		break;
	case LeaveEditMeeting:
		::MessageBox(NULL, L"Leave edit meeting page and don't save !", L"error", MB_OK);
		break;
	}
}

void CSDKSheduleMeetingUIMgr::ShowWaitingGif( bool bShow )
{
	if (m_waiting_page)
	{
		if (bShow)
		{
			SwitchToPage(WaitingPage);
			m_gifWaiting->PlayGif();
		}
		else
		{
			m_waiting_page->SetVisible(false);
			m_gifWaiting->StopGif();
			m_current_page->SetVisible(true);
		}
	}
}