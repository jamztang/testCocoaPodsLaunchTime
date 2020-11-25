//
//  Copyright © 2018-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// Displays progress indication with a title.
PSPDF_CLASS_SWIFT(ProgressLabelView)
@interface PSPDFProgressLabelView : UIView

/// Text color of the label.
/// Defaults to UIColor.secondaryLabelColor on iOS 13 and above. Falls back to UIColor.grayColor for earlier versions.
@property (nonatomic) UIColor *titleColor UI_APPEARANCE_SELECTOR;

/// Tint color of the progress indicator.
/// Defaults to UIColor.secondaryLabelColor on iOS 13 and above. Falls back to UIColor.grayColor for earlier versions.
@property (nonatomic) UIColor *progressIndicatorColor UI_APPEARANCE_SELECTOR;

@end
