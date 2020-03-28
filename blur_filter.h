#pragma once

#ifndef blur_filter
#define _blur_filter_

#include "Filter.h"

namespace filtering
{

	class blur_filter : public Filter
	{
	protected:

		component_t r, g, b;

		imaging::Image * image;

	public:

		blur_filter();

		Image & operator << (imaging::Image & image);

	};
}
#endif // !blur_filter

