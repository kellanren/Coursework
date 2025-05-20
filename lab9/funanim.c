//Kellan Ren
//Fundamentals of Computing
//Lab 9 fun animation

#include "gfx.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define PI 3.14159265358979323846
#define NUM_SHAPES 3

void draw_circle(int, int, int);
void draw_square(int, int, int);
void draw_triangle(int, int, int);

int main(){
	
	int width = 800, height = 600; //Window Size
	int centerX = width / 2, centerY = height / 2; //Set center of window
	double angle = 0.0; //current rotation angle
	double speed = 0.05; //initialize rotation speed
	int radius = 150; //distance of shapes from the center
	int run = 1; //flag to control animation
	int clock = 1; //flag to control rotation direction

	gfx_open(width, height, "Rotating Animation");
	srand(time(NULL));

	while(1){
		//check for user input
		if(gfx_event_waiting()){
			int c = gfx_wait();
			//quit if enter 'q'
			if(c == 'q'){
				break;
			//change direction if left mouse button clicked
			}else if(c == 1){
				clock = -clock;
			//pause/resume animation if space bar pressed	
			}else if(c == ' '){
				run = !run;
			}
		}
		//if animation is running, clear screen, draw shapes
		if(run){
			gfx_clear();
			for(int i = 0; i < NUM_SHAPES; i++){
				double new_angle = angle + i * 2 * PI / NUM_SHAPES; //spread them out evenly
				int x = centerX + radius * cos(new_angle); //set the new x positions
				int y = centerY + radius * sin(new_angle); //set the new y positions 
				//draw shapes based on their index
				if(i % 3 == 0){
					draw_square(x, y, 30);
				}else if(i % 3 == 1){
					draw_circle(x, y, 20);
				}else{
					draw_triangle(x, y, 50);
				}
			}	
			gfx_flush();
			
			angle += speed * clock; //update angle

			usleep(16000);
		}
	}

	return 0;
}

void draw_circle(int x, int y, int radius){
	gfx_color(255, 0, 0);
	//draw circle
	for(double theta = 0; theta < 2 * PI; theta += 0.1){
		int x1 = x + radius * cos(theta);
		int y1 = y + radius * sin(theta);
		gfx_point(x1, y1);
	}
}

void draw_square(int x, int y, int size){
	gfx_color(0, 255, 0);
	int half = size / 2;
	//draw square
	gfx_line(x - half, y - half, x + half, y - half);
	gfx_line(x + half, y - half, x + half, y + half);
	gfx_line(x + half, y + half, x - half, y + half);
	gfx_line(x - half, y + half, x - half, y - half);
}

void draw_triangle(int x, int y, int size){
	gfx_color(0, 0, 255);
	int half = size / 2;
	//draw triangle
	gfx_line(x, y - half, x - half, y + half);
	gfx_line(x - half, y + half, x + half, y + half);
	gfx_line(x + half, y + half, x, y - half);
}
