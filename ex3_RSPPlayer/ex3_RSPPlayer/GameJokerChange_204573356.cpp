#include "GameJokerChange_204573356.h"

GameJokerChange_204573356::GameJokerChange_204573356(int x, int y, char newRep)
{
	this->jokerChangePos = make_unique<MyPoint_204573356>(x, y);
	this->jokerNewRep = newRep;
}

/*
returns joker change position
*/
const Point & GameJokerChange_204573356::getJokerChangePosition() const
{
	return *(this->jokerChangePos);
}

/*
returns joker's new rep
*/
char GameJokerChange_204573356::getJokerNewRep() const
{
	return this->jokerNewRep;
}
