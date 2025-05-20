//Kellan Ren
//Fundamentals of Computing
//Lab 8 'crossword.c'
//Main crossword driver

#define LETTERS 16
#define WORDS 20
#define BOARD 15
#include "crossfunc.h"


int main(int argc, char *argv[]){

	srand(time(NULL)); //scrambling the clues differently each time	

	//Initialize boards
	char board[BOARD][BOARD];
	char puzzle[BOARD][BOARD];
	char solution[BOARD][BOARD];
	
	for(int i = 0; i < BOARD; i++){
		for(int j = 0; j < BOARD; j++){
			puzzle[i][j] = '#';
			solution[i][j] = '.';
			board[i][j] = ' ';	
		}
	}

	FILE *out = stdout; //default output is stdout, changes if argc == 3
	int num_words = 0;
	Word words[WORDS]; //initialize words array

	//no file in command line, run interactive mode
	if(argc == 1){
		char current[LETTERS] = ""; //make this empty for now
		while(num_words < WORDS){ //20 word max
			printf("Enter a word ('.' to stop): ");
			scanf("%s", current);
			current[strcspn(current, "\n")] = '\0'; //remove newline
			//end immediately if enters '.'
			if(strcmp(current, ".") == 0){
				break;
			}
			//make sure all chars are letters
			int valid = 1;
			for(int i = 0; i < strlen(current); i++){
				if(!isalpha(current[i])){
					printf("Error. A non-character is present in the word.\n");
					valid = 0;
					break;
				}	
			}
			//make sure between 2 and 15 letters
			if(strlen(current) < 2 || strlen(current) > 15){
				printf("Error. This word is not between 2 and 15 letters.\n");
				valid = 0;
			}		
			//if its valid update the word and length to the word struct
			if(valid == 1){
				uppercase(current);
				strcpy(words[num_words].word, current);
				words[num_words].length = strlen(current);
				num_words++;
			}	
		}		
	}else if(argc == 2){
		//open argv[1] and make sure it exists
		FILE *fp = fopen(argv[1], "r");
		if(fp == NULL){
			printf("Couldn't open file. \n");
			return 1;
		}
		//read the file and see how many words are in it
		num_words = read_file(fp, words);
		fclose(fp); 
		//output file
	}else if(argc == 3){
		//out is argv[2] instead of stdout
		FILE *fp = fopen(argv[1], "r");
		if(fp == NULL){
			printf("Couldn't open file. \n");
			return 1;
		}
		num_words = read_file(fp, words);
		fclose(fp);
		out = fopen(argv[2], "w");
		if(!out){
			printf("Error opening file: %s\n", argv[2]);
			return 2;
		}
	//cant do more than 3 command line arguments
	}else{
		printf("Sorry. That doesn't work. Try again.\n");
		return 1;
	}
	//sort words array with qsort
	qsort(words, num_words, sizeof(words[0]), compare);

	//place the words, supposed to call skipped words as well
	place_words(board, words, num_words, out);

	//update the solution and puzzle arrays based on the new board array
	update_solution_puzzle(board, solution, puzzle);	

	//print the solution board and puzzle board to stdout or output file, whichever one they chose
	fprintf(out, "Solution:\n");
	print_board(solution, out);

	fprintf(out, "Puzzle:\n");
	print_board(puzzle, out);

	//display the clues
	display_clues(words, num_words, out);	

	//close the file if it was opened 
	if(out != stdout){
		fclose(out);
	}

	return 0;
}

