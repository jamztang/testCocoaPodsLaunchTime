//
//  Copyright © 2015-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

@interface NSURL (PSPDFFileHelper)

/// Checks if a file NSURL refers to a directory.
@property (nonatomic, readonly) BOOL pspdf_refersToDirectory;

@end
