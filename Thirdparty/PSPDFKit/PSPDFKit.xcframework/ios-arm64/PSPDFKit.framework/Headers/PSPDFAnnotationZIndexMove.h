//
//  Copyright © 2019-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Defines the z-index position where an annotation should be moved to.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFAnnotationZIndexMove) {
    /// Move the annotation to the front of the z-index stack.
    PSPDFAnnotationZIndexMoveToFront,
    /// Move the annotation one position forward on the z-index stack.
    PSPDFAnnotationZIndexMoveForward,
    /// Move the annotation one position backward on the z-index stack.
    PSPDFAnnotationZIndexMoveBackward,
    /// Move the annotation to the back of the z-index stack.
    PSPDFAnnotationZIndexMoveToBack,
} PSPDF_ENUM_SWIFT(Annotation.ZIndexMove);

NS_ASSUME_NONNULL_END
