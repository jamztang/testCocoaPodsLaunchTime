//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFDocument, PSPDFKitGlobal, PSPDFRenderRequest, PSPDFMemoryCache, PSPDFDiskCache;

NS_ASSUME_NONNULL_BEGIN

typedef void (^PSPDFCacheDocumentImageRenderingCompletionBlock)(UIImage *image, PSPDFDocument *document, PSPDFPageIndex page, CGSize size);

typedef NS_CLOSED_ENUM(NSInteger, PSPDFCacheStoragePolicy) {
    PSPDFCacheStoragePolicyAutomatic = 0,

    PSPDFCacheStoragePolicyAllowed,
    PSPDFCacheStoragePolicyAllowedInMemoryOnly,
    PSPDFCacheStoragePolicyNotAllowed,
} PSPDF_ENUM_SWIFT(PDFCache.StoragePolicy);

typedef NS_CLOSED_ENUM(NSInteger, PSPDFCacheStatus) {
    PSPDFCacheStatusNotCached,
    PSPDFCacheStatusInMemory,
    PSPDFCacheStatusOnDisk,
} PSPDF_ENUM_SWIFT(PDFCache.Status);

/// `PSPDFCacheImageSizeMatching` is a bit mask that can be used to control how
/// the cache determines if an image's size matches a given request.
typedef NS_OPTIONS(NSUInteger, PSPDFCacheImageSizeMatching) {
    /// Requires the exact size, the default option.
    PSPDFCacheImageSizeMatchingExact = 0,
    /// Allow serving images of larger size.
    PSPDFCacheImageSizeMatchingAllowLarger = 1 << 0,
    /// Allow serving images of smaller size.
    PSPDFCacheImageSizeMatchingAllowSmaller = 1 << 1,

    PSPDFCacheImageSizeMatchingDefault = PSPDFCacheImageSizeMatchingExact
} PSPDF_ENUM_SWIFT(PDFCache.ImageSizeMatching);

/// The `PSPDFCache` is responsible for managing the memory and disk cache of rendered
/// images.
///
/// Usually you do not access any methods of `PSPDFCache` directly but instead schedule
/// a `PSPDFRenderTask` in a `PSPDFRenderQueue` which will then reach out to the cache
/// and check if there are images available before rendering a new one.
///
/// @see PSPDFRenderTask
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PDFCache)
@interface PSPDFCache : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// The designated initializer.
- (instancetype)initWithSettings:(PSPDFKitGlobal *)pspdfkit NS_DESIGNATED_INITIALIZER;

#pragma mark Access cache

/// The memory cached store used to keep images in memory for fast access.
@property (nonatomic, readonly) PSPDFMemoryCache *memoryCache;

/// The disk cache used to persist images on disk for fast access.
@property (nonatomic, readonly) PSPDFDiskCache *diskCache;

/// Get the cache status of a rendered image.
- (PSPDFCacheStatus)cacheStatusForRequest:(PSPDFRenderRequest *)request imageSizeMatching:(PSPDFCacheImageSizeMatching)imageSizeMatching;

/// Get the image for a certain document page.
/// Will first check the memory cache, then the disk cache.
///
/// If `requireExactSize` is set, images will either be downscaled or dynamically rendered. (There's no point in upscaling)
- (nullable UIImage *)imageForRequest:(PSPDFRenderRequest *)request imageSizeMatching:(PSPDFCacheImageSizeMatching)imageSizeMatching error:(NSError *__autoreleasing*)error;

#pragma mark Store into cache

/// Caches the image in memory and disk for later re-use.
/// PSPDFCache will decide at runtime if the image is worth saving into memory or just disk. (And disk will only be hit if the image is different)
- (void)saveImage:(UIImage *)image forRequest:(PSPDFRenderRequest *)request;

#pragma mark Document pre-processing

/// Asynchronously pre-renders and caches the document. The delegate method `didRenderImage:document:page:size:` gets called after each image is rendered (number of pages x number of sizes).
///
/// @note Under certain conditions (such as if the device is running low on power)
/// the cache may suspend pre caching operations until everything has been restored
/// to normal conditions.
///
/// @param document The document to render and cache — if `nil`, this message is ignored.
/// @param sizes    An array of NSValue objects constructed with CGSize. Each page will be rendered for each size specified in this array.
- (void)cacheDocument:(nullable PSPDFDocument *)document withPageSizes:(NSArray<NSValue *> *)sizes;

/// Asynchronously pre-renders and caches the document. The delegate method `didRenderImage:document:page:size:` gets called after each image is rendered (number of pages x number of sizes).
///
/// @note Under certain conditions (such as if the device is running low on power)
/// the cache may suspend pre caching operations until everything has been restored
/// to normal conditions.
///
/// @param document            The document to render and cache — if `nil`, this message is ignored.
/// @param sizes               An array of NSValue objects constructed with CGSize. Each page will be rendered for each size specified in this array.
/// @param pageCompletionBlock This block will be executed each time a page is rendered for each size (the delegates, if any, will still be called!).
- (void)cacheDocument:(nullable PSPDFDocument *)document withPageSizes:(NSArray<NSValue *> *)sizes imageRenderingCompletionBlock:(nullable PSPDFCacheDocumentImageRenderingCompletionBlock)pageCompletionBlock;

/// Stops all cache requests (render requests, queued disk writes) for the document.
- (void)stopCachingDocument:(nullable PSPDFDocument *)document;

#pragma mark Cache invalidation

/// Invalidates a single page in the document.
/// This usually is called after an annotation changes (and thus the image needs to be re-rendered)
///
/// @note If the document is nil, the request is silently ignored.
- (void)invalidateImagesFromDocument:(nullable PSPDFDocument *)document pageIndex:(PSPDFPageIndex)pageIndex;

/// Invalidates pages in the document.
/// This usually is called after an annotation changes (and thus the image needs to be re-rendered)
///
/// @note If the document is nil, the request is silently ignored.
- (void)invalidateImagesFromDocument:(nullable PSPDFDocument *const)document indexes:(NSIndexSet *)indexes;

/// Removes the whole cache (memory/disk) for `document`. Will cancel any open writes as well.
/// Enable `deleteDocument` to remove the document and the associated metadata.
- (void)removeCacheForDocument:(nullable PSPDFDocument *)document;

/// Clears the disk and memory cache.
- (void)clearCache;

@end

@interface PSPDFCache (Deprecated)

- (nullable UIImage *)imageForRequest:(PSPDFRenderRequest *)request imageSizeMatching:(PSPDFCacheImageSizeMatching)imageSizeMatching PSPDF_DEPRECATED(9.1, 4.1, "Use `initWithRequest:error:` instead.") NS_SWIFT_UNAVAILABLE("Use version with error handling");

- (void)invalidateImageFromDocument:(nullable PSPDFDocument *)document pageIndex:(PSPDFPageIndex)pageIndex PSPDF_DEPRECATED(10.1, 5.1, "Use `invalidateImagesFromDocument:pageIndex:` instead.");

@end

NS_ASSUME_NONNULL_END
