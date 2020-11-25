//
//  Copyright © 2012-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

/// Initialize with `Document` object as `activityItems` or directly with title/URL/NSData.
PSPDF_CLASS_SWIFT(ActivityViewController)
@interface PSPDFActivityViewController : UIActivityViewController<PSPDFOverridable>
@end

NS_ASSUME_NONNULL_END
