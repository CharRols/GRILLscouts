#pragma once
#include <vector>

using namespace std;

struct layer {
	int bin;
	float value;
};

class Pixel {
public:
	vector<layer*> bands;
	int binNumber;

	Pixel();
	Pixel(int);
	void print();
	bool compareBins();
};