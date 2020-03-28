#pragma once

#ifndef gray_filter
#define _gray_filter_

#include "Filter.h"

namespace filtering
{
	class gray_filter : public Filter
	{
	protected:

		component_t r, g, b;

		imaging::Image * image;

	public:

		gray_filter();

		Image & operator << (imaging::Image & image);

	};
}
#endif // !gray_filter

