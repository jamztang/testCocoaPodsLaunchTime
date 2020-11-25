//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDocumentActivity.h>

#import <PSPDFKit/PSPDFMacros+Private.h>

@class PSPDFDocumentSharingConfiguration;

/// Activity that shows the Open In... controller.
///
/// Not supported on Mac Catalyst.
PSPDF_APP_CLASS_SWIFT(OpenInActivity)
@interface PSPDFOpenInActivity : PSPDFDocumentActivity

/// The sharing configuration used for the open in activity.
@property (nonatomic, copy) PSPDFDocumentSharingConfiguration *sharingConfiguration;

@end
