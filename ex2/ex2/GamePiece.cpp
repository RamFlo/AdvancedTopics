#include "GamePiece.h"

GamePiece::GamePiece(char newPieceType, int x, int y, char newJokerRep, int p) :pieceType(newPieceType), jokerRep(newJokerRep), player(p)
{
	curPosition = make_unique<MyPoint>(x, y);
}

/*
returns gamepiece's position
*/
const Point & GamePiece::getPosition() const
{
	return *(this->curPosition);
}

/*
returns gamepiece's type
*/
char GamePiece::getPiece() const
{
	return this->pieceType;
}

/*
returns gamepiece's joker rep. (if piece is not a joker, return '#')
*/
char GamePiece::getJokerRep() const
{
	return this->jokerRep;
}

/*
returns gamepiece's player number
*/
int GamePiece::getPlayer() const
{
	return this->player;
}
