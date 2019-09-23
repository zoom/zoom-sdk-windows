#include "stdafx.h"
#include "chat_controller_workflow.h"



CSDKChatControllerWorkFlow::CSDKChatControllerWorkFlow()
{
	m_meeting_chat_event = NULL;
	bInited = false;
	m_meeting_chat_ctr = NULL;
	m_meeting_participants_ctr = NULL;
	InitController();
}

CSDKChatControllerWorkFlow::~CSDKChatControllerWorkFlow()
{
	m_meeting_chat_event = NULL;
	bInited = false;
	UnInit();
	m_meeting_chat_ctr = NULL;
	m_meeting_participants_ctr = NULL;
}

void CSDKChatControllerWorkFlow::onChatMsgNotifcation( ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc )
{
	if (m_meeting_chat_event)
	{
		m_meeting_chat_event->onChatMsgNotifcation(chatMsg,ccc);
	}
}

void CSDKChatControllerWorkFlow::onChatStautsChangedNotification( ZOOM_SDK_NAMESPACE::ChatStatus* status_ )
{
	if (m_meeting_chat_event)
	{
		m_meeting_chat_event->onChatStautsChangedNotification(status_);
	}
}

void CSDKChatControllerWorkFlow::SetEvent( IMeetingChatCtrlEventWrap* pSink )
{
	if (pSink)
	{
		m_meeting_chat_event = pSink;
	}
}

void CSDKChatControllerWorkFlow::UnInit()
{
	if(m_meeting_chat_ctr || m_meeting_participants_ctr)
	{		
		SDKInterfaceWrap::GetInst().UnListenChatServiceMgrEvent(this);
		m_meeting_chat_ctr = NULL;
		m_meeting_participants_ctr = NULL;
	}
}

bool CSDKChatControllerWorkFlow::InitController()
{
	if (!bInited)
	{
		if (m_meeting_chat_ctr == NULL)
		{
			m_meeting_chat_ctr = SDKInterfaceWrap::GetInst().GetMeetingChatController();
		}
		if (m_meeting_participants_ctr == NULL)
		{
			m_meeting_participants_ctr = SDKInterfaceWrap::GetInst().GetMeetingParticipantsController();
			
		}
		if (m_meeting_chat_ctr&&m_meeting_participants_ctr)
		{
			bInited = true;
			SDKInterfaceWrap::GetInst().ListenChatServiceMgrEvent(this);
			return true;
		}
	}

	return false;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKChatControllerWorkFlow::SendChatMsg( unsigned int receiver, wchar_t* content )
{
	if (m_meeting_chat_ctr)
	{
		ZOOM_SDK_NAMESPACE::SDKError err;
		err = m_meeting_chat_ctr->SendChatTo(receiver, content);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::IUserInfo* CSDKChatControllerWorkFlow::GetUserInfoByID( unsigned int userid )
{
	if (m_meeting_participants_ctr)
	{
		return m_meeting_participants_ctr->GetUserByUserID(userid);
	}
	return NULL;
}