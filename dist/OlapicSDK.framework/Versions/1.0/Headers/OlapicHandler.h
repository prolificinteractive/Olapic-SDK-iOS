//
//  OlapicHandler.h
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

@class OlapicSDK;
/**
 *  The base interface for the handler objects
 */
@interface OlapicHandler : NSObject
/**-----------------------------------------------------------------------------
 * @name Create Entities
 * -----------------------------------------------------------------------------
 */
/**
 *  Create entity from an API JSON response
 *
 *  @param  JSON The JSON dictionary
 *
 *  @return An entity object
 *  @since  v1.0
 */
-(id)createEntityFromJSON:(NSDictionary *)JSON;
/**-----------------------------------------------------------------------------
 * @name Entities Customization
 * -----------------------------------------------------------------------------
 */
/**
 *  Get embedded resource URLs from a JSON API response
 *
 *  @param  embedded The API JSON response
 *
 *  @return A dictionary with the resource's URLs
 *  @since  v1.0
 */
-(NSDictionary *)getResources:(NSDictionary *)embedded;
/**
 *  Get embedded forms URLs from an API JSON response
 *
 *  @param  forms The form's information from the API
 *
 *  @return A dictionary with the form's URLs
 *  @since  v1.0
 */
-(NSDictionary *)getForms:(NSDictionary *)forms;
/**-----------------------------------------------------------------------------
 * @name Utils
 * -----------------------------------------------------------------------------
 */
/**
 *  Extract entities from API response
 *
 *  @param  request The request information
 *
 *  @return A dictionary with the entities
 *  @since  v1.0
 */
-(NSDictionary *)extractEntitiesFromRequest:(NSDictionary *)request;
/**
 *  Prepare a dictionary to be sent on a POST request
 *
 *  @param metadata The information to prepare
 *
 *  @return A list with the information ready
 *  @since  v1.0
 */
-(NSArray *)prepareMetadataForPOST:(NSDictionary *)metadata;
/**
 *  Get the OlapicSDK reference
 *
 *  @return A reference to the SDK singleton
 *  @since  v1.0
 */
-(OlapicSDK *)getSDK;

@end
