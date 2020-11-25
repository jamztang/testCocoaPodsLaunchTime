//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFFormElement.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFTextFormField;

/// Form field flags specific to text fields, matching bit positions in the PDF specification.
typedef NS_OPTIONS(NSUInteger, PSPDFTextFieldFlag) {
    PSPDFTextFieldFlagMultiline = 1 << (13 - 1),
    PSPDFTextFieldFlagPassword = 1 << (14 - 1),
    PSPDFTextFieldFlagFileSelect = 1 << (21 - 1),
    PSPDFTextFieldFlagDoNotSpellCheck = 1 << (23 - 1),
    PSPDFTextFieldFlagDoNotScroll = 1 << (24 - 1),
    PSPDFTextFieldFlagComb = 1 << (25 - 1),
    PSPDFTextFieldFlagRichText = 1 << (26 - 1),
} PSPDF_ENUM_SWIFT(TextFieldFormElement.TextFieldFlag);

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFTextInputFormat) {
    PSPDFTextInputFormatNormal,
    PSPDFTextInputFormatNumber,
    PSPDFTextInputFormatDate,
    PSPDFTextInputFormatTime,
} PSPDF_ENUM_SWIFT(TextFieldFormElement.TextInputFormat);

/// Text field form element.
PSPDF_CLASS_SWIFT(TextFieldFormElement)
@interface PSPDFTextFieldFormElement : PSPDFFormElement

/// If set, the field may contain multiple lines of text; if clear, the field’s text shall be restricted to a single line.
///
/// @note Evaluates `PSPDFTextFieldFlagMultiline` in the `fieldFlags`.
@property (atomic, getter=isMultiline, readonly) BOOL multiline;

/// If set, the field is intended for entering a secure password that should not be echoed visibly to the screen.
///
/// @note Evaluates `PSPDFTextFieldFlagPassword` in the `fieldFlags`.
@property (atomic, getter=isPassword, readonly) BOOL password;

/// Returns the contents formatted based on rules in the annotation (including JavaScript)
@property (atomic, readonly, nullable) NSString *formattedContents;

/// The input format. Some forms are number/date/time specific.
@property (atomic, readonly) PSPDFTextInputFormat inputFormat;

/// Returns the parent property `formField` cast to the appropriate `PSPDFTextFormField` type.
@property (atomic, readonly, nullable) PSPDFTextFormField *textFormField;

@end

NS_ASSUME_NONNULL_END
