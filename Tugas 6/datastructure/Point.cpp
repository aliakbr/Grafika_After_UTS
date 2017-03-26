#include "Point.h"
#include <cmath>

#define PI 3.14159265

Point::Point() {
	setPoint(0.00,0.00);
}

Point::Point(int x, int y) {
	setPoint(x/1.00,y/1.00);
}

void Point::setPoint(int x, int y) {
	this->x = x/1.00;
	this->y = y/1.00;
}

void Point::setPoint(double x, double y) {
	this->x = x;
	this->y = y;
}


void Point::setX(double a){
	x = a;
}

void Point::setY(double a){
	y = a;
}

int Point::getX() {
	return round(x);
}

int Point::getY() {
	return round(y);
}

void swap (double *a, double *b) {
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void Point::swapPoint(Point *P) {
	swap(&x, &P->x);
	swap(&y, &P->y);
}

void Point::moveBy(int DeltaX, int DeltaY){
	x += DeltaX;
	y += DeltaY;
}
void Point::moveTo(int nx, int ny){
	x = nx/1.0;
	y = ny/1.0;
}

void Point::rotate(int theta){
	double oldX = x, oldY = y;
	double degree = ((double)theta)* PI/180 ;
	x = oldX*cos(degree) - oldY*sin(degree);
	y = oldX*sin(degree) + oldY*cos(degree);
}

void Point::rotatePoros(int theta, Point poros){
	double oldX = x, oldY = y;
	double degree = ((double)theta)* PI/180 ;
	x = poros.getX() + ((oldX - poros.getX()) * cos(degree) - (poros.getY() - oldY) * sin(degree));
	y = poros.getY() - ((oldX - poros.getX()) * sin(degree) + (poros.getY() - oldY) * cos(degree));
}

Point Point::scaleUp(Point center, double scale){
	Point P_new;
	P_new.setX(((getX() - center.getX()) * scale) + center.getX());
	P_new.setY(((getY() - center.getY()) * scale) + center.getY());
	return P_new;
}
