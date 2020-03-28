#include "blur_filter.h"

using namespace filtering;
using namespace math;

Image & blur_filter::operator<<(imaging::Image & image) {
	Color clr;
	int counter;
	for (int i = 0; i < image.getHeight(); i++) {
		for (int j = 0; j < image.getWidth(); j++) {
			clr = Color();
			counter = 0;
			for (int m = -1; m <= 1; m++) {
				for (int n = -1; n <= 1; n++) {
					if (i + m >= 0 && i + m < image.getHeight() && j + n >= 0 && j + n < image.getWidth()) {
						clr.operator+=(image.getPixel(i + m, j + n));
						counter++;
					}
				}
			}
			image.setPixel(j, i, clr.operator/(counter));
		}
	}
	return image;
}

blur_filter::blur_filter() : Filter() {
	r = 0;
	g = 0;
	b = 0;
}