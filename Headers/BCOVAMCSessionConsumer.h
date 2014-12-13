//
//  BCOVAMCSessionConsumer.h
//  BCOVAMC
//
//  Copyright (c) 2014 Brightcove, Inc. All rights reserved.
//  License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

#import "BCOVAMCAnalyticsPolicy.h"

#import "BCOVPlaybackController.h"

#import "ADB_VHB_ErrorInfo.h"
#import "ADBMobile.h"

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
 * @param delegate An optional delegate confirmed with `BCOVAMCSessionConsumerHeartbeatDelegate`
 * protocol.
 * @return A session consumer specifies Adobe Heartbeat analytics.
 */

+ (instancetype)heartbeatAnalyticsConsumerWithPolicy:(BCOVAMCAnalyticsPolicy *)heartbeatPolicy delegate:(id<BCOVAMCSessionConsumerHeartbeatDelegate>)delegate;

/**
 * Returns a session consumer for Adobe video media analytics that is
 * initialized with a specified media policy and an optional delegate.
 *
 * @param heartbeatPolicy A `BCOVAMCAnalyticsPolicy` instance specifies Adobe
 * video media analytics.
 * @param delegate An optional delegate confirmed with `BCOVAMCSessionConsumerMeidaDelegate`
 * protocol.
 * @return A session consumer specifies Adobe media heartbeat analytics.
 */
+ (instancetype)mediaAnalyticsConsumerWithPolicy:(BCOVAMCAnalyticsPolicy *)mediaPolicy delegate:(id<BCOVAMCSessionConsumerMeidaDelegate>)delegate;

@end

@interface BCOVAMCSessionConsumer (Unavailable)

- (instancetype)init __attribute__((unavailable("Use `-[BCOVAMCSessionConsumer heartbeatAnalyticsConsumerWithPolicy:delegate:]` or `-[BCOVAMCSessionConsumer mediaAnalyticsConsumerWithPolicy:delegate:]` instead.")));

@end

/**
 * Methods which may be implemented by delegates of an AMC session comsumer 
 * specified for Adobe video heartbeat analytics.
 */
@protocol BCOVAMCSessionConsumerHeartbeatDelegate <NSObject>

@optional
/**
 * Called when `ADB_VHB_PlayerDelegate` received `onError:` message.
 *
 * @param session The playback session with AMC session comsumer
 * specified for Adobe video Heartbeat analytics who is received `onError:`
 * message.
 * @param errorInfo the `ADB_VHB_ErrorInfo` instance.
 */
- (void)heartbeatOnSession:(id<BCOVPlaybackSession>)session error:(ADB_VHB_ErrorInfo *)errorInfo;

/**
 * Called when `ADB_VHB_PlayerDelegate` received `onVideoUnloaded` message.
 *
 * @param session The playback session with AMC session comsumer
 * specified for Adobe video Heartbeat analytics who is received `onVideoUnloaded`
 * message.
 */
- (void)heartbeatVideoUnloadedOnSession:(id<BCOVPlaybackSession>)session;

@end

/**
 * Methods which may be implemented by delegates of an AMC session comsumer
 * specified for Adobe video Media analytics.
 */
@protocol BCOVAMCSessionConsumerMeidaDelegate <NSObject>

@optional
/**
 * Called evey second for providing the most recent medita state.
 *
 * @param session The playback session with AMC session comsumer
 * specified for Adobe video Media analytics.
 * @param mediaState the state of a media item.
 */
- (void)mediaOnSession:(id<BCOVPlaybackSession>)session mediaState:(ADBMediaState *)mediaState;

@end
