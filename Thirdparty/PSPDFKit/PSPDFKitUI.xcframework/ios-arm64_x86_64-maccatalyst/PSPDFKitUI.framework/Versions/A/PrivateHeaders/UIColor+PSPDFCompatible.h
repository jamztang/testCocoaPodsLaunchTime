//
//  Copyright © 2019-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIColor (PSPDFCompatible)

/// Creates a dynamic color, given light and dark mode variants. On iOS 12 and lower,
/// light mode variant is used always.
///
/// @param lightModeColor Color to be used in light mode trait environment.
/// @param darkModeColor Color to be used in dark mode trait environment.
+ (UIColor *)pspdf_dynamicColorForLightMode:(UIColor *)lightModeColor darkMode:(UIColor *)darkModeColor NS_SWIFT_NAME(dynamicColor(lightMode:darkMode:));

/// Creates a dynamic color, given ARGB values of light and dark mode variants. On
/// iOS 12 and lower, light mode is used always.
///
/// @param lightModeValue ARGB value of light mode color variant.
/// @param darkModeValue ARGB value of dark mode color variant.
+ (UIColor *)pspdf_dynamicColorWithARGB32ForLightMode:(int32_t)lightModeValue darkMode:(int32_t)darkModeValue NS_SWIFT_NAME(dynamicColor(ARGB32lightMode:ARGB32darkMode:));

/// Resolves the color using the trait collection passed.
/// Returns the same color on versions prior iOS 13.
- (UIColor *)pspdf_resolvedColorWithTraitCollection:(UITraitCollection *)traitCollection NS_SWIFT_NAME(resolvedColor(traitCollection:));

/// Uses `UIColor.secondarySystemBackgroundColor` for iOS 13 and above.
/// Falls back to `[UIColor colorWithWhite:0.2 alpha:1.0]` for earlier versions.
@property (class, nonatomic, readonly) UIColor *pspdf_defaultConfigurationBackgroundColor NS_SWIFT_NAME(defaultConfigurationBackground);

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_systemBackgroundColor;

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_secondarySystemBackgroundColor;

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_tertiarySystemBackgroundColor;

/// @note Falls back to `UITableView.groupTableViewBackgroundColor` on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_systemGroupedBackgroundColor;

/// @note Falls back to `UITableView.groupTableViewBackgroundColor` on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_tertiarySystemGroupedBackgroundColor;

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_labelColor;

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_secondaryLabelColor;

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_tertiaryLabelColor;

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_accessoryViewColor NS_SWIFT_NAME(accessoryView);

/// @note Falls back to a UIColor.lightGrayColor on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_systemGray2Color;

/// Closes relative of UIColor.lightGrayColor.
///
/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_systemGray4Color;

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_systemFillColor;

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_secondarySystemFillColor;

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_tertiarySystemFillColor;

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_quaternarySystemFillColor;

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_separatorColor;

/// Uses `UIColor.separatorColor` for iOS 13 and above.
/// Falls back to `UIColor.blackColor` for earlier versions.
///
/// @note Used in `PSPDFPageCell` for the thumbnails border color.
@property (class, nonatomic, readonly) UIColor *pspdf_separator2Color;

/// @note Falls back to a non-dynamic color on iOS versions prior 13.
@property (class, nonatomic, readonly) UIColor *pspdf_opaqueSeparatorColor;

@end

NS_ASSUME_NONNULL_END
