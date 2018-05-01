#pragma once
#ifndef GAMEBOARD_H_
#include <string>
#include "GamePiece.h"
#include <map>
#define N 10
#define M 10
using namespace std;
class GameBoard {
public:
	map<string, int> pieceCountMap;
	//int player1flags;
	//int player1jokers;
	//int player1rocks;
	//int player1scissors;
	//int player1papers;
	//int player1bombs;
	//int player2flags;
	//int player2jokers;
	//int player2rocks;
	//int player2scissors;
	//int player2papers;
	//int player2bombs;
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