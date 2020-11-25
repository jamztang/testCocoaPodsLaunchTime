//
//  Copyright © 2012-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFViewController, PSPDFDocumentProvider, PSPDFDocument, PSPDFAnnotation;

/// Delegate to receive events regarding `Document`.
///
/// This delegate offers callbacks for custom actions after save events.
PSPDF_PROTOCOL_SWIFT(PDFDocumentDelegate)
@protocol PSPDFDocumentDelegate<NSObject>

@optional

/// PDF files can contain actions to other PDF files (`PSPDFRemoteGoToAction`).
/// Usually, these are attached to link annotations, but actions can also be connected to outline or forms.
///
/// PSPDFKit automatically tries to find the linked files based on the relative path.
/// There are also built-in tokens such as `Documents`, `Cache`, `Library`, `Bundle` and `PSBundle`
/// that help to navigate inside the typical iOS/macOS application folder structure.
///
/// This delegate allows custom tokens to be resolved, such as /MyAppToken.
/// This delegate will only get called for unknown tokens, not any built-in ones.
///
/// @see `PSPDFDocumentProvider resolveTokenizedPath:alwaysLocal:`
///
/// Return nil if the token cannot be resolved.
- (NSString *)pdfDocument:(PSPDFDocument *)document resolveCustomAnnotationPathToken:(NSString *)pathToken;

/// Called after saving was successful.
/// If document wasn't modified, delegates will not be called.
///
/// @warning Might be called from a background thread.
- (void)pdfDocumentDidSave:(PSPDFDocument *)document;

/// Called after saving failed.
///
/// @warning Might be called from a background thread.
- (void)pdfDocument:(PSPDFDocument *)document saveDidFailWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
