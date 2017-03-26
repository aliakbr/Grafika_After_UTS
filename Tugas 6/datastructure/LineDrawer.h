#ifndef __LINE_DRAWER__
#define __LINE_DRAWER__
#include "Point.h"
#include "Color.h"
#include "Screen.h"
#include <vector>
using namespace std;



class LineDrawer{

public:
	LineDrawer();

	void setView(Point P1, Point P2);
	// Draw line into screen woth bresenham algorithm
	// P1 : Starting Point
	// P2 : Ending Point
	// C : Border Color
	void drawBresenhamLine (Point P1, Point P2, Color C);

	// Draw not necessary closed polygon from vector of point
	// P : vector of point
	// C : border color
	void drawPolyline (vector <Point> P, Color C);

	// Draw closed polygon (alias convex polygon) from vector of point
	// P : vector of point
	// C : border color
	void drawPolygon (vector <Point> P, Color C);

	//Draw circle
	// radius : circle radius
	// P : circle center
	// C : border color
	void drawCircle (int radius, Point P, Color C);

	//Color an closed spaced
	//x,y : starting point
	//cBorder : closed spaced border color (to determine where to stop)
	//cNew : what color to fill


	void drawHalfCircle (int radius, Point P, Color C);
	void floodFill4Seed (int x, int y, Color cBorder, Color cNew);


	int xl,yl,xr,yr;

private:
	int getcode(Point P);
	int getcode(double x, double y);
	void plotSlopPositiveLine (Point P1, Point P2, Color C);
	void plotSlopNegativeLine (Point P1, Point P2, Color C);
	void plotVerticalLine (Point P1, Point P2, Color C);
	void plot4pixel (Point P, int p, int q, Color C);
	void plot8pixel (Point P, int p, int q, Color C);




};

extern LineDrawer linedrawer;

#endif
