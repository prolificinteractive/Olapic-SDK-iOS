//
//  OlapicViewController.m
//  OlaMediaUploader
//  https://github.com/Olapic/Olapic-SDK-iOS
//
//  Documentation
//  http://docs.photorank.me/ios
//
//  Created by The Olapic Team on 5/14/14.
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

@interface OlapicViewController ()
-(void)openSelector:(id)sender;
-(void)showAlert:(NSString *)message title:(NSString *)title;
@end

@implementation OlapicViewController
@synthesize _customer;
@synthesize _uploader;
@synthesize locationManager;
@synthesize imageUploadProgress;

- (id)init
{
    self = [super init];
    if (self) {
        // Set the API Key
        NSString *APIKey = @"<YOUR API KEY>";
        OlapicSDK *olapic = [OlapicSDK sharedOlapicSDK];
        [olapic connectWithCustomerAuthKey:APIKey onSuccess:^(OlapicCustomerEntity *customer){
            _customer = customer;
        } onFailure:^(NSError *error){
            [self showAlert:[NSString stringWithFormat:@"Error trying to connect: %@", error] title:@"Error"];
        }];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = @"Uploader";
    
    locationManager = [[CLLocationManager alloc]init];
    locationManager.distanceFilter = kCLDistanceFilterNone;
    locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    [locationManager startUpdatingLocation];
    
    [self drawUI];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

-(void)drawUI {
    UIImage *buttonImage = [UIImage imageNamed:@"button"];
    UIButton *btnTakePicture = [UIButton buttonWithType:UIButtonTypeCustom];
    btnTakePicture.frame = CGRectMake(0, 0, buttonImage.size.width, buttonImage.size.height);
    [btnTakePicture setBackgroundImage:buttonImage forState:UIControlStateNormal];
    btnTakePicture.center = CGPointMake(self.view.frame.size.width / 2, (self.view.frame.size.height - 45) - btnTakePicture.frame.size.height);
    [btnTakePicture addTarget:self action:@selector(openSelector:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btnTakePicture];
    
    self.imageUploadProgress = [[TNSexyImageUploadProgress alloc] init];
    self.imageUploadProgress.radius = 100;
    self.imageUploadProgress.progressBorderThickness = -10;
    self.imageUploadProgress.trackColor = [UIColor blackColor];
    self.imageUploadProgress.progressColor = [UIColor whiteColor];
    self.imageUploadProgress.imageToUpload = nil;
}

-(void)openSelector:(id)sender {
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:nil delegate:self cancelButtonTitle:@"Cancel" destructiveButtonTitle:nil otherButtonTitles:@"Camera", @"Photo Library", nil];
    [actionSheet showInView:self.view];
}

-(void)actionSheet:(UIActionSheet *)popup clickedButtonAtIndex:(NSInteger)buttonIndex {
    if(buttonIndex == 2) return;
    UIImagePickerController * picker = [[UIImagePickerController alloc] init];
    picker.delegate=self;
    if(buttonIndex == 0){
        if (![UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]) {
            [self showAlert:@"Device has no camera" title:@"Error"];
            return;
        }
        [picker setSourceType:(UIImagePickerControllerSourceTypeCamera)];
    } else {
        [picker setSourceType:(UIImagePickerControllerSourceTypePhotoLibrary)];
    }
    [self presentViewController:picker animated:YES completion:Nil];
}

-(void)showAlert:(NSString *)message title:(NSString *)title {
    UIAlertView *myAlertView = [[UIAlertView alloc] initWithTitle:title message:message delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil];
    [myAlertView show];
}

- (UIImage *)compressForUpload:(UIImage *)original scale:(CGFloat)scale {
    CGSize originalSize = original.size;
    CGSize newSize = CGSizeMake(originalSize.width * scale, originalSize.height * scale);
    
    UIGraphicsBeginImageContext(newSize);
    [original drawInRect:CGRectMake(0, 0, newSize.width, newSize.height)];
    UIImage* compressedImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return compressedImage;
}

#pragma mark PickerController delegate

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info {
    [picker dismissViewControllerAnimated:YES completion:^{
        UIImage *selectedImage = [info objectForKey:UIImagePickerControllerOriginalImage];
        self.imageUploadProgress.imageToUpload = selectedImage;
        [self.imageUploadProgress show];
        
        if(!_uploader){
            NSMutableDictionary *userMetadata = [[NSMutableDictionary alloc] init];
            [userMetadata setValue:@"iostest@olapic.com" forKey:@"email"];
            [userMetadata setValue:@"iOS Test" forKey:@"screen_name"];
            [_customer createUploader:userMetadata onSuccess:^(OlapicUploaderEntity *uploader) {
                _uploader = uploader;
                [self doUpload:selectedImage];
            } onFailure:^(NSError *error) {
                [self showAlert:[NSString stringWithFormat:@"Error creating the uploader: %@", error] title:@"Error"];
            }];
        } else {
            [self doUpload:selectedImage];
        }
    }];
}

-(void)doUpload:(UIImage *)selectedImage {
    NSMutableDictionary *mediaMetadata = [[NSMutableDictionary alloc] init];
    [mediaMetadata setValue:@"The caption" forKey:@"caption"];
    [mediaMetadata setValue:[NSString stringWithFormat:@"%f", locationManager.location.coordinate.latitude] forKey:@"latitude"];
    [mediaMetadata setValue:[NSString stringWithFormat:@"%f", locationManager.location.coordinate.longitude] forKey:@"longitude"];
    [_uploader uploadMediaFromImage:[self compressForUpload:selectedImage scale:0.5] metadata:mediaMetadata onSuccess:^(OlapicMediaEntity *media) {
        [self showAlert:@"The media has been uploaded, it should appear on the moderation queue soon" title:@"Ok"];
    } onFailure:^(NSError *error) {
        [self showAlert:[NSString stringWithFormat:@"Error uploading media: %@", error] title:@"Error"];
    } onProgress:^(float progress) {
        self.imageUploadProgress.progress = (progress / 100);
    }];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {
    [picker dismissViewControllerAnimated:YES completion:NULL];
}

@end
