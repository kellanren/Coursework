//Kellan Ren
//Fundamentals of Computing
//Lab 9 Bouncing ball

#include <stdlib.h>
#include <unistd.h>
#include "gfx.h"
#include <time.h>
#include <math.h>

#define PI 3.14159265358979323846

void update_pos(int *, int *, int *, int *, int, int, int);
void randomize_vel(int *, int *);

int main(){
	int wid = 800, ht = 600;
	int xc = wid / 2, yc = ht / 2; //initial ball position(middle)
	int radius = 20; //Ball radius
	int vx = 3, vy = 2; //Random initial velocity

	gfx_open(wid, ht, "Bouncing Ball"); //open window
	srand(time(NULL)); //seed for random number generator

	while(1){
		//check for user input
		if(gfx_event_waiting()){
			int c = gfx_wait();
			//quit if enter 'q'
			if(c == 'q'){
				break;
			//if left mouse button clicked, update ball position to mouse click position
			}else if(c == 1){
				xc = gfx_xpos();
				yc = gfx_ypos();
				randomize_vel(&vx, &vy); //assign a new random vel
			}
		}
		//update ball position
		update_pos(&xc, &yc, &vx, &vy, wid, ht, radius);
		
		//clear the screen and draw the ball
		gfx_clear();		
		gfx_color(255, 0, 0);
		gfx_circle(xc, yc, radius);
	
		gfx_flush();

		//sleep for 16ms to control the speed of the animation
		usleep(16000);
	}

	return 0;
}

//function to update the position of ball
void update_pos(int *x, int *y, int *vx, int *vy, int width, int height, int radius){
	//update x and y by velocities passed by reference
	*x += *vx;
	*y += *vy;

	//check left and right wall collisions
	if(*x - radius <= 0 || *x + radius >= width){
		*vx = -*vx; //reverse x velocity 
		*x = (*x - radius <= 0) ? radius : width - radius; //prevent sticking to walls
	}

	//check top and bottom wall collisions
	if(*y - radius <= 0 || *y + radius >= height){
		*vy = -*vy; //reverse y velocity
		*y = (*y - radius <= 0) ? radius : height - radius; //prevent sticking to walls
	}	
}

//function to assign random velocity 
void randomize_vel(int *vx, int *vy){
	int speed = rand() % 5 + 2; //random speed between 2 and 6
	double angle = (double)(rand() % 360) * PI / 180.0; //random angle in radians

	*vx = (int)(speed * cos(angle)); 
	*vy = (int)(speed * sin(angle));

	//make sure velocity isn't 0
	if(*vx == 0){
		*vx = (rand() % 2 == 0) ? 1 : -1;
	}

	if(*vy == 0){
		*vy = (rand() % 2 == 0) ? 1 : -1;
	}

}
