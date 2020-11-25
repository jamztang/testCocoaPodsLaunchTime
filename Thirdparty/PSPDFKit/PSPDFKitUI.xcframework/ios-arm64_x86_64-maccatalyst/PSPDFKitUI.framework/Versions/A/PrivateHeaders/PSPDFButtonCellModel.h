//
//  Copyright © 2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFCellModel.h>

NS_ASSUME_NONNULL_BEGIN

/// Models a cell that performs a discrete action when tapped, using `PSPDFButtonCell`. When running on iOS, the ‘button’ is the cell itself. When running optimized for Mac, an actual button is added to the cell.
PSPDF_APP_CLASS_SWIFT(ButtonCellModel)
@interface PSPDFButtonCellModel : PSPDFCellModel

@end

NS_ASSUME_NONNULL_END
