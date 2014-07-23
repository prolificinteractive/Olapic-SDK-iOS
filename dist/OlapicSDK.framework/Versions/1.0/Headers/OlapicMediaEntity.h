//
//  MediaEntity.h
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

#import "OlapicEntity.h"
#import "OlapicMediaHandler.h"

@class OlapicUploaderEntity;
/**
 *  Represents media on the SDK
 */
@interface OlapicMediaEntity : OlapicEntity {
    /**
     *  The media uploader information
     */
    OlapicUploaderEntity *uploader;
    /**
     *  The size of the original image (in case it's not a video)
     */
    CGSize originalSize;
}
/**
 *  The media uploader information
 */
@property (nonatomic, strong) OlapicUploaderEntity *uploader;
/**
 *  The size of the original image (in case it's not a video)
 */
@property (nonatomic) CGSize originalSize;
/**-----------------------------------------------------------------------------
 * @name Utils
 * -----------------------------------------------------------------------------
 */
/**
 *  Check if the media is a video
 *
 *  @return BOOL
 *  @since v1.0
 */
-(BOOL)isVideo;
/**
 *  Get the URL of one of the sizes of the media if it's an image
 *
 *  @param size The image size
 *
 *  @return NSString with the image URL
 *  @since v1.0
 */
-(NSString *)getMediaURLForImageSize:(OlapicMediaImageSize)size;
/**-----------------------------------------------------------------------------
 * @name Uploader
 * -----------------------------------------------------------------------------
 */
/**
 *  Get an uploader entity from a media
 *
 *  @param success A callback block for when the uploader is successfully retrieved
 *  @param failure A callback block for when the SDK can't get the uploader
 *  @since v1.0
 */
-(void)getUploader:(void (^)(OlapicUploaderEntity *uploader))success onFailure:(void (^)(NSError *error))failure;
/**-----------------------------------------------------------------------------
 * @name UI
 * -----------------------------------------------------------------------------
 */
/**
 *  Download a media image to an UIImage
 *
 *  @param size    The media image size
 *  @param success A callback block for when the image is successfully retrieved
 *  @param failure A callback block for when the SDK can't get the image
 *  @since v1.0
 */
-(void)getImageWithSize:(OlapicMediaImageSize)size onSuccess:(void (^)(NSData *mediaData,UIImage *mediaImage))success onFailure:(void (^)(NSError *error))failure;
/**-----------------------------------------------------------------------------
 * @name Report
 * -----------------------------------------------------------------------------
 */
/**
 *  Report this media
 *
 *  @param metadata A list with the report information
 *
 *  - email: The email of the user who wants to report the media
 *  - reason: The reason why the media will be reported
 *
 *  @param success  A callback block for when the media is successfully reported
 *  @param failure  A callback block for when the SDK can't report the media
 *  @since v1.0
 */
-(void)report:(NSDictionary *)metadata onSuccess:(void (^)(void))success onFailure:(void (^)(NSError *error))failure;
/**-----------------------------------------------------------------------------
 * @name Streams
 * -----------------------------------------------------------------------------
 */
/**
 *  Get streams related to this media
 *
 *  @param success A callback block for when the streams are successfully retrieved
 *  @param failure A callback block for when the SDK can't get the streams
 *  @since v1.0
 */
-(void)getRelatedStreams:(void(^)(NSArray *streams))success onFailure:(void (^)(NSError *error))failure;

@end
