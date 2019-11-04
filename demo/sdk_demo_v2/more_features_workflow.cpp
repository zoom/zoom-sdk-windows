#include "stdafx.h"
#include "more_features_workflow.h"
#include "user_manager.h"



CMoreFeaturesWorkflow::CMoreFeaturesWorkflow()
{

}

CMoreFeaturesWorkflow::~CMoreFeaturesWorkflow()
{

}

bool CMoreFeaturesWorkflow::MuteAll(CSDKUserList* _user_list)
{
	//bool bMute(true);
	//if (_user_list)
	//{
	//	int nCount = _user_list->GetCount();
	//	for (int i = 0; i< nCount; i++)
	//	{
	//		ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = _user_list->GetItem(i);
	//		if (NULL == pUserInfo)
	//		{
	//			continue;
	//		}
	//		unsigned int user_id = pUserInfo->GetUserID();
	//		ZOOM_SDK_NAMESPACE::SDKError err = SDKInterfaceWrap::GetInst().GetMeetingService()->GetMeetingAudioController()->MuteAudio(user_id);
	//		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != err)
	//		{
	//			bMute = false;
	//		}
	//	}
	//}
	//return bMute;

	//easy way to do
	ZOOM_SDK_NAMESPACE::SDKError err = SDKInterfaceWrap::GetInst().GetMeetingService()->GetMeetingAudioController()->MuteAudio(0);
	if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
	{
		return true;
	}
	else
	{
		return false;
	}
	//easy way to do
	//SDKInterfaceWrap.GetInst().GetMeetingService()->GetMeetingAudioController()->MuteAudio(0);
}

bool CMoreFeaturesWorkflow::UnMuteAll(CSDKUserList* _user_list)
{
	//bool bMute(true);
	//if (_user_list)
	//{
	//	int nCount = _user_list->GetCount();
	//	for (int i = 0; i< nCount; i++)
	//	{
	//		ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = _user_list->GetItem(i);
	//		if (NULL == pUserInfo)
	//		{
	//			continue;
	//		}
	//		unsigned int user_id = pUserInfo->GetUserID();
	//		ZOOM_SDK_NAMESPACE::SDKError err = SDKInterfaceWrap::GetInst().GetMeetingService()->GetMeetingAudioController()->UnMuteAudio(user_id);
	//		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != err)
	//		{
	//			bMute = false;
	//		}
	//	}
	//}
	//return bMute;

	//easy way to do
	ZOOM_SDK_NAMESPACE::SDKError err = SDKInterfaceWrap::GetInst().GetMeetingService()->GetMeetingAudioController()->UnMuteAudio(0);
	if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
	{
		return true;
	}
	else
	{
		return false;
	}

	//easy way to do
	//SDKInterfaceWrap.GetInst().GetMeetingService()->GetMeetingAudioController()->UnMuteAudio(0);
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::PinVideo( bool bPin, bool bFirstView, unsigned int user_id )
{
	return SDKInterfaceWrap::GetInst().GetMeetingVideoController()->PinVideo(bPin, bFirstView, user_id);
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::SpotlightVideo( bool bSpotlight, unsigned int userid )
{
	return SDKInterfaceWrap::GetInst().GetMeetingVideoController()->SpotlightVideo(bSpotlight, userid);
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::StopAttendeeVideo( unsigned int userid )
{
	ZOOM_SDK_NAMESPACE::SDKError err = SDKInterfaceWrap::GetInst().GetMeetingVideoController()->CanStopAttendeeVideo(userid);
	if (err == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
	{
		return SDKInterfaceWrap::GetInst().GetMeetingVideoController()->StopAttendeeVideo(userid);
	}
	else
	{
		return err;
	}
	
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::StartAttendeeVideo( unsigned int userid )
{
	ZOOM_SDK_NAMESPACE::SDKError err = SDKInterfaceWrap::GetInst().GetMeetingVideoController()->CanAskAttendeeToStartVideo(userid);
	if (err == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
	{
		return SDKInterfaceWrap::GetInst().GetMeetingVideoController()->AskAttendeeToStartVideo(userid);
	}
	else
	{
		return err;
	}
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::MuteAudio( unsigned int userid, bool allowUnmuteBySelf /*= true*/ )
{
	return SDKInterfaceWrap::GetInst().GetMeetingService()->GetMeetingAudioController()->MuteAudio(userid, allowUnmuteBySelf);
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::UnMuteAudio( unsigned int userid )
{
	return SDKInterfaceWrap::GetInst().GetMeetingService()->GetMeetingAudioController()->UnMuteAudio(userid);
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::ExpelUser( unsigned int userid )
{
	return SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->ExpelUser(userid);
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::MakeHost( unsigned int userid )
{
	return SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->MakeHost(userid);
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::ReclaimHost()
{
	bool bCanReclaimHost(false);
	ZOOM_SDK_NAMESPACE::SDKError err = SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->CanReclaimHost(bCanReclaimHost);
	if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err && bCanReclaimHost)
	{
		err = SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->ReclaimHost();
	}
	{
		err = ZOOM_SDK_NAMESPACE::SDKERR_SERVICE_FAILED;
	}
	return err;
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::AssignCoHost( unsigned int userid )
{
	ZOOM_SDK_NAMESPACE::SDKError err = SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->CanbeCohost(userid);
	if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
	{
		err = SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->AssignCoHost(userid);
	}
	return err;
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::RevokeCoHost( unsigned int userid )
{
	return SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->RevokeCoHost(userid);
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::EnableMuteOnEntry( bool bEnable )
{
	return SDKInterfaceWrap::GetInst().GetMeetingService()->GetMeetingAudioController()->EnableMuteOnEntry(bEnable);
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::LowerAllHands()
{
	return SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->LowerAllHands();
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::LowerHand( unsigned int userid )
{
	return SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->LowerHand(userid);
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::RaiseHand()
{
	return SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->RaiseHand();
}

ZOOM_SDK_NAMESPACE::SDKError CMoreFeaturesWorkflow::ChangeUserName( const unsigned int userid, const wchar_t* userName, bool bSaveUserName )
{
	return SDKInterfaceWrap::GetInst().GetMeetingParticipantsController()->ChangeUserName(userid, userName, bSaveUserName);
}