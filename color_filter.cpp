#include "color_filter.h"

using namespace filtering;
using namespace math;

Image & color_filter::operator<<(imaging::Image & image) {
	Color clr;
	Color color = Color(r, g, b);
	for (int i = 0; i < image.getHeight(); i++) {
		for (int j = 0; j < image.getWidth(); j++) {
			clr = image.getPixel(j, i);
			clr.operator*=(color);
			image.setPixel(j, i, clr);
		}
	}
	return image;
}

color_filter::color_filter(float red, float green, float blue) : Filter(red, green, blue) {
	r = red;
	g = green;
	b = blue;
}