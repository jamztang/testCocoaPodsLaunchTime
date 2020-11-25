//
//  Copyright © 2017-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKitUI/PSPDFPageGrabber.h>

/// The default page grabber view draws a rectangular shape with a grabber icon in
/// it. In the collapsed state it draws the shape in a small size and when expanded
/// the size is increased so that the user can still see the shape moving under their
/// finger.
PSPDF_APP_CLASS_SWIFT(DefaultPageGrabberView)
@interface PSPDFDefaultPageGrabberView : UIView <PSPDFPageGrabberView>

/// @see -[PSPDFPageGrabberView setCollapsed:animated:]
@property (nonatomic, getter=isCollapsed) BOOL collapsed;

/// The fill color is the color for the view underneath the visual effects view.
/// You can use this to slightly tint the blur effect. Defaults to clear color.
@property (nonatomic) UIColor *fillColor UI_APPEARANCE_SELECTOR;

/// The stroke color is the color that the grabber view uses for its outline and
/// drag indicators. Defaults to semi-translucent black.
@property (nonatomic) UIColor *strokeColor UI_APPEARANCE_SELECTOR;

@end
