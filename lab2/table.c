#include <stdio.h>
#include <math.h>

int main(){
	int x, y, num;
	printf("Enter X (number of columns: ");
	scanf("%d", &x);

	printf("Enter Y (number of rows): ");
	scanf("%d", &y);

	//Print the top header with the X value size
	for(int i = 1; i < x + 1; i++){
		printf("\t%d", i);
	}
	printf("\n");
	
	//Create the separator line 	
	printf("   ");
	for(int i = 0; i < 5; i++){
		printf("-");
	}
	for(int i = 0; i < (x-1)*9; i++){
		printf("-");
	}
	printf("\n");

	//Create the actual multiplication table
	for(int i = 1; i < y + 1; i++){
		printf("%d |", i);
		for(int j = 1; j < x + 1; j++){
			num = i * j;
			printf("\t%d", num);
		}
		printf("\n");
	}

	return 0;
}
