#ifndef __Circle__
#define __Circle__
#include "LineDrawer.h"
#include "Point.h"
#include <vector>
#include "AbstractShape.h"


class Circle: public AbstractShape{

public:

	//Constructor,
	//Point
	Circle();
	Circle(Point P, int r, Color c );
	//Destructor
	~Circle();

	//set floodfill color
	void setFillColor(Color C);
	//set Border Color to color c
	void setBorderColor(Color c);

	//Move the object by delta
	//deltaX : move the object in X axis by delta X
	//deltaY : move the object in Y axis by delta Y
	void moveBy(int deltaX, int deltaY);


	//rotate the object by theta degree clockwise
	void Rotate(int theta);
	double getRadius();
	Point getCenter();
	void zoom(Point c, float s);

//private:
	void erase();
	void draw();
	double radius;
	Point center;
	Color Fill;
	Color Border;
};

#endif
