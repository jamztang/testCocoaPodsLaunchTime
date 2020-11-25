//
//  Copyright © 2017-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFFileDataProvider.h>
#import <PSPDFKit/PSPDFSecurityScopedURL.h>
#else
#import "PSPDFFileDataProvider.h"
#import "PSPDFSecurityScopedURL.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFFileDataProvider ()

/// This is used by Instant to initialize without a file URL because it will be provided later when the document is loaded.
///
/// The correctly handle not having a file URL, the Instant subclass overrides the fileURL getter.
/// The Instant subclass also overrides a few methods that could read from fileURL before the document is loaded (when the progress is incomplete).
/// Methods that read from fileURL after the document is loaded assert that it is not nil at that point. Situations causing this to occur should be fixed.
///
/// Therefore the implementation of this class should be sure to not read the _fileURL instance variable anywhere except in the property getter.
///
/// @param progress A progress that completes when the document is loaded.
/// @return A new instance without a fileURL.
- (instancetype)initWithProgress:(NSProgress *)progress NS_DESIGNATED_INITIALIZER;

/// Updates the file URL and invalidates the file handle when set.
@property (nonatomic, readwrite) NSURL *fileURL;

#pragma mark File URL change tolerant data provider methods

/// An alternative to the `PSPDFDataProviding` method `size`, that allows us to specify the `destinationURL`.
- (uint64_t)sizeForFileAtURL:(NSURL *)fileURL;

/// An alternative to the `PSPDFDataProviding` method `readWithSize:atOffset:`, that allows us to specify the `destinationURL`.
- (nullable NSData *)readDataFromFileAtURL:(NSURL *)fileURL withSize:(uint64_t)size atOffset:(uint64_t)offset;

/// An alternative to the `PSPDFDataProviding` method `data`, that allows us to specify the `destinationURL`.
- (nullable NSData *)dataFromFileAtURL:(NSURL *)fileURL;

/// An alternative to the `PSPDFDataProviding` method `replaceWithDataSink:`, that allows us to specify the `fileURL`.
- (BOOL)replaceFileAtURL:(NSURL *)fileURL withDataSink:(id<PSPDFDataSink>)replacementDataSink error:(NSError *__autoreleasing *)error;

/// An alternative to the `PSPDFDataProviding` method `deleteDataWithError:`, that allows us to specify the `fileURL`.
- (BOOL)deleteFileAtURL:(NSURL *)fileURL withError:(NSError *__autoreleasing *)error;

@end

NS_ASSUME_NONNULL_END
