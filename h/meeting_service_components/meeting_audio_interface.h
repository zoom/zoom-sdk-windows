/*!
* \file meeting_audio_interface.h
* \brief Audio of Meeting Service Interface
* 
*/
#ifndef _MEETING_AUDIO_INTERFACE_H_
#define _MEETING_AUDIO_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum AudioStatus
    \brief Audio status.
    A more detailed struct description.
*/
enum AudioStatus
{
	Audio_None,
	Audio_Muted,
	Audio_UnMuted,
	Audio_Muted_ByHost,
	Audio_UnMuted_ByHost,
	Audio_MutedAll_ByHost,
	Audio_UnMutedAll_ByHost,
};

enum AudioType
{
	AUDIOTYPE_NONE,
	AUDIOTYPE_VOIP,
	AUDIOTYPE_PHONE,
	AUDIOTYPE_UNKNOW,
};

class IUserAudioStatus
{
public:
	virtual unsigned int GetUserId() = 0;
	virtual AudioStatus GetStatus() = 0;
	virtual AudioType   GetAudioType() = 0;
	virtual ~IUserAudioStatus(){};
};

/// \brief Meeting audio callback event
///
class IMeetingAudioCtrlEvent
{
public:
	/// \brief User's audio status change callback
	/// \param lstAudioStatusChange List of status changed user. This param will invalid after this function call end.
	/// \param strAudioStatusList Audio status change list in json format,Reserved.
	virtual void onUserAudioStatusChange(IList<IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL) = 0;

	/// \brief active audio change callback
	/// \param lstActiveVideo the list of active audio user.
	virtual void onUserActiveAudioChange(IList<unsigned int >* plstActiveAudio) = 0;
};

/// \brief Meeting audio controller interface
///
class IMeetingAudioController
{
public:
	/// \brief Set meeting audio controller callback event
	/// \param pEvent A pointer to a IMeetingAudioCtrlEvent* that receives audio event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingAudioCtrlEvent* pEvent) = 0;

	/// \brief Join Voip audio
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError JoinVoip() = 0;

	/// \brief Leave Voip audio
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LeaveVoip() = 0;

	/// \brief Mute audio
	/// \param userId Specifies which the user's audio to mute.if is zero, mute all of users
	/// \param allowUnmuteBySelf Specifies can unmute by self or not when mute all.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError MuteAudio(unsigned int userid, bool allowUnmuteBySelf = true) = 0;

	/// \brief Unmute audio
	/// \param userId Specifies which the user's audio to unmute.if is zero, unmute all of users
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError UnMuteAudio(unsigned int userid) = 0;

	/// \brief Can unmute by self?
	/// \return Can unmute by self or not
	virtual bool CanUnMuteBySelf() = 0;

	/// \brief Enable mute on entry feature when User join meeting
	/// \param bEnable Specifies mute on entry feature enable or disable.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableMuteOnEntry(bool bEnable) = 0;

	/// \brief Enable play chime feature when user join or leave meeting.
	/// \param bEnable Specifies play chime feature when user join or leave meeting, enable or disable.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnablePlayChimeWhenEnterOrExit(bool bEnable) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif