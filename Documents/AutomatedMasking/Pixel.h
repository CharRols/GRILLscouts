#pragma once
#include <vector>

using namespace std;

class Pixel {
public:
	vector<float> bands;
	int binNumber;

	Pixel();
	Pixel(int);
	void print();
};