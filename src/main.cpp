#include "headers.h"
#include "utility.h"
#include "object_detection.h"

using namespace cv;
using namespace std;


string stopPrototype = utility::GetCurrentWorkingDir() + "/dataset/train/stopPrototype.png";//Prototype image
/*Prototype images which are used for parameters training in command line using cascade */
string stopPrototypeFolder = utility::GetCurrentWorkingDir() + "/dataset/train//croped_positive_stop/";

/*All data sets of images file_path*/
string train_stopSign_positive = utility::GetCurrentWorkingDir() + "/dataset/train/positive_stop/";
string train_stopSign_negtive = utility::GetCurrentWorkingDir() + "/dataset/train/negative_stop/";

string test_stopSign_positive = utility::GetCurrentWorkingDir() + "/dataset/test/positive_stop/";
string test_stopSign_negtive = utility::GetCurrentWorkingDir()+ "/dataset/test/negative_stop/";


string train_trafficLight_positive = utility::GetCurrentWorkingDir() + "/dataset/train/positive_light/";
string train_trafficLight_negtive = utility::GetCurrentWorkingDir() + "/dataset/train/negative_light/";

string test_trafficLight_positive = utility::GetCurrentWorkingDir() + "/dataset/test/positive_light/";
string test_trafficLight_negtive = utility::GetCurrentWorkingDir() + "/dataset/test/negative_light/";


int main( int argc, char** argv )
{
  cout<<"Hello Self-Driving Tutorial"<<endl;
  cout << "OpenCV Version: " << CV_VERSION << endl;
	return 0;
}


void testImages(const string& folder) {
  vector<string> fileNameList = utility::GetFileName(folder);

  /*Advanced method (cascade) to detect objects*/
  for (int i = 0; i < fileNameList.size(); i++){
    cout<<fileNameList[i]<<endl;
    // ObjectDetection::detectObjCascade(fileNameList[i], test_trafficLight_positive);
  }
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
    if(frame.empty()) {
      break;
    }

    // int num = processImage(frame, gray);
    // imshow("gray", frame);
    // waitKey(0);
    // sleep(1);
    // cv::imwrite(output + to_string(counter) + ".png", frame);
  }
}

