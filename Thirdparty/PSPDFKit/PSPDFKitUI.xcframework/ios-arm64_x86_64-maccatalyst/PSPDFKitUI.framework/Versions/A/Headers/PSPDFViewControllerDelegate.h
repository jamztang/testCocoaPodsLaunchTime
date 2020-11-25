//
//  Copyright © 2011-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFViewController.h>
#import <PSPDFKit/PSPDFDocument.h>
#import <PSPDFKit/PSPDFMacros.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFAnnotationPresenting;
@class PSPDFAnnotation, PSPDFGlyph, PSPDFImageInfo, PSPDFMenuItem, PSPDFPageInfo, PSPDFPageView, PSPDFScrollView;

/// Helper method that will dig into popovers, navigation controllers, container view controllers or other controller view hierarchies and dig out the requested class if found.
PSPDF_EXPORT id _Nullable PSPDFChildViewControllerForClass(UIViewController *_Nullable controller, Class controllerClass);

/// Implement this delegate in your `UIViewController` to get notified of `PDFViewController` events.
PSPDF_PROTOCOL_SWIFT(PDFViewControllerDelegate)
@protocol PSPDFViewControllerDelegate<NSObject>

@optional

#pragma mark Document Handling

/// Asks the delegate if the specified document should be saved with the provided options.
///
/// @param pdfController   The PSPDFViewController instance.
/// @param document        The document to save.
/// @param options         The current options that the document is going to be saved with. This is an inout parameter.
///
/// @return BOOL indicating whether the passed document should be saved with the passed parameters.
///
/// @note This method will only be called if the view controller's PSPDFConfiguration autosave option is set to YES, and its annotation save mode is set to a value other than PSPDFAnnotationSaveModeDisabled.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldSaveDocument:(PSPDFDocument *)document withOptions:(NSDictionary<PSPDFDocumentSaveOption, id> * _Nonnull * _Nonnull)options;

/// Notifies the delegate that the specified document's saving operation was completed.
///
/// @param pdfController   The PSPDFViewController instance.
/// @param document        The document that was saved.
/// @param error           The error that occurred during document saving, if any. Can be nil.
///
/// @note This method will only be called if the view controller's PSPDFConfiguration autosave option is set to YES, and its annotation save mode is set to a value other than PSPDFAnnotationSaveModeDisabled.
- (void)pdfViewController:(PSPDFViewController *)pdfController didSaveDocument:(PSPDFDocument *)document error:(nullable NSError *)error;

/// Will be called when an action tries to change the document (For example, a PDF link annotation pointing to another document).
/// Will also be called when the document is changed via using the `document` property.
/// Return NO to block changing the document.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldChangeDocument:(nullable PSPDFDocument *)document;

/// Will be called after the document has been changed.
///
/// @note This will also be called for nil and broken documents. use `document.isValid` to check.
- (void)pdfViewController:(PSPDFViewController *)pdfController didChangeDocument:(nullable PSPDFDocument *)document;

#pragma mark Scroll and Page Events

// If you need more scroll events, subclass `PSPDFScrollView` and relay your custom scroll events. Don't forget calling super though.

/// Called when a page view schedules a render task to update its content view.
///
/// Once the render tasks completes, `pdfViewController:didFinishRenderTaskForPageView:`
/// will be called.
///
/// @see pdfViewController:didFinishRenderTaskForPageView:
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that scheduled the render task.
- (void)pdfViewController:(PSPDFViewController *)pdfController willScheduleRenderTaskForPageView:(PSPDFPageView *)pageView;

/// Called when a render task finishes that was scheduled by a page view to update
/// its content view.
///
/// @see pdfViewController:willScheduleRenderTaskForPageView:
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that scheduled the render task.
- (void)pdfViewController:(PSPDFViewController *)pdfController didFinishRenderTaskForPageView:(PSPDFPageView *)pageView;

/// Called when a page view sets an image on its content view. This image can either
/// be a full sized image, a smaller image that is used while waiting for a full
/// sized image, or `nil`. The image might be acquired from the cache or from a render task.
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that updated its content view's image.
/// @param placeholder YES if the image set in the content view is just a placeholder
/// while waiting for a full resolution image from the render engine.
/// The placeholder image might also be `nil`.
- (void)pdfViewController:(PSPDFViewController *)pdfController didUpdateContentImageForPageView:(PSPDFPageView *)pageView isPlaceholder:(BOOL)placeholder;

/// Called before a page view enters the visible screen area.
///
/// You can use this method to customize the page view before it is displayed. Say, for example, you’ve built a custom user
/// interface for searching, you can use this method to add the search highlights to the page before it comes on screen.
///
/// This call is bound to the page view’s spread view and will be triggered before the spread view enters the visible
/// screen area. As such, you should _generally avoid_ to begin view animations on the page in this callback:
/// CoreAnimation may skip the animation of off-screen elements.
/// If you want to animate changes to the page’s view hierarchy, have a look at
/// `PSPDFDocumentViewControllerSpreadIndexDidChangeNotification` instead.
///
/// This call will not be invoked for page views belonging to spreads that have
/// an active first responder. This matches the behavior of similar
/// `UICollectionViewDelegate` callbacks.
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that is about to enter the visible screen.
/// @param pageIndex The page index of the page that this page view will display.
- (void)pdfViewController:(PSPDFViewController *)pdfController willBeginDisplayingPageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;

/// Called when a page view exits the visible screen area.
///
/// This call is bound to the page view's spread view and will be triggered when
/// the spread view leaves the visible screen area.
///
/// This call will not be invoked for page views belonging to spreads that have
/// an active first responder. This matches the behavior of similar
/// `UICollectionViewDelegate` callbacks.
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that exits the visible screen.
/// @param pageIndex The page index of the page that this page view has displayed.
- (void)pdfViewController:(PSPDFViewController *)pdfController didEndDisplayingPageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;


/// Called when a page view is configured for the view hierarchy.
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that is configured for the view hierarchy.
/// @param pageIndex The page index of the page that this page view will display.
- (void)pdfViewController:(PSPDFViewController *)pdfController didConfigurePageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;

/// Called when a page view is cleaned up from the view hierarchy.
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that is removed from the view hierarchy.
/// @param pageIndex The page index of the page that this page view has displayed.
- (void)pdfViewController:(PSPDFViewController *)pdfController didCleanupPageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;

/// Return a PSPDFDocument for a relative path.
/// If this returns nil, we try to find the PDF ourselves with using the current document's `basePath`.
- (nullable PSPDFDocument *)pdfViewController:(PSPDFViewController *)pdfController documentForRelativePath:(NSString *)relativePath;

#pragma mark Text Selection

/// Called when text is about to be selected. Return NO to disable text selection.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldSelectText:(NSString *)text withGlyphs:(NSArray<PSPDFGlyph *> *)glyphs atRect:(CGRect)rect onPageView:(PSPDFPageView *)pageView;

/// Called after text has been selected.
/// Will also be called when text has been deselected. Deselection sometimes cannot be stopped, so the `shouldSelectText:` will be skipped.
- (void)pdfViewController:(PSPDFViewController *)pdfController didSelectText:(NSString *)text withGlyphs:(NSArray<PSPDFGlyph *> *)glyphs atRect:(CGRect)rect onPageView:(PSPDFPageView *)pageView;

#pragma mark Menu Handling

/// Called before the menu for text selection is displayed.
/// All coordinates are in view coordinate space.
///
/// Using `PSPDFMenuItem` will help with adding custom menu's w/o hacking the responder chain.
/// Default returns menuItems if not implemented. Return nil or an empty array to not show the menu.
///
/// Use `PSPDFMenuItem`’s `identifier` property to check and modify the menu items. This string will not be translated. (vs the title property)
///
/// `rect` is in the coordinate space of the `pageView`.
/// `annotationRect` or `textRect` is in the PDF coordinate space of the current page.
- (NSArray<PSPDFMenuItem *> *)pdfViewController:(PSPDFViewController *)pdfController shouldShowMenuItems:(NSArray<PSPDFMenuItem *> *)menuItems atSuggestedTargetRect:(CGRect)rect forSelectedText:(NSString *)selectedText inRect:(CGRect)textRect onPageView:(PSPDFPageView *)pageView;

/// Called before the menu for a selected image is displayed.
- (NSArray<PSPDFMenuItem *> *)pdfViewController:(PSPDFViewController *)pdfController shouldShowMenuItems:(NSArray<PSPDFMenuItem *> *)menuItems atSuggestedTargetRect:(CGRect)rect forSelectedImage:(PSPDFImageInfo *)selectedImage inRect:(CGRect)textRect onPageView:(PSPDFPageView *)pageView;

/// Called before we're showing the menu for an annotation.
/// If annotation is nil, we show the menu to create *new* annotations (in that case annotationRect will also be nil)
/// This delegate is also called as you dig into sub-menus like the color options.
///
/// @note You should filter out unwanted menu items as a blacklist - if you try to whitelist menu items, you might break functionality,
/// unless you explore every annotation type and every sub-menu and very carefully allow all entries.
/// The `identifier` property of the `PSPDFMenuItem` object is not loacalized and perfect for comparison.
- (NSArray<PSPDFMenuItem *> *)pdfViewController:(PSPDFViewController *)pdfController shouldShowMenuItems:(NSArray<PSPDFMenuItem *> *)menuItems atSuggestedTargetRect:(CGRect)rect forAnnotations:(nullable NSArray<PSPDFAnnotation *> *)annotations inRect:(CGRect)annotationRect onPageView:(PSPDFPageView *)pageView;

#pragma mark Annotations

/// Called before a annotation view is created and added to a page. Defaults to YES if not implemented.
///
/// @warning This will only be called for annotations that render as an overlay (that return YES for isOverlay)
/// If NO is returned, viewForAnnotation will not be called.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldDisplayAnnotation:(PSPDFAnnotation *)annotation onPageView:(PSPDFPageView *)pageView;

/// Delegate for tapping annotations.
///
/// Return YES to override the default action and custom-handle this.
/// Default actions might be scroll to target page, open Safari, show a menu, ...
///
/// Some annotations might not have an `annotationView` attached. (because they are rendered with the page content, for example highlight annotations)
///
/// @note This will not fire if you interact with annotation views like the `PSPDFGalleryView`.
/// See these subclasses for details (e.g. `PSPDFMediaPlayerControllerPlaybackDidStartNotification`)
///
/// @param annotationPoint the point relative to the `PSPDFAnnotation`, in PDF coordinate space.
/// @param viewPoint the point relative to the `PDFPageView`.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController didTapOnAnnotation:(PSPDFAnnotation *)annotation annotationPoint:(CGPoint)annotationPoint annotationView:(nullable UIView<PSPDFAnnotationPresenting> *)annotationView pageView:(PSPDFPageView *)pageView viewPoint:(CGPoint)viewPoint NS_SWIFT_NAME(pdfViewController(_:didTapOn:annotationPoint:annotationView:pageView:viewPoint:));

/// Called before an annotation will be selected. (but after `didTapOnAnnotation:`)
- (NSArray<PSPDFAnnotation *> *)pdfViewController:(PSPDFViewController *)pdfController shouldSelectAnnotations:(NSArray<PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView;

/// Called after an annotation has been selected by a touch directly on the
/// page view.
///
/// Note that this method isn't called for indirect selections, for example when a
/// newly created annotation is selected, a set of annotations are selected using
/// the selection tool, or an annotation is selected via the list of annotations.
///
/// For exact diff tracking, consider using the `didSelectAnnotations:` and
/// `didDeselectAnnotations:` subclass hooks of `PDFPageView`.
- (void)pdfViewController:(PSPDFViewController *)pdfController didSelectAnnotations:(NSArray<PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView;

/// Called after an annotation has been deselected by a touch directly on the
/// page view.
///
/// Note that this method isn't called for indirect selections, for example when a
/// newly created annotation is selected, a set of annotations are selected using
/// the selection tool, or an annotation is selected via the list of annotations.
///
/// For exact diff tracking, consider using the `didSelectAnnotations:` and
/// `didDeselectAnnotations:` subclass hooks of `PDFPageView`.
- (void)pdfViewController:(PSPDFViewController *)pdfController didDeselectAnnotations:(NSArray<PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView;

/// Returns a pre-generated `annotationView` that can be modified before being added to the view.
/// If no generator for a custom annotation is found, `annotationView` will be nil (as a replacement to viewForAnnotation)
/// To get the targeted rect use `[annotation boundingBoxForPageRect:pageView.bounds]`;
- (nullable UIView<PSPDFAnnotationPresenting> *)pdfViewController:(PSPDFViewController *)pdfController annotationView:(nullable UIView<PSPDFAnnotationPresenting> *)annotationView forAnnotation:(PSPDFAnnotation *)annotation onPageView:(PSPDFPageView *)pageView;

/// Invoked prior to the presentation of the annotation view: use this to configure actions etc
///
/// @warning This will only be called for annotations that render as an overlay (that return YES for `isOverlay`)
/// `PSPDFLinkAnnotations` are handled differently (they don't have a selected state) - delegate will not be called for those.
- (void)pdfViewController:(PSPDFViewController *)pdfController willShowAnnotationView:(UIView<PSPDFAnnotationPresenting> *)annotationView onPageView:(PSPDFPageView *)pageView;

/// Invoked after animation used to present the annotation view
///
/// @warning This will only be called for annotations that render as an overlay (that return YES for `isOverlay`)
/// `PSPDFLinkAnnotations` are handled differently (they don't have a selected state) - delegate will not be called for those.
- (void)pdfViewController:(PSPDFViewController *)pdfController didShowAnnotationView:(UIView<PSPDFAnnotationPresenting> *)annotationView onPageView:(PSPDFPageView *)pageView;

#pragma mark View Controller Management

/// Called before we show a internal controller (color picker, note editor, ...) modally or in a popover. Allows last minute modifications.
///
/// Return NO to process the displaying manually.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldShowController:(UIViewController *)controller options:(nullable NSDictionary<NSString *, id> *)options animated:(BOOL)animated;

/// Called after the controller has been fully displayed.
- (void)pdfViewController:(PSPDFViewController *)pdfController didShowController:(UIViewController *)controller options:(nullable NSDictionary<NSString *, id> *)options animated:(BOOL)animated;

#pragma mark General View State

/// Will be called when `viewMode` changes.
- (void)pdfViewController:(PSPDFViewController *)pdfController didChangeViewMode:(PSPDFViewMode)viewMode;

/// Called before the view controller will be dismissed (either by modal dismissal, or popping from the navigation stack).
/// Called before PSPDFKit tries to save any dirty annotation.
///
/// @note If you use child view containment then the dismissal might not be properly detected.
- (void)pdfViewControllerWillDismiss:(PSPDFViewController *)pdfController;

/// Called after the view controller has been dismissed (either by modal dismissal, or popping from the navigation stack).
///
/// @note If you use child view containment then the dismissal might not be properly detected.
- (void)pdfViewControllerDidDismiss:(PSPDFViewController *)pdfController;

#pragma mark Display State

/// Called after the view controller changed its controller state or its controller state error.
///
/// @param pdfController   The controller that changed its state.
/// @param controllerState The new state that the controller was changed to.
/// @param error           The underlying error if the controllerState provided is either .error or .locked.
- (void)pdfViewController:(PSPDFViewController *)pdfController didChangeControllerState:(PSPDFControllerState)controllerState error:(nullable NSError *)error;

#pragma mark user interface

/// Return NO to stop the user interface change event.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldShowUserInterface:(BOOL)animated;

/// User interface was displayed (called after the animation finishes)
- (void)pdfViewController:(PSPDFViewController *)pdfController didShowUserInterface:(BOOL)animated;

/// Return NO to stop the user interface change event.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldHideUserInterface:(BOOL)animated;

/// User interface was hidden (called after the animation finishes)
- (void)pdfViewController:(PSPDFViewController *)pdfController didHideUserInterface:(BOOL)animated;

#pragma mark Actions

/// Called every time before an action will be executed.
/// Actions can come from many sources: Links, Forms, or any other annotation type (via additionalActions)
/// Actions can be invoked on trigger events like PSPDFAnnotationTriggerEventMouseDown.
/// Using the back/forward list will also trigger actions.
///
/// Return NO to prevent the PDF action from being executed.
///
/// @note This is also called for every sub-action the action has.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldExecuteAction:(PSPDFAction *)action;

/// Called every time after an action has been executed.
///
/// @note This is also called for every sub-action the action has.
- (void)pdfViewController:(PSPDFViewController *)pdfController didExecuteAction:(PSPDFAction *)action;

#pragma mark Deprecated API

/// @warning This delegate method has been removed in PSPDFKit 9.5 and is no longer
/// called. You must add your own tap gesture recognizer and use the interaction
/// components to set up relationships with the internal gesture recognizrs. For
/// more information, check out the migration guide:
/// https://pspdfkit.com/guides/ios/current/migration-guides/pspdfkit-95-migration-guide
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController didTapOnPageView:(PSPDFPageView *)pageView atPoint:(CGPoint)viewPoint PSPDF_DEPRECATED_IOS(9.5, "Add your own gesture recognizer instead.");

/// @warning This delegate method has been removed in PSPDFKit 9.5 and is no longer
/// called. You must add your own long press gesture recognizer and use the
/// interaction components to set up relationships with the internal gesture
/// recognizers. For more information, check out the migration guide:
/// https://pspdfkit.com/guides/ios/current/migration-guides/pspdfkit-95-migration-guide
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController didLongPressOnPageView:(PSPDFPageView *)pageView atPoint:(CGPoint)viewPoint gestureRecognizer:(UILongPressGestureRecognizer *)gestureRecognizer PSPDF_DEPRECATED_IOS(9.5, "Add your own gesture recognizer instead.");

@end

NS_ASSUME_NONNULL_END
