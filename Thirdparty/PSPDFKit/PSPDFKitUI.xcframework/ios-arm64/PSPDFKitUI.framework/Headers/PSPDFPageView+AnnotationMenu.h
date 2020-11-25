//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFPageView.h>
#import <PSPDFKitUI/PSPDFTextSelectionView.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFNoteAnnotationViewController, PSPDFSignatureFormElement;

@interface PSPDFPageView (AnnotationMenu) <PSPDFAnnotationStyleViewControllerDelegate, PSPDFFontPickerViewControllerDelegate, PSPDFTextSelectionViewDelegate>

/// Returns available `PSPDFMenuItem`s for the current annotation.
/// The better way to extend this is to use the `shouldShowMenuItems:*` delegates.
- (NSArray<PSPDFMenuItem *> *)menuItemsForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// Menu for new annotations (can be disabled in `PDFViewController`). point is in view coordinates.
- (NSArray<PSPDFMenuItem *> *)menuItemsForNewAnnotationAtPoint:(CGPoint)point;

/// Returns available `PSPDFMenuItem`s to change the color.
/// The better way to extend this is to use the shouldShowMenuItems:* delegates.
- (NSArray<PSPDFMenuItem *> *)colorMenuItemsForAnnotation:(PSPDFAnnotation *)annotation;

/// Returns available `PSPDFMenuItem`s to change the fill color (only applies to certain annotations)
- (NSArray<PSPDFMenuItem *> *)fillColorMenuItemsForAnnotation:(PSPDFAnnotation *)annotation;

/// Returns the opacity menu item
- (PSPDFMenuItem *)opacityMenuItemForAnnotation:(PSPDFAnnotation *)annotation withColor:(nullable UIColor *)color;

/// Returns a menu item, that is used for creating a new annotation from the current text selection.
///
/// @note Only supports highlight, underline, squiggly, strike out, redaction, and link annotation types.
/// @note Requires the Redaction license feature when passing `PSPDFAnnotationStringRedaction`, returns `nil` otherwise.
- (nullable PSPDFMenuItem *)textSelectionMenuItemForCreatingAnnotationWithType:(PSPDFAnnotationString)annotationString;

/// Show the inspector.
/// `options` takes presentation option keys.
- (nullable PSPDFAnnotationStyleViewController *)showInspectorForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<NSString *, id> *)options animated:(BOOL)animated;

/// Called when an annotation is found at the tapped location.
/// This will usually call `menuItemsForAnnotation:` to show an `UIMenuController`, except for `PSPDFAnnotationTypeNote` which is handled differently on iPad. (`showNoteControllerForAnnotation`)
///
/// @note The better way to extend this is to use the `shouldShowMenuItems:*` delegates.
- (void)showMenuForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations targetRect:(CGRect)targetRect option:(PSPDFContextMenuOption)contextMenuOption animated:(BOOL)animated;

/// Presents a `PSPDFNoteAnnotationViewController` to show and edit the comments on a `PSPDFAnnotation`.
/// This can be overridden without calling super to show custom UI for annotation notes/comments.
///
/// @param annotation The annotation whose comments should be shown.
/// @param animated Whether the presentation should be animated.
- (void)showNoteControllerForAnnotation:(PSPDFAnnotation *)annotation animated:(BOOL)animated;

/// Shows the font picker.
- (void)showFontPickerForAnnotation:(PSPDFFreeTextAnnotation *)annotation animated:(BOOL)animated;

/// Shows the color picker.
- (void)showColorPickerForAnnotation:(PSPDFAnnotation *)annotation animated:(BOOL)animated;

/// Show the signature controller.
- (void)showSignatureControllerAtRect:(CGRect)viewRect withTitle:(nullable NSString *)title signatureFormElement:(nullable PSPDFSignatureFormElement *)signatureFormElement options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options animated:(BOOL)animated;

/// Font sizes for the free text annotation menu. Defaults to `@[@10, @12, @14, @18, @22, @26, @30, @36, @48, @64]`
@property (nonatomic, readonly) NSArray<NSNumber *> *availableFontSizes;

/// Line width options (ink, border). Defaults to `@[@1, @3, @6, @9, @12, @16, @25, @40]`
@property (nonatomic, readonly) NSArray<NSNumber *> *availableLineWidths;

/// Returns the passthrough views for the popover controllers (e.g. color picker).
/// By default this is fairly aggressive and returns the `pdfController`/`navController`. If you dislike this behavior return nil to enforce the rule first touch after popover = no reaction. However the passthroughViews allow a faster editing of annotations.
@property (nonatomic, readonly) NSArray<UIView *> *passthroughViewsForPopoverController;

@end

@interface PSPDFPageView (AnnotationMenuSubclassingHooks)

/// Show signature menu.
- (void)showNewSignatureMenuAtRect:(CGRect)viewRect signatureFormElement:(nullable PSPDFSignatureFormElement *)signatureFormElement options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options animated:(BOOL)animated;

/// Show digital signature menu.
/// Only shown when `signatureField` is signed already.
- (BOOL)showDigitalSignatureMenuForSignatureField:(PSPDFSignatureFormElement *)signatureField animated:(BOOL)animated;

/// Returns the default color options for the specified annotation type.
///
/// @note The default implementation uses colors from the style manager color presets for certain annotation types (e.g., PSPDFAnnotationTypeHighlight).
- (NSArray<UIColor *> *)defaultColorOptionsForAnnotationType:(PSPDFAnnotationType)annotationType;

/// Controls if the annotation inspector is used or manipulation via `UIMenuController`.
- (BOOL)useAnnotationInspectorForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// Used to prepare the `UIMenuController`-based color menu.
- (void)selectColorForAnnotation:(PSPDFAnnotation *)annotation isFillColor:(BOOL)isFillColor;

/// By default, the markup tool menu is different depending on the currently available space, evaluated via the horizontal size class.
/// In a regular size class we show all the style menu items in the menu, and in compact size class we show a 'Style' submenu.
/// Override this to customize the behavior.
@property (nonatomic, readonly) BOOL shouldMoveStyleMenuEntriesIntoSubmenu;

/// Will create and show the action sheet on long-press above a `PSPDFLinkAnnotation`.
/// Return YES if this was successful.
- (BOOL)showLinkPreviewActionSheetForAnnotation:(PSPDFLinkAnnotation *)annotation fromRect:(CGRect)viewRect animated:(BOOL)animated;

/// Show menu if annotation/text is selected.
- (void)showMenuIfSelectedAnimated:(BOOL)animated;
- (void)showMenuIfSelectedWithOption:(PSPDFContextMenuOption)contextMenuOption animated:(BOOL)animated;

/// Shows a menu as appropriate for a context menu invocation at the given location.
- (void)showMenuForPoint:(CGPoint)location animated:(BOOL)animated;

/// Shows an annotation menu as appropriate for a context menu invocation at the given location.
- (BOOL)showAnnotationMenuAtPoint:(CGPoint)viewPoint animated:(BOOL)animated;

/// The method that checks if the receiver can create annotations, optionally showing a message with the `PSPDFStatusHUD`.
///
/// @param showMessage Specifies whether a message should be displayed if annotations cannot be created.
/// @return `true` if annotations can be created, else `false`.
- (BOOL)canCreateAnnotationsShowMessage:(BOOL)showMessage;

@end

typedef NSString *PSPDFTextMenu NS_EXTENSIBLE_STRING_ENUM NS_SWIFT_NAME(TextMenu);

/// Identifier for the menu item that copies selected text to clipboard.
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuCopy;
/// Identifier for the menu item that shows dictionary definition for selected text. Not available for Mac Catalyst (FB6823989)
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuDefine;
/// Identifier for the menu item that searches the document for the selected text.
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuSearch;
/// Identifier for the menu item that looks up the selected text on Wikipedia.
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuWikipedia;
/// Identifier for the menu item that add a link annotation over the selected text.
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuCreateLink;
/// Identifier for the menu item that speaks the selected text out loud.
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuSpeak;
/// Identifier for the menu item that pauses speaking text out loud.
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuPause;
/// Text menu also uses PSPDFAnnotationMenu[Highlight|Underline|Strikeout|Squiggle].

/// Identifier for opening the iOS share sheet.
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuShare;

/// Identifier for opening a save panel for images. (Mac Catalyst specific)
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuSaveAs;

/// General
/// Annotation types are used from PSPDFAnnotationString* defines
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuCancel;
/// Identifier for the menu item that shows the selected annotation’s note/comments.
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuNote;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuGroup;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuUngroup;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuSave;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuRemove;
/// Identifier for the menu item that copies the selected annotation to the clipboard.
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuCopy;
/// Identifier for the menu item that pastes the clipboard contents as an annotation.
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuPaste;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuMerge;
/// Identifier for the menu item that shows a preview of a file annotation’s file.
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuPreviewFile;

/// Annotation Inspector
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuInspector;
/// Text markup annotation style menu.
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuStyle;

/// Colors
/// For menu colors, we use PSPDFAnnotationMenuColor_index_colorName.
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuColor;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuFillColor;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuOpacity;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuBlendMode;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuCustomColor; // Color Picker

/// Highlights
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuHighlightType; // Type
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuHighlight;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuUnderline;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuStrikeout;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuSquiggle;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuRedaction;

/// Ink
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuThickness;

/// Sound annotations
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuPlay;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuPause;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuPauseRecording;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuContinueRecording;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuFinishRecording;

/// Free Text
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuEdit;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuSize;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuFont;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuAlignment;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuAlignmentLeft;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuAlignmentCenter;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuAlignmentRight;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuFitToText;

/// Line/Polyline
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineStart;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineEnd;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeNone;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeSquare;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeCircle;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeDiamond;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeOpenArrow;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeClosedArrow;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeButt;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeReverseOpenArrow;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeReverseClosedArrow;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeSlash;

@interface PSPDFPageView (MenuDeprecated)
- (void)showMenuIfSelectedAnimated:(BOOL)animated allowPopovers:(BOOL)allowPopovers PSPDF_DEPRECATED_IOS(9.1, "Call `showMenuIfSelectedWithOption:animated:` instead");
- (void)showMenuForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations targetRect:(CGRect)targetRect allowPopovers:(BOOL)allowPopovers animated:(BOOL)animated PSPDF_DEPRECATED_IOS(9.1, "Call `showMenuForAnnotations:targetRect:option:animated:` instead");
@end

NS_ASSUME_NONNULL_END
