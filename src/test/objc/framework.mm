#import "framework.h"



// combine the mask constants to define a basic window
#define NORMAL_WINDOW (NSTitledWindowMask|NSClosableWindowMask|NSMiniaturizableWindowMask|NSResizableWindowMask)



/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 * 
 * implementation of "InvocationReturn" from "framework-objc.h"
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */
@implementation InvocationReturn

// construct from a Handle<Value>
-(id)initWithHandle:(v8::Handle<v8::Value>)handle 
{
	self = [super init];
	if (self) {  self.handle = handle; }
	return self;
}

// cast the InvocationReturn back to a Handle<Value>, so that it can be passed to Javascript
-(v8::Handle<v8::Value>)cast { return [self handle]; }

@end



/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * implementation of "AppDelegate" from "framework-objc.h"
 *
 *
 * ---- internal class; not exposed to JS -----
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */	
@implementation AppDelegate

-(id)initWithWindow: (NSWindow*)window 
{
	self = [super init];
	if (self) { self.window_ = window; }
	return self;
}

@end




/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * implementation of "App" from "framework-objc.h"
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */	
@implementation App

-(id)initWithArgs:(const v8::Arguments&)args 
{
	self = [super init];
	if (self) 
	{
		[NSApplication sharedApplication];
		[self setDelegate:[AppDelegate new]];
		[NSApp setDelegate:[self delegate]];
	}
	return self;
}

-(InvocationReturn*)exec:(const v8::Arguments&)args 
{ 
	v8::HandleScope scope;
	[NSApp run];
	WRAP_RETURN(v8::Undefined())
}

@end



/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * Callback
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */	
@implementation Callback

-(Test*)callback {
	return self.callback_;
}

-(void)setCallback:(Test*)aPtr {
	self.callback_ = aPtr;
}

-(void)callWithArgs:(int)argc argv:(v8::Handle<v8::Value>[])argv
{
	// (v8::Handle<v8::Object>)recv
	// {
	// 	auto obj = (*onMoveCallback)->ToObject();
	// std::cout << self.ref.IsEmpty() << std::endl;
	// v8::Local<v8::Context> ctx = obj->CreationContext();
		// v8::Handle<v8::Value> argv[] = {};
		// (*[self onMoveCallback])->CallAsFunction(ctx->Global(),0,argv);
	// }
}


@end





/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * implementation of "Form" from "framework-objc.h"
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */	
@implementation Form

@synthesize onMoveCallback = _onMoveCallback;

-(id)init
{
	self = [super init];	
	[self setOnMoveCallback:[[Callback alloc] init]];
	return self;
}


/**
 *
 * expects one argument, an object with the properties:
 *
 * {
 * 	'origin' - object with the properties { x, y } (ie, aw.Point)
 *	'size' - object with the properties { width, height } (ie, aw.Size)
 *	'backgroundColor' - TODO
 * }
 *
 *
 */
-(id)initWithArgs:(const v8::Arguments&)args 
{
	self = [super init];
	[self setOnMoveCallback:[[Callback alloc] init]];
	if (self && args.Length()) 
	{
		NSSize nssize; NSPoint nsorigin;
		auto arg = args[0]->IsObject() ? args[0]->ToObject() : v8::Handle<v8::Object>();
		if ( arg->Has(v8::String::New("size")) ) 
		{
			auto size = get<v8::Object>(arg,"size");
			auto width = size->Get(v8::String::New("width"));
			double widthValue = width->IsNumber() ? width->NumberValue() : 0;
			auto height = size->Get(v8::String::New("height"));
			double heightValue = height->IsNumber() ? height->NumberValue() : 0;
			nssize = NSSize{widthValue,heightValue};
		} else { nssize = NSSize{0,0}; }
		if ( arg->Has(v8::String::New("origin")) ) 
		{
			auto origin = get<v8::Object>(arg,"origin");
			auto x = origin->Get(v8::String::New("x"));
			double xValue = x->IsNumber() ? x->NumberValue() : 0;
			auto y = origin->Get(v8::String::New("y"));
			double yValue = y->IsNumber() ? y->NumberValue() : 0;
			nsorigin = NSPoint{xValue,yValue};
		} else { nsorigin = NSPoint{0,0}; }

		// instantiate the window
		[self setWindow:[[[NSWindow alloc] 
			initWithContentRect:NSRect{nsorigin,nssize}
			styleMask:NORMAL_WINDOW
            backing:NSBackingStoreBuffered
            defer:NO] autorelease]];

		// set the Form as the delegate of the window
		[[self window] setDelegate:self];

		// backgroundColor
		if ( arg->Has(v8::String::New("backgroundColor")) )
		{
			auto bg = get<v8::Object>(arg,"backgroundColor");
			Color* clr = WrappedObject<Color>::unwrap(bg);
			[[self window] setBackgroundColor:[clr color]];
		}

		// order front
		[[self window] makeKeyAndOrderFront:[self window]];
	}
	return self;
}




/**
 *
 * event handler
 *
 */
-(InvocationReturn*)on:(const v8::Arguments)args
{
	v8::HandleScope scope;
	if (args.Length() && args[0]->IsString() && args[1]->IsFunction())
	{
		auto str = v8ToCString(args[0]->ToString());
		if (strcmp(str,"move") == 0) { 
			[[self onMoveCallback] setCallback:(new Test())]; 
		}
	}
	
	WRAP_RETURN(v8::Undefined())
}


-(void)windowDidMove:(NSNotification*)notification
{
	v8::HandleScope scope;
	// v8::Handle<v8::Value> argv[] = {};
	std::cout << [[self onMoveCallback] callback] << std::endl;
	// [[self onMoveCallback] callWithArgs:0 argv:argv]; 
	scope.Close(v8::Undefined());
}

@end





/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * Color
 *
 * takes 4 parameters, red (Number), green (Number), blue (Number), alpha (Number)
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */	
@implementation Color
-(id)initWithArgs:(const v8::Arguments&)args 
{
	self = [super init];
	if ( self )
	{
		float red = 0, green = 0, blue = 0, alpha = 0;

		if (args.Length() == 4) 
		{
			red = args[0]->IsNumber() ? args[0]->NumberValue() : 0;
			green = args[1]->IsNumber() ? args[1]->NumberValue() : 0;
			blue = args[2]->IsNumber() ? args[2]->NumberValue() : 0;
			alpha = args[3]->IsNumber() ? args[3]->NumberValue() : 0;
		}

		[self setColor:[NSColor colorWithRed:red green:green blue:blue alpha:alpha]];
	}
	return self;
}
@end


@implementation Tester

-(id)init {
	self = [super init];
	if ( self )
	{
		
	}
	return self;
}

-(id)initWithArgs:(const v8::Arguments&)args 
{
	self = [super init];
	if ( self )
	{
		[self setString:v8ToCString(args[0]->ToString())];
	}
	return self;
}

-(InvocationReturn*)test:(const v8::Arguments&)args
{
	v8::HandleScope scope;
	std::cout << ([self string]==NULL) << std::endl;
	WRAP_RETURN(v8::Undefined())
}

@end



/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * init function to create the Node module as "exports"
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */
void init( v8::Handle<v8::Object> exports )
{

	// App 
	auto app = WrappedObject<App>();
	app.exposeMethod("exec",@selector(exec:));
	app.exportClass("App",exports);

	// Color
	auto color = WrappedObject<Color>();
	color.exportClass("Color",exports);

	auto test = WrappedObject<Tester>();
	test.exposeMethod("test",@selector(test:));
	test.exportClass("Test",exports);

	// Form
	auto form = WrappedObject<Form>();
	form.exposeMethod("on",@selector(on:));
	form.exportClass("Form",exports);


}




