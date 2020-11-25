//
//  Copyright © 2011-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#pragma once

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

typedef NS_OPTIONS(NSUInteger, PSPDFLogLevelMask) {
    /// Log nothing.
    PSPDFLogLevelMaskNothing = 0,

    /// Logs critical issues, that can break or limit the functionality of the framework.
    /// Should never be disabled.
    PSPDFLogLevelMaskCritical = 1 << 0,

    /// Logs errors. Should never be disabled.
    PSPDFLogLevelMaskError = 1 << 1,

    /// Logs issues that are not errors or critical, but log-worthy.
    PSPDFLogLevelMaskWarning = 1 << 2,

    /// Logs important operations.
    PSPDFLogLevelMaskInfo = 1 << 3,

    /// Will log almost everything and slow down the application flow.
    PSPDFLogLevelMaskDebug = 1 << 4,

    /// Might log security related details like signature points.
    /// Never enable this in release builds unless they are solely for testing.
    PSPDFLogLevelMaskVerbose = 1 << 5,

    /// Enables all logging categories.
    PSPDFLogLevelMaskAll = UINT_MAX,
} PSPDF_ENUM_SWIFT(LogLevelMask);
