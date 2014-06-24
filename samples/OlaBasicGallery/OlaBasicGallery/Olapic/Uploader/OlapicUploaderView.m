//
//  OlapicUploaderView.m
//  OlaBasicGallery
//
//  Created by The Olapic Team on 5/16/14.
//  Copyright (c) 2014 Olapic. All rights reserved.
//

#import "OlapicUploaderView.h"
#import "OlapicAsyncImageView.h"

@interface OlapicUploaderView(){
    /**
     *  A flag to know if the app is done downloading
     *  the uploader information
     */
    BOOL _isDone;
    /**
     *  A flag to know if the view shadows are visible
     */
    BOOL _isShadowVisible;
}

@property (nonatomic) BOOL _isDone;
@property (nonatomic) BOOL _isShadowVisible;
/**
 *  The basic Setup of the object: Create the objects & organize the UI
 */
-(void)setup;
/**
 *  This method is called every time the size of the view changes, and it
 *  adjust the size and position of the elements accordingly
 */
-(void)adjustSize;
/**
 *  The object is done downloading the information and adding it to the
 *  UI, so its time to hide the loading indicator and show the content
 */
-(void)done;

@end

@implementation OlapicUploaderView
@synthesize media,uploader,image,mainViewController,container,lblName,lblSource,txtCaption,imgAvatar,loader,_isDone,_isShadowVisible,share;
/**
 *  The class constructor
 *
 *  @param frame The size for this object
 *  @param med   The media object for which this object will show the detail
 *
 *  @return An instace of this object (OlapicUploaderView)
 */
-(id)initWithFrame:(CGRect)frame andMedia:(OlapicMediaEntity *__weak)med{
    self = [super initWithFrame:frame];
    if(self){
        media = med;
        [self setup];
    }
    return self;
}
/**
 *  The basic Setup of the object: Create the objects & organize the UI
 */
-(void)setup{
    // UI
    self.backgroundColor = [UIColor colorWithWhite:255.0/255.0 alpha:0.9];
    self.layer.masksToBounds = NO;
    self.layer.shadowOffset = CGSizeMake(-4, 0);
    self.layer.shadowRadius = 5;
    self.layer.shadowOpacity = 0;
    // - Container Area
    container = [[UIView alloc] initWithFrame:CGRectZero];
    container.alpha = 0;
    container.backgroundColor = [UIColor clearColor];
    [self addSubview:container];
    // - Label for the uploaders name
    lblName = [[UILabel alloc] initWithFrame:CGRectZero];
    lblName.font = [UIFont fontWithName:@"Helvetica-Bold" size:15.0];
    lblName.textColor = [UIColor darkGrayColor];
    lblName.backgroundColor = [UIColor clearColor];
    [container addSubview:lblName];
    // - Label for the media source
    lblSource = [[UILabel alloc] initWithFrame:CGRectZero];
    lblSource.font = [UIFont fontWithName:@"Helvetica" size:14.0];
    lblSource.textColor = [UIColor grayColor];
    lblSource.backgroundColor = [UIColor clearColor];
    [container addSubview:lblSource];
    // - Label for the uploader avatar
    imgAvatar = [[UIImageView alloc] initWithFrame:CGRectZero];
    imgAvatar.layer.masksToBounds = YES;
    imgAvatar.clipsToBounds = YES;
    imgAvatar.layer.cornerRadius = 8;
    imgAvatar.layer.shadowOffset = CGSizeMake(0, 0);
    imgAvatar.layer.shadowRadius = 2;
    imgAvatar.layer.shadowOpacity = 0.7;
    [container addSubview:imgAvatar];
    // - The text area for the media caption
    txtCaption = [[UITextView alloc] initWithFrame:CGRectZero];
    txtCaption.font = [UIFont fontWithName:@"Helvetica" size:14.0];
    txtCaption.textColor = [UIColor darkGrayColor];
    txtCaption.backgroundColor = [UIColor clearColor];
    txtCaption.delegate = self;
    [container addSubview:txtCaption];
    // - The loading indicator
    loader = [[UIActivityIndicatorView alloc] initWithFrame:CGRectZero];
    loader.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
    [self addSubview:loader];
    // - The share button
    share = [[UIButton alloc] initWithFrame:CGRectZero];
    [share setTitle:@"Share" forState:UIControlStateNormal];
    [share setTitleColor:[UIColor colorWithRed:0.44f green:0.49f blue:0.58f alpha:1.00f] forState:UIControlStateNormal];
    [[share titleLabel] setFont:[UIFont fontWithName:@"Helvetica" size:15.0]];
    [share setBackgroundColor:[UIColor clearColor]];
    [share addTarget:self action:@selector(openShareWindow) forControlEvents:UIControlEventTouchUpInside];
    [container addSubview:share];
    
    // Data
    // - Set the source and the caption (which we already have, from the media object)
    lblSource.text = [NSString stringWithFormat:@"From %@",[media get:@"source"]];
    txtCaption.text = [media get:@"caption"];
    // - Start downloading the uploaders information
    [media getUploader:^(OlapicUploaderEntity *up){
        // - - Set the uploaders reference
        uploader = up;
        // - - Show the name on the UI
        lblName.text = [uploader get:@"name"];
        OlapicSDK *olapic = [OlapicSDK sharedOlapicSDK];
        // - - Download the avatar
        [[olapic rest] getData:[uploader get:@"avatar_url"] parameters:nil onSuccess:^(NSData *response){
            // - - - Set it on the image
            imgAvatar.image = [OlapicAsyncImageView resizeImage:[UIImage imageWithData:response] to:CGSizeMake(54, 54) detectingRetina:YES];
            [self done];
        } onFailure:^(NSError *error){
            NSLog(@"ERROR ON THE UPLOADER AVATAR");
        }];

    } onFailure:^(NSError *error){
        NSLog(@"ERROR ON THE UPLOADER");
    }];
}
/**
 *  This method is called every time the size of the view changes, and it
 *  adjust the size and position of the elements accordingly
 */
-(void)adjustSize{
    container.frame = CGRectMake(0, 0, self.frame.size.width, self.frame.size.height);
    imgAvatar.frame = CGRectMake(10, 10, 54, 54);
    CGSize size = self.frame.size;
    lblName.frame = CGRectMake(74, 20, size.width-84, 20);
    lblSource.frame = CGRectMake(74, 37, size.width-84, 15);
    txtCaption.frame = CGRectMake(10, 74, size.width-20, (size.height - 74 - 50));
    loader.frame = CGRectMake((size.width/2) - 10, (size.height/2) - 10, 20, 20);
    share.frame = CGRectMake(10, size.height - 40, size.width - 20, 30);
    share.alpha = mainViewController ? 1 : 0;
    if(!_isDone && ![loader isAnimating]){
        [loader startAnimating];
    }
}
/**
 *  The object is done downloading the information and adding it to the
 *  UI, so its time to hide the loading indicator and show the content
 */
-(void)done{
    _isDone = YES;
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.25];
    container.alpha = 1;
    [loader stopAnimating];
    [UIView commitAnimations];
}
/**
 *  Show/Hide the view shadows
 *
 *  @param show YES to show them and NO to hide them
 */
-(void)showShadow:(BOOL)show{
    if((show && _isShadowVisible) || (!show && !_isShadowVisible)){
        return;
    }
    self.layer.shadowOpacity = show ? 0.5 : 0;
    _isShadowVisible = show;
}
/**
 *  Open the Social Framework modal
 */
-(void)openShareWindow{
    NSMutableArray *items = [[NSMutableArray alloc] init];
    [items addObject:txtCaption.text];
    if(image){
        [items addObject:image.image];
    }
    NSString *url = [media get:@"share_url"];
    if(url != (id)[NSNull null]){
        [items addObject:[NSURL URLWithString:url]];
    }
    UIActivityViewController *shareView = [[UIActivityViewController alloc] initWithActivityItems:items applicationActivities:nil];
    shareView.completionHandler = ^(NSString *activityType, BOOL completed){
        if(activityType == nil) return;
        if(completed){
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Olapic" message:@"Your message was successfully shared!" delegate:nil cancelButtonTitle:@"Accept" otherButtonTitles:nil];
            [alert show];
        }
    };
    [mainViewController presentViewController:shareView animated:TRUE completion:nil];
}

#pragma mark - Default cycle
/**
 *  Overwrite the default UIView setFrame method in
 *  order to call the adjustSize method every time
 *  the view's frame changes
 *
 *  @param frame The new size for the view
 */
-(void)setFrame:(CGRect)frame{
    [super setFrame:frame];
    [self adjustSize];
}
/**
 *  Overwrite the default UIView drawRect method in
 *  order to call the adjustSize method every time
 *  the view's frame changes
 *
 *  @param rect The size where the view will be drawn
 */
-(void)drawRect:(CGRect)rect{
    [super drawRect:rect];
    [self adjustSize];
}

#pragma mark - UITextView delegate
/**
 *  Tell the caption's text area that it can't enter
 *  on edit mode
 *
 *  @param textView The text view asking for the delegate
 *
 *  @return NO, so it can be editable
 */
-(BOOL)textViewShouldBeginEditing:(UITextView *)textView{
    return NO;
}

@end
