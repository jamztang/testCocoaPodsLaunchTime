//
//  Copyright © 2012-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFOverrideProvider.h>
#else
#import "PSPDFEnvironment+Private.h"
#import "PSPDFOverridable.h"
#import "PSPDFOverrideProvider.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// @name Resolution

/// Query the `PSPDFOverrideProvider` for an override and also check that instances
/// of `originalClass` conform to `PSPDFOverridable` protocol.
PSPDF_SDK_EXPORT Class PSPDFOverrideClassWithProvider(Class<PSPDFOverridable> originalClass, id<PSPDFOverrideProvider> provider, id<PSPDFOverridable> _Nullable typecheck);

/// Resolve a class using `self` as a provider, without statically checking that
/// the class conforms to `PSPDFOverridable` protocol.
#define PSPDFClassForUncheckedClass(originalClass) PSPDFOverrideClassWithProvider(originalClass, self, nil)

/// Resolve a class using `self` as a provider, and statically check that the
/// class conforms to `PSPDFOverridable` protocol, raising compile error otherwise.
#define PSPDFClass(className) PSPDFOverrideClassWithProvider(className.class, self, ((className *)nil))

/// Allocate a class, with `self` as a provider.
#define PSPDFClassAlloc(className) ((className *)([PSPDFClass(className) alloc]))

/// Allocate and initialize a class using `-init`, with `self` as a provider.
#define PSPDFClassCreate(className) [PSPDFClassAlloc(className) init]

/// Resolve a class using `self` as a provider, unless `self` is `nil`, in which
/// case the original class will be used as a fallback.
#define PSPDFClassInNullableContext(className) (self == nil ? className.class : PSPDFOverrideClassWithProvider(className.class, PSPDFNN(self), ((className *)nil)))

/// Allocate a class, with `self` as a provider, unless `self` is `nil`, in which
/// case the original class will be used as a fallback.
#define PSPDFClassAllocInNullableContext(className) ((className *)([PSPDFClassInNullableContext(className) alloc]))

/// Allocate and initialize a class using `-init`, with `self` as a provider, unless
/// `self` is `nil`, in which case the original class will be used as a fallback.
#define PSPDFClassCreateInNullableContext(className) [PSPDFClassAllocInNullableContext(className) init]

/// @name Forwarding

/// Installs a forwarder that queries the given `provider` for an override while
/// retaining `PSPDFOverrideProvider` conformance in the current class.
#define PSPDF_FORWARD_OVERRIDES_TO(provider) \
    - (nonnull Class)classForClass:(nonnull Class<PSPDFOverridable>)originalClass { \
        _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Warc-repeated-use-of-weak\"") \
        return (provider ? PSPDFOverrideClassWithProvider(originalClass, PSPDFNN(provider), nil) : originalClass); \
        _Pragma("clang diagnostic pop") \
    }

/// Does the same as `PSPDF_FORWARD_OVERRIDES_TO`, except it doesn't raise a
/// compile warning if `provider` doesn't statically conform to `PSPDFOverrideProvider`.
/// Instead, it does that check at runtime using `-conformsToProtocol:`.
#define PSPDF_FORWARD_OVERRIDES_TO_UNCHECKED(provider) \
    - (nonnull Class)classForClass:(nonnull Class<PSPDFOverridable>)originalClass { \
        _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Warc-repeated-use-of-weak\"") \
        if ([provider conformsToProtocol:@protocol(PSPDFOverrideProvider)]) { \
            return PSPDFOverrideClassWithProvider(originalClass, PSPDFNN((id<PSPDFOverrideProvider>)provider), nil); \
        } else { \
            return originalClass; \
        } \
        _Pragma("clang diagnostic pop") \
    }

/// @name Implementation

/// Return custom class if class map is provided.
PSPDF_SDK_EXPORT Class PSPDFOverrideClassForClass(Class originalClass, NSDictionary<Class, Class> * _Nullable overrideClassNames);

/// Update existing class map (or create a new one if nil)
PSPDF_SDK_EXPORT NSDictionary<Class, Class> *PSPDFOverrideClassCreate(Class originalClass, Class _Nullable subclass, NSDictionary<Class, Class> * _Nullable overrideClassNames);

NS_ASSUME_NONNULL_END
