#include "datastructure/shape.h"
#include "datastructure/Circle.h"
#include <iostream>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <termios.h>

using namespace std;
const struct timespec* delayperframe = (const struct timespec[]){{0,2*16666667L}};
static termios old, news;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

/* Base color */
Color black(0,0,0);
Color green(0,204,0);
Color blue(0,0,204);
Color red(204, 0, 0);
Color white(255, 255, 255);



/* Global Variable */
Screen screen;
LineDrawer linedrawer;
Point center_world(300,300);
float scale = 1.0;

/* Shape for obstacle */
vector< vector<Shape *>> world_shape; //list polygon
//Layer
vector<Shape *> vector_shape1;
vector<Shape *> vector_shape2;
vector<Shape *> vector_shape3;

int N;
Shape* frame;
Shape* cursor;
int Layer_size;

/* Objective */
Circle* obj;

/*Point atas cursor */
Point cursor_center_point(center_world.getX(),center_world.getY()-5);


void initTermios(int echo){
  tcgetattr(0, &old);
  news = old;
  news.c_lflag &= ~ICANON;
  news.c_lflag &= echo ? ECHO : ~ECHO;
  tcsetattr(0, TCSANOW, &news);
}

void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo){
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

char getch(void){
  return getch_(0);
}

void BuildRandomShape(){
  /* Random sheet*/
  srand(time(NULL));
  N =  rand() %  3 + 1;
  int i, j;
  for (i = 0; i < N; i++){
    double rnd_scale = fRand(0.0, 2.0);
    vector<Point> v;
	  Shape* temp;
    Point center(rand() % 200 + 200, rand() % 200 + 200);
    /* Triangle */
    Point p1(center.getX(), center.getY() - 25);
    Point p2(center.getX()-25, center.getY() + 25);
    Point p3(center.getX()+25, center.getY() + 25);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    temp = new Shape(v, green);
		temp->setFillColor(green);
		temp->setFloodFillSeed(center);
		temp->scale(rnd_scale, center);
		vector_shape1.push_back(temp);
  }
  N =  rand() %  9 + 1;
  for (i = 0; i < N; i++){
    double rnd_scale = fRand(0.0, 2.0);
    vector<Point> v;
	  Shape* temp;
    Point center(rand() % 200 + 200, rand() % 200 + 200);
    /* Rectangle */
    Point p1(center.getX()-25, center.getY() - 25);
    Point p2(center.getX()+25, center.getY() - 25);
    Point p4(center.getX()+25, center.getY() + 25);
    Point p3(center.getX()-25, center.getY() + 25);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p4);
    v.push_back(p3);
    temp = new Shape(v, blue);
    temp->setFillColor(blue);
    temp->setFloodFillSeed(center);
    temp->scale(rnd_scale, center);
    vector_shape2.push_back(temp);
  }
  N =  rand() %  9 + 1;
  for (i = 0; i < N; i++){
    double rnd_scale = fRand(0.0, 2.0);
    vector<Point> v;
	  Shape* temp;
    Point center(rand() % 200 + 200, rand() % 200 + 200);
    Point p1(center.getX()-25, center.getY() - 10);
    Point p2(center.getX(), center.getY() - 25);
    Point p3(center.getX()+25, center.getY() - 10);
    Point p4(center.getX()+25, center.getY() +10);
    Point p5(center.getX(), center.getY() + 25);
    Point p6(center.getX()-25, center.getY() + 10);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);
    v.push_back(p6);
    temp = new Shape(v, red);
    temp->setFillColor(red);
    temp->setFloodFillSeed(center);
    temp->scale(rnd_scale, center);
    vector_shape3.push_back(temp);
  }
    world_shape.push_back(vector_shape1);
    world_shape.push_back(vector_shape2);
    world_shape.push_back(vector_shape3);
}

void create_objective(){
  srand(time(NULL));
  Point center(rand() % 200 + 200, rand() % 200 + 200);
  int rds = rand()%3+3;
  obj = new Circle(center, rds, white);
}

bool checkWin(){
  /* Titik atas kursor */
  Point p1(center_world.getX(),center_world.getY()-5);
  float b = abs(p1.getY()-obj->getCenter().getY());
  float a = abs(p1.getX()-obj->getCenter().getX());
  int rads = obj->getRadius();
  int jarak = sqrt((a*a)+(b*b));
  if (jarak <= rads){
    return true;
  }
  else{
    return false;
  }
}

void make_center_point(){
  Point p1(center_world.getX(),center_world.getY()-5);
  Point p2(center_world.getX()-5,center_world.getY()+5);
  Point p3(center_world.getX(),center_world.getY()+3);
  Point p4(center_world.getX()+5,center_world.getY()+5);
  vector<Point> v;
  v.push_back(p1);
  v.push_back(p2);
  v.push_back(p3);
  v.push_back(p4);
  cursor = new Shape(v, white);
  cursor->setFillColor(white);
  cursor->setFloodFillSeed(center_world);
}

void createFrame(){
  /* Rectangle */
  vector<Point> v;
  Point p1(100,100);
  Point p2(500,100);
  Point p4(500, 500);
  Point p3(100, 500);
  v.push_back(p1);
  v.push_back(p2);
  v.push_back(p4);
  v.push_back(p3);
  frame = new Shape(v, white);
  frame -> draw();
}

/* Zoom all shape in world */
void zoom_world(Point c, double s){
  for (int i = 0; i < Layer_size; i++){
    for (int j = 0; j < world_shape[i].size(); j++){
      world_shape[i][j]->erase();
      world_shape[i][j]->zoom(c, s);
    }
  }
  obj->zoom(c,s);
}

/* Print inside frame (Clipping) Masih Salah!!!!!*/
void Print_Inside_Frame(){
  zoom_world(center_world,scale);
  scale = 1.0;
  for (int i = Layer_size-1; i >= 0 ; i--){
    for (int j = 0; j < world_shape[i].size(); j++){
      world_shape[i][j]->draw();
      sleep(1);
    }
  }
  obj->draw();
  cursor->draw();
}

void move_world(int deltaX, int deltaY){
  for (int i = 0; i < Layer_size; i++){
    for (int j = 0; j < world_shape[i].size(); j++){
      world_shape[i][j]->moveBy(deltaX,deltaY);
    }
  }
  obj->moveBy(deltaX, deltaY);
}

void initAll(){
  create_objective();
  BuildRandomShape();
  Layer_size = world_shape.size();
  make_center_point();
  createFrame();
}

void add_Layer(){
  Color c(rand() %  255 + 1, rand() % 255 + 1, rand() % 255 + 1);
  double rnd_scale = fRand(0.0, 2.0);
  vector<Point> v;
  Shape* temp;
  /* Rectangle */
  Point p1(cursor_center_point.getX()-25, cursor_center_point.getY() - 25);
  Point p2(cursor_center_point.getX()+25, cursor_center_point.getY() - 25);
  Point p4(cursor_center_point.getX()+25, cursor_center_point.getY() + 25);
  Point p3(cursor_center_point.getX()-25, cursor_center_point.getY() + 25);
  v.push_back(p1);
  v.push_back(p2);
  v.push_back(p4);
  v.push_back(p3);
  temp = new Shape(v, c);
  temp->setFillColor(c);
  temp->setFloodFillSeed(center_world);
  temp->scale(rnd_scale, cursor_center_point);
  world_shape[Layer_size-1].push_back(temp);
}

int main(){
  bool win = false;
  int life = 3;
  screen.ClearScreen();
  linedrawer.setView(Point(100,100),Point(500,500));
  initAll();
  while(!win){
    Print_Inside_Frame();
    /* Lose */
    if (life == 0){
      break;
    }
    int a = getch();
    //cout << a << endl;
    switch (a){
      case 97 :
        //cout << "geser kiri" << endl;
        move_world(1,0);
        usleep(1000);
        break;
      case 100 :
        //cout << "geser kanan" << endl;
        move_world(-1,0);
        usleep(1000);
        break;
      case 115 :
        //cout << "geser atas" << endl;
        move_world(0,-1);
        usleep(1000);
        break;
      case 119 :
        //cout << "geser bawah" << endl;
        move_world(0,1);
        usleep(1000);
        break;
      case 91 :
        //cout << "zoom out" << endl;
        scale -= 0.3;
        usleep(1000);
        break;
      case 93 :
        //cout << "zoom in" << endl;
        scale += 0.3;
        usleep(1000);
        break;
      case 32 :
        if (checkWin()){
          win = true;
        }
        else{
          life--;
        }
        break;
      case 106 :
        Layer_size--;
        break;
      case 107 :
        add_Layer();
        break;
    }
    screen.ClearScreen();
    createFrame();
  }
  return 0;
}
