/*
 * detectObjCascade.h
 *
 *  Created on: Feb 21, 2018
 *      Author: wei
 */
#include "headers.h"
#include <stdlib.h>
#ifndef SRC_DETECTOBJCASCADE_H_
#define SRC_DETECTOBJCASCADE_H_

using namespace cv;
using namespace std;

namespace detectObjCascade {

	void draw_locations(Mat & img, vector< Rect > &locations, const Scalar & color, string text);
	void detectObjCascade(string file_name, string folder_name);

} /* namespace detectObjCascade */

#endif /* SRC_DETECTOBJCASCADE_H_ */
