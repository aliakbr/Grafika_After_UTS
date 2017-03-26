#ifndef __Color__
#define __Color__

class Color{

public:
	Color();					//constructor
	Color(int r, int g, int b); //constructor with initial color

	void setColor(int r, int g, int b); //set semua warna
	int getRed();
	int getGreen();
	int getBlue();
	bool isSame(Color C);

private:
	int Red;
	int Green;
	int Blue;
};


#endif
