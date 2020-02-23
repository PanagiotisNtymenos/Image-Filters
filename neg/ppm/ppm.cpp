#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <string.h>
#include <algorithm>
#include "ppm.h"
#include <cmath>   




using namespace std;
int maximum = 0;
float *imaging::ReadPPM(const char * filename, int * width, int * height) {
	string w = "";
	string h = "";
	// Example of reading data from ASCII file
	ifstream file(filename, ios::binary);
	if (!file) {
		cout << "file not found or could not be opened!" << endl;
		return nullptr;
	}
	/* (Checking Header)
	
	We check char by char the heading so that we find the type (P6 supported)
	Then we check all the other info and accept them only if they are positive 
	The program checks for comments (#)
		
	*/

	char sinchar=' ';
	while (sinchar != 'P') {
		file.get(sinchar);
	}

	file.get(sinchar);
	if (sinchar == '6') {
		file.get(sinchar);
		while (sinchar == ' ' || sinchar == '\n' &&  sinchar != EOF) {
			file.get(sinchar);
			if (sinchar == '#') {
				while (sinchar != '\n') {
					file.get(sinchar);
				}
			}
		}
		w; w.push_back(sinchar);
		file.get(sinchar);
		while ((sinchar != ' ' && sinchar != '\n' && sinchar != EOF)) {
			w.push_back(sinchar);
			file.get(sinchar);
			if (sinchar == '#') {
				while (sinchar != '\n') {
					file.get(sinchar);
				}
			}
		}

		//
		while (sinchar == ' ' || sinchar == '\n' &&  sinchar != EOF) {
			file.get(sinchar);
			if (sinchar == '#') {
				while (sinchar != '\n') {
					file.get(sinchar);
				}
			}

		}
		h; h.push_back(sinchar);
		file.get(sinchar);
		while ((sinchar != ' ' && sinchar != '\n' && sinchar != EOF)) {
			h.push_back(sinchar);
			file.get(sinchar);
			if (sinchar == '#') {
				while (sinchar != '\n') {
					file.get(sinchar);
				}
			}
		}
		

		//
		while (sinchar == ' ' || sinchar == '\n' &&  sinchar != EOF) {
			file.get(sinchar);
			if (sinchar == '#') {
				while (sinchar != '\n') {
					file.get(sinchar);
				}
			}
		}
		string max; max.push_back(sinchar);
		file.get(sinchar);
		while ((sinchar != ' ' && sinchar != '\n' && sinchar != EOF)) {
			max.push_back(sinchar);
			file.get(sinchar);
			if (sinchar == '#') {
				while (sinchar != '\n') {
					file.get(sinchar);
				}
			}
		}

		maximum = stoi(max);
		*width = stoi(w);
		*height = stoi(h);
		if (maximum > 255 || maximum < 0 ){
			cout << "Error 404 .Not correct color depth found!24bit is the max accepted" << endl;
			file.close();
			return nullptr;

		}
		if (*width< 1) {
			cout << "Error 404 .Width must be greater than 1" << endl;
			file.close();
			return nullptr;

		}
		if (*height< 1) {
			cout << "Error 404 .Height must be greater than 1" << endl;
			file.close();
			return nullptr;
		}
	}
	else {
		cout << "Wrong Format: Type not P6" << endl;
		file.close();
	}
	/* Buffer
	first we find the size of the buffers and then we create two buffers (1 float and 1 unsigned char)
	we read the ppm info in the unsigned char one and then we pass it to float one
	Buffers will be deleted!
	*/
		int size = 3 * *width**height;
		
		float* flbuffer = new float[size];
		int i = 0;
		unsigned char * buffer = new unsigned char[size];
		file.read((char *)buffer, size);
		for (i = 0; i<size; i++){
			flbuffer[i] = (int)buffer[i] / (float)maximum;
		}
		delete[]buffer;
		return flbuffer;
	}

	bool imaging::WritePPM(const float * data, int w, int h, const char * filename) {
		fstream oFile(filename, ios::out | ios::binary);

		if (!oFile.is_open()) {
			printf("Could not open file!\n");
			return false;
		}
		// Safely use the file stream
		else {
			// Outputs to ppm file that is created
			string text = "P6\n" + std::to_string(w) + "\n" + std::to_string(h) + "\n"+std::to_string(maximum) +"\n";
			oFile.write(text.c_str(), text.size());
			
			unsigned char * temp = new unsigned char[3*w*h];//declaring a new buffer
			for (int i = 0; i <3*w*h; i++) {
				temp[i] =data[i]* maximum;//pass the float data to the unsigned char one 
			}
			oFile.write((char*)temp, 3*w*h);//write them to the file
			oFile.close();
			return true;	
		}		
	}
