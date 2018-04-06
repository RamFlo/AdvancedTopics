#include "mainAux.h"
#include "GameBoard.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
//M is x, which represents the cols. N is Y, which represents the rows.



/*
*
*
*
*
POSITIONING
*
*
*
*
*/

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

bool isLegalJokerTypeChar(char c) {
	switch (c)
	{
	case 'R':
	case 'P':
	case 'S':
	case 'B':
		return true;
		break;
	}
	return false;
}

bool updatePieceCount(GameBoard* board,int player,char piece, int incOrDec) {
	if (player == 1) {
		switch (piece)
		{
		case 'J':
			board->player1Jokers+= incOrDec;
			return (board->player1Jokers <= NUM_OF_J);
			break;
		case 'R':
			board->player1Rocks += incOrDec;
			return (board->player1Rocks <= NUM_OF_R);
			break;
		case 'P':
			board->player1Papers += incOrDec;
			return (board->player1Papers <= NUM_OF_P);
			break;
		case 'S':
			board->player1Scissors += incOrDec;
			return (board->player1Scissors <= NUM_OF_S);
			break;
		case 'B':
			board->player1Bombs += incOrDec;
			return (board->player1Bombs <= NUM_OF_B);
			break;
		case 'F':
			board->player1Flags += incOrDec;
			return (board->player1Flags <= NUM_OF_F);
			break;
		}
	}
	else {
		switch (piece)
		{
		case 'J':
			board->player2Jokers += incOrDec;
			return (board->player2Jokers <= NUM_OF_J);
			break;
		case 'R':
			board->player2Rocks += incOrDec;
			return (board->player2Rocks <= NUM_OF_R);
			break;
		case 'P':
			board->player2Papers += incOrDec;
			return (board->player2Papers <= NUM_OF_P);
			break;
		case 'S':
			board->player2Scissors += incOrDec;
			return (board->player2Scissors <= NUM_OF_S);
			break;
		case 'B':
			board->player2Bombs += incOrDec;
			return (board->player2Bombs <= NUM_OF_B);
			break;
		case 'F':
			board->player2Flags += incOrDec;
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
		return board->player1Board[row][col] == NULL;
	return board->player2Board[row][col] == NULL;
}

void putPieceOnPlayerBoard(GameBoard* board, int player, int row, int col,GamePiece* piece) {
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
	istringstream iss;
	if (fin.fail())
		return false;
	getline(fin, curLine);
	while (!fin.eof()) {
		if (fin.bad()) {
			fin.close();
			return false;
		}
		iss.str(curLine);
		iss.clear();
		if (getline(iss, token, ' ')) {
			if (token.length() != 1) { //if piece char is not sized correctly
				cout << "Bad format: input size inconsistent with given instructions on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				fin.close();
				return true;
			}
			if (!isLegalPieceChar(token[0])) { // if piece char is sized correctly but not legal
				cout << "Bad format: illegal piece character in line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				fin.close();
				return true;
			}
		}
		else { 
			cout << "Bad format: position is too short on line " << curLineNum << endl;
			handlePositioningError(board, player, curLineNum);
			fin.close();
			return true;
		}
		curPiece = new GamePiece(token[0], token[0],player);
		if (getline(iss, token, ' ')) {
			if (token.length() != 1) {
				cout << "Bad format: input size inconsistent with given instructions on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				delete curPiece;
				fin.close();
				return true;
			}
			if (!isLegalBoardCol(token[0])) {
				cout << "Bad format: illegal index on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				delete curPiece;
				fin.close();
				return true;
			}
			curCol = token[0] - '0';
		}
		else {
			cout << "Bad format: position is too short on line " << curLineNum << endl;
			handlePositioningError(board, player, curLineNum);
			fin.close();
			return true;
		}
		if (getline(iss, token, ' ')) {
			if (token.length() != 1) {
				cout << "Bad format: input size inconsistent with given instructions on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				delete curPiece;
				fin.close();
				return true;
			}
			if (!isLegalBoardRow(token[0])) {
				cout << "Bad format: illegal index on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				delete curPiece;
				fin.close();
				return true;
			}
			curRow = token[0] - '0';
		}
		else {
			cout << "Bad format: position is too short on line " << curLineNum << endl;
			handlePositioningError(board, player, curLineNum);
			delete curPiece;
			fin.close();
			return true;
		}
		if (curPiece->curPieceType != 'J') {
			if (getline(iss, token, ' ')) { //if there are more letters after position (and piece is not joker)
				if (curPiece)
					cout << "Bad format: position is too long on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				delete curPiece;
				fin.close();
				return true;
			}
		}
		else { //curPiece is joker
			if (getline(iss, token, ' ')) {
				if (token.length() != 1) { //if piece char is not sized correctly
					cout << "Bad format: input size inconsistent with given instructions on line " << curLineNum << endl;
					handlePositioningError(board, player, curLineNum);
					delete curPiece;
					fin.close();
					return true;
				}
				if (!isLegalJokerTypeChar(token[0])) { // if piece char is sized correctly but not legal
					cout << "Bad format: illegal piece character for Joker type in line " << curLineNum << endl;
					handlePositioningError(board, player, curLineNum);
					delete curPiece;
					fin.close();
					return true;
				}
			}
			else {
				cout << "Bad format: position is too short on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				delete curPiece;
				fin.close();
				return true;
			}
			curPiece->curPieceType = token[0];
		}
		if (!isSquareEmpty(board,player, curRow-1, curCol-1)) {
			cout << "Bad format: square is not empty for piece on line " << curLineNum << endl;
			handlePositioningError(board, player, curLineNum);
			delete curPiece;
			fin.close();
			return true;
		}
		putPieceOnPlayerBoard(board, player, curRow-1, curCol-1, curPiece);
		if (!updatePieceCount(board, player, curPiece->pieceType, 1)) {
			cout << "Bad format: too many instances of " << curPiece->pieceType << " on line " << curLineNum << endl;
			handlePositioningError(board, player, curLineNum);
			delete curPiece;
			fin.close();
			return true;
		}
		getline(fin, curLine);
		curLineNum++;
	}
	if (!isEnoughFlags(board, player)) {
		cout << "Bad format: missing flags - flags are not positioned according to their number " << endl;
		handlePositioningError(board, player, curLineNum);
		delete curPiece;
		fin.close();
		return true;
	}
	fin.close();
	return true;
}

void decrementCountOfPiece(GameBoard* board, GamePiece* piece, int player) {

}

GamePiece* fight(GameBoard* board, GamePiece* p1, GamePiece* p2) { //given two pieces determines which piece wins
	if (p1 == NULL)
		return p2;
	if (p2 == NULL)
		return p1;
	if (p1->curPieceType == 'B' || p2->curPieceType == 'B' || (p1->curPieceType == p2->curPieceType)) {
		updatePieceCount(board, p1->player, p1->pieceType, -1);
		updatePieceCount(board, p2->player, p2->pieceType, -1);
		return NULL;
	}
	if (p1->curPieceType == 'F') {
		updatePieceCount(board, p1->player, p1->pieceType, -1);
		return p2;
	}
	if (p2->curPieceType == 'F') {
		updatePieceCount(board, p2->player, p2->pieceType, -1);
		return p1;
	}
	else if (p1->curPieceType == 'S') {
		if (p2->curPieceType == 'R') {
			updatePieceCount(board, p1->player, p1->pieceType, -1);
			return p2;
		}	
		else if (p2->curPieceType == 'P') {
			updatePieceCount(board, p2->player, p2->pieceType, -1);
			return p1;
		}
	}
	else if (p2->curPieceType == 'S') {
		if (p1->curPieceType == 'R') {
			updatePieceCount(board, p2->player, p2->pieceType, -1);
			return p1;
		}
		else if (p1->curPieceType == 'P') {
			updatePieceCount(board, p1->player, p1->pieceType, -1);
			return p2;
		}
	}
	else if (p1->curPieceType == 'R') {
		updatePieceCount(board, p1->player, p1->pieceType, -1);
		return p2;
	}
	else if (p2->curPieceType == 'R') {
		updatePieceCount(board, p2->player, p2->pieceType, -1);
		return p1;
	}
		
}

void mergeBoardsToFinalBoard(GameBoard* board) {
	int i = 0, j = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			board->finalBoard[i][j] = fight(board, board->player1Board[i][j], board->player2Board[i][j]);
		}
	}
}


/*
*
*
*
*
GAME
*
*
*
*
*/

int getNumOfMovingPlayerPieces(GameBoard* board, int curPlayer) {
	int movingPieces = 0, i = 0, j = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			if (board->finalBoard[i][j] != NULL && board->finalBoard[i][j]->player == curPlayer) {
				if (board->finalBoard[i][j]->curPieceType == 'P' || board->finalBoard[i][j]->curPieceType == 'S' || board->finalBoard[i][j]->curPieceType == 'R')
					movingPieces++;
			}
		}
	}
	return movingPieces;
}

bool hasOtherPlayerWon(GameBoard* board, int curPlayer) {
	int movingPieces;
	if (getNumOfMovingPlayerPieces(board, curPlayer) == 0) {
		board->winner = getOtherPlayer(curPlayer);
		board->reason = "All moving PIECEs of the opponent are eaten";
		return true;
	}
	if (curPlayer == 1) {
		if (board->player1Flags == 0) {
			board->winner = 2;
			board->reason = "All flags of the opponent are captured";
			return true;
		}
	}
	if (curPlayer == 2) {
		if (board->player2Flags == 0) {
			board->winner = 1;
			board->reason = "All flags of the opponent are captured";
			return true;
		}
	}
	return false;
}

bool executePlayerMove(GameBoard* board, int player, string move) {

}



bool executeMoves(GameBoard* board) {
	bool player1FileEnded = false, player2FileEnded = false;
	string curPlayer1Line, curPlayer2Line;
	int curPlayer = 1, srcRow = 0, srcCol = 0, destRow = 0, destCol = 0;
	ifstream player1moves("player1.rps_moves");
	if (player1moves.fail())
		return false;
	ifstream player2moves("player2.rps_moves");
	if (player2moves.fail()) {
		player1moves.close();
		return false;
	}
	while (true) {
		if (hasOtherPlayerWon(board, 1)) {
			player1moves.close();
			player2moves.close();
			return true;
		}
		if (!player1FileEnded)
			getline(player1moves, curPlayer1Line);
		if (!player2FileEnded)
			getline(player2moves, curPlayer2Line);
		if (player1moves.eof())
			player1FileEnded = true;
		if (player2moves.eof())
			player2FileEnded = true;
		if (player1FileEnded && player2FileEnded) {
			board->winner = 0;
			board->reason = "A tie - both Moves input files done without a winner";
			player1moves.close();
			player2moves.close();
			return true;
		}
		if (!player1FileEnded)
			executePlayerMove(board, 1, curPlayer1Line);
		if (hasOtherPlayerWon(board, 2)) {
			player1moves.close();
			player2moves.close();
			return true;
		}
		if (!player2FileEnded)
			executePlayerMove(board, 2, curPlayer2Line);
	}




	/*getline(fin, curLine);
	while (!fin.eof()) {
		if (fin.bad()) {
			fin.close();
			return false;
		}
	}
	*/
}
