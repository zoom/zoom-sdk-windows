/*!
* \file meeting_breakout_rooms_interface2.h
* \brief Meeting Service Breakout Room Interface
* Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_BREAKOUT_ROOMS_INTERFACE2_H_
#define _MEETING_BREAKOUT_ROOMS_INTERFACE2_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

typedef enum
{
	BO_CTRL_USER_STATUS_UNASSIGNED			= 1, //User is in main conference, not assigned to BO
	BO_CTRL_USER_STATUS_ASSIGNED_NOT_JOIN   = 2, //User is assigned to BO, but not join
	BO_CTRL_USER_STATUS_IN_BO				= 3, //User is already in BO
	BO_CTRL_USER_STATUS_UNKNOWN             = 4,
}BO_CTRL_USER_STATUS;

class IBOMeeting
{
public:
	virtual ~IBOMeeting() {}

	virtual const wchar_t* GetBOID() = 0;
	virtual const wchar_t* GetBOName() = 0;
	virtual IList<const wchar_t*>* GetBOUserList() = 0;
};

////////////////////////////////////////// IBOCreator //////////////////////////////////////////
class IBOCreator
{
public:
	virtual const wchar_t* CreateBO(const wchar_t* strBOName) = 0;
	virtual bool UpdateBOName(const wchar_t* strBOID, const wchar_t* strNewBOName) = 0; 
	virtual bool RemoveBO(const wchar_t* strBOID) = 0;
	virtual bool AssignUserToBO(const wchar_t* strUserID, const wchar_t* strBOID) = 0;
	virtual bool RemoveUserFromBO(const wchar_t* strUserID, const wchar_t* strBOID) = 0;									
};

////////////////////////////////////////// IBOAdmin //////////////////////////////////////////
class IBOAdmin
{
public:
	virtual bool StartBO() = 0;
	virtual bool StopBO() = 0;
	virtual bool AssignNewUserToRunningBO(const wchar_t* strUserID, const wchar_t* strBOID) = 0;
	virtual bool SwitchAssignedUserToRunningBO(const wchar_t* strUserID, const wchar_t* strBOID) = 0;
	virtual bool CanStartBO() = 0;
};

////////////////////////////////////////// IBOAssistant //////////////////////////////////////////
class IBOAssistant
{
public:
	virtual bool JoinBO(const wchar_t* strBOID) = 0;
	virtual bool LeaveBO() = 0;	
};

////////////////////////////////////////// IBOAttendee //////////////////////////////////////////
class IBOAttendee
{
public:
	virtual bool JoinBo() = 0;
	virtual bool LeaveBo() = 0;
	virtual const wchar_t* GetBoName() = 0;
};

////////////////////////////////////////// IBOData //////////////////////////////////////////
class IBODataEvent
{
public:
	//assigned user join BO/leave BO/name modified/!
	virtual void OnBOInfoUpdated(const wchar_t* strBOID) = 0; 
	//unassigned user join master/leave master/name modified/!
	virtual void OnUnAssignedUserUpdated() = 0; 
};
class IBOData
{
public:
	virtual void SetEvent(IBODataEvent* pEvent) = 0;
	virtual IList<const wchar_t*>* GetUnassginedUserList() = 0;
	virtual IList<const wchar_t*>* GetBOMeetingIDList() = 0;
	virtual const wchar_t* GetBOUserName(const wchar_t* strUserID) = 0;
	virtual BO_CTRL_USER_STATUS GetBOUserStatus(const wchar_t* strUserID) = 0;
	virtual IBOMeeting* GetBOMeetingByID(const wchar_t* strBOID) = 0;
};

////////////////////////////////////////// IMeetingBOController //////////////////////////////////////////
class IMeetingBOControllerEvent
{
public:
	virtual void onHasCreatorRightsNotification(IBOCreator* pCreatorObj) = 0;
	virtual void onHasAdminRightsNotification(IBOAdmin* pAdminObj) = 0;
	virtual void onHasAssistantRightsNotification(IBOAssistant* pAssistantObj) = 0;
	virtual void onHasAttendeeRightsNotification(IBOAttendee* pAttendeeObj) = 0;
	virtual void onHasDataHelperRightsNotification(IBOData* pDataHelperObj) = 0;

	virtual void onLostCreatorRightsNotification() = 0;
	virtual void onLostAdminRightsNotification() = 0;
	virtual void onLostAssistantRightsNotification() = 0;
	virtual void onLostAttendeeRightsNotification() = 0;
	virtual void onLostDataHelperRightsNotification() = 0;
};

class IMeetingBOController
{
public:
	virtual bool SetEvent(IMeetingBOControllerEvent* event) = 0;

	virtual IBOCreator*    GetBOCreatorHelper() = 0;
	virtual IBOAdmin*      GetBOAdminHelper() = 0;
	virtual IBOAssistant*  GetBOAssistantHelper() = 0;
	virtual IBOAttendee*   GetBOAttedeeHelper() = 0;
	virtual IBOData*	   GetBODataHelper() = 0;
	virtual bool IsBOStarted() = 0;
	virtual bool IsBOEnabled() = 0;
	virtual bool IsInBOMeeting() =0;
};

END_ZOOM_SDK_NAMESPACE
#endif