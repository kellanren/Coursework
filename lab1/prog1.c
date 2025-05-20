//Kellan Ren
//CSE 20311
//Lab 1 Project 1

#include <stdio.h>

int main(){
	int touchdown, extrapt, fieldgl, safety;
	int totalScore;	

	printf("Touchdowns Scored: ");	
	scanf("%d", &touchdown);

	printf("Extra Points Scored: ");	
	scanf("%d", &extrapt);

	printf("Field Goals Scored: ");	
	scanf("%d", &fieldgl);

	printf("Safeties Scored: ");	
	scanf("%d", &safety);

	totalScore = (touchdown * 6) + (extrapt) + (fieldgl * 3) + (safety * 2);

	printf("The Irish scored a total of: %d points \n", totalScore);


	return 0;
}

