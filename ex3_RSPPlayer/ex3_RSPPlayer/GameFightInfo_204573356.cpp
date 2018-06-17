#include "GameFightInfo_204573356.h"
//GameFightInfo_204573356 Ctor
GameFightInfo_204573356::GameFightInfo_204573356(const Point & fPos, char p1P, char p2P, int winner)
{
	this->p1Piece = p1P;
	this->p2Piece = p2P;
	this->fightWinner = winner;
	this->fightPos = make_unique<MyPoint_204573356>(fPos.getX(), fPos.getY());
}

/*
returns fight's position
*/
const Point & GameFightInfo_204573356::getPosition() const
{
	return *(this->fightPos);
}

/*
returns fight's piece according to player number supplied
*/
char GameFightInfo_204573356::getPiece(int player) const
{
	if (player == 1)
		return this->p1Piece;
	return this->p2Piece;
}

/*
returns fight's winner number
*/
int GameFightInfo_204573356::getWinner() const
{
	return this->fightWinner;
}
