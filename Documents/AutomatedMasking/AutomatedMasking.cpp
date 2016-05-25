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

	vector<Pixel> pixels(totalPixels);
	int numMeans = numberOfBins * numberOfBands;
	//totalPixels = totalPixels * numBands;
	//vector<float> pixelBands(totalPixels * numBands);
	vector<float> means(numMeans);
	vector<float> oldMeans(numMeans);
	vector<Bin> bins(numberOfBins);

	//fill pixels with random values - this will eventually be filling with pixel values from images
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
	

	cout << "\nWhat are the initial means? Hit Enter between each one. \n"; //Eventually replace with clicked-on pixels
	int count = 0;
	for (int i = 0; i < numberOfBins; i++) {
		for (int j = 0; j < numberOfBands; j++) {
			cout << bins[i].name << " " << bins[i].bands[j]->bandName << ": ";
			cin >> means[count];
			bins[i].bands[j]->mean = means[count];
			count++;
		}
	}

	int binNumber;
	float distance, lowest;
	bool differentMeans = true;
	int recalculated = 0;
	while (!(means == oldMeans)) {
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
						distance = distance - (distance * 2);
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
		count = 0;
		for (int i = 0; i < numberOfBins; i++) {
			for (int j = 0; j < numberOfBands; j++) {
				oldMeans[count] = means[count];
				means[count] = bins[i].bands[j]->calculateMean();
				count++;
			}
		}
		recalculated++;
	}//end while

	for (int i = 1; i < totalPixels; i++) {
		for (int j = 0; j < numberOfBands; j++) {
			if (pixels[i].bands[j]->bin != pixels[i - 1].bands[j]->bin) {
				
			}
		}

	}



	//cout << "Means: ";
	//for (int i = 0; i < means.size(); i++) {
	//	cout << means[i] << " ";
	//}
	//cout << "\nOld Means: ";
	//for (int i = 0; i < oldMeans.size(); i++) {
	//	cout << oldMeans[i] << " ";
	//}
	cout << "\n";
	for (int i = 0; i < numberOfBins; i++) {
		bins[i].print();
	}

	system("PAUSE");
}//End main