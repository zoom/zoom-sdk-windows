/*!
* \file zoom_sdk_def.h
* \brief SDK utility Definition of ZOOM windows.
* 
*/

#ifndef _ZOOM_SDK_UTIL_DEFINE_H_
#define _ZOOM_SDK_UTIL_DEFINE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
class ICameraControllerEvent
{
public:
	/// Callback of event that controller status changes.				
	virtual void onControllerStatusChanged(bool valid) = 0;
};
class ICameraController
{
public:
	/// Set the controls for camera.
	virtual ~ICameraController(){}
	virtual SDKError SetEvent(ICameraControllerEvent* pEvent) = 0;
	virtual bool	 IsValid() = 0;
	
	/// Adjust the camera: turn left.
	virtual SDKError BeginTurnLeft() = 0;
	virtual SDKError ContinueTurnLeft() = 0;
	virtual SDKError EndTurnLeft() = 0;

	/// Adjust the camera: turn right.
	virtual SDKError BeginTurnRight() = 0;
	virtual SDKError ContinueTurnRight() = 0;
	virtual SDKError EndTurnRight() = 0;

	/// Adjust the camera: turn up.
	virtual SDKError BeginTurnUp() = 0;
	virtual SDKError ContinueTurnUp() = 0;
	virtual SDKError EndTurnUp() = 0;

	/// Adjust the camera: turn down.
	virtual SDKError BeginTurnDown() = 0;
	virtual SDKError ContinueTurnDown() = 0;
	virtual SDKError EndTurnDown() = 0;

	/// Adjust the camera: zoom camera in, move the camera angle closer to the players/field.
	virtual SDKError BeginZoomIn() = 0;
	virtual SDKError ContinueZoomIn() = 0;
	virtual SDKError EndZoomIn() = 0;

	/// Adjust the camera: zoom camera out, move the camera angle far from the players/field.
	virtual SDKError BeginZoomOut() = 0;
	virtual SDKError ContinueZoomOut() = 0;
	virtual SDKError EndZoomOut() = 0;

	// Used to determine whether the camera can be controlled or not
	virtual SDKError CanControlCamera(bool& bCan) = 0;
};
END_ZOOM_SDK_NAMESPACE

#endif