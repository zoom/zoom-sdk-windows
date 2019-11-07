/*!
* \file premeeting_service_interface.h
* \brief PreMeeting Service Interface.
* 
*/
#ifndef _PREMEETING_SERVICE_INTERFACE_H_
#define _PREMEETING_SERVICE_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum PremeetingAPIResult
    \brief The result of premeeting API request.
    Here are more detailed structural descriptions.
*/
enum PremeetingAPIResult
{
	PREMETAPIRET_UNKNOW,///<API returns unknown error.
	PREMETAPIRET_SUCCESS,///<Calls API successfully.
};

/// \brief The interface to query the basic information of meeting.
class IQueryMeetingItemDateInfoHelper
{
public:
	/// \brief Get the start time of the specified meeting.
	/// \return The start time of the specified meeting.
	virtual time_t      GetCurrentStartTime() = 0; 
	
	/// \brief Get the duration of the specified meeting.
	/// \return The duration of the specified meeting in minutes.
	virtual int			GetDurationInMinutes() = 0;
	
	/// \brief Determine if the recurring meeting mode is selected.
	/// \return TRUE indicates that it is a recurring meeting. False not.
	virtual bool		IsRecurringMeetingSelected() = 0;
	virtual ~IQueryMeetingItemDateInfoHelper(){}
};
/// \brief The interface to set the meeting basic information.
class ISelectMeetingItemDateHelper
{
public:
	/// \brief Set the start time of the specified meeting. It is recommended to use the time zone of the operating system.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError    SelectStartTime(time_t time) = 0;
	
	/// \brief Set the duration of the specified meeting in minutes.
	/// \param duration The meeting duration in minutes.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError    SetDurationInMinutes(int duration) = 0;

	/// \brief Set the meeting type to recurring or scheduled.
	/// \param select_ TRYE indicates the meeting type is recurring.  FALSE schedule meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SelectRecurringMeeting(bool select_) = 0;
	virtual ~ISelectMeetingItemDateHelper(){}
};

/// \brief The callback interface that the selected meeting status changes.
class ISelectMeetingItemDateHelperEvent
{
public:
	/// \brief The callback event that the selected meeting status changes.
	/// \param can_use TRUE indicates to be available.
	/// \param date_select_helper An object pointer to ISelectMeetingItemDateHelper. For more details, see \link ISelectMeetingItemDateHelper \endlink.
	virtual void onSupportSelectDateStatusNotification(bool can_use, ISelectMeetingItemDateHelper* date_select_helper) = 0;
};

/*! \enum SCHEDULEAUDIOTYPE
    \brief Specify the meeting audio type.
    Here are more detailed structural descriptions.
*/
enum SCHEDULEAUDIOTYPE
{
	SCHEDULEAUDIOTYPE_none = 0,///<For initialization.
	SCHEDULEAUDIOTYPE_telephony = (1<<1),///<Support telephony.
	SCHEDULEAUDIOTYPE_voip = (1<<2),///<Support VoiP.
	SCHEDULEAUDIOTYPE_both = (1<<3),///<Support both telephony and VoiP.
	SCHEDULEAUDIOTYPE_3rd = (1<<4),///<Support the third audio device.
};
/// \brief The interface to query the meeting telephony number information.
class IQueryMeetingItemTelAudioInfoHelper
{
public:
	virtual ~IQueryMeetingItemTelAudioInfoHelper(){}
	/// \brief Get the available telephony number list for countries that can be called in.
	/// \return If the function succeeds, the return value is the telephony number list for countries that can be called in.
	virtual IList<const wchar_t* >* GetAvailableDialinCountryCode() = 0;
	
	/// \brief Get the telephony number list of the selected country that can be called in.
	/// \return If the function succeeds, the return value is the telephony number of the selected country.
	virtual IList<const wchar_t* >* GetSelectedDialinCountryCode() = 0;
	
	/// \brief Determine if the numbers of visible dialable country contains toll-free numbers.
	/// \return TRUE indicates to contain.
	virtual bool IsIncludeTollFree() = 0;
};

/// \brief The interface to set the meeting telephony numbers information.
class ISelectMeetingItemTelAudioHelper
{
public:
	virtual ~ISelectMeetingItemTelAudioHelper(){}
	/// \brief Select the telephone number via specified country ID as the default call-in number.
	/// \param countryId The ID of the specified country.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SelectDefaultDialInCountry(const wchar_t* countryId) =0;
	
	/// \brief Remove the telephone number in the default call-in number via specified country ID.
	/// \param countryId The ID of the specified country.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RemoveDefaultDialInCountry(const wchar_t* countryId) =0;

	/// \brief Set if the toll-free numbers are enabled in the call-in number list.
	/// \param bEnable TRUE indicates to enable.	
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableIncludeTollFree(bool bEnable) = 0;
};
/// \brief The callback interface that the selected meeting audio function changes.
class ISelectMeetingItemAudioOptionHelperEvent
{
public:
	/// \brief The callback event that the selected meeting audio function changes.
	/// \param can_use TRUE indicates that the dial-in in the currently selected meeting is available.
	virtual void onSupportTelAudioNotification(bool can_use) = 0;
};

/// \brief The interface to query the meeting audio information.
class IQueryMeetingItemAudioOptionHelper
{
public:
	virtual ~IQueryMeetingItemAudioOptionHelper(){}
	/// \brief Get the meeting audio type.
	/// \param [out] type_ The meeting audio type. For more details, see \link SCHEDULEAUDIOTYPE \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GetSelectedAudioType(SCHEDULEAUDIOTYPE& type_) = 0;
	
	/// \brief Get the meeting telephone number information.
	/// \return If the function succeeds, the return value is the pointer to the IQueryMeetingItemTelAudioInfoHelper. 
	///Otherwise failed, returns NULL.
	///For more details, see \link IQueryMeetingItemTelAudioInfoHelper \endlink.
	virtual IQueryMeetingItemTelAudioInfoHelper* GetQueryTelAudioInfoHelper() = 0;
};

/// \brief The interface to set the meeting audio information.
class ISelectMeetingItemAudioOptionHelper
{
public:
	virtual ~ISelectMeetingItemAudioOptionHelper(){}
	/// \brief Determine if the specified audio type is supported by the meeting.
	/// \param audio_type The specified audio type. For more details, see \link SCHEDULEAUDIOTYPE \endlink enum.
	/// \return If the specified audio type is supported, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.	
	virtual SDKError  IsSupportAudioType(SCHEDULEAUDIOTYPE audio_type) = 0;
	
	/// \brief Set the audio type of the specified meeting.
	/// \param audio_type The audio type. For more details, see \link SCHEDULEAUDIOTYPE \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError  SelectAudioType(SCHEDULEAUDIOTYPE audio_type) = 0;

	/// \brief Get the meeting telephone number information.
	/// \return If the function succeeds, the return value is the pointer to the ISelectMeetingItemTelAudioHelper.
	///Otherwise failed, returns NULL.
	///For more details, see \link ISelectMeetingItemTelAudioHelper \endlink.
	virtual ISelectMeetingItemTelAudioHelper* GetScheduleTelAudioHelper() = 0;
};

/// \brief The interface to query meeting video information.
class IQueryMeetingItemVideoOptionHelper
{
public:
	virtual ~IQueryMeetingItemVideoOptionHelper(){}
	/// \brief Determine if the host enables the video when joins the meeting.
	/// \return TRUE indicates that the video of host is enabled.
	virtual bool IsHostVideoOnOrOff() = 0;
	
	/// \brief Determine if the video of the participant is enabled when joining meeting.
	/// \return TRUE indicates that the video of the participant is enabled.
	virtual bool IsAttendeeVideoOnOrOff() = 0;
};

/// \brief The interface to set the meeting video information.
class ISelectMeetingItemVideoOptionHelper
{
public:
	virtual ~ISelectMeetingItemVideoOptionHelper() {};
	/// \brief Enable or disable the host video function.
	/// \param bOn TRUE indicates to enable the host video.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SelectHostVideoOnOrOff(bool bOn) = 0;
	
	/// \brief Set to enable or disable the video of the participants.
	/// \param bOn TRUE indicates to enable the video.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SelectAttendeeVideoOnOrOff(bool bOn) = 0;
};
/*! \enum SCHEDULERECTYPE
    \brief Specify the meeting recording type.
    Here are more detailed structural descriptions.
*/
enum SCHEDULERECTYPE
{
	SCHEDULERecordType_none = 0,///<For initialization.
	SCHEDULERecordType_Cloud = 1,///<Cloud recording.
	SCHEDULERecordType_Local = (1<<1),///<Local recording.
};
	
/// \brief The callback interface to configure the meeting basic information.
class ISelectMeetingItemMeetingOptionHelperEvent
{
public:
	virtual ~ISelectMeetingItemMeetingOptionHelperEvent() {}
	/// \brief The callback event to request to fill in the password when the participants join the meeting.
	/// \param enable TRUE indicates to fill in the password.
	/// \param default_psw  The meeting original password. This password is only valid when the ENABLE value is TRUE.
	virtual void onMeetingPasswordEnabledStatusNotification(bool enable, const wchar_t* default_psw) = 0;
	
	/// \brief The callback event that the status JBH(Join meeting Before Host) changes.
	/// \param enable TRUE indicates to enable.
	virtual void onJoinBeforeHostEnabledStatusNotification(bool enable) = 0;
	/// \brief  The callback event that the status MUTE ALL THE PARTICIPANTS changes.
	/// \param enable TRUE indicates to mute the participants.
	virtual void onMuteUponEntryEnabledStatusNotification(bool enable) = 0;
	
	/// \brief The callback event that the status USE THE PERSONAL MEETING ID changes.
	/// \param enable TRUE indicates to use the personal meeting ID.
	virtual void onScheduleWithPmiEnabledStatusNotification(bool enable) = 0;
	
	/// \brief The callback event that the status ONLY THE SPECIFIED USERS ARE ALLOWED TO JOIN THE MEETING changes.
	/// \param enable TRUE indicates that only the specified users are allowed to join the meeting.
	/// \param default_specified_domain_can_join The users in the domain are specified. It is valid only when the ENABLE value is TRUE.
	virtual void onOnlySignedInUserCanJoinEnabledStatusNotification(bool enable, const wchar_t* default_specified_domain_can_join) = 0;
	
	/// \brief The callback event that the status HOSTING A MEETING IN CHINA changes.
	/// \param enable TRUE indicates to enable.
	virtual void onHostInChinaEnabledStatusNotification(bool enable) = 0;
	
	/// \brief The callback event that the status AUTO RECORDING IN THE MEETING changes.
	/// \param enable TRUE indicates to enable the auto recording.
	/// \param default_type The default meeting recording type. For more details, see \link SCHEDULERECTYPE \endlink enum.
	virtual void onAutoRecordEnabledStatusNotification(bool enable, SCHEDULERECTYPE& default_type) = 0;
	
	/// \brief The callback event that the status SPECIFY OTHERS AS THE HOST changes.
	/// \param can_use TRUE indicates to enable to specify others as the host.
	virtual void onSupportScheduleForNotification(bool can_use) = 0;
};
	
/// \brief The interface of the user who can be specified as the host.
class IScheduleForUser
{
public:
	virtual ~IScheduleForUser() {};
	/// \deprecated This interface is deprecated because of security reason. The return value will always be NULL now. Please stop using it. 
	/// \brief Get the user email.
	/// \return The user email.
	virtual const wchar_t* GetEmail() = 0;
	
	/// \brief Get the screen name of the user.
	/// \return The screen name of the user.
	virtual const wchar_t* GetDisplayName() = 0;
	
	/// \brief Get the user personal meeting ID.
	/// \return The user personal meeting ID.
	virtual UINT64 GetPMINumber() = 0;
};
	
/// \brief The interface to query the information of the user who is specified as the meeting host.
class IQueryMeetingItemScheduleForHelper
{
public:
	virtual ~IQueryMeetingItemScheduleForHelper() {}
	/// \brief Get the information of the user who is specified as the meeting host.
	/// \return A pointer to the IScheduleForUser. For more details, see \link IScheduleForUser \endlink.
	virtual IScheduleForUser* GetCurrentSelectedScheduleForUser() =0;
};
	
/// \brief The meeting information interface to specify others as the host.
class ISelectMeetingItemScheduleForHelper
{
public:
	virtual ~ISelectMeetingItemScheduleForHelper(){}
	/// \brief Get the user list who can be specified as the host.
	/// \param [out] can_select_schedule_for TRUE indicates that the current meeting can specify other user as the host.
	/// \return If the function succeeds, the return value is the meeting list to specify others as the host. It is only valid when the can_select_schedule_for is true. Otherwise failed, returns NULL.
	virtual IList<IScheduleForUser* >* GetAvailableScheduleForList(bool& can_select_schedule_for) = 0;
	
	/// \brief Specify a new host for the meeting.
	/// \param alternateHost Specify a new host. For more details, see \link IScheduleForUser \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SelectScheduleForUser(IScheduleForUser* alternateHost) =0;
};
	
///\brief The interface to query the meeting basic configuration information.
class IQueryMeetingItemMeetingOptionHelper
{
public:
	virtual ~IQueryMeetingItemMeetingOptionHelper(){}
	/// \brief Get the topic of the specified meeting.
	/// \return The topic of the specified meeting.	
	virtual const wchar_t*	 GetMeetingTopic() = 0;
	
	/// \brief Determine if the password is required when join the meeting. 
	/// \param [out] can_change TRUE indicates that this feature can be changed.
	/// \return TRUE indicates that the password is required.
	virtual bool     IsMeetingPasswordEnabled(bool& can_change) = 0;
	
	/// \brief Get the password of the specified meeting.
	/// \return The password of the specified meeting.
	virtual const wchar_t* GetMeetingPassword() = 0;
	
	/// \brief Determine if it is enabled to join the meeting before the host.
	/// \param [out] can_change TRUE indicates that this feature can be changed.
	/// \return TRUE indicates it is enabled to join the meeting before the host.
	virtual bool     IsJoinBeforeHostEnabled(bool& can_change) = 0;
	
	/// \brief Determine if the meeting mutes all the participants.
	/// \param [out] can_change TRUE indicates that this feature can be changed.
	/// \return TRUE indicates to currently mute all the participants.
	virtual bool     IsMuteUponEntryEnabled(bool& can_change) = 0;
	
	/// \brief Determine if the personal meeting ID is used in the meeting.
	/// \param [out] can_change TRUE indicates that this feature can be changed.
	/// \return TRUE indicates to use the PMI.
	virtual bool     IsScheduleWithPmiEnabled(bool& can_change) = 0;
	
	/// \brief Determine if only the specified user is allowed to join the meeting.
	/// \param [out] can_change TRUE indicates that this feature can be changed.
	/// \return TRUE indicates to allow only the specified user to join the meeting.
	virtual bool     IsOnlySignedInUserCanJoinEnabled(bool& can_change) = 0;
	
	/// \brief Get the domain to join the meeting.
	/// \param [out] can_change TRUE indicates that this feature can be changed.
	/// \return The domain to join the meeting.
	virtual const wchar_t* GetSpecifiedDomainCanJoin(bool& can_change) = 0;
	
	/// \brief Determine if hosting the meeting in China is enabled.
	/// \param [out] can_change TRUE indicates that this feature can be changed.
	/// \return TRUE indicates that hosting the meeting in China is enabled.
	virtual bool     IsHostInChinaEnabled(bool& can_change) = 0;
	
	/// \brief Determine that if auto video recording is enabled in the meeting.
	/// \param [out] can_change TRUE indicates that the record type can be changed.
	/// \param [out] support_rec_type indicates the recording type supported by the meeting. For more details, see \link SCHEDULERECTYPE \endlink enum.
	/// \return TRUE indicates to enable auto video recording.
	virtual bool     IsAutoRecordEnabled(bool& can_change, int& support_rec_type) = 0;
	
	/// \brief Get the recording type supported by the meeting.
	/// \return The recording type supported by the meeting. For more details, see \link SCHEDULERECTYPE \endlink enum.
	virtual SCHEDULERECTYPE GetSelectedAutoRecordType() = 0;
	
	/// \brief Get the meeting information interface for the specified meeting. 
	/// \return A pointer to the IQueryMeetingItemScheduleForHelper. For more details, see \link IQueryMeetingItemScheduleForHelper \endlink.
	virtual IQueryMeetingItemScheduleForHelper* GetQueryScheduleForHelper() = 0;
};
	
///\brief The interface to configure the meeting basic information.
class ISelectMeetingItemMeetingOptionHelper
{
public:
	virtual ~ISelectMeetingItemMeetingOptionHelper() {};
	virtual SDKError SetMeetingTopic(const wchar_t* topic) = 0;
	/// \brief Set whether the password is required when joining the meeting.
	/// \param bEnable TRUE indicates that the password is required.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.	
	/// \remarks The ISelectMeetingItemMeetingOptionHelperEvent::onMeetingPasswordEnabledStatusNotification() will be triggered each time this function is called.
	virtual SDKError EnableMeetingPassword(bool bEnable) = 0;
	
	/// \brief Set the meeting password.
	/// \param meetingPsw Meeting password.
	virtual SDKError SetMeetingPassword(const wchar_t* meetingPsw) = 0;
	
	/// \brief Set if it is able to join the meeting before the host.
	/// \param bEnable TRUE indicates that participants are allowed to join the meeting before the host. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.	
	/// \remarks The ISelectMeetingItemMeetingOptionHelperEvent::onJoinBeforeHostEnabledStatusNotification() will be triggered each time this function is called.
	virtual SDKError EnableJoinBeforeHost(bool bEnable) = 0;
	
	/// \brief Set if it is able to mute attendees automatically when join the meeting.
	/// \param bEnable TRUE indicates that participants are muted when they join the meeting. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.	
	/// \remarks The ISelectMeetingItemMeetingOptionHelperEvent::onMuteUponEntryEnabledStatusNotification()	will be triggered each time this function is called.
	virtual SDKError EnableMuteUponEntry(bool bEnable) = 0;
	
	/// \brief Set if it is able to schedule meeting by PMI(Personal meeting ID).
	/// \param bEnable TRUE indicates to use the PMI as the meeting ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.	
	virtual SDKError EnableScheduleWithPmi(bool bEnable) = 0;
	
	/// \brief Set if only the specified user can join the meeting.
	/// \param bEnable TRUE indicates that only the specified user can join the meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum. 
	/// \remarks The ISelectMeetingItemMeetingOptionHelperEvent::onOnlySignedInUserCanJoinEnabledStatusNotification() will be triggered each time this function is called.
	virtual SDKError EnableOnlySignedInUserCanJoin(bool bEnable) = 0;
	
	/// \brief Set a specified domain.
	/// \param specified_domain_can_join Specify the domain.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum. 
	/// \remarks The users in the domain are specified.
	virtual SDKError SetSpecifiedDomainCanJoin(const wchar_t* specified_domain_can_join) = 0;
	
	/// \brief Set if it is able to host a meeting in China.
	/// \param bEnable TRUE indicates that it is enabled to host the meeting in China.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum. 
	virtual SDKError EnableHostInChina(bool bEnable) = 0;
	
	/// \brief Set if it is able to record the meeting automatically.
	/// \param bEnable TRUE indicates that the meeting will be recorded automatically. False not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.	
	/// \remarks The ISelectMeetingItemMeetingOptionHelperEvent::onAutoRecordEnabledStatusNotification() will be triggered each time this function is called.	
	virtual SDKError EnableAutoRecord(bool bEnable) = 0;
	
	/// \brief Set the meeting recording type.
	/// \param type_ Specify the recording type of meeting. For more details, see \link SCHEDULERECTYPE \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SelectAutoRecordType(SCHEDULERECTYPE type_) = 0;
	
	/// \brief Get the specified meeting information interface.
	/// \return A pointer to the ISelectMeetingItemScheduleForHelper. For more details, see \link ISelectMeetingItemScheduleForHelper \endlink.
	virtual ISelectMeetingItemScheduleForHelper* GetScheduleForHelper() = 0;
};

///\brief Meeting item information interface.
class IMeetingItemInfo 
	: public IQueryMeetingItemDateInfoHelper
	, public IQueryMeetingItemVideoOptionHelper
	, public IQueryMeetingItemAudioOptionHelper
	, public IQueryMeetingItemMeetingOptionHelper
{
public:
	/// \brief Get the exclusive meeting number.
	/// \return If the function succeeds, the return value is the non-zero meeting number.
	virtual UINT64 GetUniqueMeetingID() = 0;
	
	/// \brief Get the exclusive meeting number.
	/// \return If the function succeeds, the return value is the non-zero meeting number.	
	virtual UINT64 GetMeetingID() = 0;
	
	/// \brief Determine if the specified meeting is personal.
	/// \return TRUE indicates that it is a personal meeting. False no.
	virtual bool   IsPMI() = 0;
	
	/// \brief Determine if the specified meeting is a webinar.
	/// \return TRUE indicates that it is a webinar. False no.
	virtual bool   IsWebinar() = 0;
	
	/// \brief Get the content of the email to invite the users to join the meeting.
	/// \return If the function succeeds, the return value is the content of the email. Otherwise failed, returns NULL.
	virtual const wchar_t* GetInviteEmailContent() = 0;
	
	/// \brief Get the subject of the email to invite the users to join the meeting.
	/// \return If the function succeeds, the return value is the subject of the email. Otherwise failed, returns NULL.
	virtual const wchar_t* GetInviteEmailSubject() = 0;
	
	/// \brief Get the URL to invite the users to join the meeting.
	/// \return If the function succeeds, the return value is the URL of the email. Otherwise failed, returns NULL.
	virtual const wchar_t* GetJoinMeetingUrl() = 0;
};

///\brief The interface to query the meeting information.
class IMeetingItemInfoQueryHelper : public IMeetingItemInfo
{
public:
};

class IMeetingItemInfoSelectHelper
	: public ISelectMeetingItemDateHelper
	, public ISelectMeetingItemVideoOptionHelper
	, public ISelectMeetingItemAudioOptionHelper
	, public ISelectMeetingItemMeetingOptionHelper
{
public:
};

/// \brief The interface to configure the meeting information.
class IScheduleMeetingItemStatusCallback
	: public ISelectMeetingItemDateHelperEvent
	, public ISelectMeetingItemAudioOptionHelperEvent
	, public ISelectMeetingItemMeetingOptionHelperEvent
{
public:
	virtual void onScheduleMeetingItemDestroyed() = 0;
};

/// \brief Schedule meeting item interface.
///The APIs are used to schedule meeting and edit scheduled meeting.
///You can create/destroy the interface via CreateScheduleMeetingItem and DestoryScheduleMeetingItem in IPreMeetingService
class IScheduleMeetingItem
	: public IMeetingItemInfoSelectHelper
	, public IMeetingItemInfoQueryHelper
{
public:
	/// \brief Set the scheduled meeting service callback handler.
	/// \param callback A pointer to the IScheduleMeetingItemStatusCallback that receives the scheduled meeting service event.
	virtual SDKError SetEvent(IScheduleMeetingItemStatusCallback* callback) = 0;
};

/// \brief Pre-meeting service event interface.
class IPreMeetingServiceEvent
{
public:
	/// \brief List meeting callback event.
	/// \param result The result of calling IPreMeetingService::ListMeeting(). For more details, see \link PremeetingAPIResult \endlink enum.
	/// \param lstMeetingList A pointer to the list of meeting ID. 
	virtual void onListMeeting(PremeetingAPIResult result, IList<UINT64 >* lstMeetingList) = 0;	
	
	/// \brief Schedule or edit meeting callback event.
	/// \param result The result of calling IPreMeetingService::ScheduleMeeting(). For more details, see \link PremeetingAPIResult \endlink enum.
	/// \param meetingUniqueID The meeting ID to schedule or edit the meeting.
	virtual void onScheduleOrEditMeeting(PremeetingAPIResult result, UINT64 meetingUniqueID) = 0;

	/// \brief Delete meeting callback.
	/// \param result The result of calling IPreMeetingService::DeleteMeeting(). For more details, see \link PremeetingAPIResult \endlink enum.
	virtual void onDeleteMeeting(PremeetingAPIResult result) = 0;
};

/// \brief Pre-meeting service interface.
class IPreMeetingService
{
public:
	/// \brief Create an item to schedule meeting.
	/// \return If the function succeeds, the return value is the object pointer to IScheduleMeetingItem. Otherwise failed, returns NULL.
	virtual IScheduleMeetingItem* CreateScheduleMeetingItem() = 0;

	/// \brief Destroy the item of scheduling meeting created via CreateScheduleMeetingItem().
	/// \param pMeeting A pointer to the item created via CreateScheduleMeetingItem().
	virtual void DestoryScheduleMeetingItem(IScheduleMeetingItem* pMeeting) = 0;
	
	/// \param meetingUniqueID Specify the meeting ID.
	/// \return If the function succeeds, the return value is the object pointer to IScheduleMeetingItem. Otherwise failed, returns NULL.
	///Notice that if the specified meeting is a webinar, NULL will be returned. This infterface doesn't support a webinar or a recurring one.
	virtual IScheduleMeetingItem* CreateEditMeetingItem(UINT64 meetingUniqueID) = 0;
	
	/// \brief Destroy the item of editing meeting created via CreateEditMeetingItem().
	/// \param pMeeting A pointer to the item created via CreateEditMeetingItem().
	virtual void DestoryEditMeetingItem(IScheduleMeetingItem* pMeeting) = 0;	
	
	/// \brief Set pre-meeting service event.
	/// \param pEvent A pointer to the IPreMeetingServiceEvent which is used to receive pre-meeting service callback events. For more details, see \link IPreMeetingServiceEvent \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks The event is used by the SDK to pass the callback event to user's application. If the function is not called or failed, the user's application can not retrieve the callback event.
	virtual SDKError SetEvent(IPreMeetingServiceEvent* pEvent) = 0;

	/// \brief Schedule Meeting.
	/// \param pItem The object created via CreateScheduleMeetingItem().
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Once the function is called successfully, the user will receive the callback event via IPreMeetingServiceEventreMeetingSer::onScheduleOrEditMeeting().
	virtual SDKError ScheduleMeeting(IScheduleMeetingItem* pItem) = 0;		
	
	/// \brief Schedule Meeting.
	/// \param wndParam Schedule a meeting in the dialog window box by setting its parameter. For more details, see \link WndPosition \endlink structure.
	/// \return If the function succeeds, the return value is SDKErr_Success. 
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Once the function is called successfully, the user will receive the callback event via IPreMeetingServiceEventreMeetingSer::onScheduleOrEditMeeting().
	virtual SDKError ScheduleMeeting(WndPosition& wndParam) = 0;

	/// \brief Edit Meeting.
	/// \param pItem The object created via CreateEditMeetingItem.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Once the function is called successfully, the user will receive the callback event via IPreMeetingServiceEvent::onScheduleOrEditMeeting ().
	///Notice that if the specified meeting is a recurring one or a webinar, a SDKERR_INVALID_PARAMETER error will be returned. In these cases, edit the meeting via IPreMeetingService::EditMeeting(WndPosition& wndParam, UINT64 meetingUniqueID).
	virtual SDKError EditMeeting(IScheduleMeetingItem* pItem) = 0;
	
	/// \brief Edit Meeting.
	/// \param wndParam Edit the meeting through the dialog window by setting its parameter. For more details, see \link WndPosition \endlink structure.
	/// \param meetingUniqueID Assign a meeting ID to schedule or edit related meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Once the function is called successfully, the user will receive the callback event via IPreMeetingServiceEvent::onScheduleOrEditMeeting ().
	///The recurring meeting and webinar can only be edited via this function.
	virtual SDKError EditMeeting(WndPosition& wndParam, UINT64 meetingUniqueID) = 0;

	/// \brief Delete the specified scheduled meeting.
	/// \param meetingUniqueID Assign a meeting ID to delete meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Once the function is called successfully, the user will receive the callback event via IPreMeetingServiceEvent::onDeleteMeeting ().
	///It is forbidden to delete personal meeting or webinar or a recurring one.
	virtual SDKError DeleteMeeting(UINT64 meetingUniqueID) = 0;
	
	/// \brief Get the list of current meetings.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Once the function is called successfully, the user will receive the callback event via IPreMeetingServiceEvent::onListMeeting ().
	virtual SDKError ListMeeting() = 0;

	/// \brief Get a pointer to IMyMeeingItem.
	/// \param meetingUniqueID Specifies meeting ID to get the related object of the IMeetingItemInfo. 
	/// \return If the function succeeds, the return value is not NULL. Otherwise failed, returns NULL.
	virtual IMeetingItemInfo* GetMeeingItem(UINT64 meetingUniqueID) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif