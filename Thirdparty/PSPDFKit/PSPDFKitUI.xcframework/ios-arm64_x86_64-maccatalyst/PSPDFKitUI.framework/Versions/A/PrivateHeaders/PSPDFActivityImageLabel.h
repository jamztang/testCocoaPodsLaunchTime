//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Image above label, both sized correctly.
PSPDF_APP_CLASS_SWIFT(ActivityImageLabel)
@interface PSPDFActivityImageLabel : UIView

/// Label.
@property (nonatomic, readonly) UILabel *label;

/// Convenience constructor.
+ (instancetype)labelWithText:(NSString *)text subtitle:(nullable NSString *)subtitle image:(nullable UIImage *)image showActivity:(BOOL)showActivity;

/// Update state
- (void)setText:(NSString *)text subtitle:(nullable NSString *)subtitle image:(nullable UIImage *)image showActivity:(BOOL)activity;

@end

NS_ASSUME_NONNULL_END
