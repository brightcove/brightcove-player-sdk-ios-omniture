# Omniture (Adobe Marketing Cloud - Adobe Analytics) Plugin for Brightcove Player SDK for iOS, version 6.3.11.455

Supported Platforms
===================

iOS 9.0 and above.

Installation
============

The Omniture plugin is a static library framework for iOS 8 and above.

The Omniture plugin currently supports Adobe Marketing Cloud v4.14.1 and Adobe Video Heartbeat v2.0.1. The Marketing Cloud and Video Heartbeat libraries **are not** included with this SDK and **must** be added manually to your project. Instructions for downloading the libraries are provided below.

CocoaPods
---------

You can use [CocoaPods][cocoapods] version 1.0 or higher to add the Omniture plugin to your project.  You can find the latest `Brightcove-Player-Omniture` podspec [here][podspecs]. To use this spec, add the following to the top of your Podfile: `source 'https://github.com/brightcove/BCOVSpecs.git'`.

Static Framework example:

```
source 'https://github.com/brightcove/BrightcoveSpecs.git'

pod 'Brightcove-Player-Omniture'
```

When updating your installation, it's a good idea to refresh the local copy of your BrightcoveSpecs repository so that you have the latest podspecs locally, just like you would update your CococaPods master repository.

Typically if you use `pod update` in Terminal this will happen automatically, or alternatively you can update explicitly with `pod repo update brightcove`. (Your BrightcoveSpecs repository may have a different name if you explicitly added it to your list of podspecs repos.)

Manual
------

To add the Omniture Plugin for Brightcove Player SDK to your project manually:

1. Install the latest version of the [Brightcove Player SDK][bcovsdk].
2. Download the latest zip'ed release of the plugin from the [release page][release].
3. Add the `BrightcoveAMC.framework` project.
4. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the path to the framework. This should have been done automatically unless the framework is stored under a different root directory than your project.
5. On the "Build Phases" tab of your application target, add the following to the "Link
    Binary With Libraries" phase:
    * `BrightcoveAMC.framework`
6. On the "Build Settings" tab of your application target:
    * Ensure that `-ObjC` has been added to the "Other Linker Flags" build setting.
7. Download Adobe Marketing Cloud following Adobe's [instructions][adobemarketingcloud] and add `AdobeMobileLibrary.a` to your project.
8. Download Adobe Video Heartbeat following Adobe's [instructions][adobevideoheartbeat] and add `VideoHeartbeat.a` to your project.
9. Add the Marketing Cloud and Video Heartbeat header folders to the Header Search Path settings of your project.

[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/brightcove/BrightcoveSpecs/tree/master/Brightcove-Player-Omniture
[release]: https://github.com/brightcove/brightcove-player-sdk-ios-omniture/releases

[adobemarketingcloud]: https://marketing.adobe.com/developer/gallery/app-measurement-for-ios
[adobevideoheartbeat]: https://marketing.adobe.com/resources/help/en_US/sc/appmeasurement/hbvideo/ios_2.0

Quick Start
===========
BrightcoveAMC is a bridge between the [Brightcove Player SDK for iOS][bcovsdk] and Adobe video tracking, including [Adobe Video Heartbeat v2][adobevideoheartbeat] and [Adobe Media Tracking v4][adobemobileservice]. BrightcoveAMC tracks basic video behaviors: video ready, video completed, video play, and video pause. 

Client Implementation
=====================
To setup Adobe Video Heartbeat, Omniture Plugin clients need to implement instances of BCOVAMCVideoHeartbeatConfigurationPolicy. To setup Adobe Media Tracking, an instance of BCOVAMCMediaSettingPolicy is required. These [policies][strategypattern] allow for customization of ADBMediaHeartbeatConfig or ADBMediaSettings objects for each playback session.

[strategypattern]: https://en.wikipedia.org/wiki/Strategy_pattern

Video Heartbeat v2
------------------

This example uses video heartbeat tracking.


    [1] // Create the VHB configuration policy object.
        BCOVAMCVideoHeartbeatConfigurationPolicy videoHeartbeatConfigurationPolicy = ^ADBMediaHeartbeatConfig *(id<BCOVPlaybackSession> session) {

            ADBMediaHeartbeatConfig *configData = [[ADBMediaHeartbeatConfig alloc] init];
            
            configData.trackingServer = <adobe-assigned_tracking_server>";
            configData.channel = <cutomize_sample_channel>;
            configData.appVersion = <app_version>;
            configData.ovp = <online_video_platform>;
            configData.playerName = <player_name>;
            configData.ssl = <YES | NO>;

            // Set debugLogging to true to activate debug tracing. Remove it in production.
            configData.debugLogging = YES;
            
            return configData;
        };

    [2] // Create the Brightcove AMC analytics policy object fromw1w the VHB configuration policy object.
        BCOVAMCAnalyticsPolicy *heartbeatPolicy = [[BCOVAMCAnalyticsPolicy alloc] initWithHeartbeatConfigurationPolicy:videoHeartbeatConfigPolicy];
    
        BCOVAMCSessionConsumer *sessionConsumer = [BCOVAMCSessionConsumer heartbeatAnalyticsConsumerWithPolicy:heartbeatPolicy delegate:self];
   	   
        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
        id<BCOVPlaybackController> controller = [manager createPlaybackController];
        controller.delegate = self;
        [self.view addSubview:controller.view];
       
    [3] // Add the Brightcove AMC session consumer to the playback controller.
        [controller addSessionConsumer:sessionConsumer];       

    [4] // Find and play a video.
        NSString *policyKey = <your-policy-key>;
        NSString *accountId = <your-account-id>;
        NSString *videoID = <your-video-id>;
        BCOVPlaybackService *service = [[BCOVPlaybackService alloc] initWithAccountId:accountId
                                                                            policyKey:policyKey];
        [service findVideoWithVideoID:videoID
                           parameters:nil
                           completion:^(BCOVVideo    *video,
                                        NSDictionary *jsonResponse,
                                        NSError      *error) {

            [controller setVideos:@[ video ]];
            [controller play];

        }];
       
1. Create the video heartbeat configuration policy block which will be called at the start of each playback session. The policy allows for customization of configuration data based on the current session.
1. Use the configuration policy block to create and initialize a BCOVAMCAnalyticsPolicy instance with `-[initWithHeartbeatConfigurationPolicy:]`. The BCOVAMCAnalyticsPolicy object is used to create the BCOVAMCSessionConsumer.
1. After the playback controller is created, call the add session consumer method, `-[addSessionConsumer:]`, to add the AMC session consumer.

Marketing Cloud
---------------

This example uses media tracking.



    [1] BCOVAMCMediaSettingPolicy mediaSettingPolicy = ^ADBMediaSettings *(id<BCOVPlaybackSession> session) {
	
            ADBMediaSettings *settings = [ADBMobile mediaCreateSettingsWithName:<cutomize_setting_name>
    [2]                                                                  length:0
                                                                     playerName:<cutomize_player_name>
                                                                       playerID:<cutomize_player_ID>];
    [3]     settings.milestones = @"25,50,75"; // a customization.
            return settings;

        };

    [4] BBCOVAMCAnalyticsPolicy *mediaPolicy = [[BCOVAMCAnalyticsPolicy alloc] initWithMediaSettingsPolicy:mediaSettingPolicy];
    
        BCOVAMCSessionConsumer *sessionConsumer = [BCOVAMCSessionConsumer mediaAnalyticsConsumerWithPolicy:mediaPolicy
                                                                                                  delegate:self];

        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
        id<BCOVPlaybackController> controller = [manager createPlaybackController];
        controller.delegate = self;
        [self.view addSubview:controller.view];
       
    [5] [controller addSessionConsumer:sessionConsumer];       

        NSString *policyKey = <your-policy-key>;
        NSString *accountId = <your-account-id>;
        NSString *videoID = <your-video-id>;
        BCOVPlaybackService *service = [[BCOVPlaybackService alloc] initWithAccountId:accountId
                                                                            policyKey:policyKey];
        [service findVideoWithVideoID:videoID
                           parameters:nil
                           completion:^(BCOVVideo    *video,
                                        NSDictionary *jsonResponse,
                                        NSError      *error) {

            [controller setVideos:@[ video ]];
            [controller play];

        }];
       


1. Create the media settings policy block which will be called at the start of each playback session. The policy allows for customization of media settings based on the current session.
1. When creating the ADBMediaSettings instance with a class method of ADBMobile `+[mediaCreateSettingsWithName:length:playerName:playerID:]`, you can set **video length** to **0**. The Omniture plugin will update it later.
1. Add optional settings such as milestones. 
1. Use the media settings policy block to create and initialize a BCOVAMCAnalyticsPolicy instance with `-[initWithMediaSettingsPolicy:]`. The policy object is used to create an AMC session consumer for Adobe media tracking as `+[mediaAnalyticsConsumerWithPolicy:delegate:]`.
1. After the playback controller is created, call the add session consumer method, `-[addSessionConsumer:]`, to add the AMC session consumer.

Adobe-Marketing-Cloud.git
=========================

To fetch the Adobe Marketing Cloud libraries, run the following:

```
git clone -b v4.14.1-iOS --single-branch https://github.com/Adobe-Marketing-Cloud/mobile-services.git
git clone -b ios-v2.0.1 --single-branch https://github.com/Adobe-Marketing-Cloud/video-heartbeat-v2.git
```


----
If you have questions or need help, visit the [support forum for Brightcove's Native Player SDKs][forum].

[adobeheartbeat]: https://github.com/Adobe-Marketing-Cloud/video-heartbeat/
[adobemobileservice]: https://github.com/Adobe-Marketing-Cloud/mobile-services
[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios
[forum]: https://groups.google.com/forum/#!forum/brightcove-native-player-sdks
