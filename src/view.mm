#include "model.h"
#include <Cocoa/Cocoa.h>


class Application
{
public:
	Application()
	{
		pool_ = [[NSAutoreleasePool alloc] init];
		[NSApplication sharedApplication];
		// appDelegate_ = [[AppDelegate alloc] init];
		// [NSApp setDelegate:appDelegate_];
		
	}

	~Application() { [pool_ release]; }

	void start() { [NSApp run]; }

private:
	NSAutoreleasePool *pool_;
	// AppDelegate *appDelegate_;
};


// Application::Application() : ptr_(new CocoaApp()) {}

// Application::~Application(){}

// void Application::start() const { ((CocoaApp*)ptr_)->start(); }
