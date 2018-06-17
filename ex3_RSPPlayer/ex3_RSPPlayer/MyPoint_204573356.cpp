#include "MyPoint_204573356.h"

MyPoint_204573356::MyPoint_204573356(int newX, int newY) :x(newX), y(newY) {}

/*
return the point's x position.
*/
int MyPoint_204573356::getX() const
{
	return this->x;
}

/*
return the point's y position.
*/
int MyPoint_204573356::getY() const
{
	return this->y;
}

/*
sets the point's x position.
*/
void MyPoint_204573356::setX(int newX)
{
	this->x = newX;
}

/*
sets the point's y position.
*/
void MyPoint_204573356::setY(int newY)
{
	this->y = newY;
}
