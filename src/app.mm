
#include "cocoaapp.h"

/**
 *
 * App delegate ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 */
@implementation AppDelegate

- (id)initWithWindow: (NSWindow*)window {
	self = [super init];
	if (self) { self.window_ = window; }
	return self;
}

@end


/**
 *
 * Cocoa Application ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 */
@implementation CocoaApp

- (id)init {
	self = [super init];
	if (self) 
	{
		[NSApplication sharedApplication];
		[self setDelegate:[AppDelegate new]];
		[NSApp setDelegate:[self delegate]];
	}
	return self;
}

- (void)exec { [NSApp run]; }

@end



/**
 *
 * Cocoa Form ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 */
@implementation CocoaForm

- (id)initWithWindow:(NSWindow*)window {
	self = [super init];
	if (self) { [self setWindow:window]; }
	return self;
}

- (id)initWithRect:(NSRect)frame {
	self = [super init];
	if (self) { 
		[self setWindow:[[[NSWindow alloc] 
			initWithContentRect:frame
            styleMask:NSBorderlessWindowMask
            backing:NSBackingStoreBuffered
            defer:NO] autorelease]];
		[[self window] setBackgroundColor:[NSColor blueColor]];
		[[self window] makeKeyAndOrderFront:NSApp];
	}
	return self;
}

@end


/**
 *
 * Objective C++ blend between AppWare and Cocoa classes
 *
 */

namespace aw
{


	/**
	 *
	 * Implementation of App, from "app.h" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 */
	App::App() { self_ = (void*)[[CocoaApp alloc] init]; }
	App::~App() { [(CocoaApp*)self_ release]; }
	void App::exec() { [(CocoaApp*)self_ exec]; }


	/**
	 *
	 * Implementation of Form, from "app.h" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 */
	Form::Form() { self_ = (void*)[[CocoaForm alloc] init]; }
	// Form::Form( NSRect frame ) { self_ = (void*)[[CocoaForm alloc] init]; }
	Form::~Form() { [(CocoaForm*)self_ release]; }


}
