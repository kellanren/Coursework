// quad.c
// computes the roots of a quadratic equation
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

double findDiscriminant(double a, double b, double c);

int main(){
 	bool notA = true;
	double a = 1, b, c, disc, x1, x2;
	while(a != 0 && notA){
		printf("Enter the coefficients (a,b,a) of a quadratic equation: ");
		scanf("%lf %lf %lf", &a, &b, &c);
		disc = findDiscriminant(a, b, c);
		if(a == 0){
			notA = false;
			printf("Exiting...\n");
		}else if(disc > 0){
			x1 = (-b + sqrt(disc)) / (2 * a);
			x2 = (-b - sqrt(disc)) / (2 * a);
			printf("Quadratic equation roots are: %lf and %lf.\n", x1, x2);
		}else if(disc == 0){
			x1 = (b + sqrt(disc)) / (2 * a);
			printf("Quadratic equation root is: %lf. \n", x1);
		}else{
			printf("There are no real solutions.\n");
		}	
	}
	return 0;		
}
double findDiscriminant(double a, double b, double c){
		double disc = b * b - (4 * a * c);
		return disc;
}
