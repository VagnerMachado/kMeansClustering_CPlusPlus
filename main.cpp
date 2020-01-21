/*************************************************************************
 * main.cpp
 *
 *  Created on: Mar 29, 2019
 *      Author: Vagner Machado
 *   Professor: Phillips
 *       Class: CSC 323-33
 *    Semester: Spring 2019
 ************************************************************************/

#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <math.h>
using namespace std;

class Point
{
public:
	int xCoord;
	int yCoord;
	int label;
	double distance;
	Point(int x, int i, int d, int l);
	Point();
	void printPoint();
};

class Kmean
{
public:
	int k;  			//clusters
	int numPoints; 		//pixels not zero
	Point * pointSet;	//will be of size numPoints dynamically
	int numRows;    	//in image
	int numColumns; 	//in image
	int minVal;   		//in image pixel
	int maxVal;  		//in image pixel
	int ** imgArray; 	//numRows x numColum
	Point * Kcentroids; //centroid array for each k
	int change;   		//counts how many points changed label
	Kmean();
	int extrack2DPts(ifstream & infile, ofstream & outfile);
	void loadPointSet(ifstream & infile, Point * set);
	void assignLabel(Point * set, int k);
	void kMeansClustering (Point * set, int k, ofstream & outfile);
	void computeCentroids (Point * set, Point * centroids);
	int distanceMinLabel (Point & p, Point * kCentroids);
	int computeDistance (Point p, Point centroid);
	void writePtSet (Point * pointSet, ofstream & outfile);
	void point2Image (Point * pointSet, int ** imgArray, ofstream & outfile);
	void prettyImagePrint (int ** imgArray, ofstream & ourfile, int iteration);
	void uglyImagePrint();
};

int main(int argc, char ** argv)
{
	//input file with raw image
	ifstream imageInput;
	imageInput.open(argv[1]);

	//kmean object
	Kmean kMean;

	imageInput >> kMean.numRows;
	imageInput >> kMean.numColumns;
	imageInput >> kMean.minVal;
	imageInput >> kMean.maxVal;

	//image array declaration and initialization
	kMean.imgArray = new int * [kMean.numRows];
	for(int i = 0; i < kMean.numRows ; i++)
		kMean.imgArray[i] = new int [kMean.numColumns];
	for(int i = 0; i < kMean.numRows; i++)
		for(int j = 0; j < kMean.numColumns; j++)
			kMean.imgArray[i][j] = 0;

	//outstreams
	ofstream out1; out1.open(argv[3]);
	ofstream out2; out2.open(argv[4]);
	ofstream out3; out3.open(argv[5]);

	//k clusters
	kMean.k = atoi(argv[2]);

	//declare centroids and initialization
	kMean.Kcentroids = new Point [kMean.k + 1];
	for(int i = 1; i < kMean.k+1; i++)
		kMean.Kcentroids[i] = Point();

	//extract 2D points
	kMean.numPoints = kMean.extrack2DPts(imageInput, out1);

	//point set declaration and initialization
	kMean.pointSet = new Point [kMean.numPoints];
	out1.close();

	//load points to point set
	ifstream pointSet;
	pointSet.open(argv[3]);
	kMean.loadPointSet(pointSet, kMean.pointSet);

	//k mean will loop till no change
	kMean.kMeansClustering(kMean.pointSet, kMean.k, out2);

	//writes the point and label to file
	kMean.writePtSet(kMean.pointSet, out3);

	imageInput.close();
	pointSet.close();
	out1.close();
	out2.close();
	out3.close();
}

Kmean::Kmean()
{

}

Point::Point(int x, int y, int d, int l)
{
	xCoord = x;
	yCoord = y;
	label = l;
	distance = d;
}

Point::Point()
{
	xCoord = -1;
	yCoord = -1;
	label = -1;
	distance = 9999;
}

void Point::printPoint()
{
	cout << "X: " << xCoord << " Y: " << yCoord
			<< " Label: " << label << " Dist: " << distance << endl;
}

int Kmean::extrack2DPts(ifstream & infile, ofstream & outfile)
{
	int num  = 0;
	int temp = 0;
	for(int i = 0; i < numRows; i++)
	{
		for(int j = 0; j < numColumns; j++)
		{
			infile >> temp;
			if (temp > 0)
			{
				num++;
				outfile << i << " " << j << endl;
			}
		}

	}
	return num;
}

void Kmean::loadPointSet(ifstream & infile, Point * set)
{
	int row, col, place;
	row = col = place = 0;

	while(infile >> row)
	{
		infile >> col;
		set[place] = Point (row, col, 9999.0, -1);
		place++;
	}
}

void Kmean::kMeansClustering (Point * set, int k, ofstream & outfile)
{
	int iteration = 0;
	assignLabel(set, k);
	change = 1;
	while (change > 0)
	{
		change = 0;
		point2Image(set, imgArray, outfile);
		prettyImagePrint(imgArray, outfile, iteration);
		computeCentroids(pointSet, Kcentroids);
		int index = 0;
		while(index < numPoints)
		{
			change = distanceMinLabel (pointSet[index], Kcentroids);
			index++;
		}
		iteration++;
	}
}

void Kmean::assignLabel(Point * set, int k)
{
	int front = 0;
	int back = numPoints -1;
	int label = 1;

	while (front <= back)
	{
		pointSet[front].label = label;
		front++;
		label++;
		if (label > k)
			label = 1;
		pointSet[back].label = label;
		back--;
		label++;
		if (label > k)
			label = 1;
	}
}

void Kmean::point2Image (Point * pointSet, int ** imgArray, ofstream & outfile)
{
	for (int i = 0; i < numPoints; i++)
	{
		int r = pointSet[i].xCoord;
		int c = pointSet[i].yCoord;
		int l = pointSet[i].label;
		imgArray[r][c] = l;
	}
}

void Kmean::uglyImagePrint()
{
	cout << "\n***   Ugly Image Array ***\n";
	for(int i = 0; i < numRows; i++)
	{
		for(int j = 0; j < numColumns; j++)
		{
			cout << imgArray[i][j]  << " ";
		}
		cout << "\n";
	}
}

void Kmean::prettyImagePrint (int ** imgArray, ofstream & outfile, int iteration)
{
	int temp;
	outfile << "\n***  Result of iteration " << iteration << " ***\n";
	for(int i = 0; i < numRows; i++)
	{
		for(int j = 0; j < numColumns; j++)
		{

			temp = imgArray[i][j];
			if (temp > 0)

				outfile << temp << " ";
			else
				outfile << "  ";
		}
		outfile<< "\n";
	}
}
void Kmean::computeCentroids (Point * set, Point * centroids)
{
	int * sumX = new int [k+1];
	int * sumY = new int [k+1];
	int * totalPt = new int [k+1];

	for ( int i = 0; i <= k; i++)
	{
		sumX[i] = 0;
		sumY[i] = 0;
		totalPt[i] = 0;
	}

	int index = 0;
	int label;
	while (index < numPoints)
	{
		label = pointSet[index].label;
		sumX[label] += pointSet[index].xCoord;
		sumY[label] += pointSet[index].yCoord;
		totalPt[label] = totalPt[label] + 1;
		index++;
	}
	label = 1;
	while (label <= k)
	{
		if(totalPt[label] != 0)
		{
			Kcentroids[label].xCoord = (int) (sumX[label] / totalPt[label]);
			Kcentroids[label].yCoord = (int) (sumY[label] / totalPt[label]);
		}
		label++;
	}
}
int Kmean::distanceMinLabel (Point & p, Point * kCent)
{
	int minDist = 9999;
	int minLabel = 0;
	int label = 1;
	while (label <= k)
	{
		int dist = computeDistance(p, kCent[label]);
		if (dist < minDist)
		{
			minLabel = label;
			minDist = dist;
		}
		label++;
	}
	if (p.label != minLabel)
	{
		p.label = minLabel;
		p.distance = minDist;
		change++;
	}

	return change;
}

int Kmean::computeDistance (Point p, Point centroid)
{
	return sqrt(pow(p.xCoord - centroid.xCoord,2) + pow(p.yCoord - centroid.yCoord,2));
}

void Kmean::writePtSet(Point * pointSet, ofstream & outfile)
{
	outfile << numPoints << endl;
	outfile << numRows << " " << numColumns << endl;
	int point = 0;
	while (point < numPoints)
	{
		outfile << pointSet[point].xCoord << " " <<  pointSet[point].yCoord
				<< " " <<  pointSet[point].label << endl;
		point++;
	}
}
