#ifndef __GAME_BOARD_H_
#define __GAME_BOARD_H_

//--------------------------
// GameBoard_204573356 Class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "Board.h"
#include "GamePiece_204573356.h"
#include "AllGameParameters.h"
#include <memory>

using namespace std;
//--------------------------

class GameBoard_204573356 :public Board {
	unique_ptr<GamePiece_204573356> finalBoard[N][M];
public:
	GameBoard_204573356();
	GamePiece_204573356 & getGamePiece_204573356(const Point & pos) const;
	int getPlayer(const Point& pos) const override; // 1 for player 1’s piece, 2 for 2, 0 if empty
	void setGamePiece_204573356OnBoard(const PiecePosition & piece, int player);
	//~GameBoard_204573356() {}
};

#endif