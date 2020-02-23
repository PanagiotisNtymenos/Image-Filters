#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <string.h>
#include <algorithm>
#include "Image.h"
#include "FilterLinear.h"
#include "FilterGamma.h"
#include "FilterBlur.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	string format = "";
	Image im2;
	FilterLinear filt1;
	FilterGamma filt2;
	FilterBlur filt3;
	float linear[6];
	float gamma;
	int blur;
	std::string filename="";
	if (argc > 1) {
		filename = argv[argc-1];
	}
	if (filename.length() >= 5) {
	    format = filename.substr(filename.length() - 4); //take the ending of the name given so that we can check the format
		filename.pop_back();//remove m
		filename.pop_back();//remove p
		filename.pop_back();//remove p
		filename.pop_back();//remove .
	}
	int i = 1;
	bool flag = im2.load(filename, format);
	while (i < argc-1&&flag) {
		if (argv[i] == std::string("-f")) {
			i++;
			if (argv[i] == std::string("linear")) {
				i++;
				
				for (int j = 0; j < 6; j++) {
					if (i >= argc - 1)
						flag = false;
					linear[j] = atof(argv[i]);
					i++;
				}
				filt1.seta(linear[0], linear[1], linear[2]);
				filt1.setc(linear[3], linear[4], linear[5]);
				im2=(filt1 << (im2));
			}
			else if (argv[i] == std::string("gamma")) {
				i++;
				if (i >= argc - 1)
					flag = false;
				gamma = atof(argv[i]);
				i++;
				filt2.setg(gamma);
				im2=(filt2 << (im2));
				
			}
			else if (argv[i] == std::string("blur")) {
				i++;
				if (i >= argc - 1)
					flag = false;
				blur = atoi(argv[i]);
				i++;
				filt3.setN(blur);
				im2 = (filt3 << (im2));
			}
			else {
				cerr << "Not a valid Filter read" << endl;
				flag = false;
				break;
			}

		}
		else {
			cout<<"An Error Occured while trying to load filter !" << endl;
			flag = false;
			break;
		}
	}
		if (flag) {
			cout<<"Height :"<<im2.getHeight()<<" Width: "<< im2.getWidth() << endl;
			if ((im2).save(filename, format))
			{
				cout << "Programm ended. New image name 'filtered_" <<filename<<format<<"'"<< endl;
			}
			else {
				cout << "Image Loaded but Error ocurred in save proccess";
			}
		}
}
