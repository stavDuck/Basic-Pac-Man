#ifndef _CREATURE_H_
#define _CREATURE_H_
#include <cstring>
#include <stdlib.h>
#include "Point.h"

class PacmanGame;

// Abstruct class
class Creature {
	protected:
		Point originalPosition;
		Point position;
		int direction = 4;
		PacmanGame* theGame;
	public:
		Creature(PacmanGame* _theGame, Point _originalPosition);
		virtual void move()  = 0; 

		// setters
		void setPosition(int x, int y); // row = x, cols = y
		void setDirection(int dir);
		void setGame(PacmanGame* _theGame);
		void setOriginalPosition(int x, int y);

		// getters
		Point getOriginalPosition() const;
		Point getPosition() const;
		int getDirection() const;
		int getRandomDirection() const; // get random number between 0-3
};

#endif
