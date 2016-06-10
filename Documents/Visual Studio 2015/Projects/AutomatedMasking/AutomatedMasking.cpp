#include "bin.h"
#include <iostream>
#include <sstream>

using namespace std;

int main() {
	int totalPixels;
	string str;
	cout << "What resolution are your images? ";
	cin >> totalPixels;
	totalPixels = totalPixels * totalPixels;

	int numberOfBins;
	cout << "How many features do you need classified? ";
	cin >> numberOfBins;

	int numberOfBands;
	cout << "How many bands does the data have? ";
	cin >> numberOfBands;
	int numMeans = numberOfBins * numberOfBands;

	vector<vector<float> > means(numberOfBins, vector<float>(numberOfBands));
	vector<vector<float>> oldMeans(numberOfBins, vector<float>(numberOfBands));
	vector<vector<float>> pixels(totalPixels, vector<float>(numberOfBands));
	//vector<Pixel> pixels(totalPixels);
	vector<Bin> bins(numberOfBins);

	//fill pixels with random values --------------------------------------------------------------------------------------------Fill with pixel values from images
	for (int i = 0; i < totalPixels; i++) {
		//pixels[i] = Pixel(numberOfBands);
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

	//cout << "\nWhat are the initial means? Hit Enter between each one. \n"; //---------------------------------------------------Replace with clicked-on pixels
	//int count = 0;
	//for (int i = 0; i < numberOfBins; i++) {
	//	for (int j = 0; j < numberOfBands; j++) {
	//		cout << bins[i].name << " " << bins[i].bands[j]->bandName << ": ";
	//		cin >> means[count];
	//		bins[i].bands[j]->mean = means[count];
	//		count++;
	//	}
	//}

	for (int i = 0; i < numberOfBins; i++) {
		//bins[i].addPixel(numberOfBands); --Not needed, pixels are created when the bin is
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
			lowest = 450; 
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

	system("PAUSE");
}//End main