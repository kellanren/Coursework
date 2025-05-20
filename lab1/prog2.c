/* Kellan
 * CSE 20311
 * Lab 1 Assignemnt 2
 */

#include <stdio.h>
#include <math.h>
int main(){
	double first_input, second_input;
	double third_side;

	printf("Pythagorean Theorem Calculator!\n");

	printf("Enter your first number: ");
	scanf("%lf", &first_input);

	printf("Enter your second number: ");
	scanf("%lf", &second_input);

	third_side = sqrt((first_input * first_input) + (second_input * second_input));
	printf("Your third side is %lf.\n", third_side);

	return 0;
}

