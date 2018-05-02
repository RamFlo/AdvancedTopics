#include <string>
#include "mainAux.h"
#include "GameBoard.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

/*
*  This is the main game's function. it reads both positioning files and positions the pieces on the board.
*  Then, if there is no winner after the positioning, it reads both moves files and executes the game.
*  Finally, it creates the output file according to the game's results.
*/
int main() {
	GameBoard board;
	board.reason = "";
	if (!doPiecePositioning(&board, "player1.rps_board", 1) || !doPiecePositioning(&board, "player2.rps_board", 2)) {
		cout << "Could not open a positioning file" << endl;
		return 0;
	}
	if (board.reason != "") {
		createOutputFile(&board);
		return 0;
	}
	mergeBoardsToFinalBoard(&board);
	if (board.pieceCountMap["player1Flags"] == 0 && board.pieceCountMap["player2Flags"] == 0) {
		board.reason = "A tie - all flags are eaten by both players in the position files";
		board.winner = 0;
		createOutputFile(&board);
		return 0;
	}

	if (!executeMoves(&board)) {
		cout << "Could not open a moves file" << endl;
		return 0;
	}
	createOutputFile(&board);
	return 0;
}