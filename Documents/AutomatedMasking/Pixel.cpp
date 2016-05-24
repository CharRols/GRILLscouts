#include "Pixel.h"
#include <iostream>

using namespace std;

Pixel::Pixel() {}


Pixel::Pixel(int numBands) {
	bands.reserve(numBands);
}

void Pixel::print() {
	for (int i = 0; i < bands.size(); i++) {
		cout << "Band ";
		cout << i;
		cout << ": ";
		cout << bands[i];
		cout << "\n\n";
	}
}