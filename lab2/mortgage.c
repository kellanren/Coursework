#include <stdio.h>
#include <stdbool.h>

int main(){
	double principal, rate, payment, interest, total, balance;
	int years, months;
	//Make sure the inputs are positive numbers	
	while(true){
		printf("How much would you like to take out(principal)? ");
		scanf("%lf", &principal);
		if(principal >= 0){
			break;
		}else{
			printf("Error: Please enter a positive number.\n");
		}
	}	
	
	while(true){
		printf("What is the interest rate you are getting charged? ");
		scanf("%lf", &rate);
		if(rate >= 0){
			break;
		}else{
			printf("Error: Please enter a positive number.\n");
		}
	}
	
	while(true){
		printf("What is your monthly payment on the loan? ");
		scanf("%lf", &payment);
		if(principal >= 0){
			break;
		}else{
			printf("Error: Please enter a positive number.\n");
		}
	}
	//Make sure the monthly payment is greater than the monthly interest trate
	if(payment <= balance * rate){
		printf("Error: Monthly payment is too low. Loan balance would increase each month.\n");
	}
	//Make the top row
	printf("Month\tPayment\tInterest\tBalance\n");
	int month = 1;
	//Make sure the balance is positive, if so, make sure the balance is greater than the payment, run through possible options, add interest, print
	balance = principal;
	while(balance > 0){
		interest = (rate / 12 * balance);
		balance += interest;
		if(balance <= payment){
			payment = balance;
			balance -= payment;
			total += payment;
			month++;
			printf("%5d   $%7.2f   $%7.2f   $%9.2f\n", month, payment, interest, balance);
		}else{
			balance -= payment;
			total += payment;
			month++;
			printf("%5d   $%7.2f   $%7.2f   $%9.2f\n", month, payment, interest, balance);
		}
	}
	years = (month - 1) / 12;
	months = (month - 1) % 12;
	printf("You paid a total of $%.2f over %d years and %d months.\n", total, years, months);  

	return 0;
}
