#ifndef _CALENDER_SERVICE_INTERFACE_H_
#define _CALENDER_SERVICE_INTERFACE_H_
#include "zoom_sdk_def.h"
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE


class ICalenderEvent
{
public:
	virtual UINT64 GetMeetingNum() = 0;
	virtual const wchar_t* GetEventID() = 0;
	virtual const wchar_t* GetSummary() = 0;
	virtual const wchar_t* GetStartTime() = 0;
	virtual const wchar_t* GetEndTime() = 0;
	virtual const wchar_t* GetCreatorEmail() = 0;
	virtual const wchar_t* GetCreatorName() = 0;
	virtual const wchar_t* GetDescription() = 0;
	virtual ~ICalenderEvent(){};
};
enum CalenderResult
{
	CALENDER_SUCCESS,
	CALENDER_AUTH_ERROR,
	CALENDER_WEBAPI_ERROR,
	CALENDER_UNKNOW,
};

enum CalenderAuthType
{
	CalenderAuth_None,
	CalenderAuth_OutlookExchage,
	CalenderAuth_Goole,
};

/// \brief Calender Service Callback Event
///
class ICalenderServiceEvent
{
public:
	virtual void onCalenderEventsNotifcation(CalenderAuthType type, CalenderResult result, IList<ICalenderEvent* >* plstEvents) = 0;
};

/*! \struct tagOutlookExchageAuth
    \brief SDK Calender Authentication Parameter of outlook exchange.
    A more detailed struct description.
*/
typedef struct tagOutlookExchageAuth
{
	const wchar_t* serverUrl;
	const wchar_t* userName;
	const wchar_t* password;
	const wchar_t* calendaremail;
}OutlookExchageAuth;

/// \brief Calender Service Interface
class ICalenderService
{
public:
	virtual SDKError Init(ICalenderServiceEvent* pEvent) = 0;
	virtual SDKError Uninit() = 0;
	virtual SDKError StartOutlookExchangeCalender(OutlookExchageAuth& param) = 0;
	virtual SDKError StopOutlookExchangeCalender() = 0;
	virtual SDKError RetrieveCalEvents(CalenderAuthType type) = 0;
};
///
END_ZOOM_SDK_NAMESPACE
#endif