//
//  Copyright © 2017-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDocumentViewLayout.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSInteger, PSPDFStackViewLayoutDirection) {
    PSPDFStackViewLayoutDirectionHorizontal,
    PSPDFStackViewLayoutDirectionVertical,
} PSPDF_ENUM_SWIFT(StackViewLayout.Direction);

/// The stack view layout produces a similar look than a `UIStackView`. It lays out
/// its content either in a vertical or horizontal line.
///
/// By default all items in a stack view layout have the same size and this size is
/// deduced from the viewport of the layout.
///
/// @note A stack view layout can only be used in a document view. It will not work
/// properly when assigned to an arbitrary collection view.
///
/// # Subclassing
///
/// If you want to create your own document view layout, subclassing `PSPDFStackViewLayout`
/// is a good starting point. As long as you stick with the general idea that content
/// only expands in one direction, all you need to override to customize the layout
/// is the `layoutAttributesForItemAtIndexPath:` method. It is used by the other methods
/// that deal with layout attributes.
///
/// If you just want to change the size of items, overriding `sizeForSpreadAtIndex:`
/// should be enough.
///
/// Make sure when overriding `layoutAttributesForItemAtIndexPath:` to get the size
/// for each attribute from `sizeForSpreadAtIndex:` as other parts of the layout
/// are using this as well.
PSPDF_CLASS_SWIFT(StackViewLayout)
@interface PSPDFStackViewLayout : PSPDFDocumentViewLayout

/// The insets to apply to the layout.
///
/// While `interitemSpacing` defines the spacing between the items, the content inset
/// defines the top, left, bottom and right inset around all the content. E.g. for
/// a horizontally scrolling layout, the left inset will be the x starting coordinate
/// for the first item, the right inset will define the additional space after the
/// last item and the top and bottom insets will define the spacing to the edge of
/// the content size for each item.
///
/// Subclasses can override this to change the content inset that is needed to layout
/// spreads properly. If you override this, make sure to apply the `additionalContentInsets`
/// or otherwise setting additional content insets will have no effect.
///
/// @see `-interitemSpacing`
/// @see `-additionalContentInsets`
@property (nonatomic, readonly) UIEdgeInsets contentInsets;

/// Additional insets to apply to the layout's content.
///
/// Users of the layout can set insets here to customize the appearance of the layout.
///
/// Defaults to `UIEdgeInsetsZero`.
///
/// @see `-contentInsets`
@property (nonatomic) UIEdgeInsets additionalContentInsets;

/// The spacing between two items alongside the scroll direction.
///
/// @see `-contentInsets`
@property (nonatomic) CGFloat interitemSpacing;

/// The layout direction in which the stack view layout should position its content.
@property (nonatomic) PSPDFStackViewLayoutDirection direction;

@end

@interface PSPDFStackViewLayout (Subclassing)

/// The spread size for the passed in `spreadIndex`.
///
/// This method can be subclassed to alter the size of a spread. If the size of a spread
/// changes at runtime, be sure to invalidate the spread index in question.
///
/// Defaults to the spread size scaled so that it fits the viewport's size, inset by
/// the `scrollViewFrameInsets` and `contentInsets`. This means the returned size will
/// always fit on screen and does not require any scrolling.
- (CGSize)sizeForSpreadAtIndex:(NSInteger)spreadIndex;

@end

NS_ASSUME_NONNULL_END
