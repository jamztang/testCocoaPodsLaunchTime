//
//  Copyright © 2019-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@interface UITableView (PSPDFAdditions)

/// Returns `UITableViewStyleGrouped` on iOS < 13 and `UITableViewStyleInsetGrouped` on iOS >= 13
@property (class, nonatomic, readonly) UITableViewStyle pspdf_insetGroupStyle NS_SWIFT_NAME(insetGroupStyle);

@end

NS_ASSUME_NONNULL_END
