/*
 * detectStopSignMSE.h
 *
 *  Created on: Feb 21, 2018
 *      Author: wei
 */
#include "headers.h"

#ifndef SRC_DETECTSTOPSIGNMSE_H_
#define SRC_DETECTSTOPSIGNMSE_H_

using namespace cv;
using namespace std;

namespace detectStopSignMSE {

static double meanSquareError(const Mat &img1, const Mat &img2);

void detectStopSignMSE(string model_address,string obj_address, string filename) ;
} /* namespace detectStopSignMSE */

#endif /* SRC_DETECTSTOPSIGNMSE_H_ */
