//
//  OlapicMapObject.h
//  OlaMap
//  https://github.com/Olapic/Olapic-SDK-iOS
//
//  Documentation
//  http://docs.photorank.me/ios
//
//  Created by The Olapic Team on 5/14/14.
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
#import <MapKit/MKAnnotation.h>
#import <MapKit/MapKit.h>

@class OlapicMediaEntity;
@class OlapicAsyncImageView;
@protocol OlapicMapObjectDelegate;
/**
 *  Show a map object using MapKit and JPSThumbnailAnnotation
 *  to show the media entities
 */
@interface OlapicMapObject : NSObject<MKMapViewDelegate>{
    /**
     *  A delegate object for the OlapicMapObjectDelegate methods
     */
    id  <OlapicMapObjectDelegate>__weak delegate;
    /**
     *  A list with the media entities to use on the map
     */
    NSArray *annotations;
    /**
     *  A list with the annotations object that are going to the map
     */
    NSMutableArray *annotationsObjects;
    /**
     *  The 'real' map object
     */
    MKMapView *map;
    /**
     *  The map size and position
     */
    CGRect frame;
}

@property (nonatomic,weak) id  <OlapicMapObjectDelegate>__weak delegate;
@property (nonatomic,strong) NSArray *annotations;
@property (nonatomic,strong) NSMutableArray *annotationsObjects;
@property (nonatomic,strong) MKMapView *map;
@property (nonatomic) CGRect frame;
/**
 *  Set the media entities and the delegate object. This method will
 *  check the array and only save the ones with valid coordinates
 *
 *  @param mapAnnotations A list of OlapicMediaEntiy objects
 *  @param delegateObject An object implementing the OlapicMapObjectDelegate protocol
 */
-(void)setMapAnnotations:(NSArray *)mapAnnotations andDelegate:(id<OlapicMapObjectDelegate>)delegateObject;
/**
 *  Add the map on a selected view
 *
 *  @param view The view where the map is going to be added
 */
-(void)addOnView:(UIView *)view;
/**
 *  Read the annotations, create the objects and send
 *  them to the map
 */
-(void)build;
/**
 *  Change the map frame
 *
 *  @param rect The new frame
 */
-(void)setFrame:(CGRect)rect;

@end
/**
 *  A simple protocol to listen for when a user
 *  selects an annotation
 */
@protocol OlapicMapObjectDelegate <NSObject>
@optional
/**
 *  The user did select a media entity from a map annotation
 *
 *  @param mapObject The map itself
 *  @param media     The selected media entity
 *  @param image     The image for the annotation
 */
-(void)mapObject:(OlapicMapObject *)mapObject didSelectMedia:(OlapicMediaEntity *)media fromImage:(OlapicAsyncImageView *)image;
@end