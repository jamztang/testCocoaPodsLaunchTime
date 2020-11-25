//
//  Copyright © 2017-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_SDK_CLASS_SWIFT(Progress)
@interface PSPDFProgress : NSProgress

/// Cancel parent when child progress is cancelled. Defaults to NO.
@property (nonatomic) BOOL trackChildCancellation;

/// Registers a callback to be invoked when progress completes.
///
/// The registration is thread safe. Upon returning you can be sure that either
/// progress already completed and the `completionBlock` will not be invoked,
/// or that progress is ongoing and `completionBlock` will be invoked in the future.
///
/// @param completionBlock A block that will be invoked after progress completes.
/// The completion blocks will be invoked in the order of registration.
/// The completion block is also invoked if the progress is canceled. Check `NSProgress.cancelled`,
/// if you need to determine if the completion block is being invoked due to cancelation.
/// The callback can be invoked on any queue.
/// @return an opaque token that can be used for de-registration, or `nil`, if progress already completed.
- (nullable id<NSObject>)addCompletionHandler:(dispatch_block_t)completionBlock;

/// Removes the observer associated with `token`.
///
/// @param token The token returned from `addCompletionHandler:` during callback registration.
- (BOOL)removeCompletionHandlerForToken:(id<NSObject>)token;

@end

NS_ASSUME_NONNULL_END
