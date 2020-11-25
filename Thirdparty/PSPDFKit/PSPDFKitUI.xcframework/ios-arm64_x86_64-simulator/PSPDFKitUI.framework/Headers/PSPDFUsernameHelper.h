//
//  Copyright © 2015-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFViewController;

NS_ASSUME_NONNULL_BEGIN

/// Posted after the username view controller is dismissed, both when the user cancels or confirms the name.
/// Can be used to reset the first responder after the username flow is complete.
PSPDF_EXPORT NSNotificationName const PSPDFUsernameHelperDidDismissViewNotification;

/// A helper that can be used to present a dialog, allowing the user to specify the annotation author name.
PSPDF_CLASS_SWIFT(UsernameHelper)
@interface PSPDFUsernameHelper : NSObject

/// Access or set the default annotation username.
///
/// This property uses `NSUserDefaults` for storage (the `PSPDFDocumentDefaultAnnotationUsernameKey` key).
///
/// The default will be inferred based on the device name and some internal logic.
/// This is also the value that will be used if the property is reset by setting `nil`.
///
/// @note The username set here will be used as the default value of `PSPDFDocument.defaultAnnotationUsername`
/// for newly created documents. Updating this value will not update the value on existing documents.
@property (nonatomic, class, null_resettable) NSString *defaultAnnotationUsername;

/// Checks for `PSPDFDocumentDefaultAnnotationUsernameKey`.
@property (nonatomic, class, readonly) BOOL isDefaultAnnotationUserNameSet;

/// Asks for the default new annotation username.
///
/// This will only display UI if enabled in the controller configuration and if the username is not already set.
///
/// Use this call if you're presenting a custom annotation creation UI (e.g., a custom toolbar).
/// Present your UI / toolbar inside the completion block. The behavior above ensures
/// that the UI action is not performed if the dialog is canceled.
///
/// @param pdfViewController The view controller to use as the presenting view controller.
/// @param completionBlock Called when the UI is dismissed, unless the displayed dialog is canceled.
+ (void)askForDefaultAnnotationUsernameIfNeeded:(PSPDFViewController *)pdfViewController completionBlock:(void (^)(NSString *userName))completionBlock;

/// Asks for a new default username on the provided view controller.
///
/// @param viewController The view controller to use as the presenting view controller.
/// @param suggestedName A username to be pre-filled in the dialog. If `nil` we'll try to guess the username.
/// @param completionBlock Called when the UI is dismissed, unless the displayed dialog is canceled.
///
/// @see `askForDefaultAnnotationUsernameIfNeeded:completionBlock:`
- (void)askForDefaultAnnotationUsername:(UIViewController *)viewController suggestedName:(nullable NSString *)suggestedName completionBlock:(void (^)(NSString *userName))completionBlock;

@end

NS_ASSUME_NONNULL_END
