#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"
using std::cout;

enum { UP, DOWN, LEFT, RIGHT, STAY };

class Point {
	int x = 1, y = 1;
public:
	Point() {}
	Point(int _x, int _y) {
		x = _x;
		y = _y;
	}

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void set(int _x, int _y) {
		x = _x;
		y = _y;
	}
	void draw(char ch) {
		gotoxy(x, y);
		cout << ch;
		cout.flush();
	}
	void move();
	void move(int direction);
	Point next(int direction) {
		Point next = *this;
		next.move(direction);
		return next;
	}	
};
#endif