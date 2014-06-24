//
//  OlapicUploaderView.h
//  OlaBasicGallery
//  https://github.com/Olapic/Olapic-SDK-iOS
//
//  Documentation
//  http://docs.photorank.me/ios
//
//  Created by The Olapic Team on 5/16/14.
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

/**
 *  This is the detail view, where the user will be able to
 *  see the media uploader and share it on social networks
 */
@interface OlapicUploaderView : UIView <UITextViewDelegate>{
    /**
     *  The media object from where this object will get the details
     */
    OlapicMediaEntity *__weak media;
    /**
     *  The object for the media uploader
     */
    OlapicUploaderEntity *__weak uploader;
    /**
     *  A reference to the media image, so it can be shared using the
     *  Social Framework
     */
    UIImageView *__weak image;
    /**
     *  A reference to the view controller that its including this detail.
     *  It will be used to open the Social Framework modal
     */
    UIViewController *__weak mainViewController;
    /**
     *  A simple view container for the basic UI elements of this object
     *  (avatar, name, source, etc.). This will be hidden until the app
     *  finishes downloading the uploader information
     */
    UIView *container;
    /**
     *  The label to show the uploader name
     */
    UILabel *lblName;
    /**
     *  The label to show the media source (twitter, instagram, facebook, etc.)
     */
    UILabel *lblSource;
    /**
     *  A text area to show the media caption
     */
    UITextView *txtCaption;
    /**
     *  The uploader avatar
     */
    UIImageView *imgAvatar;
    /**
     *  The button to share the media (using the Social Framework)
     */
    UIButton *share;
    /**
     *  The loading indicator for when the app is requesting the uploader
     *  information
     */
    UIActivityIndicatorView *loader;
}

@property (nonatomic,weak) OlapicMediaEntity *__weak media;
@property (nonatomic,weak) OlapicUploaderEntity *__weak uploader;
@property (nonatomic,weak) UIImageView *__weak image;
@property (nonatomic,weak) UIViewController *__weak mainViewController;
@property (nonatomic,strong) UIView *container;
@property (nonatomic,strong) UILabel *lblName;
@property (nonatomic,strong) UILabel *lblSource;
@property (nonatomic,strong) UITextView *txtCaption;
@property (nonatomic,strong) UIImageView *imgAvatar;
@property (nonatomic,strong) UIActivityIndicatorView *loader;
@property (nonatomic,strong) UIButton *share;
/**
 *  The class constructor
 *
 *  @param frame The size for this object
 *  @param med   The media object for which this object will show the detail
 *
 *  @return An instace of this object (OlapicUploaderView)
 */
-(id)initWithFrame:(CGRect)frame andMedia:(OlapicMediaEntity *__weak)med;
/**
 *  Show/Hide the view shadows
 *
 *  @param show YES to show them and NO to hide them
 */
-(void)showShadow:(BOOL)show;
/**
 *  Open the Social Framework modal
 */
-(void)openShareWindow;

@end