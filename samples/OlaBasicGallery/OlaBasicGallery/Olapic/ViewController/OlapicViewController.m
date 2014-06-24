//
//  OlapicViewController.m
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

#import "OlapicViewController.h"
#import <OlapicSDK/OlapicSDK.h>
#import "OlapicAsyncImageView.h"
#import "OlapicMediaViewController.h"

@interface OlapicViewController()
/**
 *  Center the loading indicator using the current
 *  controller view size as reference
 */
-(void)centerLoader;
/**
 *  Center the loading indicator with a given
 *  size as reference
 *
 *  @param size The size to use as reference
 */
-(void)centerLoader:(CGSize)size;

@end

@implementation OlapicViewController
@synthesize loader,firstLoad,list,scroll,thumbnails;
/**
 *  Class constructor
 *
 *  @return An instance of this object (OlapicViewController)
 */
-(id)init{
    self = [super init];
    if(self){
        scroll = [[UIScrollView alloc] initWithFrame:CGRectZero];
        loader = [[UIActivityIndicatorView alloc] initWithFrame:CGRectZero];
        loader.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        [self.view addSubview:scroll];
        [self.view addSubview:loader];
        firstLoad = NO;
        thumbnails = [[NSMutableArray alloc] init];
    }
    return self;
}
/**
 *  If this is the first time this method is called, it will
 *  connect with the API and start downloading the content
 */
-(void)viewDidLoad{
    [super viewDidLoad];
    if(!firstLoad){
        // Set the flag
        firstLoad = YES;
        // Some customization for the VC
        self.view.backgroundColor = [UIColor whiteColor];
        self.title = @"Gallery";
        // Show the loading indicator
        [self centerLoader];
        [loader startAnimating];
        // Set the API Key
        NSString *APIKey = @"<YOUR API KEY>";
        // Connect the SDK
        OlapicSDK *olapic = [OlapicSDK sharedOlapicSDK];
        [olapic connectWithCustomerAuthKey:APIKey onSuccess:^(OlapicCustomerEntity *customer){
            list = [[OlapicCustomerMediaList alloc] initForCustomer:customer delegate:self sort:OlapicMediaListSortingTypePhotorank mediaPerPage:32];
            [list startFetching];
        } onFailure:^(NSError *error){
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:error.description delegate:nil cancelButtonTitle:@"Accept" otherButtonTitles:nil];
            [alert show];
        }];
        
    }
}
/**
 *  Center the loading indicator using the current
 *  controller view size as reference
 */
-(void)centerLoader{
    [self centerLoader:self.view.frame.size];
}
/**
 *  Center the loading indicator with a given
 *  size as reference
 *
 *  @param size The size to use as reference
 */
-(void)centerLoader:(CGSize)size{
    loader.frame = CGRectMake((size.width / 2) - 10, (size.height / 2) - 10, 20, 20);
}
/**
 *  Take an array of media and, using the OlapicAsyncImageView,
 *  generate the final thumbnail list
 *
 *  @param media An array of OlapicMediaEntity objects
 */
-(void)createThumbnailsFromMedia:(NSArray *)media{
    for (int i = 0; i < [media count]; i++){
        OlapicAsyncImageView *thumb = [[OlapicAsyncImageView alloc] initWithMedia:[media objectAtIndex:i] callback:^(OlapicAsyncImageView *image){
            OlapicMediaViewController *mediaController = [[OlapicMediaViewController alloc] initWithImage:image];
            [self.navigationController pushViewController:mediaController animated:YES];
        } andFrame:CGRectMake(0, 0, 74, 74)];
        [thumbnails addObject:thumb];
        [scroll addSubview:thumb];
        [thumb download];
    }
}
/**
 *  Updates the thumbnails position, using the current controller
 *  view size as reference
 */
-(void)reorderThumbnails{
    [self reorderThumbnails:self.view.frame.size];
}
/**
 *  Updates the thumbnails position, using a given size as reference
 *
 *  @param size The size to use as reference
 */
-(void)reorderThumbnails:(CGSize)size{
    // Set the scroll size to fullscreen
    scroll.frame = CGRectMake(0, 0, size.width, size.height);
    // Get the area width
    int areaWidth = size.width;
    // Define the width and height of the thumbnails
    CGSize thumbsSize = CGSizeMake(74, 74);
    // If the area width its 0, don't render, get out
    if(areaWidth == 0) return;
    // This var will have the number of pixels between photos
    int separator = 0;
    // This var will have the number of photos that can be shown per line
    int perline = 0;
    // These two vars are loop helpers
    int currentColumn = 0;
    int currentRow = 0;
    // Check the thumbnails width agains the area width, in order
    // to determine how many of them are going per line
    if([thumbnails count] > 0){
        for(int sep = 0; sep < [thumbnails count]; sep++){
            if((sep * thumbsSize.width) > areaWidth){
                perline = (sep - 1);
                break;
            }
        }
    }
    // If there's only enough for one line, it will use all the remaining space as separation
    if(perline == 0){
        separator = (areaWidth - (thumbsSize.width * [thumbnails count])) / ([thumbnails count]+1);
    }else{
        // calculate the separation
        separator = round((areaWidth - (thumbsSize.width * perline)) / (perline+1));
    }
    // Loop the photos
    for(int img = 0; img < [thumbnails count]; img++){
        // Move one column
        currentColumn++;
        // Calculate the new position
        float newX = ((currentColumn-1) * (thumbsSize.width + separator)) + separator;
        float newY = (currentRow * (thumbsSize.height + separator)) + separator;
        CGPoint newPosition = CGPointMake(newX,newY);
        // Tell the controller to change the thumbnail position
        [self changeImage:[thumbnails objectAtIndex:img] atPosition:newPosition];
        // If the current column is the last one, reset the flag and move one row
        if(currentColumn == perline){
            currentColumn = 0;
            currentRow++;
        }
    }
    // Calculate the heigth of the scroll
    if(currentColumn > 0 && currentColumn != perline) currentRow++;
    int newScrollHeight = (currentRow * (thumbsSize.height + separator)) + separator;
    CGSize newScrollSize = CGSizeMake(areaWidth, MAX(newScrollHeight, (size.height-64)));
    scroll.contentSize = newScrollSize;
}
/**
 *  A simple shorthand method to move a thumbnail to a new position
 *
 *  @param img The thumbnail to move
 *  @param pos The new position
 */
-(void)changeImage:(OlapicAsyncImageView *)img atPosition:(CGPoint)pos{
    img.frame = CGRectMake(pos.x, pos.y, img.frame.size.width, img.frame.size.height);
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
    [self reorderThumbnails:size];
    [self centerLoader:size];
    [UIView commitAnimations];
}
/**
 *  Detect a change of orientation and update the UI elements position
 *
 *  @param fromInterfaceOrientation The previous orientation
 */
-(void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation{
    [self reorderThumbnails];
    [self centerLoader];
}

#pragma mark - List Delegate
/**
 *  The media list object downloaded the content
 *
 *  @param mediaList The media list object
 *  @param media     An array of media objects
 *  @param links     The links to the API from where this media objects were downloaded
 */
-(void)OlapicMediaList:(OlapicMediaList *)mediaList didLoadMedia:(NSArray *)media withLinks:(NSDictionary *)links{
    [self createThumbnailsFromMedia:media];
    [self reorderThumbnails];
    [loader stopAnimating];
}
/**
 *  In case the media list object finds an error while downloading the content
 *
 *  @param mediaList The media list object
 *  @param error     The error it found
 */
-(void)OlapicMediaList:(OlapicMediaList *)mediaList didReceiveAnError:(NSError *)error{
    NSLog(@"LIST ERROR : %@",error);
}

@end