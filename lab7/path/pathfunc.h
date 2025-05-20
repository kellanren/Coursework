//Kellan Ren
//FunComp
//Lab 7 "pathfunc.h"
typedef struct{
	float x;
	float y;
} Point;

int readFile(const char *fileName, Point list[], int MAX);
double calculate(Point list[], int count);
void printResult(double answer, int count, Point list[]);
