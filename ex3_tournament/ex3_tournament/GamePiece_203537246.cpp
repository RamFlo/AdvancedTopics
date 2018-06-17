#include "GamePiece_203537246.h"

GamePiece_203537246::GamePiece_203537246(char newPieceType, int x, int y, char newJokerRep, int p) :pieceType(newPieceType), jokerRep(newJokerRep), player(p)
{
	curPosition = make_unique<MyPoint_203537246>(x, y);
}

/*
returns gamepiece's position
*/
const Point & GamePiece_203537246::getPosition() const
{
	return *(this->curPosition);
}

/*
returns gamepiece's type
*/
char GamePiece_203537246::getPiece() const
{
	return this->pieceType;
}

/*
returns gamepiece's joker rep. (if piece is not a joker, return '#')
*/
char GamePiece_203537246::getJokerRep() const
{
	return this->jokerRep;
}

/*
returns gamepiece's player number
*/
int GamePiece_203537246::getPlayer() const
{
	return this->player;
}
