#include "Screen.h"
#include <iostream>
using namespace std;
Screen screen;

int main(){
	screen = Screen();
	
	screen.ClearScreen();
	cout << screen.getWidth() << " " << screen.getHeight() << endl;
	cout << screen.finfo.smem_len << endl;

	for(int i=40; i<=300; i++){
		screen.setColor(i,40,255,255,255);
		screen.setColor(i,41,255,255,255);
		screen.setColor(i,42,255,255,255);
		screen.setColor(i,43,255,255,255);
		screen.setColor(i,44,255,255,255);
		screen.setColor(i,45,255,255,255);
		screen.setColor(i,46,255,255,255);
		screen.setColor(i,47,255,255,255);
		screen.setColor(i,48,255,255,255);
		screen.setColor(i,49,255,255,255);	
	}
	


	cout << screen.getColor(30,40).getRed() << screen.getColor(49,40).getRed() << endl;

	int a;
	cin >> a;
	screen.ClearScreen();
}