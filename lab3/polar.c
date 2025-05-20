#include <stdio.h>
#include <math.h>

int get_quadrant(double, double);
double get_radius(double, double);
double get_angle(double, double);
void show_info(int, double, double);

int main(){
	double a, b;
	printf("Please enter two numbers(X, Y): ");
	scanf("%lf%lf", &a, &b);
	int quad = get_quadrant(a, b);
	double rad = get_radius(a, b);
	double angle = get_angle(a, b);
	show_info(quad, rad, angle);

	return 0;
}

int get_quadrant(double x, double y){
	int quadrant;
	if(x > 0){
		if(y > 0){
			quadrant = 1;
		}else{
			quadrant = 4;
		}
	}else if(x < 0){
		if(y > 0){
			quadrant = 2;
		}else{
			quadrant = 3;
		}
	}
	return quadrant;
}

double get_radius(double x, double y){
	double radius = sqrt(x * x + y * y);
	return radius;
}

double get_angle(double x, double y){
	double angle = atan2(y, x);
	double degrees = angle * (180.0 / M_PI);
	return degrees;
}

void show_info(int quad, double radius, double angle){
	printf("The points are in quadrant %d.\nIn polar coordinates, the R value is %.2lf.\nThe angle is %.2lf degrees.\n", quad, radius, angle);
}
