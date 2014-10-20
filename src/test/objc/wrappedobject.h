#ifndef __WRAPPED_OBJ_H__
#define __WRAPPED_OBJ_H__



#import "invocationreturn.h"



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

	// functions for Javascript
	WrappedObject(const v8::Arguments& args);
	static v8::Persistent<v8::Function> constructor;
	static v8::Handle<v8::Value> New(const v8::Arguments&);
	static v8::Handle<v8::Value> Call(const v8::Arguments&);

	// functions for C++
	WrappedObject();
	void exposeMethod(const char*,const SEL);
	void exportClass(const char*,v8::Handle<v8::Object>);
	static pointer unwrap(v8::Handle<v8::Object>);

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
 * Constructor (with arguments)
 * 
 * passes arguments through to the wrapped class (calling initWithArgs:)
 *
 */
template<class T>
WrappedObject<T>::WrappedObject(const v8::Arguments& args)
{
	tpl = v8::FunctionTemplate::New(WrappedObject::New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	ptr_ = [[T alloc] initWithArgs:args];
}



/**
 * 
 * Constructor (without arguments)
 * 
 */
template<class T>
WrappedObject<T>::WrappedObject()
{
	tpl = v8::FunctionTemplate::New(WrappedObject::New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	ptr_ = [T alloc];
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
		auto self = new WrappedObject<T>(args);
		self->Wrap(args.This());
		return scope.Close(args.This());
	} 
	else // Invoked as plain function `MyObject(...)`, turn into constructor call.
	{
		// pass arguments
		return scope.Close(v8::ThrowException(
			v8::Exception::SyntaxError(
				v8::String::New("Objects must be created with the 'new' keyword."))));
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



/**
 * 
 * Unwrap an object of type T
 * 
 */
template<class T>
T*  WrappedObject<T>::unwrap(const v8::Handle<v8::Object> object)
{
	return **(WrappedObject<T>*)node::ObjectWrap::Unwrap<WrappedObject<T>>(object);
}

#endif