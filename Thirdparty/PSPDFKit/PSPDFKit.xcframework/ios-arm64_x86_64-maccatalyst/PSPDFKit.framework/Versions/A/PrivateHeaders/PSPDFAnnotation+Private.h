//
//  Copyright © 2012-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationAuthorState.h>
#import <PSPDFKit/PSPDFAnnotationGroupItem.h>
#import <PSPDFKit/PSPDFAnnotationReplyType.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFFreeTextAnnotation.h>
#import <PSPDFKit/PSPDFGeometry.h>
#import <PSPDFKit/PSPDFModelObject+NSCoding.h>
#import <PSPDFKit/PSPDFRenderRequest.h>
#import <PSPDFKit/PSPDFRenderOptions+Private.h>

#ifdef __cplusplus
#import <mutex>
#endif

@class PSPDFStream, PSPDFUndoController, PSPDFPointArray, PSPDFPageInfo;
@protocol PSPDFAnnotationReviewSummary;

#define PROPERTY_LOCK_GUARD std::lock_guard<std::recursive_mutex> propertyLocker(self->_propertyLock);

#define PROPERTY_LOCKED_GETTER(type, name) PROPERTY_LOCKED_GETTER_CUSTOM(type, name, _##name)
#define PROPERTY_LOCKED_GETTER_CUSTOM(type, name, ivar) - (type)name { PROPERTY_LOCK_GUARD return ivar; }

NS_ASSUME_NONNULL_BEGIN

PSPDF_SDK_EXPORT const CGSize PSPDFAnnotationDefaultMinimumSize;

@interface PSPDFAnnotation () {
@public
    NSUInteger _page;

#ifdef __cplusplus
    // Property lock can be used to protect internal properties.
    // Only use this in subclasses — or when attaching to core
    // mutex cannot be a spinlock - needs to be recursive.
    std::recursive_mutex _propertyLock;
#endif
}

/// Editable version of `typeString`. Only to be used in special cases! (e.g. Instant)
@property (atomic, copy) PSPDFAnnotationString typeString;

@end

PSPDF_SDK_EXPORT const PSPDFAnnotationType PSPDFAnnotationTypeLineOrPolyLine;

/// Private `UIPasteboard` support.
PSPDF_SDK_EXPORT NSString *const PSPDFAnnotationPasteboardPrivateData;

/// Converts a `PSPDFAnnotationType` into the format the core understands.
PSPDF_EXTERN NSArray<NSNumber *> *PDFCAnnotationTypesFromPSPDFAnnotationType(PSPDFAnnotationType type);

#pragma mark - Creation

@interface PSPDFAnnotation ()

/// Use this to create custom user annotations.
- (instancetype)initWithType:(PSPDFAnnotationType)annotationType NS_DESIGNATED_INITIALIZER;

/// We inherit NSSecureCoding from `PSPDFModel` — and support it ourselves…
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Use to create a new annotation that is identical to passed annotation. It works like a copy but the uuid is different.
+ (PSPDFAnnotation *)annotationWithAnnotation:(PSPDFAnnotation *)annotation;

/// Common init method.
- (void)commonInit NS_REQUIRES_SUPER;

#pragma mark -

/// Whether or not this annotation is backed by Instant.
///
/// Some annotations have to behave differently when they are backed by Instant. Since there are multiple
/// paths for instantiating (subclasses of) `PSPDFAnnotation`, and these instances need not immediately be
/// backed by a core annotation, the value of this property can change when we attach the annotatation to
/// an annotation provider.
@property (nonatomic, getter = isBackedByInstant) BOOL backedByInstant;

/// Color with added alpha value.
@property (nonatomic, readonly, nullable) UIColor *colorWithAlpha;

/// Fill color with added alpha value.
@property (nonatomic, readonly, nullable) UIColor *fillColorWithAlpha;

/// Border color with added alpha value.
@property (nonatomic, readonly, nullable) UIColor *borderColorWithAlpha;

/// Fast internal representation of the points.
@property (nonatomic, nullable) PSPDFPointArray *pointArray;

/// A stable unique identifier used to associate replies with their parents.
/// Different when copied.
@property (nonatomic) NSString *uuidForReplies;

/// Defines how the annotation will be rendered.
@property (atomic, copy, nullable) PSPDFRenderOptions *renderOptions;

/// Defines if the annotation is rendered using core or not.
@property (class, nonatomic, readonly) BOOL isRenderedUsingCore;

/// Returns YES if this annotation type has a fixed size, no matter the internal bounding box.
@property (nonatomic, readonly) BOOL isFixedSize;

/// Whether the stored points do not have the page transform applied.
///
/// We used untransformed PDF coordinates before 8.0. This property is YES
/// when old archives are read. The points will be transformed and this
/// property set to NO when the annotation is added to a page.
@property (nonatomic) BOOL requiresCoordinateTransformation;

/// The icon name for the annotation. May return a string for which no image can be found.
@property (nonatomic, readonly) NSString *annotationIconName;

/// Corresponding `PSPDFDocumentProvider`.
@property (atomic, weak) PSPDFDocumentProvider *documentProvider;

/// The variant type that best matches the annotation’s current properties.
///
/// This does not consider the variant of the tool used to create the annotation, which is stored in the `variant` property.
/// The user could make an annotation with a tool variant and then modify the properties of the annotation so it’s more like another variant.
///
/// Defaults to nil.
/// This is intended to be overridden by subclasses that support variants. There is not expected to be any need to call this directly.
@property (nonatomic, readonly, nullable) PSPDFAnnotationVariantString effectiveVariant;

/// A user-facing string describing the type of the annotation. For example Arrow, Stamp, or Callout.
///
/// This is will use variant types, but based on the actual annotation properties rather than the variant assigned to the
/// tool that created this annotation. For example line annotations with arrow heads will be called arrows regardless of
/// the tool variant used to create the annotation, or even if the annotation was created by Acrobat or whatever.
///
/// This is intended to be called, not overridden. To customize variant types override `effectiveVariant`.
@property (nonatomic, readonly) NSString *localizedType;

/// A string that describes the annotation as it appears on the page. This is nil for the base class. For overriding.
@property (nonatomic, readonly, nullable) NSString *localizedAppearanceDescription;

/// Subclasses should override this to return YES if the `localizedAppearanceDescription` does not work well on its own. This is NO for the base class.
@property (nonatomic, readonly) BOOL shouldIncludeTypeAndAppearanceDescriptionInLocalizedDescription;

@end

#pragma mark - Private Drawing

/// Private drawing hooks for subclasses inside the framework.
///
/// @note **Important:** Although `PSPDFAnnotation` _can be_ subclassed by customers, these methods are
/// internal, and only called by our own implementations of `drawInContext:withOptions:`. By ensuring
/// our own implementations of that method hold the property lock while using the methods from this
/// category, we remove the burden of acquiring the property lock from their implementations without
/// jeopardizing consistency.
@interface PSPDFAnnotation (PrivateDrawing)

/// Draw the note icon, if there's a note or replies for the annotation.
///
/// @note Acquiring the property lock is the caller’s responsibility. In general, this should be
/// `drawInContext:withOptions:`.
- (BOOL)drawNoteIconIfNeededInContext:(nullable CGContextRef)context withOptions:(nullable PSPDFRenderOptions *)options;

/// In general, overriding `noteIconPoint` is better.
@property (nonatomic, readonly) CGRect noteIconRect;

/// Whether or not the note icon should be displayed with the given options.
///
/// @note Subclasses **must** acquire the property lock when overriding. (`PSPDFAnnotationView` uses
/// this method. So not all callers are annotations…)
- (BOOL)shouldDrawNoteIconWithOptions:(nullable PSPDFRenderOptions *)options;

/// The alpha, the note icon should be drawn with. Defaults to 0.5.
@property (nonatomic, readonly) CGFloat noteIconAlpha;

/// Draw the bounding box.
///
/// @note Acquiring the property lock is the caller’s responsibility. In general, this should be
/// `drawInContext:withOptions:`.
- (void)drawBoundingBox:(CGContextRef)context;

/// Helps with drawing annotation content with opacity.
///
/// @note Acquiring the property lock is the caller’s responsibility. In general, this should be
/// `drawInContext:withOptions:`.
- (void)drawWithTransparencyLayerInContext:(nullable CGContextRef)context block:(void (^)(void))drawBlock;

/// Helper that will prepare the context for the border style.
///
/// If you relied on this method to apply line dashing to `context` please see `pathByDashingPathIfNecessary:`.
///
/// @note Acquiring the property lock is the caller’s responsibility. In general, this should be
/// `drawInContext:withOptions:`.
/// @see pathByDashingPathIfNecessary:
- (void)prepareBorderStyleInContext:(CGContextRef)context;

/// Helper to apply the current annotation's `lineDashArray` to `path`.
///
/// Use this method to get the final path you should draw in your annotations, do not rely on `prepareBorderStyleInContext:` to adjust the context's line dash style.
///
/// @return An autoreleased path.
/// @note Not all legitimate callers of this method are `PSPDFAnnotation` objects. As such this method
/// _does_ acquire the property lock.
- (CGPathRef)pathByDashingPathIfNecessary:(CGPathRef)path;

/// Optionally returns an unrounded bounding box rect (used to improve PSPDFResizableView accuracy).
///
/// @note Not all legitimate callers of this method are `PSPDFAnnotation` objects. As such this method
/// _does_ acquire the property lock.
- (CGRect)boundingBoxForPageRect:(CGRect)pageRect rounded:(BOOL)rounded;

/// Applies the correct filters for color inversion to the context.
///
/// @param context The context to apply the filters to.
/// @param boundingBox The box in which to apply the filters.
/// @param options The render options that define the filter options.PSPDFAnnotation.mm
- (void)applyMatchingFiltersToContext:(CGContextRef)context rect:(CGRect)boundingBox options:(nullable PSPDFRenderOptions *)options;

/// Can be overridden by annotation subclasses to return an annotation style that
/// better represents the on screen annotation appearance than `borderStyle`.
/// e.g., `PSPDFAnnotationBorderStyleNone` is essentially equal to
/// `PSPDFAnnotationBorderStyleSolid` for line annotations
@property (nonatomic, readonly) PSPDFAnnotationBorderStyle effectiveBorderStyle;

@end

#pragma mark - Helper

@interface PSPDFAnnotation (Helper)

- (NSComparisonResult)compareByPositionOnPage:(PSPDFAnnotation *)otherAnnotation;

/// Helper that queries the page rotation.
@property (nonatomic, readonly) PSPDFRotation pageRotation;

/// Draw border.
///
/// @note Acquiring the property lock is the caller’s responsibility. In general, this should be
/// `drawInContext:withOptions:`.
- (void)drawBorderInContext:(CGContextRef)context;

/// Draw appearance stream.
///
/// @return Whether the appearance stream has actually been drawn.
/// @note Acquiring the property lock is the caller’s responsibility. In general, this should be
/// `drawInContext:withOptions:`.
- (BOOL)drawAppearanceStreamInContext:(CGContextRef)context options:(nullable PSPDFRenderOptions *)options;

/// Checks if the annotation should be drawn with the specified options.
/// This will ensure that the annotation has not been deleted as well.
///
/// @param options The options dictionary passed in for drawing.
/// @return `true` if the receiver should be rendered, else `false`.
- (BOOL)shouldDrawWithOptions:(nullable PSPDFRenderOptions *)options;

/// Will be called after document and page have been set.
///
/// @note **Important:** This method is meant to be called **exactly once** in the lifetime of an
/// annotation! (During the initialization and setup phase after deserializing in an annotation
/// provider.)
/// All implementations will therefore assume that there cannot be any concurrent reads/writes to the
/// state of the annotation. In other words: No additional locking is attempted, nor should it be.
- (void)parse;

/// Will create PDF data from the drawingBlock.
+ (NSData *)createAppearanceStreamDataWithRect:(CGRect)boundingBox rotation:(PSPDFRotation)pageRotation drawingBlock:(void (^)(CGContextRef context))drawingBlock;

/// Converts annotations into other classes (e.g. highlight to underscore)
///
/// Tries to save as much properties as possible.
- (PSPDFAnnotation *)convertIntoAnnotationType:(PSPDFAnnotationType)annotationType;

/// Checks whether the supplied annotation can be copied to clipboard.
///
/// @return Returns YES if the document has permissions to extract content and the annotation is of NOT of the following kind: form element, ink signature, file and redaction
///
/// @note Please make sure to also check if the annotation type is supported in the current PSPDFConfiguration before copying it to the clipboard.
@property (nonatomic, readonly) BOOL supportsCopyToClipboard;

/// Clipboard operations need to run on the main thread.
- (instancetype)copyForClipboard;
- (void)didUnarchiveFromClipboard;

/// Helper that checks if the dash array is valid.
///
/// @see "The dash array’s elements shall be numbers that specify the lengths of alternating dashes and gaps; the numbers shall be nonnegative and not all zero". See PDF Reference §8.4.3.6 (Table 55).
///
/// @note a nil or missing (empty) dash array is considered valid.
@property (nonatomic, readonly) BOOL hasValidDashArray;

@end

#pragma mark - IndexWriting

@interface PSPDFAnnotation (IndexWriting)

@end

#pragma mark - WritingSupport

@interface PSPDFAnnotation (WritingSupport)

/// Can be set to NO to nil out any AP stream.
@property (nonatomic) BOOL hasAppearanceStream;

/// Some annotations may have a popupIndex. Defaults to -1.
@property (nonatomic) NSInteger popupIndex;

@end

/// Fonts
PSPDF_SDK_EXPORT NSString *const PSPDFAnnotationDefaultTextFontName;
PSPDF_SDK_EXPORT const NSUInteger PSPDFAnnotationDefaultFontSize;

#pragma mark - FontsPrivate

@interface PSPDFAnnotation (FontsPrivate)

/// Returns font attributes, factors in annotation color.
@property (nonatomic, copy, readonly) NSDictionary<NSString *, id> *fontAttributesWithColorAndFont;

@end

#pragma mark - AdvancedPrivate

@interface PSPDFAnnotation (AdvancedPrivate)

/// HACK. Processor uses this.
- (void)setDirtyWithoutChecks:(BOOL)dirty;

/// Defines the alignment of a fixed size annotation within its bounding box.
- (PSPDFRectAlignment)fixedSizeAlignmentForSize:(CGSize)size;

/// Adjust the bounding box so it is apporpriate for a fixed size annotation.
- (CGRect)fixedSizeBoundingBoxForBoundingBox:(CGRect)boundingBox;

/// Returns the adjusted `boundingBox` for fixed size annotations in the specified page environment.
/// Returns `boundingBox` for non-fixed size annotations.
- (CGRect)fixedSizeBoundingBoxWithPageInfo:(PSPDFPageInfo *)pageInfo pageBounds:(CGRect)bounds zoomLevel:(CGFloat)zoom;

/// The associated undo controller, unless object is initializing.
@property (nonatomic, readonly, nullable) PSPDFUndoController *undoController;

/// Returns the annotation type strings that are supported. Implemented in each subclass.
+ (NSArray<PSPDFAnnotationString> *)supportedTypes;

/// Doesn't reset the appearance stream when the dirty flag is set.
- (void)performBlockWithoutResettingAnnotationStream:(NS_NOESCAPE dispatch_block_t)block;

@end

#pragma mark - ImmutablePrivate

@interface PSPDFAnnotation (ImmutablePrivate)

/// startup
@property (nonatomic, getter=isInitializing, readonly) BOOL initializing;
- (void)startInitializing; // Used in XFDF parser
- (void)finishInitializing; // Used in XFDF parser
- (void)performInitializationBlock:(void (^)(void))block;

/// Sets the dirty flag, optionally without changing the modification date.
- (void)setDirty:(BOOL)dirty updateModificationDate:(BOOL)updateModificationDate;

/// Checks if the annotation is synced to the core already.
@property (nonatomic, getter=isSyncedToCore, readonly) BOOL syncedToCore;

@end

#pragma mark - Replies

@interface PSPDFAnnotation ()

/// Annotations on the same page that have the receiver set as their in-reply-to annotation. Ordered by date.
///
/// Returns an empty array and logs a warning if `Features.annotationReplies` is not enabled.
@property (nonatomic, readonly) NSArray<PSPDFAnnotation *> *directReplies;

/// Cached value. Use this instead of counting the elements in `directReplies`, as that can be quite expensive.
@property (atomic, readonly) BOOL hasReplies;

/// Returns annotations on the page that in reply to the receiver, and annotations that are in reply to those,
/// and so on until the end of the reply tree. Ordered by date.
/// Returns an empty array and logs a warning if `Features.annotationReplies` is not enabled.
///
/// @param replyType Determines which reply types should be included in the returned annotations.
/// @return The replies.
- (NSArray<PSPDFAnnotation *> *)flattenedRepliesForReplyType:(PSPDFAnnotationReplyType)replyType;

/// This is the same as flattenedRepliesForReplyType: but without license checks.
///
/// We need to be able to clean up, even if this feature is not licensed otherwise
/// deleting an annotation with replies leaves the document in a weird state.
///
/// @param replyType Determines which reply types should be included in the returned annotations.
/// @return The replies.
- (NSArray<PSPDFAnnotation *> *)annotationsForDeletionForReplyType:(PSPDFAnnotationReplyType)replyType;

/// A summary the information about the annotation’s review state. Exactly the info we want in our UI.
/// Returns nil and logs a warning if `Features.annotationReplies` is not enabled.
@property (nonatomic, readonly, nullable) id<PSPDFAnnotationReviewSummary> reviewSummary;

/// Adds a review state or marked state attached to this annotation, using the `defaultAnnotationUsername` from the document.
///
/// Does nothing and logs a warning if `Features.annotationReplies` is not enabled.
- (void)addAuthorState:(PSPDFAnnotationAuthorState)authorState;

@end

#pragma mark -  Accessibility

@interface PSPDFAnnotation ()

/// This is for the UI to attach a UIAccessibilityElement to the annotation.
/// The UI could also use associated objects or some other approach, but having a property here seemed neater.
@property (nonatomic) id accessibilityElementStorage;

@end

#pragma mark -

/// Helper to properly escape ASCII strings.
PSPDF_EXTERN NSString *PSPDFEscapedString(NSString *_Nullable string);

/// Returns the unified rect for all given annotations.
PSPDF_EXTERN CGRect PSPDFBoundingBoxForAnnotations(NSArray<PSPDFAnnotation *> *annotations);

/// Applies a maximum size that an annotation should be rendered at, to avoid excessive memory use.
PSPDF_EXTERN CGSize PSPDFAnnotationRenderSizeForSize(CGSize requestedSize, CGFloat scale);

/// Returns a set of classes that can be used as font attributes. Includes NSFont for Mac-Support.
PSPDF_EXTERN NSSet *PSPDFFontAttributeClassSet(void);

/// Send change notifications. Can be called from any thread. Sends on main thread.
PSPDF_SDK_EXPORT void PSPDFSendChangeNotificationForAnnotations(NSArray<PSPDFAnnotation *> *annotations, NSArray<NSString *> *_Nullable properties, NSDictionary *_Nullable options) NS_SWIFT_NAME(SendChangeNotification(annotations:properties:options:));
PSPDF_SDK_EXPORT void PSPDFSendChangeNotificationForAnnotation(PSPDFAnnotation *annotation, NSString *_Nullable property, NSDictionary *_Nullable options) NS_SWIFT_NAME(SendChangeNotification(annotation:property:options:));

/// Sends `PSPDFAnnotationBatchUpdatesWillBeginNotification` or `PSPDFAnnotationBatchUpdatesDidEndNotification`
/// (depending on `sendBegin`) for a set of annotations.
PSPDF_SDK_EXPORT void PSPDFSendBatchUpdatesNotificationForAnnotations(id<NSFastEnumeration> annotations, NSArray<NSString *> *_Nullable properties, BOOL sendBegin) NS_SWIFT_NAME(SendBatchUpdatesNotification(annotations:properties:sendBegin:));
/// Sends `PSPDFAnnotationBatchUpdatesWillBeginNotification` or `PSPDFAnnotationBatchUpdatesDidEndNotification`
/// (depending on `sendBegin`) for a single annotation.
PSPDF_SDK_EXPORT void PSPDFSendBatchUpdatesNotificationForAnnotation(PSPDFAnnotation *annotation, NSString *_Nullable property, BOOL sendBegin) NS_SWIFT_NAME(SendBatchUpdatesNotification(annotation:property:sendBegin:));

/// Filters Dictionaries of annotations via a block.
PSPDF_SDK_EXPORT NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *PSPDFFilteredAnnotationDictionaryWithBlock(NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *annotationDict, BOOL (^annotationFilterBlock)(PSPDFAnnotation *annotation)) NS_SWIFT_NAME(FilteredAnnotationDictionary(annotationDict:annotationFilterBlock:));

/// Filters Dictionaries of annotations via the type.
PSPDF_EXTERN NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *PSPDFFilterAnnotationDictionaryAllowingTypes(NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *annotationDict, PSPDFAnnotationType allowedAnnotationTypes) NS_SWIFT_NAME(FilterAnnotationDictionary(annotationDict:allowedAnnotationTypes:));

NS_ASSUME_NONNULL_END
