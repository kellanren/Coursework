//Kellan Ren
//FunComp
//Lab 7 "path.c"
#include <stdio.h>
#include "pathfunc.h"

int main(){
	int MAX = 30;
	char fileName[100];
	Point list[MAX];	
	
	printf("Enter the file that you want to choose: ");
	scanf("%s", fileName);
	
	int count = readFile(fileName, list, MAX);
	if(count != 0){
		double length = calculate(list, count);
		printResult(length, count, list);
	}
	return 0;
}

