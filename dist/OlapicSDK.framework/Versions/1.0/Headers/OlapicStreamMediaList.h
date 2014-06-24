//
//  OlapicStreamMediaList.h
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

#import "OlapicMediaList.h"

@class OlapicStreamEntity;
/**
 *  List all the media objects from a specific stream
 */
@interface OlapicStreamMediaList : OlapicMediaList{
    /**
     *  The ID of the stream from where the list will get the media
     */
    NSString *listStreamId;
    /**
     *  The object from the stream from where the list will get the media
     */
    OlapicStreamEntity *listStream;
}

/**
 *  The ID of the stream from where the list will get the media
 */
@property (nonatomic,strong) NSString *listStreamId;
/**
 *  The object from the stream from where the list will get the media
 */
@property (nonatomic,strong) OlapicStreamEntity *listStream;
/**-----------------------------------------------------------------------------
 * @name Initializer with object
 * -----------------------------------------------------------------------------
 */
/**
 *  Initialize using a stream entity as reference
 *
 *  @param stream         The stream entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *
 *  @return The OlapicStreamMediaList instance
 *  @since v1.0
 */
-(id)initForStream:(OlapicStreamEntity *)stream delegate:(id <OlapicMediaListDelegate>__weak)delegateObject;

/**
 *  Initialize using a stream entity as reference and
 *  set the sorting type
 *
 *  @param stream         The stream entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *  @param sort           The sorting type
 *
 *  @return The OlapicStreamMediaList instance
 *  @since v1.0
 */
-(id)initForStream:(OlapicStreamEntity *)stream delegate:(id <OlapicMediaListDelegate>__weak)delegateObject sort:(OlapicMediaListSortingType)sort;

/**
 *  Initialize using a stream entity as reference, changing
 *  the sorting type and the amount of media per page that
 *  are going to be downloaded
 *
 *  @param stream         The stream entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *  @param sort           The sorting type
 *  @param perPage        The number of media per page
 *
 *  @return The OlapicStreamMediaList instance
 *  @since v1.0
 */
-(id)initForStream:(OlapicStreamEntity *)stream delegate:(id <OlapicMediaListDelegate>__weak)delegateObject sort:(OlapicMediaListSortingType)sort mediaPerPage:(NSInteger)perPage;

/**
 *  Initialize using a stream entity as reference, changing
 *  the sorting type, the amount of media per page and the offset
 *
 *  @param stream         The stream entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *  @param sort           The sorting type
 *  @param perPage        The number of media per page
 *  @param offset         The offset to change the page
 *
 *  @return The OlapicStreamMediaList instance
 *  @since v1.0
 */
-(id)initForStream:(OlapicStreamEntity *)stream delegate:(id <OlapicMediaListDelegate>__weak)delegateObject sort:(OlapicMediaListSortingType)sort mediaPerPage:(NSInteger)perPage offset:(NSInteger)offset;
/**-----------------------------------------------------------------------------
 * @name Initializer with URL
 * -----------------------------------------------------------------------------
 */
/**
 *  Initialize using a stream ID and its URL
 *
 *  @param streamId       The stream ID
 *  @param delegateObject The reference to the delegate object
 *  @param URL            The API URL
 *
 *  @return The OlapicStreamMediaList instance
 *  @since v1.0
 */
-(id)initWithStreamId:(NSString *)streamId delegate:(id <OlapicMediaListDelegate>__weak)delegateObject andURL:(NSString *)URL;

/**
 *  Initialize using a stream ID and its URL, but
 *  also changing the amount of media per page that
 *  are going to be downloaded
 *
 *  @param streamId       The stream ID
 *  @param delegateObject The reference to the delegate object
 *  @param URL            The API URL
 *  @param perPage        The number of media per page
 *
 *  @return The OlapicStreamMediaList instance
 *  @since v1.0
 */
-(id)initWithStreamId:(NSString *)streamId delegate:(id <OlapicMediaListDelegate>__weak)delegateObject andURL:(NSString *)URL mediaPerPage:(NSInteger)perPage;

/**
 *  Initialize using stream ID and its URL, but
 *  also changing the amount of media per page
 *  and the offset
 *
 *  @param streamId       The stream ID
 *  @param delegateObject The reference to the delegate object
 *  @param URL            The API URL
 *  @param perPage        The number of media per page
 *  @param offset         The offset to change the page
 *
 *  @return The OlapicStreamMediaList instance
 *  @since v1.0
 */
-(id)initWithStreamId:(NSString *)streamId delegate:(id <OlapicMediaListDelegate>__weak)delegateObject andURL:(NSString *)URL mediaPerPage:(NSInteger)perPage offset:(NSInteger)offset;

@end