#include "headers.h"
#include "routines.h"
#include "fileio.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
  cout << "Hello Self-Driving Tutorial" << endl;
  cout << "OpenCV Version: " << CV_VERSION << endl;

  // Routines::cascadeRoutine(); // stop sign
  Routines::pointInPolygonRoutine();
  Routines::polygonOverlapRoutine();
  Routines::convexHullRoutine();

  return 0;
}
