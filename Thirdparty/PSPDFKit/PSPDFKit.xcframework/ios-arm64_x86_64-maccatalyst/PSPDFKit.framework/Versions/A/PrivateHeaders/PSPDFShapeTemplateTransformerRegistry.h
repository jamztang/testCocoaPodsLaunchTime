//
//  Copyright © 2018-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFShapeTemplate.h>

NS_ASSUME_NONNULL_BEGIN

/// This class handles the registration of transformers for a given template identifier.
/// Note that each template identifier can only have a single transformer associated with it.
PSPDF_SDK_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ShapeTemplateTransformerRegistry)
@interface PSPDFShapeTemplateTransformerRegistry : NSObject

/// The shared registry. By default the registry has transformers defined for PSPDFKit's default set of templates.
@property (class, nonatomic, readonly) PSPDFShapeTemplateTransformerRegistry *sharedInstance NS_SWIFT_NAME(shared);

/// Registers the passed in transformer class for transforming a given template.
///
/// @param cls The class for the transformer.
/// @param identifier The template identifier for which the transformer is being registered.
- (void)registerTransformerClass:(nullable Class)cls forTemplateIdentifier:(PSPDFShapeTemplateIdentifier)identifier;

/// Retrieves the transformer class currently registered for a given identifier.
///
/// @param identifier The identifier for which
/// @return The class for `identifier`, if it was registered. Else `nil.`
- (nullable Class)transformerClassForIdentifier:(PSPDFShapeTemplateIdentifier)identifier;

@end

NS_ASSUME_NONNULL_END
