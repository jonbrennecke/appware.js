/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * Test to wrap an Objective C object in V8
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */


#ifndef __TEST_OBJC_H_
#define __TEST_OBJC_H_

#import "test.h"
#import <stdlib.h>
#import <Cocoa/Cocoa.h>



/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * InvocationReturn
 * 
 * Objective C's 'id' type is used to represent Objective C objects, and values of 'id' 
 * type can't be cast to C++ objects.  For that reason, wrapped Objective C objects need to
 * return instances of 'InvocationReturn', which can then be cast back down to a 'Handle<Value>' 
 * for Javascript.
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */
@interface InvocationReturn : NSObject {}
@property v8::Handle<v8::Value> handle;
-(id)initWithHandle:(v8::Handle<v8::Value>)handle;
-(v8::Handle<v8::Value>)cast;
@end




/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * Test class
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */
@interface Test : NSObject {}
-(InvocationReturn*)test:(const v8::Arguments&)args;
@end





/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * Templated Wrapper class
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */
template<class T>
class WrappedObject : public node::ObjectWrap
{
public:
	typedef WrappedObject<T> self_type;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

	WrappedObject();

	// functions for Javascript
	static v8::Persistent<v8::Function> constructor;
	static v8::Handle<v8::Value> New(const v8::Arguments&);
	static v8::Handle<v8::Value> Call(const v8::Arguments&);

	// functions for C++
	void exposeMethod(const char*,const SEL);
	void exportClass(const char*,v8::Handle<v8::Object>);

	// dereferencing WrappedObject yields the underlying object
	pointer operator*() { return ptr_;  }

private:
	v8::Local<v8::FunctionTemplate> tpl;
	pointer ptr_;
};






/**
 * 
 * Persistent handles to the constructor functions
 * 
 */
template <class T>
v8::Persistent<v8::Function> WrappedObject<T>::constructor;



/**
 * 
 * Constructor
 * 
 */
template<class T>
WrappedObject<T>::WrappedObject()
{
	tpl = v8::FunctionTemplate::New(WrappedObject::New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	ptr_ = [[value_type alloc] init];
}


/**
 * 
 * Expose an Objective C class method to JS
 * 
 */
template<class T>
void WrappedObject<T>::exposeMethod(const char* methodName, const SEL sel)
{
	IMP imp = [ptr_ methodForSelector:sel];
	auto func = v8::FunctionTemplate::New(WrappedObject<T>::Call);
	func->Set(v8::String::New("ptr"),v8::External::Wrap((void*)ptr_));
	func->Set(v8::String::New("sel"),v8::External::Wrap((void*)sel));
	func->Set(v8::String::New("imp"),v8::External::Wrap((void*)imp));
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol(methodName), func->GetFunction());
}


/**
 * 
 * Create a new instance (when the new operator or '()' is called)
 * 
 */
template<class T>
v8::Handle<v8::Value> WrappedObject<T>::New(const v8::Arguments& args)
{
	v8::HandleScope scope;

	// Invoked as constructor: `new MyObject(...)`
	if ( args.IsConstructCall() ) 
	{
		auto self = new WrappedObject<T>();
		self->Wrap(args.This());
		return scope.Close(args.This());
	} 
	else // Invoked as plain function `MyObject(...)`, turn into constructor call.
	{
		return scope.Close(WrappedObject::constructor->NewInstance());
	}
}


/**
 *
 * export the object template to Javascript
 *
 */
template <class T>
void WrappedObject<T>::exportClass(const char* name,v8::Handle<v8::Object> exports)
{
	constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
	exports->Set(v8::String::NewSymbol(name), constructor);
}



/**
 * 
 * Set up the wrapped function and pass through the arguments
 * 
 */
template<class T>
v8::Handle<v8::Value> WrappedObject<T>::Call(const v8::Arguments& args)
{
	v8::HandleScope scope;
	auto ptr = (pointer)v8::External::Unwrap(args.Callee()->Get(v8::String::New("ptr")));
	auto sel = (SEL)v8::External::Unwrap(args.Callee()->Get(v8::String::New("sel")));
	auto imp = (IMP)v8::External::Unwrap(args.Callee()->Get(v8::String::New("imp")));
	return scope.Close([(InvocationReturn*)imp(ptr,sel,args) cast]);
}


#endif