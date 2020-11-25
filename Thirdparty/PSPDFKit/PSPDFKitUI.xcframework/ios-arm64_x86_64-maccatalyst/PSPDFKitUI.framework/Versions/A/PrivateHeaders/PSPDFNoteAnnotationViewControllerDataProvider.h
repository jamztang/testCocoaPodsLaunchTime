//
//  Copyright © 2016-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>
#import <PSPDFKit/PSPDFOverrideProvider.h>
#import <PSPDFKit/PSPDFAnnotationAuthorState.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation, PSPDFComment, PSPDFConfiguration, PSPDFIndexPathDiff, PSPDFNoteAnnotationViewControllerDataProvider, UIColor;
@protocol PSPDFApplicationPolicy;

/// Enumerates the possible results of deleting all the comments.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFDeleteAllCommentsResult) {
    /// Nothing happened because no annotation is set.
    PSPDFDeleteAllCommentsResultNone,
    /// All annotations were deleted including the top one.
    PSPDFDeleteAllCommentsResultDeleted,
    /// Replies were deleted. The top annotation’s contents were cleared but it was not deleted.
    PSPDFDeleteAllCommentsResultClearedContents,
} NS_SWIFT_NAME(DeleteAllCommentsResult);

/// This protocol is the interface the data provider uses to notify the views of updates.
NS_SWIFT_NAME(NoteAnnotationViewControllerDataProviderDelegate)
@protocol PSPDFNoteAnnotationViewControllerDataProviderDelegate <NSObject>

/// Notifies the delegate that data is about to be saved so pending changes should be written to the data provider immediately.
- (void)noteAnnotationViewControllerDataProviderRequestsPendingChanges:(PSPDFNoteAnnotationViewControllerDataProvider *)dataProvider;

/// Notifies the delegate that the data provided by the data provider has changed, and should be reloaded.
/// When this is called the delegate should always reload all data not associated with comments at particular indexes.
///
/// @param dataProvider The data provider whose data changed.
/// @param indexPathDiff The indexes of the comments that need reloading, stored in the index path rows.
- (void)noteAnnotationViewControllerDataProvider:(PSPDFNoteAnnotationViewControllerDataProvider *)dataProvider didUpdateWithIndexPathDiff:(PSPDFIndexPathDiff *)indexPathDiff;

@end

/// This is the interface for two-way communication between a `PSPDFNoteAnnotationViewController` and the model layer.
/// Some people might call this a view-model.
///
/// The data shown consists of a top annotation and the replies to that annotation, collectivly called comments,
/// so if the top annotation has 3 replies then there are 4 comments.
///
/// The set of all the comments could be called thread.
NS_SWIFT_NAME(NoteAnnotationViewControllerDataProvider)
@interface PSPDFNoteAnnotationViewControllerDataProvider : NSObject

/// Delegate so the data provider can notify the view layer of updates.
@property (nonatomic, weak) id<PSPDFNoteAnnotationViewControllerDataProviderDelegate, PSPDFOverrideProvider> delegate;

/// A succinct user-facing title for the information being shown.
@property (nonatomic, readonly, nullable) NSString *title;

/// The color to use for the view’s background, which is derived from the annotation colors.
@property (nonatomic, readonly) UIColor *backgroundColor;

/// The color to use for lighter backgrounds, which is derived from the annotation colors.
@property (nonatomic, readonly) UIColor *lightBackgroundColor;

/// The color to use for significant elements, which is derived from the annotation colors.
@property (nonatomic, readonly) UIColor *tintedMediumColor;

/// The color to use for emphasized text content, which is derived from the annotation colors.
@property (nonatomic, readonly) UIColor *navigationBarContentColor;

/// The color to use for emphasized text content, which is derived from the annotation colors.
@property (nonatomic, readonly) UIColor *weakerTintedContentColor;

/// The color to use for emphasized text content on significant elements, which is derived from the annotation colors.
@property (nonatomic, readonly) UIColor *strongerTintedContentColor;

#pragma mark - Comments list

/// The number of comments to display.
@property (nonatomic, readonly) NSUInteger numberOfComments;

/// Properties of the comment at a given index. Must be less than numberOfComments or an exception will be raised.
- (PSPDFComment *)commentAtIndex:(NSUInteger)commentIndex;

/// Sets a comment text content.
- (void)setText:(NSString *)text forCommentAtIndex:(NSUInteger)commentIndex;

/// Determines if and where editing should be started for the current comments.
///
/// @return The index of the comment where editing should be started. Will return `NSNotFound` if editing should not be started.
- (NSUInteger)commentIndexForBeginningEditing;

#pragma mark - Text policy

/// The policy for for certain events in the comment text views.
@property (nonatomic, readonly) id<PSPDFApplicationPolicy> policy;

#pragma mark - Adding replies

/// Whether the user is allowed to add a reply/comment.
@property (nonatomic, readonly) BOOL allowsAddingReplies;

/// Whether the user is allowed to edit a reply/comment.
@property (nonatomic, readonly) BOOL allowsEditingReplies;

/// Adds a new empty reply/comment.
- (void)addReply;

#pragma mark - Reviews

/// Adds a status for the current user to the comment at the specified index.
- (void)addAuthorState:(PSPDFAnnotationAuthorState)authorState toCommentAtIndex:(NSUInteger)commentIndex;

/// Number formatter that should be used to format the number of review states displayed in the UI.
@property (nonatomic, readonly) NSNumberFormatter *numberFormatter;

#pragma mark - Deleting

/// Whether the user is allowed to delete all the comments (the whole thread).
@property (nonatomic, readonly) BOOL allowsDeletingAllComments;

/// Whether the user is allowed to delete the comment at the specified index.
- (BOOL)allowsDeletingCommentAtIndex:(NSUInteger)commentIndex;

/// The title to show on the button that will delete all the comments.
@property (nonatomic, readonly) NSString *deleteAllCommentsTitle;

/// Deletes all the comments and returns what happened so the correct public delegate callback can be called.
- (PSPDFDeleteAllCommentsResult)deleteAllComments;

/// Deletes the comment at the specific index.
/// If `commentIndex` is `0`, which maps to the parent annotations, only its `contents` is cleared,
/// as otherwise all the comments wouldn't have a parent annotation anymore.
- (BOOL)deleteCommentAtIndex:(NSUInteger)commentIndex;

#pragma mark - Menu Button Visibility

/// Whether to show the menu button for that particular index.
- (BOOL)shouldShowAuxiliaryMenuAtCommentIndex:(NSUInteger)commentIndex;

#pragma mark - Note style

/// Whether the user is allowed to set the color and icon. This is only possible for note annotations.
@property (nonatomic, readonly) BOOL allowsStyleChanges;

/// The currently set note annotation icon name, or nil if the top annotation is not a note annotation.
@property (nonatomic, copy, nullable) NSString *noteIconName;

/// The currently set note annotation color, or nil if the top annotation is not a note annotation.
@property (nonatomic, nullable) UIColor *noteColor;

#pragma mark - Pass-through from public API

/// The top annotation. The comments to be displayed are comments on this annotation.
///
/// The view controller’s annotation property should forward to this property.
///
/// Please do not read this property except to meet the needs of public API because it
/// is the data provider’s job to extract relevant information from the annotation.
@property (nonatomic, nullable) PSPDFAnnotation *annotation;

/// The view controller’s configuration property should forward to this property.
///
/// Please do not read this property at any other time because it is the
/// data provider’s job to extract relevant information from the configuration.
@property (nonatomic, nullable) PSPDFConfiguration *configuration;

/// The view controller’s showColorAndIconOptions property should forward to this property.
///
/// Please do not read this property at any other time because it is the
/// data provider’s job to consider this setting when appropriate.
@property (nonatomic) BOOL allowsStyleChanges_manuallySet;

@end

NS_ASSUME_NONNULL_END
