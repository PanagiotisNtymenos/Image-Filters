#include <iostream>
#include <vector>
#include <string>

using namespace imaging;

class FilterGamma :public Filter {

private:
	float g;
public:
	FilterGamma() {

	}
	void setg(float g) {
		this->g = g;
	}

	FilterGamma(const FilterGamma &src) {
		this->setg(src.g);
		}

	virtual Image operator << (const Image & image) {
		Image im = Image(image.getWidth(), image.getHeight(), image.getRawDataPtr());
		Vec3<float> x;
		if (g >= 0.5&&g <= 2.0) {
			for (int i = 0; i < im.getHeight(); i++) {
				for (int j = 0; j < im.getWidth(); j++) {
					x = image.getContent(j, i);
					x = Vec3<float>(pow(x.r, g), pow(x.g, g), pow(x.b, g));
					x = x.clampToLowerBound(0);
					x = x.clampToUpperBound(1.0f);
					im.setContent(j, i, x);
				}
			}
		}
		else {
			cout << "gamma value should be between 0.5 and 2 .Given Value: " << g << "!" << endl;
		}
		return im;
	}

};