//
//  Copyright © 2012-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFModelObject.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSelectionState;

/// Represents a certain view state (document position, zoom) of a `Document`.
///
/// @note Prior to PSPDFKit 8 for iOS, if an instance of this class had a `viewPort`, that view port was defined in raw PDF coordinates (not
/// considering page rotation or CropBox). The view port is now defined in normalized PDF coordinates. Instances created from old archives may
/// contain unexpected view ports, but PSPDFKit will automatically apply the page transform when such an instance is applied to a view.
PSPDF_CLASS_SWIFT(PDFViewState)
@interface PSPDFViewState : PSPDFModel<NSSecureCoding>

/// The designated initializer.
- (instancetype)initWithPageIndex:(PSPDFPageIndex)pageIndex viewPort:(CGRect)viewPort selectionState:(nullable PSPDFSelectionState *)selectionState selectedAnnotationNames:(nullable NSArray<NSString *> *)selectedAnnotationNames NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithPageIndex:(PSPDFPageIndex)pageIndex viewPort:(CGRect)viewPort selectionState:(nullable PSPDFSelectionState *)selectionState;

/// Initializes a PSPDFViewState with the specified page index and selection state only. The view port will be set to CGRectNull.
- (instancetype)initWithPageIndex:(PSPDFPageIndex)pageIndex selectionState:(nullable PSPDFSelectionState *)selectionState;

/// Initializes a PSPDFViewState with the specified page index and view port only. The selection state will be set to nil.
- (instancetype)initWithPageIndex:(PSPDFPageIndex)pageIndex viewPort:(CGRect)viewPort;

/// Initializes a PSPDFViewState with a page index only. The view port and selection state will be set to CGRectNull and nil respectively.
- (instancetype)initWithPageIndex:(PSPDFPageIndex)pageIndex;

/// Visible Page.
@property (readonly, nonatomic) PSPDFPageIndex pageIndex;

/// The effectively visible rectangle of the page in page coordinates — `CGRectNull` if the view was fully visible and not displayed in continuous scrolling mode.
///
/// @note Due to the nature of continuous scrolling, even a fully zoomed out page can have a view–port.
/// This is necessary to preserve a scrolling offset in documents where more than one page fits on the screen at once.
@property (readonly, nonatomic) CGRect viewPort;

/// Whether or not the receiver has a restorable view port.
@property (readonly, nonatomic) BOOL hasViewPort;

/// The view's selection state.
@property (readonly, nonatomic, nullable) PSPDFSelectionState *selectionState;

/// Compares the receiver to another viewstate, allowing for the specified leeway if both have a viewport.
///
/// @param other The object to compare to — may be `nil`.
/// @param leeway How much each dimension of the viewport may differ.
- (BOOL)isEqualToViewState:(nullable PSPDFViewState *)other withAccuracy:(CGFloat)leeway;

@end

NS_ASSUME_NONNULL_END
