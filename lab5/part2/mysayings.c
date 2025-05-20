//Kellan Ren
//FunComp
//Lab 5 Part 2 A sayings manager

#include <stdio.h>
#include <string.h>

#define MAXSAYINGS 50
#define MAXLENGTH 256

void print_menu();
int loadSayings(char [MAXSAYINGS][MAXLENGTH], char [MAXLENGTH], char *filename);
void display(char [MAXSAYINGS][MAXLENGTH], int);
void addSaying(char [MAXSAYINGS][MAXLENGTH], int *count);
void searchSaying(char [MAXSAYINGS][MAXLENGTH], int count);
void saveSaying(char [MAXSAYINGS][MAXLENGTH], int count);

int main(){
	char sayings[MAXSAYINGS][MAXLENGTH];
	char sayings2[MAXLENGTH];
	int count = 0;
	char filename[31];

	printf("Please enter the startup file name: ");
	scanf("%30s", filename);

	FILE *fp = fopen(filename, "r");
	if(!fp){
		printf("Bruh. That file doesn't exist. Try again\n");
		return 1;
	}
	fclose(fp);

	count = loadSayings(sayings, sayings2, filename);
	while(1){
		int choice = 0;
		print_menu();
		printf("Enter a choice: ");
		scanf("%d", &choice);
		if(choice > 5 || choice < 1){
			printf("That is not an option.\n");
			break;
		}
		if(choice == 5){
			printf("BYE!!\n");
			break;
		}
		switch(choice){
			case 1:
				display(sayings, count);
				break;
			case 2:
				addSaying(sayings, &count);
				break;
			case 3:
				searchSaying(sayings, count);
				break;
			case 4: 
				saveSaying(sayings, count);
				break;
		}
	}
	return 0;
}

void print_menu(){
	printf("\nMENU: \n");
	printf("1. display all sayings currently in the database\n");
	printf("2. enter a new saying into the database\n");
	printf("3. list sayings that contain a given substring entered by user\n");
	printf("4. save all sayings in a new text file\n");
	printf("5. quit the program\n");
	
}

int loadSayings(char sayings[MAXSAYINGS][MAXLENGTH], char sayings2[MAXLENGTH], char *filename){
	FILE *fp = fopen(filename, "r");
	int count = 0;
	while(1){
		fgets(sayings2, MAXLENGTH, fp);
		if(feof(fp)) break;
		sayings2[strlen(sayings2) - 1] = '\0';
		strcpy(sayings[count], sayings2);
		count++;
	}
	return count;
}

void display(char sayings[MAXSAYINGS][MAXLENGTH], int count){
	if(count == 0){
		printf("There aren't any sayings\n");	
	}else{
		for(int i = 0; i < count; i++){
			printf("%s\n", sayings[i]);
		}
	}
}

void addSaying(char sayings[MAXSAYINGS][MAXLENGTH], int *count){
	if(*count >= MAXSAYINGS){
		printf("Can't add any more sayings.\n");
	}else{
		printf("Enter a new saying: ");
		scanf(" %[^\n]", sayings[*count]);
		(*count)++;	
	}
}

void searchSaying(char sayings[MAXSAYINGS][MAXLENGTH], int count){
	char search[MAXLENGTH];
	int found = 0;
	printf("Enter a substring to search: ");
	scanf(" %[^\n]", search);
	printf("Matching sayings: \n");
	for(int i = 0; i < count; i++){
		if(strstr(sayings[i], search)){
			printf("%s\n", sayings[i]);
			found = 1;
		}
	}
	if(!found){
		printf("No sayings found with '%s'.\n", search);
	}
}

void saveSaying(char sayings[MAXSAYINGS][MAXLENGTH], int count){
	char filename[31];
	printf("Enter the file name you want to save to: ");
	scanf("%30s", filename);
	FILE *fp = fopen(filename, "w");
	if(!fp){
		printf("Error: Couldn't create file.\n");
	}else{
		for(int i = 0; i < count; i++){
			fprintf(fp, "%s\n", sayings[i]);
		}	
		fclose(fp);
		printf("Saved. \n");
	}
}

