//
//  PSPDFAlertController.h
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

NS_ASSUME_NONNULL_BEGIN

/// Mac Catalyst converts alerts to NSAlert. We can set alert levels here optionally.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFAlertStyle) {
    // @see NSAlertStyleWarning
    PSPDFAlertStyleWarning = 0,
    // @see NSAlertStyleInformational
    PSPDFAlertStyleInformational = 1,
    // @see NSAlertStyleCritical
    PSPDFAlertStyleCritical = 2
} NS_SWIFT_NAME(AlertStyle);

@class PSPDFAlertController;

@interface UIViewController (PSPDFAlerts)

/// Convenience method that presents an alert on the receiver with a single "Dismiss" button.
- (void)pspdf_presentDismissibleAlertWithTitle:(nullable NSString *)title message:(nullable NSString *)message;

/// Convenience method that presents an alert on the receiver with a single "Dismiss" button.
- (void)pspdf_presentDismissibleAlertWithTitle:(nullable NSString *)title error:(nullable NSError *)error;

@end

/// Defines a single button/action.
PSPDF_APP_CLASS_SUBCLASSING_RESTRICTED_SWIFT(AlertAction)
@interface PSPDFAlertAction : UIAlertAction

/// Creates a new alert action with the `UIAlertActionStyleDefault` appearance.
+ (instancetype)actionWithTitle:(nullable NSString *)title handler:(void (^_Nullable)(UIAlertAction *action))handler;

@end

/// `UIAlertController` subclass with extra convenience methods .
///
/// @note Blocks are generally executed after the dismiss animation is completed.
PSPDF_APP_CLASS_SUBCLASSING_RESTRICTED_SWIFT(AlertController)
@interface PSPDFAlertController : UIAlertController

/// Create a new alert controller with the `UIAlertControllerStyleActionSheet` appearance.
+ (instancetype)actionSheetWithTitle:(nullable NSString *)title;

/// Create a new alert controller with the `UIAlertControllerStyleAlert` appearance.
+ (instancetype)alertWithTitle:(nullable NSString *)title message:(nullable NSString *)message;

/// Create a new simple alert with "Dismiss" button.
+ (instancetype)dismissibleAlertWithTitle:(nullable NSString *)title message:(nullable NSString *)message;

/// Create a new simple error alert with "Dismiss" button.
+ (instancetype)dismissibleAlertWithTitle:(nullable NSString *)title error:(nullable NSError *)error;

/// Convenience method for presenting the alert.
///
/// @param sender Optional sender, used to configure popover arrow.
/// @param controller Presenting view controller.
/// @param animated Whether the presentation should be animated.
/// @param completion Completion block called after presentation animation completes.
- (void)showWithSender:(nullable id)sender controller:(UIViewController *)controller animated:(BOOL)animated completion:(nullable void (^)(void))completion;

/// From Apple's HIG:
/// In a two-button alert that proposes a potentially risky action, the button that cancels the action should be on the right (and light-colored).
/// In a two-button alert that proposes a benign action that people are likely to want, the button that cancels the action should be on the left (and dark-colored).
- (void)addCancelActionWithHandler:(nullable void (^)(UIAlertAction *action))handler;

/// Add block that is called after the alert controller will be dismissed (before animation).
- (void)addWillDismissBlock:(void (^)(void))willDismissBlock;

/// Add block that is called after the alert view has been dismissed (after animation).
- (void)addDidDismissBlock:(void (^)(void))didDismissBlock;

/// Returns YES when the alert controller instance is visible.
@property (nonatomic, readonly, getter=isVisible) BOOL visible;

/// Returns YES is any PSPDFAlertControllers are currently shown.
@property (class, atomic, readonly) BOOL hasVisibleAlertController;

/// Returns the first text field.
@property (nonatomic, readonly, nullable) UITextField *textField;

/// Set the alert style (Mac Catalyst only)
///
/// It defaults to `PSPDFAlertStyleWarning`.
@property (nonatomic) PSPDFAlertStyle alertStyle;

@end

@interface UIAlertAction (Images)

/// Sets an image to the alert action.
///
/// @note Uses private API, but tries to do it in a safe way.
@property (nonatomic, nullable) UIImage *pspdf_image;

@end

NS_ASSUME_NONNULL_END
