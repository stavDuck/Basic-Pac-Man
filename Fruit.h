#ifndef _FRUIT_H_
#define _FRUIT_H_

#include "Creature.h"

class Fruit : public Creature {
private:
	bool isInBoard = false; // start game with no fruit
	int value;
	int index;
	
public:
	Fruit(PacmanGame* _theGame, int index);
	void init();
	void move();
	
	// setters
	void setIsInBoard(bool res);
	void setIndex(int index);

	// getters
	bool getIsInBoard() const;
	int getRandomValue() const; // get random number between 5-9
	int getValue() const;
	Point getRandomPosition() const;
	int getIndex() const;
};
#endif
