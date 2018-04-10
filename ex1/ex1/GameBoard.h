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
	int winner;						//0-draw, 1-player1, 2-player2
	int errorLinePlayer1;
	int errorLinePlayer2;
	GamePiece* player1Board[N][M];	//The first player's board after positioning
	GamePiece* player2Board[N][M];	//The second player's board after positioning
	GamePiece* finalBoard[N][M];	//The board after positioning both players' pieces upon which the game is played
	string reason;					//The reason for win or draw
	GameBoard();
	~GameBoard();
};



#endif // !GAMEBOARD_H_