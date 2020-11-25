//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAction.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation, PSPDFCoreAnnotation, PDFCPDFObject;
@protocol PSPDFPropertyMapReader;

/// A reference to an Annotation
@interface PSPDFAnnotationReference : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

- (instancetype)initWithFieldName:(nullable NSString *)fieldName objNum:(NSInteger)objNum genNum:(NSInteger)genNum NS_DESIGNATED_INITIALIZER;

/// The optional fieldName.
@property (nonatomic, readonly, nullable) NSString *fieldName;

/// The optional objNum.
@property (nonatomic, readonly) NSInteger objNum;

/// The optional generation number.
@property (nonatomic, readonly) NSInteger genNum;

@end

/// Actions implementing this protocol need to run through a second pass to resolve annotations.
@protocol PSPDFResolvableAction <NSObject>

@property (nonatomic, copy, nullable) NSArray<PSPDFAnnotation *> *annotations;
@property (nonatomic, copy, nullable) NSArray<PSPDFAnnotationReference *> *annotationReferences;

@end

/// Recurses into the subactions of the given `actions`, post processing all objects that may reference
/// one or more annotations from the given array by resolving those references.
///
/// This function should only be called by a class that implements `PSPDFAnnotationProviding`, and only
/// as part of its parsing/deserialization implementation. It is a free function because not all of our
/// annotation providers can inherit from `PSPDFContainerAnnotationProvider`.
///
/// @param actions The actions that require post processing.
/// @param annotationPool The annotations to search from when resolving references.
void PSPDFPostProcessFreshlyParsedActions(NSArray<__kindof PSPDFAction *> *actions, NSArray<PSPDFAnnotation *> *annotationPool);

@interface PSPDFAction ()

/// Is inside the option dictionary if a `pspdfkit://` URL has been detected.
PSPDF_EXTERN NSString *const PSPDFActionIsPSPDFPrefixedURL;
PSPDF_EXTERN NSString *const PSPDFURLActionProcessed;

/// Init for subclasses.
- (instancetype)initWithType:(PSPDFActionType)actionType;

/// Parses a action from the core annotation.
///
/// @return Will return the appropriate subclass of `PSPDFAction` or nil if action couldn't be resolved.
+ (nullable instancetype)actionWithPropertyReader:(id<PSPDFPropertyMapReader>)coreAnnotation;

/// Writeable parentAction
@property (atomic, weak) PSPDFAction *parentAction;

/// Writable variants
@property (nonatomic, copy, nullable) NSDictionary<NSString *, id> *options;

/// A manually set inverse action (used by the back / forward navigation).
@property (nonatomic, nullable) PSPDFAction *inverseAction;

@end

NS_ASSUME_NONNULL_END
