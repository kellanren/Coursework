//Kellan Ren
//CSE 20311
//Lab 4 ND football
//make a menu to display facts
#include <stdio.h>
#include "nd_data.h"
#define SENTINEL 1

void printMenu();
void record(int);
void numLosses(int);
void numWins(int);
void mostWins();
void mostLosses();

int main(){
	while(SENTINEL){
		int choice;
		printMenu();
		scanf("%d", &choice);
		if(choice == 6){
			printf("Goodbye! \n");
			break;	
		}
		if(choice < 1 || choice > 6){
			printf("You can't do that.\n");
			continue;
		}
		int year = 0;
		int lossNum = 0;
		int winNum = 0;
		switch(choice){
			case 1: 
				printf("Enter the year: ");
				scanf("%d", &year);	
				record(year);
				break;
			case 2:
				printf("Enter the minimum number of losses: ");
				scanf("%d", &lossNum);
				numLosses(lossNum);
				break;
			case 3:
				printf("Enter the minimum number of wins: ");
				scanf("%d", &winNum);
				numWins(winNum);
				break;
			case 4:
				mostWins();
				break;
			case 5:
				mostLosses();
				break;
		}
	}
	return 0;
}

void printMenu(){
	printf("\n");
	printf("1: display the record for a given year. \n");
	printf("2: diplay the years with at least \"n\" losses. \n");
	printf("3: diplay the years with at least \"n\" wins. \n");
	printf("4: diplay the years with the most wins. \n");
	printf("5: diplay the years with the most losses. \n");
	printf("6: exit \n");
	printf("Enter your choice: ");
}

void record(int year){
	if(year > 2024 || year < 1900){
		printf("Bruh. Enter a year between 2024 and 1900. \n");
	}else{
		int numberWins = wins[year - 1900];
		int numberLosses = losses[year - 1900];
		printf("Wins: %d, Losses: %d \n", numberWins, numberLosses);

	}
}

void numLosses(int num){
	int size = sizeof(losses) / sizeof(losses[0]);
	printf("Years with at least %d losses: ", num);
	for(int i = 0; i < size; i++){
		if(losses[i] >= num){
			printf("%d ", i + 1900);
		}
	}		
	printf("\n");
}

void numWins(int num){
	int size = sizeof(wins) / sizeof(wins[0]);
	printf("Years with at least %d wins: ", num);
	for(int i = 0; i < size; i++){
		if(wins[i] >= num){
			printf("%d ", i + 1900);
		}
	}
	printf("\n");
}

void mostWins(){
	int max = 0;
	int size = sizeof(wins) / sizeof(wins[0]);
	for(int i = 0; i < size; i++){
		if(wins[i] > max){
			max = wins[i];
		}
	}
	printf("Year with %d wins: ", max);
	for(int i = 0; i < size; i++){
		if(wins[i] == max){
			printf("%d ", i + 1900);
		}
	}
	printf("\n");
}


void mostLosses(){
	int min = 0; 
	int size = sizeof(losses) / sizeof(losses[0]);
	for(int i = 0; i < size; i++){
		if(losses[i] > min){
			min = losses[i];
		}
	}
	printf("Year with %d losses: ", min);
	for(int i = 0; i < size; i++){
		if(losses[i] == min){
			printf("%d ", i + 1900);
		}		
	}
	printf("\n");
}
