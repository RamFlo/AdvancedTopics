#ifndef __MY_POINT_203537246_H_
#define __MY_POINT_203537246_H_

//--------------------------
// MyPoint Class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "Point.h"
//--------------------------

class MyPoint_203537246:public Point {
	int x, y;
public:
	MyPoint_203537246(int newX, int newY);
	int getX() const override;
	int getY() const override;
	void setX(int newX);
	void setY(int newY);
	//~MyPoint() {}
};

#endif