//
//  Copyright © 2017-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFInkAnnotation, PSPDFSigner, PSPDFSignatureBiometricProperties;

/// Container object for storing a signature containing an ink annotation and an optional signer.
PSPDF_CLASS_SWIFT(SignatureContainer)
@interface PSPDFSignatureContainer : NSObject<NSSecureCoding, PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Designated initializer.
- (instancetype)initWithAnnotation:(PSPDFInkAnnotation *)annotation signer:(nullable PSPDFSigner *)signer biometricProperties:(nullable PSPDFSignatureBiometricProperties *)biometricProperties NS_DESIGNATED_INITIALIZER;

/// Ink annotation that is used for signing a document.
@property (nonatomic, readonly) PSPDFInkAnnotation *annotation;

/// Signer, used for digitally signing a document.
@property (nonatomic, nullable, readonly) PSPDFSigner *signer;

/// Biometric properties of the signature. This is only honored when a `signer` is set, and stored encrypted in a created digital signature.
@property (nonatomic, nullable, readonly) PSPDFSignatureBiometricProperties *biometricProperties;

@end

NS_ASSUME_NONNULL_END
