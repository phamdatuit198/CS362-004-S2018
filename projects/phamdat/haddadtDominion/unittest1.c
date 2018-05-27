/*
	Author: Dat Pham
	Class: CS362
	Term: Spring 2018
	Description: write unittest for function buyCard Validates the card being played can be played then calls cardEffect to play the card
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
	int resultFromGameOver = 0;
	int resultFromCheck = 0;
	int failTotal = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
			   
	printf("\n------------------------------------TESTING isGameOver()------------------------------\n");
	printf("\n Description: Validates the card being played can be played then calls cardEffect to play the card");
	printf("\n---------------------------------------------------------------------------------------------------\n");
	memset(&gState,23,sizeof(struct gameState));
	initializeGame(2, k, seed, &gState);
	
	printf("\nTesting if stack of Province cards is empty, the game ends\n");
	gState.supplyCount[province] = 0;
	resultFromGameOver = isGameOver(&gState);
	resultFromCheck = checkResult(resultFromGameOver,1);
	if(resultFromCheck == 1)
			failTotal++;
		
	printf("\nTesting if three supply pile are at 0, the game ends\n");
	gState.supplyCount[province] = 1;
	gState.supplyCount[0] = 0;
	gState.supplyCount[1] = 0;
	gState.supplyCount[2] = 0;
	resultFromGameOver = isGameOver(&gState);
	resultFromCheck = checkResult(resultFromGameOver,1);
	if(resultFromCheck == 1)
			failTotal++;
	
	printf("\nTesting if three supply pile are not 0\n");
	gState.supplyCount[province] = 1;
	gState.supplyCount[0] = 1;
	gState.supplyCount[1] = 1;
	gState.supplyCount[2] = 1;
	resultFromGameOver = isGameOver(&gState);
	resultFromCheck = checkResult(resultFromGameOver,0);
	if(resultFromCheck == 1)
			failTotal++;
	
	return 0;
}