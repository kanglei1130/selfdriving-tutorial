#include "headers.h"
#include "routines.h"
#include "fileio.h"

using namespace cv;
using namespace std;

Points convexHull(Points points);

int main(int argc, char** argv) {
  cout << "Hello Self-Driving Tutorial" << endl;
  cout << "OpenCV Version: " << CV_VERSION << endl << endl;

  // Routines::cascadeRoutine();           // stop sign detection
  // Routines::pointInPolygonRoutine();    // point in polygon detection

  // Routines::polygonOverlapRoutine();    // polygon overlap detection

  // Routines::convexHullRoutine(convex);        // convex hull construction

  return 0;
}

vector<Point> convexHull(vector<Point> points) {
  return points;
}
