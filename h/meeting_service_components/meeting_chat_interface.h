/*!
* \file meeting_chat_interface.h
* \brief Chat of Meeting Service Interface
* 
*/
#ifndef _MEETING_CHAT_INTERFACE_H_
#define _MEETING_CHAT_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Chat message information Interface
///
class IChatMsgInfo
{
public:
	/// \brief Get sender user id
	/// \return If the function succeeds, the return value is sender user id.
	///If the function fails, the return value is -1.
	virtual unsigned int GetSenderUserId() = 0;

	/// \brief Get sender user display name
	/// \return If the function succeeds, the return value is sender user display name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetSenderDisplayName() = 0;

	/// \brief Get receiver user id
	/// \return If the function succeeds, the return value is receiver user id.
	///if return value is 0, this message is send to everyone
	///If the function fails, the return value is -1.
	virtual unsigned int GetReceiverUserId() = 0;

	/// \brief Get receiver user display name
	/// \return If the function succeeds, the return value is receiver user display name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetReceiverDisplayName() = 0;

	/// \brief Get chat message content
	/// \return If the function succeeds, the return value is chat message content.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetContent() = 0;

	/// \brief Get chat message timestamp
	/// \return If the function succeeds, the return value is chat message timestamp.
	virtual time_t GetTimeStamp() = 0;

	virtual ~IChatMsgInfo() {};
};

/// \brief Meeting chat callback event
///
class IMeetingChatCtrlEvent
{
public:
	/// \brief chat message callback
	/// \param chatMsg chat message object. This param will invalid after this function call end.
	/// \param content chat message in json format,Reserved.
	virtual void onChatMsgNotifcation(IChatMsgInfo* chatMsg, const wchar_t* content = NULL) = 0;
};

/// \brief Meeting chat controller interface
///
class IMeetingChatController
{
public:
	/// \brief Set meeting chat callback event
	/// \param pEvent A pointer to a IMeetingChatCtrlEvent* that receives chat event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingChatCtrlEvent* pEvent) = 0;

	/// \brief Send chat message to somebody or All
	/// \param receiver the chat message receiver. if this parameter is zero, this message send to all
	/// \param content	the chat message content.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SendChatTo(unsigned int receiver, wchar_t* content) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif