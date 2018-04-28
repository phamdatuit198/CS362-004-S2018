/*
	Author: Dat Pham
	Class: CS362
	Term: Spring 2018
	Description: write unittest for function shuffled is getter for gameState returning the card in 
					a specific position of the hand
*/
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int checkResult(int x, int y){
	
	if(x == y){
		
		printf("PASSED\n");
		return 0;
	}else{
		printf("FAILED\n");
		return 1;
	}
}

int main(){
	
	int seed = 1000;
	struct gameState gState;
	int numPlayer = 2;
	int player = 0;
	int resultFromShuffle = 0;
	int resultFromCheck = 0;
	int failTotal = 0;
	
	//kingdom cards
	int k[10] =  {adventurer, council_room, feast, gardens, mine,
						remodel, smithy, village, baron, great_hall};
						
	printf("\n--------------------------------Testing function shuffle()------------------------------------------");
	printf("\nDescription: function is getter for gameState returning the card in a specific position of the hand");
	printf("\n---------------------------------------------------------------------------------------------------\n");
	memset(&gState,23,sizeof(struct gameState));
	initializeGame(numPlayer,k,seed,&gState);
	
	printf("\nChecking if deck count is 0 of player\n");
	gState.deckCount[player] = 0;
	resultFromShuffle = shuffle(player,&gState);
	resultFromCheck = checkResult(-1,resultFromShuffle);
	if(resultFromCheck == 1)
		failTotal++;
	
	printf("\nChecking if deck count is 5\n");
	gState.deckCount[player] = 5;
	shuffle(player,&gState);
	resultFromCheck = checkResult(5,gState.deckCount[player]);
	if(resultFromCheck == 1)
		failTotal++;
	
	printf("\nChecking cards are shuffled already\n");
	int card1 = gState.deck[player][0];
	shuffle(player,&gState);
	int card2 = gState.deck[player][0];
	if(card1 != card2){
		
		resultFromCheck = checkResult(0,0);
	}else{
		resultFromCheck = checkResult(0,2);
	}
	if(resultFromCheck == 1)
		failTotal++;
	
	if(failTotal!=0){
		printf("\nTEST FAILED, the number fails: %d\n",failTotal);
	}else{
		printf("\nTEST SUCCESSFULLY\n");
	}
	printf("\n---------------------------------End Testing shuffle()----------------------------------\n");
	
	return 0;
}