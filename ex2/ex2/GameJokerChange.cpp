#include "GameJokerChange.h"

GameJokerChange::GameJokerChange(int x, int y, char newRep)
{
	this->jokerChangePos = make_unique<MyPoint>(x, y);
	this->jokerNewRep = newRep;
}

/*
returns joker change position
*/
const Point & GameJokerChange::getJokerChangePosition() const
{
	return *(this->jokerChangePos);
}

/*
returns joker's new rep
*/
char GameJokerChange::getJokerNewRep() const
{
	return this->jokerNewRep;
}
