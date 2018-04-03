#include "mainAux.h"
#include "GameBoard.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
//M is x, which represents the cols. N is Y, which represents the rows.


bool countPieces(string fileName) {

}

bool isLegalPieceChar(char c) {
	switch (c)
	{
	case 'J':
	case 'R':
	case 'P':
	case 'S':
	case 'B':
	case 'F':
		return true;
		break;
	}
	return false;
}

int getOtherPlayer(int player) {
	if (player == 1)
		return 2;
	return 1;
}

void updateWinnerAndReasonOnBadPositioning(GameBoard* board, int errorLineNum, int player) {
	
	if (board->winner == 0) {
		board->winner = getOtherPlayer(player);
		board->reason = "Bad Positioning input file for player " + to_string(player) + " - line " + to_string(errorLineNum);
	}
	else {
		board->winner = 0;
		board->reason = "Bad Positioning input file for both players - player 1: line " + to_string(board->errorLinePlayer1) + ", player 2: line " + to_string(board->errorLinePlayer2);
	}
}

void handleIncorrectTokenSize(GameBoard* board,int player,int errorLine) {
	cout << "Bad format: input size inconsistent with given instructions on line " << errorLine << endl;
	updateErrorLine(board, player, errorLine);
	updateWinnerAndReasonOnBadPositioning(board, errorLine, player);
}

void updateErrorLine(GameBoard* board, int player, int errorLine) {
	if (player == 1)
		board->errorLinePlayer1 = errorLine;
	else
		board->errorLinePlayer2 = errorLine;
		
}

bool doPiecePositioning(GameBoard* board, string fileName, int player) {
	string curLine,token;
	char curPiece;
	int curLineNum = 1;
	ifstream fin(fileName);
	if (fin.fail())
		return false;
	getline(fin, curLine);
	while (!fin.eof()) {
		if (fin.bad())
			return false;


		istringstream iss(curLine);
		getline(iss, token, ' ');
		if (token.length() != 1) {
			handleIncorrectTokenSize(board, player, curLineNum);
			return true;
		}
		if (!isLegalPieceChar(token[0])) {
			cout << "Bad format: illegal piece character in line " << curLineNum << endl;
			updateErrorLine(board, player, curLineNum);
			updateWinnerAndReasonOnBadPositioning(board, curLineNum, player);
			return true;
		}
		curPiece = token[0];
		getline(iss, token, ' ');
		if (token.length() != 1) {
			handleIncorrectTokenSize(board, player, curLineNum);
			return true;
		}




		getline(fin, curLine);
		curLineNum++;
	}
}