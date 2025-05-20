//Kellan Ren
//CSE 20311
//Lab 4 prime numbers
//Find the prime numbers from 2-999
#include <stdio.h>

#define MAX 1000

int main(){
	//Initialize all elements to true
	int numbers[MAX];
	for(int i = 2; i <= MAX + 2; i++){
		numbers[i] = 1;
	}	
	
	//Sieve of Eratoshthenes
	for(int i = 2; i * i <= MAX; i++){
		if(numbers[i]){
			for(int j = i * i; j <= MAX; j+=i){
				numbers[j] = 0;
			}
		}
	}

	//Print
	for(int i = 2; i < MAX; i++){
		if(numbers[i]){
			printf("%d ", i);
		}
	}
	printf("\n");
	
	return 0;
}
