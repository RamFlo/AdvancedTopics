#ifndef __GAME_BOARD_H_
#define __GAME_BOARD_H_

//--------------------------
// GameBoard Class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "Board.h"
#include "GamePiece.h"
#include "AllGameParameters.h"
#include <memory>

using namespace std;
//--------------------------

class GameBoard :public Board {
	unique_ptr<GamePiece> finalBoard[N][M];
public:
	GameBoard();
	GamePiece & getGamePiece(const Point & pos) const;
	int getPlayer(const Point& pos) const override; // 1 for player 1’s piece, 2 for 2, 0 if empty
	void setGamePieceOnBoard(const PiecePosition & piece, int player);
	~GameBoard() {}
};

#endif