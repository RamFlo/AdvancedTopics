#include "GameJokerChange_203537246.h"

GameJokerChange_203537246::GameJokerChange_203537246(int x, int y, char newRep)
{
	this->jokerChangePos = make_unique<MyPoint_203537246>(x, y);
	this->jokerNewRep = newRep;
}

/*
returns joker change position
*/
const Point & GameJokerChange_203537246::getJokerChangePosition() const
{
	return *(this->jokerChangePos);
}

/*
returns joker's new rep
*/
char GameJokerChange_203537246::getJokerNewRep() const
{
	return this->jokerNewRep;
}
