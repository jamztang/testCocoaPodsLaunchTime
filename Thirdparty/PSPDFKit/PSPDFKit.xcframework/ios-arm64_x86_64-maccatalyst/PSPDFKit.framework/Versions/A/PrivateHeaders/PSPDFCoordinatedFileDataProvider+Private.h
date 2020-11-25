//
//  Copyright © 2017-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFCoordinatedFileDataProvider.h>
#else
#import "PSPDFCoordinatedFileDataProvider.h"
#endif

@class PSPDFFileChangeTracker;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFCoordinatedFileDataProvider ()

/// Specifies whether an internal file copy should be created for resolving external
/// modification or deletion conflicts of the the backing file.
///
/// Defaults to `true`. Setting this to `false` prevents the data provider from ever creating a copy.
/// This also prevents conflict resolution actions that require a file copy from functioning.
///
/// The copy is created lazily on file access and only if certain conditions are met (APFS filesystem).
/// Use `isConflictResolutionAvailable` to check if a copy is currently created.
///
/// @note For best results set immediately after initialization, before any data access is attempted.
/// This will prevent the read copy from ever being created.
@property (nonatomic, getter=isFileCopyForConflictResolutionEnabled) BOOL fileCopyForConflictResolutionEnabled;

/// The change tracker monitoring file changes in the backing file.
@property (nonatomic, readonly) PSPDFFileChangeTracker *changeTracker;

/// A helper that sets up a coordinated read on the file tracked by the data provider.
///
/// @param readBlock A block with the actual read operation performed on the passed in `readURL`.
/// @param options File coordination options that are passed through to the system.
/// @param error An error, set if a problem occurs during file coordination.
/// @return `true` if the read was successful and `false` otherwise.
- (BOOL)performCoordinatedReading:(BOOL (^)(NSURL *readURL))readBlock options:(NSFileCoordinatorReadingOptions)options error:(NSError *__autoreleasing *)error;

@end

NS_ASSUME_NONNULL_END
