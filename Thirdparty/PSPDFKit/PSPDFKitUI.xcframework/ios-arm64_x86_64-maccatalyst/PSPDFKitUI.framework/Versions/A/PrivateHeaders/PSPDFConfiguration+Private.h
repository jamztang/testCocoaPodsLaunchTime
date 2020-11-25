//
//  Copyright © 2014-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFConfiguration.h>

#import <PSPDFKit/PSPDFOverrideProvider.h>
#import <PSPDFKit/PSPDFAnnotationStyleKey.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFConfiguration () <PSPDFOverrideProvider>

#pragma mark Private Sharing Activities.

/// Pre-provided activity that opens a dialog to go to a specific page.
PSPDF_EXPORT UIActivityType const PSPDFActivityTypeGoToPage;

/// Pre-provided activity that invokes text search.
PSPDF_EXPORT UIActivityType const PSPDFActivityTypeSearch;

/// Pre-provided activity that shows the outline view controller.
PSPDF_EXPORT UIActivityType const PSPDFActivityTypeOutline;

/// Pre-provided activity that shows the bookmark view controller.
PSPDF_EXPORT UIActivityType const PSPDFActivityTypeBookmarks;

@property (nonatomic, copy, readonly) NSDictionary<Class, Class> *overrideClassNames;

/// Allows editing annotation replies. Defaults to YES.
@property (nonatomic, getter=isAnnotationRepliesEditingEnabled, readonly) BOOL annotationRepliesEditingEnabled;

/// Returns YES if we should be able to edit the provided annotations with our inspectors.
/// Based on the values in `self.propertiesForAnnotations`.
- (BOOL)hasPropertiesForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// Resolves properties for the specified annotations from the provided `propertiesForAnnotations` dictionary.
+ (NSArray<NSArray<PSPDFAnnotationStyleKey> *> *)propertiesForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations dictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

@interface PSPDFConfigurationBuilder ()

@property (nonatomic, getter=isAnnotationRepliesEditingEnabled) BOOL annotationRepliesEditingEnabled;

@end

NS_ASSUME_NONNULL_END
