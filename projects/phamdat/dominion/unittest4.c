/*
Author: Dat Pham
Class: CS 362

Description: UnitTest function gainCard of Dominion
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
	int failTotal = 0;
	int resultFromGainCard = 0;
	int resultFromCheck = 0;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
	struct gameState gState;
	
	
	printf("\n------------------------------------TESTING gainCard()------------------------------\n");
	printf("\n Description: Adds a soecufuc card ti a players hand, deck, or trash. Checks for enough supply of the card then puts the card in the directed location");
	printf("\n---------------------------------------------------------------------------------------------------\n");
	memset(&gState,23,sizeof(struct gameState));
	initializeGame(2, k, seed, &gState);
	
	gState.supplyCount[gold] = 0;
	printf("\nCheck Gold supply pile is empty. \n");
	resultFromGainCard = gainCard(gold,&gState,0,0);
	resultFromCheck = checkResult(resultFromGainCard, -1); 
	if(resultFromCheck == 1)
		failTotal++;
	gState.supplyCount[gold] = 30;
	
	printf("\nCheck add card to deck\n");
	int deck = gState.deckCount[0];
	gainCard(gold,&gState,1,0);
	resultFromCheck = checkResult(gState.deckCount[0],deck+1);
	if(resultFromCheck == 1)
		failTotal++;
	
	printf("\nCheck add card to hand\n");
	int hand = gState.handCount[0];
	gainCard(gold,&gState,2,0);
	resultFromCheck = checkResult(gState.handCount[0],hand+1);
	if(resultFromCheck == 1)
		failTotal++;
	
	printf("\nCheck add card to discard\n");
	int discard = gState.discardCount[0];
	gainCard(gold,&gState,0,0);
	resultFromCheck = checkResult(gState.discardCount[0],discard+1);
	if(resultFromCheck == 1)
		failTotal++;
	
	printf("\nCheck decrease gold supply\n");
	int goldSupply = gState.supplyCount[gold];
	gainCard(gold,&gState,0,0);
	resultFromCheck = checkResult(goldSupply -1, gState.supplyCount[gold]);
	if(resultFromCheck == 1)
		failTotal++;
	
	if(failTotal!=0){
		printf("\nTEST FAILED, the number fails: %d\n",failTotal);
	}else{
		printf("\nTEST SUCCESSFULLY\n");
	}
	printf("\n---------------------------------End Testing gainCard()----------------------------------\n");
	return 0;
}