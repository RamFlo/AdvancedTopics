#include "GamePiece.h"

GamePiece::GamePiece(char newPieceType, int x, int y, char newJokerRep, int p) :pieceType(newPieceType), jokerRep(newJokerRep), player(p)
{
	curPosition = make_unique<MyPoint>(x, y);
}

const Point & GamePiece::getPosition() const
{
	return *(this->curPosition); //how does returning by reference works?
}

char GamePiece::getPiece() const
{
	return this->pieceType;
}

char GamePiece::getJokerRep() const
{
	return this->jokerRep;
}

int GamePiece::getPlayer() const
{
	return this->player;
}
