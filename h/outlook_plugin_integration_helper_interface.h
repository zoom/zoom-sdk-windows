/*!
* \file outlook_plugin_integration_helper_interface.h
* \brief Outlook plugin integration helper Interface.
* 
*/
#ifndef _OUTLOOK_PLUGIN_INTEGRATION_HELPER_INTERFACE_H_
#define _OUTLOOK_PLUGIN_INTEGRATION_HELPER_INTERFACE_H_
#include "zoom_sdk_def.h"
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Outlook plugin integration helper Callback Event
///
class IOutlookPluginIntegrationHelperEvent
{
public:
	/// \brief outlook plugin request login notification
	virtual void onOutlookPluginNeedLoginRequestNotification() = 0;

	/// \brief outlook plugin request schedule meeting notification
	virtual void onOutlookPluginScheduleMeetingRequestNotification() = 0;

	/// \brief outlook plugin request default meeting topic notification
	/// \param pScheduleForEmail schedule for email if has
	/// \param ppDefaultMeetingTopic if you want to change the default meeting topic, please change this value
	virtual void onOutlookPluginDefaultMeetingTopicRequestNotification(const wchar_t* pScheduleForEmail, wchar_t** ppDefaultMeetingTopic) = 0;
};

/// \brief Outlook plugin integration helper Interface
///
class IOutlookPluginIntegrationHelper
{
public:
	/// \brief Outlook plugin integration helper callback event
	/// \param pEvent A pointer to a IOutlookPluginIntegrationHelperEvent* that receives outlook plugin event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IOutlookPluginIntegrationHelperEvent* pEvent) = 0;

	// \brief Start outlook plugin integration
	/// \param ipc_channel_name IPC channel, default use zoom outlook plugin ipc channel, otherwise, please contact us . 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	///you need to call this APIs after onAuthenticationReturn return success status.
	virtual SDKError Start(const wchar_t* ipc_channel_name = NULL) = 0;

	// \brief Stop outlook plugin integration
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	///you need to call this APIs after onAuthenticationReturn return success status.
	virtual SDKError Stop() = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif