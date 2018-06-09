#include "GamePiece_204573356.h"

GamePiece_204573356::GamePiece_204573356(char newPieceType, int x, int y, char newJokerRep, int p) :pieceType(newPieceType), jokerRep(newJokerRep), player(p)
{
	curPosition = make_unique<MyPoint>(x, y);
}

/*
returns GamePiece_204573356's position
*/
const Point & GamePiece_204573356::getPosition() const
{
	return *(this->curPosition);
}

/*
returns GamePiece_204573356's type
*/
char GamePiece_204573356::getPiece() const
{
	return this->pieceType;
}

/*
returns GamePiece_204573356's joker rep. (if piece is not a joker, return '#')
*/
char GamePiece_204573356::getJokerRep() const
{
	return this->jokerRep;
}

/*
returns GamePiece_204573356's player number
*/
int GamePiece_204573356::getPlayer() const
{
	return this->player;
}
