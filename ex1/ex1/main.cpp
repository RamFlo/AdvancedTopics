#include <string>
#include "mainAux.h"
#include "GameBoard.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;


int main() {
	//int i = 0, j = 0;
	//char curLetter = '\0';
	GameBoard board;
	//ofstream fout;
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
	if (board.player1Flags == 0 && board.player2Flags == 0) {
		board.reason = "A tie - all flags are eaten by both players in position files";
		board.winner = 0;
	}
	if (!executeMoves(&board)) {
		cout << "Could not open a moves file" << endl;
		return 0;
	}
	/*fout.open("rps.output");
	if (fout.fail()) {
		cout << "Could not create output file" << endl;
		return 0;
	}
	fout << "Winner: " << board.winner << endl;
	fout << "Reason: " << board.reason << endl;
	fout << endl;

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			if (board.finalBoard[i][j] != NULL) {
				if (board.finalBoard[i][j]->player == 1)
					curLetter = board.finalBoard[i][j]->pieceType;
				else
					curLetter = tolower(board.finalBoard[i][j]->pieceType);
				fout << curLetter;
			}
			else
				fout << " ";
		}
		fout << endl;
	}
	fout.close();*/
	createOutputFile(&board);
	return 0;
}