//
//  Copyright © 2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#else
#import "PSPDFEnvironment.h"
#import "PSPDFOverridable.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// Provides information about overrides of `PSPDFOverridable` classes.
@protocol PSPDFOverrideProvider<NSObject>

@required

/// Might return `originalClass` or its subclass. **Must not** return `Nil`.
- (Class)classForClass:(Class<PSPDFOverridable>)originalClass;

@end

NS_ASSUME_NONNULL_END
