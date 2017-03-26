#include <iostream>
#include "LineDrawer.h"
#include <cmath>
#include <vector>
#include <queue>
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
using namespace std;

LineDrawer::LineDrawer(){
	xl = 0;
	yl = 0;

	xr = screen.getWidth();
	yr = screen.getHeight();

}
void LineDrawer::setView(Point P1, Point P2){
	xl = P1.getX(); yl = P1.getY();
	xr = P2.getX(); yr = P2.getY();
	vector<Point> P;
	P.push_back(Point(xl,yl));
	P.push_back(Point(xl,yr));
	P.push_back(Point(xr,yr));
	P.push_back(Point(xr,yl));

	drawPolygon(P,Color(255,255,255));


}


int LineDrawer::getcode(Point P){
	int x = P.getX(), y = P.getY();
	int code = 0;
	//Perform Bitwise OR to get outcode
	if(y > yr) code |=TOP;
	if(y < yl) code |=BOTTOM;
	if(x < xl) code |=LEFT;
	if(x > xr) code |=RIGHT;
	return code;
}


int LineDrawer::getcode(double x, double y){

	int code = 0;
	//Perform Bitwise OR to get outcode
	if(y > yr) code |=TOP;
	if(y < yl) code |=BOTTOM;
	if(x < xl) code |=LEFT;
	if(x > xr) code |=RIGHT;
	return code;
}

void LineDrawer::plotSlopPositiveLine (Point P1, Point P2, Color C) {
	int dX, dY, p;
	int i, j, x, y;

	dX = abs(P2.getX() - P1.getX());
	dY = abs(P2.getY() - P1.getY());
	i = P1.getX();
	j = P1.getY();

	if (dX >= dY) {
		p = 2*dY - dX;

		for (x=P1.getX(); x<=P2.getX(); x++) {
			screen.setColor(j, x, C);
			if (p >= 0) {
				p += 2* (dY - dX);
				i++;
				j++;
			}
			else {
				p += 2*dY;
				i++;
			}
		}
	}
	else {
		p = 2*dX - dY;

		for (y=P1.getY(); y<=P2.getY(); y++) {
			screen.setColor(y, i, C);
			if (p >= 0) {
				p += 2* (dX - dY);
				i++;
				j++;
			}
			else {
				p += 2*dX;
				j++;
			}
		}
	}
}


void LineDrawer::plotSlopNegativeLine (Point P1, Point P2, Color C) {
	int dX, dY, p;
	int i, j, x, y;

	dX = abs(P2.getX() - P1.getX());
	dY = abs(P2.getY() - P1.getY());

	if (dX >= dY) {
		i = P1.getX();
		j = P1.getY();
		p = 2*dY - dX;

		for (x=P1.getX(); x<=P2.getX(); x++) {
			screen.setColor(j, x, C);
			if (p >= 0) {
				p += 2* (dY - dX);
				i++;
				j--;
			}
			else {
				p += 2*dY;
				i++;
			}
		}
	}
	else {
		p = 2*dX - dY;
		i = P2.getX();
		j = P2.getY();

		for (y=P2.getY(); y<=P1.getY(); y++) {
			screen.setColor(y, i, C);
			if (p >= 0) {
				p += 2* (dX - dY);
				i--;
				j++;
			}
			else {
				p += 2*dX;
				j++;
			}
		}
	}
}

void LineDrawer::plotVerticalLine (Point P1, Point P2, Color C) {
	int j;

	if (P2.getY() < P1.getY()) {
		P1.swapPoint(&P2);
	}

	for(j = P1.getY() ; j <= P2.getY(); j++) {
		screen.setColor(j, P1.getX(), C);
	}
}

void LineDrawer::drawBresenhamLine (Point P1, Point P2, Color C) {

	bool accept = false;
	double x0,y0,x1,y1;
	x0 = P1.getX(); y0 = P1.getY();
	x1 = P2.getX(); y1 = P2.getY();
	int outcode1 = getcode(x0,y0);
	int outcode2 = getcode(x1,y1);

	while(1){
		if(!(outcode1|outcode2)){
			accept = true;
			break;
		}

		else if(outcode2 & outcode1){
			break;
		}

		else{
			double x,y;
			int outcode = outcode1 ? outcode1 : outcode2;

			if (outcode & TOP) {           // point is above the clip rectangle
				x = x0 + (x1 - x0) * (yr - y0) / (y1 - y0);
				y = yr;
			} else if (outcode & BOTTOM) { // point is below the clip rectangle
				x = x0 + (x1 - x0) * (yl - y0) / (y1 - y0);
				y = yl;
			} else if (outcode & RIGHT) {  // point is to the right of clip rectangle
				y = y0 + (y1 - y0) * (xr - x0) / (x1 - x0);
				x = xr;
			} else if (outcode & LEFT) {   // point is to the left of clip rectangle
				y = y0 + (y1 - y0) * (xl - x0) / (x1 - x0);
				x = xl;
			}

			if(outcode == outcode1){
				x0 = x, y0 = y;
				outcode1 = getcode(x,y);
			}
			else if(outcode == outcode2){
				x1 = x, y1 = y;
				outcode2 = getcode(x,y);
			}
		}


	}
	if(accept){
		P1 = Point(x0,y0),P2=Point(x1,y1);
		if (P1.getX() > P2.getX()) {
			P1.swapPoint(&P2);
		}

		if ((P2.getX() >= P1.getX() && P1.getY() > P2.getY())) {
			plotSlopNegativeLine(P1,P2,C);
		}
		else if (P1.getX() == P2.getX()) {
			plotVerticalLine(P1,P2,C);
		}
		else {
			plotSlopPositiveLine(P1,P2,C);
		}
	}


}

void LineDrawer::drawPolyline (vector<Point> P, Color C) {

	for (int i = 0;i < P.size()-1;i++) {

			drawBresenhamLine(P[i], P[i+1], C);

	}
}

void LineDrawer::drawPolygon (vector<Point> P, Color C) {


	if(P.size() <= 0)
		return;
	//P.push_back(P[0]);
	drawBresenhamLine( P[P.size()-1], P[0], C);
	drawPolyline(P, C);
}



void LineDrawer::plot4pixel (Point P, int p, int q, Color C) {

	//screen.setColor(P.getY()+q, P.getX()+p, C);
    //screen.setColor(P.getY()+q, P.getX()-p, C);
    screen.setColor(P.getY()-q, P.getX()+p, C);
    screen.setColor(P.getY()-q, P.getX()-p, C);

    //screen.setColor(P.getY()+p, P.getX()+q, C);
    //screen.setColor(P.getY()+p, P.getX()-q, C);
    screen.setColor(P.getY()-p, P.getX()+q, C);
    screen.setColor(P.getY()-p, P.getX()-q, C);

}

void LineDrawer::plot8pixel (Point P, int p, int q, Color C) {
	screen.setColor(P.getY()+q, P.getX()+p, C);
    screen.setColor(P.getY()+q, P.getX()-p, C);
    screen.setColor(P.getY()-q, P.getX()+p, C);
    screen.setColor(P.getY()-q, P.getX()-p, C);

    screen.setColor(P.getY()+p, P.getX()+q, C);
    screen.setColor(P.getY()+p, P.getX()-q, C);
    screen.setColor(P.getY()-p, P.getX()+q, C);
    screen.setColor(P.getY()-p, P.getX()-q, C);
}

void LineDrawer::drawCircle (int radius, Point P, Color C) {
    int d, p, q;

    p = 0;
    q = radius;
    d = 3 - 2*radius;

    plot8pixel(P, p, q, C);

    while (p < q) {
        p++;
        if (d<0) {
            d = d + 2*p + 1;
        }
        else {
            q--;
            d = d + 2*(p-q) + 1;
        }

        plot8pixel(P, p, q, C);
    }
}

void LineDrawer::drawHalfCircle (int radius, Point P, Color C) {
    int d, p, q;

    p = 0;
    q = radius;
    d = 3 - 2*radius;

    plot4pixel(P, p, q, C);

    while (p < q) {
        p++;
        if (d<0) {
            d = d + 2*p + 1;
        }
        else {
            q--;
            d = d + 2*(p-q) + 1;
        }

        plot4pixel(P, p, q, C);
    }

    Point P1(P.getX()-radius, P.getY());
    Point P2(P.getX()+radius, P.getY());
    drawBresenhamLine(P1, P2, C);
}

void LineDrawer::floodFill4Seed (int x, int y, Color cBorder, Color cNew) {

	queue<Point> q;
	q.push(Point(x,y));

	while(q.empty() == false){
		Point P = q.front();
		q.pop();
		x = P.getX();
		y = P.getY();
		//if ( !((x>xr || x<xl) || (y>yr || y<yl)) && !cBorder.isSame(screen.getColor(y, x))) {
		if ( !((x>xr || x<xl) || (y>yr || y<yl)) && !cBorder.isSame(screen.getColor(y, x)) && !cNew.isSame(screen.getColor(y, x)) ) {
			screen.setColor(y, x, cNew);
			q.push(Point(x+1,y));
			q.push(Point(x-1,y));
			q.push(Point(x,y+1));
			q.push(Point(x,y-1));
		}
	}



}
