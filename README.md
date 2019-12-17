# Zoom Windows Software Development Kit (SDK)
<div align="center">
<img src="https://s3.amazonaws.com/user-content.stoplight.io/8987/1541013063688" width="400px" max-height="400px" style="margin:auto;"/>
</div>

## Latest SDK Notifications
1.Our Zoom SDK and Zoom Client share some common resources in the OS, in order to allow Zoom client and Zoom client SDK app work at the same time, we renamed the filename of the following shared resources:
* `CptHost.exe` -> `zcscpthost.exe`
* `airhost.exe` -> `zcsairhost.exe`
* `CptService.exe` -> `zCSCptService.exe`
2. Kindly advise that **please do not re-sign / assign new digital signature to** the following files as assigning new digital signature on these files could lead to fatal errors:
   * **CptControl.exe**
   * **CptHost.exe**
   * **CptInstall.exe**
   * **CptService.exe**
   * **CptShare.dll**
   * **zzhost.dll**
   * **zzplugin.dll**
   * **aomhost64.exe**
3. **Variable Name Changes**: Since [v4.3.1.47204.0325](https://github.com/zoom/zoom-sdk-windows/releases/tag/v4.3.1.47204.0325), we have renamed the term "APP" to "SDK" in our demo to avoid confusion between the term "API" and "APP".
4. Our brand new [Zoom Developer Community Forum](https://devforum.zoom.us/) is now online!!! Check it out! We are here to help! :D

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
* **Localizable**: Our SDK naturally supports 7 major languages, and you can add more to grow your applications internationally.
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


## Documentation

Please visit [[https://marketplace.zoom.us/docs/sdk/native-sdks/windows](https://marketplace.zoom.us/docs/sdk/native-sdks/windows)] for details of each features and functions.

## SDK Reference

You may find the SDK interface reference at [https://marketplace.zoom.us/docs/sdk/native-sdks/windows/sdk-reference](https://marketplace.zoom.us/docs/sdk/native-sdks/windows/sdk-reference).
If you would like to get a local copy of the SDK reference, you may [download it here](https://github.com/zoom/zoom-sdk-windows/archive/gh-pages.zip).

## Versioning

For the versions available, see the [tags on this repository](https://github.com/zoom/zoom-sdk-windows/tags).

## Change log

Please refer to our [CHANGELOG](https://github.com/zoom/zoom-sdk-windows/blob/master/CHANGELOG.md) for all changes.

## Frequently Asked Questions (FAQ)

* :one: `Getting ERROR Code: 105035 while using Windows SDK`:
  * **In most of the cases, this is caused by resigning or adding new signature to the following files while integrating and deploying our SDK**:
     * **CptControl.exe**
     * **CptHost.exe**
     * **CptInstall.exe**
     * **CptService.exe**
     * **CptShare.dll**
     * **zzhost.dll**
     * **zzplugin.dll**
     * **aomhost64.exe**
   
   **Please skip signing / do not add any new signatures to the above files. If the error code appears even if the above files are not being re-signed, please visit our [Zoom Developer Community Forum](https://devforum.zoom.us/) and seek help.**
   
   
* Please visit our [Zoom Developer Community Forum](https://devforum.zoom.us/) for further assistance.

## Support

For any issues regarding our SDK, please visit our new Community Support Forum at https://devforum.zoom.us/.

## License

Use of this software is subject to important terms and conditions as set forth in the License file

Please refer to [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* :star: If you like our SDK, please give us a "Star". Your support is what keeps us moving forward and delivering happiness to you! Thanks a million! :smiley:
* If you need any support or assistance, we are here to help you: [Zoom Developer Community Forum](https://devforum.zoom.us/);

---
Copyright ©2019 Zoom Video Communications, Inc. All rights reserved.
