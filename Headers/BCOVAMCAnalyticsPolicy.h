//
//  BCOVAMCAnalyticsPolicy.h
//  BCOVAMC
//
//  Copyright (c) 2014 Brightcove, Inc. All rights reserved.
//  License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

#import "BCOVPlaybackSession.h"

#import "ADB_VHB_ConfigData.h"
#import "ADB_VHB_VideoInfo.h"

#import "ADBMobile.h"

/**
 * Each time a new playback session is ready to be processed, this
 * block is called and the session is passed in. The block must return a video
 * heartbeat configuration data that will be used to configure Adobe Heartbeat
 * for this new playback session.
 * If the block returns nil, Adobe Heartbeat will throw an illegal parameter
 * exception to configure heartbeat analytics.
 *
 * @param session The new playback session is ready to be processed.
 * @return The video heartbeat configuration data.
 */
typedef ADB_VHB_ConfigData * (^BCOVAMCVideoHeartbeatConfigurationPolicy)(id<BCOVPlaybackSession> session);

/**
 * Each time a new playback session is ready to be processed, this
 * block is called and the session is passed in. The block must return a video
 * info that will be used by Adobe video Heartbeat for this new playback session.
 * If the block returns nil, Adobe video Heartbeat will not collect and report 
 * video analytics.
 * The following properties of video info are optional and will be auto fill by 
 * `BCOVAMCSessionConsumer` instance: `length`, `playhead` and `streamType`.
 * 
 * @param session The new playback session is ready to be processed.
 * @return The video info of the new playback session for Adobe video Heartbeat.
 */
typedef ADB_VHB_VideoInfo * (^BCOVAMCVideoHeartbeatVideoInfoPolicy)(id<BCOVPlaybackSession> session);

/**
 * Each time a new playback session is ready to be processed, this
 * block is called and the session is passed in. The block must return a media
 * setting will be used to configure Adobe video media tracking for this new 
 * playback session.
 * If the block returns nil, Adobe video media tracking will not collect and 
 * report video analytics.
 * The `length` properties of media setting video can be initialized to `0` as 
 * live media and it will be updated by `BCOVAMCSessionConsumer` instance later.
 *
 * @param session The new playback session is ready to be processed.
 * @return The meida setting of the new playback session for Adobe media 
 * tracking.
 */
typedef ADBMediaSettings * (^BCOVAMCMediaSettingPolicy)(id<BCOVPlaybackSession> session);

/**
 * This policy allows clients to specify the configuration data required by 
 * Adobe video Heartbeat tracking, media tracking and video info.
 */

@interface BCOVAMCAnalyticsPolicy : NSObject

/*
 * Return a BCOVAMCVideoHeartbeatConfigurationPolicy that will be used for Adobe 
 * video Heartbeat configuration.
 *
 * @return a BCOVAMCVideoHeartbeatConfigurationPolicy that will be used for Adobe
 * video Heartbeat configuration
 */
@property (nonatomic, readonly, copy) BCOVAMCVideoHeartbeatConfigurationPolicy configurationPolicy;

/*
 * Return a BCOVAMCVideoHeartbeatVideoInfoPolicy to present video info for Adobe
 * Heartbeat.
 *
 * @return a BCOVAMCVideoHeartbeatVideoInfoPolicy to present video info for Adobe
 * Heartbeat.
 */
@property (nonatomic, readonly, copy) BCOVAMCVideoHeartbeatVideoInfoPolicy videoInfoPolicy;

/*
 * Return a BCOVAMCMediaSettingPolicy that will be used for Adobe media tracking 
 * setting.
 *
 * @return a BCOVAMCMediaSettingPolicy that will be used for Adobe media tracking
 * setting.
 */
@property (nonatomic, readonly, copy) BCOVAMCMediaSettingPolicy mediaSettingPolicy;

/**
 * Returns an initialized instance of BCOVCuePointProgressPolicy for Adobe video
 * Heartbeat with the specified `BCOVAMCVideoHeartbeatConfigurationPolicy` and `BCOVAMCVideoHeartbeatVideoInfoPolicy`.
 *
 * @param configurationPolicy a `BCOVAMCVideoHeartbeatConfigurationPolicy` that will be used for Adobe
 * video Heartbeat configuration.
 * @param videoInfoPolicy a `BCOVAMCVideoHeartbeatVideoInfoPolicy` to present video info for Adobe
 * Heartbeat
 */
- (instancetype)initWithHeartbeatConfigurationPolicy:(BCOVAMCVideoHeartbeatConfigurationPolicy)configurationPolicy videoInfoPolicy:(BCOVAMCVideoHeartbeatVideoInfoPolicy)videoInfoPolicy;

/**
 * Returns an initialized instance of BCOVCuePointProgressPolicy for Adobe media
 * tracking with the specified `BCOVAMCMediaSettingPolicy`.
 *
 * @param mediaSettingPolicy a `mediaSettingPolicy` that will be used for Adobe 
 * media tracking setting.
 */
- (instancetype)initWithMediaSettingsPolicy:(BCOVAMCMediaSettingPolicy)mediaSettingPolicy;

@end

@interface BCOVAMCAnalyticsPolicy (Unavailable)

- (instancetype)init __attribute__((unavailable("Use `-[BCOVAMCAnalyticsPolicy initWithHeartbeatConfigurationPolicy:videoInfoPolicy:]` or `-[BCOVAMCAnalyticsPolicy initWithMediaSettingsPolicy:]` instead.")));

@end
