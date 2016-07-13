#pragma once
#include <vector>
#include <iostream>
#include <string>


using namespace std;

struct imagePixel {
	vector<float> bands;

	imagePixel(int numBands) {
		bands.resize(numBands, 0);
	}

	imagePixel(vector<float> bandsSet) {
		bands.resize(bandsSet.size(), 0);
		for (int i = 0; i < bandsSet.size(); i++) {
			bands[i] = bandsSet[i];
		}
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
	void makePixel(vector<float>);
	float calculateMean(int);

	vector<imagePixel*> pixels;
	vector<float> mean;
	string name;

private:


};
