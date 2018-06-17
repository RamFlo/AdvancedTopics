#ifndef __GAME_MOVE_204573356_H_
#define __GAME_MOVE_204573356_H_

//--------------------------
// GameMove class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "Move.h"
#include "MyPoint_204573356.h"
#include <memory>
using namespace std;
//--------------------------

class GameMove_204573356: public Move {
	unique_ptr<Point> fromPoint, toPoint;
public:
	GameMove_204573356(int fromX, int fromY, int toX, int toY);
	const Point& getFrom() const override;
	const Point& getTo() const override;
	~GameMove_204573356() {}
};

#endif
