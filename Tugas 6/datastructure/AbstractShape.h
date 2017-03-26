#ifndef _Abstract_Shape_
#define _Abstract_Shape_
#include "Color.h"

class AbstractShape{

	public :

		//set floodfill color
		virtual void setFillColor(Color C) = 0;
		//set Border Color to color c
		virtual void setBorderColor(Color c) = 0;

		//Move objec by deltaX and deltaY
		virtual void moveBy(int deltaX, int deltaY) = 0;


		//rotate the object by theta degree clockwise
		virtual void Rotate(int theta) = 0;


};

#endif
