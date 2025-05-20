//Kellan Ren
//Fundamentals of Computing
//Lab 8 'crossfunc.h'
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define WORDS 20
#define LETTERS 16
#define BOARD 15

typedef struct{
	char word[LETTERS];
	char clue[LETTERS];
	int x;
	int y;
	int length;
	int placed;
	int direction;
} Word;

typedef struct Node{
	Word word;
	struct Node *next;
} Node;

void print_board(char[BOARD][BOARD], FILE *);
int read_file(FILE *, Word[WORDS]);
void uppercase(char[LETTERS]);
int compare(const void *, const void *);
void place_center(char[BOARD][BOARD], Word*);
int can_place(char[BOARD][BOARD], Word*, int, int, int, int);
void place(char[BOARD][BOARD], Word*, int, int, int, int);
Node* skip(Node*, Word, FILE*);
int place_skip(char[BOARD][BOARD], Word[], Node**, int*, FILE*);
void place_words(char[BOARD][BOARD], Word[], int, FILE*);
void scramble_word(Word*);
void display_clues(Word[], int, FILE*);
void update_solution_puzzle(char[BOARD][BOARD], char[BOARD][BOARD], char[BOARD][BOARD]);
void print_words(Word *, int, FILE *);

