//
//  Copyright © 2012-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFFreeTextAnnotation.h>
#import <PSPDFKit/PSPDFRotatableInternal.h>

NS_ASSUME_NONNULL_BEGIN

/// The default font name for free text annotations.
PSPDF_SDK_EXPORT NSString *const PSPDFDefaultFreeTextFontName;

/// The default font size for free text annotations.
PSPDF_SDK_EXPORT const CGFloat PSPDFDefaultFreeTextFontSize;

/// The default lower font size.
PSPDF_SDK_EXPORT const CGFloat PSPDFTextSizeMinimum;

/// The default upper font size.
PSPDF_SDK_EXPORT const CGFloat PSPDFTextSizeMaximum;

@interface PSPDFFreeTextAnnotation () <PSPDFRotatableInternal>

/// The line height is dynamically calculated based on the font type and size.
- (CGFloat)lineHeight;

/// Clears the “text should fit” flag for the receiver.
///
/// Should be called whenever we regenerate the AP stream and the text does not fit the bounding box.
- (void)instant_clearTextShouldFitMarker;

@end

NS_ASSUME_NONNULL_END
