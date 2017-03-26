#ifndef __Point__
#define __Point__

class Point{

public:
	Point();					//constructor
	Point(int x, int y); 		//constructor with initial x and y


	void setPoint(int x, int y); //set x and y
	void setPoint(double x, double y); //set x and y , used for rotation
	int getX();
	int getY();
	void setX(double a);
	void setY(double b);
	void swapPoint(Point *P);
	void moveBy(int DetalX, int DeltaY);
	void moveTo(int x, int y);
	void rotate(int theta);
	void rotatePoros(int theta, Point poros);
	Point scaleUp(Point center,double scale);


	double x;
	double y;
};


#endif
