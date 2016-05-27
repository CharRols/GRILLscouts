#include "bin.h"
#include "Pixel.h"
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
	vector<Pixel> pixels(totalPixels);
	vector<Bin> bins(numberOfBins);

	//fill pixels with random values --------------------------------------------------------------------------------------------Fill with pixel values from images
	for (int i = 0; i < totalPixels; i++) {
		pixels[i] = Pixel(numberOfBands);
		for (int j = 0; j < numberOfBands; j++) {
			pixels[i].bands[j]->value = static_cast <float> (rand() % 255);
		}
	}	
		cout << "\nPixels Filled\n";


	//Create bins and set the mean for each
	for (int i = 0; i < numberOfBins; i++) {
		ostringstream convert;
		convert << i;
		string binNumber = convert.str();
		bins[i] = Bin("Feature_" + binNumber, numberOfBands);
	}
	bins.push_back(Bin("Non-Feature Landscape", 1));
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

	//means.reserve(numMeans);
	//vector<float> newMeans(numMeans);
	for (int i = 0; i < numberOfBins; i++) {
		//means[i].push_back(&newMeans);
		for (int j = 0; j < numberOfBands; j++) {
			cout << bins[i].name << " " << bins[i].bands[j]->bandName << ": ";
			means[i][j] = static_cast <float> (rand() % 255);
			bins[i].bands[j]->mean = means[i][j];
			cout << means[i][j] << "\n";
		}
	}

	cout << "\nRandom Means Created\n";

	int binNumber;
	float distance, lowest;
	int recalculated = 0; //-----------------------------------------------------------------------------------------------------For Debug use only
	while (means != oldMeans) {
		for (int i = 0; i < numberOfBins; i++) {
			bins[i].clear();
		}

		for (int i = 0; i < numberOfBands; i++) {
			lowest = 300; //color values only go up to 255 so the first mean will always be closer
			binNumber = -1;
			for (int j = 0; j < totalPixels; j++) {
				for (int k = 0; k < numberOfBins; k++) {
					distance = bins[k].bands[i]->mean - pixels[j].bands[i]->value;

					if (distance < 0) { //if distance is negative make it positive ----------------------------------------------TODO find an abs function for floats
						distance = -distance;
					}
					if (distance < lowest) {
						lowest = distance;
						binNumber = k;
					}//end if
				}//end inner for - iterates through each pixel
				if (binNumber == -1) { //output error message if no bin is assigned
					cout << "\n\nError\n\n";
				}
				else {
					bins[binNumber].bands[i]->points.push_back(pixels[j].bands[i]->value);
					pixels[j].bands[i]->bin = binNumber;
				}
			}//end middle for - iterates through each bin
		}//end outer for - iterates through each band
		
		//set current means to oldMeans and then calculate new means
		for (int i = 0; i < numberOfBins; i++) {
			for (int j = 0; j < numberOfBands; j++) {
				oldMeans[i][j] = means[i][j];
				means[i][j] = bins[i].bands[j]->calculateMean();
			}
		}
 		recalculated++; //-------------------------------------------------------------------------------------------------------For Debug use only
	}//end while

	for (int i = 0; i < totalPixels; i++) {
		if (pixels[i].compareBins()) {
			pixels[i].binNumber = pixels[i].bands[0]->bin;
		}
		else {
			pixels[i].binNumber = (bins.size()-1);
		}
	}

	cout << "\n";
	for (int i = 0; i < numberOfBins; i++) {
		bins[i].print();
	}

	system("PAUSE");
}//End main