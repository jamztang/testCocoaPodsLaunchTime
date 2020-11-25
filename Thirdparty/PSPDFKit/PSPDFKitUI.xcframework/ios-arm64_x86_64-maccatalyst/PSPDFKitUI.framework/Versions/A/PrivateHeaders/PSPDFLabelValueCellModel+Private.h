//
//  Copyright © 2016-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFLabelValueCellModel.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKitUI/PSPDFTableViewCell.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_APP_CLASS_SWIFT(LabelValueBaseCell)
@interface PSPDFLabelValueBaseCell : PSPDFNeverAnimatingTableViewCell

@property (nonatomic, readonly, nullable) UIImageView *imageView NS_UNAVAILABLE;
@property (nonatomic, readonly, nullable) UILabel *textLabel NS_UNAVAILABLE;
@property (nonatomic, readonly, nullable) UILabel *detailTextLabel NS_UNAVAILABLE;

@property (nonatomic, readonly) UITextView *titleTextView;
@property (nonatomic, readonly) UIView *valueView;

/// Override in subclass to provide custom value view
- (UIView *)defaultValueView;

@end

@interface PSPDFLabelValueGridCell : PSPDFLabelValueBaseCell
@end

@interface PSPDFLabelValueTextCell : PSPDFLabelValueBaseCell
@end

NS_ASSUME_NONNULL_END
