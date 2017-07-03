//
// BCOVAMCSessionConsumer.h
// BrightcoveAMC
//
// Copyright (c) 2017 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

#import <BrightcovePlayerSDK/BCOVPlaybackController.h>

#import "BCOVAMCAnalyticsPolicy.h"


// Adobe Mobile Marketing Cloud
@class ADBMobile;


@protocol BCOVAMCSessionConsumerHeartbeatDelegate;
@protocol BCOVAMCSessionConsumerMeidaDelegate;


/**
 * The BCOVAMCSessionConsumer instance takes care of everything related to 
 * reporting Adobe marketing cloud video ananlytics.
 */

@interface BCOVAMCSessionConsumer : NSObject <BCOVPlaybackSessionConsumer>

/**
 * Returns a session consumer for Adobe video Heartbeat that is
 * initialized with a specified heartheat policy and an optional delegate.
 *
 * @param heartbeatPolicy A `BCOVAMCAnalyticsPolicy` instance specifies Adobe
 * Heartbeat analytics.
 * @param delegate An optional delegate conforming to the
 * `BCOVAMCSessionConsumerHeartbeatDelegate` protocol.
 * @return A session consumer specifies Adobe Heartbeat analytics.
 */

+ (instancetype)heartbeatAnalyticsConsumerWithPolicy:(BCOVAMCAnalyticsPolicy *)heartbeatPolicy delegate:(id<BCOVAMCSessionConsumerHeartbeatDelegate>)delegate;

/**
 * Returns a session consumer for Adobe video media analytics that is
 * initialized with a specified media policy and an optional delegate.
 *
 * @param heartbeatPolicy A `BCOVAMCAnalyticsPolicy` instance specifies Adobe
 * video media analytics.
 * @param delegate An optional delegate conforming to the
 * `BCOVAMCSessionConsumerMeidaDelegate` protocol.
 * @return A session consumer specifies Adobe media heartbeat analytics.
 */
+ (instancetype)mediaAnalyticsConsumerWithPolicy:(BCOVAMCAnalyticsPolicy *)mediaPolicy delegate:(id<BCOVAMCSessionConsumerMeidaDelegate>)delegate;

@end

@interface BCOVAMCSessionConsumer (Unavailable)

- (instancetype)init __attribute__((unavailable("Use `-[BCOVAMCSessionConsumer heartbeatAnalyticsConsumerWithPolicy:delegate:]` or `-[BCOVAMCSessionConsumer mediaAnalyticsConsumerWithPolicy:delegate:]` instead.")));

@end

/**
 * Optional methods which may be implemented by delegates of an AMC session
 * comsumer for Adobe video heartbeat analytics.
 */
@protocol BCOVAMCSessionConsumerHeartbeatDelegate <NSObject>

@optional

/**
 * Called when `ADB_VHB_PlayerDelegate` received `onVideoUnloaded` message.
 *
 * @param session The playback session with AMC session comsumer specified for
 * Adobe video Heartbeat analytics which receives the `onVideoUnloaded`
 * message.
 */
- (void)heartbeatVideoUnloadedOnSession:(id<BCOVPlaybackSession>)session;

@end

/**
 * Optional methods which may be implemented by delegates of an AMC session
 * comsumer for Adobe video Media analytics.
 */
@protocol BCOVAMCSessionConsumerMeidaDelegate <NSObject>

@optional

/**
 * Called every second in order to provide the most recent medita state.
 *
 * @param session The playback session with AMC session comsumer
 * specified for Adobe video Media analytics.
 * @param mediaState the state of a media item.
 */
- (void)mediaOnSession:(id<BCOVPlaybackSession>)session mediaState:(ADBMediaState *)mediaState;

@end
