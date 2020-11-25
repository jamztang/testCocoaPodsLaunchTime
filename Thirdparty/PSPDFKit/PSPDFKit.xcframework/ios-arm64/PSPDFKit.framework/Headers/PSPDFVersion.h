//
//  Copyright © 2014-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

@interface PSPDFVersionDummy : NSObject
@end

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"

#if TARGET_OS_OSX

#define __PSPDFKIT_MACOS__
#define __PSPDFKIT_MACOS_1_0 10000
#define __PSPDFKIT_MACOS_1_1 10100
#define __PSPDFKIT_MACOS_1_2 10200
#define __PSPDFKIT_MACOS_2_0 20000
#define __PSPDFKIT_MACOS_2_1 20100
#define __PSPDFKIT_MACOS_2_2 20200
#define __PSPDFKIT_MACOS_2_3 20300
#define __PSPDFKIT_MACOS_2_4 20400
#define __PSPDFKIT_MACOS_2_5 20500
#define __PSPDFKIT_MACOS_2_6 20600
#define __PSPDFKIT_MACOS_2_7 20700
#define __PSPDFKIT_MACOS_3_0 30000
#define __PSPDFKIT_MACOS_3_1 30100
#define __PSPDFKIT_MACOS_3_2 30200
#define __PSPDFKIT_MACOS_3_3 30301
#define __PSPDFKIT_MACOS_3_4 30400
#define __PSPDFKIT_MACOS_3_5 30500
#define __PSPDFKIT_MACOS_4_0 40000
#define __PSPDFKIT_MACOS_4_1 40100
#define __PSPDFKIT_MACOS_4_2 40200
#define __PSPDFKIT_MACOS_4_3 40300
#define __PSPDFKIT_MACOS_4_4 40400
#define __PSPDFKIT_MACOS_4_5 40500

#else

#define __PSPDFKIT_IOS__
#define __PSPDFKIT_3_0 30000
#define __PSPDFKIT_3_1 30100
#define __PSPDFKIT_3_2 30200 // 3.2 is the last version supporting iOS 5.
#define __PSPDFKIT_3_3 30300
#define __PSPDFKIT_3_4 30400
#define __PSPDFKIT_3_5 30500
#define __PSPDFKIT_3_6 30600
#define __PSPDFKIT_3_7 30700 // 3.7 is the last version supporting iOS 6.
#define __PSPDFKIT_4_0 40000
#define __PSPDFKIT_4_1 40100
#define __PSPDFKIT_4_2 40200
#define __PSPDFKIT_4_3 40300
#define __PSPDFKIT_4_4 40400 // 4.4 is the last version supporting iOS 7.
#define __PSPDFKIT_5_0 50000
#define __PSPDFKIT_5_1 50100
#define __PSPDFKIT_5_2 50200
#define __PSPDFKIT_5_3 50300
#define __PSPDFKIT_5_4 50400
#define __PSPDFKIT_5_5 50500 // 5.5 is the last version supporting iOS 8.
#define __PSPDFKIT_6_0 60000
#define __PSPDFKIT_6_1 60100
#define __PSPDFKIT_6_2 60200
#define __PSPDFKIT_6_3 60300
#define __PSPDFKIT_6_4 60400
#define __PSPDFKIT_6_5 60500
#define __PSPDFKIT_6_6 60600
#define __PSPDFKIT_6_7 60700
#define __PSPDFKIT_6_8 60800
#define __PSPDFKIT_6_9 60900
#define __PSPDFKIT_7_0 70000
#define __PSPDFKIT_7_1 70100
#define __PSPDFKIT_7_2 70200
#define __PSPDFKIT_7_3 70300
#define __PSPDFKIT_7_4 70400
#define __PSPDFKIT_7_5 70500 // 7.5 is the last version supporting iOS 9.
#define __PSPDFKIT_7_6 70600
#define __PSPDFKIT_7_7 70700
#define __PSPDFKIT_8_0 80000
#define __PSPDFKIT_8_1 80100
#define __PSPDFKIT_8_2 80200 // 8.2 is the last version supporting iOS 10.
#define __PSPDFKIT_8_3 80300
#define __PSPDFKIT_8_4 80400
#define __PSPDFKIT_8_5 80500
#define __PSPDFKIT_9_0 90000
#define __PSPDFKIT_9_1 90100
#define __PSPDFKIT_9_2 90200
#define __PSPDFKIT_9_3 90300
#define __PSPDFKIT_9_4 90400 // 9.4 is the last version supporting iOS 11.
#define __PSPDFKIT_9_5 90500
#define __PSPDFKIT_10_0 100000
#define __PSPDFKIT_10_1 100100

#endif

#pragma clang diagnostic pop
