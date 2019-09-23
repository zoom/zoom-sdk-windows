#pragma once

#include "sdk_util.h"

class CInvitationWorkflow
{
public:
	CInvitationWorkflow();
	virtual ~CInvitationWorkflow();

public:
	void Init();
	const wchar_t* GetInviteEmailTeamplate();
	const wchar_t* GetInviteEmailTitle();
	const wchar_t* GetJoinMeetingUrl();

protected:
	ZOOM_SDK_NAMESPACE::IMeetingInfo* m_current_meeting;
};
