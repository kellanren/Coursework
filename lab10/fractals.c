//Kellan Ren
//Fundamentals of Computing
//Lab 10 fractals

#include "gfx.h"
#include <math.h>


void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 );
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 );
void shrinkingSquares(int, int, int, int);
void drawSquare(double, double, double);
void spiralSquares(int, int, float);
void circularLace(int, int, int);
void snowflake(int, int, int);
void tree(int, int, int, float);
void fern(int, int, int, float);
void spiralOfSpirals(int, int, float, float);

int main(){
  int width = 700, height = 700, margin = 20;
  int trueFalse = 1; //for the while loop
  char c; //for the user input

  gfx_open(width, height, "Fractals Display"); //open the window
  
  while(trueFalse){
    c = gfx_wait(); //wait for user input
    gfx_clear();

    switch(c){
      case '1': //Sierpinski triangle
        sierpinski(margin, margin, width - margin, margin, width / 2, height - margin);
        gfx_flush();
        break;

      case '2': //Shrinking squares
        shrinkingSquares(width / 2, height / 2, (width - margin) / 2, margin);
        gfx_flush();
        break;

      case '3': //Spiral squares
        spiralSquares(width / 2, height / 2, 4); 
        gfx_flush();
        break;

      case '4': //Circular lace
        circularLace(width / 2, height / 2, (width - 2 * margin) / 3);
        gfx_flush();
        break;
      
      case '5': //Snowflake
        snowflake(width / 2, height / 2, (width - 2 * margin) / 3);
        gfx_flush();
        break;
      
      case '6': //Tree
        tree(width / 2, height - margin, height / 3, M_PI / 2);
        gfx_flush();
        break;
      
      case '7': //Fern
        fern(width / 2, height - margin, 2 * height / 3, M_PI / 2);
        gfx_flush();
        break;

      case '8': //Spiral of spirals
        spiralOfSpirals(width / 2, height / 2, width / 2, M_PI);
        gfx_flush();
        break;

      case 'q':
        trueFalse = 0;
        break;
    }
  }
}


void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  // Base case. 
  if( abs(x2-x1) < 5 ) return;

  // Draw a triangle
  drawTriangle( x1, y1, x2, y2, x3, y3 );

  // Recursive calls
  sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
  sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
  sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

//Draw a triangle
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  gfx_line(x1,y1,x2,y2); 
  gfx_line(x2,y2,x3,y3);
  gfx_line(x3,y3,x1,y1);
}

//Shrinking squares
void shrinkingSquares(int x, int y, int size, int margn){

    if(size < 3) return; //Base case, stop if it gets too small

    drawSquare(x - size / 2, y - size / 2, size); //draw the square
    
    // Slow it down   usleep(1000);

    //Recursive calls for each of the four corners
    shrinkingSquares(x - size / 2, y - size / 2, size / 2 - margn, margn / 2); // top left
    shrinkingSquares(x + size / 2, y - size / 2, size / 2 - margn, margn / 2); // top right
    shrinkingSquares(x + size / 2, y + size / 2, size / 2 - margn, margn / 2); // bottom right
    shrinkingSquares(x - size / 2, y + size / 2, size / 2 - margn, margn / 2); // bottom left
}

//Draw a square
void drawSquare(double x, double y, double size){
    gfx_line(x, y, x + size, y);
    gfx_line(x + size, y, x + size, y + size);
    gfx_line(x + size, y + size, x, y + size);
    gfx_line(x, y + size, x, y);

}

//Spiral squares
void spiralSquares(int x, int y, float angle){
    if(angle > 40) return; //Base case at 40 (around 12.7pi)

    int x1, y1;

    x1 = x + exp(0.15 * angle) * cos(angle); //New x coordinate
    y1 = y - exp(0.15 * angle) * sin(angle); //New y coordinate

    double size = exp(0.1 * angle); //Size of the square

    drawSquare(x1, y1, size);

    spiralSquares(x, y, angle + M_PI / 6); //Recursive call with a new angle

}

//Circular lace
void circularLace(int x, int y, int r){
  if(r < 1) return; // base case, stop if the diameter is too small

  gfx_circle(x, y, r); //draw the circle with diameter r

  double theta = M_PI / 3; //angle for the points around the circle
  
  //Recursively draws circles at each point of the 6 points around the circle
  for(int i = 0; i < 6; i++){
    circularLace(x + r * cos(theta), y + r * sin(theta), r / 3);
    theta += M_PI / 3;
  }
}

//Snowflake
void snowflake(int x, int y, int l){
  if(l < 1) return; // base case, stop if the length is too small

  for(int i = 0; i < 5; i++){
    gfx_line(x, y, x + l * cos(2*M_PI*i/5), y + l * sin(2*M_PI*i/5));
  }
  //Recurses at the end of each line in the pentagon of snowflakes
  for(int i = 0; i < 5; i++){
    snowflake(x+l*cos(2*M_PI*i/5), y+l*sin(2*M_PI*i/5), l/3);

  }
}

//Tree
void tree(int x, int y, int l, float a){
  if(l < 1) return; //return if the length is too small

  gfx_line(x, y, x-l*cos(a), y-l*sin(a)); //draws a branch

  tree(x-l*cos(a), y-l*sin(a), 2*l/3, a-M_PI/6); //recursion for the left branch
	tree(x-l*cos(a), y-l*sin(a), 2*l/3, a+M_PI/6); //recursion for the right branch
}

//Fern
void fern(int x, int y, int l, float a){
  if(l < 3) return; // base case, stop if the length is too small

  gfx_line(x, y, x-l*cos(a), y-l*sin(a)); //draws a branch of the fern

  for (int i = 0; i < 4; i++){
		fern(x - (i+1)*l*cos(a)/4, y - (i+1)*l*sin(a)/4, l/3, a-M_PI/5); //Recursively draws the left branches
		fern(x - (i+1)*l*cos(a)/4, y - (i+1)*l*sin(a)/4, l/3, a+M_PI/5); //Recursively draws the right branches
	}
}

//Spiral of spirals, starts at the point in the center of the spiral and then spirals inwards 
void spiralOfSpirals(int x, int y, float s, float t){
  if (s < 1) return; // base case, stop if the size is too small

	// center point
	gfx_point(x, y);

	// each rotation
	s -= s/15;
	int xf = x+s*cos(t);
	int yf = y+s*sin(t);
	t += 0.5;

	// recursion
	spiralOfSpirals(xf, yf, s/3, 0);
	spiralOfSpirals(x, y, s, t);

}