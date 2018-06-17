#ifndef __MY_POINT_204573356_H_
#define __MY_POINT_204573356_H_

//--------------------------
// MyPoint Class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "Point.h"
//--------------------------

class MyPoint_204573356:public Point {
	int x, y;
public:
	MyPoint_204573356(int newX, int newY);
	int getX() const override;
	int getY() const override;
	void setX(int newX);
	void setY(int newY);
	~MyPoint_204573356() {}
};

#endif