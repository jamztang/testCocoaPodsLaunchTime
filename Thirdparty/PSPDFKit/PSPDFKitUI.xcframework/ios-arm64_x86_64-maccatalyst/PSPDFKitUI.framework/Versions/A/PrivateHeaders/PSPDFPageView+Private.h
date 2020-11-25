//
//  Copyright © 2011-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationStyleManager.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFOverrideProvider.h>
#import <PSPDFKit/PSPDFReusableObjectCache.h>
#import <PSPDFKitUI/PSPDFPageView+AnnotationMenu.h>
#import <PSPDFKitUI/PSPDFPageView+Scribble.h>
#import <PSPDFKitUI/PSPDFTextSelectionView+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFFormElement, PSPDFKeyboardHandlingView, PSPDFPage, PSPDFBookmarkIndicatorButton, PSPDFDocument, PSPDFViewState, PSPDFDocumentView, PSPDFDocumentViewController, PSPDFPageViewDragAndDropHandler;

// Options for `add/removeAnnotation:option:animated:`
// Also see `PSPDFAnnotationOptionAnimateView` in PSPDFAnnotationProvider.h
PSPDF_EXTERN PSPDFAnnotationOption const PSPDFAnnotationOptionIgnoreOverlayState;
PSPDF_EXTERN PSPDFAnnotationOption const PSPDFAnnotationOptionRenderImmediately; // add only
PSPDF_EXTERN PSPDFAnnotationOption const PSPDFAnnotationOptionWaitForNextPageUpdate; // remove only

/// If `true`, annotation inspector will not be dismissed when deselecting
/// annotations. Valid only during deselection.
PSPDF_EXTERN PSPDFAnnotationOption const PSPDFAnnotationOptionDoNotDismissInspector;

/// If `true`, `didSelectAnnotations` and `didDeselectAnnotations` delegate methods
/// will be called when selecting or deselecting annotations.
PSPDF_EXTERN PSPDFAnnotationOption const PSPDFAnnotationOptionInformDelegate;

/// The minimum touch area in screen coordinates
PSPDF_TEST_EXPORT const CGFloat PSPDFScreenHitTestRectSize;

/// A block type called after a page update has been completed.
typedef void (^PSPDFPageUpdateBlock)(BOOL);

@interface PSPDFPageView () <PSPDFReusable, PSPDFOverrideProvider, PSPDFTextSelectionViewDataSource>

/*
 readwrite upgrade from the PSPDFReusable protocol. This needs to be set by the
 initialization block in `PSPDFSpreadView`.
 */
@property (nonatomic, copy, nullable) NSString *reuseIdentifier;

/// The document the page view is rendering pages from. Derived from the presentation context if not set.
@property (nonatomic, nullable) PSPDFDocument *document;

/// The parent document view.
@property (nonatomic, readonly, nullable) PSPDFDocumentView *documentView;

/// The parent document view controller.
@property (nonatomic, readonly, nullable) PSPDFDocumentViewController *documentViewController;

/// Allows write access to the current page.
@property (nonatomic) PSPDFPageIndex pageIndex;

/// Returns the page object.
@property (nonatomic, readonly) PSPDFPage *page;

/// Temporarily suspend rendering updates to the renderView.
@property (nonatomic) BOOL suspendUpdate;

/// The bookmark indicator button, if the configuration requires it
@property (nonatomic, nullable) PSPDFBookmarkIndicatorButton *bookmarkIndicatorButton;

/// Timestamp of the last user interaction. Used to determine page focus after rotating device.
@property (nonatomic, readonly) CFTimeInterval lastInteractionTime;

/// Indicates if the page view has loaded annotations (they might be loaded on a background thread)
@property (nonatomic, readonly) BOOL hasLoadedAnnotations;

/// The internal drag and drop handler.
@property (nonatomic, readonly, nullable) PSPDFPageViewDragAndDropHandler *dragAndDropHandler;

/// Interaction object used to allow Scribbling on the entire page.
@property (nonatomic, readonly, nullable) UIIndirectScribbleInteraction *indirectScribbleInteraction API_AVAILABLE(ios(14.0));

/// Property used to determine the focused annotation during scribbling.
@property (nonatomic) CGRect lastRequestedScribbleRect;

/// Unique identifier for the current page view used during scribbling.
@property (nonatomic) NSUUID *annotationContainerViewUUID;

/// Updates lastInteractionTime to now.
- (void)markInteraction;

/// Returns a Boolean value indicating if an inspector can be shown for the provided annotations.
- (BOOL)canShowInspectorForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// Update page view after a small delay. Optionally animated.
- (void)setNeedsUpdateAnimated:(BOOL)animated;

/// Update page view immediately, without enqueueing. Optionally animated.
- (void)updateAnimated:(BOOL)animated;

/// Hides all additional page elements — potentially animated.
- (void)hidePageElementsAnimated:(BOOL)animated;

/// Remove a page annotation/view as soon as the page has been refreshed. Will also refresh page.
- (void)removeViewOnNextPageUpdate:(UIView *)view;

/// Adds a view on the next page update.
- (void)addViewOnNextPageUpdate:(UIView *)view;

/// Executes the provided block on the next page update.
///
/// @param block The block to be executed. `finished` will be false
/// if the block is removed from the page view before the page update
/// completes (e.g., due to pageView resue).
- (void)performBlockOnNextPageUpdate:(PSPDFPageUpdateBlock)block;

/// Returns the first annotation view of the provided class.
/// Queries both annotationContainerView subviews and viewsToBeAdded.
- (nullable UIView *)firstAnnotationViewOfClass:(Class)queriedClass;

/// Will parse the text glyphs async to allow text selection. Override to disable.
- (void)preloadTextParser;

/// Form Element tap processing.
PSPDF_EXTERN NSString *const PSPDFToggleFormElementKey;
PSPDF_EXTERN NSString *const PSPDFZoomFormElementKey;

/// Helper to correctly delete annotations after checking permissions.
- (nullable NSArray<PSPDFAnnotation *> *)deleteAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// Get the shared, private keyboard handler.
@property (nonatomic, readonly, nullable) PSPDFKeyboardHandlingView *keyboardHandler;

/// Set block that is executed within `updateShadow` when `isShadowEnabled = YES`.
@property (nonatomic, copy, nullable) void (^updateShadowBlock)(PSPDFPageView *pageView);

/// Presentation helper to display an alert view while calling the delegates.
- (BOOL)presentAlertController:(PSPDFAlertController *)alertController options:(nullable NSDictionary<NSString *, id> *)options sender:(nullable id)sender animated:(BOOL)animated;

/// Applies the view state to the receiver.
///
/// @param viewState The view state to apply.
/// @note This method currently only applies `PSPDFViewState.selectionState`.
- (void)applyViewState:(PSPDFViewState *)viewState;

/// Views waiting to become visible.
@property (nonatomic, readonly) NSMutableSet<UIView *> *viewsToBeAdded;
@property (nonatomic, readonly) NSMutableSet<UIView *> *viewsToBeRemoved;

/// Shared queue. Exposed for testing teardown.
@property (nonatomic, class, readonly) NSOperationQueue *pageViewQueue;

/// To allow tap to edit
@property (nonatomic, readonly, nullable) NSHashTable<UIMenuItem *> *lastVisibleMenuItems;

/// Indicates whether menus should be invoked via the context menu gesture instead of being displayed automatically.
/// Default behaviour: `true` on Mac Catalyst and `false` otherwise.
@property (nonatomic, readonly) BOOL usesContextMenus;

/// Required so we can forward the delegate from the enclosing scroll view.
- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset;

#pragma mark Annotation Interaction

/// Returns annotations that can be tapped at the given location.
///
/// This method will add a variance of a few pixels to the point to make selecting
/// small annotations easier.
///
/// @note This method doesn't consult `editableAnnotationTypes`. You must filter
/// the results yourself!
///
/// @note Setting selected annotations programmatically **does not** take the return
/// value of this method into consideration.
///
/// @param point The point in page view's coordinate space.
///
/// @returns An array of tappable annotations at the given location.
- (NSArray<PSPDFAnnotation *> *)allTappableAnnotationsAtPoint:(CGPoint)point;

/// Select or deselect the given annotations.
///
/// In contrast to `selectAnnotation...` and `deselectAnnotations...` mehtods, this
/// method sets the given array of annotations directly, without resolving the
/// enclosing groups.
///
/// @param annotations Annotations to become selected or `nil` if deselecting.
/// @param options Selection/deselection options.
/// @param animated Whether to animate view controller transitions.
- (void)setSelectedAnnotations:(nullable NSArray<PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<PSPDFAnnotationOption, NSNumber /* BOOL */ *> *)options animated:(BOOL)animated;

/// Select the given annotation, along with its enclosing group. The menu is not
/// automatically shown afterwards.
///
/// @param annotation Annotation to become selected.
/// @param options Selection options.
/// @param animated Whether to animate view controller transitions.
- (void)selectAnnotation:(PSPDFAnnotation *)annotation options:(nullable NSDictionary<PSPDFAnnotationOption, NSNumber /* BOOL */ *> *)options animated:(BOOL)animated;

/// Select the given form element.
///
/// @param formElement Form element to select.
/// @param options Selection options.
/// @param animated Whether to animate view controller transitions.
///
/// @returns Whether the given form element was successfully selected.
- (BOOL)selectFormElement:(PSPDFFormElement *)formElement options:(nullable NSDictionary<NSString *, NSNumber /* BOOL */ *> *)options animated:(BOOL)animated;

/// Deselect any selected annotations and hide the menu.
///
/// @param options Deselection options.
/// @param animated Whether to animate view controller transitions.
- (void)deselectAnnotationsWithOptions:(nullable NSDictionary<PSPDFAnnotationOption, NSNumber /* BOOL */ *> *)options animated:(BOOL)animated;

/// Deselect any currently selected annotations **or text**.
///
/// @param animated Whether to animate view controller transitions.
- (void)discardSelectionAnimated:(BOOL)animated;

@end

@interface PSPDFPageView (Shortcuts)

/// Shortcut to access the textParser corresponding to the current page.
@property (nonatomic, readonly, nullable) PSPDFTextParser *textParser;

/// The document provider in the document corresponding to the page view's page.
@property (nonatomic, readonly, nullable) PSPDFDocumentProvider *documentProvider;

/// The current configuration, queried via the configuration data source.
@property (nonatomic, copy, readonly, nullable) PSPDFConfiguration *configuration;

@end

@interface PSPDFPageView (AnnotationMenuPrivate)

/// Handle action. `rect` is page relative.
- (void)handleTouchUpForAnnotationIgnoredByDelegate:(PSPDFAnnotation *)annotation inRect:(CGRect)rect;

/// Used to calculate the rect for showing the annotation menu and popovers.
- (CGRect)presentationRectForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// Can be overridden to customize the actions that are shown in the link annotation long-press alert.
- (NSArray<UIAlertAction *> *)alertActionsForLinkPreviewActionSheetWithDefaultActions:(NSArray<UIAlertAction *> *)actions;

/// Copies selected text, image or annotation to the pasteboard.
///
/// @param sender The object invoking the action.
- (void)copy:(nullable id)sender;

/// Copies selected text, image or annotation to the pasteboard.
/// Removes annotations after copying, but doesn't remove other types of data.
///
/// @param sender The object invoking the action.
- (void)cut:(nullable id)sender;

/// Pastes the contents of the clipboard as a new annotation,
/// provided the clipboard contents is an annotation or can
/// be converted to an annotation.
///
/// @param sender The object invoking the action.
- (void)paste:(nullable id)sender;

@end

/// Line end image helper.
PSPDF_EXTERN UIImage *PSPDFImageForLineEndTypeOfColorAndSize(UIColor *_Nullable color, UIColor *_Nullable fillColor, PSPDFLineEndType endType, CGSize imageSize, NSUInteger pointNumber);

/// Enum for the values shown in the link annotation long-press menu
/// that apply only when link editing is enabled.
typedef NSString *PSPDFLinkEditingMenu NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(LinkEditingMenu);

PSPDF_EXPORT const PSPDFLinkEditingMenu PSPDFLinkEditingMenuNote;
PSPDF_EXPORT const PSPDFLinkEditingMenu PSPDFLinkEditingMenuComments;
PSPDF_EXPORT const PSPDFLinkEditingMenu PSPDFLinkEditingMenuEditLink;
PSPDF_EXPORT const PSPDFLinkEditingMenu PSPDFLinkEditingMenuMoveLink;
PSPDF_EXPORT const PSPDFLinkEditingMenu PSPDFLinkEditingMenuRemoveLink;

NS_ASSUME_NONNULL_END
