/*
 *  routine.h
 *
 *  Created on: Mar 8, 2018
 *  Author: lkang
 */

#ifndef SRC_ROUTINES_H_
#define SRC_ROUTINES_H_

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "headers.h"
#include "fileio.h"
#include "geometry.h"
#include "object_detection.h"

using namespace std;

namespace Routines {

void cascadeRoutine(const string &folder);
void pointInPolygonRoutine(const string &address);
void polygonOverlapRoutine(const string &address);
void convexHullRoutine(const string &address);
}

#endif /* SRC_ROUTINES_H_ */
