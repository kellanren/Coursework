//Kellan Ren
//CSE 20311
//Lab 4 a simple array
//Find the mean and standard deviation of the grades in the array
#include <stdio.h>
#include <math.h>

// function prototypes ...
float average(int [], int);
float stdv(int [], float, int);

int main()
{
  int grades[] =
    { 96,73,62,87,80,63,93,79,71,99,
      82,83,80,97,89,82,93,92,95,89,
      71,97,91,95,63,81,76,98,64,86,
      74,79,98,82,77,68,87,70,75,97,
      71,94,68,87,79 };

  // rest of program goes here ...
	int num = sizeof(grades) / sizeof(grades[0]);
	float avg = average(grades, num);
	float standev = stdv(grades, avg, num);
	printf("There are %d grades.\n", num);
	printf("The average of the grades is: %.2lf\n", avg);
	printf("The standard deviation of the grades is: %.2lf\n", standev);
  
  return 0;
}

// function definitions ...
float average(int grades[], int num){
	int total = 0;
	for(int i = 0; i < num; i++){
		total += grades[i];
	}
	float result = 0;
	return total*1.0 / num;
}
float stdv(int grades[], float mean, int num){
	float sqdfsum = 0;
	for(int i = 0; i < num; i++){
		sqdfsum += (grades[i] - mean) * (grades[i] - mean);
	}
	return sqrt(sqdfsum / num);
}
