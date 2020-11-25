//
//  Copyright © 2014-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKitUI/PSPDFControlDelegate.h>
#import <PSPDFKitUI/PSPDFPresentationActions.h>
#import <PSPDFKitUI/PSPDFVisiblePagesDataSource.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument;

@protocol PSPDFDocumentActivityControllerPresenter <NSObject>

@optional

/// This method will get called at an appropriate time for custom view controller presentation.
- (void)presentControllerAnimated:(BOOL)animated;

@end

/// Base class for various document activities.
PSPDF_APP_CLASS_SWIFT(DocumentActivity)
@interface PSPDFDocumentActivity : UIActivity<PSPDFDocumentActivityControllerPresenter>

/// Required for custom popover presentation.
@property (nonatomic, weak) UIViewController<PSPDFPresentationActions> *presentationController;
@property (nonatomic, weak) id actionSender;

/// UIActivity doesn't like custom activityItems, so we pass them along the old-school way.
@property (nonatomic, nullable) NSArray<PSPDFDocument *> *documents;

/// Delegate to access page controls
@property (nonatomic, weak) id<PSPDFPageControls> pageControlsDelegate;

/// Delegate used for getting the list of visible pages.
///
/// `PDFViewController` implements this protocol.
@property (nonatomic, weak) id<PSPDFVisiblePagesDataSource> visiblePagesDataSource;


/// Enhanced version of performActivity that works better for popovers.
/// Use this instead of the stock `performActivity`.
- (void)performActivityAnimated:(BOOL)animated NS_REQUIRES_SUPER;

@end

NS_ASSUME_NONNULL_END
