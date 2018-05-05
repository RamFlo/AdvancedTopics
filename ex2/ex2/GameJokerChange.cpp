#include "GameJokerChange.h"

GameJokerChange::GameJokerChange(int x, int y, char newRep)
{
	this->jokerChangePos = make_unique<MyPoint>(x, y);
	this->jokerNewRep = newRep;
}

const Point & GameJokerChange::getJokerChangePosition() const
{
	return *(this->jokerChangePos);
}

char GameJokerChange::getJokerNewRep() const
{
	return this->getJokerNewRep();
}
