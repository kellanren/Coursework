//Kellan Ren
//Lab 5
//CSE 20311
//Scrabble
#include <stdio.h>
#include <ctype.h>

int main(){
	char filename[31];
	FILE *fp;
	int count[26] = {0};
	int totalChars = 0, totalLetters = 0;
	
	printf("Enter file name: ");
	scanf("%s", filename);
	fp = fopen(filename, "r");

	if(fp == NULL){
		printf("Error: File couldn't be read.\n");
		return 1;
	}
	
	while(1){
		char c = fgetc(fp);
		if(c == EOF){
			break;
		}
		totalChars++;
		if(isalpha(c)){
			totalLetters++;
			c = tolower(c);
		}
		count[c - 'a']++;
	}
	fclose(fp);

	printf("\n");
	
	printf("General summary for %s:\n", filename);
	printf("Total number of characters: %d\n", totalChars);
	printf("Total number of letters: %d\n", totalLetters);

	printf("\n");
	int size = sizeof(count) / sizeof(count[0]);

	printf("Letter counts: \n");
	int numLines = 0;
	for(int i = 0; i < size; i++){
		printf("%c: %5d\t", i + 'a', count[i]);
		numLines++;
		if(numLines == 6){
			printf("\n");
			numLines = 0;
		}
	}
	
	printf("\n");
	printf("\n");

	printf("Letter percentages: \n");
	numLines = 0;
	for(int i = 0; i < size; i++){
		printf("%c: %5.1f%\t", i + 'a', count[i] * 100.0 / totalLetters);
		numLines++;
		
		if(numLines == 6){
			printf("\n");
			numLines = 0;
		}
	}
	
	printf("\n");
	return 0;
}

