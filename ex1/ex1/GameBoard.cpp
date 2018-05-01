#include "GameBoard.h"
#include "mainAux.h"


GameBoard::GameBoard() {
	int i = 0, j = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			this->player1Board[i][j] = NULL;
			this->player2Board[i][j] = NULL;
			this->finalBoard[i][j] = NULL;
		}
	}


	this->pieceCountMap["player1Flags"] = 0;
	this->pieceCountMap["player1Jokers"] = 0;
	this->pieceCountMap["player1Rocks"] = 0;
	this->pieceCountMap["player1Scissors"] = 0;
	this->pieceCountMap["player1Papers"] = 0;
	this->pieceCountMap["player1Bombs"] = 0;
	this->pieceCountMap["player2Flags"] = 0;
	this->pieceCountMap["player2Jokers"] = 0;
	this->pieceCountMap["player2Rocks"] = 0;
	this->pieceCountMap["player2Scissors"] = 0;
	this->pieceCountMap["player2Papers"] = 0;
	this->pieceCountMap["player2Bombs"] = 0;
	this->winner = 0;
	this->errorLinePlayer1 = 0;
	this->errorLinePlayer2 = 0;
	this->reason = "";
}
GameBoard::~GameBoard() {
	int i = 0, j = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			if (this->player1Board[i][j] != NULL)
				delete this->player1Board[i][j];
			if (this->player2Board[i][j] != NULL)
				delete this->player2Board[i][j];
			this->finalBoard[i][j] = NULL;
		}
	}
}