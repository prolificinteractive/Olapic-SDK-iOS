//
//  OlapicMediaList.h
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

#import <Foundation/Foundation.h>
/**
 *  The different type of sorting supported by lists
 */
typedef NS_ENUM(NSInteger, OlapicMediaListSortingType){
    /**
     *  Ordered by date, the newer first
     */
    OlapicMediaListSortingTypeRecent = 0,
    /**
     *  Oredered randomly
     */
    OlapicMediaListSortingTypeShuffled = 1,
    /**
     *  Ordered based on conversion
     */
    OlapicMediaListSortingTypePhotorank = 2,
    /**
     *  Ordered by rating
     */
    OlapicMediaListSortingTypeRated = 3
};
@protocol OlapicMediaListDelegate;
@class OlapicSDK;
/**
 *  The basic interface for media lists objects
 */
@interface OlapicMediaList : NSObject{
    /**
     *  The delegate object
     */
    id <OlapicMediaListDelegate>__weak delegate;
    /**
     *  The initial API URL from where the list will get the media objects
     */
    NSString *initialURL;
    /**
     *  The API URL of the last request. This may change depending on the pagination.
     */
    NSMutableString *currentURL;
    /**
     *  The API URL to the previous page
     */
    NSMutableString *prevURL;
    /**
     *  The API URL to the next page
     */
    NSMutableString *nextURL;
    /**
     *  The list sorting type
     */
    OlapicMediaListSortingType sorting;
    /**
     *  How many media objects per page will be loaded
     */
    NSInteger mediaPerPage;
    /**
     *  The list pagination current offset
     */
    NSInteger currentOffset;
    /**
     *  A list with the pages from the API.
     *  Each item will be a dictionary with the following keys:
     *  - links: The API pagination links
     *  - media: An array with all the media objects for that page
     */
    NSMutableArray *pages;
}

/**
 *  The delegate object
 */
@property (nonatomic,weak) id <OlapicMediaListDelegate>__weak delegate;
/**
 *  The initial API URL from where the list will get the media objects
 */
@property (nonatomic,strong) NSString *initialURL;
/**
 *  The API URL of the last request This may change depending on the pagination
 */
@property (nonatomic,strong) NSMutableString *currentURL;
/**
 *  The API URL to the previous page
 */
@property (nonatomic,strong) NSMutableString *prevURL;
/**
 *  The API URL to the next page
 */
@property (nonatomic,strong) NSMutableString *nextURL;
/**
 *  The list sorting type
 */
@property (nonatomic) OlapicMediaListSortingType sorting;
/**
 *  How many media objects per page will be loaded
 */
@property (nonatomic) NSInteger mediaPerPage;
/**
 *  The list pagination current offset
 */
@property (nonatomic) NSInteger currentOffset;
/**
 *  A list with the pages from the API
 *  Each item will be a dictionary with the follwing keys:
 *  - links: The API pagination links
 *  - media: An array with all the media objects for that page
 */
@property (nonatomic,strong) NSMutableArray *pages;
/**-----------------------------------------------------------------------------
 * @name Utils
 * -----------------------------------------------------------------------------
 */
/**
 *  Get string key for a sorting type
 *
 *  The returned key will be used to call the ``get``
 *  method of a OlapicEntity, so if you send
 *  OlapicMediaListSortingTypeShuffled, you'll get "media/shuffled"
 *
 *  @param stype OlapicMediaListSortingType
 *
 *  @return The string with the key
 *  @since  v1.0
 */
+(NSString *)getKeyForSortingType:(OlapicMediaListSortingType)stype;
/**
 *  Get the OlapicSDK reference
 *
 *  @return The OlapicSDK
 *  @since  v1.0
 */
-(OlapicSDK *)getSDK;
/**-----------------------------------------------------------------------------
 * @name Initializer
 * -----------------------------------------------------------------------------
 */
/**
 *  When the SDK is initialized using a specific endpoint, this method
 *  will take care of reading the JSON and create the list based on
 *  that information
 *
 *  This method has its own implementation for each subclass
 *
 *  @param data The received information
 *
 *  @return An OlapicMediaList subclass instance
 */
-(id)initFromConnectionData:(NSDictionary *)data;
/**-----------------------------------------------------------------------------
 * @name Connection
 * -----------------------------------------------------------------------------
 */
/**
 *  Start downloading media objects
 *  @since v1.0
 */
-(void)startFetching;
/**-----------------------------------------------------------------------------
 * @name Pagination
 * -----------------------------------------------------------------------------
 */
/**
 *  Check if there's a previous page that can be loaded
 *
 *  @return If a previous page exists
 *  @since v1.0
 */
-(BOOL)canLoadPreviousPage;
/**
 *  Load the previous page
 *
 *  @since v1.0
 */
-(void)loadPreviousPage;
/**
 *  Check if there's a new page that can be loaded
 *
 *  @return If a new page can be loaded
 *  @since  v1.0
 */
-(BOOL)canLoadNextPage;
/**
 *  Load a new page
 *  
 *  @since v1.0
 */
-(void)loadNextPage;
/**-----------------------------------------------------------------------------
 * @name Extras
 * -----------------------------------------------------------------------------
 */
/**
 *  Check if the list is currenly downloading media
 *
 *  @return If the list is downloading
 *  @since  v1.0
 */
-(BOOL)fetching;
/**
 *  Get the current page information. A dictionary with
 *  the following keys:
 *  - links: The API pagination links
 *  - media: An array with all the media objects for that page
 *
 *  @return The page information
 *  @since  v1.0
 */
-(NSDictionary *)getCurrentPage;
/**
 *  Get the current page's media objects
 *
 *  @return An array of OlapicMediaEntity objects
 *  @since  v1.0
 */
-(NSArray *)getCurrentPageMedia;
/**
 *  Get all the media currently saved on the list
 *
 *  @return An array of OlapicMediaEntity objects
 *  @since  v1.0
 */
-(NSArray *)getMedia;

@end
/**
 *  The protocol that handles the basic media list events
 */
@protocol OlapicMediaListDelegate <NSObject>
/**
 *  Every time a page is loaded, even if the pagination is
 *  going back, this method is called
 *
 *  @param mediaList The list object that generated the event
 *  @param media     A list with the loaded media objects
 *  @param links     The API pagination links
 *  @since v1.0
 */
-(void)OlapicMediaList:(OlapicMediaList *)mediaList didLoadMedia:(NSArray *)media withLinks:(NSDictionary *)links;
/**
 *  This is called when the list is trying to load media objects, but finds an error
 *
 *  @param mediaList The list object that generated the event
 *  @param error     The error containing the reason why the request failed
 *  @since v1.0
 */
-(void)OlapicMediaList:(OlapicMediaList *)mediaList didReceiveAnError:(NSError *)error;
@optional
/**
 *  This method is called only when the list is requesting
 *  new media objects from the API
 *
 *  @param mediaList The list object that generated the event
 *  @param media     A list with the loaded media objects
 *  @param links     The API pagination links
 *  @since v1.0
 */
-(void)OlapicMediaList:(OlapicMediaList *)mediaList didLoadNewMedia:(NSArray *)media withLinks:(NSDictionary *)links;
/**
 *  This is called only the first time the lists download
 *  media objects
 *
 *  @param mediaList The list object that generated the event
 *  @param media     A list with the loaded media objects
 *  @param links     The API pagination links
 *  @since v1.0
 */
-(void)OlapicMediaList:(OlapicMediaList *)mediaList didLoadMediaForTheFirstTime:(NSArray *)media withLinks:(NSDictionary *)links;
/**
 *  This is called when the list is trying to load media objects for the
 *  first time but finds an error
 *
 *  @param mediaList The list object that generated the event
 *  @param error     The error containing the reason why the request failed
 *  @since v1.0
 */
-(void)OlapicMediaList:(OlapicMediaList *)mediaList didReceiveAnErrorForTheFirstTime:(NSError *)error;
/**
 *  This is called every time the list offset changes.
 *
 *  @param mediaList  The list object that generated the event
 *  @param newOffset  The list new offset
 *  @param prevOffset The list previous offset
 */
-(void)OlapicMediaList:(OlapicMediaList *)mediaList didChangeOffset:(NSNumber*)newOffset fromPreviousOffset:(NSNumber*)prevOffset;

@end
