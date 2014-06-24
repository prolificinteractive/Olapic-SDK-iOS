//
//  OlapicCustomerEntity.h
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

#import "OlapicEntity.h"

@class OlapicStreamEntity;
@class OlapicUploaderEntity;
/**
 *  Represents customers on the SDK
 */
@interface OlapicCustomerEntity : OlapicEntity {
    /**
     *  The default uploader for the customer
     */
    OlapicUploaderEntity * uploader;
}

@property (nonatomic, strong) OlapicUploaderEntity * uploader;
/**-----------------------------------------------------------------------------
 * @name Uploader
 * -----------------------------------------------------------------------------
 */
/**
 *  Get the default uploader for this customer, if it doesn't exists it
 *  will create a new one
 *
 *  Example:
 *
 *  ```
 *  OlapicSDK *olapic = [OlapicSDK sharedOlapicSDK]
 *  [[olapic customer]	getUploader:^(OlapicUploaderEntity *uploader){
 *  						// Now you can upload some media
 *  					}
 *  					onFailure:^(NSError *error){
 *  						NSLog(@"Error: %@",error.description);
 *  					}];
 *  ```
 *
 *  @param success  A callback block for when the uploader is successfully retrieved
 *  @param failure  A callback block for when the SDK can't get the uploader
 *  @since v1.0
 *  @see OlapicCustomerHandler
 */
-(void)getUploader:(void (^)(OlapicUploaderEntity *uploader))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Create an uploader for this customer
 *
 *  Example:
 *
 *  ```
 *  NSMutableDictionary *metadata = [[NSMutableDictionary alloc] init];
 *  [metadata setValue:@"example@olapic.com" forKey:@"email"];
 *  [metadata setValue:@"Example" forKey:@"screen_name"];
 *  OlapicSDK *olapic = [OlapicSDK sharedOlapicSDK]
 *  [[olapic customer]	createUploader:metadata
 *  					onSuccess:^(OlapicUploaderEntity *uploader){
 *  						// Now you can upload some media
 *  					}
 *  					onFailure:^(NSError *error){
 *  						NSLog(@"Error: %@",error.description);
 *  					}];
 *  ```
 *
 *  @param metadata A dictionary that contains the uploader information
 *  @param success  A callback block for when the uploader is successfully created
 *  @param failure  A callback block for when the SDK can't create the uploader
 *  @since v1.0
 *  @see OlapicCustomerHandler
 */
-(void)createUploader:(NSDictionary *)metadata onSuccess:(void (^)(OlapicUploaderEntity *uploader))success onFailure:(void (^)(NSError *error))failure;

@end
