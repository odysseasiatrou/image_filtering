#pragma once

#ifndef median_filter
#define _median_filter_

#include "Filter.h"

namespace filtering
{

	class median_filter : public Filter
	{
	protected:

		component_t r, g, b;

		imaging::Image * image;

	public:

		median_filter();

		Image & operator<<(imaging::Image & image);

	};
}
#endif // !median_filter

