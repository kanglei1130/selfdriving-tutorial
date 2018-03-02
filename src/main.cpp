#include "headers.h"
#include "utility.h"
#include "object_detection.h"
#include "geometry.h"

using namespace cv;
using namespace std;

// MSE
/*Prototype images which are used for parameters training in command line using cascade */
string stopPrototype = utility::GetCurrentWorkingDir() + "/dataset/train/stopPrototype.png";//Prototype image
string stopPrototypeFolder = utility::GetCurrentWorkingDir() + "/dataset/train//croped_positive_stop/";

// CASCADE
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

void cascadeRoutine(const string& folder);
void geometryRoutine();

int main( int argc, char** argv ) {
  cout<<"Hello Self-Driving Tutorial"<<endl;
  cout << "OpenCV Version: " << CV_VERSION << endl;

  // cascadeRoutine(test_stopSign_positive);

  geometryRoutine();

  return 0;
}

void geometryRoutine() {
    int numVertices = 0;
    vector<Point> vertices;
    cout << "How many vertices does the polygon have?" << endl;
    cin >> numVertices;
    for (int i = 0; i < numVertices; i++) {
        double x, y;
        cout << "Enter the x coordinate of vertex " << i << ": ";
        cin >> x;
        cout << "Enter the y coordinate of vertex " << i << ": ";
        cin >> y;
        vertices.push_back(Point(x, y));
     }

     int numTest;
     cout << "How many points do you want to test?" << endl;
     cin >> numTest;
     for (int i = 0; i < numTest; i++) {
         double x, y;
         cout << "Enter the x coordinate of point " << i << ": ";
         cin >> x;
         cout << "Enter the y coordinate of point " << i << ": ";
         cin >> y;
         Geometry::isInside(vertices, Point(x, y))? cout << "Yes \n": cout << "No \n";
     }
}


void cascadeRoutine(const string& folder) {
  vector<string> fileNameList = utility::GetFileName(folder);
  int cnt = 0;
  /*Advanced method (cascade) to detect objects*/
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

