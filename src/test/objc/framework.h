/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * AppWare Framework
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */



#ifndef __FRAMEWORK_OBJC_H_
#define __FRAMEWORK_OBJC_H_



#import "../common.h"
#import "wrappedobject.h"
#import <Cocoa/Cocoa.h>



#include <iostream>




typedef void* CRef;



// Forward declarations of classes
// @class FormDelegate;
@class Form;
@class AppDelegate;
@class App;




/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * AppDelegate
 *
 * event handler to respond to changes in system/app state
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */	
@interface AppDelegate : NSResponder <NSApplicationDelegate> {}
@property(nonatomic, retain) NSWindow* window_;
- (id)initWithWindow: (NSWindow*)window;
@end




/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * App
 *
 * create a main application instance
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */	
@interface App : NSObject {}
@property(nonatomic, retain) AppDelegate* delegate;
-(id)initWithArgs:(const v8::Arguments&)args;
-(InvocationReturn*)exec:(const v8::Arguments&)args;
@end


class Test
{
public:
	Test()
	{

	}

	~Test()
	{
		std::cout << "destructor called!" << std::endl;
	}

	
};


/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * Callback function wrapper in Objective C
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */	
@interface Callback : NSObject {}

@property(nonatomic,assign) Test* callback_;

-(Test*)callback;
-(void)setCallback:(Test*)aPtr;
-(void)callWithArgs:(int)argc argv:(v8::Handle<v8::Value>[])argv;
@end


/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * Form
 *
 * create a Form, and respond to changes in the state of the Form
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */	
@interface Form : NSResponder <NSWindowDelegate> {
	Callback* _onMoveCallback;
}

@property(nonatomic, retain) NSWindow* window;
@property(nonatomic, retain) Callback* onMoveCallback;

-(id)initWithArgs:(const v8::Arguments&)args;
// -(InvocationReturn*)setBackgroundColor:(const v8::Arguments&)args;

// windowWillMiniaturize:
// windowDidMiniaturize:
// windowDidDeminiaturize:
-(InvocationReturn*)on:(const v8::Arguments)args;
-(void)windowDidMove:(NSNotification *)notification;
@end



/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * Color
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */	
@interface Color : NSObject {}
@property(nonatomic,retain) NSColor* color;
-(id)initWithArgs:(const v8::Arguments&)args;
@end


@interface Tester : NSObject {}
@property(nonatomic,assign) const char* string;
-(id)initWithArgs:(const v8::Arguments&)args;
-(InvocationReturn*)test:(const v8::Arguments&)args;
@end



#endif