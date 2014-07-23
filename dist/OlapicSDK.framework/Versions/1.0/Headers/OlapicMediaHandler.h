//
//  MediaHandler.h
//  OlapicSDKFramework
//  https://github.com/Olapic/Olapic-SDK-iOS
//
//  Created by The Olapic Team on 4/15/14.
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

#import "OlapicHandler.h"
#import <UIKit/UIKit.h>
/**
 *  The different image sizes for the media
 */
typedef NS_ENUM(NSInteger,OlapicMediaImageSize){
    /**
     *  A small version of the original image, cropped to be square
     */
    OlapicMediaImageSizeSquare = 0,
    /**
     *  A small thumbnail version, keeping the original proportion size
     */
    OlapicMediaImageSizeThumbnail = 1,
    /**
     *  A medium size version, for mobile devices, keeping the original proportion size
     *
     *  @warning For retina display, you should use the original
     */
    OlapicMediaImageSizeMobile = 2,
    /**
     *  A big size vesion, keeping the original proportion size
     */
    OlapicMediaImageSizeNormal = 3,
    /**
     *  The original image
     */
    OlapicMediaImageSizeOriginal = 4
};

@class OlapicMediaEntity;
/**
 *  The object in charge of the media's common functionalities
 */
@interface OlapicMediaHandler : OlapicHandler
/**-----------------------------------------------------------------------------
 * @name Utils
 * -----------------------------------------------------------------------------
 */
/**
 *  Get string key for an image size
 *
 *  The returned key will be used to call the ``get``
 *  method of a OlapicMediaEntity, so if you send
 *  OlapicMediaImageSizeMobile, you'll get "images/mobile"
 *
 *  @param size OlapicMediaImageSize
 *
 *  @return The string value
 *  @since v1.0
 */
+(NSString *)getKeyForImageSize:(OlapicMediaImageSize)size;
/**-----------------------------------------------------------------------------
 * @name Get a list of media
 * -----------------------------------------------------------------------------
 */
/**
 *  Get a media from an API URL
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] media] getMediaFromURL:@"//photorankapi-a.akamaihd.net/customers/{ID}/media/recent/"
 *  									 onSuccess:^(NSDictionary *response){
 *  										 NSArray *media = [response valueForKey:@"media"]
 *  										 for(int i = 0; i < [media count]; i++){
 *  											 OlapicMediaEntity *mediaObject = [media objectAtIndex:i];
 *  											 NSLog(@"Media %@",mediaObject);
 *  										 }
 *  									 }
 *  									 onFailure:^(NSError *error){
 *  										 NSLog(@"Error: %@",error.description);
 *  									 }];
 *  ```
 *  @param URL     The API URL
 *  @param success A callback block for when the media is successfully retrieved.
 *                 The response is a dictionary with the following keys:
 *                 
 *                 - links: An ``NSDictionary`` with the API URLs to paginate the media objects
 *                 - media: An ``NSArray`` with the media objects
 *
 *  @param failure A callback block for when the SDK can't get the media
 *
 *  @since v1.0
 */
-(void)getMediaFromURL:(NSString *)URL onSuccess:(void (^)(NSDictionary *response))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Get a media from an API URL, with extra
 *  parameters
 *
 *  Example:
 *
 *  ```
 *  NSMutableDictionary *parameters = [[NSMutableDictionary alloc] init];
 *  [parameters setValue:@"10" forKey:@"count"];
 *  [[[OlapicSDK sharedOlapicSDK] media] getMediaFromURL:@"//photorankapi-a.akamaihd.net/customers/{ID}/media/recent/"
 *  									 onSuccess:^(NSDictionary *response){
 *  										 NSArray *media = [response valueForKey:@"media"]
 *  										 for(int i = 0; i < [media count]; i++){
 *  											 OlapicMediaEntity *mediaObject = [media objectAtIndex:i];
 *  											 NSLog(@"Media %@",mediaObject);
 *  										 }
 *  									 }
 *  									 onFailure:^(NSError *error){
 *  										 NSLog(@"Error: %@",error.description);
 *  									 } parameters:parameters];
 *  ```
 *
 *  @param URL        The API URL
 *  @param success    A callback block for when the media is successfully retrieved
 *  @param failure    A callback block for when the SDK can't get the media
 *  @param parameters A list of parameters for the request, like 'count' or 'limit'
 *
 *  @since v1.0
 */
-(void)getMediaFromURL:(NSString *)URL onSuccess:(void (^)(NSDictionary *response))success onFailure:(void (^)(NSError *error))failure parameters:(NSDictionary *)parameters;
/**-----------------------------------------------------------------------------
 * @name UI
 * -----------------------------------------------------------------------------
 */
/**
 *  Load an image with a specific size
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] media] loadImageWithSize:OlapicMediaImageSizeOriginal
 *  									 fromMedia:mediaEntityObject
 *  									 onSuccess:^(NSData *mediaData,UIImage *mediaImage){
 *  										 UIImageView *imageView = [[UIImageView alloc] initWithImage:mediaImage];
 *  										 [self.view addSubview:imageView];
 *  									 }
 *  									 onFailure:^(NSError *error){
 *  										 NSLog(@"Error: %@",error.description);
 *  									 }];
 *  ```
 *
 *  @param size    The image size
 *  @param media   The media object from where the image will be loaded
 *  @param success A callback block for when the image is successfully retrieved
 *  @param failure A callback block for when the SDK can't get the image
 *
 *  @since v1.0
 */
-(void)loadImageWithSize:(OlapicMediaImageSize)size fromMedia:(OlapicMediaEntity *)media onSuccess:(void (^)(NSData *mediaData,UIImage *mediaImage))success onFailure:(void (^)(NSError *error))failure;
/**-----------------------------------------------------------------------------
 * @name Report
 * -----------------------------------------------------------------------------
 */
/**
 *  Report a media
 *
 *  Example:
 *
 *  ```
 *  NSMutableDictionary *metadata = [[NSMutableDictionary alloc] init];
 *  [metadata setValue:@"example@olapic.com" forKey:@"email"];
 *  [metadata setValue:@"I find this photo offensive!" forKey:@"reason"];
 *  [[[OlapicSDK sharedOlapicSDK] media] reportMedia:mediaEntityObject
 *  									 metadata:metadata
 *  									 onSuccess:^(void){
 *  										 NSLog(@"Successfully reported");
 *  									 }
 *  									 onFailure:^(NSError *error){
 *  										 NSLog(@"Error: %@",error.description);
 *  									 }];
 *  ```
 *
 *  @param media    The media object to report
 *  @param metadata A list with the report information
 *
 *  - email: The email of the user who wants to report the media
 *  - reason: The reason why the media will be reported
 *
 *  @param success  A callback block for when the media is successfully reported
 *  @param failure  A callback block for when the SDK can't report the media
 *
 *  @since v1.0
 */
-(void)reportMedia:(OlapicMediaEntity *)media metadata:(NSDictionary *)metadata onSuccess:(void(^)(void))success onFailure:(void (^)(NSError *error))failure;
/**-----------------------------------------------------------------------------
 * @name Streams
 * -----------------------------------------------------------------------------
 */
/**
 *  Get a list of streams related to a media
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] media] getRelatedStreamsFromMedia:mediaEntityObject
 *  									 onSuccess:^(NSArray *streams){
 *  										 for(int i = 0; i < [streams count]; i++){
 *  											 OlapicStreamEntity *streamObject = [streams objectAtIndex:i];
 *  											 NSLog(@"Stream %@",streamObject);
 *  										 }
 *  									 }
 *  									 onFailure:^(NSError *error){
 *  										 NSLog(@"Error: %@",error.description);
 *  									 }];
 *  ```
 *
 *  @param media   The media object
 *  @param success A callback block for when the streams are successfully retrieved
 *  @param failure A callback block for when the SDK can't get the streams
 *
 *  @since v1.0
 */
-(void)getRelatedStreamsFromMedia:(OlapicMediaEntity *)media onSuccess:(void(^)(NSArray *streams))success onFailure:(void (^)(NSError *error))failure;

@end
