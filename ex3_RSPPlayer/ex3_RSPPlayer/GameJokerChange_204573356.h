#ifndef __GAME_JOKER_CHANGE_204573356_H_
#define __GAME_JOKER_CHANGE_204573356_H_

//--------------------------
// GameJokerChange class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B
#include "JokerChange.h"
#include "MyPoint_204573356.h"
#include <memory>
using namespace std;
//--------------------------

//--------------------------

class GameJokerChange_204573356: public JokerChange {
	unique_ptr<Point> jokerChangePos;
	char jokerNewRep;
public:
	GameJokerChange_204573356(int x, int y, char newRep);
	const Point& getJokerChangePosition() const override;
	char getJokerNewRep() const override; // R, P, S or B (but NOT J and NOT F)
	~GameJokerChange_204573356() {}
};

#endif
