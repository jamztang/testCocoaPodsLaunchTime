//
//  Copyright © 2011-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

#define PSPDFFeatureMaskInteger NSUInteger

// Obfuscate symbols that could cause confusion when Xcode picks random symbols during
// failures in the re-symbolication process.
#define PSPDFStatisticsSend PSPDFSS
#define PSPDFStatisticsSendData PSPDFSSD

NS_ASSUME_NONNULL_BEGIN

PSPDF_SDK_EXPORT void PSPDFInfo(void);

/// Checks if any of the specified features are enabled.
///
/// @param feature A bitmask of features, which may be combined with the bitwise or operator (|).
/// @param warn If YES, log a warning if the features are not all available. If NO the call is always silent.
/// @return YES if any of the features in the passed in bitmask are enabled. NO if all of the features are not enabled.
PSPDF_TEST_EXPORT BOOL PSPDFIsFeatureEnabled(PSPDFFeatureMaskInteger feature, BOOL warn);

/// Creates an error if any of the specified features are disabled. An additional
/// optional error message will be combined with the default `Your license does not
/// include...` message.
///
/// @param feature A bitmask of features, which may be combined with the bitwise or operator (|).
/// @param errorMessage The error message format, followed by arguments.
/// @return An error if any of the features are not enabled. `nil` if all specified features are enabled.
PSPDF_EXPORT NSError * _Nullable PSPDFCreateErrorIfFeatureIsNotEnabled(PSPDFFeatureMaskInteger feature, NSString * _Nullable errorMessage, ...) NS_FORMAT_FUNCTION(2, 3);

/// String representation for `PSPDFFeatureMaskInteger`.
PSPDF_EXPORT NSString *PSPDFFeatureMaskToString(PSPDFFeatureMaskInteger features);

/// Is in demo mode.
PSPDF_TEST_EXPORT BOOL PSPDFIsDemo(void);

/// Shows an alert from the model layer. Use sparingly!
PSPDF_EXTERN void PSPDFPresentAlert(NSString *_Nullable title, NSString *_Nullable message, BOOL dismissible);

/// C method to set the license key.
PSPDF_EXTERN PSPDFFeatureMaskInteger _PSPDFSetLicenseKey(const char *licenseKey, NSDictionary<NSString *, id> *_Nullable options);

/// Sends statistics to the ping endpoint. Triggers a version and license check.
PSPDF_EXTERN void PSPDFStatisticsSend(BOOL force, void (^_Nullable completionBlock)(NSData *_Nullable responseData, NSInteger httpResponseCode, NSError *_Nullable sessionError));

/// Sends the given data to the ping endpoint.
PSPDF_EXPORT void PSPDFStatisticsSendData(NSData *data, BOOL force, void (^completionBlock)(NSData *responseData, NSInteger httpResponseCode, NSError *sessionError));

NS_ASSUME_NONNULL_END
