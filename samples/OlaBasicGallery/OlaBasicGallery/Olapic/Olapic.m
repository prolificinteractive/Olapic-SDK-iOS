//
//  Olapic.m
//  OlaBasicGallery
//  https://github.com/Olapic/Olapic-SDK-iOS
//
//  Documentation
//  http://docs.photorank.me/ios
//
//  Created by The Olapic Team on 5/12/14.
//  Copyright (c) 2014 Olapic, Inc. All rights reserved.
//  https://olapic.com
//
//  The MIT License (MIT)
//  
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in
//  the Software without restriction, including without limitation the rights to
//  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
//  the Software, and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#import "Olapic.h"
#import "NavigationController/OlapicNavigationController.h"
#import "ViewController/OlapicViewController.h"

@implementation Olapic
@synthesize navigation,gallery;
/**
 *  Start the sample and return the navigation controller,
 *  so the UIApplication can set it as rootViewController
 *
 *  @return The navigation controller for the sample
 */
-(UINavigationController *)startSample{
    gallery = [[OlapicViewController alloc] init];
    navigation = [[OlapicNavigationController alloc] initWithRootViewController:gallery];
    
    [[UINavigationBar appearance] setBarTintColor:[UIColor colorWithRed:0.29f green:0.34f blue:0.45f alpha:1.00f]];
    [[UINavigationBar appearance] setTitleTextAttributes:[NSDictionary dictionaryWithObjectsAndKeys:[UIColor whiteColor], NSForegroundColorAttributeName, nil]];
    [[UINavigationBar appearance] setTintColor:[UIColor colorWithRed:0.60f green:0.75f blue:1.00f alpha:1.00f]];
    
    return navigation;
}

@end