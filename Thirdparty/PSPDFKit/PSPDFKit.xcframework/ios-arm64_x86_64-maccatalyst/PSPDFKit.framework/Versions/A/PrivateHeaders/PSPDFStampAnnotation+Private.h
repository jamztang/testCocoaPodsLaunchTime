//
//  Copyright © 2014-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFStampAnnotation.h>

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFRotatableInternal.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_SDK_EXPORT const CGSize PSPDFStampDefaultSize;

@interface PSPDFStampAnnotation () <PSPDFRotatableInternal>

/// Returns the stamp types for default stamps.
+ (NSArray<PSPDFStampType> *)defaultStampTypes;

/// A boxed `PDFCStampType` from the stamp’s `stampType` string or nil if it’s not a standard stamp.
@property (atomic, readonly, nullable) NSNumber *boxedStampType;

/// Loads the image from core. Images are not loaded from core by default, only when required.
- (BOOL)loadAndSetImageWithError:(NSError **)error;

@end

@interface UIImage (PSPDFStampAnnotationMarker)

/// Can be set when an image, associated with a stamp annotation, doesn't have an alpha value or should not respect its alpha value.
@property (atomic, assign) BOOL pspdf_forceIgnoreAlpha;

@end

NS_ASSUME_NONNULL_END
