//
//  Copyright © 2016-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAppearanceModeManager.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFAppearanceModeManager ()

/// @section Mode operations

/// Returns the document render options for the provided mode.
- (PSPDFRenderOptions *)renderOptionsForMode:(PSPDFAppearanceMode)mode withCurrentOptions:(PSPDFRenderOptions *)options;

/// Applies UIAppearance settings for the selected mode.
- (void)applyAppearanceSettingsForMode:(PSPDFAppearanceMode)mode;

/// Updates `builder` with setting specific to the provided `mode`.
- (void)updateConfiguration:(PSPDFConfigurationBuilder *)builder forMode:(PSPDFAppearanceMode)mode;

/// Reloads the provided window following a UIAppearance change.
- (void)updateWindow:(UIWindow *)window forAppearanceChangeAnimated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
