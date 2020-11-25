//
//  Copyright © 2014-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIResponder (PSPDFFoundation)

/// Fast way to find the current first responder.
+ (nullable UIResponder *)pspdf_firstResponder;

/// Checks if the receiver is has an instance of any of the classes in `responderClasses` as a parent in the responder chain.
///
/// @param responderClasses The classes to check for.
/// @return `true` if an instance of any of `responderClasses` is above the receiver in the chain.
- (BOOL)pspdf_isInsideAnyInstanceOfResponderClasses:(NSArray<Class> *)responderClasses;

#if DEBUG
/// Debug feature to print the full responder chain.
+ (void)pspdf_printResponderChainWithFullDescriptions:(BOOL)withDescriptions;
+ (void)pspdf_printResponderChain;
#endif

@end

@interface UIView (PSPDFFirstResponder)

/// Finds the first responder if it's inside a subview.
@property (nonatomic, readonly, nullable) UIView *pspdf_firstResponderInsideView;

/// Checks if the first responder is a text input.
///
/// This method only returns true for native text inputs. E.g. it returns `false` for
/// text input inside a web view.
@property (nonatomic, readonly) BOOL pspdf_firstResponderIsTextInput;

@end

/// This is a workaround for the unfortunate way UIKit decides between text input and UIKeyCommands.
///
/// Key commands from the responder chain take precedence over sending the event to a UITextField or
/// UITextView. This function is a best effort to return an array by removing items from the input so that
/// the key commands do not conflict with text input. Call this in an implementation of keyCommands when
/// you don’t know whether text input is happening and you don’t want to interfere with text editing.
///
/// Do not call this function if you do want your commands to take precedence over text input.
///
/// @param commands The proposed key commands.
/// @return Filtered input to exclude commands that would interfere with text input.
PSPDF_EXTERN NSArray<UIKeyCommand *> *PSPDFKeyCommandsByRemovingTextInputConflictsIfRequired(NSArray<UIKeyCommand *> *commands) NS_SWIFT_NAME(KeyCommandsByRemovingTextInputConflictsIfRequired(_:));

NS_ASSUME_NONNULL_END
