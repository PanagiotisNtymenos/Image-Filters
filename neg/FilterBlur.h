#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace imaging;

class FilterBlur :public Filter {
private:
	int N;
	int tx;
	int ty;
public:
	void setN(int N) {
		this->N = N;
		}

	virtual Image operator << (const Image & image) {
		Image im = Image(image.getWidth(), image.getHeight(), image.getRawDataPtr());
		Vec3<float> vec;
		if (N % 2 != 0&& N>=1) {
			for (int i = 0; i < im.getHeight(); i++) {
				for (int j = 0; j < im.getWidth(); j++) {
					float totalx = 0;
					float totaly = 0;
					float totalz = 0;

					for (int m = -N / 2; m <= N/ 2; m++) {
						for (int n = -N / 2; n <= N / 2; n++)
						{
							tx = i + m;
							ty = j + n;
							if (tx >= 0 && ty < im.getWidth() && ty >= 0 && tx < im.getHeight())
							{

								vec = im.getContent(ty, tx);
								totalx += vec.x;
								totaly += vec.y;
								totalz += vec.z;
							}
						}

					}

					vec = Vec3<float>(totalx / (N*N), totaly / (N*N), totalz / (N*N));
					vec = vec.clampToUpperBound(1.0f);
					vec = vec.clampToLowerBound(0);
					im.setContent(j, i, vec);

				}
			}
		}
		else {
			cout << "No filter applied because with N=" << N << " no square with center (i,j) could be created!"<<endl;
		}
		return im;
	}

};