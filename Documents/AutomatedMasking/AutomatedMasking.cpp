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
	totalPixels = totalPixels * 2;

	int numberOfBins;
	cout << "How many features do you need classified? ";
	cin >> numberOfBins;

	int numBands;
	cout << "How many bands does the data have? ";
	cin >> numBands;

	vector<Pixel> pixels(totalPixels);
	int numMeans = numberOfBins * numBands;
	//totalPixels = totalPixels * numBands;
	//vector<float> pixelBands(totalPixels * numBands); //changes depending on picture resolution - get from user.
	vector<float> means(numMeans);
	vector<float> oldMeans(numMeans);
	vector<Bin> bins(numberOfBins);

	//fill pixels with random values - this will eventually be filling the vector with pixel values
	for (int i = 0; i < totalPixels; i++) {
		//pixelBands[i] = static_cast <float> (rand() % 255);
		for(int j = 0; j < )
	}	
	




	cout << "\npixels filled\n";
	//Create bins and set the mean for each
	for (int i = 0; i < numberOfBins; i++) {
		ostringstream convert;
		convert << i;
		string binNumber = convert.str();
		bins[i] = Bin("Feature" + binNumber, numBands);
	}
	bins.push_back(Bin("Non-Feature Landscape", 1));
	cout << "Bins Created \n";
	
	cout << "What are the initial means? Hit Enter between each one. \n";
	int count = 0;
	for (int i = 0; i < numberOfBins; i++) {
		for (int j = 0; j < numBands; j++) {
			cout << bins[i].name << " " << bins[i].bands[j]->bandName << ": ";
			cin >> means[count];
			bins[i].bands[j]->mean = means[count];
			count++;
		}
	}

	int binNumber, clusterNumber;
	float distance, lowest;
	bool differentMeans = true;
	while (!(means == oldMeans)) {

		for (int i = 0; i < numberOfBins; i++) {
			bins[i].clear();
		}

		for (int i = 0; i < totalPixels; i++) {
			lowest = 300; //color values only go up to 255 so the first mean will always be closer
			clusterNumber = -1;
			binNumber = -1;
			for (int j = 0; j < numberOfBins; j++) {
				for (int k = 0; k < numBands; k++) {
					distance = bins[j].bands[k]->mean - pixelBands[i];
					//cout << "\n\nMean: ";
					//cout << bins[j].bands[k]->mean;
					//cout << "\npixel value: ";
					//cout << pixels[i];
					//cout << ", ";
					//cout << i;
					if (distance < 0) { //if distance is negative make it positive TODO find an abs function for floats
						distance = distance - (distance * 2);
					}
					//cout << "\nDistance: ";
					//cout << distance;
					//cout << "\nLowest: ";
					//cout << lowest;
					if (distance < lowest) {
						lowest = distance;
						binNumber = j;
						clusterNumber = k;
					}//end if
				}//end inner for - determines which cluster in what bin the pixel belongs in
			}//end middle for
			if (binNumber == -1 || clusterNumber == -1) {
				cout << "\n\nError\n\n";
			}
			else {
				bins[binNumber].bands[clusterNumber]->points.push_back(pixelBands[i]);
			}
		}//end outer for - iterates through each pixel
		
		//set current means to oldMeans and then calculate new means
		count = 0;
		for (int i = 0; i < numberOfBins; i++) {
			for (int j = 0; j < numBands; j++) {
				oldMeans[count] = means[count];
				means[count] = bins[i].bands[j]->calculateMean();
				count++;
			}
		}
	}//end while

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