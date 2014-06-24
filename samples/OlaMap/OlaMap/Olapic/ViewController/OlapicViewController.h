//
//  OlapicViewController.h
//  OlaMap
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

#import <Foundation/Foundation.h>
#import <OlapicSDK/OlapicCustomerMediaList.h>
#import "OlapicMapObject.h"

@class OlapicCustomerMediaList;
@class OlapicAsyncImageView;
/**
 *  Show the map with the media as annotations
 */
@interface OlapicViewController : UIViewController <OlapicMediaListDelegate,OlapicMapObjectDelegate>{
    /**
     *  The loading indicator to show while the app is downloading the content
     */
    UIActivityIndicatorView *loader;
    /**
     *  A flag to know if its the first time the view controller calls
     *  the viewDidLoad method
     */
    BOOL firstLoad;
    /**
     *  The SDK object to handle media lists
     */
    OlapicCustomerMediaList *list;
    /**
     *  The map to show
     */
    OlapicMapObject *map;
}

@property (nonatomic,strong) UIActivityIndicatorView *loader;
@property (nonatomic) BOOL firstLoad;
@property (nonatomic,strong) OlapicCustomerMediaList *list;
@property (nonatomic,strong) OlapicMapObject *map;

@end