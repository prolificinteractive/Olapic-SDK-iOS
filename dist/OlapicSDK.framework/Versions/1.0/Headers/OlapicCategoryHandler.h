//
//  OlapicCategoryHandler.h
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

#import "OlapicHandler.h"

@class OlapicCategoryEntity;
/**
 *  The object in charge of creating and managing the OlapicCategoryEntities
 */
@interface OlapicCategoryHandler : OlapicHandler
/**-----------------------------------------------------------------------------
 * @name Get a category
 * -----------------------------------------------------------------------------
 */
/**
 *  Get a category entity by its tag_key property
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] categories] getCategoryByTagKey:@"my_tag"
 *  										  onSuccess:^(OlapicCategoryEntity *category){
 *  											  label.text = [category get:@"name"];
 *  										  }
 *  										  onFailure:^(NSError *error){
 *  											  NSLog(@"Error: %@",error.description);
 *  										  }];
 *  ```
 *
 *  @param tag     The value of the tag_key property
 *  @param success A callback block for when the category is successfully retrieved
 *  @param failure A callback block for when the SDK can't get the category
 *  @since v1.0
 */
-(void)getCategoryByTagKey:(NSString *)tag onSuccess:(void (^)(OlapicCategoryEntity *category))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Get a category entity by its ID
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] categories] getCategoryByID:@"001"
 *  										  onSuccess:^(OlapicCategoryEntity *category){
 *  											  label.text = [category get:@"name"];
 *  										  }
 *  										  onFailure:^(NSError *error){
 *  											  NSLog(@"Error: %@",error.description);
 *  										  }];
 *  ```
 *
 *  @param ID      The ID of the category
 *  @param success A callback block for when the category is successfully retrieved
 *  @param failure A callback block for when the SDK can't get the category
 *  @since v1.0
 */
-(void)getCategoryByID:(NSString *)ID onSuccess:(void (^)(OlapicCategoryEntity *category))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Get a category entity from the API URL
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] categories] getCategoryFromURL:@"categories/001"
 *  										  onSuccess:^(OlapicCategoryEntity *category){
 *  											  label.text = [category get:@"name"];
 *  										  }
 *  										  onFailure:^(NSError *error){
 *  											  NSLog(@"Error: %@",error.description);
 *  										  }];
 *  ```
 *
 *  @param URL     The URL for the category
 *  @param success A callback block for when the category is successfully retrieved
 *  @param failure A callback block for when the SDK can't get the category
 *  @since v1.0
 */
-(void)getCategoryFromURL:(NSString *)URL onSuccess:(void (^)(OlapicCategoryEntity *category))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Get a category entity from an API URL with extra parameters
 *
 *  Example:
 *
 *  ```
 *  [[[OlapicSDK sharedOlapicSDK] categories] getCategoryFromURL:@"categories/001"
 *  										  onSuccess:^(OlapicCategoryEntity *category){
 *  												label.text = [category get:@"name"];
 *  										  }
 *  										  onFailure:^(NSError *error){
 *  												NSLog(@"Error: %@",error.description);
 *  										  }
 *  										  parameters:nil];
 *  ```
 *
 *  @param URL        the API URL
 *  @param success    A callback block for when the category is successfully retrieved
 *  @param failure    A callback block for when the SDK can't get the category
 *  @param parameters A list of parameters for the request, like 'count' or 'limit'
 *  @since v1.0
 */
-(void)getCategoryFromURL:(NSString *)URL onSuccess:(void (^)(OlapicCategoryEntity *category))success onFailure:(void (^)(NSError *error))failure parameters:(NSDictionary *)parameters;

@end
