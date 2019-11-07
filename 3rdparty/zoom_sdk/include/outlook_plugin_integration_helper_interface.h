/*!
* \file outlook_plugin_integration_helper_interface.h
* \brief Outlook Plugin Integration Helper Interface.
* 
*/
#ifndef _OUTLOOK_PLUGIN_INTEGRATION_HELPER_INTERFACE_H_
#define _OUTLOOK_PLUGIN_INTEGRATION_HELPER_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Outlook plugin integration helper Callback event.
///
class IOutlookPluginIntegrationHelperEvent
{
public:
	/// \brief The callback event will be triggered when the outlook plugin requests a login.
	virtual void onOutlookPluginNeedLoginRequestNotification() = 0;

	/// \brief The callback event will be triggered when the outlook plugin requests to schedule a meeting.
	virtual void onOutlookPluginScheduleMeetingRequestNotification() = 0;

	/// \brief The callback event will be triggered when the outlook plugin requests to assign a meeting topic.
	/// \param pScheduleForEmail The email owner will be the host of the scheduled meeting.	
	/// \param ppDefaultMeetingTopic The meeting topic by default. It is able to be changed.
	virtual void onOutlookPluginDefaultMeetingTopicRequestNotification(const wchar_t* pScheduleForEmail, wchar_t** ppDefaultMeetingTopic) = 0;
};

/// \brief Outlook plugin integration helper interface.
///
class IOutlookPluginIntegrationHelper
{
public:
	/// \brief Outlook plugin integration helper callback handler.
	/// \param pEvent A pointer to the IOutlookPluginIntegrationHelperEvent that receives outlook plugin event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IOutlookPluginIntegrationHelperEvent* pEvent) = 0;

	/// \brief Start outlook plugin integration.
	/// \param ipc_channel_name Currently only the default value is supported. If you have any special requirements, please contact the vendor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Start(const wchar_t* ipc_channel_name = NULL) = 0;

	/// \brief Stop Outlook plugin integration.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Stop() = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif