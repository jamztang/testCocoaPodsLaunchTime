//
//  Copyright © 2018-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFCellModel.h>
#import <PSPDFKitUI/PSPDFLabelValueCellModel+Private.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFStaticTableViewController, PSPDFLabeledTextFieldCell, PSPDFTextView;

/// Editable label and value cell model to use with `PSPDFStaticTableViewController`.
@interface PSPDFLabeledTextFieldCellModel : PSPDFLabelValueCellModel

@property (nonatomic, copy) void (^valueDidChangeHandler)(__kindof PSPDFStaticTableViewController *, PSPDFLabeledTextFieldCell *cell, NSIndexPath *indexPath, NSString *value);

/// A Boolean value that indicates whether the value is read-only.
///
/// @note The text can still be selected when `readOnly` is true.
@property (nonatomic, getter=isReadOnly) BOOL readOnly;

/// The placeholder that is shown in the text field if value is empty.
@property (nonatomic, copy) NSString *placeholder;

/// The autocapitalization type of the text field.
@property (nonatomic) UITextAutocapitalizationType autocapitalizationType;

@end

PSPDF_APP_CLASS_SWIFT(LabeledTextFieldCell)
@interface PSPDFLabeledTextFieldCell : PSPDFLabelValueBaseCell

@property (nonatomic, copy) void (^valueDidChangeHandler)(UITextView *textView, NSString *value);

@property (nonatomic, readonly) PSPDFTextView *textView;

/// A Boolean value that indicates whether the value is read-only.
@property (nonatomic, getter=isReadOnly) BOOL readOnly;

@end

NS_ASSUME_NONNULL_END
