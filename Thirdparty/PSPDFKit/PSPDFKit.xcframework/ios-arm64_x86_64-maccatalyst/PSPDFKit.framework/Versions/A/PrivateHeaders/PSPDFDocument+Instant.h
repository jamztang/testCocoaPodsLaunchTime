//
//  Copyright © 2017-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocument.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFCDocumentOpenResult;

@interface PSPDFDocument (CustomCoreDocument)

/// Creates the Core document and returns a `PDFCDocumentOpenResult`.
/// Due to how Instant is set-up, we can't guarantee to return a `PDFCDocumentOpenResult` (`self.instantDocumentBackend` is
/// weak) and we also can't allocate a `PDFCDocumentOpenResult` (due to not compiling the class into the binary). Treat
/// a nil return value as an unknown error.
- (nullable PDFCDocumentOpenResult *)actuallyCreateCoreDocument:(nullable NSString *)password;

@end

NS_ASSUME_NONNULL_END
