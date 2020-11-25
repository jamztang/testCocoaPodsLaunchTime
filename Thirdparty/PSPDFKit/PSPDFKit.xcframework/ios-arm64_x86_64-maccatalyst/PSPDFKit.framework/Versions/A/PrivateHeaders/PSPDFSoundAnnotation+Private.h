//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFSoundAnnotation.h>

@class PSPDFCoreAnnotation;

NS_ASSUME_NONNULL_BEGIN
@interface PSPDFSoundAnnotation ()

@property (atomic, copy, nullable) NSURL *soundURL;
@property (atomic) BOOL canRecord;
@property (atomic) NSTimeInterval recordingTimeLimit;

- (instancetype)initWithRate:(NSUInteger)rate channels:(uint32_t)channels bits:(uint32_t)bits encoding:(NSString *)encoding NS_DESIGNATED_INITIALIZER;

@end
NS_ASSUME_NONNULL_END
