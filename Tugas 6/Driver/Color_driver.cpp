#include "Color.h"
#include <iostream>
using namespace std;
int main(){
	Color C;
	Color D(1,2,3);

	cout << C.getRed();
	cout << C.getGreen();
	cout << C.getBlue();
	cout << endl;
	cout << D.getRed();
	cout << D.getGreen();
	cout << D.getBlue();

}