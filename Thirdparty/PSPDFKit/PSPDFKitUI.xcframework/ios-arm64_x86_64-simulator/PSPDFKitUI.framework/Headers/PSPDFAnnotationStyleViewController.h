//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationStyleKey.h>
#import <PSPDFKit/PSPDFAnnotationZIndexMove.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFFontPickerViewController.h>
#import <PSPDFKitUI/PSPDFStaticTableViewController.h>
#import <PSPDFKitUI/PSPDFStyleable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotationStyleViewController, PSPDFAnnotation;
@protocol PSPDFAnnotationPresenting;

/// Delegate for `AnnotationStyleViewController`.
PSPDF_PROTOCOL_SWIFT(AnnotationStyleViewControllerDelegate)
@protocol PSPDFAnnotationStyleViewControllerDelegate<NSObject>

/// Called whenever one or more style properties of `AnnotationStyleViewController` change.
- (void)annotationStyleController:(PSPDFAnnotationStyleViewController *)styleController didChangeProperties:(NSArray<NSString *> *)propertyNames;

@optional

/// Called when a user starts changing a property (e.g. touch down on the slider)
///
/// @warning There might not be a call to `didChangeProperty:` if the user doesn't actually change the value (just touches it)
/// @note Will not be fired for all properties.
- (void)annotationStyleController:(PSPDFAnnotationStyleViewController *)styleController willStartChangingProperty:(NSString *)propertyName;

/// Called when a user finishes changing a property (e.g. slider touch up)
///
/// @note Will not be fired for all properties.
- (void)annotationStyleController:(PSPDFAnnotationStyleViewController *)styleController didEndChangingProperty:(NSString *)propertyName;

/// Should return the annotation view that currently represents the provided `annotation`, if available.
/// Important for free text annotation sizing.
- (nullable UIView<PSPDFAnnotationPresenting> *)annotationStyleController:(PSPDFAnnotationStyleViewController *)styleController annotationViewForAnnotation:(PSPDFAnnotation *)annotation;

/// Called when the annotation style view controller triggers a z-index move.
/// The delegate is responsible for actually executing the z-index move.
- (void)annotationStyleController:(PSPDFAnnotationStyleViewController *)styleController executeZIndexMove:(PSPDFAnnotationZIndexMove)zIndexMove;

/// Called to determine if the annotation style view controller can execute a z-index move.
/// This causes the z-index reordering buttons to be enabled or disabled accordingly.
- (BOOL)annotationStyleController:(PSPDFAnnotationStyleViewController *)styleController canExecuteZIndexMove:(PSPDFAnnotationZIndexMove)zIndexMove;

@end

/// An inspector that allows users to view and change the properties of annotations.
///
/// @note The inspector currently only supports setting *one* annotation, but since long-term we want multi-select-change, the API has already been prepared for.
PSPDF_CLASS_SWIFT(AnnotationStyleViewController)
@interface PSPDFAnnotationStyleViewController : PSPDFStaticTableViewController<PSPDFFontPickerViewControllerDelegate, PSPDFStyleable, PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Designated initializer.
/// Initialize the controller with one or multiple annotations.
- (instancetype)initWithAnnotations:(nullable NSArray<PSPDFAnnotation *> *)annotations NS_DESIGNATED_INITIALIZER;

/// The current selected annotations.
@property (nonatomic, copy, nullable) NSArray<PSPDFAnnotation *> *annotations;

/// Controller delegate. Informs about begin/end editing a property.
@property (nonatomic, weak) IBOutlet id<PSPDFAnnotationStyleViewControllerDelegate> delegate;

/// Shows a preview area on top. Defaults to NO.
@property (nonatomic) BOOL showPreviewArea;

#pragma mark Customization

/// List of supported inspector properties for various annotation types
///
/// The dictionary is keyed by annotation type (`PSPDFAnnotationString`).
/// The values are either:
/// - an array of arrays of property name strings (see `PSPDFAnnotationStyleKeyGroupedList`)
/// - a block taking an annotation and returning `PSPDFAnnotationStyleKeyGroupedList` for it (see `PSPDFAnnotationStyleBlock`)
///
/// See `AnnotationStyle.Key` for a list of supported keys.
///
/// Defaults to an empty dictionary. Normally set to the values from PSPDFConfiguration after initialization.
@property (nonatomic, copy) NSDictionary<PSPDFAnnotationString, id> *propertiesForAnnotations;

/// Shows a custom cell with configurable color presets for the provided annotation types.
/// Defaults to PSPDFAnnotationTypeAll. Normally set to the values from PSPDFConfiguration after initialization.
@property (nonatomic) PSPDFAnnotationType typesShowingColorPresets;

/// Saves changes to the color presets. Defaults to YES.
@property (nonatomic) BOOL persistsColorPresetChanges;

/// Determines if changing the z-index is supported.
/// If enabled, a row with buttons allowing changing the z-index will be shown.
///
/// This only works for existing annotations, not when previewed from the annotation toolbar.
///
/// Usually set to the `allowAnnotationZIndexMoves` value of `PDFConfiguration`.
///
/// Defaults to YES.
@property (nonatomic) BOOL allowAnnotationZIndexMoves;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFAnnotationStyleViewController (SubclassingHooks)

/// Returns the list of properties where we want to build cells for.
///
/// @note The arrays can be used to split the properties into different sections.
- (NSArray<NSArray<PSPDFAnnotationStyleKey> *> *)propertiesForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

@end

NS_ASSUME_NONNULL_END
