//Kellan Ren
//FunComp
//Lab 7 "pathfunc.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pathfunc.h"

int readFile(const char *fileName, Point list[], int MAX){
	char number[10];
	int count = 0;
	FILE *fp = fopen(fileName, "r");
	if(!fp){
		printf("Error. Could not open file.\n");
		return 0;
	}
	while(1){
		fscanf(fp, "%f %f", &list[count].x, &list[count].y);	
		if(feof(fp)) break;	
		count++;
	}
	fclose(fp);
	return count;
}

double calculate(Point list[], int count){
	double xDistance = 0.0, yDistance = 0.0, totalDistance = 0.0;
	for(int i = 0; i < count - 1; i++){
		xDistance = list[i+1].x - list[i].x;
		yDistance = list[i+1].y - list[i].y;
		totalDistance += sqrt(xDistance * xDistance + yDistance * yDistance);	
	}
	return totalDistance;
}

void printResult(double answer, int count, Point list[30]){
	printf("There are %d points: \n\n", count);
	printf("  x   |   y\n");
	printf("------+--------\n");
	for(int i = 0; i < count; i++){
		printf("%5.1f | %5.1f\n", list[i].x, list[i].y);
	}
	printf("The length of the path through the points is: %.2f\n", answer);
}
