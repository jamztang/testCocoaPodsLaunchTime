//
//  Copyright © 2018-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIMenuController (PSPDFVisibility)

/// YES while setting the menu visible via `setMenuVisible:animated:`, NO in all other cases.
///
/// @note Only set while the method is executing.
@property (nonatomic, readonly) BOOL pspdf_isShowingMenu NS_SWIFT_NAME(isShowingMenu);

/// Variant of `showMenuFromView` that works with iOS 12.
- (void)pspdf_showMenuFromView:(UIView *)targetView rect:(CGRect)targetRect;

/// Variant of `hideMenu` that works with iOS 12.
- (void)pspdf_hideMenu;

@end

NS_ASSUME_NONNULL_END
