/*
	Author: Dat Pham
	Class: CS362
	Term: Spring 2018
	Description: write unittest for function buyCard Validates the card being played can be played then calls cardEffect to play the card
*/
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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
	int resultFromBuyCard = 0;
	int resultFromCheck = 0;
	int failTotal = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
			   
	printf("\n------------------------------------TESTING buyCard()------------------------------\n");
	printf("\n Description: Validates the card being played can be played then calls cardEffect to play the card");
	printf("\n---------------------------------------------------------------------------------------------------\n");
	memset(&gState,23,sizeof(struct gameState));
	initializeGame(2, k, seed, &gState);
	
	printf("\nTesting if you do not have any buys left\n");
	gState.numBuys = 0;
	gState.coins = 5;
	resultFromBuyCard = buyCard(2,&gState);
	resultFromCheck = checkResult(resultFromBuyCard,-1);
	if(resultFromCheck == 1)
			failTotal++;
		
	printf("\nTesting if you do not enought coins\n");
	gState.numBuys = 2;
	gState.coins = 2;
	resultFromBuyCard = buyCard(2,&gState);
	resultFromCheck = checkResult(resultFromBuyCard,-1);
	if(resultFromCheck == 1)
			failTotal++;
	
	printf("\nTesting a perfect purchase\n");
	gState.numBuys = 2;
	gState.coins = 10;
	resultFromBuyCard = buyCard(2,&gState);
	resultFromCheck = checkResult(resultFromBuyCard,0);
	if(resultFromCheck == 1)
			failTotal++;
	
	printf("\nTesting when we have exact coins amount\n");
	gState.numBuys = 1;
	gState.coins = 5;
	resultFromBuyCard = buyCard(2,&gState);
	resultFromCheck = checkResult(resultFromBuyCard,0);
	if(resultFromCheck == 1)
			failTotal++;
	
	printf("\nTesting there are not any of that type of card left\n");
	gState.numBuys = 1;
	gState.coins = 5;
	resultFromBuyCard = buyCard(6,&gState);
	resultFromCheck = checkResult(resultFromBuyCard,-1);
	if(resultFromCheck == 1)
			failTotal++;
	
	if(failTotal!=0){
		printf("\nTEST FAILED, the number fails: %d\n",failTotal);
	}else{
		printf("\nTEST SUCCESSFULLY\n");
	}
	printf("\n---------------------------------End Testing buyCard()----------------------------------\n");
	
	return 0;
}