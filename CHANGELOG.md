# CHANGELOG

## 2017-06-08

### Added

1. Lock share status notify

2. Support switch video wall to next page feature

3. Support join leave VoIP feature

4. Support get meeting type feature

5. Support get user role feature

6. Breakout room feature enhancement

7. Webinar feature enhancement

8. Waiting room feature enhancement

9. More settings support:
    1> Support disable input meeting password dialog
    2> Allow or disallow "can unmute by self if mute by host" flag
    3> Support hide enter and exit full screen button

10. Bug fix

## 2017-04-12

### Added

1. Webinar promote and depromote meeting status change notify

2. Join and leave Breakout room meeting status change notify

3. Show or hide invite button in meeting ui and callback invite button click message support

4. Add new interface for H323 password

5. Bug Fix

## 2017-03-10

### Added

1. Add host change callback

2. Add spotlight video change callback

3. Add self record privilige change callback

4. Add Low Or Raise Hand Status change callback

5. Bug Fix

## 2017-03-02

### Added

1. Enhancement of proxy
   zoom_sdk.h
    - New interface:
		SDK_API SDKError CreateNetworkConnectionHelper(INetworkConnectio Helper** ppNetworkHelper);
        network_connection_handler_interface.h
    - New callback event:
        virtual void onProxySettingNotification(IProxySettingHandler* handler) = 0;

2. Enhancement of SSL cert Verification
   zoom_sdk.h
    - New interface:
    	SDK_API SDKError CreateNetworkConnectionHelper(INetworkConnectionHelper** ppNetworkHelper);
    	network_connection_handler_interface.h
    - New callback event:
    	virtual void onSSLCertVerifyNotification(ISSLCertVerificationHandler* handler    ) = 0;

3. Video/Audio session connection quality API
    meeting_service_interface.h
    - New interface:
       virtual ConnectionQuality GetAudioConnQuality() = 0;
       virtual ConnectionQuality GetVideoConnQuality() = 0;

4. Bugs fix

## 2017-02-10

### Added

1. Support waiting room

2. Support embedded browser feature

3. Refine the sdk demo project, add VS2015 support

5. Bug Fix

## 2017-01-20

### Added

1. Support to join Webinar meeting with as Panelist Support to pin/spotlight video

2. Support to pause/resume screen sharing Support H.323/SIP callout directly

3. Support invite by Phone andCall Medirectly

4. Add watermark - Powered by Zoom 

5. Support to start/join meeting without audio

6. Support to start/join meeting without video

7. Support Multi-share

8. New interface in ISettingService

9. New interface in IMeetingConfiguration 

10. Refine IMeetingService interface

## 2016-11-15

### Added

1. Add new interface for get windows handle

2. Fix branding issue in setting dialog, whiteboard and airhost window

3. Fix participant id don't take effect when start/join meeting

## 2016-10-05

### Added

1. fix leave meeting wnd cut off issue

## 2016-06-05

### Added

1. Support login zoom user
