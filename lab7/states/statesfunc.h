//Kellan Ren
//Fundamentals of Computing
//Lab 7 Part 2 'statesfunc.h'
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	char abbrev[5];
	char name[20];
	char capital[30];
	int year;
} States;

FILE * askFile();
int read_states(FILE *fp, States state[]);
void print_menu();
int user_choice(States state[], int count);
void display_capital(States state[], int count);
void display_abb(States state[], int count);
void display_state(States state[], int count);
void display_starting_letter(States state[], int count);
void display_everything(States state[], int count);
void display_one(States state);
void toLowerCase(char str[]);


