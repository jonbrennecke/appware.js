#ifndef __INVOCATION_RETURN_H__
#define __INVOCATION_RETURN_H__



#import <Cocoa/Cocoa.h>



// close a HandleScope (assumed to be named "scope") and return
// an InvocationReturn wrapping the Handle<Value> "value"
#define WRAP_RETURN(value) return [[InvocationReturn alloc] initWithHandle:scope.Close((value))];



/**
 * /////////////////////////////////////////////////////////////////////////////////
 *
 *
 * InvocationReturn
 *
 * lightweight wrapper around a 'Handle<Value>'
 *
 * Objective C's 'id' type is used to represent Objective C objects, and values of 'id' 
 * type can't be cast to C++ objects.  For that reason, functions exposed within a wrapped 
 * Objective C objects need to return instances of 'InvocationReturn', which can then be
 * cast back down to a 'Handle<Value>' for Javascript.
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////
 */
@interface InvocationReturn : NSObject {}
@property v8::Handle<v8::Value> handle;
-(id)initWithHandle:(v8::Handle<v8::Value>)handle;
-(v8::Handle<v8::Value>)cast;
@end


#endif