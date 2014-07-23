//
//  OlapicSDK.h
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

#import "OlapicRestClient.h"

#pragma mark - Include Media Lists

#import "OlapicMediaList.h"
#import "OlapicCustomerMediaList.h"
#import "OlapicStreamMediaList.h"
#import "OlapicCategoryMediaList.h"
#import "OlapicUploaderMediaList.h"

#pragma mark - Include entities files

#import "OlapicCustomerEntity.h"
#import "OlapicMediaEntity.h"
#import "OlapicUploaderEntity.h"
#import "OlapicStreamEntity.h"
#import "OlapicCategoryEntity.h"
#import "OlapicWidgetInstanceEntity.h"

#pragma mark - Include handlers files

#import "OlapicCustomerHandler.h"
#import "OlapicMediaHandler.h"
#import "OlapicUploaderHandler.h"
#import "OlapicStreamHandler.h"
#import "OlapicCategoryHandler.h"
#import "OlapicWidgetInstanceHandler.h"
/**
 *  The different type of endpoints where the SDK can connect
 */
typedef NS_ENUM(NSInteger, OlapicEndpointType){
    /**
     * Gets just the customer information
     */
    OlapicEndpointTypeDefault = 0,
    /**
     * Gets the customer and a media list with its media
     */
    OlapicEndpointTypeCustomerMedia = 1,
    /**
     * Gets the customer and a category media list
     */
    OlapicEndpointTypeCategoryMedia = 2,
    /**
     * Gets the customer and a stream media list
     */
    OlapicEndpointTypeStreamMedia = 3,
    /**
     * Gets the customer and a stream object
     */
    OlapicEndpointTypeStream = 4,
    /**
     * Gets the customer and a category object
     */
    OlapicEndpointTypeCategory = 5,
    /**
     * Gets the customer and search for a specific stream
     */
    OlapicEndpointTypeStreamSearch = 6,
    /**
     * Gets the customer and search for a specific category
     */
    OlapicEndpointTypeCategorySearch = 7,
    /**
     * Gets the customer and all the objects related to a widget instance
     */
    OlapicEndpointTypeWidgetInstance = 8
};
/**
 *  The main singleton object for the SDK
 */
@interface OlapicSDK : NSObject

#pragma mark - Constructor
/**-----------------------------------------------------------------------------
 * @name Initializer
 * -----------------------------------------------------------------------------
 */
/**
 *  Get the singleton shared instance
 *
 *  @return The shared instance
 *  @since  v1.0
 */
+(instancetype)sharedOlapicSDK;
/**-----------------------------------------------------------------------------
 * @name Connection
 * -----------------------------------------------------------------------------
 */
/**
 *  Create the initial connection between the application and the API
 *
 *  @param auth    The authorization key for the API
 *  @param success A callback block for when the application successfully connects
 *  @param failure A callback block for when the connection fails
 *  @since v1.0
 */
-(void)connectWithCustomerAuthKey:(NSString *)auth onSuccess:(void (^)(OlapicCustomerEntity *customer))success onFailure:(void (^)(NSError *error))failure;
/**
 *  Create the initial connection between the application and the API
 *
 *  @param auth       The authorization key for the API
 *  @param success    A callback block for when the application successfully connects
 *  @param failure    A callback block for when the connection fails
 *  @param endpoint   Each one of this endpoint will have different responses.
 *
 *  - OlapicEndpointTypeDefault
 *  - OlapicEndpointTypeCustomerMedia
 *  - OlapicEndpointTypeCategoryMedia
 *  - OlapicEndpointTypeStreamMedia
 *  - OlapicEndpointTypeStream
 *  - OlapicEndpointTypeCategory
 *  - OlapicEndpointTypeStreamSearch
 *  - OlapicEndpointTypeCategorySearch
 *  - OlapicEndpointTypeWidgetInstance
 *
 *  @param parameters The available parameteres are:
 *
 *  - sort: The sorting for the media list
 *  - count: The limit of results per request
 *  - tag_key: The string to search streams or categories
 *  - customer: The customer ID
 *  - stream: The stream ID
 *  - category: The category ID
 *  - delegate: The pointer
 *  - widget_instance: The widget instance hash
 *
 *  @since            v1.0
 */
-(void)connectWithCustomerAuthKey:(NSString *)auth onSuccess:(void (^)(NSDictionary *response))success onFailure:(void (^)(NSError *error))failure toEndpoint:(OlapicEndpointType)endpoint withParameters:(NSDictionary *)parameters;

#pragma mark - Core customization
/**-----------------------------------------------------------------------------
 * @name Customization
 * -----------------------------------------------------------------------------
 */
/**
 *  Change the initial endpoint for the API
 *
 *  @param url The new URL
 *  @since v1.0
 */
-(void)setBaseURL:(NSString *)url;
/**
 *  Get the current endpoint for the API
 *
 *  @return The URL
 *  @since  v1.0
 */
-(NSString *)getBaseURL;

#pragma mark - Rest
/**-----------------------------------------------------------------------------
 * @name REST
 * -----------------------------------------------------------------------------
 */
/**
 *  Get access to the rest client
 *
 *  @return The object for the rest client
 *  @since  v1.0
 */
-(OlapicRestClient *)rest;
#pragma mark - Customer
/**-----------------------------------------------------------------------------
 * @name Customer
 * -----------------------------------------------------------------------------
 */
/**
 *  Get access to the current customer entity
 *
 *  @return The object for the customer
 *  @since  v1.0
 */
-(OlapicCustomerEntity *)customer;

#pragma mark - Handlers
/**-----------------------------------------------------------------------------
 * @name Handlers
 * -----------------------------------------------------------------------------
 */
/**
 *  Get access to the media handler object
 *
 *  @return The media handler
 *  @since  v1.0
 */
-(OlapicMediaHandler *)media;

/**
 *  Get access to the uploader handler object
 *
 *  @return The uploader handler
 *  @since  v1.0
 */
-(OlapicUploaderHandler *)uploaders;

/**
 *  Get access to the stream handler object
 *
 *  @return The stream handler
 *  @since  v1.0
 */
-(OlapicStreamHandler *)streams;

/**
 *  Get access to the category handler object
 *
 *  @return The category handler
 *  @since  v1.0
 */
-(OlapicCategoryHandler *)categories;

/**
 *  Get access to the customer handler object
 *
 *  @return The customer handler
 *  @since  v1.0
 */
-(OlapicCustomerHandler *)customers;

/**
 *  Get access to the widget instances handler object
 *
 *  @return The widget instance handler
 *  @since  v1.0
 */
-(OlapicWidgetInstanceHandler *)widgetInstances;
#pragma mark - Others
/**-----------------------------------------------------------------------------
 * @name Utils
 * -----------------------------------------------------------------------------
 */
/**
 *  Prepare a URL for a specific endpoint
 *
 *  @param type    The URL type
 *  @param context The information to be used to build the URL
 *
 *  @return A URL ready to be used with the API
 *  @since  v1.0
 */
-(NSString *)prepareURLWithType:(NSString *)type context:(NSDictionary *)context;
/**
 *  Check if the initial connection was made
 *
 *  @return That
 *  @since  v1.0
 */
-(BOOL)connected;
/**
 *  Get a standard NSError to inform that the initial connection
 *  couldn't be made
 *
 *  @return The error with the reason why the connection failed
 *  @since  v1.0
 */
-(NSDictionary *)getDisconnectedError;
/**-----------------------------------------------------------------------------
 * @name Log
 * -----------------------------------------------------------------------------
 */
/**
 *  Turn on a flag that starts showing all the URLs being
 *  called by the SDK on the console
 *  @since v1.0
 */
-(void)startLoggingURLs;
/**
 *  Log a URL request on the console
 *
 *  @param url  The URL to log
 *  @param done If its NO, the request just started, if its YES, the request just finished
 *  @since v1.0
 */
-(void)logURL:(NSString *)url done:(BOOL)done;


@end
