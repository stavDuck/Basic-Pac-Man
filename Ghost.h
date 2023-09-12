#ifndef _GHOST_H_
#define _GHOST_H_

#include <time.h>
#include "Creature.h"

class Ghost: public Creature {
private:
	char ghostType;

public:
	// the following static vars are only in good ghost game
	static int smartMoveForGoodGhost;
	static int noviceMoveForGoodGhost;

	constexpr static char SMART = 'a';
	constexpr static char GOOD = 'b';
	constexpr static char NOVICE = 'c';
	Ghost(PacmanGame* _theGame, Point _originalPosition);
	void move();
	Point smartMove();
	Point goodMove();
	Point noviceMove();

	// setters
	void setGhostType(char c);

	// getters
	char getGhostType() const;
};
#endif