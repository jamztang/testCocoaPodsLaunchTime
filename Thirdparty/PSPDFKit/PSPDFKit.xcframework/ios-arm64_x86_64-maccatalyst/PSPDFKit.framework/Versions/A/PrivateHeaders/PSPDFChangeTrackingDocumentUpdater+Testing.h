//
//  Copyright © 2019-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFChangeTrackingDocumentUpdater.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation, PSPDFFormField;

@interface PSPDFChangeTrackingDocumentUpdater ()

/// Returns a list of platform annotations, given a set of object IDs and page indices.
- (NSArray<PSPDFAnnotation *> *)affectedPlatformAnnotations:(NSArray *)affectedAnnotationsIds pageIndices:(NSSet *)affectedAnnotationsPageIndices;

/// Returns a list of platform form fields, given a set of object IDs.
- (NSArray<PSPDFFormField *> *)affectedPlatformFormFields:(NSArray *)formFieldIds;

@end

NS_ASSUME_NONNULL_END
