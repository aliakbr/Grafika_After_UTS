#ifndef __Screen__
#define __Screen__
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "Color.h"


class Screen{

public :
	Screen(); // Constructor
	Color getColor(int r, int c); // Mendapatkan warna yang sedang ditampilkan pada baris ke r kolom ke c
	void setColor(int r, int c, int red, int green, int blue); //set warna layar pada koordinat r,c
	void setColor(int r, int c, Color C); //set warna layar pada koordinat r,c

	int getWidth(); // mendapatkan width dari resolusi layar
	int getHeight(); // mendapatkan height dari resolusi layar

	void ClearScreen(); //Membersihkan layar

private :
	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;
	int fb_fd;
	char *fbp;

};

extern Screen screen; //a Global variable screen for other class to use

#endif
