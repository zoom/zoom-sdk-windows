/*!
* \file meeting_interpretation_interface.h
* \brief Meeting Service Interpretation Interface
* Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_INTERPRETATION_INTERFACE_H_
#define _MEETING_INTERPRETATION_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/// \brief interpretation language interface.
///
class IInterpretationLanguage
{
public:
	virtual ~IInterpretationLanguage() {}
	virtual int GetLanguageID() = 0;
	virtual const wchar_t* GetLanguageAbbreviations() = 0;
	virtual const wchar_t* GetLanguageName() = 0;
};

/// \brief interpreter interface.
///
class IInterpreter
{
public:
	virtual ~IInterpreter() {}
	virtual unsigned int GetUserID() = 0;
	virtual int GetLanguageID1() = 0;  
	virtual int GetLanguageID2() = 0;
	virtual bool IsAvailable() = 0;
};

/// \brief Meeting interpretation callback event.
///
class IMeetingInterpretationControllerEvent
{
public:
	virtual ~IMeetingInterpretationControllerEvent() {}

	/// \brief interpretation start callback. This function is used to inform the user interpretation has been started, and all users in meeting can get the event.
	virtual void OnInterpretationStart() = 0;

	/// \brief interpretation stop callback. This function is used to inform the user interpretation has been stopped, and all users in meeting can get the event.
	virtual void OnInterpretationStop() = 0;

	/// \brief interpreter list changed callback. when some interpreter leave meeting or preset interpreter join meeting, and only host can get the event.
	virtual void OnInterpreterListChanged() = 0;

	/// \brief interpreter role changed callback. when a user's role changed(participant <-> interpreter), and all users in meeting can get the event.
	/// \param userID Specify the user ID whose status changed.
	/// \param isInterpreter Specify the user's role is interpreter or not.
	virtual void OnInterpreterRoleChanged(unsigned int userID, bool isInterpreter) = 0;

	/// \brief interpreter active language changed callback. when a interpreter's active language changed, and all users in meeting can get the event.
	/// \param userID Specify the user ID whose active language changed.
	/// \param activeLanID Specify the interpreter current active language id.
	virtual void OnInterpreterActiveLanguageChanged(unsigned int userID, int activeLanID) = 0;
	
	/// \brief interpreter languages changed callback. when a interpreter's languages changed, and only the interpreter can get the event.
	/// \param lanID1 Specify the new language ID1.
	/// \param lanID2 Specify the new language ID2.
	virtual void OnInterpreterLanguageChanged(int lanID1, int lanID2) = 0;

	/// \brief available languages changed callback. when available languages in meeting are changed, all non interpreter users in meeting can get the event.
	/// \param pAvailableLanguageList Specify the available languages list.
	virtual void OnAvailableLanguageListUpdated(IList<IInterpretationLanguage*>* pAvailableLanguageList) = 0;
};

/// \brief Meeting interpretation controller interface
///
class IMeetingInterpretationController
{
public:
	virtual ~IMeetingInterpretationController() {}

	//Common (for all)

	/// \brief Set the interpretation controller callback event handler.
	/// \param event A pointer to the IMeetingInterpretationControllerEvent that receives the interpretation event. . 
	virtual void SetEvent(IMeetingInterpretationControllerEvent * event) = 0;  

	/// \brief Determine if interpretation feature is enabled in the meeting.
	virtual bool IsInterpretationEnabled() = 0;

	/// \brief Determine if interpretation has been started by host.
	virtual bool IsInterpretationStarted() = 0;

	/// \brief Determine if myself is interpreter.
	virtual bool IsInterpreter() = 0;

	/// \brief Get the interpretation language object of specified language ID.
	/// \param lanID Specify the language ID for which you want to get the information. 
	/// \return If the function succeeds, the return value is a pointer to the IInterpretationLanguage, Otherwise failed, the return value is NULL.
	virtual IInterpretationLanguage* GetInterpretationLanguageByID(int lanID) = 0;

	//Admin (only for host) 

	/// \brief Get the all interpretation language list.
	/// \return If the function succeeds, the return value is a pointer to the IList<IInterpretationLanguage*>, Otherwise failed, the return value is NULL.
    virtual IList<IInterpretationLanguage*>* GetAllLanguageList() = 0;
	
	/// \brief Get the interpreters list.
	/// \return If the function succeeds, the return value is a pointer to the IList<IInterpreter*>, Otherwise failed, the return value is NULL.
	virtual IList<IInterpreter*>* GetInterpreterList() = 0;

	/// \brief Add someone as a interpreter.
	/// \param userID Specify the user.
	/// \param lanID1 Specify the language1.
	/// \param lanID2 Specify the language2.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError AddInterpreter(unsigned int userID, int lanID1, int lanID2) = 0;

	/// \brief Remove some interpreter.
	/// \param userID Specify the interpreter.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RemoveInterpreter(unsigned int userID) = 0;

	/// \brief modify the language of some interpreter.
	/// \param userID Specify the interpreter.
	/// \param lanID1 Specify the new language1.
	/// \param lanID2 Specify the new language2.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ModifyInterpreter(unsigned int userID, int lanID1, int lanID2) = 0;

	/// \brief Start interpretation.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartInterpretation() = 0;

	/// \brief Stop interpretation.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StopInterpretation() = 0;

	//Listener (for non interpreter)

	/// \brief Get the available interpretation language list.
	/// \return If the function succeeds, the return value is a pointer to the IList<IInterpretationLanguage*>, Otherwise failed, the return value is NULL.
	virtual IList<IInterpretationLanguage*>* GetAvailableLanguageList() = 0;

	/// \brief Join some language channel.
	/// \param lanID Specify the language channel.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError JoinLanguageChannel(int lanID) = 0;
	
	/// \brief Get the language ID which myself is in.
	/// \param [out] lanID indicates the language ID which myself is in.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GetJoinedLanguageID(int& lanID) = 0;
	
	/// \brief Turn off the major audio, if you are in some interpreter language channel.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError TurnOffMajorAudio() = 0;
	
	/// \brief Turn on the major audio, if you are in some interpreter language channel.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError TurnOnMajorAudio() = 0;
	
	/// \brief Determine if the major audio is off.
	/// \param [out] bOff indicates the major audio off status.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError IsMajorAudioTurnOff(bool& bOff) = 0;

	//Interpreter (only for interpreter)

	/// \brief Get languages if myself is a interpreter.
	/// \param [out] lanID1 Specify the language1.
	/// \param [out] lanID2 Specify the language2.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GetInterpreterLans(int& lanID1, int& lanID2) = 0;

	/// \brief Set a language channel which myself will be in, if myself is a interpreter.
	/// \param activeLanID Specify the active language.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetInterpreterActiveLan(int activeLanID) = 0;

	/// \brief Get the active language ID, if myself is a interpreter.
	/// \param [out] lanID Specify the active language.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GetInterpreterActiveLan(int& lanID) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif