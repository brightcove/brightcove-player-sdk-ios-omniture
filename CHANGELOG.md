# Please Note:
* As of v1.1.0, the Brightcove Omniture plugin requires version 5.1.0 or higher of the [Brightcove Player SDK for iOS](https://github.com/brightcove/brightcove-player-sdk-ios/releases).

# 1.1.0
### Additions and Improvements
* The Omniture plugin is now packaged as a static framework.
* The plugin now supports Adobe Marketing Cloud v4.11.1 and Adobe Video Heartbeat v2.0.0.

### Breaking Changes
* The Omniture plugin now requires version 5.1.0 or higher of the Brightcove Player SDK for iOS.
* Support for Video Heartbeat v2.0.0. necessitates minor changes in the Omniture SDK API.
 * The `initWithHeartbeatConfigurationPolicy` method of the `BCOVAMCAnalyticsPolicy` class has changed to reflect the v2.0.0 Adobe Video Heartbeat API.
 * The `-heartbeatOnSession:error:` method of the `BCOVAMCSessionConsumerHeartbeatDelegate` protocol has been removed. See the README.md file and native [sample projects](https://github.com/BrightcoveOS/ios-player-samples) for details.

# 1.0.3
### Additions and Improvements
* Fixed a bug of tracking completed event and video unload event. Now completed event is for a video complete; video unload event is for a playback session complete.

# 1.0.2
### Additions and Improvements
* Fixed a bug that caused by Adobe VideoHeartbeat 1.4.0 library (linkage issue).
* Qualified with Adobe VideoHeartbeat 1.4.1.2.

# 1.0.1

### Additions and Improvements
* Fixed a bug that caused the tracking of video play events to be done incorrectly. 
