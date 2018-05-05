#ifndef __GAME_JOKER_CHANGE_H_
#define __GAME_JOKER_CHANGE_H_

//--------------------------
// GameJokerChange class
//--------------------------
// abstract class JokerChange should be the base class for your "JokerChange" implementation
// returned from PlayerAlgorithm to "Game" in the flow:
// "Game" -> PlayerAlgorithm : virtual unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested
// Note that "Game" is in parantheses because this is your class and you can choose its name

// @author Amir Kirsh, TAU - Advanced Topics in Programming - 2018 Semester B
#include "JokerChange.h"
#include "MyPoint.h"
#include <memory>
using namespace std;
//--------------------------

//--------------------------

class GameJokerChange: public JokerChange {
	unique_ptr<Point> jokerChangePos;
	char jokerNewRep;
public:
	GameJokerChange(int x, int y, char newRep);
	const Point& getJokerChangePosition() const override;
	char getJokerNewRep() const override; // R, P, S or B (but NOT J and NOT F)
	~GameJokerChange() {}
};

#endif
