#include "GameBoard.h"


GameBoard::GameBoard() :player1Board(NULL), player2Board(NULL), finalBoard(NULL) {}
GameBoard::~GameBoard() {
	if (player1Board != NULL)
		delete[] player1Board;
	if (player2Board != NULL)
		delete[] player2Board;
	if (finalBoard != NULL)
		delete[] finalBoard;
}