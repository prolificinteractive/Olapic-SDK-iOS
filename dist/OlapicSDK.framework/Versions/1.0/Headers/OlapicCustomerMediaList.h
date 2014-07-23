//
//  OlapicCustomerMediaList.h
//  OlapicSDKFramework
//  https://github.com/Olapic/Olapic-SDK-iOS
//
//  Created by The Olapic Team on 4/18/14.
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

@class OlapicCustomerEntity;
/**
 *  List all the media objects from an specific customer
 */
@interface OlapicCustomerMediaList : OlapicMediaList{
    /**
     *  A reference to the customer from where the list will
     *  get the media. Its a weak reference because, there's
     *  only one customer object on the SDK, and its the one
     *  you get with ``[[OlapicSDK sharedOlapicSDK] customer]``
     */
    OlapicCustomerEntity *__weak listCustomer;
}

@property (nonatomic,weak) OlapicCustomerEntity *__weak listCustomer;
/**-----------------------------------------------------------------------------
 * @name Initializer
 * -----------------------------------------------------------------------------
 */
/**
 *  Initialize using a customer entity as reference
 *
 *  @param customer       The customer entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *
 *  @return               The OlapicCustomerMediaList instance
 *  @since                v1.0
 */
-(id)initForCustomer:(OlapicCustomerEntity *)customer delegate:(id <OlapicMediaListDelegate>__weak)delegateObject;
/**
 *  Initialize using a customer entity as reference and
 *  set the sorting type
 *
 *  @param customer       The customer entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *  @param sort           The sorting type
 *
 *  @return               The OlapicCustomerMediaList instance
 *  @since                v1.0
 */
-(id)initForCustomer:(OlapicCustomerEntity *)customer delegate:(id <OlapicMediaListDelegate>__weak)delegateObject sort:(OlapicMediaListSortingType)sort;
/**
 *  Initialize using a customer entity as reference, changing
 *  the sorting type and the amount of media per page that
 *  are going to be downloaded
 *
 *  @param customer       The customer entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *  @param sort           The sorting type
 *  @param perPage        The number of media per page
 *
 *  @return               The OlapicCustomerMediaList instance
 *  @since                v1.0
 */
-(id)initForCustomer:(OlapicCustomerEntity *)customer delegate:(id <OlapicMediaListDelegate>__weak)delegateObject sort:(OlapicMediaListSortingType)sort mediaPerPage:(NSInteger)perPage;
/**
 *  Initialize using a customer entity as reference, changing
 *  the sorting type, the amount of media per page and the offset
 *
 *  @param customer       The customer entity to use as reference
 *  @param delegateObject The reference to the delegate object
 *  @param sort           The sorting type
 *  @param perPage        The number of media per page
 *  @param offset         The offset to change the page
 *
 *  @return               The OlapicCustomerMediaList instance
 *  @since                v1.0
 */
-(id)initForCustomer:(OlapicCustomerEntity *)customer delegate:(id <OlapicMediaListDelegate>__weak)delegateObject sort:(OlapicMediaListSortingType)sort mediaPerPage:(NSInteger)perPage offset:(NSInteger)offset;


@end
