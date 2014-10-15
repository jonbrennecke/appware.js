#ifndef __INDEX_H__
#define __INDEX_H__

#include <v8.h>
#include <node.h>

#include "app.h"

namespace aw
{



	/**
	 *
	 * JSExport ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 * abstract base class for exporting objects to V8
	 *
	 */
	class JSExport : public node::ObjectWrap {};

	/**
	 *
	 * JSApp ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 * extends "App" with methods for V8
	 *
	 */	
	class JSApp : public JSExport, public App
	{
	private:
		static v8::Persistent<v8::Function> constructor;
	public:
		static v8::Handle<v8::Value> Exec(const v8::Arguments& args);
		static v8::Handle<v8::Value> New(const v8::Arguments& args);
		static void Export( v8::Handle<v8::Object> exports );
	};

	/**
	 *
	 * JSForm ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 * extends "Form" with methods for V8
	 *
	 */	
	class JSForm : public JSExport, public Form
	{
	private:
		static v8::Persistent<v8::Function> constructor;
	public:
		JSForm();
		JSForm( v8::Handle<v8::Object> params );
		static v8::Handle<v8::Value> New(const v8::Arguments& args);
		static void Export( v8::Handle<v8::Object> exports );
	};



}

#endif