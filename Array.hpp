//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2016
//
//

#ifndef _ARRAY_IMPLEMENTATION_
#define _ARRAY_IMPLEMENTATION_

#include "Array.h"

namespace math
{

	//--------------------------------------------------------------------------------------------
	// This file is included from the templated Array class header.
	// TODO: Provide its member function implementations here:
	//--------------------------------------------------------------------------------------------

	template <typename T>
	void * const Array<T>::getRawDataPtr() {
		return buffer;
	}

	template <typename T>
	T & Array<T>::operator () (int x, int y) {
		if ((x < this->width) && (y < this->height)) {
			unsigned int index = ((y*width) + x);
			return buffer[index];
		}
	}

	template <typename T>
	const T & Array<T>::operator () (int x, int y) const {
		if ((x < this->width) && (y < this->height)) {
			unsigned int index = ((y*width) + x);
			return buffer[index];
		}
	}

	template <typename T>
	Array<T>::Array(unsigned int w, unsigned int h) {
		width = w;
		height = h;
		buffer = nullptr;
	}

	template <typename T>
	Array<T>::Array(const Array<T> & source) {
		width = source.width;
		height = source.height;
		buffer = new Vec3<component_t>[height*width];
		//for (int i = 0; i < width; i++) {
		//for (int j = 0; j < height; j++) {
		//Vec3<component_t> component = Vec3<component_t>(source.buffer[i*(j - 1) + i].operator()(i, j));
		//buffer[i*(j - 1) + i] = component;
		//cout << buffer[i*(j - 1) + i].operator[](0) << endl;
		//}
		//}
		memcpy(buffer, source.buffer, height*width * sizeof(math::Vec3<component_t>));
	}

	template <typename T>
	Array<T> & Array<T>::operator = (const Array<T> & source) {
		height = source.height;
		width = source.width;
		buffer = new Vec3<component_t>[height*width];
		memcpy(buffer, source.buffer, height*width * sizeof(math::Vec3<component_t>));
		return *this;
	}

	template <typename T>
	bool Array<T>::operator == (const Array<T> & right) const {
		if ((height != right.height) || (width != right.width))
			return false;
		for (int i = 0; i < height*width; i++) {
			if (!buffer[i].operator == (right.buffer[i]))
				return false;
		}
		return true;
	}

	template <typename T>
	void Array<T>::resize(unsigned int new_width, unsigned int new_height) {
		if ((width == new_width) && (height == new_height))
			return;
		else {
			T* my_new_buffer = new T;
			int counter_1, counter_2, increment_size = 0;
			if (width > new_width)
				increment_size = width - new_width;
			for (int i = 0; i < new_height; i++) {
				for (int j = 0; j < new_width; j++) {
					if ((j < width) && (i < height)) {
						my_new_buffer[counter_2] = buffer[counter_1];
						counter_1 += 1;
						counter_2 += 1;
					}
					else {
						my_new_buffer[counter_2] = 0;
						counter_2 += 1;
					}
				}
				counter_1 += increment_size;
			}
			delete[] buffer;
			buffer = my_new_buffer;
		}
	}

	template <typename T>
	Array<T>::~Array() {}

} // namespace math

#endif