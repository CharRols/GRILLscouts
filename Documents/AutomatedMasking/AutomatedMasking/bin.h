#pragma once
#include <vector>
#include <iostream>
#include <string>


using namespace std;

struct cluster {
	vector<float> points;
	float mean;
	string bandName;


	float calculateMean() {
		float average = 0;
		for (int i = 0; i < points.size(); i++) {
			average = average + points[i];
		}
		average = (average / points.size());
		mean = average;
		return average;
	}

	void print() {
		cout << "Name: " << bandName << "\nContains: ";
		for (int i = 0; i < points.size(); i++) {
			cout << points[i] << " ";
		}
		cout << "\nMean: " << mean << "\n\n";
	}
};


class Bin{
public:
	Bin();
	Bin(string, int);
	void clear();
	void print();

	vector<cluster*> bands;
	string name;

private:


};
