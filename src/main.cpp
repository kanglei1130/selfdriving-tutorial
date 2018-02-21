#include "headers.h"
#include "utility.h"

using namespace cv;
using namespace std;

void inversePerspectiveMapping(Mat& input, Mat& output);
void processVideo();
int changePixelColor();
void videoQuality(string rawVideo, string lossVideo);
void creatDir(string file_path);
string GetCurrentWorkingDir();
void detectStopSignMSE(string obj_address,string model_address);
void detectObjCascade(string file_name,string folder_name);
void draw_locations(Mat & img, vector< Rect > & locations, const Scalar & color,string text);

/*All data sets of images file_path*/
string train_stopSign_positive = GetCurrentWorkingDir() + "/dataset/train/positive_stop/";
string train_stopSign_negtive = GetCurrentWorkingDir() + "/dataset/train/negative_stop/";

string test_stopSign_positive = GetCurrentWorkingDir() + "/dataset/test/positive_stop/";
string test_stopSign_negtive = GetCurrentWorkingDir()+ "/dataset/train/negative_stop/";

string train_trafficLight_positive = GetCurrentWorkingDir() + "/dataset/train/positive_stop/";
string train_trafficLight_negtive = GetCurrentWorkingDir() + "/dataset/train/negative_stop/";

string test_trafficLight_positive = GetCurrentWorkingDir() + "/dataset/test/positive_stop/";
string test_trafficLight_negtive = GetCurrentWorkingDir() + "/dataset/test/negative_stop/";

string stopPrototype = string("/home/wei/Downloads/cv-selfdriving/StopSignDataset/stopPrototype.png");//Prototype image

int main( int argc, char** argv )
{
	/*Basic method (MSE) to detect objects*/
	//detectStopSignMSE(obj_address, stopPrototype);

	/*Advanced method (cascade) to detect objects*/
	string file_name = string("5.jpg");
	string folder_name = string("/home/wei/Documents/project/selfdriving-cv-tutorial/dataset/train/positive_stop/");
	detectObjCascade(file_name, test_stopSign_positive);

	/*Handle video file*/
	//processVideo();

	/*Read all images from one folder*/


   return 0;
}


//get the local file path
std::string GetCurrentWorkingDir() {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}

//creat a new directory with name file_path
void creatDir(string file_path){
	std::string dir = "mkdir -p " + GetCurrentWorkingDir() + file_path;
	const int dir_err = system(dir.c_str());
	if (-1 == dir_err)
	{
	    printf("Error creating directory!n");
	    exit(1);
	}
}


/*Detect stop sign with simple method by comparing MSE*/
void detectStopSignMSE(string obj_address, string model_address) {
	// set threshold of detection a stop sign
	int THRESHOLD = 7100;
    Mat targetImage = imread(obj_address, IMREAD_COLOR);;

    // resize the image
    int width = 500;
    int height = width * targetImage.rows / targetImage.cols;
    resize(targetImage, targetImage, Size(width, height));
    // read prototype image
    Mat prototypeImg = imread(model_address, IMREAD_COLOR);

    int minMSE = INT_MAX;
    int location[4] = {0, 0, 0, 0};
    // start time
    int t0 = clock();
    //Mat tmpImg;
    Mat tmpImg = prototypeImg.clone();
    Mat window;
    for (int wsize = tmpImg.cols; wsize > 15; wsize /= 1.3) {
        if (tmpImg.rows < 15 || tmpImg.cols < 15)
        	break;
        if (tmpImg.rows > 900 || tmpImg.cols > 900) {
        	resize(tmpImg, tmpImg, Size(wsize, wsize));
        	continue;
        }
        cout << "Image pyramid width: " << wsize << " height: " << wsize << endl;
        for (int y = 0; y < targetImage.rows; y += 5) {
            for (int x = 0; x < targetImage.cols; x += 5) {
            	if (x + tmpImg.cols > targetImage.cols || y + tmpImg.cols > targetImage.rows)
            	    continue;
                Rect R(x, y, tmpImg.cols, tmpImg.cols); // create a rectangle
                window = targetImage(R); // crop the region of interest using above rectangle
                if (window.rows != tmpImg.rows || window.cols != tmpImg.cols)
                    continue;
                double tempSim = meanSquareError(tmpImg, window);
                if (tempSim < minMSE) {
                    minMSE = tempSim;
                    location[0] = x;
                    location[1] = y;
                    location[2] = tmpImg.rows;
                    location[3] = tmpImg.cols;
                }
            }
        }
        resize(tmpImg, tmpImg, Size(wsize, wsize));
    }

    // end time
    int t1 = clock();

    cout << "Execution time: " << (t1 - t0)/double(CLOCKS_PER_SEC)*1000 << " s" << endl;
    cout << "Minimum MSE: " << minMSE << endl;
    if (minMSE < THRESHOLD) {
    	int buff1 = 50;
    	int x = location[0];
    	int y = location[1];
    	int w = location[2];
    	int h = location[3];
    	// draw the rectangle
    	rectangle(targetImage, Point(x-buff1/2,y-buff1/2), Point(x+w+buff1/2,y+h+buff1/2), Scalar(0,255,0), 2);
    	cout << "Stop sign found!" << endl;
    } else {
    	cout << "Stop sign not found!" << endl;
    }

    // show the image
    imshow("image", targetImage);
    waitKey(50000);
}

/* Computes Mean Square Error between two n-d matrices.*/
/* Lower value means more similar*/
static double meanSquareError(const Mat &img1, const Mat &img2) {
    Mat s1;
    absdiff(img1, img2, s1);   // |img1 - img2|
    s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
    s1 = s1.mul(s1);           // |img1 - img2|^2
    Scalar s = sum(s1);        // sum elements per channel
    double sse = s.val[0] + s.val[1] + s.val[2];  // sum channels
    double mse = sse / (double)(img1.channels() * img1.total());
    return mse;
}


/*use cascade(boosting) to detect object*/
#define STOP_SIGN_CASCADE_NAME GetCurrentWorkingDir() + "/params/cascade.xml"
//#define TRAFFIC_LIGHT_CASCADE_NAME GetCurrentWorkingDir() + "/params/trafficlight_classifier2.xml"

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

    cout<<GetCurrentWorkingDir()<<endl;
    //traffic_light.load(TRAFFIC_LIGHT_CASCADE_NAME);
    stop_sign.load(STOP_SIGN_CASCADE_NAME);

    double t = (double) getTickCount(); // start time

	//traffic_light.detectMultiScale(targetImage, traffic_light_found, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));
    stop_sign.detectMultiScale(targetImage, stop_sign_found, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));

    t = (double) getTickCount() - t; // time duration
    cout << "Time taken : " << (t*1000./cv::getTickFrequency()) << " s" << endl;

    // draw_locations(targetImage, cars_found, Scalar(0, 255, 0), "Car");
    draw_locations(targetImage, traffic_light_found, Scalar(0, 255, 255), "Traffic Light");
    draw_locations(targetImage, stop_sign_found, Scalar(0, 0, 255), "Stop Sign");

    creatDir("/object_detection_output");
    string output_address = GetCurrentWorkingDir() + "/object_detection_output/output" + file_name;
    imwrite(output_address, targetImage);
    cout << "Detected Images Locate: " << output_address << endl;
}

/*Rectangle target object*/
void draw_locations(Mat & img, vector< Rect > &locations, const Scalar & color, string text) {
	if (!locations.empty()) {
        for(size_t i = 0 ; i < locations.size(); ++i){
            rectangle(img, locations[i], color, 3);
            putText(img, text, Point(locations[i].x+1, locations[i].y+8), FONT_HERSHEY_DUPLEX, 0.3, color, 1);
        }
	}
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






