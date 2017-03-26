#include "shape.h"
#include "Screen.h"
#include <iostream>
using namespace std;
Screen screen;
int main(){
	screen.ClearScreen();
	vector<Point> edge;
	edge.push_back(Point(100,100));
	edge.push_back(Point(200,100));
	edge.push_back(Point(200,200));
	edge.push_back(Point(100,200));

	Shape s(edge, Color(255,0,0));
	s.setFillColor(Color(0,255,050));

	while(1){
		s.moveBy(10,1);
		sleep(1);
	}

	
}