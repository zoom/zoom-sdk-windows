/*!
* \file meeting_h323_helper_interface.h
* \brief H.323 helper Interface of meeting service
* Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_H323_HELPER_INTERFACE_H_
#define _MEETING_H323_HELPER_INTERFACE_H_
#include "..\zoom_sdk_def.h"
#include <string>

BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Callback Event of Meeting H.323 helper.
///

/*! \enum H323CalloutStatus
    \brief H.323 Callout status.
    Here are more detailed structural descriptions.
*/
enum H323CalloutStatus
{
	H323Callout_Unknown, ///<Used only for initialization.
	H323Callout_Success, ///<Call out successfully.
	H323Callout_Ring,   ///<Bell during the call.
	H323Callout_Timeout, ///<Call timeout.
	H323Callout_Failed, ///<Call fails.
};

/*! \enum H323ParingResult
    \brief H.323 Pairing status.
    Here are more detailed structural descriptions.
*/
enum H323ParingResult
{
	H323Paring_Unknown,///<Used only for initialization. 
	H323Paring_Success,///<Pairing successful.
	H323Paring_Meeting_Not_Exist,///<The meeting being paired does not exist.
	H323Paring_Paringcode_Not_Exist,///<Pairing code does not exist.
	H323Paring_No_Privilege, ///<No pairing privilege.
	H323Paring_Other_Error, ///<Other issues.
};

/// \brief Meeting H.323 Helper callback event.
///
class IMeetingH323HelperEvent
{
public:
	/// \brief Callback event when the calling status of H.323 device changes.
	/// \param status H.323 device calling out status value. For more details, see \link H323CalloutStatus \endlink enum.
	virtual void onCalloutStatusNotify(H323CalloutStatus status) = 0;

	/// \brief The callback event is triggered when the result of using the H.323 device to pair the assigned meeting is out.
	/// \param result Paring result. For more details, see \link H323ParingResult \endlink enum.
	/// \param meetingNumber The meeting number to be paired.
	virtual void onParingH323Result(H323ParingResult result, UINT64 meetingNumber) = 0;
};


/*! \enum H323DeviceType
    \brief H.323 device type.
    Here are more detailed structural descriptions.
*/
enum H323DeviceType
{
	H323DeviceType_Unknown,///<Unknown device, only for initialization.
	H323DeviceType_H323,///<H.323 device.
	H323DeviceType_SIP,///<SIP device.
	H323DeviceType_BOTH,///<H.323 device and SIP device.
};

/// \brief Meeting H.323 device Interface
///
class IH323Device
{
public:
	///<Virtual function definition.
	virtual const wchar_t* GetName() = 0;
	///<Virtual function definition.
	virtual const wchar_t* GetIP() = 0;
	///<Virtual function definition.
	virtual const wchar_t* GetE164Num() = 0;
	///<Virtual function definition.
	virtual H323DeviceType GetDeviceType() = 0;
	virtual bool IsCustomizedH323Device() = 0;
	virtual ~IH323Device(){};
};

/// \brief Customized Meeting H.323 device
///
class CustomizedH323Device : public IH323Device
{
public:
	CustomizedH323Device()
	{
		_type = H323DeviceType_Unknown;
	}

	virtual void SetName(const wchar_t* name_)
	{
		if (name_)
			_name = name_;
	}

	virtual const wchar_t* GetName()
	{
		return _name.c_str();
	}

	virtual void SetIP(const wchar_t* ip_)
	{
		if (ip_)
			_ip = ip_;
	}

	virtual const wchar_t* GetIP()
	{
		return _ip.c_str();
	}

	virtual void SetE164Num(const wchar_t* e164num_)
	{
		if (e164num_)
			_e164num = e164num_;
	}

	virtual const wchar_t* GetE164Num()
	{
		return _e164num.c_str();
	}

	virtual void SetDeviceType(H323DeviceType type_)
	{
		_type = type_;
	}

	virtual H323DeviceType GetDeviceType()
	{
		return _type;
	}

	virtual bool IsCustomizedH323Device()
	{
		return true;
	}

private:
	H323DeviceType _type;///<Type of device.
	std::wstring _name;///<Device name.
	std::wstring _ip;///<Device IP.
	std::wstring _e164num;///<E.164 number
};

/// \brief Meeting H323 Helper Interface.
///
class IMeetingH323Helper
{
public:
	/// \brief Set meeting H.323 helper callback event handler.
	/// \param pEvent A pointer to the IMeetingH323HelperEvent that receives H.323 helper event. 
	virtual void SetEvent(IMeetingH323HelperEvent* pEvent) = 0;

	/// \brief Get the list of H.323 call-in number supported by the current meeting.
	/// \return If the function succeeds, the return value is the pointer to the list of the call-in number. Otherwise failed, the return value is NULL.
	virtual IList<const wchar_t* >* GetH323Address() = 0;

	/// \brief Get the H.323 password for the current meeting.
	/// \return If the function succeeds, the return value is the H.323 meeting connect password. Otherwise failed, the return value is the length of zero(0）. 
	virtual const wchar_t* GetH323Password() = 0;

	/// \brief Determine if it is enabled to pair the meeting.
	/// \param meetingNum TRUE Specifies the meeting number.
	/// \return If pairing meeting is enabled, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanPairingMeeting(UINT64 meetingNum) = 0;

	/// \brief Send Meeting paring code.
	/// \param meetingNum Specifies which meeting to paring. 
	/// \param paringCode Code for paring
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If the function succeeds, the IMeetingH323HelperEvent::onParingH323Result() will be triggered once received the response of the H.323 device. 
	virtual SDKError SendMeetingParingCode(UINT64 meetingNum, wchar_t* paringCode) = 0;

	/// \brief Get the list of the call-out devices supported by the current meeting.
	/// \return If the function succeeds, the return value is the pointer to the list of devices. 
	///Otherwise failed, the return value is an empty list. For more details, see \link IH323Device \endlink.
	/// \remarks The list will be cleared each time the function is called.
	virtual IList<IH323Device* >* GetCalloutH323DviceList() = 0;

	/// \brief Call out with the assigned H.323 device.
	/// \param deviceInfo Specify the H.323 device to use. For more details, see \link IH323Device \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success. 
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If the function succeeds, the IMeetingH323HelperEvent::onCalloutStatusNotify() will be triggered once the callout status of H.323 device changes.
	virtual SDKError CallOutH323(IH323Device* deviceInfo) = 0;

	/// \brief Cancel current outgoing call.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CancelCallOutH323() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif