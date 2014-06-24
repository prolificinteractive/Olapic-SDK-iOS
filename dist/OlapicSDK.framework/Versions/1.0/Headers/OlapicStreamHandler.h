//
//  OlapicStreamHandler.h
//  OlapicSDKFramework
//  https://github.com/Olapic/Olapic-SDK-iOS
//
//  Created by The Olapic Team on 5/1/14.
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

@class OlapicStreamEntity;
/**
 *  The object in charge of the streams common functionalities
 */
@interface OlapicStreamHandler : OlapicHandler
/**-----------------------------------------------------------------------------
 * @name Get a stream
 * -----------------------------------------------------------------------------
 */
/**
 *  Get a stream entity by its tag_key property
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] streams] getStreamByTagKey:@"my_tag"
 *  									   onSuccess:^(OlapicStreamEntity *stream){
 *  										   label.text = [stream get:@"name"];
 *  									   }
 *  									   onFailure:^(NSError *error){
 *  										   NSLog(@"Error: %@",error.description);
 *  									   }];
 *  ```
 *
 *  @param tag     The value of the tag_key property
 *  @param success A callback block for when the stream is successfully retrieved
 *  @param failure A callback block for when the SDK can't get the stream
 *  @since v1.0
 */
-(void)getStreamByTagKey:(NSString *)tag onSuccess:(void (^)(OlapicStreamEntity *stream))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Get a stream entity by its ID
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] streams] getStreamByID:@"ID"
 *  									   onSuccess:^(OlapicStreamEntity *stream){
 *  										   label.text = [stream get:@"name"];
 *  									   }
 *  									   onFailure:^(NSError *error){
 *  										   NSLog(@"Error: %@",error.description);
 *  									   }];
 *  ```
 *
 *  @param ID      The stream ID
 *  @param success A callback block for when the stream is successfully retrieved
 *  @param failure A callback block for when the SDK can't get the stream
 *  @since v1.0
 */
-(void)getStreamByID:(NSString *)ID onSuccess:(void (^)(OlapicStreamEntity *stream))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Get a stream entity from it's API URL
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] streams] getStreamFromURL:@"streams/001"
 *  									   onSuccess:^(OlapicStreamEntity *stream){
 *  										   label.text = [stream get:@"name"];
 *  									   }
 *  									   onFailure:^(NSError *error){
 *  										   NSLog(@"Error: %@",error.description);
 *  									   }];
 *  ```
 *
 *  @param URL     The API URL for the stream
 *  @param success A callback block for when the stream is successfully retrieved
 *  @param failure A callback block for when the SDK can't get the stream
 *  @since v1.0
 */
-(void)getStreamFromURL:(NSString *)URL onSuccess:(void (^)(OlapicStreamEntity *stream))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Get the Stream entity from API's URL with extra parameters
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] streams] getStreamFromURL:@"streams/001"
 *  									   onSuccess:^(OlapicStreamEntity *stream){
 *  										   label.text = [stream get:@"name"];
 *  									   }
 *  									   onFailure:^(NSError *error){
 *  										   NSLog(@"Error: %@",error.description);
 *  									   } parameters:nil];
 *  ```
 *
 *  @param URL        The API URL for the stream
 *  @param success    A callback block for when the stream is successfully retrieved
 *  @param failure    A callback block for when the SDK can't get the stream
 *  @param parameters A list of parameters for the request, like 'count' or 'limit'
 *  @since v1.0
 */
-(void)getStreamFromURL:(NSString *)URL onSuccess:(void (^)(OlapicStreamEntity *stream))success onFailure:(void (^)(NSError *error))failure parameters:(NSDictionary *)parameters;

@end
