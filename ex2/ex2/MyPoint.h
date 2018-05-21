#ifndef __MY_POINT_H_
#define __MY_POINT_H_

//--------------------------
// MyPoint Class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "Point.h"
//--------------------------

class MyPoint:public Point {
	int x, y;
public:
	MyPoint(int newX, int newY);
	int getX() const override;
	int getY() const override;
	void setX(int newX);
	void setY(int newY);
	~MyPoint() {}
};

#endif