//
//  Copyright © 2012-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFCryptoInputStream.h>

NS_ASSUME_NONNULL_BEGIN

/// AES encryption, RNCryptor data format  (see https://github.com/RNCryptor/RNCryptor-Spec/blob/master/RNCryptor-Spec-v3.md )
PSPDF_CLASS_SWIFT(AESCryptoInputStream)
@interface PSPDFAESCryptoInputStream : PSPDFCryptoInputStream

/// Designated initializer with the passphrase. The encryption key salt and HMAC key salt will be loaded from the file header.
- (instancetype)initWithInputStream:(NSInputStream *)stream passphrase:(NSString *)passphrase;

/// On the first call the provided data buffer size must be at least 98 bytes (82 bytes if original data were < 16 bytes) due to the RNCryptor data format,
/// otherwise an exception will be thrown.
- (NSInteger)read:(uint8_t *)buffer maxLength:(NSUInteger)len;

/// Use this method to close the stream and append the provided data to previously decrypted data.
///
/// @return leftovers of the decrypted data (due to the way CBC decryption works).
/// Returns nil is the error is occurred, otherwise return NSData instance (even if there is no decrypted data left).
- (nullable NSData *)closeWithData;

/// DO NOT CALL this method to close the stream. Instead, call the - (NSData *)closeWithData;
/// Throws the exception if called.
- (void)close;

@end

/// The PSPDFAESCryptoInputStream Error Domain.
///
/// @note Used in the PSPDFAESCryptoInputStream -(NSError *)streamError method.
PSPDF_EXPORT NSString *const PSPDFAESCryptoInputStreamErrorDomain;

/// List of documented errors within the PSPDFAESCryptoInputStream.
///
/// @note Used in the PSPDFAESCryptoInputStream -(NSError *)streamError method.
typedef NS_ERROR_ENUM(PSPDFAESCryptoInputStreamErrorDomain, PSPDFAESCryptoInputStreamErrorCode) {
    PSPDFAESCryptoInputStreamErrorUnknownVersionInFileHeader = 110,
    PSPDFAESCryptoInputStreamErrorWrongCloseCalled = 120,
    PSPDFAESCryptoInputStreamErrorCryptorCreationFailed = 130,
    PSPDFAESCryptoInputStreamErrorCryptorResetToIVFailed = 140,
    PSPDFAESCryptoInputStreamErrorCloseExpectedInsteadOfRead = 150,
    PSPDFAESCryptoInputStreamErrorDecryptingBlockFailed = 160,
    PSPDFAESCryptoInputStreamErrorCryptorFinalFailed = 170,
    PSPDFAESCryptoInputStreamErrorHMACCheckFailed = 180,
    PSPDFAESCryptoInputStreamErrorIncorrectHMACInFile = 190,
    PSPDFAESCryptoInputStreamErrorMemoryAllocationFailed = 200,
    PSPDFAESCryptoInputStreamErrorUnknown = NSIntegerMax,

    PSPDFErrorCodeAESCryptoInputStreamUnknownVersionInFileHeader PSPDF_DEPRECATED(9.4, 4.4, "Use `.unknownVersionInFileHeader` instead.") = PSPDFAESCryptoInputStreamErrorUnknownVersionInFileHeader,
    PSPDFErrorCodeAESCryptoInputStreamWrongCloseCalled PSPDF_DEPRECATED(9.4, 4.4, "Use `.wrongCloseCalled` instead.") = PSPDFAESCryptoInputStreamErrorWrongCloseCalled,
    PSPDFErrorCodeAESCryptoInputStreamCryptorCreationFailed PSPDF_DEPRECATED(9.4, 4.4, "Use `.cryptorCreationFailed` instead.") = PSPDFAESCryptoInputStreamErrorCryptorCreationFailed,
    PSPDFErrorCodeAESCryptoInputStreamCryptorResetToIVFailed PSPDF_DEPRECATED(9.4, 4.4, "Use `.cryptorResetToIVFailed` instead.") = PSPDFAESCryptoInputStreamErrorCryptorResetToIVFailed,
    PSPDFErrorCodeAESCryptoInputStreamCloseExpectedInsteadOfRead PSPDF_DEPRECATED(9.4, 4.4, "Use `.closeExpectedInsteadOfRead` instead.") = PSPDFAESCryptoInputStreamErrorCloseExpectedInsteadOfRead,
    PSPDFErrorCodeAESCryptoInputStreamErrorDecryptingBlock PSPDF_DEPRECATED(9.4, 4.4, "Use `.decryptingBlockFailed` instead.") = PSPDFAESCryptoInputStreamErrorDecryptingBlockFailed,
    PSPDFErrorCodeAESCryptoInputStreamCryptorFinalFailed PSPDF_DEPRECATED(9.4, 4.4, "Use `.cryptorFinalFailed` instead.") = PSPDFAESCryptoInputStreamErrorCryptorFinalFailed,
    PSPDFErrorCodeAESCryptoInputStreamHMACCheckFailed PSPDF_DEPRECATED(9.4, 4.4, "Use `.hMACCheckFailed` instead.") = PSPDFAESCryptoInputStreamErrorHMACCheckFailed,
    PSPDFErrorCodeAESCryptoInputStreamIncorrectHMACInFile PSPDF_DEPRECATED(9.4, 4.4, "Use `.incorrectHMACInFile` instead.") = PSPDFAESCryptoInputStreamErrorIncorrectHMACInFile,
    PSPDFErrorCodeAESCryptoInputStreamFailedToAllocateMemory PSPDF_DEPRECATED(9.4, 4.4, "Use `.memoryAllocationFailed` instead.") = PSPDFAESCryptoInputStreamErrorMemoryAllocationFailed,
    PSPDFErrorCodeAESCryptoInputStreamUnknown PSPDF_DEPRECATED(9.4, 4.4, "Use `.unknown` instead.") = PSPDFAESCryptoInputStreamErrorUnknown,
} PSPDF_ENUM_SWIFT(AESCryptoInputStreamError);

NS_ASSUME_NONNULL_END
