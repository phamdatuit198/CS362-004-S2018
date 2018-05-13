/*
	Author: Dat Pham
	CS 362
	Spring 2018
	Assignment 4
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>


int failCardEffect = 0;
int failShuffle =0;
int failDrawCard = 0;
int failDeckHand= 0;
int failTreasureCount=0;

void checkCard(struct gameState *state, int player){
	struct gameState tempState;
	int actions = 0;
	int handCount = 0;
	int stateCount = 0;
	int tempCount = 0;
	int hand[MAX_HAND];
	
	int card;
	int cardDrawn;

	int i=0;
	
	//save game state
	memcpy(&tempState,state,sizeof(struct gameState));
	int resultCheck = 0; 
	resultCheck = cardEffect(adventurer, 0,0,0,state,0,0);
	
	//check cardEffect 
	if(resultCheck)
		failCardEffect++;
	
	// get the state treasureCount
    for (i = 0; i < state->handCount[player]; i++) {
        card = state->hand[player][i];
        if (card == copper || card == silver || card == gold) {
            stateCount++;
        }
    }
    // get the temp treasureCount
    for (i = 0; i < tempState.handCount[player]; i++) {
        card = tempState.hand[player][i];
        if (card == copper || card == silver || card == gold) {
            tempCount++;
        }
    }
    // check if treasures match up
    if (stateCount != tempCount) {
      failTreasureCount++;
    }
	
	if(!(state->handCount[player] == tempState.handCount[player] 
		&& state->deckCount[player] == tempState.deckCount[player]
		&& state->discardCount[player] == tempState.discardCount[player]))
		failDeckHand++;
	
	while(actions < 2){
		
		handCount = tempState.handCount[player] - 1;
		cardDrawn = tempState.hand[player][handCount];
		if(cardDrawn != gold && cardDrawn != silver && cardDrawn != copper){
			hand[i] = cardDrawn;
			i++;
			tempState.handCount[player]--;
		
		}else{
			actions++;
		}
		
		resultCheck = drawCard(player,&tempState);
		if(tempState.deckCount[player]!=0 && resultCheck == -1)
			failDrawCard++;
		
		if(tempState.deckCount[player] < 1){
			resultCheck = shuffle(player,&tempState);
			if(resultCheck == -1 && tempState.deckCount[player] >= 1 )
				failShuffle++;
		}
	}
}

int main(){
	
	int numPlayer=0;
	struct gameState state;
	int totalFails = 0;
	int loop = 10000;
	int i=0;
	int n=0;
	int numberTreasures = 0;
	int treasuresCard[] = {copper, silver, gold};
	int length = sizeof(struct gameState);
	int minCardDeck = 3; 
	int tempRandomDeckCount = 0;
	int tempRandomHandCount = 0;
	int tempRandomTreasures = 0;
	printf("\n----------- RANDOM TEST ---------\n");
	printf("\nTestting RefactorAdventurerCard()");
	printf("\n-----------------------------------");
	srand(time(NULL));
	
	for(n =0; n< loop;n++){
		for(i=0;i<length;i++){
			((char*)&state)[i] = floor(Random() * 256);
		}
		
		numPlayer = floor(Random() * MAX_PLAYERS);
		state.discardCount[numPlayer] = 0;
		state.whoseTurn = numPlayer;
		
		tempRandomDeckCount = MAX_DECK - minCardDeck +1;
		state.deckCount[numPlayer] = floor(Random() * tempRandomDeckCount + minCardDeck);
		
		tempRandomHandCount = MAX_HAND - minCardDeck +1;
		state.handCount[numPlayer] = floor(Random() * tempRandomHandCount + minCardDeck);
		
		tempRandomTreasures = state.deckCount[numPlayer] - minCardDeck+1;
		numberTreasures = floor(Random() * tempRandomTreasures + minCardDeck);
		//numberTreasures = floor(Random() * ((state.deckCount[numPlayer] - minCardDeck)+1)+minCardDeck);
		
		for(i = 0; i< numberTreasures; i++)
			state.deck[numPlayer][i] = treasuresCard[rand() %3];
	
		
		checkCard(&state,numPlayer);
	
	}

		
	totalFails = failCardEffect + failShuffle + failDeckHand + failTreasureCount;
	printf("\n\n----------RESULT-----------------");
	printf("\n Total FAILED TEST: %d",totalFails);
	printf("\nThe amount failed failed shuffle(): %d",failShuffle);
	printf("\nThe amount failed failed drawCard(): %d",failDrawCard);
	printf("\nThe amount failed failed cardEffect(): %d",failCardEffect);
	printf("\nTreasure count doesn't match: %d",failTreasureCount);
	printf("\nCount hand and desk don't match: %d\n",failDeckHand);
	
	return 0;
}