#pragma once

#ifndef diff_filter
#define _diff_filter_

#include "Filter.h"


namespace filtering
{
	class diff_filter : public Filter
	{
	protected:

		component_t r, g, b;

		imaging::Image* image_cp;

	public:

		diff_filter();

		Image & operator<<(imaging::Image & image);

	};
}
#endif // !diff_filter

