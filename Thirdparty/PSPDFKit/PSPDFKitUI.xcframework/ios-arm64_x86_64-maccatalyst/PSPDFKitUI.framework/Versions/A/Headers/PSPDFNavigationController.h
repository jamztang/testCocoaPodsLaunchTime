//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Simple subclass that forwards following iOS 6+ rotation methods to the top view controller:
/// `shouldAutorotate`, `supportedInterfaceOrientations`, `preferredInterfaceOrientationForPresentation:`.
PSPDF_CLASS_SWIFT(PDFNavigationController)
@interface PSPDFNavigationController : UINavigationController<UINavigationControllerDelegate>

- (void)setDelegate:(nullable id<UINavigationControllerDelegate>)delegate PSPDF_UNAVAILABLE("Not available.");

/// Forward the modern rotation method to the visible view controller. Defaults to YES.
@property (nonatomic, getter=isRotationForwardingEnabled) BOOL rotationForwardingEnabled;

@end

NS_ASSUME_NONNULL_END
