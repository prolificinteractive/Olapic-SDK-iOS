Olapic SDK for iOS
====================

Olapic’s iOS SDK contains code samples and documentation for leveraging the Olapic platform within an iOS app. The SDK makes it easier for iOS developers to build applications that can take advantage of Olapic’s core offerings and capabilities.

To get immediate access to the SDK navigate to the `dist/` folder, which contains the `OlapicSDK.framework` file with the latest version of the SDK.

##What can you do with the Olapic SDK:

###Get Media

The SDK allows the capability of getting content at multiple different levels, these include:

- Customer Level, which returns all media across the entire customer account.
- Individual Media Level, which returns a single media.
- Stream Level, which returns all media for a specific stream.
- Category Level, which returns media in a specific category.
 
Media can be received in a variety of different orders including; 

- Most Recent 
- Shufled
- Highest ranked by PhotoRank
- Highest Click Through Rate

###Upload Media

The SDK allows the capability of uploading UGC directly into the Olapic platform. When media is uploaded the API will return the user and media ID associated to that UGC.

- Directly uploaded content has been seen to perform better and be of higher quality.

###Report Media

To best comply with copyright laws and regulations Olapic provides an easy method to allow users to report media that is under copyright or inappropriate. Our SDK provides easy access to this functionality so that you app can easily stay in compliance.


###Manage Streams/Categories

Streams are a big part of the Olapic platform and because of this we’ve made managing streams through the SDK simple. You’ll be able to easily:

- Get a list of all Streams/Categories
- Get a specific Stream/Category

###Users

If you are looking to feature any specific users, Olapic’s SDK will provide the tools to retrieve specific users UGC and display that content. This can be very helpful for use on user profile pages or when dealing with ambassador or celebrity content.

##Requirements

- iOS 7.0+
- ARC
- An Olapic account and credentials

##Installation

###Authentication and Authorization:

Olapic API Key can be found within your account under the `Settings Tab >>> API Key`. Once you have API key drag the `OlapicSDK.framework` into your project. The next example will show you how to go through client authentication.


###Client Authentication

First import the `<OlapicSDK/OlapicSDK.h>` into your file, then make a connection with the Olapic API. On the success callback of this method you’ll be able to start using the SDK.

```
OlapicSDK *olapic = [OlapicSDK sharedOlapicSDK];
[olapic connectWithCustomerAuthKey:AUTH_TOKEN_HERE onSuccess:^(OlapicCustomerEntity *customer){
	NSLog("%@", customer);
} onFailure:^(NSError *error){
	NSLog("%@", error);
}];
```

*Note: Replace AUTH_TOKEN_HERE with your Olapic token.*

###Get a list of media

Once the connection has been completed, the success callback will return the Customer entity, by using this entity you can get a list of media objects:

```
list = [[OlapicCustomerMediaList alloc] initForCustomer:customer delegate:self sort:SORTING_TYPE mediaPerPage:NUMBER_OF_MEDIAS_PER_PAGE];
```

The `list` variable should be an `OlapicCustomerMediaList` object, the `SORTING_TYPE` available are *[OlapicMediaListSortingTypeRecent, OlapicMediaListSortingTypeShuffled, OlapicMediaListSortingTypePhotorank, OlapicMediaListSortingTypeRated]*.

After this you need to use `[list startFetching];` to get all the media, this will execute the delegate methods with the information.

```
-(void)OlapicMediaList:(OlapicMediaList *)mediaList didLoadMedia:(NSArray *)media withLinks:(NSDictionary *)links;
-(void)OlapicMediaList:(OlapicMediaList *)mediaList didReceiveAnError:(NSError *)error
```

##Documentation

You can find the documentation on every class on [http://docs.photorank.me/ios/](http://docs.photorank.me/ios/).

##Start Making Amazing Apps

Once the SDK is installed and ready to go, start using it from any of your implementation files by adding the Olapic SDK header file. To import headers include the following line to your code:

`#import “OlapicSDK.h”`

##License	

The Olapic SDK for iOS is available under the MIT license. See the LICENSE file for more info.
