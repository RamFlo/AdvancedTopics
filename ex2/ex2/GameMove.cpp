#include "GameMove.h"

GameMove::GameMove(int fromX, int fromY, int toX, int toY)
{
	fromPoint = make_unique<MyPoint>(fromX, fromY);
	toPoint = make_unique<MyPoint>(toX, toY);
}

const Point & GameMove::getFrom() const
{
	return *(this->fromPoint);
}

const Point & GameMove::getTo() const
{
	return *(this->toPoint);
}
