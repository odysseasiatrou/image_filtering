#include "gray_filter.h"

using namespace filtering;
using namespace math;
using namespace std;

Image & gray_filter::operator<<(imaging::Image & image) {
	component_t mean = 0;
	Color clr;
	Color color;
	for (int i = 0; i < image.getHeight(); i++) {
		for (int j = 0; j < image.getWidth(); j++) {
			clr = image.getPixel(j, i);
			mean = clr.operator[](0) + clr.operator[](1) + clr.operator[](2);
			mean /= 3;
			color = Color(mean, mean, mean);
			clr.operator=(color);
			image.setPixel(j, i, clr);
		}
	}
	return image;
}

gray_filter::gray_filter() : Filter() {
	r = 0;
	g = 0;
	b = 0;
}