/*!
* \file calender_service_interface.h
* \brief Calendar Service Interface
* 
*/
#ifndef _CALENDER_SERVICE_INTERFACE_H_
#define _CALENDER_SERVICE_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/// \brief Calendar information interface.
///

class ICalenderEvent
{
public:
	/// \brief Get the meeting number.
	/// \return The meeting number.
	virtual UINT64 GetMeetingNum() = 0;
	
	/// \brief Get the ID of calendar.
	/// \return The ID of calendar.
	virtual const wchar_t* GetEventID() = 0;
	
	/// \brief Get the summary of calendar.
	/// \return The summary of calendar.
	virtual const wchar_t* GetSummary() = 0;
	
	/// \brief Get the start time of meeting.
	/// \return The start time of meeting.
	virtual const wchar_t* GetStartTime() = 0;
	
	/// \brief Get the end time of meeting.
	/// \return The end time of meeting.
	virtual const wchar_t* GetEndTime() = 0;

	/// \brief Get the email of the meeting creator.
	/// \return The email of the meeting creator.
	virtual const wchar_t* GetCreatorEmail() = 0;

	/// \brief Get the name of the meeting creator.
	/// \return The name of the meeting creator.
	virtual const wchar_t* GetCreatorName() = 0;

	/// \brief Get the description of the meeting.
	/// \return The description of the meeting.
	virtual const wchar_t* GetDescription() = 0;

	virtual ~ICalenderEvent(){};
};

/*! \enum CalenderResult
	\brief The type of calendar result.
	Here are more detailed structural descriptions.
*/
enum CalenderResult
{
	CALENDER_SUCCESS,///<Verification successful.
	CALENDER_AUTH_ERROR,///<Verification failed.
	CALENDER_WEBAPI_ERROR,///<Web API service error.
	CALENDER_UNKNOW,///<Unknown error.
};

/*! \enum CalenderAuthType
	\brief The type of calendar authority.
	Here are more detailed structural descriptions.
*/
enum CalenderAuthType
{
	CalenderAuth_None,///<For initiation.
	CalenderAuth_OutlookExchage,///<Use OutlookExchange to verify.
	CalenderAuth_Goole,///<Use Google to verify. This function is currently invalid, hereby only for reservations.
};

/// \brief calendar Service Callback Event.
///
class ICalenderServiceEvent
{
public:
	/// \brief calendar service callback.
	/// \param type The type of authority. For more details, see \link CalenderAuthType \endlink enum.
	/// \param result The result of authority. For more details, see \link CalenderResult \endlink enum.
	/// \param plstEvents A pointer to the ICalenderEvent* list. For more details, see \link ICalenderEvent \endlink.
	/// \remarks The plstEvents* will be destroyed once the function calls end.
	virtual void onCalenderEventsNotifcation(CalenderAuthType type, CalenderResult result, IList<ICalenderEvent* >* plstEvents) = 0;
};

/*! \struct tagOutlookExchageAuth
    \brief The verification of SDK when use the Outlook Exchange.
    Here are more detailed structural descriptions.
*/
typedef struct tagOutlookExchageAuth
{
	const wchar_t* serverUrl;///<The URL of server.
	const wchar_t* userName;///<Username.
	const wchar_t* password;///<The password of user.
	const wchar_t* calendaremail;///<The email box of user.
}OutlookExchageAuth;

/// \brief calendar Service Interface
class ICalenderService
{
public:
	/// \brief Set the calendar service callback event handler, and initialize the calendar service.
	/// \param pEvent Specifies a pointer to ICalenderServiceEvent which will handle the callback events.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Init(ICalenderServiceEvent* pEvent) = 0;
	
	/// \brief Uninitialized the calendar service.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Uninit() = 0;
	
	/// \brief Schedule the meeting by the calendar of Outlook Exchange.
	/// \param param Specifies the parameter. For more details, see \link OutlookExchageAuth \endlink structure.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartOutlookExchangeCalender(OutlookExchageAuth& param) = 0;
	
	/// \brief Stop using the Outlook Exchange to schedule the meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StopOutlookExchangeCalender() = 0;
	
	/// \brief Get the calendar event. The SDK will inform the user via ICalenderServiceEvent::onCalenderEventsNotifcation().
	/// \param type Specifies the type to get. The only type supported for the moment is the CalenderAuth_OutlookExchage. For more details, see \link CalenderAuthType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RetrieveCalEvents(CalenderAuthType type) = 0;
};
///
END_ZOOM_SDK_NAMESPACE
#endif