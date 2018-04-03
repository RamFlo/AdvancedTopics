#include <string>
#include "mainAux.h"
#include "GameBoard.h"


int main() {
	int i = 0, j = 0;
	GameBoard board;
	board.reason = "";
	char startingString[M];
	
	board.player1Board = new string[N];
	board.player2Board = new string[N];
	board.finalBoard = new string[N];
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++)
			board.player1Board[i][j] = '_';
	}
	return 0;
}