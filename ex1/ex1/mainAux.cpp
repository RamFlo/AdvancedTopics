#include "mainAux.h"
#include "GameBoard.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
//M is x, which represents the cols. N is Y, which represents the rows.


void createOutputFile(GameBoard* board) {
	char curLetter = '\0';
	ofstream fout;
	int i = 0, j = 0;
	fout.open("rps.output");
	if (fout.fail())
		cout << "Could not create output file" << endl;
	else {
		fout << "Winner: " << board->winner << endl;
		fout << "Reason: " << board->reason << endl;
		fout << endl;

		for (i = 0; i < N; i++) {
			for (j = 0; j < M; j++) {
				if (board->finalBoard[i][j] != NULL) {
					if (board->finalBoard[i][j]->player == 1)
						curLetter = board->finalBoard[i][j]->pieceType;
					else
						curLetter = tolower(board->finalBoard[i][j]->pieceType);
					fout << curLetter;
				}
				else
					fout << " ";
			}
			fout << endl;
		}
		fout.close();
	}
}

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

bool isLegalNonNegativeNumber(string numString) {
	int i = 0,strSize= numString.length();
	for (i = 0; i < strSize; i++) {
		if (!isdigit(numString[i]))
			return false;
	}
	return true;
}

bool isLegalBoardCol(string colIndex) {
	return isLegalNonNegativeNumber(colIndex) && stoi(colIndex) > 0 && stoi(colIndex) <= M;
}

bool isLegalBoardRow(string rowIndex) {
	return isLegalNonNegativeNumber(rowIndex) && stoi(rowIndex) > 0 && stoi(rowIndex) <= N;
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
	int curLineNum = 0,curCol=0,curRow=0;
	ifstream fin(fileName);
	istringstream iss;
	if (fin.fail())
		return false;
	//getline(fin, curLine);
	//while (!fin.eof()) {
	while (getline(fin, curLine)) {
		if (fin.bad()) {
			fin.close();
			return false;
		}
		curLineNum++;
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
			if (!isLegalBoardCol(token)) {
				cout << "Bad format: illegal index on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				delete curPiece;
				fin.close();
				return true;
			}
			curCol = stoi(token);
		}
		else {
			cout << "Bad format: position is too short on line " << curLineNum << endl;
			handlePositioningError(board, player, curLineNum);
			fin.close();
			return true;
		}
		if (getline(iss, token, ' ')) {
			if (!isLegalBoardRow(token)) {
				cout << "Bad format: illegal index on line " << curLineNum << endl;
				handlePositioningError(board, player, curLineNum);
				delete curPiece;
				fin.close();
				return true;
			}
			curRow = stoi(token);
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
			//delete curPiece;
			fin.close();
			return true;
		}
		//getline(fin, curLine);
		//curLineNum++;
	}
	if (!isEnoughFlags(board, player)) {
		cout << "Bad format: missing flags - flags are not positioned according to their number " << endl;
		handlePositioningError(board, player, curLineNum);
		//delete curPiece;
		fin.close();
		return true;
	}
	fin.close();
	return true;
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
	return NULL;
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

void updateWinnerAndReasonOnBadMoveFile(GameBoard* board, int errorLineNum, int player) {
	board->winner = getOtherPlayer(player);
	board->reason = "Bad Moves input file for player " + to_string(player) + " - line " + to_string(errorLineNum);
}

void handleMovingFileError(GameBoard* board, int player, int errorLine) {
	updateErrorLine(board, player, errorLine);
	updateWinnerAndReasonOnBadMoveFile(board, errorLine, player);
}

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

//col, row 1-indexed
bool isLegalPieceInSourceSquare(GameBoard* board, int curPlayer, int col, int row) {
	if (board->finalBoard[row - 1][col - 1] == NULL || board->finalBoard[row - 1][col - 1]->player != curPlayer)
		return false;
	if (board->finalBoard[row - 1][col - 1]->curPieceType != 'S' && board->finalBoard[row - 1][col - 1]->curPieceType != 'R' && board->finalBoard[row - 1][col - 1]->curPieceType != 'P')
		return false;
	return true;
}

//col, row 1-indexed
bool isLegalMoveFromSourceSquare(GameBoard* board, int curPlayer, int srcCol, int srcRow, int destCol, int destRow) {
	if ((abs(srcCol - destCol) + abs(srcRow - destRow)) != 1)
		return false;
	if (board->finalBoard[destRow - 1][destCol - 1] == NULL || board->finalBoard[destRow - 1][destCol - 1]->player != curPlayer)
		return true;
	return false;
}

//true: move executed
//false: bad format
bool executePlayerMove(GameBoard* board, int player, string move, int curLineNum) {
	int srcCol = 0, srcRow = 0, destCol = 0, destRow = 0,i=0,jCol=0,jRow=0;
	char jokerNewType = '\0';
	string token;
	istringstream iss(move);
	for (i = 0; i < 4; i++) {
		if (getline(iss, token, ' ')) {
			if (((i == 1 || i == 3) && !isLegalBoardRow(token)) || ((i == 0 || i == 2) && !isLegalBoardCol(token))) {
				cout << "Bad format: illegal move index by player " << player << " on line " << curLineNum << endl;
				handleMovingFileError(board, player, curLineNum);
				iss.clear();
				return false;
			}
			if (i == 0)
				srcCol = stoi(token);
			if (i == 1)
				srcRow = stoi(token);
			if (i == 2)
				destCol = stoi(token);
			if (i == 3)
				destRow = stoi(token);
		}
		else {
			cout << "Bad format: move command is too short by player " << player << " on line " << curLineNum << endl;
			handleMovingFileError(board, player, curLineNum);
			iss.clear();
			return false;
		}
	}
	if (getline(iss, token, ' ')) {
		if (token == "J:") {
			for (i = 0; i < 2; i++) {
				if (getline(iss, token, ' ')) {
					if ((i == 1 && !isLegalBoardRow(token)) || (i == 0 && !isLegalBoardCol(token))) {
						cout << "Bad format: illegal move index by player " << player << " on line " << curLineNum << endl;
						handleMovingFileError(board, player, curLineNum);
						iss.clear();
						return false;
					}
					if (i == 0)
						jCol = stoi(token);
					if (i == 1)
						jRow = stoi(token);
				}
				else {
					cout << "Bad format: move command is too short by player " << player << " on line " << curLineNum << endl;
					handleMovingFileError(board, player, curLineNum);
					iss.clear();
					return false;
				}
			}
			if (getline(iss, token, ' ')) {
				if (token.length() != 1) {
					cout << "Bad format: move input size by player " << player << " inconsistent with given instructions on line " << curLineNum << endl;
					handleMovingFileError(board, player, curLineNum);
					iss.clear();
					return false;
				}
				if (!isLegalJokerTypeChar(token[0])) {
					cout << "Bad format: illegal move command joker type by player " << player << " on line " << curLineNum << endl;
					handleMovingFileError(board, player, curLineNum);
					iss.clear();
					return false;
				}
				jokerNewType = token[0];
			}
			else {
				cout << "Bad format: move command is too short by player " << player << " on line " << curLineNum << endl;
				handleMovingFileError(board, player, curLineNum);
				iss.clear();
				return false;
			}
		}
		else {
			cout << "Bad format: bad character at move command player " << player << " on line " << curLineNum << endl;
			handleMovingFileError(board, player, curLineNum);
			iss.clear();
			return false;
		}
	}
	
	if (!isLegalPieceInSourceSquare(board, player, srcCol, srcRow)) {
		cout << "Bad format: illegal move command's source square chosen by player " << player << " on line " << curLineNum << endl;
		handleMovingFileError(board, player, curLineNum);
		iss.clear();
		return false;
	}
	if (!isLegalMoveFromSourceSquare(board, player, srcCol, srcRow, destCol, destRow)) {
		cout << "Bad format: illegal move command's destination square chosen by player " << player << " on line " << curLineNum << endl;
		handleMovingFileError(board, player, curLineNum);
		iss.clear();
		return false;
	}
	board->finalBoard[destRow - 1][destCol - 1] = fight(board,board->finalBoard[srcRow - 1][srcCol - 1], board->finalBoard[destRow - 1][destCol - 1]);
	board->finalBoard[srcRow - 1][srcCol - 1] = NULL;

	if (jokerNewType != '\0') {
		if ((board->finalBoard[jRow - 1][jCol - 1] != NULL) && (board->finalBoard[jRow - 1][jCol - 1]->pieceType == 'J')&&(board->finalBoard[jRow - 1][jCol - 1]->player = player))
			board->finalBoard[jRow - 1][jCol - 1]->curPieceType = jokerNewType;
		else {
			cout << "Bad format: illegal joker updating command specified by player " << player << " on line " << curLineNum << endl;
			handleMovingFileError(board, player, curLineNum);
			iss.clear();
			return false;
		}
	}
	return true;

}


//true: game ended
//false: bad input moves file/files
bool executeMoves(GameBoard* board) {
	bool player1FileEnded = false, player2FileEnded = false;
	string curPlayer1Line, curPlayer2Line;
	int curLinePlayer1Num=0, curLinePlayer2Num = 0;
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
		/*if (!player1FileEnded)
			getline(player1moves, curPlayer1Line);
		if (!player2FileEnded)
			getline(player2moves, curPlayer2Line);
		if (player1moves.eof() || curPlayer1Line == "")
			player1FileEnded = true;
		else
			curLinePlayer1Num++;
		if (player2moves.eof() || curPlayer2Line == "")
			player2FileEnded = true;
		else
			curLinePlayer2Num++;*/

		if (!player1FileEnded) {
			if(!getline(player1moves, curPlayer1Line) || curPlayer1Line == "")
				player1FileEnded = true;
			else
				curLinePlayer1Num++;
		}
		if (!player2FileEnded) {
			if (!getline(player2moves, curPlayer2Line) || curPlayer2Line == "")
				player2FileEnded = true;
			else
				curLinePlayer2Num++;
		}
		if (player1FileEnded && player2FileEnded) {
			board->winner = 0;
			board->reason = "A tie - both Moves input files done without a winner";
			player1moves.close();
			player2moves.close();
			return true;
		}
		if (!player1FileEnded) {
			if (!executePlayerMove(board, 1, curPlayer1Line, curLinePlayer1Num)) {
				player1moves.close();
				player2moves.close();
				return true;
			}
		}
		if (hasOtherPlayerWon(board, 2)) {
			player1moves.close();
			player2moves.close();
			return true;
		}
		if (!player2FileEnded) {
			if (!executePlayerMove(board, 2, curPlayer2Line, curLinePlayer2Num)) {
				player1moves.close();
				player2moves.close();
				return true;
			}
		}
	}
	return true;
}
