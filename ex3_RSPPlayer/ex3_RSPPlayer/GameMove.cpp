#include "GameMove.h"

GameMove::GameMove(int fromX, int fromY, int toX, int toY)
{
	fromPoint = make_unique<MyPoint>(fromX, fromY);
	toPoint = make_unique<MyPoint>(toX, toY);
}

/*
returns move source square's position
*/
const Point & GameMove::getFrom() const
{
	return *(this->fromPoint);
}

/*
returns move destionation square's position
*/
const Point & GameMove::getTo() const
{
	return *(this->toPoint);
}
