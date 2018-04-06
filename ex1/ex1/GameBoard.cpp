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
	this->player1Flags = 0;
	this->player1Flags=0;
	this->player1Jokers = 0;
	this->player1Rocks = 0;
	this->player1Scissors = 0;
	this->player1Papers = 0;
	this->player1Bombs = 0;
	this->player2Flags = 0;
	this->player2Jokers = 0;
	this->player2Rocks = 0;
	this->player2Scissors = 0;
	this->player2Papers = 0;
	this->player2Bombs = 0;
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

	/*
	if (player1Board != NULL) {
	for (i=0; i<N; i++)
	delete[] player1Board[]

	}
	delete[] player1Board;
	if (player2Board != NULL)
	delete[] player2Board;
	if (finalBoard != NULL)
	delete[] finalBoard;
	*/

}