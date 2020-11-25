//
//  Copyright © 2018-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFBaseViewController.h>

@class PSPDFRedactionViewController, PSPDFDocument;

NS_ASSUME_NONNULL_BEGIN

/// Delegate for the redaction view controller.
@protocol PSPDFRedactionViewControllerDelegate <NSObject>

/// Called when the redaction view controller applied redactions.
- (void)redactionViewController:(PSPDFRedactionViewController *)redactionViewController didApplyRedactionsToDocument:(PSPDFDocument *)document;

@end

/// Screen that informs the user about uncommitted redactions in the document.
/// Contains buttons, used to commit the redactions, either in the current file or in a new file,
/// and a preview switch to render the redactions in their redacted state.
PSPDF_APP_CLASS_SWIFT(RedactionViewController)
@interface PSPDFRedactionViewController : PSPDFBaseViewController<PSPDFOverridable>

/// Creates a new redaction view controller with a given document.
- (instancetype)initWithDocument:(PSPDFDocument *)document;

/// Document that is used as the source for previewing and applying redactions on.
@property (nonatomic, readonly) PSPDFDocument *document;

/// Delegate for callback when redactions have been applied.
@property (nonatomic, weak) id<PSPDFRedactionViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
