//
//  Copyright © 2012-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKitUI/PSPDFMenuItem.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFMenuItem ()
@end

/// Executes invokable menu items and returns the execution count.
PSPDF_EXTERN NSUInteger PSPDFExecuteInvokableMenuItems(NSArray<PSPDFMenuItem *> *_Nullable menuItems) NS_SWIFT_NAME(ExecuteInvokableMenuItems(_:));

/// Wraps string to allow image support.
PSPDF_TEST_EXPORT NSString *PSPDFWrapStringWithInvisibleIdentifier(NSString *originalString) NS_SWIFT_NAME(WrapStringWithInvisibleIdentifier(_:));

NS_ASSUME_NONNULL_END
