
//
//  Copyright © 2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFScrubberBarContentView.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFScrubberBin, PSPDFScrubberThumbView;

@interface PSPDFScrubberBarContentView ()

/// Used internally to compute the page range of thumbnails at a point in the scubber bar.
/// Exposed privately for use in ScrubberBarUITests.
@property (nonatomic, nullable, copy, readonly) NSArray<PSPDFScrubberBin *> *scrubberBins;


/// Holds a reference to the thumbnail (`PSPDFScrubberThumbView`) of the currently opened page.
/// Exposed privately for use in ScrubberBarUITests.
@property (nonatomic, nullable, readonly) PSPDFScrubberThumbView *markerView;

/// MARK: Exposed for Tests

// This takes away stress from the render engine as previously we requested the image for all bin
// images from the render caches every time the user switched the page.
// See https://github.com/PSPDFKit/PSPDFKit/pull/8506 for more info.
@property (nonatomic, readonly) NSMutableDictionary<PSPDFRenderRequest *, UIImage *> *thumbnailImageCache;
@property (nonatomic, readonly) NSMutableDictionary<PSPDFRenderRequest *, UIImage *> *markerImageCache;

@end

NS_ASSUME_NONNULL_END
