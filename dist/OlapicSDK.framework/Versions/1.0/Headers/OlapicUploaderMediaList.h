//
//  OlapicUploaderMediaList.h
//  OlapicSDKFramework
//  https://github.com/Olapic/Olapic-SDK-iOS
//
//  Created by The Olapic Team on 6/2/14.
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

#import "OlapicMediaList.h"

@class OlapicUploaderEntity;
/**
 *  List all the media objects from a specific uploader
 */
@interface OlapicUploaderMediaList : OlapicMediaList {
    /**
     *  The uploader from where the list will get the media
     */
    OlapicUploaderEntity *listUploader;
}

@property (nonatomic,strong) OlapicUploaderEntity *listUploader;
/**-----------------------------------------------------------------------------
 * @name Initializer
 * -----------------------------------------------------------------------------
 */
/**
 *  Initialize using a uploader entity as reference
 *
 *  @param uploader       The uploader entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *
 *  @return The OlapicUploaderMediaList instance
 *  @since v1.0
 */
-(id)initForUploader:(OlapicUploaderEntity *)uploader delegate:(id <OlapicMediaListDelegate>__weak)delegateObject;
/**
 *  Initialize using a uploader entity as reference and
 *  changing the amount of media per page that are going
 *  going to be downloaded
 *
 *  @param uploader       The uploader entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *  @param perPage        The number of media per page
 *
 *  @return The OlapicUploaderMediaList instance
 *  @since v1.0
 */
-(id)initForUploader:(OlapicUploaderEntity *)uploader delegate:(id <OlapicMediaListDelegate>__weak)delegateObject mediaPerPage:(NSInteger)perPage;

/**
 *  Initialize using a uploader entity as reference,
 *  changing the amount of media per page that are
 *  going to be downloaded and set an offset
 *
 *  @param uploader       The uploader entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *  @param perPage        The number of media per page
 *  @param offset         The offset to change the page
 *
 *  @return The OlapicUploaderMediaList instance
 *  @since v1.0
 */
-(id)initForUploader:(OlapicUploaderEntity *)uploader delegate:(id <OlapicMediaListDelegate>__weak)delegateObject mediaPerPage:(NSInteger)perPage offset:(NSInteger)offset;

@end
