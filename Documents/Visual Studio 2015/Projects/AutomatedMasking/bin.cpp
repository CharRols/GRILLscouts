#include "bin.h"
#include <sstream>
#include <ostream>

using namespace cv;
using namespace std;

Bin::Bin(){}

Bin::Bin(string title, int numPixels, int numBands) {
	name = title;
	pixels.reserve(numPixels);
	mean.reserve(numBands);
	for (int i = 0; i < numPixels; i++) {
		pixels.push_back(new imagePixel(numBands));
	}
}

void Bin::clear() {
	pixels.clear();
}

void Bin::print() {
	cout << "Name: " << name << "\n";
	for (int i = 0; i < mean.size(); i++) {
		cout << mean[i] << ", ";
	}
	cout << "\n";
	for (int i = 0; i < pixels.size(); i++) {
		cout << "pixel " << i << ": ";
		pixels[i]->print();
	}
	cout << "\n";
}

void Bin::makePixel(vector<uchar> newBands, int xCoord, int yCoord) {
	pixels.push_back(new imagePixel(newBands, xCoord, yCoord));
}

float Bin::calculateMean(int bandNum) {
	float sum = 0;
	for (int i = 0; i < pixels.size(); i++) {
		sum = sum + pixels[i]->bands[bandNum];
	}
	float average = sum / pixels.size();
	return average;
}