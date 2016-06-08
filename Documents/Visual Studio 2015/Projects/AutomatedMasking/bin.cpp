#include "bin.h"
#include <sstream>
#include <ostream>

using namespace std;

Bin::Bin(){}

Bin::Bin(string title, int numPixels, int numBands) {
	name = title;
	pixels.reserve(numPixels);
	mean.reserve(numBands);
	for (int i = 0; i < numPixels; i++) {
		pixels.push_back(new imagePixel(numBands));
	//	string bandNum = to_string(i);
	//	pixels[i]->bandName = (bandNum);
	}
}

void Bin::clear() {
	for (int i = 0; i < pixels.size(); i++) {
		pixels[i]->bands.clear();
	}
	//pixels.clear();
}

void Bin::print() {
	for (int i = 0; i < pixels.size(); i++) {
		pixels[i]->print();
	}
}

void Bin::makePixel(vector<float> newBands) {
	pixels.push_back(new imagePixel(newBands));
}

float Bin::calculateMean(int bandNum) {
	float sum = 0;
	for (int i = 0; i < pixels.size(); i++) {
		sum = sum + pixels[i]->bands[bandNum];
	}
	float average = sum / pixels.size();
	return average;
}