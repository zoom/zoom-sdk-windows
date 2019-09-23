/*!
* \file premeeting_service_interface.h
* \brief PreMeeting Service Interface.
* 
*/
#ifndef _PREMEETING_SERVICE_INTERFACE_H_
#define _PREMEETING_SERVICE_INTERFACE_H_
#include "zoom_sdk_def.h"
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum PremeetingAPIResult
    \brief Premeeting API request result.
    A more detailed struct description.
*/
enum PremeetingAPIResult
{
	PREMETAPIRET_UNKNOW,
	PREMETAPIRET_SUCCESS,
};

/// \brief Schedule meeting item Interface
/// This interface is for schedule and edit meeting APIs
/// You can create and destroy this object with CreateScheduleMeetingItem and DestoryScheduleMeetingItem in IPreMeetingService
///
class IScheduleMeetingItem
{
public:
	/// \brief Set meeting topic
	/// \param topic meeting topic.
	virtual void SetMeetingTopic(const wchar_t* topic) = 0;

	/// \brief Set meeting password
	/// \param password meeting password.
	virtual void SetMeetingPassword(const wchar_t* password) = 0;

	/// \brief Set meeting start time, please use your OS system timezone
	/// \param time meeting start time.
	virtual void SetStartTime(time_t time) = 0;
	
	/// \brief Set meeting duration, in minutes.
	/// \param duration meeting duration.
	virtual void SetDurationInMinutes(time_t duration) = 0;

	/// \brief Set meeting join before host flag
	/// \param bAllow if yes, attendee can join this meeting before host in meeting.
	virtual void SetAllowJoinBeforeHost(bool bAllow) = 0;

	/// \brief Set meeting use your personal meeting id flag
	/// \param bUserPMI if yes, meeting will use your personal meeting id.
	virtual void SetUsePMIAsMeetingID(bool bUserPMI) = 0;

	/// \brief Turn off video for host
	/// \param bTurnOff if true,host start meeting without video.
	virtual void TurnOffVideoForHost(bool bTurnOff) = 0;

	/// \brief Turn off video for attendee
	/// \param bTurnOff if true, attendee join meeting without video.
	virtual void TurnOffVideoForAttendee(bool bTurnOff) = 0;
protected:
	virtual ~IScheduleMeetingItem(){};
};


/// \brief Meeting item information interface
/// Get the basic information of your meeting with this interface
class IMyMeetingItem
{
public:
	/// \brief Determines whether the specified meeting identifies a personal meeting.
	/// \return If the meeting identifies a personal meeting, the return value is true.otherwise is false.
	virtual bool   IsPersonalMeeting() = 0;
	
	/// \brief Determines whether the specified meeting identifies a webinar meeting.
	/// \return If the meeting identifies a webinar meeting, the return value is true.otherwise is false.
	virtual bool   IsWebinarMeeting() = 0;

	/// \brief Determines whether the specified meeting identifies a recurring meeting.
	/// \return If the meeting identifies a recurring meeting, the return value is true.otherwise is false.
	virtual bool   IsRecurringMeeting() = 0;

	/// \brief Get ID of the specified meeting
	/// \return ID of the specified meeting. use this value in edit and delete meeting APIS
	virtual UINT64 GetMeeingUniqueID() = 0;

	/// \brief Get number of the specified meeting
	/// \return The number of the specified meeting
	virtual UINT64 GetMeetingNumber() = 0;

	/// \brief Get topic of the specified meeting
	/// \return The topic of the specified meeting
	virtual const wchar_t* GetMeetingTopic() = 0;

	/// \brief Get password of the specified meeting
	/// \return The password of the specified meeting
	virtual const wchar_t* GetMeetingPassword() = 0;

	/// \brief Get start time of the specified meeting
	/// \return The start time of the specified meeting
	virtual time_t GetStartTime() = 0;

	/// \brief Get duration of the specified meeting
	/// \return The duration of the specified meeting, in minutes.
	virtual time_t GetDurationInMinutes() = 0;

	/// \brief Get the join before host flag of the specified meeting
	/// \return The join before host flag of the specified meeting.
	virtual bool IsAllowJoinBeforeHost() = 0;

	/// \brief Get the use personal meeting id flag of the specified meeting
	/// \return The use personal meeting id flag before host flag of the specified meeting.
	virtual bool IsUsePMIAsMeetingID() = 0;
};

/// \brief PreMeeting service event interface
class IPreMeetingServiceEvent
{
public:
	/// \brief List meeting callback
	/// \param result List meeting result. refer enum PremeetingAPIResult.
	/// \param lstMeetingList meeting's unique ID list.
	virtual void onListMeeting(PremeetingAPIResult result, IList<UINT64 >* lstMeetingList) = 0;

	/// \brief Schedule or edit meeting callback
	/// \param result Schedule or edit meeting result. refer enum PremeetingAPIResult.
	/// \param meetingUniqueID  the unique ID which meeting you scheduled or edited.
	virtual void onScheduleOrEditMeeting(PremeetingAPIResult result, UINT64 meetingUniqueID) = 0;

	/// \brief Delete meeting callback
	/// \param result Delete meeting result. refer enum PremeetingAPIResult.
	virtual void onDeleteMeeting(PremeetingAPIResult result) = 0;
};

/// \brief PreMeeting service interface
class IPreMeetingService
{
public:
	/// \brief Create schedule meeting item
	/// \return If the function succeeds, the return value is IScheduleMeetingItem object.
	virtual IScheduleMeetingItem* CreateScheduleMeetingItem() = 0;

	/// \brief Destory schedule meeting item
	/// \param pMeeting The object created by CreateScheduleMeetingItem
	virtual void DestoryScheduleMeetingItem(IScheduleMeetingItem* pMeeting) = 0;

	/// \brief Set premeeting service event
	/// \param pEvent The premeeting service event
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IPreMeetingServiceEvent* pEvent) = 0;

	/// \brief Schedule Meeting
	/// \param pItem The object created by CreateScheduleMeetingItem
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ScheduleMeeting(IScheduleMeetingItem* pItem) = 0;

	/// \brief Schedule Meeting
	/// \param wndParam brief Show schedule dialog Parameter, more detailed refer to struct description.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ScheduleMeeting(WndPosition& wndParam) = 0;

	/// \brief Edit Meeting
	/// \param meetingUniqueID The meeting unique ID which meeting you want to edit
	/// \param pItem The object created by CreateScheduleMeetingItem
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EditMeeting(UINT64 meetingUniqueID, IScheduleMeetingItem* pItem) = 0;

	/// \brief Edit Meeting
	/// \param wndParam brief Show schedule dialog Parameter, more detailed refer to struct description.
	/// \param meetingUniqueID The meeting unique ID which meeting you want to edit
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EditMeeting(WndPosition& wndParam, UINT64 meetingUniqueID) = 0;

	/// \brief Set premeeting service event
	/// \param meetingUniqueID The meeting unique ID which meeting you want to delete
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DeleteMeeting(UINT64 meetingUniqueID) = 0;

	/// \brief List your meetings
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ListMeeting() = 0;

	/// \brief Get meeting item
	/// \param meetingUniqueID The meeting unique ID which meeting you want to query information
	/// \return If the function succeeds, the return value is not NULL.
	///If the function fails, the return value is NULL.
	virtual IMyMeetingItem* GetMeeingItem(UINT64 meetingUniqueID) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif