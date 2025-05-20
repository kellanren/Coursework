//Kellan Ren
//Fundamentals of Computing
//Lab 8 'crossfunc.c'
#define WORDS 20
#define LETTERS 16
#define BOARD 15

#include "crossfunc.h"

void print_board(char board[BOARD][BOARD], FILE *out){
	for(int x = -1; x <= BOARD; x++){
		for(int y = -1; y <= BOARD; y++){
			if(x == -1 || x == BOARD){
			//Horizontal edge, print -
				fprintf(out, "-");
			}else if(y == -1 || y == BOARD){
			//Vertical edge, print |
				fprintf(out, "|");
			}else{
			// print X or ' ' on the inside
				fprintf(out, "%c", board[x][y]);
			}
		}
		fprintf(out, "\n");
	}
}

//returning the number of words in a file and update the words array
int read_file(FILE *fp, Word words[WORDS]){
	int num_words = 0;
	char current[LETTERS];

	while(fgets(current, sizeof(current), fp) != NULL && num_words < 20){
		current[strcspn(current, "\n")] = '\0'; //remove newline char if present
		if(current[0] == '.'){
			break;
		}
		int valid = 1;
		//make sure that every char is a letter
		for(int i = 0; i < strlen(current); i++){
			if(!isalpha(current[i])){
				break;
			}
		}	
		//between 2 and 15 letters
		if(strlen(current) < 2 || strlen(current) > 15){
			valid = 0;
		}
		//update word and length if its a valid word
		if(valid == 1){
			uppercase(current);
			strcpy(words[num_words].word, current);
			words[num_words].length = strlen(current);
			num_words++;
		}
	}
	return num_words;
}
//make the letters uppercase
void uppercase(char word[LETTERS]){
	int i = 0;
	while(word[i] != '\0'){
		word[i] = toupper(word[i]);
		i++;
	}
}
//compare function for qsort
//return positive if the first element should go after the second
int compare(const void *a, const void *b){
	const Word *wordA = (const Word *)a;
	const Word *wordB = (const Word *)b;

	return wordB->length - wordA->length; 
}

//place the first word in the center of the board
void place_center(char board[BOARD][BOARD], Word *word){
	//get starting position based on position and length of the word
	int first_col = (BOARD - word->length) / 2;
	int row = BOARD / 2;	

	//place the word on the board
	for(int i = 0; word->word[i] != '\0'; i++){
		board[row][first_col + 1] = word->word[i];
	}
	//update the word struct
	word->x = row;
	word->y = first_col;
	word->direction = 0;
	word->placed = 1;
	scramble_word(word);
}

//checks to see if a word can be placed at an intersection point, 
int can_place(char board[BOARD][BOARD], Word *word, int direction, int x, int y, int index){
	int len = word->length;

	//vertical direction
	if(direction == 1){
		//end of the word relative to the board
		int top = x - index;
		int bottom = x + (len - index - 1);

		//checks the top and bottom to be in the bounds of the board
		if(top < 0 || bottom >= BOARD || y >= BOARD || y < 0){
			return 0;
		}

		//check the cell above the word
		if(top > 0 && board[top - 1][y] != ' '){
			return 0;
		}
	
		//check the cell below the word
		if(bottom < BOARD - 1 && board[bottom + 1][y] != ' '){
			return 0;
		}

		for(int i = 0; i < len; i++){
			int curr_x = top + i;
			int curr_y = y;

			//check if the cell is empty or matches the word char
			if(board[curr_x][curr_y] != ' ' && board[curr_x][curr_y] != word->word[i]){
				return 0;
			}
	
			//check the neighbors but not at index bc that won't be empty
			if(i != index){

				//left neighbor
				if(curr_y > 0 && board[curr_x][curr_y - 1] != ' '){
					return 0;
				}
				//right neighbor
				if(curr_y < BOARD - 1 && board[curr_x][curr_y + 1] != ' '){
					return 0;
				}
			}
		}
		return 1;
	//checking for across
	}else if(direction == 0){
		//ends of the word
		int left = y - index;
		int right = y + (len - index - 1);

		//make sure the ends are in the bounds
		if(left < 0 || right >= BOARD || x < 0 || x >= BOARD){
			return 0;
		}
		//check index to the left of the board
		if(left > 0 && board[x][left - 1] != ' '){
			return 0;
		}
		//check index to the right of the board
		if(right < BOARD - 1 && board[x][right + 1] != ' '){
			return 0;	
		}

		for(int i = 0; i < len; i++){
			int curr_x = x;
			int curr_y = left + i;
			if(curr_y < 0 || curr_y >= BOARD){
				return 0;
			}

			//check top and bottom only if isn't at intersect
			if(i != index){
				//top neighbor
				if(curr_x > 0 && board[curr_x - 1][curr_y] != ' '){
					return 0;
				}
				//bottom neighbor
				if(curr_x < BOARD - 1 && board[curr_x + 1][curr_y] != ' '){
					return 0;
				}
			}
		}
		return 1;
	//invalid direction
	}else{
		return 0;
	}
}

//places the word 
void place(char board[BOARD][BOARD], Word *word, int direction, int x, int y, int index){
	int len = word->length;
	if(direction == 1){
		//starting index
		int top = x - index;
		for(int i = 0; i < len; i++){
			int curr_x = top + i;
			int curr_y = y;

			if(board[curr_x][curr_y] == ' ' || board[curr_x][curr_y] == word->word[i]){
				board[curr_x][curr_y] = word->word[i];
			}
		}

		//update the word now that its placed
		word->direction = 1;
		word->x = top;
		word->y = y;
		word->placed = 1;
		scramble_word(word);
	}else if(direction == 0){
		int left = y - index;
	
		//if checks are valid, add the word
		for(int i = 0; i < len; i++){
			int curr_x = x;
			int curr_y = left + i;
			if(board[curr_x][curr_y] == ' ' || board[curr_x][curr_y] == word->word[i]){
				board[curr_x][curr_y] = word->word[i];
			}
		}

		//update the word
		word->x = x;
		word->y = left;
		word->direction = 0;
		word->placed = 1;
		scramble_word(word);
	}
}

//finding the places to intersect closer to the center, return 1 if intersection exists, -1 if it doesn't. 
//looking at words that are already placed and initialized
int best_intersection(char board[BOARD][BOARD], Word *word1, Word *word2, int *index, int *x, int *y){
	int len1 = strlen(word1->word);
	int len2 = strlen(word2->word);
	//passed by value, initialized at -1 to check
	*index = -1;
	*x = -1;
	*y = -1;
	int min_distance = BOARD; //big number for the minimum function

	//word 1 horizontal so try vertically
	if(word1->direction == 0){
		//loop through both words and check shared letters
		for(int i = 0; i < len1; i++){
			for(int j = 0; j < len2; j++){
				if((word1->word[i] == word2->word[j])){
					//find x and y of the shared position
					int x_one = word1->x;
					int y_one = word1->y + i;
					
					//if its placeable, find distance to combined center
					if(can_place(board, word2, 1, x_one, y_one, j) == 1){
						int distance = abs(i - len1 / 2) + abs(j - len2 / 2);
						//if its below the minimum distance, update the indices
						if(distance < min_distance){
							*x = x_one;
							*y = y_one;
							*index = j;
							min_distance = distance;
						}	
					}
				}
			}
		}
	//word1 is vertical so try horizontal
	}else if(word1->direction == 1){
		//same stuff
		for(int i = 0; i < len1; i++){
			for(int j = 0; j < len2; j++){
				if((word1->word[i] == word2->word[j])){
					int x_one = word1->x + i;
					int y_one = word1->y;
			
					if(can_place(board, word2, 0, x_one, y_one, j) == 1){
						int distance = abs(i - len1 / 2) + abs(j - len2 / 2);
						if(distance < min_distance){
							*x = x_one;
							*y = y_one;
							*index = j;
							min_distance = distance;
						}
					}
				}
			}
		}
	}
	//if x and y are unchanged, return -1
	if(*x == -1 || *y == -1){
		return -1;
	}	
	//intersection exists, and indices are updated
	return 1;
}

//function to add a word to the skipped linked list
Node *skip(Node *head, Word word, FILE *out){
	//create memory of size Node
	Node *new_node = (Node*) malloc(sizeof(Node));
	if(!new_node){
		fprintf(out, "Memory Allocation failed.\n");
		return head;
	}
	//copy the word to new_node
	new_node->word;
	
	//point node to the head, making it at the front of the linked list
	//rather do this than append 
	new_node->next = head;

	return new_node;
}

//try to place the words from the skipped linked list
int place_skip(char board[BOARD][BOARD], Word placed_words[], Node **skipped_head, int *words_placed, FILE *out){
	//starting at the head so no node points to it
	Node *prev = NULL;
	Node *current = *skipped_head; // let the current node represent the head node 
	int num_placed = 0;

	//go to the end of the linked list w current
	while(current != NULL){
		int success = 0;
		int index, x, y;	
		
		//try placing current->word with any of the words already placed
		for(int i = 0; i < *words_placed; i++){
			//get the opposite of the placed words' direction
			int direction = 1 - placed_words[i].direction;
			//checks if a good intersection exists, and places it
			if(best_intersection(board, &placed_words[i], &current->word, &index, &x, &y) == 1){
				//if its possible to place, place on board
				place(board, &current->word, direction, x, y, index);
				fprintf(out, "Placed %s even though it was skipped.\n", current->word.word);
				//copies current->word to placed_words[*words_placed] by memory directly
				memcpy(&placed_words[*words_placed], &current->word, sizeof(Word));
				(*words_placed)++;
				success = 1;
				num_placed++;

				break;
			}
		}
	//removes a placed word from the linked list
		if(success){
			Node *temp = current;
			// checks if its the head, and sets head to next node
			if(prev == NULL){
				*skipped_head = current->next;
			//if not, puts the previous node point to the next one
			}else{
				prev->next = current->next;
			}
			//update the current to be the next node
			current = current->next;
			free(temp); // free previous memory
		}
		//move to the next word if it wasn't placed
		else{
			prev = current; 
			current = current->next;
		}
	}	
	return num_placed; 
}

//function to place words, adds to linked list if can't
void place_words(char board[BOARD][BOARD], Word words[], int num_words, FILE *out){
	Node *skipped_head = NULL; // empty linked list for skipped words
	Word placed_words[WORDS]; //array to store successful words placed
	int words_placed = 0;
	int curr_word = 0;

	//place the first word in the center
	place_center(board, &words[0]);
	placed_words[words_placed] = words[0];
	words_placed++;
	curr_word++;

	//try the remaining words to add the words to linked list if not
	while(curr_word < num_words){
		int index, x, y;
		int placed = 0;
		for(int i = 0; i < words_placed; i++){
			//make direction opposite of the placed words'
			int direction = 1 - placed_words[i].direction;
			//if it can be placed, then place it
			if(best_intersection(board, &placed_words[i], &words[curr_word], &index, &x, &y) == 1){
				place(board, &words[curr_word], direction, x, y, index);
				fprintf(out, "Placing %s\n", words[curr_word].word);
				//add to placed words array and increment counter
				placed_words[words_placed] = words[curr_word];
				words_placed++;
				placed = 1;
				break;
			}
		}
		//if it couldn't be placed, add it to the skipped linked list
		if(!placed){
			fprintf(out, "Couldn't place %s. Adding to the skipped list.\n", words[curr_word].word);
			skipped_head = skip(skipped_head, words[curr_word], out);
		}
		curr_word++;
	}
	int num_places = -1;

	//loop through the linked list until it can't fit anymore
	while(num_places != 0){
		num_places = place_skip(board, placed_words, &skipped_head, &words_placed, out);
	}
	//free remaining nodes in the skipped list
	while(skipped_head != NULL){
		Node *temp = skipped_head;
		skipped_head = skipped_head->next;
		free(temp);
	}
}

//generate an anagram and update the clue
void scramble_word(Word *word){
	//use a temp array to avoid changing word struct until the end
	char temp[LETTERS]; 
	strcpy(temp, word->word);
	int len = strlen(temp);

	//scramble the array
	for(int i = 0; i < len - 1; i++){
		int j = i + rand() / (RAND_MAX / (len - i) + 1);
		//randomly swap them
		char temp_char = temp[i];
		temp[i] = temp[j];
		temp[j] = temp_char;
	}
	strcpy(word->clue, temp);
	word->clue[len] = '\0';
}

//print out the anagrams
void display_clues(Word placed_words[], int words_placed, FILE *out){
	fprintf(out, "\nClues: \n");
	fprintf(out, "Location | Direction | Anagram\n");
	for(int i = 0; i < words_placed; i++){
		Word *word = &placed_words[i];
		if(word->placed && word->x >= 0 && word->y >= 0 && (word->direction == 0 || word->direction == 1)){
			fprintf(out, " %4d,%2d | %8s | %-15s\n", word->x, word->y, (word->direction == 0) ? "Across" : "Down", word->clue);
		}
	}
}

//update the solution and puzzle arrays to the value of board array
void update_solution_puzzle(char board[BOARD][BOARD], char solution[BOARD][BOARD], char puzzle[BOARD][BOARD]){
	for(int i = 0; i < BOARD; i++){
		for(int j = 0; j < BOARD; j++){
			if(board[i][j] != ' '){
				solution[i][j] = board[i][j];
				puzzle[i][j] = ' ';
			}
		}
	}
}
//used this for the deliverable part. I dont want to get rid of my hard work :)
void print_words(Word *w, int num_words, FILE *out){
	printf("Words entered in order: \n");
	for(int i = 0; i < num_words; i++){
		printf("%s\n", w->word);
		w++;
	}
}
