#include <stdio.h>

double add(double a, double b);
double sub(double a, double b);
double mult(double a, double b);
double div(double a, double b);
void menu();

int main(){
	double num1, num2;
	double quotient;
	int val;
	
	while(1){
		menu();
		printf("Enter your choice: ");
		scanf("%d", &val);
		
		if(val == 5){
			printf("Good bye!\n");
			break;	
		}
		if(val < 1 || val > 5){
			printf("Bruh. That's not an option. Pick a number between 1 and 5.\n");
			continue;
		}

		printf("Enter your first number: ");
		scanf("%lf", &num1);
		printf("Enter your second number: ");
		scanf("%lf", &num2);

		switch(val){
			case 1: 
				printf("\n(%lf) + (%lf) = %lf\n", num1, num2, add(num1, num2));
				break;
			case 2: 
				printf("\n(%lf) - (%lf) = %lf\n", num1, num2, sub(num1, num2));
				break;
			case 3: 
				printf("\n(%lf) * (%lf) = %lf\n", num1, num2, mult(num1, num2));
				break;
			case 4: 
				if(num2 == 0){
					printf("\nYou can't divide by 0. Try again.\n");
				}else{
					quotient = div(num1, num2);
					printf("\n(%lf) / (%lf) = %lf\n", num1, num2, quotient);
				}
				break;
		}
	}

	return 0;
}

double add(double a, double b){
	return a + b;
}

double sub(double a, double b){
	return a - b;
}

double mult(double a, double b){
	return a * b;
}

double div(double a, double b){
	return a / b;
}

void menu(){
	printf("\nWhat would you like to do?\n");
	printf(" 1 for addition\n");
	printf(" 2 for subtrction\n");
	printf(" 3 for multiplication\n");
	printf(" 4 for division\n");
	printf(" 5 to exit\n");
}
