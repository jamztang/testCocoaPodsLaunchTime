//
//  Copyright © 2015-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationToolbarConfiguration.h>

@class PSPDFAnnotationGroupItem;

@interface PSPDFAnnotationToolbarConfiguration (PSPDFPresets)

/// Default toolbar configurations, designed for adaptivity.
+ (NSArray<PSPDFAnnotationToolbarConfiguration *> *)defaultConfigurations;

/// Default redaction group item.
+ (PSPDFAnnotationGroupItem *)redactionGroupItem;

/// Default link group item.
+ (PSPDFAnnotationGroupItem *)linkGroupItem;

@end
