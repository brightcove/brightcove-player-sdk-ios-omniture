# BCOVAMC Plugin for Brightcove Player SDK for iOS, version 1.0.3.82

Installation
============

You can use [Cocoapods][cocoapods] to add the Omniture (Adobe Marketing Cloud - Adobe Analytics) Plugin for Brightcove Player SDK to your project. You can find the latest `Brightcove-Player-SDK-Omniture` podspec [here][podspecs]. To use this spec, using Cocoapods 0.34.1+, add the following to the top of Podfile: source 'https://github.com/brightcove/BCOVSpecs.git'.

The Adobe Mobile Service library and Adobe Video Heartbeat library **are not** included in this pod.  You **must** manually add the Adobe Video Heartbeat library VideoHeartbeat.a to your project. The pod will however add all the libraries required by this framework.

To add the Omniture Plugin for Brightcove Player SDK to your project manually:

1. Install the latest version of the [Brightcove Player SDK][bcovsdk].
1. Download the latest zip'ed release of the plugin from our [release page][release].
1. Add the contents of Library and Headers to the project.
1. On the "Build Phases" tab of your application target, add the following to the "Link
    Binary With Libraries" phase:
    * `libBCOVAMC.a`
1. On the "Build Settings" tab of your application target:
    * Ensure that BCOVAMC headers are in your application's "Header Search Path".
    * Ensure that `-ObjC` has been added to the "Other Linker Flags" build setting.
1. Install Adobe Video Heartbeat library v1.4.1.2, including VideoHeartbeat and AdobeAnalyticsPlugin, following their [directions][adobeheartbeat].
1. Install Adobe Mobile Service library v4.3.0, following their [directions][adobemobileservice]

[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/brightcove/BCOVSpecs/blob/master/Brightcove-Player-SDK-Omniture/1.0.0/Brightcove-Player-SDK-Omniture.podspec
[release]: https://github.com/brightcove/brightcove-player-sdk-ios-omniture/releases

Quick Start
===========
BCOVAMC is a bridge between the [Brightcove Player SDK for iOS][bcovsdk] and Adobe video tracking, including [Adobe Video Heartbeat v3][adobeheartbeat] and [Adobe Media Tracking v4][adobemobileservice]. BCOVAMC will track basic video behaviors as default: video ready, video completed, video play, and video pause. Its use is relatively straightforward. 

##Client Implementation
===========
To setup Adobe Video Heartbeat, Omniture Plugin clients need to implement instances of BCOVAMCVideoHeartbeatConfigurationPolicy and BCOVAMCVideoHeartbeatVideoInfoPolicy or to setup Adobe Media Tracking an instance of BCOVAMCMediaSettingPolicy is required. These policies allow for customization of ADB\_VHB\_ConfigData, ADB\_VHB\_VideoInfo, and ADBMediaSettings objects for each session. If you want to add specific video info such as video ID into ADB\_VHB\_ConfigData, ADB\_VHB\_VideoInfo, or ADBMediaSettings you can use the video's properties dictionary, `session.video.properties[<key>]`.

##Video Heartbeat
===========

This example uses video heartbeat tracking.



    [1] BCOVAMCVideoHeartbeatConfigurationPolicy heartbeatConfigPolicy = ^ADB_VHB_ConfigData *(id<BCOVPlaybackSession> session) {

            ADB_VHB_ConfigData *configData = [[ADB_VHB_ConfigData alloc] initWithTrackingServer:<cutomize_sample_server> jobId:<cutomize_sample_job> publisher:<cutomize_sample_publisher>];
            configData.channel = <cutomize_sample_channel>;

            // Set this to true to activate the debug tracing.
            // NOTE: remove this in production code.
            configData.debugLogging = YES;
            return configData;

            };

        BCOVAMCVideoHeartbeatVideoInfoPolicy videoInfoPolicy = ^ADB_VHB_VideoInfo *(id<BCOVPlaybackSession> session) {

        [2] NSString *videoID = session.video.properties[kBCOVCatalogJSONKeyId]; // Retrieve or create a video ID for each session.

            ADB_VHB_VideoInfo *videoInfo = [[ADB_VHB_VideoInfo alloc] init];
            videoInfo.id = videoID;
            videoInfo.name = videoID;
            videoInfo.playerName = <cutomize_player_name>;
            return videoInfo;
    
            };

    [3] BCOVAMCAnalyticsPolicy *heartbeatPolicy = [[BCOVAMCAnalyticsPolicy alloc] initWithHeartbeatConfigurationPolicy: heartbeatConfigPolicy videoInfoPolicy: videoInfoPolicy];
        BCOVAMCSessionConsumer *sessionConsumer = [BCOVAMCSessionConsumer heartbeatAnalyticsConsumerWithPolicy:heartbeatPolicy delegate:self];
   	   
        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
        id<BCOVPlaybackController> controller = [manager createPlaybackControllerWithViewStrategy:[manager defaultControlsViewStrategy]];
        controller.delegate = self;
        [self.view addSubview:controller.view];
       
    [4] [controller addSessionConsumer: sessionConsumer];       

        NSString *token;      // (Brightcove Media API token with URL access)
        NSString *playlistID; // (ID of the playlist you wish to use)
        BCOVCatalogService *catalog = [[BCOVCatalogService alloc] initWithToken:token];
        [catalog findPlaylistWithPlaylistID:playlistID
                                 parameters:nil
                                 completion:^(BCOVPlaylist *playlist,
                                              NSDictionary *jsonResponse,
                                              NSError      *error) {
            [controller setVideos:playlist];
            [controller play];

        }];
       


Let's break this code down into steps, to make it a bit simpler to digest:

1. You create the video heartbeat configuration policy and video info policy block for each session. These policies allow for customization of configuration and video info. They are executed once per session.
1. videoID can be customized for each session, but the simplest way is using video's properties dictionary with either `kBCOVCatalogJSONKeyId` or `kBCOVCatalogJSONKeyReferenceId`.
1. Use the configuration policy and video info policy blocks to create and initialize a BCOVAMCAnalyticsPolicy instance with `-[initWithHeartbeatConfigurationPolicy:videoInfoPolicy:]`. The BCOVAMCAnalyticsPolicy policy is used to create the BCOVAMCSessionConsumer.
1. After controller is created, you can use add session consumer method, `-[addSessionConsumer:]`, to add an AMC session consumer.

##Media tracking
===========

This example uses media tracking.



    [1] BCOVAMCMediaSettingPolicy mediaSettingPolicy = ^ADBMediaSettings *(id<BCOVPlaybackSession> session) {
	
            ADBMediaSettings *settings = [ADBMobile mediaCreateSettingsWithName:<cutomize_setting_name>
    [2]                                                                  length:0
                                                                     playerName:<cutomize_player_name>
                                                                       playerID:<cutomize_player_ID>];
    [3]     settings.milestones = @"25,50,75";
            return settings;

        };

    [4] BBCOVAMCAnalyticsPolicy *mediaPolicy = [[BCOVAMCAnalyticsPolicy alloc] initWithMediaSettingsPolicy:mediaSettingPolicy];
        BCOVAMCSessionConsumer *sessionConsumer = [BCOVAMCSessionConsumer mediaAnalyticsConsumerWithPolicy:mediaPolicy delegate:self];

        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
        id<BCOVPlaybackController> controller = [manager createPlaybackControllerWithViewStrategy:[manager defaultControlsViewStrategy]];
        controller.delegate = self;
        [self.view addSubview:controller.view];
       
    [5] [controller addSessionConsumer: sessionConsumer];       

        NSString *token;      // (Brightcove Media API token with URL access)
        NSString *playlistID; // (ID of the playlist you wish to use)
        BCOVCatalogService *catalog = [[BCOVCatalogService alloc] initWithToken:token];
        [catalog findPlaylistWithPlaylistID:playlistID
                                 parameters:nil
                                 completion:^(BCOVPlaylist *playlist,
                                              NSDictionary *jsonResponse,
                                              NSError      *error) {
            [controller setVideos:playlist];
            [controller play];

        }];
       


Although the process of media tracking is very similar to video heartbeat, let's break this code down into steps, to make it a bit simpler to digest:

1. You create the media tracking setting policy block for each session. Each session will be passed to the block for customizing tracking setting.
1. When creating the ADBMobileSetting instance with a class method of ADBMobile `+[mediaCreateSettingsWithName:length:playerName:playerID:]`, you can set **video length** to **0**. Omniture plugin will update it later for you.
1. You can add other optional setting, such as milestones. 
1. Use media tracking setting policy block to create and initialize BCOVAMCAnalyticsPolicy instance with `-[initWithMediaSettingsPolicy:]`. Then it can be used for creating an AMC session consumer for Adobe media tracking as `+[mediaAnalyticsConsumerWithPolicy:delegate:]`.
1. After controller is created, you can use add session consumer method, `-[addSessionConsumer:]`, to add an AMC session consumer.

If you have questions or need help, we have a support forum for Brightcove's native Player SDKs at [https://groups.google.com/forum/#!forum/brightcove-native-player-sdks][forum].

[adobeheartbeat]: https://github.com/Adobe-Marketing-Cloud/video-heartbeat/
[adobemobileservice]: https://github.com/Adobe-Marketing-Cloud/mobile-services
[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios
[forum]: https://groups.google.com/forum/#!forum/brightcove-native-player-sdks
