#include <iostream>
#include <vector>
#include "Filter.h"
#include <string>

using namespace imaging;

class FilterLinear :public Filter {

private:
	float a1, a2, a3, c1, c2, c3;
public:
	FilterLinear() {

	}
	void seta(float A1, float A2, float A3) {
		a1 = A1;
		a2 = A2;
		a3 = A3;
	}

	void setc(float A1, float A2, float A3) {
		c1 = A1;
		c2 = A2;
		c3 = A3;
	}

	FilterLinear(const FilterLinear &src) {
		this->seta(src.a1, src.a2, src.a3);
		this->setc(src.c1, src.c2, src.c3);
	}

	virtual Image operator << (const Image & image) {
		Image im = Image(image.getWidth(), image.getHeight(), image.getRawDataPtr());
		Vec3<float> x;
		for (int i = 0; i < im.getHeight(); i++) {
			for (int j = 0; j < im.getWidth(); j++) {
				x = image.getContent(j, i);
				x = Vec3<float>(a1*x[0] + c1, a2*x[1] + c2, a3*x[2] + c3);
				x=x.clampToLowerBound(0);
				x=x.clampToUpperBound(1.0f);
				im.setContent(j,i, x);
			}
		}
		return im;
	}
};