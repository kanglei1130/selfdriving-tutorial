/*
 *  fileio.cpp
 *
 *  Created on: Mar 8, 2018
 *  Author: lkang
 */

#include "fileio.h"

namespace FileIO {

void loadPointPolygonTestCase(const string &address, vector<Point> points1, vector<Point> points2) {
    int numPoints = 0;
    ifstream inFile;
    inFile.open(address);
    cout << "Test input file: " << address << endl;
    inFile >> numPoints;
    for (int i = 0; i < numPoints; i++) {
        double x, y;
        inFile >> x;
        inFile >> y;
        points1.push_back(Point(x, y));
    }
    inFile >> numPoints;
    for (int i = 0; i < numPoints; i++) {
        double x, y;
        inFile >> x;
        inFile >> y;
        points2.push_back(Point(x, y));
    }
    inFile.close();
}

void loadConvexHullFile(const string& address, vector<Point> points) {
  int numPoints = 0;
  ifstream inFile;
  inFile.open(address);
  cout << "File address: " << address << endl;
  inFile >> numPoints;
  for (int i = 0; i < numPoints; i++) {
    double x, y;
    inFile >> x;
    inFile >> y;
    points.push_back(Point(x, y));
  }
  inFile.close();
}

}
