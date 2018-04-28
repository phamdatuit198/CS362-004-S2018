/*
	Author: Dat Pham
	Class: CS362
	Term: Spring 2018
*/
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"


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
	int resultFromCheck = 0;
	int seed = 1000;
	int bonus = 0;
	int numplayer = 2;
	int player1=0;
	int player2=1;
	int handpos =0;
	int firstChoice=0;
	int secondChoice =0;
	int thirdChoice =0;
	
	
	
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	struct gameState gState;
	struct gameState tempState;
	printf("\n------------------------------------TESTING council_roomCard of Card------------------------------\n");
	
	memset(&gState,23,sizeof(struct gameState));
    memset(&tempState,23,sizeof(struct gameState));
	
	// create a state
    initializeGame(numplayer, k, seed, &gState);
	
	//save state
	memcpy(&tempState, &gState, sizeof(struct gameState));
	cardEffect(council_room, firstChoice, secondChoice, thirdChoice, &gState, handpos, &bonus);
	
	printf("\nTest player gains 4 cards: ");
	resultFromCheck = checkResult(gState.handCount[player1],tempState.handCount[player1]+3);
	if(resultFromCheck == 1)
		failTotal++;
	
	printf("\nTest player gains 4 cards from deck: ");
	resultFromCheck = checkResult(gState.deckCount[player1],tempState.deckCount[player1]-4);
	if(resultFromCheck == 1)
		failTotal++;
	
	printf("\nTest add one to number of buys: ");
	resultFromCheck = checkResult(gState.numBuys,tempState.numBuys+1);
	if(resultFromCheck == 1)
		failTotal++;
	
	printf("\n---Check data of another player wasn't affected---\n");
	printf("Deck card don't change: ");
	resultFromCheck = checkResult(gState.deckCount[player2],tempState.deckCount[player2]-1);
	if(resultFromCheck == 1)
		failTotal++;
	
	printf("Hand card don't change: ");
	resultFromCheck = checkResult(gState.handCount[player2],tempState.handCount[player2]+1);
	if(resultFromCheck == 1)
		failTotal++;
	
	printf("\n---Check another type cards don't change---\n");
	printf("The number curse cards don't change: ");
	resultFromCheck = checkResult(gState.supplyCount[curse],tempState.supplyCount[curse]);
	if(resultFromCheck == 1)
		failTotal++;
	printf("The number estate victory cards don't change: ");
	resultFromCheck = checkResult(gState.supplyCount[estate],tempState.supplyCount[estate]);
	if(resultFromCheck == 1)
		failTotal++;
	printf("The number duchy victory cards don't change: ");
	resultFromCheck = checkResult(gState.supplyCount[duchy],tempState.supplyCount[duchy]);
	if(resultFromCheck == 1)
		failTotal++;
	printf("The number province victory cards don't change: ");
	resultFromCheck = checkResult(gState.supplyCount[province],tempState.supplyCount[province]);
	if(resultFromCheck == 1)
		failTotal++;
	
	if(failTotal!=0){
		printf("\nTEST FAILED, the number fails: %d\n",failTotal);
	}else{
		printf("\nTEST SUCCESSFULLY\n");
	}
	
	printf("\n---------------------------------End Testing council_roomCard of Card----------------------------------\n");
	
	return 0;
}