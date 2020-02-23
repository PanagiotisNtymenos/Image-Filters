#include <string>
#include "Vec3.h"
#include <vector>

using namespace std;
using namespace math;
	template <typename T> class Array {

	protected:

		vector<T> buffer;                              //! Holds the image data.

		unsigned int width, height;						 //! The width of the image (in pixels)

	public:
		const unsigned int getWidth() const { return width; }
		const unsigned int getHeight() const { return height; }
		T & operator ()(int i, int j) {

		}

		Array() {
			width = 0;
			height = 0;

		}

		vector<T> getRawDataPtr() const {
			return buffer;
		}

		T getContent(unsigned int x, unsigned int y) const {
			if (width < x || height < y) {
				cerr << "width or height out f range" << endl;
				return buffer[0];
			}
			return	buffer[(y)*width + x];
		}

		void setContent(unsigned int x, unsigned int y, T & value) {

			if (width < x || height < y) {
				cerr << "width or height out f range" << endl;
			}
			else {
				buffer[(y)*width + x] = value;
			}
		}

		~Array() {

		}

		Array(const Array &src) {
			this->height = src.getHeight();
			this->width = src.getWidth();
			if (height == 0 || width == 0) {
				cerr << "wrong data" << endl;
			}
			else {
				for (int i = 0; i < height*width; i++) {
					buffer[i] = src.buffer[i];
				}
			}
		}

		Array(unsigned int w, unsigned int h) {
			width = w;
			height = h;
			buffer.clear();
		}

		Array(unsigned int w, unsigned int h, vector<T> & data_ptr) {
			width = w;
			height = h;
			buffer = data_ptr;

		}

		void setData(const T* & data_ptr) {
			if (getHeight() == 0 || getWidth() == 0) {
				cerr << "wrong data" << endl;
			}
			else {
				for (int i = 0; i < getHeight()*getWidth(); i++) {
					buffer[i] = data_ptr[i];

				}
			}

		}

		Array & operator = (const Array & right) {
			Array im;
			im.width = right.getWidth();
			im.height = right.getHeight();
			im.buffer = right.buffer;
			return im;
		}

	};
