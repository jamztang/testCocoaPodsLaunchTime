//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDocumentActivity.h>

/// Opens an alert view to choose to switch to another page.
/// Also accepts page labels.
PSPDF_TEST_CLASS_SWIFT(GoToPageActivity)
@interface PSPDFGoToPageActivity : PSPDFDocumentActivity

/// Match partial label string names. Defaults to YES.
@property (nonatomic) BOOL enablePartialLabelMatching;

/// The page index currently shown to the user.
///
/// Setting an invalid page index leads to undefined behavior.
///
/// This defaults to `NSNotFound` which results in no back link being created.
@property (nonatomic) NSInteger currentPageIndex;

@end
