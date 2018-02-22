#include "headers.h"
#include "utility.h"
#include "detectStopSignMSE.h"
#include "detectObjCascade.h"

using namespace cv;
using namespace std;

void inversePerspectiveMapping(Mat& input, Mat& output);
void processVideo();
int changePixelColor();
void videoQuality(string rawVideo, string lossVideo);

/*All data sets of images file_path*/
string train_stopSign_positive = utility::GetCurrentWorkingDir() + "/dataset/train/positive_stop/";
string train_stopSign_negtive = utility::GetCurrentWorkingDir() + "/dataset/train/negative_stop/";

string test_stopSign_positive = utility::GetCurrentWorkingDir() + "/dataset/test/positive_stop/";
string test_stopSign_negtive = utility::GetCurrentWorkingDir()+ "/dataset/test/negative_stop/";

string train_trafficLight_positive = utility::GetCurrentWorkingDir() + "/dataset/train/positive_stop/";
string train_trafficLight_negtive = utility::GetCurrentWorkingDir() + "/dataset/train/negative_stop/";

string test_trafficLight_positive = utility::GetCurrentWorkingDir() + "/dataset/test/positive_stop/";
string test_trafficLight_negtive = utility::GetCurrentWorkingDir() + "/dataset/test/negative_stop/";

string stopPrototype = utility::GetCurrentWorkingDir() + "/dataset/train/stopPrototype.png";//Prototype image

/*Prototype images which are used for parameters training in command line using cascade */
string stopPrototypeFolder = utility::GetCurrentWorkingDir() + "/dataset/train//croped_positive_stop/";

int main( int argc, char** argv )
{

	/*Read all images from one folder*/
	vector<string> fileNameList = utility::GetFileName(test_stopSign_positive);
	for (vector<string>::const_iterator i = fileNameList.begin(); i != fileNameList.end(); ++i){
	    cout << *i << ' ';
	}

	/*Basic method (MSE) to detect objects*/
	for (int i = 0; i < fileNameList.size(); i++){
		detectStopSignMSE::detectStopSignMSE(stopPrototype,test_stopSign_positive,fileNameList[i]);
	}

	/*Advanced method (cascade) to detect objects*/
	for (int i = 0; i < fileNameList.size(); i++){
		detectObjCascade::detectObjCascade(fileNameList[i], test_stopSign_positive);
	}

	/*Handle video file*/
	//processVideo();

	return 0;
}







void videoQuality(string rawVideo, string lossVideo) {
  VideoCapture raw(rawVideo.c_str());
  VideoCapture loss(lossVideo.c_str());

  if(!raw.isOpened() || !loss.isOpened()) { // check if we succeeded
    cout<<"not able to open"<<endl;
    return;
  }
  int counter = 0;
  double sum = 0.0;
  for(;;) {
    Mat raw_frame;
    Mat loss_frame;
    raw >> raw_frame; // get a new frame from camera
    loss >> loss_frame; // get a new frame from camera
    if(raw_frame.empty() || loss_frame.empty()) {
      break;
    }

    double snr = utility::getPSNR(raw_frame, loss_frame);
    if (snr == 0.0) snr = 40;
    // cout<<snr<<endl;
    counter ++;
    sum += snr;
  }
  cout<<sum / counter<<endl;
}



void processVideo() {
  VideoCapture cap("/home/lkang/Desktop/video.h264"); // open the default camera
  string output{"/home/lkang/Desktop/images/"};
  if(!cap.isOpened()) { // check if we succeeded
    cout<<"not able to open"<<endl;
    return;
  }
  Mat gray;

  int counter = 0;
  for(;;) {
    counter ++;
    Mat frame;
    cap >> frame; // get a new frame from camera
    if(frame.empty()) {
      break;
    }

    // int num = processImage(frame, gray);
    // imshow("gray", frame);
    // waitKey(0);
    // sleep(1);
    cv::imwrite(output + to_string(counter) + ".png", frame);

    if (counter > 10) {
      break;
    }
  }
  cout<<counter<<endl;
}



int changePixelColor() {
  cv::String in = string(train_stopSign_positive + string("f00185.png"));
  Mat img = imread(in, IMREAD_COLOR);
  if (img.empty()) {
    cerr << "No image supplied ..." << endl;
    return -1;
  }
  int cols = img.cols;
  int rows = img.rows;

  cout<<rows<<","<<cols<<endl;
  for(int x = 0; x < rows; ++x) {
    for(int y = 0; y < cols; ++y) {
      if(y == cols/2) {
        img.at<Vec3b>(x, y) = Vec3b(255, 255, 255);;
      }
    }
  }
  imshow("Change Pixel Color", img);
  waitKey(0);
}



void inversePerspectiveMapping(Mat& input, Mat& output) {

  // Input Quadilateral or Image plane coordinates
  Point2f inputQuad[4];
  // Output Quadilateral or World plane coordinates
  Point2f outputQuad[4];

  // Lambda Matrix
  Mat lambda( 2, 4, CV_32FC1 );

  // Set the lambda matrix the same type and size as input
  lambda = Mat::zeros( input.rows, input.cols, input.type() );

  // The 4 points that select quadilateral on the input , from top-left in clockwise order
  // These four pts are the sides of the rect box used as input
  inputQuad[0] = Point2f( input.cols/2 - 500, -100);
  inputQuad[1] = Point2f( input.cols/2 + 500, -100);
  inputQuad[2] = Point2f( input.cols - 1, input.rows - 1);
  inputQuad[3] = Point2f( 0, input.rows - 1);
  // The 4 points where the mapping is to be done , from top-left in clockwise order
  outputQuad[0] = Point2f(0, 0);
  outputQuad[1] = Point2f(input.cols-1, 0);
  outputQuad[2] = Point2f(input.cols-1, input.rows-1);
  outputQuad[3] = Point2f(0, input.rows-1);

  // Get the Perspective Transform Matrix i.e. lambda
  lambda = getPerspectiveTransform( inputQuad, outputQuad );
  // Apply the Perspective Transform just found to the src image
  warpPerspective(input, output, lambda, output.size());
}






