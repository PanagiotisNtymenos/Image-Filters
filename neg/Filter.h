#include "Image.h";
#include <string>
using namespace imaging;
class Filter {
public:

	Filter() {
	}

	Filter(const Filter &src) {	
	}

	virtual Image operator << (const Image & image) = 0;
};