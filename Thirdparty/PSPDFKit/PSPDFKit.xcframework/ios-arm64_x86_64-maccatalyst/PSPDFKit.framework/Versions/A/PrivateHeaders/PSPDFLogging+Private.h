//
//  Copyright © 2011-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFLogging.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFError+Private.h>
#import <PSPDFKit/PSPDFAssert.h>
#else
#import "PSPDFLogging.h"
#import "PSPDFMacros+Private.h"
#import "Error/PSPDFError+Private.h"
#import "PSPDFAssert.h"
#endif

NS_ASSUME_NONNULL_BEGIN

typedef void (^PSPDFLogHandler)(PSPDFLogLevelMask level, const char *_Nullable tag, NS_NOESCAPE NSString * (^message)(void), const char *_Nullable file, const char *_Nullable function, NSUInteger line);

/// Internal global variable for the log level. Set via PSPDFKitGlobal.sharedInstance.logLevel.
PSPDF_EXTERN PSPDFLogLevelMask PSPDFLogLevel;

/// Default handler for logging.
PSPDF_APP_EXPORT PSPDFLogHandler PSPDFLogHandlerBlock;

/// Internal logging function to make setting breakpoints easier.
PSPDF_EXTERN void _PSPDFLog(PSPDFLogLevelMask level, const char *_Nullable tag, NSString *format, ...) NS_FORMAT_FUNCTION(3, 4);
PSPDF_EXTERN void _PSPDFLogv(PSPDFLogLevelMask level, const char *_Nullable tag, NSString *format, va_list args) NS_FORMAT_FUNCTION(3, 0);

NS_ASSUME_NONNULL_END

// Logging

#if defined(PSPDF_BLOCK_LOGGING)
#define PSPDF_LOG_USE_ONLY __unused
#else
#define PSPDF_LOG_USE_ONLY
#endif

#if defined(PSPDF_BLOCK_LOGGING)
#define PSPDFLogMacro(_level, _tag, _message)
#else
#define PSPDFLogMacro(_level, _tag, _message) PSPDFLogHandlerBlock(_level, _tag, _message, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__)
#endif

#define PSPDFLogVerbose(format, ...)                                                   \
    PSPDFLogMacro(PSPDFLogLevelMaskVerbose, NULL, (^{                                  \
                      return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
                  }))
#define PSPDFLog(format, ...)                                                          \
    PSPDFLogMacro(PSPDFLogLevelMaskInfo, NULL, (^{                                     \
                      return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
                  }))
#define PSPDFLogWarning(format, ...)                                                   \
    PSPDFLogMacro(PSPDFLogLevelMaskWarning, NULL, (^{                                  \
                      return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
                  }))
#define PSPDFLogError(format, ...)                                                     \
    PSPDFLogMacro(PSPDFLogLevelMaskError, NULL, (^{                                    \
                      return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
                  }))
#define PSPDFLogDebug(format, ...)                                                     \
    PSPDFLogMacro(PSPDFLogLevelMaskDebug, NULL, (^{                                    \
                      return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
                  }))
#define PSPDFLogCritical(format, ...)                                                  \
    PSPDFLogMacro(PSPDFLogLevelMaskCritical, NULL, (^{                                 \
                      return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
                  }))

#if defined(PSPDF_BLOCK_LOGGING)
#define PSPDFLogWarningOnce(format, ...)
#else
#define PSPDFLogWarningOnce(format, ...)            \
    do {                                            \
        static dispatch_once_t onceToken;           \
        dispatch_once(&onceToken, ^{                \
            PSPDFLogWarning(format, ##__VA_ARGS__); \
        });                                         \
    } while (0)
#endif
