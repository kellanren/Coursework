//Kellan Ren
//Fundamentals of Computing
//Lab 9 Symbolic Typewriter
#include "gfx.h"
#include <stdlib.h>
#include <math.h> //For Pi

#define SIZE 50 //Define size of the shapes

//Function prototypes
void draw_square(int, int, int);
void draw_cir(int, int, int);
void draw_tri(int, int, int);
void draw_poly(int, int, int, int);

int main(){
	gfx_open(600, 400, "Symbolic Typewriter");
	int xm, ym; //Mouse coords
	char c; //char input
	
	while(1){
		c = gfx_wait();
		xm = gfx_xpos();
		ym = gfx_ypos();
	
		if(c == 'q'){
			break;
		}
	
		switch(c){
			//Draw a square
			case 1: 
				gfx_color(0, 0, 255);
				draw_square(xm, ym, SIZE);
				break;
			//Draw a circle
			case 'c':
				gfx_color(255, 255, 255);
				draw_cir(xm, ym, SIZE);
				break;
			//Draw a triangle
			case 't':
				gfx_color(0, 255, 0);
				draw_tri(xm, ym, SIZE / 2);
				break;
			//Clear the screen
			case 27:
				gfx_clear();
				break;
			//Draw polygon with sides based on key pressed
			default:
				if(c >= '3' && c <= '9'){
					gfx_color(128, 0, 128);
					draw_poly(xm, ym, SIZE, c - '0');
				}
				break;
		}
	}
	
	return 0;
}


void draw_square(int x, int y, int size){
	int len = size / 2;
	gfx_line(x - len, y - len, x + len, y - len); //Top
	gfx_line(x + len, y - len, x + len, y + len); //Right
	gfx_line(x + len, y + len, x - len, y + len); //Bottom
	gfx_line(x - len, y + len, x - len, y - len); //Left
}


void draw_cir(int x, int y, int size){
	int rad = size / 2; //Make radius half of size
	gfx_circle(x, y, size);
}


void draw_tri(int x, int y, int size){
	int len = size / 2;
	gfx_line(x, y - len, x + len, y + len);
	gfx_line(x, y - len, x - len, y + len);
	gfx_line(x - len, y + len, x + len, y + len);
}


void draw_poly(int x, int y, int size, int num_sides){
	double rad = size / 2.0; //Make radius half of size
	double angle = 2 * M_PI / num_sides; //Calculate angle between points
		
	for(int i = 0; i < num_sides; i++){
		double x1 = x + rad * cos(i * angle); //Calculate x1
		double y1 = y + rad * sin(i * angle); //Calculate y1
		double x2 = x + rad * cos((i + 1) * angle); //Calculate x2
		double y2 = y + rad * sin((i + 1) * angle); //Calculate y2
		
		//Draw line between points
		gfx_line(x1, y1, x2, y2);
	}
}
