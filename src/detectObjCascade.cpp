/*
 * detectObjCascade.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: wei
 */

#include "detectObjCascade.h"
#include "utility.h"

namespace detectObjCascade {

/*Rectangle target object*/
void draw_locations(Mat & img, vector< Rect > &locations, const Scalar & color, string text) {
	if (!locations.empty()) {
        for(size_t i = 0 ; i < locations.size(); ++i){
            rectangle(img, locations[i], color, 3);
            putText(img, text, Point(locations[i].x+1, locations[i].y+8), FONT_HERSHEY_DUPLEX, 0.3, color, 1);
        }
	}
}

/*use cascade(boosting) to detect object*/
/*students are encouraged to try different parameter files, and also need to train you own parameter file*/
#define STOP_SIGN_CASCADE_NAME utility::GetCurrentWorkingDir() + "/params/trained_stopsign_classifier.xml"
#define TRAFFIC_LIGHT_CASCADE_NAME utility::GetCurrentWorkingDir() + "/params/trafficlight_classifier2.xml"

void detectObjCascade(string file_name, string folder_name) {
    cout << "OpenCV Version: " << CV_VERSION << endl;
	CascadeClassifier traffic_light, stop_sign;
	vector<Rect> cars_found, traffic_light_found, stop_sign_found, pedestrian_found;

	string obj_address = folder_name + file_name;
    Mat targetImage;
    if (!obj_address.empty()) {
    	targetImage = imread(obj_address);
    	cout << "Target Image: " << obj_address << endl;
    }

    cout<<utility::GetCurrentWorkingDir()<<endl;
    traffic_light.load(TRAFFIC_LIGHT_CASCADE_NAME);
    stop_sign.load(STOP_SIGN_CASCADE_NAME);

    double t = (double) getTickCount(); // start time

	traffic_light.detectMultiScale(targetImage, traffic_light_found, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));
    stop_sign.detectMultiScale(targetImage, stop_sign_found, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));

    t = (double) getTickCount() - t; // time duration
    cout << "Time taken : " << (t*1000./cv::getTickFrequency()) << " s" << endl;

    draw_locations(targetImage, traffic_light_found, Scalar(0, 255, 255), "Traffic Light");
    draw_locations(targetImage, stop_sign_found, Scalar(0, 0, 255), "Stop Sign");

    utility::creatDir("/obj_detect_output_cascade");
    string output_address = utility::GetCurrentWorkingDir() + "/obj_detect_output_cascade/output" + file_name;
    if (file_name.find(".jpg") and !targetImage.empty()){
    	imwrite(output_address, targetImage);
    }
	cout << "Detected Images Locate: " << output_address << endl;
}

} /* namespace detectObjCascade */
