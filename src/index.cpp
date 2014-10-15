#ifndef BUILDING_NODE_EXTENSION
	#define BUILDING_NODE_EXTENSION
#endif

#include "index.h"
#include <iostream>


/**
 * //////////////////////////////////////////////////////////////////////////////////////////
 *
 *
 * Forward declare constructors
 *
 *
 * //////////////////////////////////////////////////////////////////////////////////////////
 */
v8::Persistent<v8::Function> aw::JSApp::constructor;
v8::Persistent<v8::Function> aw::JSForm::constructor;




/**
 * //////////////////////////////////////////////////////////////////////////////////////////
 *
 *
 * JSApp implementation
 *
 *
 * //////////////////////////////////////////////////////////////////////////////////////////
 */
v8::Handle<v8::Value> aw::JSApp::Exec(const v8::Arguments& args)
{
	v8::HandleScope scope;
	aw::JSApp *self = node::ObjectWrap::Unwrap<aw::JSApp>(args.This());
	self->exec();
	return scope.Close(args.This());
}



void aw::JSApp::Export( v8::Handle<v8::Object> exports )
{
	v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(aw::JSApp::New);
	tpl->SetClassName(v8::String::NewSymbol("App"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// prototype
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("__exec__"),
		v8::FunctionTemplate::New(aw::JSApp::Exec)->GetFunction());

	constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
	exports->Set(v8::String::NewSymbol("App"), constructor);
}

v8::Handle<v8::Value> aw::JSApp::New(const v8::Arguments& args)
{
	v8::HandleScope scope;

	// Invoked as constructor: `new MyObject(...)`
	if ( args.IsConstructCall() ) 
	{
		aw::JSApp* self = new aw::JSApp();
		self->Wrap(args.This());
		return scope.Close(args.This());
	} 
	else // Invoked as plain function `MyObject(...)`, turn into constructor call.
	{
		return scope.Close(aw::JSApp::constructor->NewInstance());
	}
}


/**
 * //////////////////////////////////////////////////////////////////////////////////////////
 *
 *
 * JSForm implementation
 *
 *
 * //////////////////////////////////////////////////////////////////////////////////////////
 */
void aw::JSForm::Export( v8::Handle<v8::Object> exports )
{
	v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(aw::JSForm::New);
	tpl->SetClassName(v8::String::NewSymbol("Form"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
	exports->Set(v8::String::NewSymbol("Form"), constructor);
}

// retrieve a field from an object, or return 'undefined' if it doesn't exist
v8::Handle<v8::Value> getField( v8::Handle<v8::Object> obj, const char* key )
{
	auto str = v8::String::New(key);
	return (obj->Has(str))?obj->Get(str):v8::Handle<v8::Value>();
}

aw::JSForm::JSForm( v8::Handle<v8::Object> params ) 
{
	auto origin = getField(params,"origin");
	auto size = getField(params,"size");
	auto border = getField(params,"border");

	// (origin, size, border)
	// v8::Handle<v8::Value>

}

aw::JSForm::JSForm() {}

v8::Handle<v8::Value> aw::JSForm::New(const v8::Arguments& args)
{
	v8::HandleScope scope;

	// Invoked as constructor: `new MyObject(...)`
	if ( args.IsConstructCall() ) 
	{
		aw::JSForm* self;
		if ( args.Length() && args[0]->IsObject() )
			self = new aw::JSForm(args[0]->ToObject());
		else 
			self = new aw::JSForm();
		self->Wrap(args.This());
		return scope.Close(args.This());
	} 
	else // Invoked as plain function `MyObject(...)`, turn into constructor call.
	{
		const int argc = args.Length();
		v8::Handle<v8::Value> argv[] = { args.Data() };
		return scope.Close(aw::JSForm::constructor->NewInstance(argc,argv));
	}
}


/**
 * //////////////////////////////////////////////////////////////////////////////////////////
 *
 *
 * Export
 *
 *
 * //////////////////////////////////////////////////////////////////////////////////////////
 */

void init( v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module ) 
{ 
	aw::JSApp::Export(exports); 
	aw::JSForm::Export(exports); 
}


// module building macro
NODE_MODULE( appware, init )