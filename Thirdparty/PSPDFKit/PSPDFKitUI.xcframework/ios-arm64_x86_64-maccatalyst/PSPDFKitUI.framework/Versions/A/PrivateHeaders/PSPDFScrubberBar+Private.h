//
//  Copyright © 2015-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFScrubberBar.h>

#import <PSPDFKitUI/PSPDFScrubberBarContentView.h>
#import <PSPDFKitUI/PSPDFAdornmentContainerView.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_EXPORT const CGFloat PSPDFFloatingScrubberBarPadding;

@protocol PSPDFScrubberBarLayout;

/// Acts as a container for the actual scrubber bar (`PSPDFScrubberBarContentView`)
/// and serves as data source for the calculations necessary to layout the thumbnails correctly
/// when using scrubber bar thumbnail bar styles.
@interface PSPDFScrubberBar ()

/// The adjusted height to account for when the scrubber bar is floating.
@property (nonatomic, readonly) CGFloat containerHeight;

///// The underlying scrubber bar.
@property (nonatomic) PSPDFScrubberBarContentView *contentView;

///// If the scrubber bar itself should be floating.
@property (nonatomic, readonly, getter=isFloating) BOOL floating;

/// The view that houses the scrubber bar adornments.
@property (nonatomic, readonly) PSPDFAdornmentContainerView *adornmentContainer;

/// Convenience accessor
@property (nonatomic, readonly) PSPDFScrubberBar *scrubberContainer;

@property (nonatomic, weak) id<PSPDFScrubberBarLayout> layoutDelegate;

@end


NS_ASSUME_NONNULL_END
