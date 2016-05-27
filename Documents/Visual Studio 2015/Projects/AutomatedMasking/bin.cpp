#include "bin.h"
#include <sstream>
#include <ostream>

using namespace std;

Bin::Bin(){}

Bin::Bin(string title, int numBands) {
	name = title;
	bands.reserve(numBands);
	for (int i = 0; i < numBands; i++) {
		bands.push_back(new cluster);
		ostringstream convert;
		convert << i;
		string bandNum = "Band " + convert.str();
		bands[i]->bandName = (bandNum);
	}
}

void Bin::clear() {
	for (int i = 0; i < bands.size(); i++) {
		bands[i]->points.clear();
	}
}

void Bin::print() {
	for (int i = 0; i < bands.size(); i++) {
		bands[i]->print();
	}
}
