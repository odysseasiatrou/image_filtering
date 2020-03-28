#pragma once

#ifndef color_filter
#define _color_filter_

#include "Filter.h"


namespace filtering
{

	class color_filter : public Filter
	{
	protected:

		component_t r, g, b;

		imaging::Image * image_cp;

	public:

		color_filter(float red, float green, float blue);

		Image & operator << (imaging::Image & image);

	};
}
#endif // !color_filter

