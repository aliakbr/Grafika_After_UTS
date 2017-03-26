#include "Circle.h"

Circle::Circle(){}

Circle::Circle(Point P, int r, Color c ){

	Border = c;

	center = P;
	radius = r;
	Fill = c;
	draw();
}
Circle::~Circle(){
	erase();

}

void Circle::moveBy(int deltaX, int deltaY){
	erase();
	center.moveBy(deltaX,deltaY);
	draw();
}

//rotate the object by theta degree clockwise
void Circle::Rotate(int theta){
	//Well, we can say circle is constanlu rotating
}


void Circle::erase(){
	linedrawer.drawCircle(radius,center,Color(0,0,0));
	linedrawer.floodFill4Seed(center.getX(), center.getY(), Border, Color(0,0,0));
}

void Circle::draw(){
	linedrawer.drawCircle(radius, center, Border);
	linedrawer.floodFill4Seed(center.getX(), center.getY(), Border, Fill);
}

//set floodfill color
void Circle::setFillColor(Color C){
	Fill = C;

}
//set Border Color to color c
void Circle::setBorderColor(Color c){
	Border = c;
}

double Circle::getRadius(){
	return radius;
}

Point Circle::getCenter(){
	return center;
}

void Circle::zoom(Point c, float s){
	erase();
	center = center.scaleUp(c,s);
	radius *= s;
}
