#include "stdafx.h"

#include "close_caption_workflow.h"

CCloseCaptionWorkflow::CCloseCaptionWorkflow()
{
	m_close_caption_ctrl = NULL;
	m_close_caption_workflow_event = NULL;
	Init();
}

CCloseCaptionWorkflow::~CCloseCaptionWorkflow()
{
	m_close_caption_ctrl = NULL;
	SDKInterfaceWrap::GetInst().UnListenCloseCaptionEvent(this);
	m_close_caption_workflow_event = NULL;
}

bool CCloseCaptionWorkflow::CanIAssignOthersToSendCC()
{
	if (m_bSupportCC && m_close_caption_ctrl)
	{
		return m_close_caption_ctrl->CanAssignOthersToSendCC();
	}
	return false;
}

ZOOM_SDK_NAMESPACE::SDKError CCloseCaptionWorkflow::AssignCCPriviledge( unsigned int userid, bool bAssigned )
{
	if (m_bSupportCC && m_close_caption_ctrl)
	{
		return m_close_caption_ctrl->AssignCCPriviledge(userid, bAssigned);
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

bool CCloseCaptionWorkflow::CanBeAssignedToSendCC( unsigned int userid )
{
	if (m_bSupportCC && m_close_caption_ctrl)
	{
		return m_close_caption_ctrl->CanBeAssignedToSendCC(userid);
	}
	return false;
}

bool CCloseCaptionWorkflow::CanSendClosedCaption()
{
	if (m_bSupportCC && m_close_caption_ctrl)
	{
		return m_close_caption_ctrl->CanSendClosedCaption();
	}
	return false;
}

ZOOM_SDK_NAMESPACE::SDKError CCloseCaptionWorkflow::SendClosedCaption( const wchar_t* ccMsg )
{
	if (m_bSupportCC && m_close_caption_ctrl)
	{
		return m_close_caption_ctrl->SendClosedCaption(ccMsg);
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

void CCloseCaptionWorkflow::Init()
{
	if (NULL == m_close_caption_ctrl)
	{
		m_close_caption_ctrl = SDKInterfaceWrap::GetInst().GetCloseCaptionController();
	}
	
	if (m_close_caption_ctrl)
	{
		SDKInterfaceWrap::GetInst().ListenCloseCaptionEvent(this);
		m_bSupportCC = m_close_caption_ctrl->IsMeetingSupportCC();
	}
}

void CCloseCaptionWorkflow::onAssignedToSendCC( bool bAssigned )
{
	if (m_close_caption_workflow_event)
	{
		m_close_caption_workflow_event->onAssignedToSendCC(bAssigned);
	}
}

void CCloseCaptionWorkflow::onClosedCaptionMsgReceived( const wchar_t* ccMsg, time_t time )
{
	if (m_close_caption_workflow_event)
	{
		m_close_caption_workflow_event->onClosedCaptionMsgReceived(ccMsg, time);
	}
}

void CCloseCaptionWorkflow::SetEvent( IClosedCaptionWorkflowEvent* _event )
{
	m_close_caption_workflow_event = _event;
}

const wchar_t* CCloseCaptionWorkflow::GetClosedCaptionUrlFor3rdParty()
{
	if (m_bSupportCC && m_close_caption_ctrl)
	{
		const wchar_t* pUrl = m_close_caption_ctrl->GetClosedCaptionUrlFor3rdParty();
		return pUrl;
	}
	return NULL;
}

ZOOM_SDK_NAMESPACE::SDKError CCloseCaptionWorkflow::SaveCCHistory()
{
	if (m_bSupportCC && m_close_caption_ctrl)
	{
		if(m_close_caption_ctrl->IsSaveCCEnabled())
		{
			return m_close_caption_ctrl->SaveCCHistory();
		}
		return ZOOM_SDK_NAMESPACE::SDKERR_NO_PERMISSION;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_SERVICE_FAILED;
}

const wchar_t* CCloseCaptionWorkflow::GetClosedCaptionSavePath()
{
	if (m_bSupportCC && m_close_caption_ctrl)
	{
		return m_close_caption_ctrl->GetClosedCaptionHistorySavedPath();
	}
	return NULL;
}