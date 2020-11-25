//
//  Copyright © 2018-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// Annotations that can be rotated conform to this protocol.
PSPDF_PROTOCOL_SWIFT(Rotatable)
@protocol PSPDFRotatable <NSObject>

/// The counterclockwise angle of the annotation relative to the page, in degrees.
/// The angle should be between 0 and 359. Defaults to 0.
///
/// To set the rotation, use `setRotation(_:, updateBoundingBox:)`.
@property (atomic, readonly) NSUInteger rotation;

/// Sets the `rotation` property, optionally updating the `boundingBox` to preserve the content size.
///
/// Updating the `boundingBox` of the annotation will ensure it encloses the content while
/// preserving the content size and center, without distorting the annotation.
///
/// Not updating the `boundingBox` would in general distort the annotation, but
/// in some cases it is required to get the correct results, such as during setup.
///
/// @param rotation The new value for the `rotation` property. This should be between 0 and 359.
/// @param shouldUpdateBoundingBoxToMaintainContentSize If true the `boundingBox` will be updated to preserve the content size.
- (void)setRotation:(NSUInteger)rotation updateBoundingBox:(BOOL)shouldUpdateBoundingBoxToMaintainContentSize;

@end
