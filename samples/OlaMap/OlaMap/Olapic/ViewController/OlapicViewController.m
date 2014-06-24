//
//  OlapicViewController.m
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

#import "OlapicViewController.h"
#import <OlapicSDK/OlapicSDK.h>
#import "OlapicAsyncImageView.h"
#import "OlapicMediaViewController.h"

@interface OlapicViewController()
/**
 *  Center the loading indicator and the map
 *  using the current controller view size
 *  as reference
 */
-(void)centerContent;
/**
 *  Center the loading indicator and the map
 *  with a given size as reference
 *
 *  @param size The size to use as reference
 */
-(void)centerContent:(CGSize)size;

@end

@implementation OlapicViewController
@synthesize loader,firstLoad,list,map;
/**
 *  Class constructor
 *
 *  @return An instance of this object (OlapicViewController)
 */
-(id)init{
    self = [super init];
    if(self){
        loader = [[UIActivityIndicatorView alloc] initWithFrame:CGRectZero];
        loader.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        [self.view addSubview:loader];
        firstLoad = NO;
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
        self.title = @"Map";
        // Show the loading indicator
        [self centerContent];
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
 *  Center the loading indicator and the map
 *  using the current controller view size
 *  as reference
 */
-(void)centerContent{
    [self centerContent:self.view.frame.size];
}
/**
 *  Center the loading indicator and the map
 *  with a given size as reference
 *
 *  @param size The size to use as reference
 */
-(void)centerContent:(CGSize)size{
    loader.frame = CGRectMake((size.width / 2) - 10, (size.height / 2) - 10, 20, 20);
    if(map) [map setFrame:CGRectMake(0, 0, size.width, size.height)];
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
    [self centerContent:size];
    [UIView commitAnimations];
}
/**
 *  Detect a change of orientation and update the UI elements position
 *
 *  @param fromInterfaceOrientation The previous orientation
 */
-(void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation{
    [self centerContent];
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
    map = [[OlapicMapObject alloc] init];
    [map addOnView:self.view];
    [map setMapAnnotations:media andDelegate:self];
    [map setFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)];
    [map build];
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

#pragma mark - Map Delegate
/**
 *  The user did select a media entity from a map annotation
 *
 *  @param mapObject The map itself
 *  @param media     The selected media entity
 *  @param image     The image for the annotation
 */
-(void)mapObject:(OlapicMapObject *)mapObject didSelectMedia:(OlapicMediaEntity *)media fromImage:(OlapicAsyncImageView *)image{
    OlapicMediaViewController *mediaController = [[OlapicMediaViewController alloc] initWithImage:image];
    [self.navigationController pushViewController:mediaController animated:YES];
}

@end