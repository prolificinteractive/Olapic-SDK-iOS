//
//  OlapicUploaderHandler.h
//  OlapicSDKFramework
//  https://github.com/Olapic/Olapic-SDK-iOS
//
//  Created by The Olapic Team on 4/29/14.
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

@class OlapicUploaderEntity;
@class OlapicMediaEntity;
/**
 *  The object in charge of the uploader's common functionalities
 */
@interface OlapicUploaderHandler : OlapicHandler
/**-----------------------------------------------------------------------------
 * @name Get an uploader
 * -----------------------------------------------------------------------------
 */
/**
 *  Get an uploader from a media object
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] uploaders] getUploaderFromMedia:mediaEntityObject
 *  										 onSuccess:^(OlapicUploaderEntity *uploader){
 *  											 label.text = [uploader get:@"name"];
 *  										 }
 *  										 onFailure:^(NSError *error){
 *  											 NSLog(@"Error: %@",error.description);
 *  										 }];
 *  ```
 *
 *  @param media   The media object
 *  @param success A callback block for when the uploader is successfully retrieved
 *  @param failure A callback block for when the SDK can't get the uploader
 *  @since v1.0
 */
-(void)getUploaderFromMedia:(OlapicMediaEntity *)media onSuccess:(void (^)(OlapicUploaderEntity *uploader))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Get an uploader from its API URL
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] uploaders] getUploaderFromURL:@"users/001"
 *  										 onSuccess:^(OlapicUploaderEntity *uploader){
 *  											 label.text = [uploader get:@"name"];
 *  										 }
 *  										 onFailure:^(NSError *error){
 *  											 NSLog(@"Error: %@",error.description);
 *  										 }];
 *  ```
 *
 *  @param URL     The uploader API URL
 *  @param success A callback block for when the uploader is successfully retrieved
 *  @param failure A callback block for when the SDK can't get the uploader
 *  @since v1.0
 */
-(void)getUploaderFromURL:(NSString *)URL onSuccess:(void (^)(OlapicUploaderEntity *uploader))success onFailure:(void (^)(NSError *error))failure;
/**-----------------------------------------------------------------------------
 * @name Upload a media
 * -----------------------------------------------------------------------------
 */
/**
 *  Upload a media object
 *
 *  Example:
 *
 *  ```
 *  NSMutableDictionary *metadata = [[NSMutableDictionary alloc] init];
 *  // Required
 *  [metadata setValue:@"A brief description for the photo" forKey:@"caption"];
 *  // Optional
 *  // - Location
 *  [metadata setValue:@"latitude" forKey:@"latitude"];
 *  [metadata setValue:@"longitude" forKey:@"longitude"];
 *  // - Streams
 *  NSArray *streams = [[NSArray alloc] initWithObjects:streamEntityObject1,streamEntityObject2,nil];
 *  [metadata setValue:streams forKey:@"stream"];
 *
 *  NSString *imagePath = [[NSBundle bundleForClass:[self class]] pathForResource:@"sample" ofType:@"png"];
 *  NSData *imageData = [NSData dataWithContentsOfFile:imagePath];
 *
 *  [[[OlapicSDK sharedOlapicSDK] uploaders] uploadMediaFromUploader:uploaderEntityObject
 *  										 imageData:imageData
 *  										 metadata:metadata
 *  										 onSuccess:^(OlapicMediaEntity *media){
 *  											 // Done! The image should appear on the MQ
 *  										 }
 *  										 onFailure:^(NSError *error){
 *  											 NSLog(@"Error: %@",error.description);
 *  										 }];
 *  ```
 *
 *  @param uploader  The uploader entity that will 'own' the media
 *  @param imageData The image to upload, on data format
 *  @param metadata  The media information
 *
 *  - NSString caption      -required
 *  - NSString latitude     -optional
 *  - NSString longitude    -optional
 *  - NSArray  stream       -stream
 *
 *  @param success   A callback block for when the media is successfully uploaded
 *  @param failure   A callback block for when the media can't be uploaded
 *  @since v1.0
 */
-(void)uploadMediaFromUploader:(OlapicUploaderEntity *)uploader imageData:(NSData *)imageData metadata:(NSDictionary *)metadata onSuccess:(void (^)(OlapicMediaEntity *media))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Upload a media object and track the upload progresss
 *
 *  Example:
 *
 *  ```
 *  NSMutableDictionary *metadata = [[NSMutableDictionary alloc] init];
 *  // Required
 *  [metadata setValue:@"A brief description for the photo" forKey:@"caption"];
 *  // Optional
 *  // - Location
 *  [metadata setValue:@"latitude" forKey:@"latitude"];
 *  [metadata setValue:@"longitude" forKey:@"longitude"];
 *  // - Streams
 *  NSArray *streams = [[NSArray alloc] initWithObjects:streamEntityObject1,streamEntityObject2,nil];
 *  [metadata setValue:streams forKey:@"stream"];
 *
 *  NSString *imagePath = [[NSBundle bundleForClass:[self class]] pathForResource:@"sample" ofType:@"png"];
 *  NSData *imageData = [NSData dataWithContentsOfFile:imagePath];
 *
 *  [[[OlapicSDK sharedOlapicSDK] uploaders] uploadMediaFromUploader:uploaderEntityObject
 *  										 imageData:imageData
 *  										 metadata:metadata
 *  										 onSuccess:^(OlapicMediaEntity *media){
 *  											 // Done! The image should appear on the MQ
 *  										 }
 *  										 onFailure:^(NSError *error){
 *  											 NSLog(@"Error: %@",error.description);
 *  										 }
 *  										 onProgress:^(float progress){
 *  											 NSLog(@"Progress: %%@",(progress/100));
 *  										 }];
 *  ```
 *
 *  @param uploader  The uploader entity that will 'own' the media
 *  @param imageData The image to upload, on data format
 *  @param metadata  The media information
 *
 *  - NSString caption      -required
 *  - NSString latitude     -optional
 *  - NSString longitude    -optional
 *  - NSArray  stream       -stream
 *
 *  @param success   A callback block for when the media is successfully uploaded
 *  @param failure   A callback block for when the media can't be uploaded
 *  @param progress  A callback block that can be used to track the upload progress
 *  @since v1.0
 */
-(void)uploadMediaFromUploader:(OlapicUploaderEntity *)uploader imageData:(NSData *)imageData metadata:(NSDictionary *)metadata onSuccess:(void (^)(OlapicMediaEntity *media))success onFailure:(void (^)(NSError *error))failure onProgress:(void (^)(float progress))progress;

@end
