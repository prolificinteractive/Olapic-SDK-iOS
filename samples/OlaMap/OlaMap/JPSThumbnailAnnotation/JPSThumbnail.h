//
//  JPSThumbnail.h
//  JPSThumbnailAnnotation
//
//  Created by Jean-Pierre Simard on 4/22/13.
//  Copyright (c) 2013 JP Simard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OlapicSDK/OlapicSDK.h>
#import "JPSThumbnailAnnotationView.h"
@import MapKit;

typedef void (^ActionBlock)(JPSThumbnailAnnotationView *annotation);

@interface JPSThumbnail : NSObject

@property (nonatomic,strong) OlapicMediaEntity *media;
@property (nonatomic, strong) UIImage *image;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *subtitle;
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;
@property (nonatomic, copy) ActionBlock disclosureBlock;

@end
