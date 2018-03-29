#include "headers.h"
#include "routines.h"
#include "fileio.h"

using namespace cv;
using namespace std;

bool point_in_polygon(Points polygon, Point p);
bool polygon_overlap(Points polygon1, Points polygon2);
Points convex_hull(Points points);

int main(int argc, char** argv) {
  cout << "Hello Self-Driving Tutorial" << endl;
  cout << "OpenCV Version: " << CV_VERSION << endl << endl;

  // Routines::cascadeRoutine();           // stop sign detection
  Routines::pointInPolygonRoutine(point_in_polygon); // point in polygon detection
  Routines::polygonOverlapRoutine(polygon_overlap);  // polygon overlap detection
  // Routines::convexHullRoutine(convex_hull);          // convex hull construction
  function<Points(Points)> convexHull = convex_hull;
  Routines::testConvexHullRoutine(convexHull); 

  return 0;
}

/*
 * Parameter: vector<Point> polygon, Point p;
 * Return: false if p is outside the polygon, true otherwise;
 */
bool point_in_polygon(Points polygon, Point p) {
    // write your code here
    // ... ...
    return Geometry::isInside(polygon, p);
}

/*
 * Parameter: vector<Point> polygon1, vector<Point> polygon2;
 * Return: false if there's no overlap between the two polygons, true otherwise;
 */
bool polygon_overlap(Points polygon1, Points polygon2) {
    // write your code here
    // ... ...
    return Geometry::hasOverlap(polygon1, polygon2);
}

/*
 * Parameter: vector<Point> points;
 * Return: vector<Point> convex_hull if there's a convex hull that can completely cover all points;
 *         return an empty vector<Point> convex_hull if impossible;
 */
Points convex_hull(Points points) {
    // write yoru code here
    // ... ...
    return Geometry::convexHull_Javis(points);
}
