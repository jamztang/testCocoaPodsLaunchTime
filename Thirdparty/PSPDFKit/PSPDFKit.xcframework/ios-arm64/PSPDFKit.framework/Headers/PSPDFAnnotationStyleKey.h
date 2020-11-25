//
//  Copyright © 2018-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation;

/// Property keys for annotation inspector customization.
///
/// @see PSPDFAnnotationStyleViewController
/// @see PSPDFConfiguration
/// @see https://pspdfkit.com/guides/ios/current/annotations/annotation-inspector/
typedef NSString *PSPDFAnnotationStyleKey NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(AnnotationStyle.Key);

/// A list of annotation style keys (inner array) grouped into serval groups (outer array).
typedef NSArray<NSArray<PSPDFAnnotationStyleKey> *> * PSPDFAnnotationStyleKeyGroupedList;

/// A block type that takes an annotation and returns the grouped list of style keys for that particular annotation.
typedef PSPDFAnnotationStyleKeyGroupedList _Nonnull (^PSPDFAnnotationStyleBlock)(PSPDFAnnotation *annotation);

/// Style key representing the annotation color property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyColor;

/// Style key representing the annotation fillColor property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyFillColor;

/// Style key representing the annotation alpha property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyAlpha;

/// Style key representing the annotation lineWidth property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyLineWidth;

/// Style key representing the annotation dashArray property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyDashArray;

/// Style key representing the free text annotation lineEnd property (in callout mode).
///
/// @note Applicable only to `FreeTextAnnotation`.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyLineEnd;

/// Style key representing the abstract line annotation lineEnd1 property.
///
/// @note Applicable only to `PSPDFAbstractLineAnnotation` subclasses.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyLineEnd1;

/// Style key representing the abstract line annotation lineEnd2 property.
///
/// @note Applicable only to `PSPDFAbstractLineAnnotation` subclasses.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyLineEnd2;

/// Style key representing the annotation fontName property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyFontName;

/// Style key representing the annotation fontSize property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyFontSize;

/// Style key representing the annotation textAlignment property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyTextAlignment;

/// Style key representing the annotation blendMode property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyBlendMode;

/// Converting a regular free text annotation to a callout modifies multiple properties.
/// This cannot be controlled with a single property and we use a special key for the change.
///
/// @note Applicable only to `FreeTextAnnotation`.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyCalloutAction;

/// Style key representing the outline color property of redactions.
///
/// @note Applicable only to `PSPDFRedactionAnnotation`.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyOutlineColor;

/// Style key representing the overlay text property of redactions.
///
/// @note Applicable only to `PSPDFRedactionAnnotation`.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyOverlayText;

/// Style key representing the property for repeating the overlay text of redactions.
///
/// @note Applicable only to `PSPDFRedactionAnnotation`.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyRepeatOverlayText;

NS_ASSUME_NONNULL_END
