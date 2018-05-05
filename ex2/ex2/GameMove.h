#ifndef __GAME_MOVE_H_
#define __GAME_MOVE_H_

//--------------------------
// GameMove class
//--------------------------
// abstract class Move should be the base class for your "Move" implementation
// This interface is in use in two flows:
// (a) returned from PlayerAlgorithm to "Game" in the flow:
// "Game" -> PlayerAlgorithm : virtual unique_ptr<Move> getMove();
// (b) sent to PlayerAlgorithm by "Game" in the flow:
// "Game" -> PlayerAlgorithm : notifyOnOpponentMove(const Move& move); // called only on opponent’s move
// Note that "Game" is in parantheses because this is your class and you can choose its name

// @author Amir Kirsh, TAU - Advanced Topics in Programming - 2018 Semester B

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
