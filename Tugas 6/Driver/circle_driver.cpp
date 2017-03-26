#include "Circle.h"
#include "Point.h"
#include "Screen.h"

Screen screen;
int main(){
	Circle c(Point(80,80), 50, Color(255,255,255));
	c.setBorderColor(Color(255,255,255));
	c.setFillColor(Color(0,255,255));
	while(1){
		c.moveBy(1,0);
		sleep(1);
	}
}