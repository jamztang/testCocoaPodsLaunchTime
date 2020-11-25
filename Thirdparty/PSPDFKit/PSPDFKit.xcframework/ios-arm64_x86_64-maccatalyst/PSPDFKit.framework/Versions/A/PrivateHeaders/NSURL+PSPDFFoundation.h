//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@interface NSURL (PSPDFAdditions)

/// Resolves a content URL. If the URL is of the form pspdfkit://localhost/Bundle/...,
/// it will be resolved to the appropriate file URL. Otherwise a copy of the unmodified
/// URL will be returned.
- (NSURL *)pspdf_resolveContentURLWithUnknownPathBlock:(nullable NS_NOESCAPE NSString * (^)(NSString *unknownPath))block;

/// Invokes `bookmarkDataWithOptions:includingResourceValuesForKeys:relativeToURL:error:` with some
/// default options and logs if the conversion fails.
@property (nonatomic, readonly, nullable) NSData *pspdf_bookmarkData;

/// The inverse operation for pspdf_bookmarkData. Creates a new URL from the bookmark data.
+ (nullable NSURL *)pspdf_urlWithBookmarkData:(nullable NSData *)data;

/// Workaround for radar FB6120834 (Mac Catalyst)
///
/// Symlink resolving fails with Catalyst NSURL Document with iCloud sync.
- (NSURL *)pspdf_URLByResolvingSymlinks;

/// Returns the relative path that can be added to `baseURL` to reach `self`.
///
/// @param baseURL The base URL used to compute the relative path.
/// @return A string path that can be added to `baseURL` using
/// `NSURL` relative path initializers e.g., `fileURLWithPath:relativeToURL:`
/// to reach the URL represented in `self`.
- (NSString *)pspdf_relativePathToURL:(NSURL *)baseURL;

@end

NS_ASSUME_NONNULL_END
