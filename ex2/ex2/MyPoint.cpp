#include "MyPoint.h"

MyPoint::MyPoint(int newX, int newY) :x(newX), y(newY) {}

int MyPoint::getX() const
{
	return this->x;
}

int MyPoint::getY() const
{
	return this->y;
}
