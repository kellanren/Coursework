//Kellan Ren
//Fundamentals of Computing
//Lab 7 Part 2 'usastates.c'
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "statesfunc.h"

const int SIZE = 100;

int main(){
	States states[SIZE];
	FILE *fp = askFile(); //gets a file pointer from the askFile function
	if(fp == NULL){
		printf("Error opening file.\n"); //Checks to see if the file exists
		return 1;
	}
	 
	int count = read_states(fp, states); //sets the count to the number of lines in the file

	while(1){
		int choice = user_choice(states, count);
		
		if(choice == 1){
			display_capital(states, count);
		}else if(choice == 2){
			display_abb(states, count);
		}else if(choice == 3){
			display_state(states, count);
		}else if(choice == 4){
			display_starting_letter(states, count);
		}else if(choice == 5){
			display_everything(states, count);
		}else if(choice == 6){
			printf("Good job studying!\n");
			break;
		}else{
			printf("That is not an option. Try again. \n");
		}
	}

	return 0;
}
