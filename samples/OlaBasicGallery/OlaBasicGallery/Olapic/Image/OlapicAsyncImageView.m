//
//  OlapicAsyncImageView.m
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

#import "OlapicAsyncImageView.h"

@interface OlapicAsyncImageView()
/**
 *  This method is called every time the size of the view changes, and it
 *  adjust the size and position of the elements accordingly
 */
-(void)adjustSize;
/**
 *  Show the fake overlay when the button is pressed down
 */
-(void)buttonOnTouchDown;
/**
 *  Hide the fake overlay and call the button action
 */
-(void)buttonAction;

@end

@implementation OlapicAsyncImageView
@synthesize media,image,loader,border,button,overlay,callback,fullImage,thumbImage;
/**
 *  Class constructor
 *
 *  @param med  The media object from which this object will download the image
 *  @param call The callback action to be called when the user touches the button
 *  @param rect The image frame
 *
 *  @return An instance of this object (OlapicAsyncImageView)
 */
-(id)initWithMedia:(OlapicMediaEntity *)med callback:(void (^)(OlapicAsyncImageView *image))call andFrame:(CGRect)rect{
    self = [super initWithFrame:rect];
    if(self){
        self.backgroundColor = [UIColor clearColor];
        media = med;
        callback = call;
        
        image = [[UIImageView alloc] initWithFrame:CGRectZero];
        image.backgroundColor = [UIColor clearColor];
        [self addSubview:image];
        
        loader = [[UIActivityIndicatorView alloc] initWithFrame:CGRectZero];
        loader.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        [self addSubview:loader];
        
        border = [[UIView alloc] initWithFrame:CGRectZero];
        border.layer.borderColor = [UIColor colorWithWhite:120.0/255.0 alpha:0.20].CGColor;
        border.layer.borderWidth = 1.0f;
        [self addSubview:border];
        
        button = [[UIButton alloc] initWithFrame:CGRectZero];
        [button addTarget:self action:@selector(buttonAction) forControlEvents:UIControlEventTouchUpInside];
        [button addTarget:self action:@selector(buttonOnTouchDown) forControlEvents:UIControlEventTouchDown];
        [self addSubview:button];
        
        overlay = [[UIView alloc] initWithFrame:CGRectZero];
        overlay.backgroundColor = [UIColor colorWithWhite:0.0/255.0 alpha:0.20];
        overlay.alpha = 0;
        [self addSubview:overlay];
        
        [self adjustSize];
    }
    return self;
}
/**
 *  Tell the object to start downloading the thumbnail
 */
-(void)download{
    [loader startAnimating];
    [[[OlapicSDK sharedOlapicSDK] media] loadImageWithSize:OlapicMediaImageSizeThumbnail fromMedia:media onSuccess:^(NSData *mediaData, UIImage *mediaImage){
        thumbImage = mediaImage;
        image.image = [OlapicAsyncImageView resizeImage:mediaImage to:CGSizeMake(self.frame.size.width,self.frame.size.height) detectingRetina:YES];
        [loader stopAnimating];
        [self adjustSize];
    } onFailure:^(NSError *error){
        [loader stopAnimating];
        self.backgroundColor = [UIColor redColor];
    }];
}
/**
 *  This method is called every time the size of the view changes, and it
 *  adjust the size and position of the elements accordingly
 */
-(void)adjustSize{
    CGRect zero =  CGRectMake(0, 0, self.frame.size.width, self.frame.size.height);
    image.frame = zero;
    loader.frame = CGRectMake((self.frame.size.width / 2)-10, (self.frame.size.height / 2) - 10, 20, 20);
    border.frame = zero;
    button.frame = zero;
    overlay.frame = zero;
}
/**
 *  Show the fake overlay when the button is pressed down
 */
-(void)buttonOnTouchDown{
    overlay.alpha = 1;
}
/**
 *  Hide the fake overlay and call the button action
 */
-(void)buttonAction{
    overlay.alpha = 0;
    if(callback) callback(self);
}
/**
 *  Download the original image from the media object
 *
 *  @param call A callback action to be called when the image is ready (it will be accessible via the ivar fullImage).
 */
-(void)downloadFullImageAndDo:(void (^)(OlapicAsyncImageView *image))call{
    OlapicSDK *olapic = [OlapicSDK sharedOlapicSDK];
    [[olapic media] loadImageWithSize:OlapicMediaImageSizeOriginal fromMedia:media onSuccess:^(NSData *mediaData, UIImage *mediaImage){
        fullImage = mediaImage;
        if(call) call(self);
    } onFailure:^(NSError *error){
    
    }];
}
/**
 *  Resize and crop an image proportionally
 *
 *  @param rimage The original image
 *  @param size   The size wanted
 *  @param retina If this is true and the image size allows it, it will double the 'size' parameter
 *
 *  @return The resized & cropped image
 */
+(UIImage *)resizeImage:(UIImage *)rimage to:(CGSize)size detectingRetina:(BOOL)retina{
    float currentScale = 1.0;
    BOOL _retinaScreen = [UIScreen mainScreen].scale == 2.0;
    if(retina && _retinaScreen && (rimage.size.width >= (size.width*2) && rimage.size.height >= (size.height*2))){
        size = CGSizeMake(size.width*2, size.height*2);
    }
    if (rimage.size.width > size.width || rimage.size.height > size.height){
        if (!((currentScale = (size.width / rimage.size.width)) > (size.height / rimage.size.height))){
            currentScale = (size.height / rimage.size.height);
        }
    }
    UIGraphicsBeginImageContextWithOptions(size, NO, [UIScreen mainScreen].scale);
    CGRect rect = CGRectMake(floor((size.width - rimage.size.width * currentScale) / 2),
                             floor((size.height -  rimage.size.height * currentScale) / 2),
                             floor(rimage.size.width * currentScale), floor(rimage.size.height * currentScale));
    [rimage drawInRect:rect];
    UIImage *result = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return result;
}
#pragma mark - Default cycle
/**
 *  Overwrite the default UIView setFrame method in
 *  order to call the adjustSize method every time
 *  the view's frame changes
 *
 *  @param frame The new size for the view
 */
-(void)setFrame:(CGRect)frame{
    [super setFrame:frame];
    [self adjustSize];
}
/**
 *  Overwrite the default UIView drawRect method in
 *  order to call the adjustSize method every time
 *  the view's frame changes
 *
 *  @param rect The size where the view will be drawn
 */
-(void)drawRect:(CGRect)rect{
    [super drawRect:rect];
    [self adjustSize];
}

@end