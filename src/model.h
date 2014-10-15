#ifndef __MODEL_H__
#define __MODEL_H__

const void start();

#include "stdlib.h"

namespace aw
{

	/**
	 *
	 * Size ***********************************
	 *
	 */
	struct Size
	{
		float width;
		float height;

		Size( float w, float h )
			: width(w), height(h) {}
		Size() : Size(0,0) {}
	};

	/**
	 *
	 * Point ***********************************
	 *
	 */
	struct Point
	{
		float x;
		float y;

		Point( float x_, float y_ )
			: x(x_), y(y_) {}
		Point() : Point(0,0) {}
	};

	/**
	 *
	 * Rectangle ***********************************
	 *
	 */
	struct Rect
	{
		Point origin;
		Size size;
		
		Rect(){}
		Rect( Point origin_, Size size_ )
			: origin(origin_), size(size_) {}
		Rect( float x, float y, float w, float h )
			: origin(Point(x,y)), size(Size(w,h)) {}
	};

	/**
	 *
	 * Window ***********************************
	 *
	 *
	 * abstract base class
	 *
	 */
	struct Window
	{
	public:
		virtual Window& bringFront() = 0;
		virtual Window& setBackgroundColor() = 0;
	protected:
		Window() {}
	};



}


#endif