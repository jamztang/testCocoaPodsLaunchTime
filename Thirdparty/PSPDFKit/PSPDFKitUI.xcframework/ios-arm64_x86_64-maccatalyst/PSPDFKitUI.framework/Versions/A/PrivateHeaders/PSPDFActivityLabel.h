//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Preconfigured label subclass that optionally shows an activity indicator.
PSPDF_APP_CLASS_SWIFT(ActivityLabel)
@interface PSPDFActivityLabel : UILabel<PSPDFOverridable>

/// Convenience constructor.
+ (instancetype)labelWithText:(nullable NSString *)text showActivity:(BOOL)showActivity;

/// Enable spinning wheel next to text.
@property (nonatomic) BOOL showActivity;

@end

NS_ASSUME_NONNULL_END
