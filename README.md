# Zoom Windows Software Development Kit (SDK)
<div align="center">
<img src="https://s3.amazonaws.com/user-content.stoplight.io/8987/1541013063688" width="400px" max-height="400px" style="margin:auto;"/>
</div>


## Table of Contents
- [Latest SDK News](#latest-sdk-news)   
- [Full Documentation && Community Support](#full-documentation-community-support)   
- [What is Zoom Windows SDK?](#what-is-zoom-windows-sdk)   
- [Disclaimer](#disclaimer)   
- [Getting Started](#getting-started)   
  - [Prerequisites](#prerequisites)   
  - [Installing](#installing)   
- [Documentation](#documentation)   
- [Navigating SDK sample files](#navigating-sdk-sample-files)   
- [SDK Reference](#sdk-reference)   
- [Versioning](#versioning)   
- [Change log](#change-log)   
- [Frequently Asked Questions (FAQ)](#frequently-asked-questions-faq)   
- [Support](#support)   
- [License](#license)   
- [Acknowledgments](#acknowledgments)   


## Latest SDK News
1.  Starting from 5.2.41727.0928, the Windows SDK requires building with Visual Studio 2019.

2.  If you would like to run the Windows SDK demo app directly, you may install the VS2019 x86 runtime library(**vc_redist_x86.exe**) from the following:

    * https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads
    
3. Starting from Client SDK 5.0, if you are using tokens to start a meeting, you will only need to retrieve ZAK from Zoom API. The user token has been deprecated. 
4. To follow with Zoom client's recent changes, Zoom SDK has temporary remove the "Unmute All" interface in Client SDK 5.0.
5. To align with Zoom’s [recent announcement](https://blog.zoom.us/wordpress/2020/04/22/zoom-hits-milestone-on-90-day-security-plan-releases-zoom-5-0/) pertaining to our security initiative, Zoom Client SDKs have added **AES 256-bit GCM encryption** support, which provides more protection for meeting data and greater resistance to tampering. **The system-wide account enablement of AES 256-bit GCM encryption will take place on June 01, 2020.** You are **strongly recommended** to start the required upgrade to this latest version 4.6.21666.0428 at your earliest convenience. Please note that any Client SDK versions below 4.6.21666.0428 will **no longer be operational** from June 01.

6. **Starting from 4.6.15798.0403, all DLL files(\*.dll) and EXE files(\*.exe) cannot be re-signed. Please DO NOT re-sign or assign new digital signature to those files as assigning new digital signature on these files could lead to fatal errors.**

7. Our Zoom SDK and Zoom Client share some common resources in the OS, in order to allow Zoom client and Zoom client SDK app work at the same time, since v4.4.56616.1028, we renamed the filename of the following shared resources:
* `CptHost.exe` -> `zcscpthost.exe`
* `airhost.exe` -> `zcsairhost.exe`
* `CptService.exe` -> `zCSCptService.exe`

8. If you are using SDK versions before 4.6.15798.0403, kindly advise that **please do not re-sign / assign new digital signature to** the following files as assigning new digital signature on these files could lead to fatal errors:
   * **CptControl.exe**
   * **CptInstall.exe**
   * **CptHost.exe** / **zcscpthost.exe**
   * **airhost.exe** / **zcsairhost.exe**
   * **CptService.exe** / **zCSCptService.exe**
   * **CptShare.dll**
   * **zzhost.dll**
   * **zzplugin.dll**(Deprecated since v4.6.15074.0203)
   * **aomhost64.exe**
   * **zCrashReport.dll**
   * **libeay32.dll**
   * **ssleay32.dll**

## Full Documentation && Community Support
You can find the full Zoom Windows SDK documentation and the community support forum here:
<div align="center">
   <a target="_blank" href="https://marketplace.zoom.us/docs/sdk/native-sdks/windows" style="text-decoration:none">
   <img src="https://s3-us-west-1.amazonaws.com/sdk.zoom.us/Doc-button.png" width="350px" max-height="350px" style="margin:1vh 1vw;"/>
   </a>
   <a target="_blank" href="https://devforum.zoom.us/c/desktop-sdk" style="text-decoration:none">
   <img src="https://s3-us-west-1.amazonaws.com/sdk.zoom.us/Forum-button.png" width="350px" max-height="350px" style="margin:1vh 1vw;"/>
   </a>
</div>

## What is Zoom Windows SDK?
Zoom SDK makes it easy to integrate Zoom with your Windows applications, and boosts up your applications with the power of Zoom.

* **Easy to use**: Our SDK is built to be easy to use. Just import the libraries, call a few functions, and we will take care all video conferencing related stuffs for you.
* **Localizable**: Our SDK naturally supports [multiple major languages](https://support.zoom.us/hc/en-us/articles/209982306-Change-your-language-on-Zoom), and you can add more to grow your applications internationally.
* **Custom Meeting UI**: If you want to add your own decorations to your Zoom meeting rooms, try our Custom UI feature to make your meeting room special.

## Disclaimer

**Please be aware that all hard-coded variables and constants shown in the documentation and in the demo, such as Zoom Token, Zoom Access, Token, etc., are ONLY FOR DEMO AND TESTING PURPOSES. We STRONGLY DISCOURAGE the way of HARDCODING any Zoom Credentials (username, password, API Keys & secrets, SDK keys & secrets, etc.) or any Personal Identifiable Information (PII) inside your application. WE DON’T MAKE ANY COMMITMENTS ABOUT ANY LOSS CAUSED BY HARD-CODING CREDENTIALS OR SENSITIVE INFORMATION INSIDE YOUR APP WHEN DEVELOPING WITH OUR SDK**.

## Getting Started

The following instructions will get you a copy of the project up and running on your local machine for development and testing purposes.
* For detailed instructions, please refer to our documentation website: [https://marketplace.zoom.us/docs/sdk/native-sdks/windows](https://marketplace.zoom.us/docs/sdk/native-sdks/windows);
* If you need support or assistance, please visit our [Zoom Developer Community Forum](https://devforum.zoom.us/);

### Prerequisites

Before you try out our SDK, you would need the following to get started:

* **A Zoom Account**: If you do not have one, you can sign up at [https://zoom.us/signup](https://zoom.us/signup).
  * Once you have your Zoom Account, sign up for a 60-days free trial at [https://marketplace.zoom.us/](https://marketplace.zoom.us/)
* **A device with Windows OS**:
  * OS: Windows XP or later. Currently Windows 10 UWP is not supported.
  * Visual Studio 2019


### Installing

Clone or download a copy of our SDK files from GitHub. After you unzipped the file, you should have the following folders:

```
.
├── CHANGELOG.md
├── LICENSE.md
├── README.md
├── bin
├── h
├── lib
├── [sdk_demo] <-- demo app is inside
└── version.txt
```
Launch your **Visual Studio**, locate the `sdk_demo.vcproj` file, and open it.

The `DemoUI.cpp` file includes a high-level application which you can reference to understand how to call the stack functions and register call backs.

The Zoom SDK runs as a `DLL` in the context of the calling application process.

### Initializing SDK with JWT token
When initializing the SDK, you will need to compose a JWT token using your SDK key & secret.

* How to compose JWT token for SDK initialization

You may generate your JWT token using the online tool https://jwt.io/. **It is highly recommended to generate your JWT token in your backend server.**

JWT is generated with three core parts: Header, Payload, and Signature. When combined, these parts are separated by a period to form a token: aaaaa.bbbbb.cccc.

Please follow this template to compose your payload for SDK initialization:

** Header
```
{
  "alg": "HS256",
  "typ": "JWT"
}
```
** Payload
```
{
         "appKey": "string",     // Your SDK key
         "iat": long,   // access token issue timestamp (unit: second)
         "exp": long,  // access token expire timestamp, MAX: iat + 2 days (unit: second)
         "tokenExp": long // token expire timestamp, MIN:iat + 30 minutes (unit: second)
}
```
**The minimum value of `tokenExp` should be at least 30 minutes, otherwise, SDK will reject the authentication request.**
** Signature
```
HMACSHA256(
  base64UrlEncode(header) + "." +
  base64UrlEncode(payload),
  "Your SDK secret here"
)
```
You do not need to secret base64 encoded your signature. Once the JWT token is generated, please do not reveal it or publish it. **It is highly recommended to handle your SDK key and secret and generate JWT in a backend server to be consumed by your application. Do not generate JWT in a production application.**


## Documentation

Please visit [[https://marketplace.zoom.us/docs/sdk/native-sdks/windows](https://marketplace.zoom.us/docs/sdk/native-sdks/windows)] for details of each features and functions.

## Navigating SDK sample files

The following table provides the link to the implementation of each features in our demo app:

| UI mode            | Feature                                                      | Corresponding sample files                                   |
| ------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Essential features | SDK Initialization & Authentication                          | * [sdk_init_auth_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/sdk_init_auth_ui.cpp) <br />* [init_auth_sdk_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/init_auth_sdk_workflow.cpp) <br />* [sdk_util.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/sdk_util.cpp) |
|                    | Authenticate with Zoom REST API and start a meeting as API user | * [zoomHmacSHA256.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/zoomHmacSHA256.cpp) <br />* [httpRequestHelper.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/HttpRequestHelper.cpp) <br />* [login_sdk_login_UI.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/LOGIN_sdk_login_UI.cpp) <br />* [login_restapi_without_login_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/LOGIN_restapi_without_login_workflow.cpp) |
|                    | Login with email & password                                  | * [login_sdk_login_UI.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/LOGIN_sdk_login_UI.cpp) <br />* [login_login_with_email_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/LOGIN_login_with_email_workflow.cpp) |
|                    | Login with SSO token                                         | * [login_sdk_login_UI.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/LOGIN_sdk_login_UI.cpp) <br />* [login_login_with_sso_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/LOGIN_login_with_sso_workflow.cpp) |
|                    | Start an instant meeting(For Logged-in user)                 | * [loggedIn_sdk_controller.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/LoggedIn_sdk_controller_ui.cpp) <br />* [loggedIn_sdk_controller_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/LoggedIn_sdk_controller_workflow.cpp) |
|                    | Join a meeting                                               | * [join_meeting_for_login_user_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/Join_meeting_for_login_user_ui.cpp) <br />* [join_meeting_for_login_user_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/Join_meeting_for_login_user_workflow.cpp) <br />* [login_join_meeting_only_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/LOGIN_join_meeting_only_workflow.cpp) <br />* [sdk_util.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/sdk_util.cpp) |
|                    | Schedule a meeting (For logged-in user)                      | * [schedule_meeting_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/schedule_meeting_ui.cpp) <br />* [schedule_meeting_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/schedule_meeting_workflow.cpp) |
|                    | User management                                              | * [user_manager.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/user_manager.cpp) |
|                    | Settings                                                     | * [settings_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/settings_ui.cpp) <br />* [settings_audio_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/SETTINGS_audio_workflow.cpp) <br />* [settings_feature_custom_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/SETTINGS_feature_custom_workflow.cpp) <br />* [settings_general_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/SETTINGS_general_workflow.cpp) <br />* [settings_recording_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/SETTINGS_recording_workflow.cpp) <br />* [settings_ui_custom_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/SETTINGS_ui_custom_workflow.cpp) <br />* [settings_video_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/SETTINGS_video_workflow.cpp) <br />* [settings_virtualBG_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/SETTINGS_virtualBG_workflow.cpp) |
|                    | Invitation                                                   | * [invitation_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/invitation_ui.cpp) <br />* [invitation_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/invitation_workflow.cpp) |
| Custom UI          | Basic UI management                                          | * [custom_ui_mgr.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/custom_ui_mgr.cpp) <br />* [custom_ui_mgr_flow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/custom_ui_mgr_flow.cpp) |
|                    | Video                                                        | * [custom_ui_video_flow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/custom_ui_video_flow.cpp) <br />* [custom_ui_video_mgr.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/custom_ui_video_mgr.cpp) |
|                    | Share                                                        | * [custom_ui_share_flow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/custom_ui_share_flow.cpp) <br />* [custom_ui_share_mgr.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/custom_ui_share_mgr.cpp) |
|                    | Annotation                                                   | * [annotateBarWindow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/AnnotateBarWindow.cpp) <br />* [annotateClearWindow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/AnnotateClearWindow.cpp) <br />* [annotateDrawWindow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/AnnotateDrawWindow.cpp) <br />* [annotateFormatWindow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/AnnotateFormatWindow.cpp) <br />* [annotateSplotlightWindow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/AnnotateSpolightWindow.cpp) <br />* [annotateStampWindow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/AnnotateStampWindow.cpp) |
|                    | Arrow                                                        | * [arrow_window.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/arrow_window.cpp) |
|                    | Camera Control                                               | * [cameraControlWindow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/CameraControlWindow.cpp) |
|                    | Recording                                                    | * [customizedUIRecordMgr.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/CustomizedUIRecordMgr.cpp) |
|                    | Share Toolbar                                                | * [shareToolbarWindow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/ShareToolbarWindow.cpp) |
|                    | View Options                                                 | * [viewOptionsWindow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/ViewOptionsWindow.cpp) |
|                    | Chat                                                         | * [chat_controller_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/chat_controller_ui.cpp) <br />* [chat_controller_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/chat_controller_workflow.cpp) |
|                    | Close caption                                                | * [close_caption_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/close_caption_ui.cpp) <br />* [close_caption_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/close_caption_workflow.cpp) |
|                    | Dial-in country                                              | * [dial_in_country_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/dial_in_country_ui.cpp) |
|                    | Display CC                                                   | * [display_cc_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/display_cc_ui.cpp) |
|                    | Participant UI                                               | * [participant_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/participant_ui.cpp) |
|                    | Participant pop up menu                                      | * [participantPopMenu.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/ParticipantPopMenu.cpp) |
|                    | More features                                                | * [more_features_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/more_features_ui.cpp) <br />* [more_features_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/more_features_workflow.cpp) |
|                    | More menu                                                    | * [more_menu_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/more_menu_ui.cpp) |
|                    | Toolbar                                                      | * [toolbar_bottom_ui.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/toolbar_bottom_ui.cpp) <br />* [toolbar_bottom_workflow.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/toolbar_bottom_workflow.cpp) <br />* [toolbar_manager.cpp](https://github.com/zoom/zoom-sdk-windows/blob/6295059767afa50e42ca8a59ce797a3001684c87/demo/sdk_demo_v2/toolbar_manager.cpp) |

## SDK Reference

You may find the SDK interface reference at [https://marketplace.zoom.us/docs/sdk/native-sdks/windows/sdk-reference](https://marketplace.zoom.us/docs/sdk/native-sdks/windows/sdk-reference).
If you would like to get a local copy of the SDK reference, you may [download it here](https://github.com/zoom/zoom-sdk-windows/archive/gh-pages.zip).

## Versioning

For the versions available, see the [tags on this repository](https://github.com/zoom/zoom-sdk-windows/tags).

## Change log

Please refer to our [CHANGELOG](https://github.com/zoom/zoom-sdk-windows/blob/master/CHANGELOG.md) for all changes.

## Frequently Asked Questions (FAQ)

* :one: `Getting ERROR Code: 105035 while using Windows SDK`:
  * **In most of the cases, this is caused by resigning or adding new signature to the SDK DLL files(\*.dll) and EXE files(\*.exe)**

   **Please skip signing / do not add any new signatures to the DLL files(\*.dll) and EXE files(\*.exe). If the error code appears even if the files are not being re-signed, please visit our [Zoom Developer Community Forum](https://devforum.zoom.us/) and seek help.**


* Please visit our [Zoom Developer Community Forum](https://devforum.zoom.us/) for further assistance.

## Support

For any issues regarding our SDK, please visit our new Community Support Forum at https://devforum.zoom.us/.

## License

Use of this software is subject to important terms and conditions as set forth in the License file

Please refer to [LICENSE.pdf](LICENSE.pdf) file for details

## Acknowledgments

* :star: If you like our SDK, please give us a "Star". Your support is what keeps us moving forward and delivering happiness to you! Thanks a million! :smiley:
* If you need any support or assistance, we are here to help you: [Zoom Developer Community Forum](https://devforum.zoom.us/);

---
Copyright ©2020 Zoom Video Communications, Inc. All rights reserved.
