#include "GameFightInfo_203537246.h"

GameFightInfo_203537246::GameFightInfo_203537246(const Point & fPos, char p1P, char p2P, int winner)
{
	this->p1Piece = p1P;
	this->p2Piece = p2P;
	this->fightWinner = winner;
	this->fightPos = make_unique<MyPoint_203537246>(fPos.getX(), fPos.getY());
}

/*
returns fight's position
*/
const Point & GameFightInfo_203537246::getPosition() const
{
	return *(this->fightPos);
}

/*
returns fight's piece according to player number supplied
*/
char GameFightInfo_203537246::getPiece(int player) const
{
	if (player == 1)
		return this->p1Piece;
	return this->p2Piece;
}

/*
returns fight's winner number
*/
int GameFightInfo_203537246::getWinner() const
{
	return this->fightWinner;
}
