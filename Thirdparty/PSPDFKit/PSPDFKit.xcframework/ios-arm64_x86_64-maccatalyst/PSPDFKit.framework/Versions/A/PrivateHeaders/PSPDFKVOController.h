//
//  Copyright © 2015-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

@protocol PSPDFObservance <NSObject>

/// Safely de–registers the KV–observation represented by the receiver.
- (void)cancel;

@end

NS_ASSUME_NONNULL_BEGIN

PSPDF_SDK_CLASS_SWIFT(KVOController)
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFKVOController <ObserverType> : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Returns a KVO controller with the specified observer that holds strong references to all observed objects.
+ (instancetype)controllerWithObserver:(ObserverType)observer;

/// The object whose observations are managed by the receiver.
/// Passed as `observer` into the block that’s called when a KVO event fires.
@property (atomic, weak, readonly) ObserverType observer;

/// Adds `observer` as an observer of `object`’s `keyPath`.
///
/// @warning Watch out for retain cycles with the block.
/// @return A observance token that can be sent `cancel` to unregister the observation. Do not pass this token to `unobserve:`.
- (id<PSPDFObservance>)observe:(id)object keyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options block:(void (^)(ObserverType observer, id object, NSDictionary<NSString *, id> *change))block;

/// Returns an array of tokens to use for cancellation, one for each passed key path.
- (NSArray<id<PSPDFObservance>> *)observe:(id)object keyPaths:(NSArray<NSString *> *)keyPaths options:(NSKeyValueObservingOptions)options block:(void (^)(ObserverType observer, id object, NSDictionary<NSString *, id> *change))block;

/// Clears all observations of the specified keyPaths on object.
///
/// @param object The object that should no longer be observed.
/// @param keyPaths The key–paths of `object` which should no longer be observed. If `nil`, all observations of `object` are cleared.
- (void)unobserve:(id)object keyPaths:(nullable NSArray<NSString *> *)keyPaths;

/// Clears obvervation for the specified key-path, convenience method for `unobserve:keyPaths:`.
- (void)unobserve:(id)object keyPath:(NSString *)keyPath;

/// Remove all observations the owning object has on `object`.
///
/// @param object The object to remove observations of, not a token returned from an `observe:...` method.
- (void)unobserve:(id)object;

/// Clears all observeations of all objects that are observed by the receiver.
- (void)unobserveAll;

@end

#pragma mark - Conveniences:

@interface NSObject (PSPDFKVO)

/**
 Lazily loads a KVO controller with the receiver as the observer, that keeps strong references to the objects it observes.
 The KVO controller is stored strongly on the receiver using associated objects.

 @warning Do not use this API if — for whatever valid reason — you need to observe the receiver itself, as that would create a strong reference cycle.
 Example:
 ```
 [foo.pspdf_KVOController observe:foo keyPath:@"bar" options:0 block:^(Foo *observer, Foo *object, NSDictionary<NSString *, id> *change) {…}];
 ```
 Objects observing themselves are an anti–pattern to begin with, but there _may be_ situations where that’s the only halfway sane solution.
 In those cases, **do not use this property**!
 Should you find yourself in a situation where you absolutely have to have `foo` observe `foo`, use the `pspdf_KVOControllerUnretainedObserving` property, and explain in a comment why that’s a sane solution.
 */
@property (nonatomic, readonly) PSPDFKVOController *pspdf_KVOController NS_SWIFT_NAME(KVOController);

/**
 Lazily loads a KVO controller with the receiver as the observer, that keeps unretained references to the objects it observes.
 The KVO controller is stored strongly on the receiver using associated objects.

 @note In general, you will want to use `pspdf_KVOController` instead.
 In fact, the only occasion where this is the appropriate API to use is to have an object observe itself!
 Example:
 ```
 [foo.pspdf_KVOControllerUnretainedObserving observe:foo keyPath:@"bar" options:0 block:^(Foo *observer, Foo *object, NSDictionary<NSString *, id> *change) {…}];
 ```
 That said, having an object observe itself is a very strong code smell and **should be avoided**!
 For the very rare occasion where this is the sanest solution, leave a comment explaining _why_ you chose this approach.

 @warning Because the KVOController does not keep strong references to the observed object, you should only use this API when you know for certain that the observed objects live as long as the receiver, or maybe even longer.
 If that is not the case, the references to the observed objects might dangle, and that invites all kinds of undefined behavior.
 */
@property (nonatomic, readonly) PSPDFKVOController *pspdf_KVOControllerUnretainedObserving NS_SWIFT_NAME(KVOControllerUnretainedObserving);

@end

NS_ASSUME_NONNULL_END
