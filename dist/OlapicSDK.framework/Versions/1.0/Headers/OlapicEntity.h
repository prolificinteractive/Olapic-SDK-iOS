//
//  OlapicEntity.h
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
 *  The base interface for all the entities on the SDK
 */
@interface OlapicEntity : NSObject{
    /**
     *  The base data retrieved from the API response
     */
    NSMutableDictionary *data;
}

@property (nonatomic,strong) NSMutableDictionary *data;
/**-----------------------------------------------------------------------------
 * @name Initializer
 * -----------------------------------------------------------------------------
 */
/**
 *  Initialize the entity
 *
 *  @param idata The entity information
 *
 *  @return An instance of the entity
 *  @since  v1.0
 */
-(id)initWithData:(NSDictionary *)idata;
/**-----------------------------------------------------------------------------
 * @name Read
 * -----------------------------------------------------------------------------
 */
/**
 *  Get specific information from the entity
 *
 *  @param path The navigation path, using slashes like a real path: key1/key2/value
 *
 *  @return The value for the given path
 *  @since  v1.0
 */
-(id)get:(NSString *)path;
/**-----------------------------------------------------------------------------
 * @name Utils
 * -----------------------------------------------------------------------------
 */
/**
 *  Get the OlapicSDK reference
 *
 *  @return The OlapicSDK
 *  @since  v1.0
 */
-(OlapicSDK *)getSDK;

@end
