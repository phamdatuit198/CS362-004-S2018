/*
	Author: Dat Pham
	CS 362
	Spring 2018
	
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


// fail counter variables

int failCardEffect = 0;
int failDiscardCard = 0;
int failDrawCard = 0;
int failDeckHandCount = 0;
int failNumberBuy = 0;
int failDeckHandCount2 = 0;


void checkCard(struct gameState *state,int player) {
  
    struct gameState tempState;
	int drawCard1,drawCard2,drawCard3,drawCard4;
	int result;
	int i=0;
    // save state to tempState
    memcpy(&tempState,state,sizeof(struct gameState));

    // check cardEffect
    result = cardEffect(council_room,0,0,0,state,0,0);
	if(result)
		failCardEffect++;
	
	 //discardCard
	result = discardCard(0,player,&tempState,0);
	if(result)
		failDiscardCard++;
	
    // call draw card 4 times
    drawCard1 = drawCard(player,&tempState);
    drawCard2 = drawCard(player,&tempState);
    drawCard3 = drawCard(player,&tempState);
    drawCard4 = drawCard(player,&tempState);
	
	// check drawcard failed
	if(tempState.deckCount[player] != 0){
		if (drawCard1 == -1) {
			failDrawCard++;
		}
		if (drawCard2 == -1) {
			failDrawCard++;
		}
		if (drawCard3 == -1) {
			failDrawCard++;
		}
		if (drawCard4 == -1) {
			failDrawCard++;
		}
	}
	
	//check numBuys
    tempState.numBuys++;
	if (tempState.numBuys != state->numBuys) {
        failNumberBuy++;
    }

    // check hand and deck have amount don't same
    if(!(state->handCount[player]==tempState.handCount[player] 
		&&state->deckCount[player] == tempState.deckCount[player]))
			failDeckHandCount++;


    // check another player with hand and deck counts don't match
    for (i = 0; i < tempState.numPlayers; i++) {
        if (i != player) {
            if (!(state->handCount[i] == tempState.handCount[i] &&
                  state->deckCount[i] == tempState.deckCount[i])) {
                      failDeckHandCount2++;
            }
        }
    }
	
	// check drawCard with another people
    for (i = 0; i < tempState.numPlayers; i++) {
        if (i != player) {
            result = drawCard(i,&tempState);
           
            if (result == -1 && tempState.deckCount[i] != 0)
                failDrawCard++;
        }
    }
	
}


int main () {
	
	int loop = 10000;
    int i, n, player;
	int total = 0;
	int countDeck = 0;
	int countHand = 0;
	int countDiscard = 0;
    struct gameState state;
	int numberOfPlayers[] = {2,3,4};
    srand(time(NULL));
	
	printf("\n----------- RANDOM TEST ------------");
    printf("\n Testing function council_roomCard()");
    printf("\n------------------------------------");
	

    // random the game state
    for (n = 0; n < loop; n++) {
        for (i = 0; i < sizeof(struct gameState); i++)
            ((char*)&state)[i] = floor(Random() * 256);
        	
        // random select values
        state.numPlayers = numberOfPlayers[rand() % 3];
        state.numBuys = 1;
        state.playedCardCount = floor(Random() * (MAX_DECK-1));
        player = state.numPlayers - 2;
        state.whoseTurn = player;
		
		countDeck 	 = floor(Random() * MAX_DECK);
        countHand 	 = floor(Random() * MAX_HAND);
        countDiscard = floor(Random() * MAX_DECK);
        for (i = 0; i < state.numPlayers; i++) {
            state.deckCount[i] 	  = countDeck;
            state.handCount[i]    = countHand;
            state.discardCount[i] = countDiscard;
        }
        // call the check function
        checkCard(&state,player);
    }
 
    total = failCardEffect + failDrawCard + failDiscardCard + failDeckHandCount + failNumberBuy + failDeckHandCount2;
       
	printf("\n\n\n----- RESULT RANDOM TEST---------\n");
	printf("\nTotal FAILED: %d",total);
	printf("\nThe amount failed failed drawCard(): %d",failDrawCard);
	printf("\nThe amount failed failed cardEffect() failed: %d",failCardEffect);
	printf("\nThe amount failed failed discardCard() failed: %d",failDiscardCard);
	printf("\nCount numBuy don't match: %d",failNumberBuy);
	printf("\nCount hand and desk don't match: %d",failDeckHandCount);
	printf("\nCount hand and desk don't match from another player: %d\n",failDeckHandCount2);
    return 0;
}
