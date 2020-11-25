//
//  Copyright © 2013-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFAnnotationGridViewController.h>
#import <PSPDFKitUI/PSPDFStyleable.h>

@class PSPDFAnnotationSet;

NS_ASSUME_NONNULL_BEGIN

/// Protocol for the annotation store implementation.
PSPDF_PROTOCOL_SWIFT(AnnotationSetStore)
@protocol PSPDFAnnotationSetStore<NSObject>

/// The annotation set to read/write.
@property (nonatomic, copy) NSArray<PSPDFAnnotationSet *> *annotationSets;

@end

/// A default store that saves annotations into the keychain.
PSPDF_CLASS_SWIFT(KeychainAnnotationSetsStore)
@interface PSPDFKeychainAnnotationSetsStore : NSObject<PSPDFAnnotationSetStore>
@end

/// Shows an editable grid of saved annotation sets.
///
/// Allows saving/loading of stored annotations.
/// Annotations are stored securely in the Keychain.
PSPDF_CLASS_SWIFT(SavedAnnotationsViewController)
@interface PSPDFSavedAnnotationsViewController : PSPDFAnnotationGridViewController<PSPDFAnnotationGridViewControllerDataSource, PSPDFStyleable, PSPDFOverridable>

/// The default `PSPDFKeychainAnnotationSetsStore`, used if no custom store is set.
@property(class, atomic, readonly) id<PSPDFAnnotationSetStore> sharedAnnotationStore NS_SWIFT_NAME(shared);

/// The store object that gets called when annotations are changed. Set to use the controller.
@property (nonatomic) id<PSPDFAnnotationSetStore> annotationStore;

@end

NS_ASSUME_NONNULL_END
