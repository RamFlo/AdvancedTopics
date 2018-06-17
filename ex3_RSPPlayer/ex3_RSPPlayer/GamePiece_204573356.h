#ifndef __GAME_PIECE_204573356_H_
#define __GAME_PIECE_204573356_H_

//--------------------------
// GamePiece Class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "PiecePosition.h"
#include "MyPoint_204573356.h"
#include <memory>

using std::unique_ptr;
using namespace std;
//--------------------------

class GamePiece_204573356:public PiecePosition {
	unique_ptr<MyPoint_204573356> curPosition;
	char pieceType, jokerRep;
	int player;
public:
	GamePiece_204573356(char newPieceType, int x, int y, char newJokerRep,int player);
	const Point& getPosition() const override;
	char getPiece() const override; // R, P, S, B, J or F
	char getJokerRep() const override; // ONLY for Joker: R, P, S or B -- non-Joker may return ‘#’
	int getPlayer() const;
	~GamePiece_204573356() {}
};

#endif