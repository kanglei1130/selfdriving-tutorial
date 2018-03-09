/*
 * fileio.h
 *
 *  Created on: Mar 8, 2018
 *      Author: lkang
 */

#ifndef SRC_FILEIO_H_
#define SRC_FILEIO_H_

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <fstream>

#include "headers.h"
#include "utility.h"

using namespace std;

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

void loadPointPolygonTestCase(const string &address, vector<Point> points1, vector<Point> points2);
void loadConvexHullFile(const string& address, vector<Point> points);

}

#endif /* SRC_FILEIO_H_ */
