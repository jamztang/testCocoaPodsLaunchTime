//
//  Copyright © 2018-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAnnotationCreator.h>

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKitUI/PSPDFConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_TEST_CLASS_SWIFT(TextMarkupAnnotationCreator)
@interface PSPDFTextMarkupAnnotationCreator : PSPDFAnnotationCreator

/// Inserts a markup annotation on the page the receiver was created for. This method automatically merges the new annotation with the annotation type
///
/// @param markupClass The subclass of `PSPDFTextMarkupAnnotation` that is to be used to create the markup.
/// @param annotationType The type of markup annotation to be created.
/// @param rectsToMarkup The rects, in PDF coordinates, to which the markup is to be applied.
/// @param markupColor The color to apply to the markup. If `nil`, the annotation's default color is used.
- (void)insertMarkupAnnotationOfClass:(Class)markupClass type:(PSPDFAnnotationType)annotationType withRects:(nullable NSArray<NSValue *> *)rectsToMarkup usingColor:(nullable UIColor *)markupColor;

/// Controls if markup annotations should be merged.
///
/// Defaults to `PSPDFMarkupAnnotationMergeIfColorMatches`.
@property (nonatomic) PSPDFMarkupAnnotationMergeBehavior mergeBehavior;

@end

NS_ASSUME_NONNULL_END
