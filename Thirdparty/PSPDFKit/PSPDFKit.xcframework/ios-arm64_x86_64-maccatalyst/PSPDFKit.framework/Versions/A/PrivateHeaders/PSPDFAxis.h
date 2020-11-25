//
//  Copyright © 2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

/// Defines a axis in 2D cartesian coordinate space. This is a shim for `UIAxis`
/// which is available since iOS 13.4 and can be removed once we drop iOS 13.
typedef NS_OPTIONS(NSUInteger, PSPDFAxis) {
    PSPDFAxisNeither = 0,
    PSPDFAxisHorizontal = 1 << 0,
    PSPDFAxisVertical = 1 << 1,
    PSPDFAxisBoth = (PSPDFAxisHorizontal | PSPDFAxisVertical),
} NS_SWIFT_NAME(Axis);
