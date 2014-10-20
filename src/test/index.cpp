
#ifndef BUILDING_NODE_EXTENSION
	#define BUILDING_NODE_EXTENSION
#endif


#include "common.h"


/**
 * //////////////////////////////////////////////////////////////////////////////////////////
 *
 * Test!
 *
 * //////////////////////////////////////////////////////////////////////////////////////////
 */


/**
 *
 * forward declaration of the init function
 * 
 * the function implementation is defined in 'framework-objc.mm'
 *
 */
void init( v8::Handle<v8::Object> exports );

// module building macro from node.h
NODE_MODULE( test, init )