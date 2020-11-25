//
//  Copyright © 2011-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// Detects any iPad.
PSPDF_APP_EXPORT BOOL PSPDFIsiPad(void) NS_SWIFT_NAME(isiPad());

/// Returns YES if the application is compiled as Mac Catalyst. Useful in Swift code as a boolean check.
PSPDF_APP_EXPORT BOOL PSPDFIsMacCatalyst(void) NS_SWIFT_NAME(isMacCatalyst());

/// Returns YES if the application is compiled as Mac Catalyst and running on macOS Big Sur. 11.0.
PSPDF_APP_EXPORT BOOL PSPDFIsMacCatalyst11(void) NS_SWIFT_NAME(isMacCatalyst11());

/// Returns YES if the application is compiled as Mac Catalyst and running on macOS Big Sur 11.0 AND using Optimized for Mac Idiom.
PSPDF_APP_EXPORT BOOL PSPDFIsMacCatalystOptimized(void) NS_SWIFT_NAME(isMacCatalystOptimized());

/// Returns YES if the application is running on macOS (Not Catalyst)
PSPDF_APP_EXPORT BOOL PSPDFIsMacOS(void) NS_SWIFT_NAME(isMacOS());

/// Simulator detection.
PSPDF_APP_EXPORT BOOL PSPDFIsSimulator(void) NS_SWIFT_NAME(isSimulator());

/// Returns YES if this instance is a development build. Will always return YES in the Simulator.
PSPDF_EXTERN BOOL PSPDFIsDevelopmentBuild(void) NS_SWIFT_NAME(isDevelopmentBuild());

/// Detect if we run inside an app extension.
PSPDF_SDK_EXPORT BOOL PSPDFRunningInAppExtension(void) NS_SWIFT_NAME(isRunningInAppExtension());

/// Detects a 5.5" iPhone Plus. Almost certainly don’t want this in new code.
PSPDF_SDK_EXPORT BOOL PSPDFIsiPhone_5_5(void) NS_SWIFT_NAME(isiPhone_5_5());

/// Checks if `key` is set inside the main bundle info dictionary.
/// `reason` will be part of the explanatory log message.
PSPDF_SDK_EXPORT BOOL PSPDFCheckUsageDescriptionKey(NSString *key, NSString *reason);

// If iOS 11+ specific API is used, this needs to be acknowledged.
#define PSPDF_PARTIAL_AVAILABILITY_BEGIN _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wpartial-availability\"")

#define PSPDF_PARTIAL_AVAILABILITY_END _Pragma("clang diagnostic pop")

// If iOS 13.4 specific API is used, this needs to be acknowledged.
#define PSPDF_UNGUARDED_AVAILABILITY(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wunguarded-availability-new\"") expression _Pragma("clang diagnostic pop")

#define PSPDF_UNGUARDED_AVAILABILITY_BEGIN _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wunguarded-availability-new\"")

#define PSPDF_UNGUARDED_AVAILABILITY_END _Pragma("clang diagnostic pop")

// Remove this when Catalyst is also on the iOS 14 SDK (expected October 2020).
#ifdef __IPHONE_14_0
#define PSPDF_IS_IOS14_OR_GREATER 1
#else
#define PSPDF_IS_IOS14_OR_GREATER 0
#endif

#if PSPDF_IS_IOS14_OR_GREATER
#define PSPDF_IF_IOS14_OR_GREATER(...) __VA_ARGS__
#else
#define PSPDF_IF_IOS14_OR_GREATER(...)
#endif

NS_ASSUME_NONNULL_END
