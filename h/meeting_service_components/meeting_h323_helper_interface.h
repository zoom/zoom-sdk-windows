/*!
* \file meeting_service_interface.h
* \brief Meeting Service Interface
* 
*/
#ifndef _MEETING_H323_HELPER_INTERFACE_H_
#define _MEETING_H323_HELPER_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Meeting H323 helper Callback Event
///

/*! \enum H323CalloutStatus
    \brief H323 Callout status.
    A more detailed struct description.
*/
enum H323CalloutStatus
{
	H323Callout_Unknown,
	H323Callout_Success,
	H323Callout_Ring,
	H323Callout_Timeout,
	H323Callout_Failed,
};

/*! \enum H323ParingStatus
    \brief H323 Paring status.
    A more detailed struct description.
*/
enum H323ParingResult
{
	H323Paring_Unknown,
	H323Paring_Success,
	H323Paring_Meeting_Not_Exist,
	H323Paring_Paringcode_Not_Exist,
	H323Paring_No_Privilege,
	H323Paring_Other_Error,
};

/// \brief Meeting H323 Helper callback event
///
class IMeetingH323HelperEvent
{
public:
	/// \brief H323 device call out status callback
	/// \param status H323 device call out status value.
	virtual void onCalloutStatusNotify(H323CalloutStatus status) = 0;

	/// \brief Paring H323 to meeting status callback
	/// \param result Paring result.
	virtual void onParingH323Result(H323ParingResult result) = 0;
};


/*! \enum H323DeviceType
    \brief H323 device type.
    A more detailed struct description.
*/
enum H323DeviceType
{
	H323DeviceType_Unknown,
	H323DeviceType_H323,
	H323DeviceType_SIP,
};

/*! \struct tagH323Device
    \brief H323 Device info.
    A more detailed struct description.
*/
typedef struct tagH323Device{
	tagH323Device()
	{
		name = NULL;
		ip = NULL;
		e164num = NULL;
		type = H323DeviceType_Unknown;
	}
	wchar_t* name;
	wchar_t* ip;
	wchar_t* e164num;
	H323DeviceType	type;
}H323Device;

/// \brief Meeting H323 Helper Interface
///
class IMeetingH323Helper
{
public:
	/// \brief Set meeting h323 helper callback event
	/// \param pEvent A pointer to a IMeetingH323HelperEvent* that receives h323 helper event. 
	virtual void SetEvent(IMeetingH323HelperEvent* pEvent) = 0;

	/// \brief Get h323 address for current meeting
	/// \return If the function succeeds, the return value is not NULL.
	virtual IList<const wchar_t* >* GetH323Address() = 0;

	/// \brief Get h323 password for current meeting
	/// \return h323 password
	virtual const wchar_t* GetH323Password() = 0;

	/// \brief Send Meeting paring code
	/// \param meetingNum Specifies which meeting to paring. 
	/// \param paringCode Code for paring
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SendMeetingParingCode(UINT64 meetingNum, wchar_t* paringCode) = 0;

	/// \brief Call out a H323 device
	/// \param deviceInfo Specifies which h323 device you want to call out.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CallOutH323(H323Device& deviceInfo) = 0;

	/// \brief Cancel a h323 device call out
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CancelCallOutH323() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif