//
//  Copyright © 2019-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFRenderOptions.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *PSPDFLegacyRenderOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(LegacyRenderOption);

/// Applies the non-default values from source to target, and returns a new `PSPDFRenderOptions` instance.
PSPDF_EXPORT PSPDFRenderOptions *PSPDFUpdateTargetRenderOptionsWithUpdatedValuesFromSource(PSPDFRenderOptions * _Nullable target, PSPDFRenderOptions * _Nullable source);

@interface PSPDFRenderOptions ()

@property (nonatomic) BOOL shouldAnimate;

/// Set to `true` to skip the rendering of the annotations text. Defaults to `false`.
@property (nonatomic) BOOL skipTextRendering;

/// Set to `true` to draw the current absolute tab order in each element. Defaults to `false`.
@property (nonatomic) BOOL drawTabOrder;

/// Used by the `PSPDFRenderManager` (`PSPDFPageRendererPageInfoKey`) to pass page info into the core page renderer.
@property (nonatomic, nullable) NSDictionary<NSString *, id> *extraInfo;

/// Annotation Drawing

/// Disables the AP stream generator.
///
/// This is needed when the AP stream generator delegates generating an AP stream
/// to core, otherwise we end up in an endless loop.
@property (nonatomic) BOOL disableAPStreamGenerator;

/// Forces the note annotation to draw as text.
@property (nonatomic) BOOL drawNoteAnnotationAsText;

/// Tries to convert a legacy render options dictionary (PSPDFKit 8.x and below) into a
/// PSPDFRenderOptions object, and returns it.
///
/// @param dictionary The dictionary that contains the legacy keys. See `-[PSPDFDocument initWithCoder:]`.
- (nullable instancetype)initWithLegacyDictionary:(nullable NSDictionary<PSPDFLegacyRenderOption, id> *)dictionary;

/// Returns a set of the classes required for decoding the legacy property map from PSPDFKit 8.x and earlier.
+ (NSSet<Class> *)classesRequiredForDecodingLegacyPropertyMap;

@end

NS_ASSUME_NONNULL_END
