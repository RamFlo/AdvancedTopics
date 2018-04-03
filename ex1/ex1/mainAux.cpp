#include "mainAux.h"
#include "GameBoard.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
//M is x, which represents the cols. N is Y, which represents the rows.

bool isLegalBoardCol(char colIndex) {
	return isdigit(colIndex) && (colIndex - '0') > 0 && (colIndex - '0') < M;
}

bool isLegalBoardRow(char rowIndex) {
	return isdigit(rowIndex) && (rowIndex - '0') > 0 && (rowIndex - '0') < N;
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

bool updatePieceCount(GameBoard* board,int player,char piece) {
	if (player == 1) {
		switch (piece)
		{
		case 'J':
			board->player1Jokers++;
			return (board->player1Jokers <= NUM_OF_J);
			break;
		case 'R':
			board->player1Rocks++;
			return (board->player1Rocks <= NUM_OF_R);
			break;
		case 'P':
			board->player1Papers++;
			return (board->player1Papers <= NUM_OF_P);
			break;
		case 'S':
			board->player1Scissors++;
			return (board->player1Scissors <= NUM_OF_S);
			break;
		case 'B':
			board->player1Bombs++;
			return (board->player1Bombs <= NUM_OF_B);
			break;
		case 'F':
			board->player1Flags++;
			return (board->player1Flags <= NUM_OF_F);
			break;
		}
	}
	else {
		switch (piece)
		{
		case 'J':
			board->player2Jokers++;
			return (board->player2Jokers <= NUM_OF_J);
			break;
		case 'R':
			board->player2Rocks++;
			return (board->player2Rocks <= NUM_OF_R);
			break;
		case 'P':
			board->player2Papers++;
			return (board->player2Papers <= NUM_OF_P);
			break;
		case 'S':
			board->player2Scissors++;
			return (board->player2Scissors <= NUM_OF_S);
			break;
		case 'B':
			board->player2Bombs++;
			return (board->player2Bombs <= NUM_OF_B);
			break;
		case 'F':
			board->player2Flags++;
			return (board->player2Flags <= NUM_OF_F);
			break;
		}
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


void updateErrorLine(GameBoard* board, int player, int errorLine) {
	if (player == 1)
		board->errorLinePlayer1 = errorLine;
	else
		board->errorLinePlayer2 = errorLine;
		
}

void handlePositioningError(GameBoard* board, int player, int errorLine) {
	updateErrorLine(board, player, errorLine);
	updateWinnerAndReasonOnBadPositioning(board, errorLine, player);
}

bool isSquareEmpty(GameBoard* board, int player, int row, int col) {
	if (player == 1)
		return board->player1Board[row][col] == '_';
	return board->player2Board[row][col] == '_';
}

void putPieceOnPlayerBoard(GameBoard* board, int player, int row, int col,char piece) {
	if (player == 1)
		board->player1Board[row][col] = piece;
	else
		board->player2Board[row][col] = piece;
}

bool isEnoughFlags(GameBoard* board, int player) {
	if (player == 1)
		return board->player1Flags == NUM_OF_F;
	return board->player2Flags == NUM_OF_F;
}

bool doPiecePositioning(GameBoard* board, string fileName, int player) {
	string curLine,token;
	GamePiece* curPiece = NULL;
	int curLineNum = 1,curCol=0,curRow=0;
	ifstream fin(fileName);
	if (fin.fail())
		return false;
	getline(fin, curLine);
	while (!fin.eof()) {
		if (fin.bad())
			return false;
		istringstream iss(curLine);
		if (getline(iss, token, ' ')) {
			if (token.length() != 1) {
				cout << "Bad format: input size inconsistent with given instructions on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				return true;
			}
			if (!isLegalPieceChar(token[0])) {
				cout << "Bad format: illegal piece character in line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				return true;
			}
		}
		else {
			cout << "Bad format: position is too short on line " << curLineNum << endl;
			handlePositioningError(board, player, curLineNum);
			return true;
		}
		curPiece = new GamePiece(token[0], token[0]);
		if (getline(iss, token, ' ')) {
			if (token.length() != 1) {
				cout << "Bad format: input size inconsistent with given instructions on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				delete curPiece;
				return true;
			}
			if (!isLegalBoardCol(token[0])) {
				cout << "Bad format: illegal index on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				delete curPiece;
				return true;
			}
			curCol = token[0] - '0';
		}
		else {
			cout << "Bad format: position is too short on line " << curLineNum << endl;
			handlePositioningError(board, player, curLineNum);
			return true;
		}
		if (getline(iss, token, ' ')) {
			if (token.length() != 1) {
				cout << "Bad format: input size inconsistent with given instructions on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				delete curPiece;
				return true;
			}
			if (!isLegalBoardRow(token[0])) {
				cout << "Bad format: illegal index on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				delete curPiece;
				return true;
			}
			curRow = token[0] - '0';
		}
		else {
			cout << "Bad format: position is too short on line " << curLineNum << endl;
			handlePositioningError(board, player, curLineNum);
			delete curPiece;
			return true;
		}
		if (getline(iss, token, ' ')) {
			if (curPiece)
			cout << "Bad format: position is too long on line " << curLineNum << endl;
			handlePositioningError(board, player, curLineNum);
			delete curPiece;
			return true;
		}

		if (!isSquareEmpty(board,player, curRow-1, curCol-1)) {
			cout << "Bad format: square is not empty for piece on line " << curLineNum << endl;
			handlePositioningError(board, player, curLineNum);
			delete curPiece;
			return true;
		}

		putPieceOnPlayerBoard(board, player, curRow-1, curCol-1, curPiece);
		if (!updatePieceCount(board, player, curPiece)) {
			cout << "Bad format: too many instances of " << curPiece << " on line " << curLineNum << endl;
			handlePositioningError(board, player, curLineNum);
			delete curPiece;
			return true;
		}
		getline(fin, curLine);
		curLineNum++;
	}
	if (!isEnoughFlags(board, player)) {
		cout << "Bad format: missing flags - flags are not positioned according to their number " << endl;
		handlePositioningError(board, player, curLineNum);
		delete curPiece;
		return true;
	}
	return true;
}

void fight(GameBoard* board, int i, int j) {
	
}

void mergeBoardsToFinalBoard(GameBoard* board) {
	int i = 0, j = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			fight(board,i,j);
		}
	}
}