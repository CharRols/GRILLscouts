#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "opencv2\opencv.hpp"

using namespace cv;
using namespace std;

struct imagePixel {
	vector<uchar> bands;
	int x, y;


	imagePixel(int numBands) {
		bands.resize(numBands, 0);
	}

	imagePixel(vector<uchar> bandsSet, int xCoord, int yCoord) {
		bands.resize(bandsSet.size(), 0);
		for (int i = 0; i < bandsSet.size(); i++) {
			bands[i] = bandsSet[i];
		}

		x = xCoord;
		y = yCoord;

	}

	void print() {
		for (int i = 0; i < bands.size(); i++) {
			cout << bands[i] << " ";
		}
		cout << "\n";
	}
};


class Bin{
public:
	Bin();
	Bin(string, int, int);
	void clear();
	void print();
	void makePixel(vector<uchar>, int, int);
	float calculateMean(int);

	vector<imagePixel*> pixels;
	vector<float> mean;
	string name;

private:


};
