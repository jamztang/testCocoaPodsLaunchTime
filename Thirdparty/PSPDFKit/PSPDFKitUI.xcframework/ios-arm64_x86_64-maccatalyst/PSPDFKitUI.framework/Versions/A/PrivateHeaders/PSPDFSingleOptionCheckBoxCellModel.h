//
//  Copyright © 2018-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFCheckBoxCellModel.h>

NS_ASSUME_NONNULL_BEGIN

/// Custom cell model to account for single options being present.
@interface PSPDFSingleOptionCheckBoxCellModel : PSPDFCheckBoxCellModel

/// Creates a cell with the given title and configures it as single option given the onlyOption flag.
+ (instancetype)cellWithTitle:(nullable NSString *)cellTitle isOnlyOption:(BOOL)onlyOption;

@end

NS_ASSUME_NONNULL_END
