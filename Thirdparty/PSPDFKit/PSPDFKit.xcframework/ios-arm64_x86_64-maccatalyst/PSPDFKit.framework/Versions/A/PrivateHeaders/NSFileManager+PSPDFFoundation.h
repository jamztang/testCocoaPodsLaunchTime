//
//  Copyright © 2018-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSFileManager (PSPDFFoundation)

/// Checks if the filesystem at the give file or directory path is APFS.
///
/// @param path A path specifying a local file or directory.
/// @return YES if the file system is set up to use APFS at the provided path
/// and NO otherwise.
+ (BOOL)pspdf_isAPFSFileSystemAtPath:(NSString *)path;


/// Checks if a lightweight copy of a file can be created at a given destination path.
///
/// This is done by checking if both source and destination are using APFS and are on the same mounted volume.
///
/// @param source The source path of the file that should be copied.
/// @param destination The destination directory the copy.
+ (BOOL)pspdf_supportsLightweightCopyFrom:(NSString *)source to:(NSString *)destination;

@end

NS_ASSUME_NONNULL_END
