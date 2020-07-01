/*!
* \file meeting_audio_interface.h
* \brief Meeting Service Audio Interface.
* 
*/
#ifndef _MEETING_AUDIO_INTERFACE_H_
#define _MEETING_AUDIO_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum AudioStatus
    \brief Define the audio status of the user.
    Here are more detailed structural descriptions.
*/
enum AudioStatus
{
	Audio_None,///<Initialization.
	Audio_Muted,///<Muted status.
	Audio_UnMuted,///<Unmuted status.
	Audio_Muted_ByHost,///<Muted by the host.
	Audio_UnMuted_ByHost,///<Unmuted by the host.
	Audio_MutedAll_ByHost,///<The host mutes all.
	Audio_UnMutedAll_ByHost,///<The host unmutes all.
};
/*! \enum AudioType
    \brief Define the audio type of the user.
    Here are more detailed structural descriptions.
*/
enum AudioType
{
	AUDIOTYPE_NONE,///<Normal audio type.
	AUDIOTYPE_VOIP,///<In VoIP mode.
	AUDIOTYPE_PHONE,///<In telephone mode.
	AUDIOTYPE_UNKNOW,///<Unknown mode.
};

/// \brief Process after the user receives the requirement from the host to turn on the audio.
class IRequestStartAudioHandler
{
public:
	virtual ~IRequestStartAudioHandler(){};
	/// \brief Get the user ID who asks to turn on the audio.
	/// \return If the function succeeds, the return value is the user ID. FALSE 0.
	virtual unsigned int GetReqFromUserId() = 0;
	/// \brief Instance to ignore the requirement, return nothing and finally self-destroy.
	virtual SDKError Ignore() = 0;
	/// \brief Instance to accept the requirement, turn on the audio and finally self-destroy.
	virtual SDKError Accept() = 0;
	/// \brief Ignore the request to enable the video in the meeting and finally the instance self-destroys.
	virtual SDKError Cancel() = 0;
};

/// \brief User audio status interface.
class IUserAudioStatus
{
public:
	/// \brief Get the user ID.
	/// \return The user ID.
	virtual unsigned int GetUserId() = 0;
	
	/// \brief Get the audio status of the user.
	/// \return Value defined in AudioStatus enum, see \link AudioStatus \endlink enum.
	virtual AudioStatus GetStatus() = 0;
	
	/// \brief Get the audio type of the user. 
	/// \return Value defined in AudioType enum, see \link AudioType \endlink enum.
	virtual AudioType   GetAudioType() = 0;
	virtual ~IUserAudioStatus(){};
};

/// \brief Meeting audio callback event
///
class IMeetingAudioCtrlEvent
{
public:
	/// \brief User's audio status changed callback.
	/// \param lstAudioStatusChange List of the user information with audio status changed. The list will be emptied once the function calls end. 
	/// \param strAudioStatusList List of the user information whose audio status changes, saved in json format. This parameter is currently invalid, hereby only for reservations. 
	virtual void onUserAudioStatusChange(IList<IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL) = 0;

	/// \brief The callback event that users whose audio is active changed.
	/// \param plstActiveAudio List to store the ID of user whose audio is active.
	virtual void onUserActiveAudioChange(IList<unsigned int >* plstActiveAudio) = 0;

	/// \brief Callback event of the requirement to turn on the audio from the host.
	/// \param handler_ A pointer to the IRequestStartAudioHandler. For more details, see \link IRequestStartAudioHandler \endlink.
	virtual void onHostRequestStartAudio(IRequestStartAudioHandler* handler_) = 0;
};

/// \brief Meeting audio controller interface.
///
class IMeetingAudioController
{
public:
	/// \brief Configure the meeting audio controller callback event handler.
	/// \param pEvent An object pointer to the IMeetingAudioCtrlEvent that receives the meeting audio callback event. For more details, see \link IMeetingAudioCtrlEvent \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks The SDK use pEvent to transmit the callback event to the user's application. If the function is not called or failed, the user's application is unabled to retrieve the callback event.
	virtual SDKError SetEvent(IMeetingAudioCtrlEvent* pEvent) = 0;

	/// \brief Join VoIP meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError JoinVoip() = 0;

	/// \brief Leave VoIP meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError LeaveVoip() = 0;

	/// \brief Mute the assigned user.
	/// \param userid Specify the user ID to mute. ZERO(0) indicates to mute all the participants.
	/// \param allowUnmuteBySelf The user may unmute himself when everyone is muted.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError MuteAudio(unsigned int userid, bool allowUnmuteBySelf = true) = 0;

	/// \brief Unmute the assigned user. 
	/// \param userid Specify the user ID to unmute. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError UnMuteAudio(unsigned int userid) = 0;

	/// \brief Check if the user can unmute himself.
	/// \return TRUE indicates that the user can unmute himself. Otherwise not. 
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual bool CanUnMuteBySelf() = 0;

	/// \brief Mute or umute the user after joining the meeting. 
	/// \param bEnable TRUE indicates to mute the user after joining the meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError EnableMuteOnEntry(bool bEnable) = 0;

	/// \brief User joins or leaves the meeting in silence or no.
	/// \param bEnable TRUE indicates to play chime when the user joins or leaves the meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError EnablePlayChimeWhenEnterOrExit(bool bEnable) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif