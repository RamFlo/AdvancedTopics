#ifndef __GAME_FIGHT_INFO_203537246_H_
#define __GAME_FIGHT_INFO_203537246_H_

//--------------------------
// GameFightInfo Class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "FightInfo.h"
#include "MyPoint_203537246.h"
#include <memory>
using namespace std;
//--------------------------

class GameFightInfo_203537246:public FightInfo {
	int fightWinner;
	char p1Piece, p2Piece;
	unique_ptr<Point> fightPos;
public:
	GameFightInfo_203537246(const Point & fPos,char p1P,char p2P,int winner);
	const Point& getPosition() const override;
	char getPiece(int player) const override; // R, P, S, B or F (but NOT J)
	int getWinner() const override; // 0 - both lost / tie, 1 - player 1 won, 2 - player 2 won
	//~GameFightInfo() {}
};

#endif