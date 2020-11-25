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

@class PSPDFAppearanceModeManager, PSPDFConfigurationBuilder, PSPDFRenderOptions;

typedef NS_OPTIONS(NSUInteger, PSPDFAppearanceMode) {
    /// Normal application appearance and page rendering, as configured by the host app.
    PSPDFAppearanceModeDefault = 0,
    /// Renders the PDF content with a sepia tone.
    PSPDFAppearanceModeSepia = 1 << 0,
    /// Inverts the PDF page content and applies color correction. On iOS versions prior to iOS 13, it also applies a dark interface theme via UIAppearance.
    PSPDFAppearanceModeNight = 1 << 1,
    /// All options.
    PSPDFAppearanceModeAll = PSPDFAppearanceModeDefault | PSPDFAppearanceModeSepia | PSPDFAppearanceModeNight
} NS_SWIFT_NAME(PDFAppearanceMode);

NS_ASSUME_NONNULL_BEGIN

/// Notification sent out after `appearanceMode` is changed.
PSPDF_EXPORT NSNotificationName const PSPDFAppearanceModeChangedNotification;

/// Notification `userInfo` dictionary key. Holds a `BOOL` `NSNumber` which is `true`
/// when an animated mode change was requested.
PSPDF_EXPORT NSString *const PSPDFAppearanceModeChangedAnimatedKey;

PSPDF_PROTOCOL_SWIFT(AppearanceModeManagerDelegate)
@protocol PSPDFAppearanceModeManagerDelegate<NSObject>

@optional

/// Provides the document render options for the specified mode.
///
/// @param manager A reference to the invoking appearance mode manager.
/// @param mode The mode that is about to be applied.
///
/// @note Overrides the default behavior, if implemented.
- (PSPDFRenderOptions *)appearanceManager:(PSPDFAppearanceModeManager *)manager renderOptionsForMode:(PSPDFAppearanceMode)mode;

/// Update any UIAppearance changes for the selected mode.
///
/// Can be used to customize the application interface for the selected mode.
/// On iOS 13 and later this can be done using `overrideUserInterfaceStyle`
/// available on `UIViewController` or a `UIView`.
///
/// @param manager A reference to the invoking appearance mode manager.
/// @param mode The mode that is about to be applied.
///
/// @note Overrides the default behavior present on iOS versions prior to iOS 13, if implemented.
- (void)appearanceManager:(PSPDFAppearanceModeManager *)manager applyAppearanceSettingsForMode:(PSPDFAppearanceMode)mode;

/// Update `builder` with any settings specific to the provided `mode`.
///
/// @param manager A reference to the invoking appearance mode manager.
/// @param builder The controller configuration that can be updated.
/// @param mode The mode that is about to be applied.
///
/// @note Overrides the default behavior present on iOS versions prior to iOS 13, if implemented.
- (void)appearanceManager:(PSPDFAppearanceModeManager *)manager updateConfiguration:(PSPDFConfigurationBuilder *)builder forMode:(PSPDFAppearanceMode)mode;

@end

/// Coordinates appearance mode changes.
///
/// On iOS versions prior to iOS 13, this class will update the PDF page rendering style,
/// as well as the UI appearance of certain UI widgets when transitioning in and out of
/// the dark interface style.
///
/// On iOS 13 and later the this class will only change the PDF page rendering style.
/// Any UI appearance changes should be instead handled by the host application via the
/// delegate methods this class offers.
PSPDF_CLASS_SWIFT(PDFAppearanceModeManager)
@interface PSPDFAppearanceModeManager : NSObject<PSPDFOverridable>

/// The currently selected appearance mode. Defaults to `PSPDFAppearanceModeDefault`.
@property (nonatomic) PSPDFAppearanceMode appearanceMode;

/// Sets the appearance mode.
///
/// @param appearanceMode The new mode to apply.
/// @param animated Fades any theme changes if set to `true`. This parameter is not relevant on iOS 13 and later.
- (void)setAppearanceMode:(PSPDFAppearanceMode)appearanceMode animated:(BOOL)animated;

/// The appearance delegate. Can be used to customize the default behaviors for each mode.
@property (nonatomic, weak) id<PSPDFAppearanceModeManagerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
