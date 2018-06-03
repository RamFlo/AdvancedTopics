#ifndef __GAME_MOVE_H_
#define __GAME_MOVE_H_

//--------------------------
// GameMove class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "Move.h"
#include "MyPoint.h"
#include <memory>
using namespace std;
//--------------------------

class GameMove: public Move {
	unique_ptr<Point> fromPoint, toPoint;
public:
	GameMove(int fromX, int fromY, int toX, int toY);
	const Point& getFrom() const override;
	const Point& getTo() const override;
	~GameMove() {}
};

#endif
