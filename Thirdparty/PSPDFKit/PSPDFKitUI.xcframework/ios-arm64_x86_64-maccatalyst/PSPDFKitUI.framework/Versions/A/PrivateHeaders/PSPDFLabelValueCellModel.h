//
//  Copyright © 2016-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKitUI/PSPDFCellModel.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFStaticTableViewController;

// --------------
// |-label-value|
// |      -value|
// --------------
@interface PSPDFLabelValueCellModel : PSPDFCellModel

/// The label shown next to the value field.
@property (nonatomic, copy) NSString *label;

/// The value shown in the text field.
@property (nonatomic, copy, nullable) id value;

@property (nonatomic, copy, nullable) NSString *title NS_UNAVAILABLE;
@property (nonatomic, copy, nullable) NSString *subtitle NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
