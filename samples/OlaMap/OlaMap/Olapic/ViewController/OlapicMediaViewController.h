//
//  OlapicMediaViewController.h
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
#import <OlapicSDK/OlapicSDK.h>
#import "OlapicAsyncImageView.h"
#import "OlapicUploaderView.h"
/**
 *  Show a single media entity in detail, with a zoom
 *  controller and the information about its uploader
 */
@interface OlapicMediaViewController : UIViewController <UIScrollViewDelegate,UIGestureRecognizerDelegate>{
    /**
     *  A reference to the thumbnail from which this
     *  screen is loaded
     */
    OlapicAsyncImageView *__weak mimage;
    /**
     *  The image object for the zoom
     */
    UIImageView *image;
    /**
     *  The zoom controller
     */
    UIScrollView *zoomView;
    /**
     *  A flag to know if its the first time the view controller calls
     *  the viewDidLoad method
     */
    BOOL firstLoad;
    /**
     *  A container for the 'detail view' (the information about the uploader)
     */
    UIView *uploaderView;
    /**
     *  The small blue rectange on the edge of the screen that indicates that
     *  you can drag the uploader detail view
     */
    UIView *uploaderArrow;
    /**
     *  The blue line on the edge of the screen
     */
    UIView *uploaderArrowLine;
    /**
     *  A flag to know if the uploader detail view is open
     */
    BOOL uploaderViewOpen;
    /**
     *  The real object with the uploader detail
     */
    OlapicUploaderView *detail;
}

@property (nonatomic,weak) OlapicAsyncImageView *__weak mimage;
@property (nonatomic,strong) UIImageView *image;
@property (nonatomic,strong) UIScrollView *zoomView;
@property (nonatomic) BOOL firstLoad;
@property (nonatomic,strong) UIView *uploaderView;
@property (nonatomic,strong) UIView *uploaderArrow;
@property (nonatomic,strong) UIView *uploaderArrowLine;
@property (nonatomic) BOOL uploaderViewOpen;
@property (nonatomic,strong) OlapicUploaderView *detail;

/**
 *  Class constructor
 *
 *  @param img The thumbnail that called this screen
 *
 *  @return An instance of this object (OlapicMediaViewController)
 */
-(id)initWithImage:(OlapicAsyncImageView *__weak)img;

@end
