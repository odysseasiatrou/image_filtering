#include "Image.h"
#include "ppm_format.h"
#include <iostream>

using namespace imaging;
using namespace std;


Color * Image::getRawDataPtr() {
	return math::Array<Color>::buffer;
}

Color Image::getPixel(unsigned int x, unsigned int y) const {
	return math::Array<Color>::operator()(x, y);
}

void Image::setPixel(unsigned int x, unsigned int y, Color & value) {
	if ((x < this->width) && (y < this->height)) {
		buffer[(y*width) + x].operator=(value);
		math::Array<Color>::buffer[(y*width) + x].operator=(value);
	}
}

void Image::setData(const component_t * & data_ptr) {
	if ((buffer == nullptr) || (height == 0) || (width == 0))
		return;
	else
		memcpy(buffer, data_ptr, 3 * height*width * sizeof(component_t));
}

void Image::resize(unsigned int new_width, unsigned int new_height) {
	math::Array<Color>::resize(new_width, new_height);
}

Image::Image() : Array(0, 0) {
	this->height = 0;
	this->width = 0;
	buffer = nullptr;
}

Image::Image(unsigned int width, unsigned int height) : Array(width, height) {
	this->height = height;
	this->width = width;
	buffer = nullptr;
}

Image::Image(unsigned int width, unsigned int height, const component_t * data_ptr) : Array(width, height) {
	this->height = height;
	this->width = width;
	buffer = new Color[height*width];
	Color clr;
	for (int i = 0; i < 3 * height*width; i += 3) {
		clr = Color(data_ptr[i], data_ptr[i + 1], data_ptr[i + 2]);
		buffer[i / 3].operator=(clr);
	}
	math::Array<Color>::buffer = this->buffer;
}

Image::Image(const Image &src) : Array(src) {
	height = src.height;
	width = src.width;
	buffer = new Color[height*width];
	memcpy(buffer, src.buffer, height*width * sizeof(Color));
}

Image::~Image() {
	if (buffer)
		delete[] buffer;
}

Image & Image::operator = (const Image & right) {
	math::Array<Color>::operator=(right);
	height = right.height;
	width = right.width;
	if (buffer)
		delete[] buffer;
	buffer = new Color[height*width];
	memcpy(buffer, right.buffer, height*width * sizeof(Color));
	return *this;
}

bool Image::operator << (std::string filename) {
	char* new_image = nullptr;
	new_image = &filename[0];
	const char* file_name = (const char*)new_image;
	Image* streamin = ReadPPM(file_name);
	operator = (*streamin);
	delete streamin;
	return true;
}

bool Image::operator >> (std::string filename) {
	char* new_image = nullptr;
	new_image = &filename[0];
	const char* file_name = (const char*)new_image;
	bool flag = WritePPM(*this, file_name);
	return flag;
}