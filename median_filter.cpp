#include "median_filter.h"
#include <vector>
#include <algorithm>

using namespace filtering;
using namespace math;


Image & median_filter::operator<<(imaging::Image & image) {
	Color clr;
	int counter;
	std::vector<component_t> red_set(9);
	std::vector<component_t> green_set(9);
	std::vector<component_t> blue_set(9);
	for (int i = 0; i < image.getHeight(); i++) {
		for (int j = 0; j < image.getWidth(); j++) {
			counter = 0;
			for (int m = -1; m <= 1; m++) {
				for (int n = -1; n <= 1; n++) {
					if (i + m >= 0 && i + m < image.getHeight() && j + n >= 0 && j + n < image.getWidth()) {
						clr = image.getPixel(i + m, j + n);
						red_set[counter] = clr.operator[](0);
						green_set[counter] = clr.operator[](1);
						blue_set[counter] = clr.operator[](2);
						counter++;
					}
				}
			}
			std::sort(red_set.begin(), red_set.end());
			std::sort(green_set.begin(), green_set.end());
			std::sort(blue_set.begin(), blue_set.end());
			clr = Color(red_set[counter - 1] - red_set[0], green_set[counter - 1] - green_set[0], blue_set[counter - 1] - blue_set[0]);
			image.setPixel(j, i, clr);
		}
	}
	std::cout << image.getPixel(1, 0).operator[](0) << image.getPixel(1, 0).operator[](1) << image.getPixel(1, 0).operator[](2) << std::endl;
	return image;
}

median_filter::median_filter() : Filter() {
	r = 0;
	g = 0;
	b = 0;
}