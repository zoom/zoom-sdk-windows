#include "stdafx.h"

#include "invitation_workflow.h"

CInvitationWorkflow::CInvitationWorkflow()
{
	m_current_meeting = NULL;
	Init();
}

CInvitationWorkflow::~CInvitationWorkflow()
{
	m_current_meeting = NULL;
}

void CInvitationWorkflow::Init()
{
	ZOOM_SDK_NAMESPACE::IMeetingService* meeting_service = SDKInterfaceWrap::GetInst().GetMeetingService();
	if (meeting_service)
	{
		m_current_meeting = meeting_service->GetMeetingInfo();
	}
}

const wchar_t* CInvitationWorkflow::GetInviteEmailTeamplate()
{
	if (m_current_meeting)
	{
		return m_current_meeting->GetInviteEmailTeamplate();
	}
	return NULL;
}

const wchar_t* CInvitationWorkflow::GetInviteEmailTitle()
{
	if (m_current_meeting)
	{
		return m_current_meeting->GetInviteEmailTitle();
	}
	return NULL;
}

const wchar_t* CInvitationWorkflow::GetJoinMeetingUrl()
{
	if (m_current_meeting)
	{
		return m_current_meeting->GetJoinMeetingUrl();
	}
	return NULL;
}