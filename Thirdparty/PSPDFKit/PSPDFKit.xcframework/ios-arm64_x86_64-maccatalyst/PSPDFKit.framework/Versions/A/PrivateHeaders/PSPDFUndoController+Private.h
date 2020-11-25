//
//  Copyright © 2011-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFUndoController.h>

#define PSPDFUndoDebugging 0

#if PSPDFUndoDebugging
#define PSPDFUndoDebugLog(__msg__, ...) NSLog(@"[Undo] %@: " __msg__, NSStringFromSelector(_cmd), ##__VA_ARGS__)
#define PSPDFUndoLog(__msg__, ...) do { NSLog(@"[Undo] "  __msg__, ##__VA_ARGS__); }while(0)
#else
#define PSPDFUndoDebugLog(__msg__, ...)
#define PSPDFUndoLog(__msg__, ...)
#endif

NS_ASSUME_NONNULL_BEGIN

/// A note about locking:
///
/// Locking on the internal queue of the undo controller has been the cause of many deadlocks.
/// The undo controller lock should be above all other more fine granular locks including the document provider lock. Take utmost care, whenever you open a `PSPDFPerformBlockAsGroup` as it should be very fine granular in most cases.
///
/// Notable exception is `PSPDFContainerAnnotationProvider` which has an internal queue that locks annotations, which is below the undo controller.
@interface PSPDFUndoController ()

/// Begin/end an undo group.
///
/// @note `PSPDFPerformBlockAsGroup` is preferred since it is less error prone
/// If `groupName` is nil, a default name for the changes will be inferred.
- (void)beginUndoGrouping;
- (void)endUndoGroupingWithName:(nullable NSString *)groupName;

/// Mass register objects that conform to PSPDFUndoSupport.
- (void)registerObjectsForUndo:(NSArray<id<PSPDFUndoSupport>> *)collection;

/// Testing only: Flushes the test for keys that should not change.
+ (void)flushCache;

/// Will be set to the undo actions object if the undo controller is currently undoing or redoing.
@property (nonatomic, nullable, readonly) id currentUndoTarget;

@end

NS_ASSUME_NONNULL_END
