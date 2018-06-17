#include "GameMove_204573356.h"

GameMove_204573356::GameMove_204573356(int fromX, int fromY, int toX, int toY)
{
	fromPoint = make_unique<MyPoint_204573356>(fromX, fromY);
	toPoint = make_unique<MyPoint_204573356>(toX, toY);
}

/*
returns move source square's position
*/
const Point & GameMove_204573356::getFrom() const
{
	return *(this->fromPoint);
}

/*
returns move destionation square's position
*/
const Point & GameMove_204573356::getTo() const
{
	return *(this->toPoint);
}
