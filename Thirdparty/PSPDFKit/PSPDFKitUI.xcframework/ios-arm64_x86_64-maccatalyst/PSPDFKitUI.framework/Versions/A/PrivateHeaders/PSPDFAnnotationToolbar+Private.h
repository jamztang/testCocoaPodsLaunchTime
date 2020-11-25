//
//  Copyright © 2018-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAnnotationToolbar.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFAnnotationToolbar ()

/// Target action for the touch up inside even on the redaction annotation toolbar button.
- (void)redactButtonPressed:(nullable id)sender;

/// Target action for the touch up inside even on the link annotation toolbar button.
- (void)linkButtonPressed:(nullable id)sender;

/// Toggle Saved Annotations Controller.
- (void)savedannotationsButtonPressed:(nullable id)sender;

/// Used only for UI tests to always show undo redo button.
- (BOOL)shouldAddRedoButtonForToolbarPosition:(PSPDFFlexibleToolbarPosition)position;

@end

NS_ASSUME_NONNULL_END
