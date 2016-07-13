#include "bin.h"
#include <iostream>
#include <sstream>
//#include "opencv\sources\modules\core\include\opencv2\core.hpp"
//#include "mat.hpp"

using namespace std;

int main() {
	int totalXPixels;
	int totalYPixels;
	int totalPixels;
	cout << "What is the X resolution of your images? ";
	cin >> totalXPixels;

	cout << "What is the Y resolution of your images? ";
	cin >> totalYPixels;
	totalPixels = totalXPixels * totalYPixels;

	int numberOfBins = 4;
	while (numberOfBins > 3) {
		cout << "How many features do you need classified? (Up to 3)";
		cin >> numberOfBins;
	}

	vector<float> percentages;
	percentages.resize(numberOfBins);
	for (int i = 0; i < numberOfBins; i++) {
		percentages[i] = 150;
		while (percentages[i] > 100 || percentages[i] < 0) {
			cout << "What percentage of the satellite data do you want to show through?";
			cin >> percentages[i];
		}
		percentages[i] = (percentages[i] / 100) * 255; //multiply by 255 because that the max value for rgb color
	}

	int numberOfBands;
	cout << "How many bands does the data have? ";
	cin >> numberOfBands;
	int numMeans = numberOfBins * numberOfBands;

	vector<vector<float>> means(numberOfBins, vector<float>(numberOfBands));
	vector<vector<float>> oldMeans(numberOfBins, vector<float>(numberOfBands));
	vector<vector<float>> pixels(totalPixels, vector<float>(numberOfBands));
	vector<Bin> bins(numberOfBins);
	//---------------------------------------------------------------------------------------------------------------------------Input an image

	//fill pixels with random values --------------------------------------------------------------------------------------------Replace with fill with pixel values from images
	for (int i = 0; i < totalPixels; i++) {
		for (int j = 0; j < numberOfBands; j++) {
			pixels[i][j] = static_cast <float> (rand() % 255);
		}
	}
	cout << "\nPixels Filled\n";


	//Create bins and set the mean for each
	for (int i = 0; i < numberOfBins; i++) {
		string binNum = to_string(i);
		bins[i] = Bin("Feature_" + binNum, totalPixels, numberOfBands);
	}
	bins.push_back(Bin("Non-Feature Landscape", totalPixels, numberOfBands));
	cout << "\nBins Created\n";

	//Assign random means to each bin
	for (int i = 0; i < numberOfBins; i++) {//-------------------------------------------------------------------------------------Replace with clicked-on pixels (Drag a section and take euclidean distance of that for initial means?)
		for (int j = 0; j < numberOfBands; j++) {
			cout << bins[i].name << " ";
			bins[i].mean.resize(numberOfBands);
			bins[i].mean[j] = static_cast <float> (rand() % 255);
			means[i][j] = bins[i].mean[j];
			cout << means[i][j] << "\n";
		}
	}

	cout << "\nRandom Means Created\n";

	int binNumber;
	float distance = 0;
	float lowest;
	int recalculated = 0; //-------------------------------------------------------------------------------------------------------For Debug use only
	while (means != oldMeans) {
		for (int i = 0; i < numberOfBins; i++) {
			bins[i].clear();
		}

		for (int j = 0; j < totalPixels; j++) {
			//with a max of 255 for each band in a pixel, the max distance between two pixels is ~800 if there are 10 bands. The max number of bands
			//that this will currently be used is 7, so setting lowest to 1000 makes sure that the first bin will always initially be the lowest.
			lowest = 1000; 
			binNumber = -1;
			for (int k = 0; k < numberOfBins; k++) {
				for (int i = 0; i < numberOfBands; i++) {
					distance = distance + pow((bins[k].mean[i] - pixels[j][i]), 2);
				}//end inner for - iterates through every band
				distance = sqrt(distance); // Euclidian Distance from pixel to mean through n dimensions, where n is the number of bands in the image

				if (distance < lowest) {
					lowest = distance;
					binNumber = k;
				}//end if
			}//end middle for - iterates through each bin
			
			if (binNumber == -1) { //output error message if no bin is assigned
				cout << "\n\nError\n\n";
			}
			else {
				bins[binNumber].makePixel(pixels[j]);
			}
		}//end outer for - iterates through each pixel

		//set current means to oldMeans and then calculate new means
		for (int i = 0; i < numberOfBins; i++) {
			for (int j = 0; j < numberOfBands; j++) {
				oldMeans[i][j] = means[i][j];
				means[i][j] = bins[i].calculateMean(j);
			}
		}
		recalculated++; //-------------------------------------------------------------------------------------------------------For Debug use only
	}//end while

	cout << "\n";
	for (int i = 0; i < numberOfBins; i++) {
		bins[i].print();
	}

	//---------------------------------------------------------------------------------------------------------------------------Output new image
	system("PAUSE");
}//End main