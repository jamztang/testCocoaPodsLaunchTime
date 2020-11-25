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
#import <PSPDFKit/PSPDFError.h>
#import <PSPDFKit/NSError+PSPDFFoundation.h>
#else
#import "PSPDFEnvironment+Private.h"
#import "PSPDFError.h"
#import "Categories/NSError+PSPDFFoundation.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@interface NSError (PSPDFAdditions)

// Creates an error within the PSPDFKit error domain.
+ (instancetype)pspdf_errorWithCode:(NSUInteger)code description:(nullable NSString *)format, ... NS_FORMAT_FUNCTION(2, 3);
+ (instancetype)pspdf_errorWithCode:(NSUInteger)code description:(nullable NSString *)description failureReason:(nullable NSString *)failureReason;

@end

// Error promotion is a common pattern.
// We want to always capture internal errors but can't rely on external error objs being given.
#define PSPDFPromoteError(localError) \
    do {                              \
        if (error) {                  \
            *error = localError;      \
        }                             \
    } while (0)
#define PSPDFPromoteLocalError() PSPDFPromoteError(localError)

// Promotes only if the error is not already set
#define PSPDFPromoteErrorIfUnset(localError) \
    do {                                     \
        if (error && *error == nil) {        \
            *error = localError;             \
        }                                    \
    } while (0)
#define PSPDFPromoteLocalErrorIfUnset() PSPDFPromoteErrorLocalIfUnset(localError)

/// Like PSPDFSetError, but doesn’t log.
#define PSPDFSilentError(errorPointer, errorCode, message, ...) ({ \
    if (errorPointer) { \
        *errorPointer = [NSError errorWithDomain:PSPDFErrorDomain code:errorCode userInfo:@{ \
            NSLocalizedDescriptionKey: [NSString stringWithFormat:message, ## __VA_ARGS__], \
        }]; \
    } \
})

/// Like PSPDFUnderlyingError, but doesn’t log.
#define PSPDFSilentUnderlyingError(errorPointer, underlyingError, errorCode, message, ...) ({ \
    if (errorPointer) { \
        *errorPointer = [NSError errorWithDomain:PSPDFErrorDomain code:errorCode userInfo:@{ \
            NSLocalizedDescriptionKey: [NSString stringWithFormat:message, ## __VA_ARGS__], \
            NSUnderlyingErrorKey: underlyingError, \
        }]; \
    } \
})

// Generate NSError object with a sub-error.
#define PSPDFErrorWithUnderlyingError(errorToSet, underlyingError, errorCode, format, ...)          \
    _PSPDFErrorWithUnderlyingError(errorToSet, underlyingError, errorCode, format, ##__VA_ARGS__);  \
    if (underlyingError == nil) {                                                                   \
        PSPDFLogError(@"Code %lu: " format, (unsigned long)errorCode, ##__VA_ARGS__);               \
    } else {                                                                                        \
PSPDFLogError(@"Code %lu: " format " internal error: %@", (unsigned long)errorCode, ##__VA_ARGS__, underlyingError); \
    }                                                                                               \
    do {} while (0)

// Generate a NSError object in the PSPDFErrorDomain.
#define PSPDFError(errorToSet, errorCode, ...)                              \
    _Pragma("clang diagnostic push")                                        \
    _Pragma("clang diagnostic ignored \"-Wformat\"")                        \
    _Pragma("clang diagnostic ignored \"-Wunreachable-code\"")              \
    PSPDFErrorWithUnderlyingError(errorToSet, nil, errorCode, __VA_ARGS__); \
    _Pragma("clang diagnostic pop")                                         \
    do {} while (0)

// Generate a NSError object in the PSPDFErrorDomain from an exception.
#define PSPDFErrorWithException(errorToSet, exception, errorCode, format, ...) PSPDFErrorWithUnderlyingError(errorToSet, (NSError *)exception, errorCode, format, ##__VA_ARGS__)

// internal only. Use the macros instead.
PSPDF_SDK_EXPORT NSError *_PSPDFErrorWithUnderlyingError(NSError *_Nullable __autoreleasing *_Nullable errorToSet, NSError *_Nullable underlyingError, NSInteger errorCode, NSString *description, ...) NS_FORMAT_FUNCTION(4, 5);

#define PSPDFSetError(error, errorCode, errorDescription)                                                                                          \
    do {                                                                                                                                           \
        _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wpointer-bool-conversion\"") PSPDFLogError(@"%@", errorDescription); \
        if (error) {                                                                                                                               \
            NSDictionary *errorUserInfo = (errorDescription) != nil ? @{NSLocalizedDescriptionKey: (errorDescription)} : nil;                      \
            *error = [NSError errorWithDomain:PSPDFErrorDomain code:errorCode userInfo:errorUserInfo];                                             \
            _Pragma("clang diagnostic pop")                                                                                                        \
        }                                                                                                                                          \
    } while (0)

NS_ASSUME_NONNULL_END
