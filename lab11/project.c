//Kellan Ren
//Fundamentals of Computing
//Lab 11: Blackjack
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DECK_SIZE 52
#define MAX_CARDS 11

//
typedef struct {
    char *rank;
    char *suit;
    int value;
} Card;

typedef struct {
    Card hand[MAX_CARDS];
    int cardCount;
    int total;
    int hasBlackjack;
    int isDealer;
} Player;

const char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
const int values[]   = { 2 ,  3 ,  4 ,  5 ,  6 ,  7 ,  8 ,  9 ,  10 , 10 , 10 , 10 , 11};
const char *suits[]  = {"Hearts", "Diamonds", "Clubs", "Spades"};

void shuffleDeck(Card deck[]);
Card drawCard(Card deck[], int *deckIndex);
void addCard(Player *p, Card c);
int getHandValue(Player *p);
void printHand(Player *p, const char *name, int hideSecond);
int hasBlackjack(Player *p);
void playDealer(Player *dealer, Card deck[], int *deckIndex);
void playRound(int *balance, Card deck[], int *deckIndex);

int main() {
    srand(time(NULL));
    Card deck[DECK_SIZE];
    int deckIndex = 0;
    int balance = 100;
    shuffleDeck(deck);
    printf("Welcome to Blackjack!\n");
    printf("If you don't know how to play, that's too bad.\n");

    while (balance > 0) {
        playRound(&balance, deck, &deckIndex);
        if(balance == 0){
            printf("You have lost all your money!\n");
            break;
        }
        printf("Current balance: $%d\n", balance);
        if(balance == 0){
            break;
        }
        char again;
        printf("Play another round? (y/n): ");
        scanf(" %c", &again);
        if (again == 'y'){
            continue;
        }else if (again == 'n') {
            break;
        }else if(again == 'q'){
            printf("Quitting the game.\n");
            break;
        }else{
            printf("Invalid input. Try again.\n");
        }
    }
    printf("Game over. Final balance: $%d\n", balance);
    return 0;
}

void shuffleDeck(Card deck[]) {
    int idx = 0;
    for (int s = 0; s < 4; s++) {
        for (int r = 0; r < 13; r++) {
            deck[idx].rank = (char *)ranks[r];
            deck[idx].suit = (char *)suits[s];
            deck[idx].value = values[r];
            idx++;
        }
    }
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

Card drawCard(Card deck[], int *deckIndex) {
    if (*deckIndex >= DECK_SIZE - 10){
        shuffleDeck(deck);
        *deckIndex = 0;
    }
    return deck[(*deckIndex)++];
}

void addCard(Player *p, Card c) {
    p->hand[p->cardCount++] = c;
}

int getHandValue(Player *p) {
    int total = 0, aces = 0;
    for (int i = 0; i < p->cardCount; i++) {
        total += p->hand[i].value;
        if (strcmp(p->hand[i].rank, "A") == 0) aces++;
    }
    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }
    return total;
}

void printHand(Player *p, const char *name, int hideSecond) {
    printf("%s's hand:\n", name);
    for (int i = 0; i < p->cardCount; i++) {
        if (i == 1 && hideSecond && p->isDealer) {
            printf("  [Hidden Card]\n");
        } else {
            printf("  %s of %s\n", p->hand[i].rank, p->hand[i].suit);
        }
    }
    if (!hideSecond || !p->isDealer) {
        printf("Total: %d\n\n", getHandValue(p));
    }
}

int hasBlackjack(Player *p) {
    return (p->cardCount == 2 && getHandValue(p) == 21);
}

void playDealer(Player *dealer, Card deck[], int *deckIndex) {
    while (getHandValue(dealer) < 17) {
        addCard(dealer, drawCard(deck, deckIndex));
    }
}

void playRound(int *balance, Card deck[], int *deckIndex) {
    Player player = {.cardCount = 0, .total = 0, .hasBlackjack = 0, .isDealer = 0};
    Player dealer = {.cardCount = 0, .total = 0, .hasBlackjack = 0, .isDealer = 1};
    int wager; 
    while(1){
        printf("You have $%d. Enter wager: ", *balance);
        scanf("%d", &wager);
        if (wager < 1 || wager > *balance) {
            printf("Invalid wager. Please enter a value between 1 and %d.\n", *balance);
            continue;
        }else{
            printf("You wagered $%d.\n", wager);
            break;
        }
    }

    addCard(&player, drawCard(deck, deckIndex));
    addCard(&dealer, drawCard(deck, deckIndex));
    addCard(&player, drawCard(deck, deckIndex));
    addCard(&dealer, drawCard(deck, deckIndex));

    printHand(&player, "Player", 0);
    printHand(&dealer, "Dealer", 1);

    if (hasBlackjack(&player) || hasBlackjack(&dealer)) {
        printHand(&dealer, "Dealer", 0);
        if (hasBlackjack(&player) && hasBlackjack(&dealer)) {
            printf("Both have Blackjack. Push.\n");
        } else if (hasBlackjack(&player)) {
            printf("Blackjack! You win 1.5x your wager.\n");
            *balance += wager * 1.5;
        } else {
            printf("Dealer has Blackjack. You lose.\n");
            *balance -= wager;
        }
        return;
    }

    char choice;
    while (1) {
        if(hasBlackjack(&player) && !hasBlackjack(&dealer)){
            break;
        }
        printf("Hit or Stand? (h/s): ");
        scanf(" %c", &choice);
        printf("\n");
        if (choice == 'h') {
            addCard(&player, drawCard(deck, deckIndex));
            printHand(&player, "Player", 0);
            if (getHandValue(&player) > 21) {
                printf("You busted!\n");
                *balance -= wager;
                return;
            }
        } else if(choice == 's') {
            break;
        } else {
            printf("Invalid choice. Please enter 'h' or 's'.\n");
            continue;
        }
    }

    playDealer(&dealer, deck, deckIndex);
    printHand(&dealer, "Dealer", 0);

    int pt = getHandValue(&player);
    int dt = getHandValue(&dealer);

    if (dt > 21 || pt > dt) {
        printf("You win!\n");
        *balance += wager;
    } else if (pt < dt) {
        printf("Dealer wins.\n");
        *balance -= wager;
    } else {
        printf("Push (tie).\n");
    }
}