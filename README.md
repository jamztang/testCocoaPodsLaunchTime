Testing App Launch Time with or without CocoaPods
---

tldr; Basically there's no affect on launch time when using CocoaPods or intergrate manually using Frameworks

Gotcha: AppCenter 4.0.0 don't work on Mac Catalyst, .podspec was not specifying .xcframework

No Pods at all:
```
Total pre-main time: 134.65 milliseconds (100.0%)
         dylib loading time: 153.07 milliseconds (113.6%)
        rebase/binding time: 126687488.9 seconds (385169234.4%)
            ObjC setup time:   7.82 milliseconds (5.8%)
           initializer time:  25.36 milliseconds (18.8%)
           slowest intializers :
             libSystem.B.dylib :   2.15 milliseconds (1.5%)
   libBacktraceRecording.dylib :   3.89 milliseconds (2.8%)
    libMainThreadChecker.dylib :  15.91 milliseconds (11.8%)

TTT print 2020-11-25 04:06:31 +0000 loaded frameworks: []
```

With Frameworks:
```
Total pre-main time: 305.14 milliseconds (100.0%)
         dylib loading time: 194.33 milliseconds (63.6%)
        rebase/binding time:  10.43 milliseconds (3.4%)
            ObjC setup time:  21.21 milliseconds (6.9%)
           initializer time:  79.16 milliseconds (25.9%)
           slowest intializers :
             libSystem.B.dylib :   3.02 milliseconds (0.9%)
    libMainThreadChecker.dylib :  23.04 milliseconds (7.5%)
                      PSPDFKit :   7.15 milliseconds (2.3%)
                    PSPDFKitUI :  74.13 milliseconds (24.2%)

TTT print 2020-11-25 04:10:34 +0000 loaded frameworks: ["PSPDFKit", "PSPDFKitUI", "AppCenter"]
```

With CocoaPods:
```
Total pre-main time: 313.02 milliseconds (100.0%)
         dylib loading time: 187.80 milliseconds (59.9%)
        rebase/binding time:  12.36 milliseconds (3.9%)
            ObjC setup time:  21.67 milliseconds (6.9%)
           initializer time:  91.18 milliseconds (29.1%)
           slowest intializers :
             libSystem.B.dylib :   2.87 milliseconds (0.9%)
    libMainThreadChecker.dylib :  28.81 milliseconds (9.2%)
                      PSPDFKit :   7.18 milliseconds (2.2%)
                    PSPDFKitUI :  79.09 milliseconds (25.2%)

TTT print 2020-11-25 04:11:44 +0000 loaded frameworks: ["PSPDFKit", "PSPDFKitUI", "AppCenter"]
```
