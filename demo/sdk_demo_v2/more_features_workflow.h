#pragma once
#include "sdk_util.h"

// to add new feature according requirements.
class CSDKUserList;
class CMoreFeaturesWorkflow
{
public:
	CMoreFeaturesWorkflow();
	~CMoreFeaturesWorkflow();

public:
	bool MuteAll(CSDKUserList* _user_list);
	bool UnMuteAll(CSDKUserList* _user_list);

	ZOOM_SDK_NAMESPACE::SDKError PinVideo(bool bPin, bool bFirstView, unsigned int user_id);
	ZOOM_SDK_NAMESPACE::SDKError SpotlightVideo(bool bSpotlight, unsigned int userid);

	ZOOM_SDK_NAMESPACE::SDKError StopAttendeeVideo(unsigned int userid);
	ZOOM_SDK_NAMESPACE::SDKError StartAttendeeVideo(unsigned int userid);

	ZOOM_SDK_NAMESPACE::SDKError MuteAudio(unsigned int userid, bool allowUnmuteBySelf = true);
	ZOOM_SDK_NAMESPACE::SDKError UnMuteAudio(unsigned int userid);

	ZOOM_SDK_NAMESPACE::SDKError ExpelUser(unsigned int userid);
	ZOOM_SDK_NAMESPACE::SDKError MakeHost(unsigned int userid);
	ZOOM_SDK_NAMESPACE::SDKError ReclaimHost();
	ZOOM_SDK_NAMESPACE::SDKError AssignCoHost(unsigned int userid);
	ZOOM_SDK_NAMESPACE::SDKError RevokeCoHost(unsigned int userid);
	ZOOM_SDK_NAMESPACE::SDKError LowerAllHands();
	ZOOM_SDK_NAMESPACE::SDKError LowerHand(unsigned int userid);
	ZOOM_SDK_NAMESPACE::SDKError RaiseHand();
	ZOOM_SDK_NAMESPACE::SDKError ChangeUserName(const unsigned int userid, const wchar_t* userName, bool bSaveUserName);

	ZOOM_SDK_NAMESPACE::SDKError EnableMuteOnEntry(bool bEnable);


	
};