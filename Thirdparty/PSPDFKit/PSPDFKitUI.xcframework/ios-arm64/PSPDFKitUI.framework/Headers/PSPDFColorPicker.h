//
//  Copyright © 2016-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

/// A color set describes a set of different color pickers that provide colors for
/// a certain use case.
///
/// @note The list of color sets may grow, keep this in mind when designing custom
/// color pickers and provide a suitable default (or fall back to PSPDFKit's
/// built-in color picker in this case).
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFColorSet) {
    /// The default color set, used for most foreground colors in PSPDFKit.
    PSPDFColorSetDefault,
    /// The default color set but including transparent / empty color. Mostly used for background colors through out PSPDFKit.
    PSPDFColorSetDefaultWithTransparency,
    /// The color set used when selecting page background colors. Its colors are suitable for full page background colors.
    PSPDFColorSetPageBackgrounds,
} PSPDF_ENUM_SWIFT(ColorPatch.ColorSet);

/// A color patch represents a single patch of colors in the UI. It contains of
/// one or multiple colors that should be grouped together.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ColorPatch)
@interface PSPDFColorPatch : NSObject

/// Create a color patch representing a single color.
///
/// @param color The color that this patch should represent.
///
/// @return A newly created instance of `PSPDFColorPatch` representing the passed in color.
+ (PSPDFColorPatch *)colorPatchWithColor:(UIColor *)color;

/// Create a color patch representing multiple colors.
///
/// @param colors The colors that this patch should represent.
///
/// @return A newly created instance of `PSPDFColorPatch` representing the passed in colors.
+ (PSPDFColorPatch *)colorPatchWithColors:(NSArray<UIColor *> *)colors;

/// The colors that this color patch represents.
@property (nonatomic, copy, readonly) NSArray<UIColor *> *colors;

@end

/// A color palette is a set of color patches that are grouped together based on a specific
/// look or theme.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ColorPalette)
@interface PSPDFColorPalette : NSObject

/// Creates a color palette with a given title and the patches it should group.
///
/// @param title   The title of the palette.
/// @param patches The color patches that should be grouped by this palette.
///
/// @return A new color palette.
+ (PSPDFColorPalette *)colorPaletteWithTitle:(NSString *)title colorPatches:(NSArray<PSPDFColorPatch *> *)patches;

/// Creates a color palette representing all colors of the hsv color space.
///
/// @param title The title of the palette.
///
/// @return A new color palette.
+ (PSPDFColorPalette *)hsvColorPaletteWithTitle:(NSString *)title;

/// The title of the color palette as shown in the UI.
@property (nonatomic, copy, readonly) NSString *title;

/// The color patches this color space represents.
@property (nonatomic, copy, readonly) NSArray<PSPDFColorPatch *> *colorPatches;

@end

@interface PSPDFColorPalette (PSPDFColorPalettes)

/// @return A unified color palette with 13 rainbow colors and 5 gray scale colors.
+ (PSPDFColorPalette *)unifiedColorPalette;

/// @return A unified color palette with 12 rainbow colors, 5 gray scale colors and a clear color.
+ (PSPDFColorPalette *)unifiedTransparentColorPalette;

/// @return A monochrome color palette containing 6 gray scale colors.
+ (PSPDFColorPalette *)monochromeColorPalette;

/// @return A monochrome color palette containing 5 gray scale colors and a clear color.
+ (PSPDFColorPalette *)monochromeTransparentPalette;

/// @return A modern color palette with 6 colors.
+ (PSPDFColorPalette *)modernColorPalette;

/// @return A vintage color palette with 6 colors.
+ (PSPDFColorPalette *)vintageColorPalette;

/// @return A color palette with 6 colors similar to those in a rainbow.
+ (PSPDFColorPalette *)rainbowColorPalette;

/// @return A color palette with colors suitable for page backgrounds.
+ (PSPDFColorPalette *)paperColorPalette;

/// @return A color palette representing the hsv color space.
+ (PSPDFColorPalette *)hsvColorPalette;

@end

/// The factory used to create color pickers. Subclass this to customize your color
/// pickers.
PSPDF_CLASS_SWIFT(ColorPickerFactory)
@interface PSPDFColorPickerFactory : NSObject<PSPDFOverridable>

/// You can override this method to customize the color palettes for a certain color set.
///
/// @note When overriding, design your method so that it can handle arbitrary values
/// for the `colorSet` parameter. You can either return your own default palettes
/// if you are experiencing unknown values or return super's return value to
/// fall back to PSPDFKit's internal color palettes.
///
/// @param colorSet The color set whose color palettes are requested.
///
/// @return An array of `PSPDFColorPalette`s representing the passed in color set.
+ (NSArray<PSPDFColorPalette *> *)colorPalettesInColorSet:(PSPDFColorSet)colorSet;

@end

NS_ASSUME_NONNULL_END
