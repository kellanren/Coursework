// Kellan Ren
// FunComp 
// Lab 6 "lifefunc.c"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "lifefunc.h"

void interactive(char board[][SIZE], int size){
	while(1){
		char c;
		int x, y;
		display(board, size);
		printf("COMMAND: ");
		scanf(" %c", &c);
		if(c == 'a' || c == 'r'){
			while(!(isspace(getchar())));
			scanf("%d %d", &x, &y);
			if(c == 'a'){
				addCell(board, x, y);
			}
			if(c == 'r'){
				removeCell(board, x, y);
			}
		}else if(c == 'n'){
			iterate(board, size);
		}else if(c == 'q'){
			printf("Bye!\n");
			break;
		}else if(c == 'p'){
			autopilot(board, size);
		}else{
			while(getchar() != '\n');
			printf("You can't do that. Try again\n");
		}
	}
}

void batch(char fileName[], char board[][SIZE], int size){
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL){
		printf("Couldn't open file. \n");
	}
	char c;
	int x, y;
	while(!feof(fp)){
		fscanf(fp, "%c", &c);
		if(c == 'a'){
			fscanf(fp, "%d %d", &x, &y);
			addCell(board, x, y);
		}else if(c == 'p'){
			display(board, size);
			autopilot(board, size);
		}
	}
}

void display(char board[][SIZE], int size){
	printf(" ");
	for(int i = 0; i < size; i++){
		printf("-");
	}
	printf("\n");

	for(int i = 0; i < size; i++){
		printf("|");
		for(int j = 0; j < size; j++){
			printf("%c", board[i][j]);
		}
		printf("|\n");
	}
	printf(" ");
	for(int i = 0; i < size; i++){
		printf("-");
	}
	printf("\n");
}

void addCell(char board[][SIZE], int x, int y){
	if(x < 0 || x > 39 || y < 0 || y > 39){
		printf("Error. Enter valid coordinates. \n");
	}else if(board[x][y] == 'X'){
		printf("That space already has an X in it.\n");
	}else{
		board[x][y] = 'X';
	}
}	

void removeCell(char board[][SIZE], int x, int y){
	if(x < 0 ||x > 39 || y < 0 ||y > 39){
		printf("Error. Enter valid coordinates.\n");
	}else if(board[x][y] != 'X'){
		printf("There are no live spaces there. Try again\n");
	}else{
		board[x][y] = ' ';
	}
}

void iterate(char board[][SIZE], int size){
	char testboard[SIZE][SIZE];
	arrCopy(board, testboard, size);
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			int count = countCells(board, i, j, size);
			if(board[i][j] == 'X'){
				if(count == 2 || count == 3){
					testboard[i][j] = 'X';
				}else{
					testboard[i][j] = ' ';
				}
			}else{
				if(count == 3){
					testboard[i][j] = 'X';
				}else{
					testboard[i][j] = ' ';
				}
			}	
		}
	}
	arrCopy(testboard, board, size);
}

void arrCopy(char arr1[][SIZE], char arr2[][SIZE], int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			arr2[i][j] = arr1[i][j];
		}
	}
}

void autopilot(char board[][SIZE], int size){
	while(1){
		system("clear");
		iterate(board, size);
		display(board, size);
		usleep(100000);
	}
}

void initialize(char board[][SIZE], int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			board[i][j] = ' ';
		}
	}
}

int countCells(char board[][SIZE], int i, int j, int size){
	int count = 0;
	for(int k = -1; k <= 1; k++){
		for(int l = -1; l <= 1; l++){
			if(k == 0 && l == 0) continue;
			int row = i + k;
			int col = j + l;
			if(col < 40 && col >= 0 && row < 40 && row >= 0){
				if(board[row][col] == 'X'){
					count++;
				}
			}
		}
	}
	return count;
}
