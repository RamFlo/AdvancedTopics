#include "mainAux.h"
#include "GameBoard.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
//M is x, which represents the cols. N is Y, which represents the rows.

//This function creates the output file, and adds the winner, reason and gameboard to it
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

void parseStringIntoVector(vector<string>* myVec, string str) {
	string buf; // Have a buffer string
	stringstream ss(str); // Insert the string into a stream
	while (ss >> buf)
		myVec->push_back(buf);
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

//This function checks if a string represents a non-negative integer
bool isLegalNonNegativeNumber(string numString) {
	int i = 0,strSize= numString.length();
	for (i = 0; i < strSize; i++) {
		if (!isdigit(numString[i]))
			return false;
	}
	return true;
}

//checks if a string represents a legal column index
bool isLegalBoardCol(string colIndex) {
	return isLegalNonNegativeNumber(colIndex) && stoi(colIndex) > 0 && stoi(colIndex) <= M;
}
//checks if a string represents a legal row index
bool isLegalBoardRow(string rowIndex) {
	return isLegalNonNegativeNumber(rowIndex) && stoi(rowIndex) > 0 && stoi(rowIndex) <= N;
}

//checks if a string represents a legal piece char
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

//checks if a string represents a legal joker curType char (board pieces the joker can become)
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

//After a piece is added to the board, increments or decrements (as needed) the number of instances of this piece, 
// for the player that added the piece
bool updatePieceCount(GameBoard* board,int player,char piece, int incOrDec) {
	if (player == 1) {
		switch (piece)
		{
		case 'J':
			board->pieceCountMap["player1Jokers"]+= incOrDec;
			return (board->pieceCountMap["player1Jokers"] <= NUM_OF_J);
			break;
		case 'R':
			board->pieceCountMap["player1Rocks"] += incOrDec;
			return (board->pieceCountMap["player1Rocks"] <= NUM_OF_R);
			break;
		case 'P':
			board->pieceCountMap["player1Papers"] += incOrDec;
			return (board->pieceCountMap["player1Papers"] <= NUM_OF_P);
			break;
		case 'S':
			board->pieceCountMap["player1Scissors"] += incOrDec;
			return (board->pieceCountMap["player1Scissors"] <= NUM_OF_S);
			break;
		case 'B':
			board->pieceCountMap["player1Bombs"] += incOrDec;
			return (board->pieceCountMap["player1Bombs"] <= NUM_OF_B);
			break;
		case 'F':
			board->pieceCountMap["player1Flags"] += incOrDec;
			return (board->pieceCountMap["player1Flags"] <= NUM_OF_F);
			break;
		}
	}
	else {
		switch (piece)
		{
		case 'J':
			board->pieceCountMap["player2Jokers"] += incOrDec;
			return (board->pieceCountMap["player2Jokers"] <= NUM_OF_J);
			break;
		case 'R':
			board->pieceCountMap["player2Rocks"] += incOrDec;
			return (board->pieceCountMap["player2Rocks"] <= NUM_OF_R);
			break;
		case 'P':
			board->pieceCountMap["player2Papers"] += incOrDec;
			return (board->pieceCountMap["player2Papers"] <= NUM_OF_P);
			break;
		case 'S':
			board->pieceCountMap["player2Scissors"] += incOrDec;
			return (board->pieceCountMap["player2Scissors"] <= NUM_OF_S);
			break;
		case 'B':
			board->pieceCountMap["player2Bombs"] += incOrDec;
			return (board->pieceCountMap["player2Bombs"] <= NUM_OF_B);
			break;
		case 'F':
			board->pieceCountMap["player2Flags"] += incOrDec;
			return (board->pieceCountMap["player2Flags"] <= NUM_OF_F);
			break;
		}
	}
	return false;
}

// Given a player, returns the other player
int getOtherPlayer(int player) {
	if (player == 1)
		return 2;
	return 1;
}

// When a positioning error is found, this function updates the Board's winner and reason variables
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

// When some player has an error, this function updates that player's error line (where the error occured)
void updateErrorLine(GameBoard* board, int player, int errorLine) {
	if (player == 1)
		board->errorLinePlayer1 = errorLine;
	else
		board->errorLinePlayer2 = errorLine;
		
}

// When we find a positioning error, this function updates the line where it occured, then updates the reason and winner
void handlePositioningError(GameBoard* board, int player, int errorLine) {
	updateErrorLine(board, player, errorLine);
	updateWinnerAndReasonOnBadPositioning(board, errorLine, player);
}

//checks if a certain square of a certain player's board is empty
bool isSquareEmpty(GameBoard* board, int player, int row, int col) {
	if (player == 1)
		return board->player1Board[row][col] == NULL;
	return board->player2Board[row][col] == NULL;
}

//puts a piece on a given player's board
void putPieceOnPlayerBoard(GameBoard* board, int player, int row, int col,GamePiece* piece) {
	if (player == 1)
		board->player1Board[row][col] = piece;
	else
		board->player2Board[row][col] = piece;
}

// checks if a given player has enough flags (as many as needed)
bool isEnoughFlags(GameBoard* board, int player) {
	if (player == 1)
		return board->pieceCountMap["player1Flags"] == NUM_OF_F;
	return board->pieceCountMap["player2Flags"] == NUM_OF_F;
}

bool checkPositioningCommandVectorIsValid(vector<string>* myVec, int curLineNum) {
	vector<string>& myCommandVec = *myVec;
	if (myCommandVec.size() > 4 || myCommandVec.size() < 3) {
		cout << "Bad format: input size inconsistent with given instructions on line " << curLineNum << endl;
		return false;
	}
	if (myCommandVec[0].length() != 1 || (myCommandVec.size() == 4 && myCommandVec[3].length() != 1)) {
		cout << "Bad format: input size inconsistent with given instructions on line " << curLineNum << endl;
		return false;
	}
	if (!isLegalPieceChar(myCommandVec[0][0])) {
		cout << "Bad format: illegal piece character in line " << curLineNum << endl;
		return false;
	}
	if (!isLegalBoardCol(myCommandVec[1]) || !isLegalBoardRow(myCommandVec[2])) {
		cout << "Bad format: illegal index on line " << curLineNum << endl;
		return false;
	}
	if (myCommandVec[0][0] == 'J') {
		if (myCommandVec.size() != 4) {
			cout << "Bad format: input size inconsistent with given instructions on line " << curLineNum << endl;
			return false;
		}
		if (!isLegalJokerTypeChar(myCommandVec[3][0])) {
			cout << "Bad format: illegal piece character for Joker type in line " << curLineNum << endl;
			return false;
		}
	}
	return true;
}


bool handlePositioningLine(GameBoard* board, vector<string>* myVec, int curLineNum, int player) {
	vector<string>& myCommandVec = *myVec;
	GamePiece* curPiece = NULL;
	
	if (!isSquareEmpty(board, player, stoi(myCommandVec[2]) - 1, stoi(myCommandVec[1]) - 1)) {
		cout << "Bad format: square is not empty for piece on line " << curLineNum << endl;
		return false;
	}
	curPiece = new GamePiece(myCommandVec[0][0], myCommandVec[0][0], player);
	if (myCommandVec.size() == 4)
		curPiece->curPieceType = myCommandVec[3][0];
	putPieceOnPlayerBoard(board, player, stoi(myCommandVec[2]) - 1, stoi(myCommandVec[1]) - 1, curPiece); //putting the piece on the player's board
	if (!updatePieceCount(board, player, curPiece->pieceType, 1)) { //checking there aren't too many instances of the current piece
		cout << "Bad format: too many instances of " << curPiece->pieceType << " on line " << curLineNum << endl;
		delete curPiece;
		return false;
	}
	return true;
}


//Given a player's positioning file, positions all of it's pieces on his board
bool doPiecePositioning(GameBoard* board, string fileName, int player) {
	string curLine,token;
	GamePiece* curPiece = NULL;
	vector<string> myWordVec;
	int curLineNum = 0,curCol=0,curRow=0;
	ifstream fin(fileName);
	istringstream iss;
	if (fin.fail()) //checking if we could open the file
		return false;
	while (getline(fin, curLine)) { //returns false when reaching EOF
		if (fin.bad()) {
			fin.close();
			return false;
		}
		myWordVec.clear();
		curLineNum++;
		parseStringIntoVector(&myWordVec, curLine);
		if (!checkPositioningCommandVectorIsValid(&myWordVec, curLineNum) || !handlePositioningLine(board,&myWordVec,curLineNum,player)) {
			handlePositioningError(board, player, curLineNum);
			fin.close();
			return true;
		}
	}
	if (!isEnoughFlags(board, player)) { //checking the player has enough flags (finished the while loop, positioning finished
		cout << "Bad format: missing flags - flags are not positioned according to their number " << endl;
		handlePositioningError(board, player, curLineNum);
		fin.close();
		return true;
	}
	fin.close();
	return true;
}

// Simulates a fight between 2 pieces - returns a pointer to the winner
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

//Merging both player's boards into one final board, including holding all needed fights between two pieces
//The final board holds a pointer to the winning piece of each fight
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

//When a player does a bad move, updates the winner (other player) and reason
void updateWinnerAndReasonOnBadMoveFile(GameBoard* board, int errorLineNum, int player) {
	board->winner = getOtherPlayer(player);
	board->reason = "Bad Moves input file for player " + to_string(player) + " - line " + to_string(errorLineNum);
}

// When we find a moving error, this function updates the line where it occured, then updates the reason and winner
void handleMovingFileError(GameBoard* board, int player, int errorLine) {
	updateErrorLine(board, player, errorLine);
	updateWinnerAndReasonOnBadMoveFile(board, errorLine, player);
}

//Counts the number of given player's pieces that are alive and able to move (such as rock, paper etc)
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

// given a player, checks if the other player has won:
//1 - checks if the given player has moves to make. 2 - checks if the player has flags left
bool hasOtherPlayerWon(GameBoard* board, int curPlayer) {
	if (getNumOfMovingPlayerPieces(board, curPlayer) == 0) {
		board->winner = getOtherPlayer(curPlayer);
		board->reason = "All moving PIECEs of the opponent are eaten";
		return true;
	}
	if (curPlayer == 1) {
		if (board->pieceCountMap["player1Flags"] == 0) {
			board->winner = 2;
			board->reason = "All flags of the opponent are captured";
			return true;
		}
	}
	if (curPlayer == 2) {
		if (board->pieceCountMap["player2Flags"] == 0) {
			board->winner = 1;
			board->reason = "All flags of the opponent are captured";
			return true;
		}
	}
	return false;
}

//checks if a given player can move the piece in the given square (it's his piece, and the piece is of a type that can move)
//col, row 1-indexed
bool isLegalPieceInSourceSquare(GameBoard* board, int curPlayer, int col, int row) {
	if (board->finalBoard[row - 1][col - 1] == NULL || board->finalBoard[row - 1][col - 1]->player != curPlayer)
		return false;
	if (board->finalBoard[row - 1][col - 1]->curPieceType != 'S' && board->finalBoard[row - 1][col - 1]->curPieceType != 'R' && board->finalBoard[row - 1][col - 1]->curPieceType != 'P')
		return false;
	return true;
}

//given a player, src square and dest square, checks if the move is legal assuming the src square is legal (contains a moveable piece)
//namely, checks if the dest square is only 1 square away (not diagonal), and is empty or contains opponent piece
//col, row 1-indexed
bool isLegalMoveFromSourceSquare(GameBoard* board, int curPlayer, int srcCol, int srcRow, int destCol, int destRow) {
	if ((abs(srcCol - destCol) + abs(srcRow - destRow)) != 1)
		return false;
	if (board->finalBoard[destRow - 1][destCol - 1] == NULL || board->finalBoard[destRow - 1][destCol - 1]->player != curPlayer)
		return true;
	return false;
}

bool isLegalMoveCommandVec(vector<string>* myVec, int curLineNum, int player) {
	vector<string> myCommandVec = *myVec;
	if (myCommandVec.size() != 4 && myCommandVec.size() != 8) {
		cout << "Bad format: move command length is inconsistent with instructions by player " << player << " on line " << curLineNum << endl;
		return false;
	}
	if (!isLegalBoardRow(myCommandVec[1]) || !isLegalBoardRow(myCommandVec[3]) || !isLegalBoardCol(myCommandVec[0]) || !isLegalBoardCol(myCommandVec[2])) {
		cout << "Bad format: illegal move index by player " << player << " on line " << curLineNum << endl;
		return false;
	}
	if (myCommandVec.size() == 8) {
		if (myCommandVec[4] != "J:") {
			cout << "Bad format: illegal move command by player " << player << " on line " << curLineNum << endl;
			return false;
		}
		if (!isLegalBoardRow(myCommandVec[6]) || !isLegalBoardCol(myCommandVec[5])) {
			cout << "Bad format: illegal move index by player " << player << " on line " << curLineNum << endl;
			return false;
		}
		if (!isLegalJokerTypeChar(myCommandVec[7][0])) {
			cout << "Bad format: illegal move command joker type by player " << player << " on line " << curLineNum << endl;
			return false;
		}
	}
	return true;
}

bool handleMoveCommand(GameBoard* board, int player, vector<string>* myVec, int curLineNum) {
	vector<string> myCommandVec = *myVec;
	int srcCol = stoi(myCommandVec[0]), srcRow = stoi(myCommandVec[1]), dstCol = stoi(myCommandVec[2]), dstRow = stoi(myCommandVec[3]), jRow = 0, jCol = 0;
	char jokerNewType = '\0';
	if (!isLegalPieceInSourceSquare(board, player, srcCol, srcRow)) { //checks that the src square holds a legal piece for the player
		cout << "Bad format: illegal move command's source square chosen by player " << player << " on line " << curLineNum << endl;
		return false;
	}
	if (!isLegalMoveFromSourceSquare(board, player, srcCol, srcRow, dstCol, dstRow)) { //checks if dest square is legal
		cout << "Bad format: illegal move command's destination square chosen by player " << player << " on line " << curLineNum << endl;
		return false;
	} //updates the board - does fight between the pieces if necessary
	board->finalBoard[dstRow - 1][dstCol - 1] = fight(board, board->finalBoard[srcRow - 1][srcCol - 1], board->finalBoard[dstRow - 1][dstCol - 1]);
	board->finalBoard[srcRow - 1][srcCol - 1] = NULL;

	if (myCommandVec.size() == 8) { //There was a joker change of type in the command
		jCol = stoi(myCommandVec[5]);
		jRow = stoi(myCommandVec[6]);
		jokerNewType = myCommandVec[7][0];
		if ((board->finalBoard[jRow - 1][jCol - 1] != NULL) && (board->finalBoard[jRow - 1][jCol - 1]->pieceType == 'J') && (board->finalBoard[jRow - 1][jCol - 1]->player = player))
			board->finalBoard[jRow - 1][jCol - 1]->curPieceType = jokerNewType;
		else { //there isn't a joker in the specified joker square
			cout << "Bad format: illegal joker updating command specified by player " << player << " on line " << curLineNum << endl;
			return false;
		}
	}
	return true;
}

// executes a given move for a given player.
//return value - false: bad format. true: move executed
bool executePlayerMove(GameBoard* board, int player, string move, int curLineNum) {
	vector<string> myVec;
	parseStringIntoVector(&myVec, move);
	if (!isLegalMoveCommandVec(&myVec, curLineNum, player) || !handleMoveCommand(board,player,&myVec,curLineNum)) {
		handleMovingFileError(board, player, curLineNum);
		return false;
	}
	return true;
	


	//string token;
	//istringstream iss(move);
	//for (i = 0; i < 4; i++) {
	//	if (getline(iss, token, ' ')) { //tries to take the next input index
	//		if (((i == 1 || i == 3) && !isLegalBoardRow(token)) || ((i == 0 || i == 2) && !isLegalBoardCol(token))) { //checks if legal
	//			cout << "Bad format: illegal move index by player " << player << " on line " << curLineNum << endl;
	//			handleMovingFileError(board, player, curLineNum);
	//			iss.clear();
	//			return false;
	//		}//updates relevant src/dest row/col
	//		if (i == 0)
	//			srcCol = stoi(token);
	//		if (i == 1)
	//			srcRow = stoi(token);
	//		if (i == 2)
	//			destCol = stoi(token);
	//		if (i == 3)
	//			destRow = stoi(token);
	//	}
	//	else { //getline failed on a certain iteration - could not get index
	//		cout << "Bad format: move command is too short by player " << player << " on line " << curLineNum << endl;
	//		handleMovingFileError(board, player, curLineNum);
	//		iss.clear();
	//		return false;
	//	}
	//} //at this point, we have all src/dest row/col indexes
	//if (getline(iss, token, ' ')) { //checks if there is a joker change of type given
	//	if (token == "J:") { 
	//		for (i = 0; i < 2; i++) {
	//			if (getline(iss, token, ' ')) { //tries to get the index of the joker (2 indexes, done 2 times)
	//				if ((i == 1 && !isLegalBoardRow(token)) || (i == 0 && !isLegalBoardCol(token))) {
	//					cout << "Bad format: illegal move index by player " << player << " on line " << curLineNum << endl;
	//					handleMovingFileError(board, player, curLineNum);
	//					iss.clear();
	//					return false;
	//				}//updates relevant joker row/col
	//				if (i == 0)
	//					jCol = stoi(token);
	//				if (i == 1)
	//					jRow = stoi(token);
	//			}
	//			else { //getline failed - at least one index missing
	//				cout << "Bad format: move command is too short by player " << player << " on line " << curLineNum << endl;
	//				handleMovingFileError(board, player, curLineNum);
	//				iss.clear();
	//				return false;
	//			}
	//		}
	//		if (getline(iss, token, ' ')) { //gets the new curType of the given joker
	//			if (token.length() != 1) {
	//				cout << "Bad format: move input size by player " << player << " inconsistent with given instructions on line " << curLineNum << endl;
	//				handleMovingFileError(board, player, curLineNum);
	//				iss.clear();
	//				return false;
	//			}
	//			if (!isLegalJokerTypeChar(token[0])) { //checks given curType is legal
	//				cout << "Bad format: illegal move command joker type by player " << player << " on line " << curLineNum << endl;
	//				handleMovingFileError(board, player, curLineNum);
	//				iss.clear();
	//				return false;
	//			}
	//			jokerNewType = token[0];
	//		}
	//		else { //getline failed - joker's new type is missing
	//			cout << "Bad format: move command is too short by player " << player << " on line " << curLineNum << endl;
	//			handleMovingFileError(board, player, curLineNum);
	//			iss.clear();
	//			return false;
	//		}
	//	}
	//	else { //an extra char/string was given, and it isn't J: - meaning it's an error
	//		cout << "Bad format: bad character at move command player " << player << " on line " << curLineNum << endl;
	//		handleMovingFileError(board, player, curLineNum);
	//		iss.clear();
	//		return false;
	//	}
	//}
	
	//if (!isLegalPieceInSourceSquare(board, player, srcCol, srcRow)) { //checks that the src square holds a legal piece for the player
	//	cout << "Bad format: illegal move command's source square chosen by player " << player << " on line " << curLineNum << endl;
	//	handleMovingFileError(board, player, curLineNum);
	//	iss.clear();
	//	return false;
	//}
	//if (!isLegalMoveFromSourceSquare(board, player, srcCol, srcRow, destCol, destRow)) { //checks if dest square is legal
	//	cout << "Bad format: illegal move command's destination square chosen by player " << player << " on line " << curLineNum << endl;
	//	handleMovingFileError(board, player, curLineNum);
	//	iss.clear();
	//	return false;
	//} //updates the board - does fight between the pieces if necessary
	//board->finalBoard[destRow - 1][destCol - 1] = fight(board,board->finalBoard[srcRow - 1][srcCol - 1], board->finalBoard[destRow - 1][destCol - 1]);
	//board->finalBoard[srcRow - 1][srcCol - 1] = NULL;

	//if (jokerNewType != '\0') { //There was a joker change of type in the command
	//	if ((board->finalBoard[jRow - 1][jCol - 1] != NULL) && (board->finalBoard[jRow - 1][jCol - 1]->pieceType == 'J')&&(board->finalBoard[jRow - 1][jCol - 1]->player = player))
	//		board->finalBoard[jRow - 1][jCol - 1]->curPieceType = jokerNewType;
	//	else { //there isn't a joker in the specified joker square
	//		cout << "Bad format: illegal joker updating command specified by player " << player << " on line " << curLineNum << endl;
	//		handleMovingFileError(board, player, curLineNum);
	//		iss.clear();
	//		return false;
	//	}
	//}
	//return true;

}


//Executes the moves of both players - the actual game.
//return value - false: bad input moves file/files. true: game ended
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
		if (hasOtherPlayerWon(board, 1)) { //checks if the first player lost (on second player's move or before)
			player1moves.close();
			player2moves.close();
			return true;
		}
		if (!player1FileEnded) { //if there are more player1's commands to do - get the next command
			if(!getline(player1moves, curPlayer1Line) || curPlayer1Line == "")
				player1FileEnded = true;
			else
				curLinePlayer1Num++;
		}
		if (!player2FileEnded) { //if there are more player2's commands to do - get the next command
			if (!getline(player2moves, curPlayer2Line) || curPlayer2Line == "")
				player2FileEnded = true;
			else
				curLinePlayer2Num++;
		}
		if (player1FileEnded && player2FileEnded) { //both players ran out of plays - tie
			board->winner = 0;
			board->reason = "A tie - both Moves input files done without a winner";
			player1moves.close();
			player2moves.close();
			return true;
		}
		if (!player1FileEnded) {//if there are more player1's commands to do - execute the next command
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
		if (!player2FileEnded) {//if there are more player2's commands to do - execute the next command
			if (!executePlayerMove(board, 2, curPlayer2Line, curLinePlayer2Num)) {
				player1moves.close();
				player2moves.close();
				return true;
			}
		}
	}
	return true;
}
