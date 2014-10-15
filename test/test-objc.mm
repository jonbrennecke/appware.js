#import "test-objc.h"

@implementation InvocationReturn

-(id)initWithHandle:(v8::Handle<v8::Value>)handle 
{
	self = [super init];
	if (self) {  self.handle = handle; }
	return self;
}

-(v8::Handle<v8::Value>)cast {
	return [self handle];
}

@end

// ************************************************************

@implementation Test

-(InvocationReturn*)test:(const v8::Arguments&)args {
	v8::HandleScope scope;
	return [[InvocationReturn alloc] initWithHandle:scope.Close(v8::String::New("Hello World!"))];
}

@end 


// ************************************************************


void init( v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module ) 
{

	// wrap an Objective C class
	auto wrap = WrappedObject<Test>();
	wrap.exposeMethod("method",@selector(test:));
	wrap.exportClass("Class",exports); // TODO reverse the args here to match exposeMethod


}