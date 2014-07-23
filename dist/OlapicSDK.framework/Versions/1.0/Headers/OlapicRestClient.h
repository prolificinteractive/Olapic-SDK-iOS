//
//  OlapicRestClient.h
//  OlapicSDKFramework
//  https://github.com/Olapic/Olapic-SDK-iOS
//
//  Created by The Olapic Team on 4/17/14.
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

@class OlapicAFHTTPRequestOperationManager;
/**
 *  The object in charge of connecting with the API
 */
@interface OlapicRestClient : NSObject
/**-----------------------------------------------------------------------------
 * @name Initializer
 * -----------------------------------------------------------------------------
 */
/**
 *  Initialize the object
 *
 *  @param key The authorization key for the API
 *
 *  @return An instance of this object
 *  @since  v1.0
 */
-(id)initWithAuthorization:(NSString *)key;
/**-----------------------------------------------------------------------------
 * @name GET
 * -----------------------------------------------------------------------------
 */
/**
 *  Make a GET request
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] rest] get:@"//photorankapi-a.akamaihd.net/customers/{ID}/media/recent/"
 *  									parameters:nil
 *  									onSuccess:^(id responseObject){
 *  										NSLog(@"Response: %@",responseObject);
 *  									}
 *  									onFailure:^(NSError *error){
 *  										NSLog(@"Error: %@",error.description);
 *  									}];
 *  ```
 *
 *  @param URL        The API URL
 *  @param parameters The parameters for the query string
 *  @param success    A callback block for when the connection is successfully done
 *  @param failure    A callback block for when the connection fails
 *  @since            v1.0
 */
-(void)get:(NSString *)URL parameters:(NSDictionary *)parameters onSuccess:(void (^)(id responseObject))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Make a GET request, but for the NSData information.
 *  This can be used to load an image
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] rest] getData:@"//photorankapi-a.akamaihd.net/sample.png"
 *  									parameters:nil
 *  									onSuccess:^(id responseObject){
 *  										NSLog(@"Response: %@",responseObject);
 *  									}
 *  									onFailure:^(NSError *error){
 *  										NSLog(@"Error: %@",error.description);
 *  									}];
 *  ```
 *
 *  @param URL        The API URL
 *  @param parameters The parameters for the query string
 *  @param success    A callback block for when the connection is successfully done
 *  @param failure    A callback block for when the connection fails
 *  @since            v1.0
 */
-(void)getData:(NSString *)URL parameters:(NSDictionary *)parameters onSuccess:(void (^)(NSData *responseData))success onFailure:(void (^)(NSError *error))failure;
/**-----------------------------------------------------------------------------
 * @name POST
 * -----------------------------------------------------------------------------
 */
/**
 *  Make a POST Request
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] rest] post:@"//photorankapi-a.akamaihd.net/post"
 *  									parameters:nil
 *  									data:postData
 *  									onSuccess:^(id responseObject){
 *  										NSLog(@"Response: %@",responseObject);
 *  									}
 *  									onFailure:^(NSError *error){
 *  										NSLog(@"Error: %@",error.description);
 *  									}];
 *  ```
 *
 *  @param URL        The API URL
 *  @param parameters The parameters for the query string
 *  @param data       A list of metadata information
 *  @param success    A callback block for when the connection is successfully done
 *  @param failure    A callback block for when the connection fails
 *  @since            v1.0
 */
-(void)post:(NSString *)URL parameters:(NSDictionary *)parameters data:(NSArray *)data onSuccess:(void (^)(id responseObject))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Make a POST Request and track the connection progress
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] rest] post:@"//photorankapi-a.akamaihd.net/post"
 *  									parameters:nil
 *  									data:postData
 *  									onSuccess:^(id responseObject){
 *  										NSLog(@"Response: %@",responseObject);
 *  									}
 *  									onFailure:^(NSError *error){
 *  										NSLog(@"Error: %@",error.description);
 *  									}
 *  									onProgress:^(float progress){
 *  										NSLog(@"Progress: %%@",(progress/100));
 *  									}];
 *  ```
 *
 *  @param URL        The API URL
 *  @param parameters The parameters for the query string
 *  @param data       A list of metadata information
 *  @param success    A callback block for when the connection is successfully done
 *  @param failure    A callback block for when the connection fails
 *  @param progress   A callback block that can be used to track the connection progress
 */
-(void)post:(NSString *)URL parameters:(NSDictionary *)parameters data:(NSArray *)data onSuccess:(void (^)(id responseObject))success onFailure:(void (^)(NSError *error))failure onProgress:(void (^)(float progress))progress;
/**-----------------------------------------------------------------------------
 * @name Extras
 * -----------------------------------------------------------------------------
 */
/**
 *  Validate an API response (it will check
 *  for a 200 status)
 *
 *  @param  request The API response
 *
 *  @return If the response status is 200
 *  @since  v1.0
 */
-(BOOL)isValid:(NSDictionary *)request;
/**
 *  Get the AFNetworking operation manager
 *
 *  @return A new instance of the operation manager
 */
-(OlapicAFHTTPRequestOperationManager *)getOperationManager;


@end
