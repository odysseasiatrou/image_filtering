#pragma once


#ifndef _Filter_
#define _Filter_

#include "Image.h"

namespace filtering
{

	typedef float component_t;

	using namespace imaging;

	class Filter {

	protected:

		component_t r, g, b;

		imaging::Image * image_cp;

	public:

		Filter() : r(0), g(0), b(0) {};

		Filter(component_t red, component_t green, component_t blue) : r(red), g(green), b(blue) {};

		virtual Image & operator << (imaging::Image & image) = 0;

	};
}
#endif // !_Filter_

