#include "CustomizedUI.h"
#if (defined ENABLE_CUSTOMIZED_UI)
void CustomizeInMeetingUI::onVideoContanierDestroy()
{
	_video_container = NULL;
}

void CustomizeInMeetingUI::onShareRenderDestroy()
{
	_share_render = NULL;
}

void CustomizeInMeetingUI::onSize(RECT& rc)
{
	if (_video_container)
		_video_container->Resize(rc);

	if (_in_view_sharing)
		DoLayoutShareRender(rc);
}

void CustomizeInMeetingUI::onRenderUserChanged(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement, unsigned int userid)
{

}

void CustomizeInMeetingUI::onRenderDataTypeChanged(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement, ZOOM_SDK_NAMESPACE::VideoRenderDataType dataType)
{

}

void CustomizeInMeetingUI::onLayoutNotification(RECT wnd_client_rect)
{
	DoLayout();
}

void CustomizeInMeetingUI::onVideoRenderElementDestroyed(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement)
{
	if (pElement)
	{
		switch (pElement->GetType())
		{
		case ZOOM_SDK_NAMESPACE::VideoRenderElement_PRVIEW:
			{
				_preview_elem = NULL;
			}
			break;
		case ZOOM_SDK_NAMESPACE::VideoRenderElement_ACTIVE:
			{
				_active_elem = NULL;
			}
			break;
		case ZOOM_SDK_NAMESPACE::VideoRenderElement_NORMAL:
			{
				//todo
				for (int i = 0; i < Normal_Video_Elem_Count; i++)
				{
					ZOOM_SDK_NAMESPACE::IVideoRenderElement* tmp_ = dynamic_cast<ZOOM_SDK_NAMESPACE::IVideoRenderElement*>(_normal_elem[i]);
					if (tmp_ == pElement)
					{
						_normal_elem[i] = NULL;
					}
				}
				
			}
			break;
		}
	}
}

void CustomizeInMeetingUI::HandleSharingShareAnnotationStatusChanged4ViewShare(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_)
{
	switch (status_)
	{
	case ZOOM_SDK_NAMESPACE::CS_ANNO_READYTOUSE:
		{
			if (_anno_obj)
				return;
			if (_meeting_service->GetAnnotationController())
			{
				ZOOM_SDK_NAMESPACE::ICustomizedAnnotationController* 
					anno_ctrl_ = _meeting_service->GetAnnotationController()->GetCustomizedAnnotationController();
				if (anno_ctrl_)
				{
					anno_ctrl_->CreateAnnoObj(_share_render, &_anno_obj);
					if (_anno_obj)
					{
						_anno_obj->SetLineWidth(20);
						_anno_obj->SetColor(RGB(255, 0, 0));
						_anno_obj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_LINE);
					}
				}
			}
		}
		break;
	case ZOOM_SDK_NAMESPACE::CS_ANNO_CLOSE:
		{
			if (_anno_obj && _meeting_service->GetAnnotationController())
			{
				ZOOM_SDK_NAMESPACE::ICustomizedAnnotationController* 
					anno_ctrl_ = _meeting_service->GetAnnotationController()->GetCustomizedAnnotationController();
				if (anno_ctrl_)
				{
					anno_ctrl_->DestroyAnnoObj(_anno_obj);
				}
				_anno_obj = NULL;
			}
		}
		break;
	default:
		break;
	}
}

void CustomizeInMeetingUI::HandleSharingShareAnnotationStatusChanged4SendingShare(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_)
{
	switch (status_)
	{
	case ZOOM_SDK_NAMESPACE::CS_ANNO_READYTOUSE:
		{
			if (_anno_obj)
				return;
			if (_meeting_service->GetAnnotationController())
			{
				ZOOM_SDK_NAMESPACE::ICustomizedAnnotationController* 
					anno_ctrl_ = _meeting_service->GetAnnotationController()->GetCustomizedAnnotationController();
				if (anno_ctrl_)
				{
					anno_ctrl_->CreateAnnoObj(NULL, &_sending_sharing_anno_obj);
					if (_sending_sharing_anno_obj)
					{
						_sending_sharing_anno_obj->SetLineWidth(20);
						_sending_sharing_anno_obj->SetColor(RGB(255, 0, 0));
						_sending_sharing_anno_obj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_LINE);
					}
				}
			}
		}
		break;
	case ZOOM_SDK_NAMESPACE::CS_ANNO_CLOSE:
		{
			if (_sending_sharing_anno_obj && _meeting_service->GetAnnotationController())
			{
				ZOOM_SDK_NAMESPACE::ICustomizedAnnotationController* 
					anno_ctrl_ = _meeting_service->GetAnnotationController()->GetCustomizedAnnotationController();
				if (anno_ctrl_)
				{
					anno_ctrl_->DestroyAnnoObj(_sending_sharing_anno_obj);
				}
				_sending_sharing_anno_obj = NULL;
			}
		}
		break;
	default:
		break;
	}
}

void CustomizeInMeetingUI::onSharingShareAnnotationStatusChanged(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_)
{
	if (share_render_ == _share_render)//view share
	{
		HandleSharingShareAnnotationStatusChanged4ViewShare(share_render_, status_);
	}
	else // sending share
	{
		HandleSharingShareAnnotationStatusChanged4SendingShare(share_render_, status_);
	}
}

void CustomizeInMeetingUI::onVideoContainerWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

}

void CustomizeInMeetingUI::onSharingContentStartRecving()
{
	
}

void CustomizeInMeetingUI::onSharingSourceUserIDNotification(unsigned int userid)
{

}

void CustomizeInMeetingUI::HandleCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper)
{
	if (layout_helper)
	{

		int support_layout = layout_helper->GetSupportLayout();
		if (ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_SHARE_AND_VIDEO & support_layout)
		{
			layout_helper->SelectRecordingLayoutMode(ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_SHARE_AND_VIDEO);
			if (layout_helper->IsSendSharingSourceAvailable())
			{
				layout_helper->SelectSendSharingSource();
			}
			else
			{
				ZOOM_SDK_NAMESPACE::IList<unsigned int >* lst_recv_share = layout_helper->GetValidRecvSharingSourceList();
				int count_recv_share = lst_recv_share ? lst_recv_share->GetCount() : 0;
				if (count_recv_share > 0)
				{
					layout_helper->SelectRecvSharingSource(lst_recv_share->GetItem(0));
				}
			}

			ZOOM_SDK_NAMESPACE::IList<unsigned int >* lst_video = layout_helper->GetValidVideoSourceList();
			int count_video = lst_video ? lst_video->GetCount() : 0;
			if (count_video > 0)
			{
				for (int i = 0; i < min(count_video, 5); i++)
				{
					unsigned int user_id = lst_video->GetItem(i);
					layout_helper->AddVideoSourceToRecList(user_id);
				}
			}

			if (layout_helper->HasActiveVideoSource())
			{
				layout_helper->SelectActiveVideoSource();
			}
		}
		else if (ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_ONLY_SHARE & support_layout)
		{
			layout_helper->SelectRecordingLayoutMode(ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_ONLY_SHARE);
			if (layout_helper->IsSendSharingSourceAvailable())
			{
				layout_helper->SelectSendSharingSource();
			}
			else
			{
				ZOOM_SDK_NAMESPACE::IList<unsigned int >* lst_recv_share = layout_helper->GetValidRecvSharingSourceList();
				int count_recv_share = lst_recv_share ? lst_recv_share->GetCount() : 0;
				if (count_recv_share > 0)
				{
					layout_helper->SelectRecvSharingSource(lst_recv_share->GetItem(0));
				}
			}
		}
		else if (ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_VIDEO_WALL & support_layout)
		{
			layout_helper->SelectRecordingLayoutMode(ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_VIDEO_WALL);
			ZOOM_SDK_NAMESPACE::IList<unsigned int >* lst_video = layout_helper->GetValidVideoSourceList();
			int count_video = lst_video ? lst_video->GetCount() : 0;
			if (count_video > 0)
			{
				for (int i = 0; i < min(count_video, 5); i++)
				{
					unsigned int user_id = lst_video->GetItem(i);
					layout_helper->AddVideoSourceToRecList(user_id);
				}
			}

			if (layout_helper->HasActiveVideoSource())
			{
				layout_helper->SelectActiveVideoSource();
			}
		}
		else if (ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_ACTIVE_VIDEO_ONLY & support_layout)
		{
			layout_helper->SelectRecordingLayoutMode(ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_ACTIVE_VIDEO_ONLY);
			if (layout_helper->HasActiveVideoSource())
			{
				layout_helper->SelectActiveVideoSource();
			}
		}
		else if (ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_ONLY_AUDIO & support_layout)
		{
			layout_helper->SelectRecordingLayoutMode(ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_ONLY_AUDIO);
		}
	}
}

void CustomizeInMeetingUI::onShareRenderWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (NULL == _meeting_service)
		return;

	ZOOM_SDK_NAMESPACE::IMeetingRemoteController* remote_ctrl_ = _meeting_service->GetMeetingRemoteController();
	if (remote_ctrl_ && _share_render)
	{
		if (WM_RBUTTONUP == uMsg)//remote control
		{
			bool can_remote_ctrl = (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == remote_ctrl_->CanRequestControl(_share_render->GetUserID())) ? true : false;
			bool in_remote_ctrl = (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == remote_ctrl_->IsHaveRemoteControlRight(_share_render->GetUserID())) ? true : false;
			if (!can_remote_ctrl)
				return;

			int ret = MessageBox(NULL, in_remote_ctrl ? _T("give up remote control") : _T("request remote control"), _T("Remote control"), MB_YESNO);
			if (IDYES == ret)
			{
				if (in_remote_ctrl)
				{
					remote_ctrl_->GiveupRemoteControl(_share_render->GetUserID());
				}
				else
				{
					remote_ctrl_->RequestRemoteControl(_share_render->GetUserID());
				}
			}
		}
		else if (WM_LBUTTONDOWN == uMsg)
		{
			bool can_remote_ctrl = (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == remote_ctrl_->CanRequestControl(_share_render->GetUserID())) ? true : false;
			if (can_remote_ctrl)
			{
				remote_ctrl_->EnterRemoteControllingStatus(_share_render->GetUserID());
			}
		}
	}
	
}

CustomizeInMeetingUI::CustomizeInMeetingUI()
{
	Reset();
}

void CustomizeInMeetingUI::Reset()
{
	_default_video_size.x= 1600;
	_default_video_size.y = 540;

	_default_video_share_size.x = 1600;
	_default_video_share_size.y = 810;
	_in_view_sharing = false;

	_video_container = NULL;
	_active_elem = NULL;
	_preview_elem = NULL;
	
	ZeroMemory(_normal_elem, sizeof(_normal_elem)/sizeof(_normal_elem[0]));
	_share_render = NULL;
	_meeting_service = NULL;
	_total_page = 0;
	_current_page = 0;
	_in_meeting = false;
	_is_valid = false;
	_anno_obj = NULL;
	_sending_sharing_anno_obj = NULL;
}

void CustomizeInMeetingUI::Uninit()
{
	Stop();
}

void CustomizeInMeetingUI::Start()
{
	do 
	{
		if (_is_valid)
			break;

		CustomizedUIMgrWrap::GetInst().Init();
		ZOOM_SDK_NAMESPACE::ICustomizedUIMgr*  ui_mgr_ = CustomizedUIMgrWrap::GetInst().GetSDKObj();
		if (NULL == ui_mgr_ || ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != ui_mgr_->HasLicense())
			break;

		create_owner_hwnd(this, _default_video_size.x, _default_video_size.y);
		if (NULL == m_hOwnerHwnd || !::IsWindow(m_hOwnerHwnd))
			break;

		RECT rc;
		::GetClientRect(m_hOwnerHwnd, &rc);
		ui_mgr_->CreateVideoContainer(&_video_container, m_hOwnerHwnd, rc);
		if (NULL == _video_container)
			break;

		_video_container->SetEvent(this);
		_video_container->Show();
		CustomizedUIMgrWrap::GetInst().MapUIVideoContainer2SDKObj(this, _video_container);
		

		ui_mgr_->CreateShareRender(&_share_render, m_hOwnerHwnd, rc);
		if (NULL == _share_render)
			break;
		_share_render->SetEvent(this);
		CustomizedUIMgrWrap::GetInst().MapUIShareRender2SDKObj(this, _share_render);

		_is_valid = true;
	} while (false);
	if (!_is_valid)
	{
		ZOOM_SDK_NAMESPACE::ICustomizedUIMgr*  ui_mgr_ = CustomizedUIMgrWrap::GetInst().GetSDKObj();
		if (ui_mgr_)
		{
			if (_video_container)
			{
				ui_mgr_->DestroyVideoContainer(_video_container);
				_video_container = NULL;
			}

			if (_share_render)
			{
				ui_mgr_->DestroyShareRender(_share_render);
				_share_render = NULL;
			}
		}
	}
}

void CustomizeInMeetingUI::Stop()
{
	if (_is_valid && CustomizedUIMgrWrap::GetInst().GetSDKObj())
	{
		
		ZOOM_SDK_NAMESPACE::ICustomizedAnnotationController* 
			anno_ctrl_ = _meeting_service->GetAnnotationController()->GetCustomizedAnnotationController();
		if (anno_ctrl_)
		{
			if (_anno_obj)
			{
				_anno_obj->SetEvent(NULL);
				anno_ctrl_->DestroyAnnoObj(_anno_obj);
				_anno_obj = NULL;
			}
			if (_sending_sharing_anno_obj)
			{
				_sending_sharing_anno_obj->SetEvent(NULL);
				anno_ctrl_->DestroyAnnoObj(_sending_sharing_anno_obj);
				_sending_sharing_anno_obj = NULL;
			}
		}

		CustomizedUIMgrWrap::GetInst().GetSDKObj()->DestroyAllVideoContainer();
		CustomizedUIMgrWrap::GetInst().GetSDKObj()->DestroyAllShareRender();
		Reset();
		destroy_owner_wnd();
		CustomizedUIMgrWrap::GetInst().Uninit();
	}
}

void CustomizeInMeetingUI::ShowPreview()
{
	if (_is_valid && NULL == _preview_elem)
	{
		RECT rc;
		::GetClientRect(m_hOwnerHwnd, &rc);
		ZOOM_SDK_NAMESPACE::IVideoRenderElement* elem_ = NULL;
		_video_container->CreateVideoElement(&elem_, ZOOM_SDK_NAMESPACE::VideoRenderElement_PRVIEW);
		_preview_elem = dynamic_cast<ZOOM_SDK_NAMESPACE::IPreviewVideoRenderElement*>(elem_);
		if (_preview_elem)
		{
			_preview_elem->SetPos(rc);
			_preview_elem->Start();
		}
	}
}

void CustomizeInMeetingUI::StopPreview()
{
	if (_is_valid && _preview_elem)
	{
		_preview_elem->Stop();
		if (_video_container)
			_video_container->DestroyVideoElement(_preview_elem);
	}
}

void CustomizeInMeetingUI::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult /*= 0*/)
{
	switch (status)
	{
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_CONNECTING:
	//case ZOOM_SDK_NAMESPACE::MEETING_STATUS_RECONNECTING:
		{
			if (!_is_valid)
				Start();

			ShowPreview();
		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_DISCONNECTING:
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_ENDED:
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_FAILED:
		{
			if (_is_valid)
				Stop();
		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_INMEETING:
		{
			StopPreview();
			if(_meeting_service->GetMeetingConfiguration())
			{
				_meeting_service->GetMeetingConfiguration()->HideMeetingInfoFromMeetingUITitle(false);
			}
			HandleInMeeting();
		}
	default:
		break;
	}
}

void CustomizeInMeetingUI::SetSDKMeetingService(ZOOM_SDK_NAMESPACE::IMeetingService* meeting_service_)
{
	_meeting_service = meeting_service_;

	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationControllerEvent* anno_ctrl_cb = NULL;
	if (meeting_service_)
	{
		anno_ctrl_cb = this;
	}
	if (_meeting_service->GetAnnotationController()
		&& _meeting_service->GetAnnotationController()->GetCustomizedAnnotationController())
		_meeting_service->GetAnnotationController()->GetCustomizedAnnotationController()->SetEvent(anno_ctrl_cb);

}

void CustomizeInMeetingUI::CalcTotalPage()
{
	if (_meeting_service && _meeting_service->GetMeetingParticipantsController())
	{
		ZOOM_SDK_NAMESPACE::IList<unsigned int>* lst_user_ = _meeting_service->GetMeetingParticipantsController()->GetParticipantsList();
		if (lst_user_)
		{
			//calc page
			int user_count_ = lst_user_->GetCount();
			_total_page = user_count_/Normal_Video_Elem_Count;
			if (user_count_%Normal_Video_Elem_Count > 0)
				++_total_page ;
		}
	}
}
void CustomizeInMeetingUI::HandleInMeeting()
{
	_in_meeting = true;
	CalcTotalPage();
	_current_page = 0;
	if (NULL == _video_container)
		return;

	ZOOM_SDK_NAMESPACE::IVideoRenderElement* elem_ = NULL;
	_video_container->CreateVideoElement(&elem_, ZOOM_SDK_NAMESPACE::VideoRenderElement_ACTIVE);
	_active_elem = dynamic_cast<ZOOM_SDK_NAMESPACE::IActiveVideoRenderElement*>(elem_);
	if (_active_elem)
	{
		_active_elem->Start();
		_active_elem->Show();
	}

	for (int i = 0; i < Normal_Video_Elem_Count; i++)
	{
		elem_ = NULL;
		_video_container->CreateVideoElement(&elem_, ZOOM_SDK_NAMESPACE::VideoRenderElement_NORMAL);
		ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* normal_video_ = dynamic_cast<ZOOM_SDK_NAMESPACE::INormalVideoRenderElement*>(elem_);
		if (normal_video_)
		{
			_normal_elem[i] = normal_video_;
		}
	}
	AutoUpdateNormalElemUser(false);
	if (!_in_view_sharing 
		&&_share_render 
		&& _meeting_service
		&& _meeting_service->GetMeetingShareController())
	{
		ZOOM_SDK_NAMESPACE::IList<unsigned int >* lst_insharing_ = _meeting_service->GetMeetingShareController()->GetViewableShareSourceList();
		if (lst_insharing_ && lst_insharing_->GetCount() > 0)
		{
			_in_view_sharing = true;
			_share_render->SetUserID(lst_insharing_->GetItem(0));
			adjust_wnd_pos(_default_video_share_size.x, _default_video_share_size.y, m_hOwnerHwnd);
		}
	}

	DoLayout();
}

void CustomizeInMeetingUI::DoLayout()
{
	DoLayoutActiveVideo();
	DoLayoutNormalVideo();
}

void CustomizeInMeetingUI::DoLayoutActiveVideo()
{
	if (NULL == _active_elem)
		return;

	RECT rc;
	::GetClientRect(m_hOwnerHwnd, &rc);
	//1|3|1
	int width_ = rc.right - rc.left;
	int height_ = rc.bottom - rc.top;
	rc.left = width_/5;
	rc.right = rc.left + width_/5*3;
	rc.top = 0;
	rc.bottom = height_;
	if (_in_view_sharing)
	{
		//active video
		//------------
		//share
		rc.bottom = height_/3*2;
	}
	_active_elem->SetPos(rc);
}

void CustomizeInMeetingUI::DoLayoutNormalVideo()
{
	RECT rc;
	::GetClientRect(m_hOwnerHwnd, &rc);
	for (int i = 0; i < Normal_Video_Elem_Count; i++)
	{
		ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* elem_ = _normal_elem[i];
		if (elem_)
		{
			if (i < 3)//left
			{
				RECT normal_rc_ = rc;
				normal_rc_.left = 0;
				normal_rc_.right = (rc.right - rc.left)/5;
				normal_rc_.top = (rc.bottom - rc.top)/3 * i;
				normal_rc_.bottom = normal_rc_.top + (rc.bottom - rc.top)/3;
				elem_->SetPos(normal_rc_);
			}
			else //right
			{
				RECT normal_rc_ = rc;
				normal_rc_.left = (rc.right - rc.left)/5*4;
				normal_rc_.right = (rc.right - rc.left);
				normal_rc_.top = (rc.bottom - rc.top)/3 * (i - 3);
				normal_rc_.bottom = normal_rc_.top + (rc.bottom - rc.top)/3;
				elem_->SetPos(normal_rc_);
			}

			if (elem_->GetCurrentRenderUserId() > 0)
			{
				elem_->Show();
			}
			else
			{
				elem_->Hide();
			}
		}
	}
}

void CustomizeInMeetingUI::DoLayoutShareRender(RECT rc)
{
	if (_in_view_sharing)
	{
		{
			int width_ = rc.right - rc.left;
			int height_ = rc.bottom - rc.top;
			rc.left = width_/5;
			rc.right = rc.left + width_/5*3;
			rc.top = height_/3*2 + 10;
			rc.bottom = height_;
		}

		if (_share_render)
		{
			_share_render->Show();
			_share_render->Resize(rc);
		}
	}
}

void CustomizeInMeetingUI::onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId)
{
	if (_share_render && userId == _share_render->GetUserID())
	{
		switch (status)
		{
		case ZOOM_SDK_NAMESPACE::Remote_Control_I_Can_Control_Who_Begin:
			{
				MessageBox(NULL, _T("you can control!"), _T("zoom"), MB_OK);
			}
			break;
		case ZOOM_SDK_NAMESPACE::Remote_Control_I_Can_Control_Who_End:
			{
				MessageBox(NULL, _T("you can't control!"), _T("zoom"), MB_OK);
			}
			break;
		default:
			break;
		}
		
	}
}
void CustomizeInMeetingUI::onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId)
{
	switch (status)
	{
	case ZOOM_SDK_NAMESPACE::Sharing_Other_Share_Begin:
		{
			if (_in_view_sharing)
			{
				if (_share_render)
				{
					_share_render->SetUserID(userId);
				}
			}
			else
			{
				_in_view_sharing = true;
				_share_render->SetUserID(userId);
				adjust_wnd_pos(_default_video_share_size.x, _default_video_share_size.y, m_hOwnerHwnd);
			}
		}
		break;
	case ZOOM_SDK_NAMESPACE::Sharing_Other_Share_End:
		{
			if (_in_view_sharing
				&&_share_render 
				&& _meeting_service
				&& _meeting_service->GetMeetingShareController())
			{
				ZOOM_SDK_NAMESPACE::IList<unsigned int >* lst_insharing_ = _meeting_service->GetMeetingShareController()->GetViewableShareSourceList();
				if (lst_insharing_ && lst_insharing_->GetCount() > 0)
				{
					_share_render->SetUserID(lst_insharing_->GetItem(0));
				}
				else
				{
					_in_view_sharing = false;
					_share_render->SetUserID(0);
					_share_render->Hide();
					adjust_wnd_pos(_default_video_size.x, _default_video_size.y, m_hOwnerHwnd);
				}
			}
		}	
		break;
	case ZOOM_SDK_NAMESPACE::Sharing_Self_Send_Begin:
		{
		}
		break;
	case ZOOM_SDK_NAMESPACE::Sharing_Self_Send_End:
		{
		}
		break;
	default:
		break;
	}
}	

void CustomizeInMeetingUI::onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList /*= NULL*/)
{
	if (!_in_meeting || NULL == lstUserID)
		return;

	CalcTotalPage();
	AutoUpdateNormalElemUser(false);
	
}

void CustomizeInMeetingUI::onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList /*= NULL*/)
{
	CustomizeInMeetingUI::CalcTotalPage();
	AutoUpdateNormalElemUser(false);
}

void CustomizeInMeetingUI::AutoUpdateNormalElemUser(bool switch_to_next)
{
// 	if (_sending_sharing_anno_obj)
// 	{
// 		_sending_sharing_anno_obj->SetLineWidth(20);
// 		_sending_sharing_anno_obj->SetColor(RGB(255, 0, 0));
// 		_sending_sharing_anno_obj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_LINE);
// 	}
// 	return;

	if (0 == _total_page)
		return;
	
	if (switch_to_next)
	{
		int old_select_page = _current_page;
		_current_page++;
		_current_page = (_current_page > (_total_page - 1)) ? 0 : _current_page;
		if (old_select_page == _current_page)
			return;
	}
	
	int start_pos_ = _current_page*Normal_Video_Elem_Count;
	if (_meeting_service && _meeting_service->GetMeetingParticipantsController())
	{
		ZOOM_SDK_NAMESPACE::IList<unsigned int>* lst_user_ = _meeting_service->GetMeetingParticipantsController()->GetParticipantsList();
		if (lst_user_)
		{
			int count_ = lst_user_->GetCount();
			if (start_pos_ > count_ - 1)
			{
				return;
			}
			int elem_index_ = 0;
			for (int index_ = start_pos_; (index_ < count_ && elem_index_ < Normal_Video_Elem_Count); index_++, elem_index_++)
			{
				unsigned int user_id_ = lst_user_->GetItem(index_);
				if (0 == user_id_ || NULL == _normal_elem[elem_index_])
					continue;

				if (user_id_ != _normal_elem[elem_index_]->GetCurrentRenderUserId())
				{
					_normal_elem[elem_index_]->Subscribe(user_id_);
					_normal_elem[elem_index_]->Show();
				}
			}

			if (elem_index_ < (Normal_Video_Elem_Count-1))
			{
				for (;elem_index_ < Normal_Video_Elem_Count; elem_index_++)
				{
					if (NULL == _normal_elem[elem_index_])
						continue;
					if (0 != _normal_elem[elem_index_]->GetCurrentRenderUserId())
						_normal_elem[elem_index_]->Unsubscribe(_normal_elem[elem_index_]->GetCurrentRenderUserId());
					_normal_elem[elem_index_]->Hide();
				}
			}
		}
	}
}

void CustomizeInMeetingUI::AnnotationSnapshot()
{
	if (_anno_obj && ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == _anno_obj->CanSaveSnapshot())
	{
		_anno_obj->SaveSnapshot(L"d:\\");
	}

	if (_sending_sharing_anno_obj && ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == _sending_sharing_anno_obj->CanSaveSnapshot())
	{
		_sending_sharing_anno_obj->SaveSnapshot(L"d:\\");
	}
}
#endif