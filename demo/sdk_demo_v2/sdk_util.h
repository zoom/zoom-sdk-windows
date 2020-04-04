#pragma once

#include "zoom_sdk.h"
#include "zoom_sdk_ext.h"
#include "premeeting_service_interface.h"
#include "outlook_plugin_integration_helper_interface.h"
#include "calender_service_interface.h"
#include "direct_share_helper_interface.h"
#include "network_connection_handler_interface.h"
#include "auth_service_interface.h"
#include "zoom_sdk_sms_helper_interface.h"

#include "meeting_service_interface.h"
#include "meeting_service_components/meeting_annotation_interface.h"
#include "meeting_service_components/meeting_audio_interface.h"
#include "meeting_service_components/meeting_breakout_rooms_interface.h"
#include "meeting_service_components/meeting_chat_interface.h"
#include "meeting_service_components/meeting_configuration_interface.h"
#include "meeting_service_components/meeting_h323_helper_interface.h"
#include "meeting_service_components/meeting_participants_ctrl_interface.h"
#include "meeting_service_components/meeting_phone_helper_interface.h"
#include "meeting_service_components/meeting_recording_interface.h"
#include "meeting_service_components/meeting_remote_ctrl_interface.h"
#include "meeting_service_components/meeting_sharing_interface.h"
#include "meeting_service_components/meeting_ui_ctrl_interface.h"
#include "meeting_service_components/meeting_video_interface.h"
#include "meeting_service_components/meeting_waiting_room_interface.h"
#include "meeting_service_components/meeting_closedcaption_interface.h"
#include "customized_ui/customized_local_recording.h"
#include "setting_service_interface.h"
#include "customized_ui/customized_ui_mgr.h"
#include "customized_ui/customized_video_container.h"
#include "customized_ui/zoom_customized_ui.h"
#include "customized_ui/customized_share_render.h"
#include "customized_ui/customized_annotation.h"
#include "customized_ui/customized_local_recording.h"
#include <atlbase.h>
#include <set>
#include <WinUser.h>


#define ENABLE_CUSTOMIZED_UI_FLAG (1 << 5)

#define KEY_SECRET_LIMIT_LENGTH_MAX 63 

#define  Call_SINK_Pool(T_Name, EventSinkPool_Name, FUNC) \
{ \
	EventSinkPool_Name._event_sink_lock.Lock();\
	std::set<T_Name* > tmp_set;\
	tmp_set.insert(EventSinkPool_Name._event_sink_pool.begin(), EventSinkPool_Name._event_sink_pool.end());\
	std::set<T_Name* >::iterator iter_ = tmp_set.begin();\
	for (;tmp_set.end() != iter_; iter_++)\
	{\
		if (*iter_)\
			(*iter_)->FUNC;\
	}\
	EventSinkPool_Name._event_sink_lock.Unlock();\
}
template<class T>
class EventSinkPool
{
public:
	EventSinkPool()
	{

	}
	virtual ~EventSinkPool()
	{
		_event_sink_lock.Lock();
		_event_sink_pool.clear();
		_event_sink_lock.Unlock();
	}

	void AddListener(T* sink_)
	{
		if (sink_)
		{
			_event_sink_lock.Lock();
			_event_sink_pool.insert(sink_);
			_event_sink_lock.Unlock();
		}
	}

	void RemoveListener(T* sink_)
	{
		if (sink_)
		{
			_event_sink_lock.Lock();
			_event_sink_pool.erase(sink_);
			_event_sink_lock.Unlock();
		}
	}

public:
	CComAutoCriticalSection _event_sink_lock;
	std::set<T* > _event_sink_pool;
};

class ISDKInMeetingServiceMgrEvent
	:public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent,
	public ZOOM_SDK_NAMESPACE::IMeetingAudioCtrlEvent,
	public ZOOM_SDK_NAMESPACE::IMeetingChatCtrlEvent,
	public ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent,
	public ZOOM_SDK_NAMESPACE::IMeetingRecordingCtrlEvent,
	public ZOOM_SDK_NAMESPACE::IMeetingRemoteCtrlEvent,
	public ZOOM_SDK_NAMESPACE::IMeetingShareCtrlEvent,
	public ZOOM_SDK_NAMESPACE::IMeetingVideoCtrlEvent,
	public ZOOM_SDK_NAMESPACE::IMeetingUIControllerEvent,
	public ZOOM_SDK_NAMESPACE::ITestAudioDeviceHelperEvent,
	public ZOOM_SDK_NAMESPACE::ITestVideoDeviceHelperEvent,
	public ZOOM_SDK_NAMESPACE::IClosedCaptionControllerEvent,
	public ZOOM_SDK_NAMESPACE::ICustomizedAnnotationControllerEvent
{
public:
	//IMeetingServiceEvent
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0) = 0;
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type)  = 0;
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler) = 0;
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param) = 0;

	//IMeetingParticipantsCtrlEvent
	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;
	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;
	virtual void onHostChangeNotification(unsigned int userId) = 0;
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid) = 0;
	virtual void onUserNameChanged(unsigned int userId, const wchar_t* userName) = 0;
	virtual void onCoHostChangeNotification(unsigned int userId, bool isCoHost) = 0;

	//IMeetingRecordingCtrlEvent
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath) = 0;
	virtual void onRecording2MP4Processing(int iPercentage) = 0;
	virtual void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status) = 0;
	virtual void onRecordPriviligeChanged(bool bCanRec) = 0;
	virtual void onCloudRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status) = 0;
	virtual void onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper) = 0;

	//IMeetingVideoCtrlEvent
	virtual void onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status) = 0;
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid) = 0;
	virtual void onHostRequestStartVideo(ZOOM_SDK_NAMESPACE::IRequestStartVideoHandler* handler_) = 0;
	virtual void onActiveSpeakerVideoUserChanged(unsigned int userid) = 0;
	virtual void onActiveVideoUserChanged(unsigned int userid) = 0;

	//IMeetingAudioCtrlEvent
	virtual void onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL) = 0;
	virtual void onUserActiveAudioChange(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstActiveAudioUser) = 0;
	virtual void onHostRequestStartAudio(ZOOM_SDK_NAMESPACE::IRequestStartAudioHandler* handler_) = 0;

	//IMeetingChatCtrlEvent
	virtual void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc) = 0;
	virtual void onChatStautsChangedNotification(ZOOM_SDK_NAMESPACE::ChatStatus* status_) = 0;

	//IMeetingRemoteCtrlEvent
	virtual void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId) = 0;

	//IMeetingShareCtrlEvent
	virtual void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId) = 0;
	virtual void onLockShareStatus(bool bLocked) = 0;
	virtual void onShareContentNotification(ZOOM_SDK_NAMESPACE::ShareInfo& shareInfo) = 0;
	virtual void onMultiShareSwitchToSingleShareNeedConfirm(ZOOM_SDK_NAMESPACE::IShareSwitchMultiToSingleConfirmHandler* handler_) = 0;

	//IMeetingUIControllerEvent
	virtual void onInviteBtnClicked(bool& bHandled) = 0;
	virtual void onStartShareBtnClicked() = 0;
	virtual void onEndMeetingBtnClicked() = 0;
	virtual void onParticipantListBtnClicked() = 0;
	virtual void onCustomLiveStreamMenuClicked() = 0;
	virtual void onZoomInviteDialogFailed() = 0;
	virtual void onCCBTNClicked() = 0;
	virtual void onAudioBtnClicked(ZOOM_SDK_NAMESPACE::AudioBtnClickedCallbackInfo info) = 0;
	virtual void onAudioMenuBtnClicked() = 0;
	virtual void onBreakoutRoomBtnClicked() = 0;

	//ITestAudioDeviceHelperEvent
	virtual void OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume) = 0;
	virtual void OnNoAudioDeviceIsUseful(bool bMicOrSpk) = 0;
	virtual void OnTestMicStatusChanged(ZOOM_SDK_NAMESPACE::SDK_TESTMIC_STATUS status, bool& bHandled) = 0;
	virtual void OnSelectedAudioDeviceIsChanged() = 0;

	//ITestVideoDeviceHelperEvent
	virtual void OnNoVideoDeviceIsUseful() = 0;
	virtual void OnSelectedVideoDeviceIsChanged() = 0;
	virtual void OnNoWindowToShowPreview() = 0;

	//IClosedCaptionControllerEvent
	virtual void onAssignedToSendCC(bool bAssigned) = 0;
	virtual void onClosedCaptionMsgReceived(const wchar_t* ccMsg, time_t time) = 0;

	//ICustomizedAnnotationControllerEvent
	virtual void onCustomizedAnnotationObjDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* obj_) = 0;
	virtual void onSharingShareAnnotationStatusChanged(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_) = 0;
};

class SDKInterfaceWrap
	: public ZOOM_SDK_NAMESPACE::IAuthServiceEvent
	, public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent
	,public ZOOM_SDK_NAMESPACE::IPreMeetingServiceEvent
	,public ZOOM_SDK_NAMESPACE::IMeetingChatCtrlEvent
	,public ZOOM_SDK_NAMESPACE::IMeetingAudioCtrlEvent
	,public ZOOM_SDK_NAMESPACE::IMeetingVideoCtrlEvent
	,public ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent
	,public ZOOM_SDK_NAMESPACE::IClosedCaptionControllerEvent
	
{
public:
	static SDKInterfaceWrap& GetInst();
	bool IsSelectCustomizedUIMode() {return _customiezed_ui_mode;};
	ZOOM_SDK_NAMESPACE::SDKError  Init(ZOOM_SDK_NAMESPACE::InitParam& param_);
	ZOOM_SDK_NAMESPACE::SDKError  Cleanup();
	ZOOM_SDK_NAMESPACE::INetworkConnectionHelper* GetNetworkConnectionHelper();

	ZOOM_SDK_NAMESPACE::IAuthService* GetAuthService();
	void ListenAuthServiceEvent(ZOOM_SDK_NAMESPACE::IAuthServiceEvent* event_);// set event
	void UnListenAuthServiceEvent(ZOOM_SDK_NAMESPACE::IAuthServiceEvent* event_);//remove event
	ZOOM_SDK_NAMESPACE::IMeetingService* GetMeetingService();
	void ListenMeetingServiceEvent(ZOOM_SDK_NAMESPACE::IMeetingServiceEvent* event_);
	void UnListenMeetingServiceEvent(ZOOM_SDK_NAMESPACE::IMeetingServiceEvent* event_);

	ZOOM_SDK_NAMESPACE::ISettingService* GetSettingService();
	const ZOOM_SDK_NAMESPACE::IZoomLastError* GetLastError();

	ZOOM_SDK_NAMESPACE::IPreMeetingService* GetPreMeetingService();
	void ListenPremeetingServiceEvent(ZOOM_SDK_NAMESPACE::IPreMeetingServiceEvent* event_);
	void UnListenPremeetingServiceEvent(ZOOM_SDK_NAMESPACE::IPreMeetingServiceEvent* event_);

	void ListenChatServiceMgrEvent(ZOOM_SDK_NAMESPACE::IMeetingChatCtrlEvent* event_);
	void UnListenChatServiceMgrEvent(ZOOM_SDK_NAMESPACE::IMeetingChatCtrlEvent* event_);

	void ListenInMeetingServiceMgrEvent(ISDKInMeetingServiceMgrEvent* event_);
	void UnListenInMeetingServiceMgrEvent(ISDKInMeetingServiceMgrEvent* event_);
	void ListenCloseCaptionEvent(ZOOM_SDK_NAMESPACE::IClosedCaptionControllerEvent* event_);
	void UnListenCloseCaptionEvent(ZOOM_SDK_NAMESPACE::IClosedCaptionControllerEvent* event_);

	void ListenMeetingVideoCtrEvent(ZOOM_SDK_NAMESPACE::IMeetingVideoCtrlEvent* event_);
	void UnListenMeetingVideoCtrEvent(ZOOM_SDK_NAMESPACE::IMeetingVideoCtrlEvent* event_);

	void ListenMeetingParticipantsCtrEvent(ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent* event_);
	void UnListenMeetingParticipantsCtrEvent(ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent* event_);

	ZOOM_SDK_NAMESPACE::IMeetingChatController* GetMeetingChatController();
	ZOOM_SDK_NAMESPACE::IMeetingParticipantsController* GetMeetingParticipantsController();	
	ZOOM_SDK_NAMESPACE::IClosedCaptionController* GetCloseCaptionController();
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationController* SDKInterfaceWrap::GetCustomizedAnnotationController(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* pShareRender = NULL);
	ZOOM_SDK_NAMESPACE::IMeetingRemoteController* GetMeetingRemoteController();
	ZOOM_SDK_NAMESPACE::IMeetingVideoController* GetMeetingVideoController();
	//auth service
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IAuthServiceEvent, _auth_service_event_pool, onAuthenticationReturn(ret))
	}
	virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo)
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IAuthServiceEvent, _auth_service_event_pool, onLoginRet(ret, pAccountInfo))
	}
	virtual void onLogout()
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IAuthServiceEvent, _auth_service_event_pool, onLogout())
	}
	virtual void onZoomIdentityExpired()
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IAuthServiceEvent, _auth_service_event_pool, onZoomIdentityExpired())
	}
	virtual void onZoomAuthIdentityExpired()
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IAuthServiceEvent, _auth_service_event_pool, onZoomAuthIdentityExpired())
	}
	//meetings service
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onMeetingStatusChanged(status, iResult))
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IMeetingServiceEvent, _meeting_service_event_pool, onMeetingStatusChanged(status, iResult))
	}
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type)
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IMeetingServiceEvent, _meeting_service_event_pool, onMeetingStatisticsWarningNotification(type))
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onMeetingStatisticsWarningNotification(type))
	}
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler)
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IMeetingServiceEvent, _meeting_service_event_pool, onMeetingSecureKeyNotification(key, len, pHandler))
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onMeetingSecureKeyNotification(key, len, pHandler))	
	}
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param)
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IMeetingServiceEvent, _meeting_service_event_pool, onMeetingParameterNotification(meeting_param))
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onMeetingParameterNotification(meeting_param))	
	}

	//premeeting service
	virtual void onListMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, ZOOM_SDK_NAMESPACE::IList<UINT64 >* lstMeetingList)
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IPreMeetingServiceEvent, _premeeting_service_event_pool, onListMeeting(result, lstMeetingList))
	}
	virtual void onScheduleOrEditMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result, UINT64 meetingUniqueID)
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IPreMeetingServiceEvent, _premeeting_service_event_pool, onScheduleOrEditMeeting(result, meetingUniqueID))
	}
	virtual void onDeleteMeeting(ZOOM_SDK_NAMESPACE::PremeetingAPIResult result)
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IPreMeetingServiceEvent, _premeeting_service_event_pool, onDeleteMeeting(result))
	}

	//IMeetingAudioCtrlEvent
	virtual void onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onUserAudioStatusChange(lstAudioStatusChange, strAudioStatusList))	
	}
	virtual void onUserActiveAudioChange(ZOOM_SDK_NAMESPACE::IList<unsigned int >* plstActiveAudio)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onUserActiveAudioChange(plstActiveAudio))
	}
	virtual void onHostRequestStartAudio(ZOOM_SDK_NAMESPACE::IRequestStartAudioHandler* handler_)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onHostRequestStartAudio(handler_))
	}
	//IMeetingChatCtrlEvent,
	virtual void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* content = NULL)
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IMeetingChatCtrlEvent, _chat_servic_event_pool, onChatMsgNotifcation(chatMsg, content))
	}
	virtual void onChatStautsChangedNotification(ZOOM_SDK_NAMESPACE::ChatStatus* status_)
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IMeetingChatCtrlEvent, _chat_servic_event_pool, onChatStautsChangedNotification(status_))
	}

	//IMeetingParticipantsCtrlEvent
	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onUserJoin(lstUserID, strUserList))
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent, _meeting_participants_ctr_event_pool, onUserJoin(lstUserID, strUserList))
	}
	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onUserLeft(lstUserID, strUserList))
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent, _meeting_participants_ctr_event_pool, onUserLeft(lstUserID, strUserList))
	}
	virtual void onHostChangeNotification(unsigned int userId)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onHostChangeNotification(userId))
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent, _meeting_participants_ctr_event_pool, onHostChangeNotification(userId))
	}
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onLowOrRaiseHandStatusChanged(bLow, userid))
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent, _meeting_participants_ctr_event_pool, onLowOrRaiseHandStatusChanged(bLow, userid))
	}
	virtual void onUserNameChanged(unsigned int userId, const wchar_t* userName)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onUserNameChanged(userId, userName))
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent, _meeting_participants_ctr_event_pool, onUserNameChanged(userId, userName))
	}
	virtual void onCoHostChangeNotification(unsigned int userId, bool isCoHost)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onCoHostChangeNotification(userId, isCoHost))
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent, _meeting_participants_ctr_event_pool, onCoHostChangeNotification(userId, isCoHost))
	}

	//IMeetingRecordingCtrlEvent
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onRecording2MP4Done(bsuccess, iResult, szPath))
	}
	virtual void onRecording2MP4Processing(int iPercentage)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onRecording2MP4Processing(iPercentage))
	}
	virtual void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onRecordingStatus(status))
	}
	virtual void onCloudRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onCloudRecordingStatus(status))
	}
	virtual void onRecordPriviligeChanged(bool bCanRec)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onRecordPriviligeChanged(bCanRec))
	}
	virtual void onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onCustomizedLocalRecordingSourceNotification(layout_helper))
	}

	//IMeetingRemoteCtrlEvent
	virtual void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onRemoteControlStatus(status, userId))
	}

	//IMeetingShareCtrlEvent
	virtual void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onSharingStatus(status, userId))
	}
	virtual void onLockShareStatus(bool bLocked)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onLockShareStatus(bLocked))
	}
	virtual void onShareContentNotification(ZOOM_SDK_NAMESPACE::ShareInfo& shareInfo)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onShareContentNotification(shareInfo))
	}

	//IMeetingVideoCtrlEvent
	virtual void onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onUserVideoStatusChange(userId, status))
		Call_SINK_Pool(IMeetingVideoCtrlEvent, _meeting_video_ctrl_event_pool, onUserVideoStatusChange(userId, status))
	}
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onSpotlightVideoChangeNotification(bSpotlight, userid))
		Call_SINK_Pool(IMeetingVideoCtrlEvent, _meeting_video_ctrl_event_pool, onSpotlightVideoChangeNotification(bSpotlight, userid))
	}
	virtual void onHostRequestStartVideo(ZOOM_SDK_NAMESPACE::IRequestStartVideoHandler* handler_)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onHostRequestStartVideo(handler_))
		Call_SINK_Pool(IMeetingVideoCtrlEvent, _meeting_video_ctrl_event_pool, onHostRequestStartVideo(handler_))
	}
	virtual void onActiveSpeakerVideoUserChanged(unsigned int userid)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onActiveSpeakerVideoUserChanged(userid))
		Call_SINK_Pool(IMeetingVideoCtrlEvent, _meeting_video_ctrl_event_pool, onActiveSpeakerVideoUserChanged(userid))
	}
	virtual void onActiveVideoUserChanged(unsigned int userid)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onActiveVideoUserChanged(userid))
		Call_SINK_Pool(IMeetingVideoCtrlEvent, _meeting_video_ctrl_event_pool, onActiveVideoUserChanged(userid))
	}

	//IMeetingUIControllerEvent
	virtual void onInviteBtnClicked(bool& bHandled)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onInviteBtnClicked(bHandled))
	}
	virtual void onStartShareBtnClicked()
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onStartShareBtnClicked())
	}
	virtual void onEndMeetingBtnClicked()
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onEndMeetingBtnClicked())
	}
	virtual void onParticipantListBtnClicked()
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onParticipantListBtnClicked())
	}
	virtual void onCustomLiveStreamMenuClicked()
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onCustomLiveStreamMenuClicked())
	}
	virtual void onZoomInviteDialogFailed()
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onZoomInviteDialogFailed())
	}
	virtual void onCCBTNClicked()
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onCCBTNClicked())
	}

	virtual void onAudioBtnClicked(ZOOM_SDK_NAMESPACE::AudioBtnClickedCallbackInfo info)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onAudioBtnClicked(info))
	}

	virtual void onAudioMenuBtnClicked()
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, onAudioMenuBtnClicked())
	}

	//ITestAudioDeviceHelperEvent
	virtual void OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, OnMicSpkVolumnChanged(MicVolume, SpkVolume))
	}
	virtual void OnNoAudioDeviceIsUseful(bool bMicOrSpk)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, OnNoAudioDeviceIsUseful(bMicOrSpk))
	}
	virtual void OnTestMicStatusChanged(ZOOM_SDK_NAMESPACE::SDK_TESTMIC_STATUS status,bool& bHandled)
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, OnTestMicStatusChanged(status, bHandled))
	}
	virtual void OnSelectedAudioDeviceIsChanged()
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, OnSelectedAudioDeviceIsChanged())
	}
	
	//ITestVideoDeviceHelperEvent
	virtual void OnNoVideoDeviceIsUseful()
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, OnNoVideoDeviceIsUseful())
	}
	virtual void OnSelectedVideoDeviceIsChanged()
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, OnSelectedVideoDeviceIsChanged())
	}
	virtual void OnNoWindowToShowPreview()
	{
		Call_SINK_Pool(ISDKInMeetingServiceMgrEvent, _sdk_inmeeting_service_mgr_event_pool, OnNoWindowToShowPreview())
	}

	//ICloseCaptionControllerEvent
	virtual void onAssignedToSendCC(bool bAssigned)
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IClosedCaptionControllerEvent, _close_caption_event_pool, onAssignedToSendCC(bAssigned))
	}
	virtual void onClosedCaptionMsgReceived(const wchar_t* ccMsg, time_t time)
	{
		Call_SINK_Pool(ZOOM_SDK_NAMESPACE::IClosedCaptionControllerEvent, _close_caption_event_pool, onClosedCaptionMsgReceived(ccMsg, time))
	}

private: 
	SDKInterfaceWrap();
	virtual ~SDKInterfaceWrap();
	EventSinkPool<ZOOM_SDK_NAMESPACE::IAuthServiceEvent > _auth_service_event_pool;
	EventSinkPool<ZOOM_SDK_NAMESPACE::IMeetingServiceEvent > _meeting_service_event_pool;
	EventSinkPool<ZOOM_SDK_NAMESPACE::IPreMeetingServiceEvent > _premeeting_service_event_pool;
	EventSinkPool<ISDKInMeetingServiceMgrEvent > _sdk_inmeeting_service_mgr_event_pool;
	EventSinkPool<ZOOM_SDK_NAMESPACE::IMeetingChatCtrlEvent> _chat_servic_event_pool;
	EventSinkPool<ZOOM_SDK_NAMESPACE::IClosedCaptionControllerEvent> _close_caption_event_pool;
	EventSinkPool<ZOOM_SDK_NAMESPACE::IMeetingVideoCtrlEvent> _meeting_video_ctrl_event_pool;
	EventSinkPool<ZOOM_SDK_NAMESPACE::IMeetingParticipantsCtrlEvent> _meeting_participants_ctr_event_pool;

	ZOOM_SDK_NAMESPACE::IAuthService* _auth_service;
	ZOOM_SDK_NAMESPACE::IMeetingService* _meeting_service;
	ZOOM_SDK_NAMESPACE::INetworkConnectionHelper* _network_connection_helper;
	ZOOM_SDK_NAMESPACE::ISettingService* _setting_service;
	ZOOM_SDK_NAMESPACE::IPreMeetingService* _premeeting_service;
	
	const ZOOM_SDK_NAMESPACE::IZoomLastError* _last_error;
	
	bool _inited;
	ZOOM_SDK_NAMESPACE::IMeetingChatController* _meeting_chat_ctrl;
	ZOOM_SDK_NAMESPACE::IMeetingParticipantsController* _meeting_participants_ctrl;
	ZOOM_SDK_NAMESPACE::IClosedCaptionController* _close_caption_ctrl;
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationController* _customer_annotation_ctrl;
	bool _customiezed_ui_mode;
	ZOOM_SDK_NAMESPACE::IMeetingVideoController* _meeting_video_ctrl;
};

void ActiveWindowToTop(HWND hWnd, BOOL bGrabFocusByForce = FALSE);
bool SetDataToClipboard( const wchar_t* data_str, HWND _hwnd );