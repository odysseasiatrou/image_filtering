#include <iostream>
#include <string>
#include "ppm_format.h"
#include "Image.h"
#include "gray_filter.h"
#include "color_filter.h"
#include "blur_filter.h"
#include "diff_filter.h"
#include "median_filter.h"
#include <fstream>
#include <vector>


typedef float component_t;
typedef math::Array<math::Vec3<imaging::component_t>> Color;

using namespace std;

int main(int argc, char* argv[])
{
	char command[250];
	string filename = "";
	string auxiliary = "";
	float r = -1.0;
	float g = -1.0;
	float b = -1.0;
	string red = "";
	string green = "";
	string blue = "";
	imaging::Image image = imaging::Image();
	cout << "Apply filters and image file name : ";
	cin.getline(command, 250);
	int i = 0;
	int j = 0;
	while (command[i] != '\0'&&i<250) {
		if (command[i] == ' ')
			j = i + 1;
		i++;
	}
	for (int k = j; k <= i; k++) {
		filename += command[k];
	}
	image.operator<<(filename);
	filename = "";
	for (int k = j; k <= i; k++) {
		filename += command[k];
		if (command[k + 1] == '.')
			filename += "filtered";
	}
	bool flag = false;
	for (int k = 1; k < j - 1; k++) {
		if (flag&&command[k] != ' ') {
			auxiliary += command[k];
			if (command[k + 1] == ' ') {
				flag = false;
				if (!auxiliary.compare("gray")) {
					filtering::gray_filter flt = filtering::gray_filter();
					image = imaging::Image(flt.operator<<(image));
					image.operator >> (filename);
				}
				else if (!auxiliary.compare("color")) {
					int l = k + 1;
					while (b == -1.0) {
						if (command[l] != ' ') {
							if (r == -1.0)
								red += command[l];
							else if (g == -1.0)
								green += command[l];
							else if (b == -1.0)
								blue += command[l];
							flag = true;
						}
						else if (flag) {
							if (r < 0)
								r = atoi(&red[0]);
							else if (g < 0)
								g = atoi(&green[0]);
							else
								b = atoi(&blue[0]);
						}
						l++;
					}
					flag = false;
					filtering::color_filter flt = filtering::color_filter(r, g, b);
					r = -1.0, g = -1.0, b = -1.0;
					red = "", green = "", blue = "";
					image = imaging::Image(flt.operator<<(image));
					image.operator >> (filename);
				}
				else if (!auxiliary.compare("blur")) {
					filtering::blur_filter flt = filtering::blur_filter();
					image = imaging::Image(flt.operator<<(image));
					image.operator >> (filename);
				}
				else if (!auxiliary.compare("diff")) {
					filtering::diff_filter flt = filtering::diff_filter();
					image = imaging::Image(flt.operator<<(image));
					image.operator >> (filename);
				}
				else if (!auxiliary.compare("median")) {
					filtering::median_filter flt = filtering::median_filter();
					image = imaging::Image(flt.operator<<(image));
					image.operator >> (filename);
				}
				else {
					cerr << "Error filter missing" << endl;
					return 0;
				}
				auxiliary = "";
			}
		}
		if (command[k] == 'f'&&command[k - 1] == '-')
			flag = true;
	}
	return 0;
}

imaging::Image * imaging::ReadPPM(const char * filename)
{
	fstream image_file;
	string line;
	string my_auxiliary_string = "";
	image_file.open(filename, std::fstream::in);
	int counter = 0;
	int index = 0;
	Image* image = nullptr;
	if (image_file.is_open()) {
		while (getline(image_file, line)) {
			for (char c : line) {
				if (counter > 3)
					break;
				if (c != ' ' && c != '\t')
					my_auxiliary_string += c;
				else {
					my_auxiliary_string += c;
					counter++;
				}
				index++;
			}
			if (counter > 3)
				break;
			my_auxiliary_string += ' ';
			counter++;
			index++;
		}

		int auxiliary_counter = 0;
		string head = "";
		string height_string = "";
		string width_string = "";
		string code_sys = "";
		for (char c : my_auxiliary_string) {
			if (c == ' ')
				auxiliary_counter++;
			else {
				switch (auxiliary_counter) {
				case 0:
					head += c;
					break;
				case 1:
					height_string += c;
					break;
				case 2:
					width_string += c;
					break;
				case 3:
					code_sys += c;
					break;
				default:
					break;
				}
			}
		}
		if (head != "P6") {
			cerr << "ERROR with image infos : wrong image format" << endl;
			exit(0);
		}
		if (code_sys != "255") {
			if (height_string == "255" || width_string == "255") {
				cerr << "ERROR with image infos : information missing" << endl;
				exit(0);
			}
			else {
				cerr << "ERROR with image infos : pixels are formatted in non readable type" << endl;
				exit(0);
			}
		}
		unsigned int height = atoi(height_string.c_str());
		unsigned int width = atoi(width_string.c_str());
		image_file.close();
		ifstream imageFile;
		imageFile.open(filename, ios::in | ios::binary | ios::ate);
		imageFile.seekg(0, ios::end);
		size_t imageSize = imageFile.tellg();
		const int image_size = 3 * height*width;
		if (static_cast<int>(imageSize) != image_size + index) {
			cerr << "ERROR with image data : pixels missing" << endl;
			exit(0);
		}
		imageFile.seekg(0, ios::beg);
		imageFile.seekg(index);
		char* pixel_data = new char[image_size + 1];
		imageFile.read(pixel_data, image_size);
		pixel_data[image_size] = '\0';
		imageFile.close();
		component_t* pixel_buffer = new component_t[image_size];
		component_t pixel_value = 0;
		for (int i = 0; i < image_size; i++) {
			pixel_value = (component_t)((unsigned char)pixel_data[i]);
			pixel_value /= 255.0f;
			pixel_buffer[i] = pixel_value;
		}
		const component_t* buffer = pixel_buffer;
		image = new Image(width, height, buffer);
		delete[] pixel_data;
		delete[] pixel_buffer;
	}
	else {
		cerr << "File missing" << endl;
	}
	return image;
}

bool imaging::WritePPM(Image & image, const char * filename) {
	ofstream file;
	file.open(filename);
	file << "P6 " << image.getHeight() << " " << image.getWidth() << " 255\n";
	file.close();
	file.open(filename, ios::out | ios::app | ios::binary);
	Color* buffer = image.getRawDataPtr();
	char* pixel_to_write = new char[3 * image.getHeight()*image.getWidth()];
	for (int i = 0; i < 3 * image.getHeight()*image.getWidth(); i += 3) {
		Color clr = buffer[i / 3].operator*(255.0f);
		pixel_to_write[i] = (char)clr.operator[](0);
		pixel_to_write[i + 1] = (char)clr.operator[](1);
		pixel_to_write[i + 2] = (char)clr.operator[](2);
	}
	file.write(pixel_to_write, 3 * image.getWidth()*image.getHeight());
	file.close();
	delete[] pixel_to_write;
	return false;
}