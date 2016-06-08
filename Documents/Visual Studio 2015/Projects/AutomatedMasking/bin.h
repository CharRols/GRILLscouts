#pragma once
#include <vector>
#include <iostream>
#include <string>


using namespace std;

struct imagePixel {
	vector<float> bands;
	//string binNumber;

	imagePixel(int numBands) {
		bands.reserve(numBands);
	}

	imagePixel(vector<float> bandsSet) {
		for (int i = 0; i < bands.size(); i++) {
			bands[i] = bandsSet[i];
		}
	}

	void print() {
		//cout << "Band: " << bandName << "\nContains: ";
		for (int i = 0; i < bands.size(); i++) {
			cout << bands[i] << " ";
		}
		//cout << "In bin: " << binNumber;
	}
};


class Bin{
public:
	Bin();
	Bin(string, int, int);
	void clear();
	void print();
	void makePixel(vector<float>);
	float calculateMean(int);

	vector<imagePixel*> pixels;
	vector<float> mean;
	string name;

private:


};
