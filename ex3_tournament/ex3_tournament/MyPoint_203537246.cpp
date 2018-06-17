#include "MyPoint_203537246.h"

MyPoint_203537246::MyPoint_203537246(int newX, int newY) :x(newX), y(newY) {}

/*
return the point's x position.
*/
int MyPoint_203537246::getX() const
{
	return this->x;
}

/*
return the point's y position.
*/
int MyPoint_203537246::getY() const
{
	return this->y;
}

/*
sets the point's x position.
*/
void MyPoint_203537246::setX(int newX)
{
	this->x = newX;
}

/*
sets the point's y position.
*/
void MyPoint_203537246::setY(int newY)
{
	this->y = newY;
}
