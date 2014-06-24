//
//  OlapicMediaViewController.m
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

#define kUploaderWidth 250

#import <QuartzCore/QuartzCore.h>
#import "OlapicMediaViewController.h"

@interface OlapicMediaViewController()
/**
 *  Adjust the size and position of the elements accordingly, using
 *  the controller view size as reference
 */
-(void)readjustSize;
/**
 *  Adjust the size and position of the elements accordingly, using
 *  a given size as reference.
 *  This method not always use the controller view size because its
 *  also called when the orientation its going to change, so the
 *  animation for the roation won't break
 *
 *  @param size The size to use as reference
 */
-(void)readjustSize:(CGSize)size;
/**
 *  Reset the zoom scale
 */
-(void)resetZoom;
/**
 *  Center the zoom image inside the scroll view
 *
 *  @param scroll The scroll view where the image will be centered
 *  @param rView  The image to center
 *
 *  @return The new frame for the image
 */
-(CGRect)centeredFrameForScrollView:(UIScrollView *)scroll andUIView:(UIView *)rView;
/**
 *  Start downloading the full image.
 *  When it first loads, the image will have the thumbnail quality, but as
 *  soon as the full image is downloaded, it will replace it.
 */
-(void)loadFullImage;
/**
 *  Resize the image proportionally
 */
-(void)resizeAndCenter;
/**
 *  Recognize the swipe from the right edge in order to show the uploader
 *  detail view
 *
 *  @param gesture The swipe gesture
 */
-(void)handleSwipeRight:(UIScreenEdgePanGestureRecognizer*)gesture;
/**
 *  Recognize the swipe from left to right used to hide the uploader
 *  detail view
 *
 *  @param gesture The swipe gesture
 */
-(void)handleSwipeLeft:(UIScreenEdgePanGestureRecognizer*)gesture;
/**
 *  Move the uploader detail view to a new position and show its shadows
 *
 *  @param x The new X position
 */
-(void)moveUploaderViewX:(CGFloat)x;
/**
 *  Check the position of the uploader detail view and change the value
 *  of the uploaderViewOpen flag
 */
-(void)checkUploaderView;
/**
 *  Reset the position of the uploader detail view. It will use the
 *  uploaderViewOpen flag to determine if it should reset to an open
 *  position or not. This method will use the current controller view
 *  size as reference
 */
-(void)resetUploaderViewPosition;
/**
 *  Reset the position of the uploader detail view, using a given
 *  size as reference
 *
 *  @param size The size to use as reference
 */
-(void)resetUploaderViewPosition:(CGSize)size;

-(void)toggleDetail;

@end

@implementation OlapicMediaViewController
@synthesize mimage,image,zoomView,firstLoad,uploaderView,uploaderViewOpen,detail,uploaderArrow,uploaderArrowLine;
/**
 *  Class constructor
 *
 *  @param img The thumbnail that called this screen
 *
 *  @return An instance of this object (OlapicMediaViewController)
 */
-(id)initWithImage:(OlapicAsyncImageView *__weak)img{
    self = [super init];
    if(self){
        mimage = img;
        zoomView = [[UIScrollView alloc] initWithFrame:CGRectZero];
        uploaderView = [[UIView alloc] initWithFrame:CGRectZero];
        uploaderView.backgroundColor = [UIColor clearColor];
        uploaderArrow = [[UIView alloc] initWithFrame:CGRectZero];
        uploaderArrow.backgroundColor = [UIColor colorWithRed:0.44f green:0.49f blue:0.58f alpha:1.00f];
        uploaderArrowLine = [[UIView alloc] initWithFrame:CGRectZero];
        uploaderArrowLine.backgroundColor = [UIColor colorWithRed:0.44f green:0.49f blue:0.58f alpha:1.00f];
        detail = [[OlapicUploaderView alloc] initWithFrame:CGRectZero andMedia:[mimage media]];
        detail.mainViewController = self;
        [uploaderView addSubview:detail];
        [uploaderView addSubview:uploaderArrow];
        [uploaderView addSubview:uploaderArrowLine];
        [zoomView setDelegate:self];
        [zoomView setMaximumZoomScale:4.0];
        [zoomView setBouncesZoom:YES];
        [zoomView setShowsHorizontalScrollIndicator:NO];
        [zoomView setShowsVerticalScrollIndicator:NO];
        [zoomView setUserInteractionEnabled:NO];
        [self.view addSubview:zoomView];
        [self.view addSubview:uploaderView];
        firstLoad = NO;
    }
    return self;
}
/**
 *  If this is the first time this method is called, it will
 *  show the image and set the gestures
 */
-(void)viewDidLoad{
    [super viewDidLoad];
    if(!firstLoad){
        firstLoad = YES;
        // Adjust the position and size of the UI elements
        [self readjustSize];
        // Some customization for the VC
        self.view.backgroundColor = [UIColor whiteColor];
        self.title = @"Image";
        // Add the button on the navigation bar
        UIBarButtonItem *detailBtn = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"dots.png"] style:UIBarButtonItemStyleBordered target:self action:@selector(toggleDetail)];
        self.navigationItem.rightBarButtonItem = detailBtn;
        // Show the image and center it
        image = [[UIImageView alloc] initWithImage:mimage.thumbImage];
        if(mimage.media.originalSize.width > 0){
            [self resizeAndCenter];
        }
        [zoomView addSubview:image];
        image.contentMode = UIViewContentModeScaleAspectFit;
        // Set the uploader detail view
        uploaderView.frame = CGRectMake(self.view.frame.size.width, 0, kUploaderWidth, self.view.frame.size.height);
        // Start downloading the full image
        [self loadFullImage];
        // Set the gestures
        // - The swipe from the right edge to show the uploader detail view
        UIScreenEdgePanGestureRecognizer *swipeRight = [[UIScreenEdgePanGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeRight:)];
        [swipeRight setEdges:UIRectEdgeRight];
        [swipeRight setDelegate:self];
        [self.view addGestureRecognizer:swipeRight];
        [zoomView addGestureRecognizer:swipeRight];
        // - The swipe from left to right, to hide the uploader detail view
        UISwipeGestureRecognizer *swipeLeft = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeLeft:)];
        [swipeLeft setDirection:UISwipeGestureRecognizerDirectionRight];
        [swipeLeft setDelegate:self];
        [uploaderView addGestureRecognizer:swipeLeft];
        // - Anothe swipe from left to do the same, because using the same gesture object wasn't working
        UISwipeGestureRecognizer *zswipeLeft = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeLeft:)];
        [zswipeLeft setDirection:UISwipeGestureRecognizerDirectionRight];
        [zswipeLeft setDelegate:self];
        [zoomView addGestureRecognizer:zswipeLeft];
    }
    [self readjustSize];
}
/**
 *  Recognize the swipe from the right edge in order to show the uploader
 *  detail view
 *
 *  @param gesture The swipe gesture
 */
-(void)handleSwipeRight:(UIScreenEdgePanGestureRecognizer*)gesture{
    if(uploaderViewOpen) return;
    CGPoint translation = [gesture translationInView:self.view];
    CGFloat xValue = abs(translation.x);
    CGFloat width = self.view.frame.size.width;
    CGFloat newX = round(width - xValue);
    if(gesture.state == UIGestureRecognizerStateCancelled || gesture.state == UIGestureRecognizerStateEnded){
        BOOL shouldOpen = (width - newX) > (uploaderView.frame.size.width / 3);
        newX = shouldOpen ? (width - uploaderView.frame.size.width) : width;
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationDuration:0.25];
        [UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
        [UIView setAnimationDelegate:self];
        [UIView setAnimationDidStopSelector:@selector(checkUploaderView)];
        [self moveUploaderViewX:newX];
        [UIView commitAnimations];
    }else{
        if(xValue > uploaderView.frame.size.width){
            return;
        }
        [self moveUploaderViewX:newX];
        [self checkUploaderView];
    }
}
/**
 *  Recognize the swipe from left to right used to hide the uploader
 *  detail view
 *
 *  @param gesture The swipe gesture
 */
-(void)handleSwipeLeft:(UIScreenEdgePanGestureRecognizer*)gesture{
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.25];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
    [UIView setAnimationDelegate:self];
    [UIView setAnimationDidStopSelector:@selector(checkUploaderView)];
    [self moveUploaderViewX:self.view.frame.size.width];
    [UIView commitAnimations];
    
}
/**
 *  Move the uploader detail view to a new position and show its shadows
 *
 *  @param x The new X position
 */
-(void)moveUploaderViewX:(CGFloat)x{
    uploaderView.frame = CGRectMake(x, 0, uploaderView.frame.size.width, uploaderView.frame.size.height);
    [detail showShadow:YES];
}
/**
 *  Check the position of the uploader detail view and change the value
 *  of the uploaderViewOpen flag
 */
-(void)checkUploaderView{
    uploaderViewOpen = self.view.frame.size.width - uploaderView.frame.origin.x >= uploaderView.frame.size.width;
    if(!uploaderViewOpen){
        [detail showShadow:NO];
    }
}
/**
 *  Reset the position of the uploader detail view. It will use the
 *  uploaderViewOpen flag to determine if it should reset to an open
 *  position or not. This method will use the current controller view
 *  size as reference
 */
-(void)resetUploaderViewPosition{
    [self resetUploaderViewPosition:self.view.frame.size];
}
/**
 *  Reset the position of the uploader detail view, using a given
 *  size as reference
 *
 *  @param size The size to use as reference
 */
-(void)resetUploaderViewPosition:(CGSize)size{
    CGFloat uploaderX = uploaderViewOpen ? size.width - kUploaderWidth : size.width;
    uploaderView.frame = CGRectMake(uploaderX, 0, kUploaderWidth, self.view.frame.size.height);
}
/**
 *  Resize the image proportionally
 */
-(void)resizeAndCenter{
    CGSize size = mimage.media.originalSize;
	CGSize oboundsSize = zoomView.bounds.size;
    CGSize boundsSize = CGSizeMake(oboundsSize.width, oboundsSize.height - (UIInterfaceOrientationIsPortrait(self.interfaceOrientation) ? 64 : 54));
    float newWidth = size.width;
    float newHeight = size.height;
    if(size.width/size.height > boundsSize.width/boundsSize.height && size.width > boundsSize.width){
        newWidth = boundsSize.width;
        newHeight = boundsSize.width/size.width * size.height;
    }else if(size.height > boundsSize.height){
        newWidth = boundsSize.height/size.height * size.width;
        newHeight = boundsSize.height;
    }
    image.frame = CGRectMake(0, 0, newWidth, newHeight);
}
/**
 *  Adjust the size and position of the elements accordingly, using
 *  the controller view size as reference
 */
-(void)readjustSize{
    [self readjustSize:self.view.frame.size];
}
/**
 *  Adjust the size and position of the elements accordingly, using
 *  a given size as reference.
 *  This method not always use the controller view size because its
 *  also called when the orientation its going to change, so the
 *  animation for the roation won't break
 *
 *  @param size The size to use as reference
 */
-(void)readjustSize:(CGSize)size{
    CGFloat navHeigth = (size.width < size.height ? 64 : 50);
    zoomView.frame = CGRectMake(0, 0, size.width, size.height);
    image.frame = [self centeredFrameForScrollView:zoomView andUIView:image];
    uploaderView.frame = CGRectMake(uploaderView.frame.origin.x, 0, kUploaderWidth, size.height);
    detail.frame = CGRectMake(0, navHeigth, kUploaderWidth, size.height-navHeigth);
    uploaderArrowLine.frame = CGRectMake(-2, 0, 2, size.height);
    uploaderArrow.frame = CGRectMake(-5, ((size.height/2)-10)+(navHeigth/2), 5, 20);
}
/**
 *  Reset the zoom scale
 */
-(void)resetZoom{
    if(self.view.frame.size.width < 1) return;
    CGSize theSize = [mimage.fullImage size];
    CGSize screenSize = zoomView.frame.size;
    CGFloat widthRatio = screenSize.width / theSize.width;
    CGFloat heightRatio = screenSize.height / theSize.height;
    CGFloat initialZoom = (widthRatio > heightRatio) ? heightRatio : widthRatio;
    CGFloat currentZoom = zoomView.zoomScale;
    [zoomView setMinimumZoomScale:MAX(1.0,initialZoom)];
    if(currentZoom < 1.1){
        [zoomView setZoomScale:MAX(1.0,initialZoom)];
        [self resizeAndCenter];
    }
    image.frame = [self centeredFrameForScrollView:zoomView andUIView:image];
    zoomView.contentSize = image.frame.size;
}
/**
 *  Center the zoom image inside the scroll view
 *
 *  @param scroll The scroll view where the image will be centered
 *  @param rView  The image to center
 *
 *  @return The new frame for the image
 */
-(CGRect)centeredFrameForScrollView:(UIScrollView *)scroll andUIView:(UIView *)rView{
	CGSize oboundsSize = scroll.bounds.size;
    CGSize boundsSize = CGSizeMake(oboundsSize.width, oboundsSize.height - 64);
    CGRect frameToCenter = rView.frame;
    if(frameToCenter.size.width < boundsSize.width) {
        frameToCenter.origin.x = ((boundsSize.width - frameToCenter.size.width) / 2);
    }else{
        frameToCenter.origin.x = 0;
    }
    if(frameToCenter.size.height < boundsSize.height){
        frameToCenter.origin.y = ((boundsSize.height - frameToCenter.size.height) / 2);
    }else{
        frameToCenter.origin.y = 0;
    }
	return frameToCenter;
}
/**
 *  Start downloading the full image.
 *  When it first loads, the image will have the thumbnail quality, but as
 *  soon as the full image is downloaded, it will replace it.
 */
-(void)loadFullImage{
    [mimage downloadFullImageAndDo:^(OlapicAsyncImageView *imageo){
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationDuration:0.30];
        [UIView setAnimationDelegate:self];
        image.image = imageo.fullImage;
        image.frame = [self centeredFrameForScrollView:zoomView andUIView:image];
        image.contentMode = UIViewContentModeScaleAspectFill;
        [UIView commitAnimations];
        [zoomView setUserInteractionEnabled:YES];
        detail.image = image;
        [self performSelector:@selector(resetZoom) withObject:nil afterDelay:0.30];
    }];
}

-(void)toggleDetail{
    uploaderViewOpen = uploaderViewOpen ? NO : YES;
    [self resetUploaderViewPosition];
}

#pragma mark - Default cycle
/**
 *  When the app is rotating to a new orientation, this method will resize the UI
 *  using a CGSize with the values inverted (the vc width as height and the heigth
 *  as width), so the animation will look good
 *
 *  @param toInterfaceOrientation The new orientation
 *  @param duration               The duration of transition
 */
-(void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration{
    CGSize size = CGSizeMake(self.view.frame.size.height, self.view.frame.size.width);
    if(UIInterfaceOrientationIsLandscape(toInterfaceOrientation) && UIInterfaceOrientationIsLandscape(self.interfaceOrientation)){
        size = self.view.frame.size;
    }
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.30];
    [self readjustSize:size];
    [self resetUploaderViewPosition:size];
    [UIView commitAnimations];
}
/**
 *  Detect a new orientation and resize the UI elements
 *
 *  @param fromInterfaceOrientation The previous orientation
 */
-(void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation{
    [self readjustSize];
    [self resetZoom];
    [self resetUploaderViewPosition];
}

#pragma mark - Scroll view delegate
/**
 * Detect the zoom change on the scroll view and center the image
 */
- (void)scrollViewDidZoom:(UIScrollView *)scrollView {
    image.frame = [self centeredFrameForScrollView:scrollView andUIView:image];
}
/**
 * Make the zoom for the scroll view
 */
-(UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView{
    scrollView.contentSize = CGSizeMake(MAX(image.frame.size.width,scrollView.contentSize.width), MAX(image.frame.size.height,scrollView.contentSize.height));
	return image;
}

@end