#include "GameFightInfo.h"

GameFightInfo::GameFightInfo(const Point & fPos, char p1P, char p2P, int winner) :p1Piece(p1P),p2Piece(p2P),fightWinner(winner)
{
	this->fightPos = make_unique<MyPoint>(fPos.getX(), fPos.getY());
}

const Point & GameFightInfo::getPosition() const
{
	return *(this->fightPos);
}

char GameFightInfo::getPiece(int player) const
{
	if (player == 1)
		return this->p1Piece;
	return this->p2Piece;
}

int GameFightInfo::getWinner() const
{
	return this->fightWinner;
}
