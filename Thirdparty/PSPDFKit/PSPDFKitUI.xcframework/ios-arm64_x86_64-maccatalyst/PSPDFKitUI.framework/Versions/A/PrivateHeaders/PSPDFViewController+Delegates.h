//
//  Copyright © 2012-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFViewController.h>

#import <PSPDFKitUI/PSPDFAlertController.h>
#import <PSPDFKitUI/PSPDFViewControllerDelegate.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation, PSPDFGlyph, PSPDFImageInfo, PSPDFMenuItem, PSPDFPageInfo, PSPDFPageView;
@protocol PSPDFAnnotationPresenting;

@interface PSPDFViewController (Delegates)

- (BOOL)delegateShouldChangeDocument:(nullable PSPDFDocument *)document;
- (void)delegateDidChangeDocument;

- (void)delegateWillScheduleRenderTaskForPageView:(PSPDFPageView *)pageView;
- (void)delegateDidFinishRenderTaskForPageView:(PSPDFPageView *)pageView;

- (void)delegateDidUpdateContentImageForPageView:(PSPDFPageView *)pageView isPlaceholder:(BOOL)placeholder;

- (void)delegateDidChangeViewMode:(PSPDFViewMode)viewMode;

- (void)delegateWillBeginDisplayingPageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;
- (void)delegateDidEndDisplayingPageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;

- (void)delegateDidConfigurePageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;
- (void)delegateDidCleanupPageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;

#pragma mark Text selection

- (BOOL)delegateShouldSelectText:(NSString *)text withGlyphs:(NSArray<PSPDFGlyph *> *)glyphs atRect:(CGRect)rect onPageView:(PSPDFPageView *)pageView;

- (void)delegateDidSelectText:(NSString *)text withGlyphs:(NSArray<PSPDFGlyph *> *)glyphs atRect:(CGRect)rect onPageView:(PSPDFPageView *)pageView;

- (nullable NSArray<PSPDFMenuItem *> *)delegateShouldShowMenuItems:(NSArray<PSPDFMenuItem *> *)menuItems atSuggestedTargetRect:(CGRect)rect forSelectedText:(NSString *)selectedText inRect:(CGRect)textRect onPageView:(PSPDFPageView *)pageView;

- (nullable NSArray<PSPDFMenuItem *> *)delegateShouldShowMenuItems:(NSArray<PSPDFMenuItem *> *)menuItems atSuggestedTargetRect:(CGRect)rect forSelectedImage:(PSPDFImageInfo *)selectedImage inRect:(CGRect)textRect onPageView:(PSPDFPageView *)pageView;

#pragma mark Annotations

- (BOOL)delegateDidTapOnAnnotation:(PSPDFAnnotation *)annotation annotationPoint:(CGPoint)annotationPoint annotationView:(nullable UIView<PSPDFAnnotationPresenting> *)annotationView pageView:(PSPDFPageView *)pageView viewPoint:(CGPoint)viewPoint;

- (NSArray<PSPDFAnnotation *> *)delegateShouldSelectAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView;
- (void)delegateDidSelectAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView;
- (void)delegateDidDeselectAnnotations:(NSArray<PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView;

- (nullable NSArray<PSPDFMenuItem *> *)delegateShouldShowMenuItems:(NSArray<PSPDFMenuItem *> *)menuItems atSuggestedTargetRect:(CGRect)rect forAnnotations:(nullable NSArray<__kindof PSPDFAnnotation *> *)annotations inRect:(CGRect)textRect onPageView:(PSPDFPageView *)pageView;

#pragma mark Customizing Annotation Display
/// Override point to customize the decision making process whether the given annotation should be
/// displayed.
///
/// If the receiver’s `delegate` implements `pdfViewController:shouldDisplayAnnotation:onPageView:`,
/// the parameters are forwarded to it, and the result of that call is returned. Otherwise, this method
/// returns `true`.
- (BOOL)pageView:(PSPDFPageView *)pageView shouldDisplayAnnotation:(PSPDFAnnotation *)annotation;

/// Override point to customize or replace the view used to display the given annotation.
///
/// If the receiver’s `delegate` implements `pdfViewController:annotationView:forAnnotation:onPageView:`,
/// the parameters are forwarded to it, and the result of that call is returned. If the delegate does
/// not implement this method, the `annotationView` is returned as is.
///
/// @param pageView The page view that will add the return value to its view hierarchy.
/// @param annotationView The view to be customized/replaced.
/// @param annotation The annotation that is displayed by the view.
- (nullable UIView<PSPDFAnnotationPresenting> *)pageView:(PSPDFPageView *)pageView customizeAnnotationView:(nullable UIView<PSPDFAnnotationPresenting> *)annotationView forAnnotation:(PSPDFAnnotation *)annotation;

#pragma mark Annotation View Life-cycle
/// Override point to customize the behavior when an annotation view is about to be displayed.
///
/// If the receiver’s `delegate` implements `pdfViewController:willShowAnnotationView:onPageView:`, the
/// default implementation invokes that, forwarding the parameters as is. Otherwise, this method does
/// nothing.
///
/// @param pageView The page view about to add the given view to its hierarchy.
/// @param annotationView The view to be added.
- (void)pageView:(PSPDFPageView *)pageView willShowAnnotationView:(UIView<PSPDFAnnotationPresenting> *)annotationView;

/// Override point to customize the behavior when an annotation view has been added and made visible.
///
/// If the receiver’s `delegate` implements `pdfViewController:didShowAnnotationView:onPageView:`, the
/// default implementation invokes that, forwarding the parameters as is. Otherwise, this method does
/// nothing.
///
/// @param pageView The page view that has added the given view to its hierarchy and made it visible.
/// @param annotationView The view that has been added and made visible.
- (void)pageView:(PSPDFPageView *)pageView didShowAnnotationView:(UIView<PSPDFAnnotationPresenting> *)annotationView;

/// Override point to customize the behavior when an annotation view is about to be recycled.
///
/// The default implementation does nothing.
- (void)willRecycleAnnotationView:(UIView<PSPDFAnnotationPresenting> *)annotationView;

#pragma mark Customizing Child View Controller Presentation
- (BOOL)delegateShouldShowController:(UIViewController *)viewController options:(nullable NSDictionary<NSString *, id> *)options animated:(BOOL)animated;
- (void)delegateDidShowController:(UIViewController *)viewController options:(nullable NSDictionary<NSString *, id> *)options animated:(BOOL)animated;

#pragma mark ???
- (void)delegateDidChangeControllerState;

@end

@interface PSPDFAlertController (PSPDFDelegateCallingSupport)

// delegateTarget checks for delegateShouldShowController and delegateDidShowController - both optional.
- (BOOL)presentOnController:(UIViewController *)controller delegate:(nullable id)delegateTarget options:(nullable NSDictionary<NSString *, id> *)options sender:(nullable id)sender animated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
