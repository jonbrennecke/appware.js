#ifndef __VIEW_H__
#define __VIEW_H__

#import <Cocoa/Cocoa.h>
#include "model.h"

namespace cocoa
{

	/**
	 *
	 * Size ***********************************
	 *
	 */
	struct Size : public aw::Size
	{
		Size() : aw::Size() {}
		Size( aw::Size size )
			: aw::Size(size) {}
		Size( NSSize size )
			: aw::Size(size.width, size.height) {}
		operator NSSize () { return NSSize{width,height}; }
	};

	/**
	 *
	 * Point ***********************************
	 *
	 */
	struct Point : public aw::Point
	{
		Point() : aw::Point() {}
		Point( aw::Point point ) 
			: aw::Point(point) {}
		Point( NSPoint point )
			: aw::Point(point.x, point.y) {}
		operator NSPoint () { return NSPoint{x,y}; }
	};

	/**
	 *
	 * Rectangle ***********************************
	 *
	 */
	struct Rect : public aw::Rect
	{
		Rect() : aw::Rect() {}
		Rect( NSPoint point, NSSize size )
			: aw::Rect(Point(point), Size(size)) {}
		Rect( NSRect rect ) : Rect(rect.origin,rect.size) {}
		Rect( float x, float y, float w, float h ) : aw::Rect(x,y,w,h) {}
		operator NSRect () { return NSRect{Point(origin),Size(size)}; }
	};

	// NSColor

	/**
	 *
	 * Window ***********************************
	 *
	 */
	class Window : public aw::Window
	{
	public:
		Window( Rect& frame )
		{
			window_ = [[[NSWindow alloc] 
				initWithContentRect:frame
				styleMask:NSBorderlessWindowMask
				backing:NSBackingStoreBuffered 
				defer:NO] autorelease];

			this->setBackgroundColor();
		}

		Window& bringFront()
		{
			[window_ makeKeyAndOrderFront:NSApp];
			return *this;
		}

		Window& setBackgroundColor( /*Color color*/ )
		{
			[window_ setBackgroundColor:[NSColor blueColor]];
			return *this;
		}

	private:
		NSWindow* window_;
	};

}

#endif