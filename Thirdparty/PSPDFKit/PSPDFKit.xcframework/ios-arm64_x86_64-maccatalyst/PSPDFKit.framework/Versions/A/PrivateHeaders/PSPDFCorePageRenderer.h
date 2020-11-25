//
//  Copyright © 2014-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFDocumentProvider, PSPDFAnnotation, PSPDFRenderOptions;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFCorePageRenderer : NSObject

/// Sends a request to the underlying core page renderer to cancel the rendering
/// operation in the next available checkpoint.
///
/// @param cancellationToken   The token that was used to start the rendering.
/// @param documentProvider    The document provider that serves the current rendering operation.
/// @param pageIndex           The index of the page that's being rendered.
///
/// @return `true` if the underlying renderer accepted the cancellation request. `false` if there was no rendering operation associated with the provided cancellation token active.
///
/// @note When this method returns `true`, it does not mean that the rendering operation *was* cancelled, but that it will eventually be cancelled. Cancellation call requires a core lock and might be slow; advisable to call on a background thread.
- (BOOL)cancelWithToken:(int)cancellationToken documentProvider:(PSPDFDocumentProvider *)documentProvider pageIndex:(PSPDFPageIndex)pageIndex;

/// Renders the current page index into a context.
- (BOOL)drawPageAtIndex:(PSPDFPageIndex)pageIndex inContext:(CGContextRef)context documentProvider:(PSPDFDocumentProvider *)documentProvider withOptions:(nullable PSPDFRenderOptions *)options error:(NSError **)error cancellationToken:(nullable NSNumber *)cancellationToken;

/// Renders annotation appearance streams.
///
/// @return NO if rendering failed.
- (BOOL)renderAppearanceStream:(PSPDFAnnotation *)annotation inContext:(CGContextRef)context withOptions:(nullable PSPDFRenderOptions *)options error:(NSError **)error;
@end

NS_ASSUME_NONNULL_END
