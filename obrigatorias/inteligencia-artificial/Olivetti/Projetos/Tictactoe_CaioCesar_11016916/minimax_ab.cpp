
/****************************************************************
 * minimax_ab.cpp
 * Purpose: Tic-tac-toe agent using Minimax Alpha-Beta Pruning
 * Author:	Caio Cesar Ramalho Follador
 * RA: 11016916
 * Date: 	nov 16, 2018
 ****************************************************************/

#include "mm.h"

int main(){
	No state;
	int player = 2;
	while(player != 0 and player != 1) {
		printf("Who first? AI = 0, You = 1\n");
		scanf("%d", &player);
	}

	int symbol[2] = {1, -1}; //IA, player

	printTable(state);
	while(!ehTerminal(state)) {
		if(!player) {
    		state = iaTurn(state, symbol[player]);
    	} else {
    		state = playerTurn(state, symbol[player]);
    	}
    	printTable(state);
   		player = (1 - player);
	}

	printWinner(state);

	return 0;
}
