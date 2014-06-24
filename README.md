Olapic SDK for iOS
====================

Here is the official SDK for iOS made it by Olapic. In this repository you will find the latests version of the framework and a bunch of code samples to lear how to use it.

The `dist/` folder contain the `OlapicSDK.framework` file with the latest version of the SDK.


##Requirements

- iOS 7.0+
- ARC

##Installation

Drag the `OlapicSDK.framework` into your project.

##Quick examples

###Client Authentication

First import the `<OlapicSDK/OlapicSDK.h>` in your file, then made the connection with the API. On the success callback of this method you can start using the SDK.

```
OlapicSDK *olapic = [OlapicSDK sharedOlapicSDK];
[olapic connectWithCustomerAuthKey:AUTH_TOKEN_HERE onSuccess:^(OlapicCustomerEntity *customer){
	NSLog("%@", customer);
} onFailure:^(NSError *error){
	NSLog("%@", error);
}];
```

*Note: Replace AUTH_TOKEN_HERE for the correct token.*

###Get a list of media

Once the connect has been completed, the success callbackk will return the Customer entity, using the the entity you can get a list of media objects:

```
list = [[OlapicCustomerMediaList alloc] initForCustomer:customer delegate:self sort:SORTING_TYPE mediaPerPage:NUMBER_OF_MEDIAS_PER_PAGE];
```

The `list` variable should be a `OlapicCustomerMediaList` object, the `SORTING_TYPE` avialble are *[OlapicMediaListSortingTypeRecent, OlapicMediaListSortingTypeShuffled, OlapicMediaListSortingTypePhotorank, OlapicMediaListSortingTypeRated]*.

After this you need to use `[list startFetching];` to get all the media, this will execute the delagate methods with the information.

```
-(void)OlapicMediaList:(OlapicMediaList *)mediaList didLoadMedia:(NSArray *)media withLinks:(NSDictionary *)links;
-(void)OlapicMediaList:(OlapicMediaList *)mediaList didReceiveAnError:(NSError *)error
```

##Documentation

You can find the documentation to every class on [http://docs.photorank.me/ios/](http://docs.photorank.me/ios/).

##License	

The Olapic SDK for iOS is available under the MIT license. See the LICENSE file for more info.