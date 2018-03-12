/*
 *  fileio.cpp
 *
 *  Created on: Mar 8, 2018
 *  Author: lkang
 */

#include "fileio.h"

namespace FileIO {

/* MSE */
// Prototype images which are used for parameters training in command line using cascade
string stopPrototype = utility::GetCurrentWorkingDir() + "/dataset/train/stopPrototype.png";
string stopPrototypeFolder = utility::GetCurrentWorkingDir() + "/dataset/train//croped_positive_stop/";

/* CASCADE */
// Tutorial
string train_stopSign_positive = utility::GetCurrentWorkingDir() + "/dataset/train/positive_stop/";
string train_stopSign_negtive = utility::GetCurrentWorkingDir() + "/dataset/train/negative_stop/";
string test_stopSign_positive = utility::GetCurrentWorkingDir() + "/dataset/test/positive_stop/";
string test_stopSign_negtive = utility::GetCurrentWorkingDir()+ "/dataset/test/negative_stop/";

// Assignment
string train_trafficLight_positive = utility::GetCurrentWorkingDir() + "/dataset/train/positive_light/";
string train_trafficLight_negtive = utility::GetCurrentWorkingDir() + "/dataset/train/negative_light/";
string test_trafficLight_positive = utility::GetCurrentWorkingDir() + "/dataset/test/positive_light/";
string test_trafficLight_negtive = utility::GetCurrentWorkingDir() + "/dataset/test/negative_light/";

void loadPointPolygonInputFile(const string &address, vector<Point> points1, vector<Point> points2) {
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

string loadPointPolygonOutputFile(const string &address) {
    string results = "";

    ifstream inFile;
    inFile.open(address);
    cout << "Test output file: " << address << endl;
    char result;
    while (inFile >> result)
        results += string(1, result);
    return results;
}

// input / output file have the same format
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
