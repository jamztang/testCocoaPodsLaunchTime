//
//  AppDelegate.swift
//  testCocoaPodsLaunchTime
//
//  Created by James Tang on 25/11/2020.
//

import UIKit

#if canImport(PSPDFKit)
import PSPDFKit
#endif
#if canImport(AppCenter)
import AppCenter
#endif

@main
class AppDelegate: UIResponder, UIApplicationDelegate {


    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.

        var frameworks: [String] = []
        #if canImport(PSPDFKit)
        frameworks.append("PSPDFKit")
        #endif

        #if canImport(AppCenter)
        frameworks.append("AppCenter")
        #endif

        Swift.print("TTT print \(Date()) loaded frameworks: \(frameworks)")
        return true
    }

    // MARK: UISceneSession Lifecycle

    func application(_ application: UIApplication, configurationForConnecting connectingSceneSession: UISceneSession, options: UIScene.ConnectionOptions) -> UISceneConfiguration {
        // Called when a new scene session is being created.
        // Use this method to select a configuration to create the new scene with.
        return UISceneConfiguration(name: "Default Configuration", sessionRole: connectingSceneSession.role)
    }

    func application(_ application: UIApplication, didDiscardSceneSessions sceneSessions: Set<UISceneSession>) {
        // Called when the user discards a scene session.
        // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
        // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
    }


}

