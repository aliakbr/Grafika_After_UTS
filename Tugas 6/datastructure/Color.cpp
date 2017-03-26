#include "Color.h"

Color::Color(){
	setColor(0,0,0);
}

Color::Color(int r, int g, int b){
	setColor(r,g,b);
}

void Color::setColor(int r, int g, int b){
	Red = r;
	Green = g;
	Blue = b;
}
int Color::getRed(){
	return Red;
}
int Color::getGreen(){
	return Green;
}
int Color::getBlue(){
	return Blue;
}
bool Color::isSame(Color C) {
	if ((C.getRed() == Red) && (C.getGreen() == Green) && (C.getBlue() == Blue)) {
		return true;
	}
	else {
		return false;
	}
}

