//Kellan Ren
// FunComp
//Lab 6 "playlife.c"
#include "lifefunc.h"
#include <stdio.h>
#include <string.h>

int SIZE = 40;

int main(int argc, char *argv[]){
	char board[SIZE][SIZE];
	initialize(board, SIZE);
	if(argc == 1){
		interactive(board, SIZE);
	}else if(argc == 2){
		batch(argv[1], board, SIZE);
	}else{
		printf("Too many command line arguments. Try again. \n");
		return 1;
	}
	return 0;
}
