#include "model.h"
#include "appdelegate.h"
#include <Cocoa/Cocoa.h>

@implementation AppDelegate
@end


class Application
{
public:
	Application()
	{
		pool_ = [[NSAutoreleasePool alloc] init];
		[NSApplication sharedApplication];

		window = 

		// NSRect frame = NSMakeRect(100, 100, 200, 200);
		// NSUInteger styleMask = NSBorderlessWindowMask;
		// NSRect rect = [NSWindow contentRectForFrameRect:frame styleMask:styleMask];
		// NSWindow * window = [[NSWindow alloc] initWithContentRect:rect styleMask:styleMask backing: NSBackingStoreBuffered    defer:false];
		// [window setBackgroundColor:[NSColor blueColor]];
		// [window makeKeyAndOrderFront: window];


		delegate_ = [[AppDelegate alloc] initWithWindow:];
		[NSApp setDelegate:delegate_];
	}

	~Application() { [pool_ release]; }

	void start() { [NSApp run]; }

private:
	NSAutoreleasePool *pool_;
	AppDelegate *delegate_;
};

const void start()
{
	auto app = Application();
}


// Application::Application() : ptr_(new CocoaApp()) {}

// Application::~Application(){}

// void Application::start() const { ((CocoaApp*)ptr_)->start(); }
