//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFFormElement.h>
#import <CoreText/CoreText.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFCoreAnnotation;

@interface PSPDFFormElement ()

/// Factory method to create a form element. Allocs and initializes the correct subclass.
+ (nullable instancetype)createFormElementWithCoreAnnotation:(PSPDFCoreAnnotation *)coreAnnotation formField:(PSPDFFormField *)formField documentProvider:(PSPDFDocumentProvider *)documentProvider pageIndex:(PSPDFPageIndex)pageIndex;

/// Initializes allocated instance of a form element.
/// * @param   coreAnnotation      The core annotation.
/// * @param   formField           The form field.
- (instancetype)initWithCoreAnnotation:(PSPDFCoreAnnotation *)coreAnnotation formField:(PSPDFFormField *)formField documentProvider:(PSPDFDocumentProvider *)documentProvider;

/// Resets the form value to the original value.
- (void)resetWithAction:(nullable PSPDFResetFormAction *)action;

/// Combines the `isReadOnly` and `isEditable` property.
@property (atomic, readonly) BOOL isInteractive;

/// Allows read-write access to the form field.
@property (atomic, weak) PSPDFFormField *formField;

/// Performs calculations to deteremine if, although the field is marked as multiline, can actually behave as a single-line field.
@property (nonatomic, readonly) BOOL isEffectivelySingleLine;

@end

@interface PSPDFFormElement (FontsPrivate)

/// Helper that returns a font for `contents`. Useful for auto-sized form elements.
- (UIFont *)fontWithContents:(nullable NSString *)contents;

/// Properties for subclassing.
@property (atomic, readonly) UIEdgeInsets edgeInsets;

/// Sizing
- (UIFont *)autoSizedFontWithContents:(nullable NSString *)contents preferredSize:(CGFloat)preferredSize forRect:(CGRect)rect;

@end

NS_ASSUME_NONNULL_END
