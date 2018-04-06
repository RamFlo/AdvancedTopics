#include <string>
#include "mainAux.h"
#include "GameBoard.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;


int main() {
	int i = 0, curPlayer = 1;
	GameBoard board;
	board.reason = "";
	if (!doPiecePositioning(&board, "player1.rps_board", 1) || !doPiecePositioning(&board, "player2.rps_board", 2)) {
		cout << "Could not open a positioning file" << endl;
		return 0;
	}
	mergeBoardsToFinalBoard(&board);
	if (board.player1Flags == 0 && board.player2Flags == 0) {
		board.reason = "A tie - all flags are eaten by both players in position files";
		board.winner = 0;
	}
	ofstream fout("rps.output");
	if (fout.fail()) {
		cout << "Could not create output file" << endl;
		return 0;
	}
	if (board.reason != "") {
		fout << "Winner: " << board.winner << endl;
		fout << "Reason: " << board.reason << endl;
		return 0;
	}
	/*
	while (true) {
		doTurn(GameBoard* board, int curPlayer, string )

	}
	*/
	

	
}