//
//  OlapicAsyncImageView.h
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
/**
 *  Its like a UIImageView that works with the SDK's
 *  media entities: It recieves an entity and it handles
 *  connection (to download the image) and resize (in
 *  case its needed).
 *  This object is used mostly for thumbnails. It has
 *  a special method to download the original image
 */
@interface OlapicAsyncImageView : UIView{
    /**
     *  The media entity from where the image comes
     */
    OlapicMediaEntity *media;
    /**
     *  The view it uses to show the media image
     */
    UIImageView *image;
    /**
     *  A loading indicator to show while it downloads
     *  the image
     */
    UIActivityIndicatorView *loader;
    /**
     *  A small 1px border that goes on top of the image
     *  (to give it a similar appearance to the Photos app)
     */
    UIView *border;
    /**
     *  The button, so the image can be interactive
     */
    UIButton *button;
    /**
     *  A fake overlay to show when the image is tapped
     */
    UIView *overlay;
    /**
     *  The callback for when the user touches the button
     */
    void (^callback)(OlapicAsyncImageView  *image);
    /**
     *  The original thumbnail downloaded (without resizes,
     *  so it mantains the size proportions to the original)
     */
    UIImage *thumbImage;
    /**
     *  The original image. It will be downloaded as a resource
     *  for the 'Zoom screen'
     */
    UIImage *fullImage;
}

@property (nonatomic,strong) OlapicMediaEntity *media;
@property (nonatomic,strong) UIImageView *image;
@property (nonatomic,strong) UIActivityIndicatorView *loader;
@property (nonatomic,strong) UIView *border;
@property (nonatomic,strong) UIButton *button;
@property (nonatomic,strong) UIView *overlay;
@property (nonatomic,strong) void (^callback)(OlapicAsyncImageView  *image);
@property (nonatomic,strong) UIImage *thumbImage;
@property (nonatomic,strong) UIImage *fullImage;
/**
 *  Class constructor
 *
 *  @param med  The media object from which this object will download the image
 *  @param call The callback action to be called when the user touches the button
 *  @param rect The image frame
 *
 *  @return An instance of this object (OlapicAsyncImageView)
 */
-(id)initWithMedia:(OlapicMediaEntity *)med callback:(void (^)(OlapicAsyncImageView *image))call andFrame:(CGRect)rect;
/**
 *  Tell the object to start downloading the thumbnail
 */
-(void)download;
/**
 *  Download the original image from the media object
 *
 *  @param call A callback action to be called when the image is ready (it will be accessible via the ivar fullImage).
 */
-(void)downloadFullImageAndDo:(void (^)(OlapicAsyncImageView *image))call;
/**
 *  Resize and crop an image proportionally
 *
 *  @param rimage The original image
 *  @param size   The size wanted
 *  @param retina If this is true and the image size allows it, it will double the 'size' parameter
 *
 *  @return The resized & cropped image
 */
+(UIImage *)resizeImage:(UIImage *)rimage to:(CGSize)size detectingRetina:(BOOL)retina;

@end