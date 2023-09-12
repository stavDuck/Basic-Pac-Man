#ifndef _PACMAN_H_
#define _PACMAN_H_

#include "Creature.h"

class Pacman : public Creature{
private:
	constexpr static int KEYS_ARR_SIZE = 5;
	char arrowKeys[KEYS_ARR_SIZE];
	void printScore();
public:
	Pacman(PacmanGame* _theGame, const char* keys);
	void move();

	// setters
	void setArrowKeys(const char* keys) {
		arrowKeys[0] = keys[0];
		arrowKeys[1] = keys[1];
		arrowKeys[2] = keys[2];
		arrowKeys[3] = keys[3];
		arrowKeys[4] = keys[4]; // for s - stay
	}

	// getters
	int getDirection(char key) const;
};

#endif