#include "Pixel.h"
#include <iostream>

using namespace std;

Pixel::Pixel() {}


Pixel::Pixel(int numBands) {
	bands.reserve(numBands);
	for (int i = 0; i < numBands; i++) {
		bands.push_back(new layer);
	}
}

void Pixel::print() {
	for (int i = 0; i < bands.size(); i++) {
		cout << "Band ";
		cout << i;
		cout << ": ";
		cout << bands[i]->value;
		cout << "\n\n";
	}
}

bool Pixel::compareBins() {
	for (int i = 1; i < bands.size(); i++) {
		if (bands[i] != bands[i - 1]) {
			return false;
		}
	}
	return true;
}