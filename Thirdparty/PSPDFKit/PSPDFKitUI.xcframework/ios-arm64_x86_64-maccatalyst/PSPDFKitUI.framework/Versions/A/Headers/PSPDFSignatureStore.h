//
//  Copyright © 2012-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFSignatureContainer.h>

NS_ASSUME_NONNULL_BEGIN

/// Securely stores ink signatures in the keychain.
/// Supports `NSSecureCoding` since this is part of the `PDFConfiguration` object.
PSPDF_PROTOCOL_SWIFT(SignatureStore)
@protocol PSPDFSignatureStore<NSObject, NSSecureCoding>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Designated initializer.
/// `storeName` can be used to differentiate between different stores.
- (instancetype)initWithStoreName:(NSString *)storeName;

/// Add signature to store.
- (void)addSignature:(PSPDFSignatureContainer *)signature;

/// Remove signature from store.
- (BOOL)removeSignature:(PSPDFSignatureContainer *)signature;

/// Access the saved signatures (`PSPDFSignatureContainer` objects).
@property (nonatomic, copy, null_resettable) NSArray<PSPDFSignatureContainer *> *signatures;

/// The store name used for the keychain storage.
@property (nonatomic, copy, readonly) NSString *storeName;

@end

/// The default store name used in the `PSPDFKeychainSignatureStore`.
PSPDF_EXPORT NSString *PSPDFKeychainSignatureStoreDefaultStoreName NS_SWIFT_NAME(KeychainSignatureStore.DefaultStoreName);

/// Default signature store implementation that uses the keychain.
/// `storeName` is used as the service name in the keychain.
PSPDF_CLASS_SWIFT(KeychainSignatureStore)
@interface PSPDFKeychainSignatureStore : NSObject<PSPDFSignatureStore>
@end

NS_ASSUME_NONNULL_END
