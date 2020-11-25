//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationProvider.h>
#import <PSPDFKit/PSPDFDataProviding.h>

NS_ASSUME_NONNULL_BEGIN

/// Parses an XML in the XFDF standard.
/// http://partners.adobe.com/public/developer/en/xml/XFDF_Spec_3.0.pdf
PSPDF_CLASS_SWIFT(XFDFParser)
@interface PSPDFXFDFParser : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Designated initializer.
- (instancetype)initWithDataProvider:(id<PSPDFDataProviding>)dataProvider documentProvider:(PSPDFDocumentProvider *)documentProvider NS_DESIGNATED_INITIALIZER;

/// Parse XML and block until it's done. Returns the resulting annotations after parsing is finished
/// (which can also be accessed later on).
/// `PSPDFFormField` will not be returned by this method, but if values were imported they are now set in the
/// appropriate fields on `documentProvider.formParser.formFields`.
///
/// @warning If the XFDF contains annotations with page indicies beyond the length of the document,
/// then warnings will be logged and those annotations will be skip but otherwise parsing will
/// complete successfully. It will not return an error for this case.
- (nullable NSArray<PSPDFAnnotation *> *)parseWithError:(NSError **)error;

/// Return all annotations as array. Annotations are sorted by page.
@property (nonatomic, copy, readonly) NSArray<PSPDFAnnotation *> *annotations;

/// Returns YES if parsing has ended for `dataProvider`.
@property (atomic, readonly) BOOL parsingEnded;

/// The attached document provider.
@property (nonatomic, weak, readonly) PSPDFDocumentProvider *documentProvider;

/// The used data provider.
@property (nonatomic, readonly) id<PSPDFDataProviding> dataProvider;

@end

NS_ASSUME_NONNULL_END
