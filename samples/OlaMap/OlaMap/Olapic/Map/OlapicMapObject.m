//
//  OlapicMapObject.m
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

#import "OlapicMapObject.h"
#import "OlapicAsyncImageView.h"
#import "JPSThumbnailAnnotation.h"
#import <OlapicSDK/OlapicSDK.h>

@implementation OlapicMapObject
@synthesize delegate,annotations,map,frame,annotationsObjects;

/**
 * Class constructor
 */
-(id)init{
    self = [super init];
    if(self){
        annotationsObjects = [[NSMutableArray alloc] init];
        map = [[MKMapView alloc] initWithFrame:CGRectZero];
        [map setMapType:MKMapTypeStandard];
        [map setDelegate:self];
        [map setZoomEnabled:YES];
        [map setScrollEnabled:YES];
    }
    return self;
}
/**
 *  Set the media entities and the delegate object. This method will
 *  check the array and only save the ones with valid coordinates
 *
 *  @param mapAnnotations A list of OlapicMediaEntiy objects
 *  @param delegateObject An object implementing the OlapicMapObjectDelegate protocol
 */
-(void)setMapAnnotations:(NSArray *)mapAnnotations andDelegate:(id<OlapicMapObjectDelegate>)delegateObject{
    NSMutableArray *cleanAnnotations = [[NSMutableArray alloc] init];
    for(int i = 0; i < [mapAnnotations count]; i++){
        OlapicMediaEntity *media = [mapAnnotations objectAtIndex:i];
        NSDictionary *mediaLoc = [media get:@"location"];
        if(mediaLoc != (id)[NSNull null]){
            [cleanAnnotations addObject:media];
        }
    }
    annotations = [[NSArray alloc] initWithArray:cleanAnnotations];
    delegate = delegateObject;
}
/**
 *  Add the map on a selected view
 *
 *  @param view The view where the map is going to be added
 */
-(void)addOnView:(UIView *)view{
    [view addSubview:map];
}
/**
 *  Read the annotations, create the objects and send
 *  them to the map
 */
-(void)build{
    CLLocationCoordinate2D startCoordinates;
    startCoordinates.latitude = 0;
    startCoordinates.longitude = 0;
    NSMutableArray *lats = [[NSMutableArray alloc] init];
    NSMutableArray *lngs = [[NSMutableArray alloc] init];
    float latitude = 0;
    float longitude = 0;
    // Loop the entities
    for(int i = 0; i < [annotations count]; i++){
        OlapicMediaEntity *media = [annotations objectAtIndex:i];
        NSDictionary *mediaLocation = [media get:@"location"];
        latitude = [[mediaLocation valueForKey:@"latitude"] floatValue];
        longitude = [[mediaLocation valueForKey:@"longitude"] floatValue];
        [lats addObject:[[mediaLocation valueForKey:@"latitude"] stringValue]];
        [lngs addObject:[[mediaLocation valueForKey:@"longitude"] stringValue]];
        
        CLLocationCoordinate2D newCoordinates;
        
        newCoordinates.latitude = latitude;
        newCoordinates.longitude = longitude;
        
        JPSThumbnail *npin = [[JPSThumbnail alloc] init];
        npin.media = media;
        npin.title = [media get:@"caption"];
        npin.subtitle = [media get:@"source"];
        npin.coordinate = newCoordinates;
        npin.disclosureBlock = ^(JPSThumbnailAnnotationView *annotation){
            if([delegate respondsToSelector:@selector(mapObject:didSelectMedia:fromImage:)]){
                [delegate mapObject:self didSelectMedia:[annotation media] fromImage:[annotation asyncImage]];
            }
        };
        [map addAnnotation:[JPSThumbnailAnnotation annotationWithThumbnail:npin]];
        [annotationsObjects addObject:npin];
    }
    
    // Calculate a region to show the most annotations possible
    // - Sort the latitudes
    [lats sortUsingComparator:^NSComparisonResult(id obj1, id obj2) {
        if ([obj1 floatValue] > [obj2 floatValue]){
            return NSOrderedDescending;
        }else if ([obj1 floatValue] < [obj2 floatValue]){
            return NSOrderedAscending;
        }
        return NSOrderedSame;
    }];
    // - Sort the longitudes
    [lngs sortUsingComparator:^NSComparisonResult(id obj1, id obj2) {
        if ([obj1 floatValue] > [obj2 floatValue])
            return NSOrderedDescending;
        else if ([obj1 floatValue] < [obj2 floatValue])
            return NSOrderedAscending;
        return NSOrderedSame;
    }];
    // - Get the highest and lower latitudes and longitudes
    float lowLat = [[lats objectAtIndex:0] floatValue];
    float highLat = [[lats objectAtIndex:([lats count] - 1)] floatValue];
    float lowLng = [[lngs objectAtIndex:0] floatValue];
    float highLng = [[lngs objectAtIndex:([lngs count] - 1)] floatValue];
    
    // - Do the magic to calculate the distance and the scale
    CLLocationCoordinate2D swCoordinates;
    swCoordinates.latitude = lowLat;
    swCoordinates.longitude = lowLng;
    CLLocationCoordinate2D neCoordinates;
    neCoordinates.latitude = highLat;
    neCoordinates.longitude = highLng;
    CLLocation *locSouthWest = [[CLLocation alloc] initWithLatitude:swCoordinates.latitude longitude:swCoordinates.longitude];
    CLLocation *locNorthEast = [[CLLocation alloc] initWithLatitude:neCoordinates.latitude longitude:neCoordinates.longitude];
    CLLocationDistance meters = [locSouthWest distanceFromLocation:locNorthEast];
    MKCoordinateRegion startRegion;
    startRegion.center.latitude = (swCoordinates.latitude + neCoordinates.latitude) / 2.0;
    startRegion.center.longitude = (swCoordinates.longitude + neCoordinates.longitude) / 2.0;
    startRegion.span.latitudeDelta = meters / 111319.5;
    startRegion.span.longitudeDelta = meters / 111319.5;
    // - Set it on the map
    [map setRegion:startRegion animated:TRUE];
    
}
/**
 *  Change the map frame
 *
 *  @param rect The new frame
 */
-(void)setFrame:(CGRect)rect{
    map.frame = rect;
}

#pragma mark - Map delegate
/**
 *  An annotation was selected.
 *  In this case, JPSThumbnailAnnotationViewProtocol handles it.
 *
 *  @param mapView The annotation map
 *  @param view    The annotation view
 */
- (void)mapView:(MKMapView *)mapView didSelectAnnotationView:(MKAnnotationView *)view {
    if ([view conformsToProtocol:@protocol(JPSThumbnailAnnotationViewProtocol)]) {
        [((NSObject<JPSThumbnailAnnotationViewProtocol> *)view) didSelectAnnotationViewInMap:mapView];
    }
}
/**
 *  An annotation was deselected.
 *  In this case, JPSThumbnailAnnotationViewProtocol handles it.
 *
 *  @param mapView The annotation map
 *  @param view    The annotation view
 */
- (void)mapView:(MKMapView *)mapView didDeselectAnnotationView:(MKAnnotationView *)view {
    if ([view conformsToProtocol:@protocol(JPSThumbnailAnnotationViewProtocol)]) {
        [((NSObject<JPSThumbnailAnnotationViewProtocol> *)view) didDeselectAnnotationViewInMap:mapView];
    }
}
/**
 *  Create the view for the annotation object
 *  In this case, JPSThumbnailAnnotationViewProtocol handles it.
 *
 *  @param mapView    The annotation map
 *  @param annotation The annotation object
 *
 *  @return A view to be included on the map
 */
- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id<MKAnnotation>)annotation {
    if ([annotation conformsToProtocol:@protocol(JPSThumbnailAnnotationProtocol)]) {
        return [((NSObject<JPSThumbnailAnnotationProtocol> *)annotation) annotationViewInMap:mapView];
    }
    return nil;
}
/**
 *  Finish killing the map and its dependencies
 */
-(void)dealloc{
    [map removeAnnotations:annotationsObjects];
    map.delegate = nil;
    [map removeFromSuperview];
    map = nil;
}

@end