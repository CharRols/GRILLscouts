#include "bin.h"
#include <iostream>
#include <sstream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int totalXPixels;
int totalYPixels;
int totalPixels;
const int numberOfBands = 3;
vector<vector<uchar>> pixels(totalPixels, vector<uchar>(numberOfBands));
vector<vector<int>> coordinates(totalPixels, vector<int>(2));

vector<vector<uchar>> fillPixels(Mat inputImage) {
	int currentPixel = 0;
	for (int i = 0; i < totalXPixels; i++) {
		for (int j = 0; j < totalYPixels; j++) {
			Vec3b intensity = inputImage.at<Vec3b>(Point(j, i));
			vector<uchar> pixelValues (numberOfBands);
			coordinates[currentPixel] = { i, j };
			
			for (int k = 0; k < numberOfBands; k++) {
				pixels[currentPixel][k] = intensity.val[k];
			}

			currentPixel++;
		}
	}

	cout << "Pixels filled \n";
	return pixels;
}



vector<vector<uchar>> getUserInput(int* numberOfBins, vector<float>* percentages) {

	cout << "Your image must be regular 3 channel RGB \n";

	string inputFile;
	cout << "Where is your image loacted?"; //--------------------------------------------------------------------------------------------Replace with file explorer
	getline (cin, inputFile);
	Mat inputImage = imread(inputFile);

	totalXPixels = inputImage.rows;
	totalYPixels = inputImage.cols;
	totalPixels = totalYPixels * totalXPixels;

	while (*numberOfBins != 1 && *numberOfBins != 2 && *numberOfBins != 3) {
		cout << "How many features do you need classified? (Up to 3) \n";
		cin >> *numberOfBins;
	}

	
	percentages->resize(*numberOfBins);
	for (int i = 0; i < *numberOfBins; i++) {
		percentages->at(i) = 150;
		while (percentages->at(i) > 100 || percentages->at(i) < 0) {
			cout << "What percentage of the satellite data for feature " << i << " do you want to show through?";
			cin >> percentages->at(i);
		}
		percentages->at(i) = (percentages->at(i) / 100) * 255;
	}


	return fillPixels(inputImage);
}



void getDistance(vector<vector<float>> oldMeans, vector<vector<float>> means, int numberOfBins, 
	vector<Bin>* bins) {

	int binNumber;
	float distance = 0;
	float lowest;
	int recalculated = 0; //-------------------------------------------------------------------------------------------------------For Debug use only
	while (means != oldMeans) {
		for (int i = 0; i < numberOfBins; i++) {
			bins->at(i).clear();
		}

		for (int j = 0; j < totalPixels; j++) {
			//with a max of 255 for each band in a pixel, the max distance between two pixels is ~800 if there are 10 bands. The max number of bands
			//that this will currently be used is 7, so setting lowest to 1000 makes sure that the first bin will always initially be the lowest.
			lowest = 1000;
			binNumber = -1;
			for (int k = 0; k < numberOfBins; k++) {
				for (int i = 0; i < numberOfBands; i++) {
					distance = distance + pow((bins->at(k).mean[i] - pixels[j][i]), 2);
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
				bins->at(binNumber).makePixel(pixels[j]);
			}
		}//end outer for - iterates through each pixel

		 //set current means to oldMeans and then calculate new means
		for (int i = 0; i < numberOfBins; i++) {
			for (int j = 0; j < numberOfBands; j++) {
				oldMeans[i][j] = means[i][j];
				means[i][j] = bins->at(i).calculateMean(j);
			}
		}
		recalculated++; //-------------------------------------------------------------------------------------------------------For Debug use only
	}//end while

}



void outputMask(vector<Bin> bins, int numberOfBins) {
	string outputPath;
	cout << "Input the path where you want to save the output file: ";
	cin >> outputPath;

	Mat outputImage;
	
	int currentPixel = 0;
	for (int i = 0; i < totalXPixels; i++) {
		for (int j = 0; j < totalYPixels; j++) {
			Vec3b pixel(numberOfBands);
			for (int k = 0; k < numberOfBands; k++) {
				outputImage.at<uchar>(j, i);
			}			
			currentPixel++;
		}
	}

	imwrite(outputPath, outputImage);


}



int main() {
	int numberOfBins;
	const int numberOfBands = 3;
	vector<float> percentages;
	
	vector<vector<uchar>> pixels = getUserInput(&numberOfBins, &percentages);

	vector<vector<float>> means(numberOfBins, vector<float>(numberOfBands));
	vector<vector<float>> oldMeans(numberOfBins, vector<float>(numberOfBands));
	//vector<vector<vector<float>>> pixels(totalXPixels, vector<vector<float>>(totalYPixels, vector<float>(numberOfBands)));
	vector<Bin> bins(numberOfBins);

	//fill pixels with random values --------------------------------------------------------------------------------------------Replace with fill with pixel values from images
	//for (int i = 0; i < totalPixels; i++) {
	//	for (int j = 0; j < numberOfBands; j++) {
	//		pixels[i][j] = static_cast <float> (rand() % 255);
	//	}
	//}
	//cout << "\nPixels Filled\n";

	//Create bins
	for (int i = 0; i < numberOfBins; i++) {
		string binNum = to_string(i);
		bins[i] = Bin("Feature_" + binNum, totalPixels, numberOfBands);
	}
	bins.push_back(Bin("Non-Feature Landscape", totalPixels, numberOfBands));
	cout << "\nBins Created\n";

	//Assign random means to each bin
	for (int i = 0; i < numberOfBins; i++) {//-------------------------------------------------------------------------------------Replace with clicked-on pixels/section
		for (int j = 0; j < numberOfBands; j++) {
			cout << bins[i].name << " band " << j << ": ";
			bins[i].mean.resize(numberOfBands);
			bins[i].mean[j] = static_cast <float> (rand() % 255);
			means[i][j] = bins[i].mean[j];
			cout << means[i][j] << "\n";
		}
	}

	cout << "\nRandom Means Created\n";

	getDistance(oldMeans, means, numberOfBins, &bins);



	cout << "\n";
	for (int i = 0; i < numberOfBins; i++) {
		bins[i].print();
	}

	outputMask(bins, numberOfBins);

	//---------------------------------------------------------------------------------------------------------------------------Output new image
	system("PAUSE");
}//End main