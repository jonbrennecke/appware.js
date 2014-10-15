#ifndef __COCOA_APP_H_
#define __COCOA_APP_H_

#include "app.h"
#include <Cocoa/Cocoa.h>


/**
 *
 * AppDelegate ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 */	
@interface AppDelegate : NSResponder <NSApplicationDelegate> {}
@property(nonatomic, retain) NSWindow* window_;
- (id)initWithWindow: (NSWindow*)window;
@end


/**
 *
 * App ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * class definition for the main application instance
 *
 */	
@interface CocoaApp : NSObject {}
@property(nonatomic, retain) AppDelegate* delegate;
- (void)exec;
@end


/**
 *
 * Form ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * represents a window or dialog box that makes up an application's user interface
 *
 */
@interface CocoaForm : NSObject {}
@property(nonatomic, retain) NSWindow* window;
- (id)initWithWindow: (NSWindow*)window;
- (id)initWithRect: (NSRect)frame;
@end




#endif