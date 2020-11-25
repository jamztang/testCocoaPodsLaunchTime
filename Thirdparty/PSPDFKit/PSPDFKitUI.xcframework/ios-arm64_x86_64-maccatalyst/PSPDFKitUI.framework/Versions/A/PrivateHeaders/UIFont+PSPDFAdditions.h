//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_EXTERN CGFloat PSPDFValueScaledForPreferredContentSize(CGFloat unscaledValue);

@interface UIFont (PSPDFAdditions)

// Similar to `systemFontOfSize:` but factors the default font setting in.
// Prefer  +[UIFont preferredFontForTextStyle:] if possible.
+ (UIFont *)pspdf_systemFontOfDynamicSize:(CGFloat)fontSize;
+ (UIFont *)pspdf_boldSystemFontOfDynamicSize:(CGFloat)fontSize;

@end

NS_ASSUME_NONNULL_END
