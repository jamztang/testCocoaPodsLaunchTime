//
//  Copyright © 2017-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDocumentView.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFPageChangeReason) {
    PSPDFPageChangeReasonProgrammatic,
    PSPDFPageChangeReasonUser,
} NS_SWIFT_NAME(PageChangeReason);

@class PSPDFViewState, PSPDFDocumentViewScrollView, PSPDFPageView;

@interface PSPDFDocumentView ()

/// Called to invalidate the layout configuration.
///
/// This is resposible for invalidating everything that is not related to the collection
/// view layout.
- (void)invalidateConfiguration;

/// The view responsible for scrolling and zooming (when not in spread based zooming mode).
- (UIScrollView *)scrollView;

/// Applies the view state to the document view, optionally with animation.
///
/// @param viewState The view state to be applied.
/// @param animated `true` if the state application should be animated, else `false`.
- (void)applyViewState:(PSPDFViewState *)viewState animated:(BOOL)animated;

#pragma mark Testing

/// Useful for UI tests, to ensure content comes to rest sooner after scrolling.
@property (nonatomic) BOOL throttleDeceleration;

#pragma mark Scrolling and Zooming

/// Sets scroll indicator insets to both the scroll view responsible for scrolling
/// as well to the scroll views responsible for zooming.
@property (nonatomic) UIEdgeInsets scrollIndicatorInsets;

/// Set content insets to the scroll views responsible for zooming.
@property (nonatomic) UIEdgeInsets contentInset;

/// Content insets that are added to the `contentInset` property but do not alter
/// the cell or spread size of an item.
///
/// @note Setting this in a paginated environment will most likely not result in a
/// proper layout. This should only be set in a non paginated hierarchy.
@property (nonatomic) UIEdgeInsets additionalContentInset;

/// Set the continuous spread index and pass on animations that are preserved for the time of the animation.
- (void)setContinuousSpreadIndex:(CGFloat)continuousSpreadIndex reason:(PSPDFPageChangeReason)reason animated:(BOOL)animated;

/// Holds last `reason` passed via setContinuousSpreadIndex:reason:animated:`.
- (PSPDFPageChangeReason)lastSpreadIndexChangeReason;

#pragma mark Page Views

/// Array of all currently visible page views in the document view.
@property (nonatomic, readonly) NSArray<PSPDFPageView *> *visiblePageViews;

/// Ask for a visible page view at the given location.
///
/// @param point Point in document view's coordiante space.
///
/// @return Visible page view at the given location, if any.
- (nullable PSPDFPageView *)visiblePageViewAtPoint:(CGPoint)point;

@end

NS_ASSUME_NONNULL_END

