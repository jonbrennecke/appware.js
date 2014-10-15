
#ifndef BUILDING_NODE_EXTENSION
	#define BUILDING_NODE_EXTENSION
#endif

#include "test.h"

// wrap native Objective C functions with C++, encapsulate C++
// with V8 and pass to Javascript

/**
 * //////////////////////////////////////////////////////////////////////////////////////////
 *
 * Export
 *
 * //////////////////////////////////////////////////////////////////////////////////////////
 */

void init( v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module );

// module building macro from node.h
NODE_MODULE( test, init )