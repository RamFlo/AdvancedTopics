#ifndef __GAME_BOARD_203537246_H_
#define __GAME_BOARD_203537246_H_

//--------------------------
// GameBoard Class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "Board.h"
#include "GamePiece_203537246.h"
#include "AllGameParameters.h"
#include <memory>

using namespace std;
//--------------------------

class GameBoard_203537246 :public Board {
	unique_ptr<GamePiece_203537246> finalBoard[N][M];
public:
	GameBoard_203537246();
	GamePiece_203537246 & getGamePiece(const Point & pos) const;
	int getPlayer(const Point& pos) const override; // 1 for player 1’s piece, 2 for 2, 0 if empty
	void setGamePieceOnBoard(const PiecePosition & piece, int player);
	//~GameBoard() {}
};

#endif