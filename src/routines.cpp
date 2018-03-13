/*
 *  routines.cpp
 *
 *  Created on: Mar 8, 2018
 *  Author: lkang
 */

#include <algorithm>
#include "routines.h"
#include "geometry.h"
#define TEST_MODE 0
#define ALGORITHM 0  // 0 - Javis'; 1 - Graham's

namespace Routines {

// test whether a point is inside a polygon or not
void pointInPolygonRoutine(const string &address) {
    vector<Point> polygon;
    vector<Point> points;
    vector<string> results;  // students' results
    FileIO::loadPointPolygonInputFile(address, polygon, points);      // load test cases
    if (TEST_MODE) {
        results = FileIO::loadPointPolygonOutputFile(address);        // load result file
    }
    for (int i = 0; i < points.size(); i++) {
        if (Geometry::isInside(polygon, Point(points[i].x, points[i].y))) {
            cout << "Sample answer: Yes - (" << points[i].x << ", " << points[i].y << ")" << endl;
            if (TEST_MODE)
                (results.size() >= i+1 && results[i] == "Y") ? cout << "Correct answer!\n" : cout << "Wrong answer!\n";
        } else {
            cout << "Sample answer: No - (" << points[i].x << ", " << points[i].y << ")" << endl;
            if (TEST_MODE)
                (results.size() >= i+1 && results[i] == "N") ? cout << "Correct answer!\n" : cout << "Wrong answer!\n";
        }
    }
}

// test whether two polygons overlap or not
void polygonOverlapRoutine(const string &address) {
    vector<Point> polygon1;
    vector<Point> polygon2;
    vector<string> result;  // students' results
    if (TEST_MODE) {
        result = FileIO::loadPointPolygonOutputFile(address);         // load result files
    }
    FileIO::loadPointPolygonInputFile(address, polygon1, polygon2);   // load test cases
    if (Geometry::hasOverlap(polygon1, polygon2)) {
        cout << "Sample answer: Yes \n";
        if (TEST_MODE)
            (result.size() == 1 && result[0] == "Y") ? cout << "Correct answer!\n" : cout << "Wrong answer!\n";
    } else {
        cout << "Sample answer: No \n";
        if (TEST_MODE)
            (result.size() == 1 && result[0] == "N") ? cout << "Correct answer!\n" : cout << "Wrong answer!\n";
    }
}

// construct a convex hull over all given points
void convexHullRoutine(const string& directory) {
    string address = directory;
    vector<Point> points;
    vector<Point> result;
    vector<Point> hull;
    FileIO::loadConvexHullFile(address, points);          // load test cases
    if (TEST_MODE) {
        FileIO::loadConvexHullFile(address, result);      // load result file
        sort(result.begin(), result.end(), Geometry::compare_sort); // sort the hull points
    }
    if (ALGORITHM == 0) {
        // Javis' Algorithm
        hull = Geometry::convexHull_Javis(points);
    } else {
        // Graham's Algorithm
        hull = Geometry::convexHull_Graham(points);
    }
    if (hull.size() == 0) {
        cout << "Sample answer: Impossible" << endl;
        if (TEST_MODE)
            (result.size() == 0) ? cout << "Correct answer!\n" : cout << "Wrong answer!\n";
    } else {
        cout << "Sample answer: \n" << hull.size() << "\n";
        bool isWrong = false;
        if (hull.size() != result.size())
            isWrong = true;
        for (int i = 0; i < hull.size(); i++) {
            if (!isWrong && hull[i].x != result[i].x && hull[i].y != result[i].y)
                isWrong = true;
            cout << hull[i].x << " " << hull[i].y << endl;
        }
        if (isWrong)    
            cout << "Wrong answer!" << endl;
        else 
            cout << "Correct answer!" << endl;
    }
}

void cascadeRoutine(const string &folder) {
  vector<string> fileNameList = utility::GetFileName(folder);
  int cnt = 0;
  /* Advanced method (cascade) to detect objects */
  string model = utility::GetCurrentWorkingDir() + "/params/cascade.xml";
  for (int i = 0; i < (int)fileNameList.size(); i++){
    cout<<fileNameList[i]<<endl;
    string file = fileNameList[i];
    cnt += ObjectDetection::detectObjCascade(model, folder, file);
  }
  cout<< cnt << " objects are detected in "<<fileNameList.size()<<" files"<<endl;
}

void processVideo() {
  VideoCapture cap("/home/lkang/Desktop/video.h264"); // open the default camera
  string output{"/home/lkang/Desktop/images/"};
  if(!cap.isOpened()) { // check if we succeeded
    cout<<"not able to open"<<endl;
    return;
  }
  Mat gray;
  for (;;) {
    Mat frame;
    cap >> frame; // get a new frame from camera
    if(frame.empty()) break;

    // int num = processImage(frame, gray);
    // imshow("gray", frame);
    // waitKey(0);
    // sleep(1);
    // cv::imwrite(output + to_string(counter) + ".png", frame);
  }
}

}
