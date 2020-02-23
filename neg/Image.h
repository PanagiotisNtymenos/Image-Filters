//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2017 - 2018
//
//

#ifndef _IMAGE
#define _IMAGE

#include <iostream>
#include "ppm/ppm.h"
#include "Vec3.h"
#include <vector>
#include <string>

using namespace std;
using namespace math;
/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation. 
 */ 
namespace imaging
{
#include "Array.h"
//------------------------------------ class Image ------------------------------------------------

	/*! It is the class that represents a generic data container for an image.
	 * 
	 * It holds the actual buffer of the pixel values and provides methods for accessing them, 
	 * either as individual pixels or as a memory block. The Image class alone does not provide 
	 * any functionality for loading and storing an image, as it is the result or input to such a procedure. 
	 *
	 * The internal buffer of an image object stores the actual bytes (data) of the color image as
	 * a contiguous sequence of Color structures. Hence, the size of the buffer variable holding these data is 
	 * width X height X sizeof(Color) bytes.
	 *
	 * All values stored in the Color data type components are assumed to be floating point values and for typical (normalized)
	 * intensity ranges, each color component is within the range [0.0, 1.0].
	 */ 
	class Image :public Array<Vec3<float>>
	{
	protected:


	

	public:
		Image():Array() {
			
		}

		Image(const Image &src) {
			this->height = src.getHeight();
			this->width = src.getWidth();
			if (height == 0 || width == 0) {
				cerr << "wrong data" << endl;
			}
			else {
				this->buffer=src.getRawDataPtr();
			}
		}

		~Image() {

		}

		Image(unsigned int w, unsigned int h):Array(w, h) {
		}

		Image(unsigned int w, unsigned int h, vector<Vec3<float>> & data_ptr) :Array(w, h,data_ptr){
			
		}

		Image & operator = (const Image & right) {
			if (this != &right) {
				this->width = right.getWidth();
				this->height = right.getHeight();
				this->buffer = right.buffer;
			}
			return *this;
		}

		bool Image::load(const std::string & filename, const std::string & format) {

			if (format != ".ppm") {
				cerr << "Image should be of format ppm" << endl;

				return false;
			}
			else {
				int w = width;
				int h = height;
				buffer.reserve(3 * w*h);
				string filewithform;
		 		filewithform = filename + format;
				const char *filen = filewithform.c_str();
				float *flarray = imaging::ReadPPM(filen, &w, &h);
				if (w == 0) {
					return false;
				}

				int k = 0;
				
				for (int i = 0; i < 3 * w*h - 2; i += 3) {
					buffer.push_back(Vec3<float>(flarray[i], flarray[i + 1], flarray[i + 2]));
					k++;
				}
				width = w;
				height = h;
				delete[]flarray;
				
				return true;
			}
		}
		bool Image::save(const std::string & filename, const std::string & format) {
			int k = getWidth()*getHeight();
			if (k == 0) {			//the Image is not initiallized and thus false is returned
				return false;
			}
			
			
			if (format != ".ppm") {
				cerr << "ERROR: Format should be ppm" << endl;
				return false;
			}
			string filewithform ="filtered_"+ filename + format;
			const char *filnew = filewithform.c_str();
			float *temp = new float[3*k];
			int i = 0;
			for (int j=0; j < 3*k-1; j=j+3) {
					temp[j] = buffer[i].r;
					temp[j + 1] = buffer[i].g;
					temp[j + 2] = buffer[i].b;
				i++;
			}
			imaging::WritePPM(temp,getWidth(),getHeight(), filnew);
			delete[]temp;
			buffer.clear();
			buffer.shrink_to_fit();
			return true;
		}

	};

} //namespace imaging

#endif