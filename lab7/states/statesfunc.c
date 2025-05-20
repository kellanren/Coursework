//Kellan Ren
//Fundamentals of Computing 
//Lab 7 Part 2 'statesfunc.c'
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "statesfunc.h"

FILE * askFile(){
	char fileName[30];
	
	printf("Enter a file name: ");
	scanf("%s", fileName);
	FILE *fp = fopen(fileName, "r");
	return fp;	//returns the file pointer 
}

int read_states(FILE *fp, States state[]){
	int count = 0;
	char line[100];
	
	while(1){
		fgets(line, 100, fp);

		if(feof(fp)) break;
		
		strcpy(state[count].abbrev, strtok(line, ",")); //seperated by commas
		strcpy(state[count].name, strtok(NULL, ","));
		strcpy(state[count].capital, strtok(NULL, ","));
		state[count].year = atoi(strtok(NULL, "\n")); //convert the string to an int

		count++;
	}	
	return count;
}

void print_menu(){
	printf("\nMENU: \n");
	printf("1. Display the capital of a state (enter state name)\n");
	printf("2. Display the abbreviation of a state (enter state name)\n");
	printf("3. Display the state name (enter state abbreviation)\n");
	printf("4. Enter a letter, which displays all of the states starting with that letter. \n");
	printf("5. Display all of the info.\n");
	printf("6. Exit\n");
}

int user_choice(States state[], int count){
	int choice = 0;
	print_menu(); //prints the menu every time
	printf("Enter a choice: ");
	scanf("%d", &choice);
	return choice;
}

void display_capital(States state[], int count){
	char stateName[20];
	int trueFalse = 0;
	printf("Enter the state name: ");
	scanf("%s", stateName);

	toLowerCase(stateName); //Makes the input lower case

	for(int i = 0; i < count; i++){
		char temp[20];
		strcpy(temp, state[i].name); //assigns the temporary variable to temp
		toLowerCase(temp); //so that the function doesn't change the actual value in the file
		if(strcmp(temp, stateName) == 0){ //compares the lower case names
			printf("The state capital is: %s\n", state[i].capital);
			trueFalse = 1;
			break;
		}else{
			trueFalse = 0;
		}
	}
	if(!trueFalse) printf("That is not a state.\n"); //checks to see if the state they entered was correctly spelled or exists
}

void display_abb(States state[], int count){
	char stateName[30];
	int trueFalse = 0;
	printf("Enter the state name that you want the abbreviation to: ");
	scanf("%s", stateName);
	for(int i = 0; i < count; i++){
		char temp[30];
		strcpy(temp, state[i].name);//same stuff as before
		toLowerCase(temp);
		if(strcmp(temp, stateName) == 0){
			printf("The state abbreviation is: %s\n", state[i].abbrev);
			trueFalse = 1;
			break;
		}else{
			trueFalse = 0;
		}
	}
	if(!trueFalse) printf("That is not a state.\n");
}

void display_state(States state[], int count){
	char abbreviation[5];
	int trueFalse = 0;
	printf("Enter the abbreviation for the state that you want: ");//pretty much same thing
	scanf("%s", abbreviation);
	for(int i = 0; i < count; i++){
		char temp[5];
		strcpy(temp, state[i].abbrev);
		toLowerCase(temp);
		if(strcmp(temp, abbreviation) == 0){
			printf("The state with the abbreviation %s is: %s \n", state[i].abbrev, state[i].name);
			trueFalse = 1;
			break;
		}else{
			trueFalse = 0;
		}
	}
	if(!trueFalse) printf("That abbreviation is wrong.\n");

}

void display_starting_letter(States state[], int count){
	getchar(); //clear char from command line
	char starting_letter;
	int num = 0;

	printf("Enter a letter: ");
	scanf("%s", &starting_letter);

	for(int i = 0; i < count; i++){
		if(tolower(starting_letter) == tolower(state[i].name[0])){ //don't need a temporary thing because its comparing chars
			printf("%s starts with a(n) %c.\n", state[i].name, starting_letter);
			num++;
		}
	}
	if(num == 0){
		printf("Sorry. There are no states that start with a(n) %c.\n", starting_letter);
	}
}

void display_everything(States state[], int count){
	for(int i = 0; i < count; i++){ //displays all of the states through iterating every one through the display_one function
		display_one(state[i]);
	}	
}

void display_one(States state){ 
	printf("Abbreviation: %s, Name: %s, Capital %s, Year: %d\n", state.abbrev, state.name, state.capital, state.year);
}

void toLowerCase(char str[]){
	if(str == NULL){
		return;
	}else{
		for(int i = 0; str[i] != '\0'; i++){ //Keeps going until NULL character
			str[i] = tolower(str[i]); //assigns lowercase value to each character
		}
	}
}
