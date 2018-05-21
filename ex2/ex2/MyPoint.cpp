#include "MyPoint.h"

MyPoint::MyPoint(int newX, int newY) :x(newX), y(newY) {}

/*
return the point's x position.
*/
int MyPoint::getX() const
{
	return this->x;
}

/*
return the point's y position.
*/
int MyPoint::getY() const
{
	return this->y;
}

/*
sets the point's x position.
*/
void MyPoint::setX(int newX)
{
	this->x = newX;
}

/*
sets the point's y position.
*/
void MyPoint::setY(int newY)
{
	this->y = newY;
}
