#pragma once
#ifndef GAMEBOARD_H_
#include <string>
#include "GamePiece.h"
#define N 10
#define M 10
using namespace std;
class GameBoard {
public:
	int player1Flags;
	int player1Jokers;
	int player1Rocks;
	int player1Scissors;
	int player1Papers;
	int player1Bombs;
	int player2Flags;
	int player2Jokers;
	int player2Rocks;
	int player2Scissors;
	int player2Papers;
	int player2Bombs;
	int winner;
	int errorLinePlayer1;
	int errorLinePlayer2;
	GamePiece* player1Board[N][M];
	GamePiece* player2Board[N][M];
	GamePiece* finalBoard[N][M];
	string reason;
	GameBoard();
	~GameBoard();
};



#endif // !GAMEBOARD_H_