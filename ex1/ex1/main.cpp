#include <string>
#include "mainAux.h"
#include "GameBoard.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;


int main() {
	int i = 0;
	GameBoard board;
	board.reason = "";
	char startingString[M+1];
	for (i = 0; i < M; i++)
		startingString[i] = '_';
	startingString[M] = '\0';
	board.player1Board = new string[N];
	board.player2Board = new string[N];
	board.finalBoard = new string[N];
	for (i = 0; i < N; i++) {
		board.player1Board[i] = startingString;
		board.player2Board[i] = startingString;
		board.finalBoard[i] = startingString;
	}
	if (!doPiecePositioning(&board, "player1.rps_board", 1) || !doPiecePositioning(&board, "player2.rps_board", 2)) {
		cout << "Could not open a positioning file" << endl;
		return 0;
	}
	ofstream fout("rps.output");
	if (fout.fail()) {
		cout << "Could not create output file" << endl;
		return 0;
	}
	if (board.reason != "") {
		fout << "Winner: " << board.winner << endl;
		fout << "Reason: " << board.reason << endl;
	}
	
}