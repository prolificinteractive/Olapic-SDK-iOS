//
//  OlapicCategoryMediaList.h
//  OlapicSDKFramework
//  https://github.com/Olapic/Olapic-SDK-iOS
//
//  Created by The Olapic Team on 5/5/14.
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

@class OlapicCategoryEntity;
/**
 *  List all the media objects from a specific category
 */
@interface OlapicCategoryMediaList : OlapicMediaList{
    /**
     *  The category from where the list will get the media
     */
    OlapicCategoryEntity *listCategory;
    /**
     *  The ID of the category that the list will use to get the media
     */
    NSString *listCategoryId;    
}
/**
 *  The category from where the list will get the media
 */
@property (nonatomic,strong) OlapicCategoryEntity *listCategory;
/**
 *  The ID of the category that the list will use to get the media
 */
@property (nonatomic,strong) NSString *listCategoryId;
/**-----------------------------------------------------------------------------
 * @name Initializer with Object
 * -----------------------------------------------------------------------------
 */
/**
 *  Initialize using a category entity as reference
 *
 *  @param category       The category entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *
 *  @return The OlapicCategoryMediaList instance
 *  @since v1.0
 */
-(id)initForCategory:(OlapicCategoryEntity *)category delegate:(id <OlapicMediaListDelegate>__weak)delegateObject;
/**
 *  Initialize using a category entity as reference set
 *  the sorting type
 *
 *  @param category       The category entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *  @param sort           The sorting type
 *
 *  @return The OlapicCategoryMediaList instance
 *  @since v1.0
 */
-(id)initForCategory:(OlapicCategoryEntity *)category delegate:(id <OlapicMediaListDelegate>__weak)delegateObject sort:(OlapicMediaListSortingType)sort;
/**
 *  Initialize using a category entity as reference, with
 *  the sorting type and the number of media per page that
 *  are to be retrieved
 *
 *  @param category       The category entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *  @param sort           The sorting type
 *  @param perPage        The number of media per page
 *
 *  @return The OlapicCategoryMediaList instance
 *  @since v1.0
 */
-(id)initForCategory:(OlapicCategoryEntity *)category delegate:(id <OlapicMediaListDelegate>__weak)delegateObject sort:(OlapicMediaListSortingType)sort mediaPerPage:(NSInteger)perPage;
/**
 *  Initialize using a category entity as reference, with
 *  sorting type, amount of media per page and an offset
 *
 *  @param category       The category entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *  @param sort           The sorting type
 *  @param perPage        The number of media per page
 *  @param offset         The offset to change the page
 *
 *  @return The OlapicCategoryMediaList instance
 *  @since v1.0
 */
-(id)initForCategory:(OlapicCategoryEntity *)category delegate:(id <OlapicMediaListDelegate>__weak)delegateObject sort:(OlapicMediaListSortingType)sort mediaPerPage:(NSInteger)perPage offset:(NSInteger)offset;

/**-----------------------------------------------------------------------------
 * @name Initializer with ID and URL
 * -----------------------------------------------------------------------------
 */
/**
 *  Initialize using a category ID and its URL
 *
 *  @param categoryId     The category ID
 *  @param delegateObject The reference to the delegate object
 *  @param URL            The API URL for this category
 *
 *  @return The OlapicCategoryMediaList instance
 *  @since v1.0
 */
-(id)initWithCategoryId:(NSString *)categoryId delegate:(id <OlapicMediaListDelegate>__weak)delegateObject andURL:(NSString *)URL;
/**
 *  Initialize using a category ID and its URL, but
 *  also changing the amount of media per page that
 *  are going to be downloaded
 *
 *  @param categoryId     The category ID
 *  @param delegateObject The reference to the delegate object
 *  @param URL            The API URL for this category
 *  @param perPage        The number of media per page
 *
 *  @return The OlapicCategoryMediaList instance
 *  @since v1.0
 */
-(id)initWithCategoryId:(NSString *)categoryId delegate:(id <OlapicMediaListDelegate>__weak)delegateObject andURL:(NSString *)URL mediaPerPage:(NSInteger)perPage;
/**
 *  Initialize using a category ID and its URL, but
 *  also changing the amount of media per page and
 *  the offset
 *
 *  @param categoryId     The category ID
 *  @param delegateObject The reference to the delegate object
 *  @param URL            The API URL for this category
 *  @param perPage        The number of media per page
 *  @param offset         The offset to change the page
 *
 *  @return The OlapicCategoryMediaList instance
 *  @since v1.0
 */
-(id)initWithCategoryId:(NSString *)categoryId delegate:(id <OlapicMediaListDelegate>__weak)delegateObject andURL:(NSString *)URL mediaPerPage:(NSInteger)perPage offset:(NSInteger)offset;

@end