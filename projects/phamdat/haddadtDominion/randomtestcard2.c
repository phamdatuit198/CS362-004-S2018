/*
	Author: Dat Pham
	CS 362
	
*/
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int failCardEffect = 0;
int failDiscardCard = 0;
int failDrawCard = 0;
int failDeckHandCount = 0;


void checkCard(struct gameState *state,int player) {
  
	int result;
	int drawCard1,drawCard2,drawCard3;
    struct gameState tempState;

    //save state to tempState
    memcpy(&tempState,state,sizeof(struct gameState));

	
    cardEffect(smithy,0,0,0,state,0,0);
	
	//discardCard
	result = discardCard(0,player,&tempState,0);
	
	if(result)
		failDiscardCard++;
	
    drawCard1 = drawCard(player,&tempState);
    drawCard2 = drawCard(player,&tempState);
    drawCard3 = drawCard(player,&tempState);

    // check if drawcard failed
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
	}

    // check if the hand and deck have amount don't same
    if(!(state->handCount[player]==tempState.handCount[player] 
		&&state->deckCount[player] == tempState.deckCount[player]))
			failDeckHandCount++;
}


int main () {
    
    int loop = 10000;
    int i, n, player;
	int total = 0;
    struct gameState state;
    srand(time(NULL));
	
	printf("\n----------- RANDOM TEST ------------");
    printf("\n Testing function RefactorSmithyCard()");
    printf("\n------------------------------------");
	
    // random the game state
    for (n = 0; n < loop; n++) {
        for (i = 0; i < sizeof(struct gameState); i++)
            ((char*)&state)[i] = floor(Random() * 256);
        
        // randomly select appropriate values
        player = floor(Random() * MAX_PLAYERS);
		state.whoseTurn = player;
		
        state.playedCardCount = floor(Random() * (MAX_DECK-1));
		state.handCount[player] = floor(Random() * MAX_HAND);
		state.deckCount[player] = floor(Random() * MAX_DECK);
        state.discardCount[player] = floor(Random() * MAX_DECK);
           
        // call the check function
        checkCard(&state,player);
    }
    total = failCardEffect + failDrawCard + failDiscardCard + failDeckHandCount;
       
	printf("\n\n\n----- RESULT RANDOM TEST---------\n");
	printf("\nTotal FAILED : %d",total);
	printf("\nThe amount failed failed drawCard(): %d",failDrawCard);
	printf("\nThe amount failed failed discardCard() failed: %d",failDiscardCard);
	printf("\nCount hand and desk don't match: %d\n",failDeckHandCount);

    return 0;
}
