#ifndef __COMMON_H__
#define __COMMON_H__

#include <node.h>
#include <v8.h>

/**
 *
 * retrieve a field from an object and cast as type ""
 *
 *
 */
template<class T>
v8::Handle<T> get(v8::Handle<v8::Object> obj, const char* fieldName)
{
	return v8::Handle<T>::Cast(obj->Get(v8::String::New(fieldName)));
}

/**
 *
 * retrieve an ASCII valued string from a v8::String
 *
 */
inline const char* v8ToCString(v8::Handle<v8::String> v8_string)
{
	v8::String::AsciiValue _str(v8_string);
	char *str = (char*)malloc(_str.length()+1);
	strcpy(str, *_str);
	return str;
}


#endif