
# Table of Contents

1.  [What Does It Do?](#org26e09fb)
2.  [How To Run This?](#orga3ed773)
    1.  [Recording](#org790284f)
    2.  [Dependency](#org1154e95)
    3.  [Hack](#org139f86d)
    4.  [Command Line Parameters](#org2d74af2)
3.  [Status of This App](#org6ebe7c9)
4.  [Code Structure](#orgc1ded8a)
5.  [How To View Recordings](#org1c7aa45)
6.  [Extra Info](#orgfb677e7)

Zoom has many different client SDKs, among all available one, the only thing
that we could possibly use on a cloud setup is the Windows SDK. This project is
a modified version of the original SDK under demo/sdk<sub>demo</sub>, and renamed as
*recorder*.


<a id="org26e09fb"></a>

# What Does It Do?

This is a windows application which does the following:

-   join a conference with a given ID
-   start to tap into audio and video streams once the meeting starts
-   TODO: open a Win32 pipes (shared memory) to communicate with recording process
    which does the video composition as well as H264 encoding.
-   once meeting ends, the process should just die


<a id="orga3ed773"></a>

# How To Run This?

This is built with Visual Studio 2019. Please note that only **Release** version
built. (Same as the original demo/sdk<sub>demo</sub>). To run this, just open
zoom-recorder.sln and run from there. Once successfully built, a binary will be
dropped to bin/ folder.


<a id="org790284f"></a>

## Recording

The recording capability is done with a unpublished RAW data access API that we
got from Zoom development team. Currently, it&rsquo;s not possible to run this with a
corp account (That&rsquo;s a bug that they are trying to address). So for now, please
use the credential specified in the sln file.


<a id="org1154e95"></a>

## Dependency

-   This depends on files under bin/. Please note that you can&rsquo;t run both recorder/

and demo/sdk<sub>demo</sub> at the same time, as they both will try to modify files under
bin/ and causes random crashes.

-   There is no requirement of having a mic or camera at all.


<a id="org139f86d"></a>

## Hack

In the original SDK, there is a limitation that a single machine can only run
one instance of SDK. What they did was to create a global named event and
detected if it exists already. Based on my understanding, container has no its
own kernel object namespace (I could be wrong on this one). So the only way for
us to run this is to have a single VM to run one SDK. VM preparation is usually
on demand, but can take couple minutes based on my experience with azure. So I
implemented a hack which is to kill this Event handle during the process
initialization phase. This so far works well and allows us to run multiple SDK
instances on a given machine.


<a id="org2d74af2"></a>

## Command Line Parameters

This tool supports a rich set of command line options. Many of them are added
during the phase when I don&rsquo;t fully understand zoom&rsquo;s authentication model. I
believe at the time when we need to go production, we will have to send
username/password of a given user which has the special RAW api privilege turned on.


<a id="org6ebe7c9"></a>

# Status of This App

-   Currently, this will write file to c:\temp\audio.bin, video.bin, and
    video.meta.
-   The code quality is for prototyping. So there are still a bit work to be done
    to make it production quality. However, since this is NOT a long running


<a id="orgc1ded8a"></a>

# Code Structure

Main.cpp has a window message loop which is required as the underneath Zoom SDK
is a UX app. Most of our code changes happen in *MeetingServiceMgr.cpp*


<a id="org1c7aa45"></a>

# How To View Recordings

-   For audio, it&rsquo;s recorded as 32k, single channel, PCM data. I have used
    Audacity to listen to the file
-   For video, I use [PYUV](http://dsplab.diei.unipg.it/software/pyuv_raw_video_sequence_player) to view the recording. The format is YUV, 420, 640X480

I have verified both work.


<a id="orgfb677e7"></a>

# Extra Info

Please see [ZOOM original README](https://github.com/zoom/zoom-sdk-windows/blob/master/README.md)
