#include "Ghost.h"
#include "PacmanGame.h"

int Ghost::smartMoveForGoodGhost = 1 + rand() % 20; // random number between 1 - 20
int Ghost::noviceMoveForGoodGhost = 5;

// Ghost ctor
Ghost::Ghost(PacmanGame* _theGame, Point _originalPosition): Creature(_theGame, _originalPosition){
}

// move Ghose in the board, if going to hit a wall or a tunnel we generate a new direction
void Ghost::move()
{
	int newDirection;
	Point nextPosition;
	bool isHitWall, isHitBorder, isHitFruit1, isHitFruit2;

	switch (ghostType)
	{
	case SMART:
		nextPosition = smartMove();
		break;
	case GOOD:
		nextPosition = goodMove();
		break;
	case NOVICE:
		nextPosition = noviceMove();
		break;
	}
	isHitFruit1 = theGame->isHitFruit(0, nextPosition);
	isHitFruit2 = theGame->isHitFruit(1, nextPosition);
	
	// check if hit pacman
	if (theGame->isHitPacman(nextPosition)) {
		theGame->handleStrike();
	}

	// continue game
	else{
		// get the char in board in curr position and print (ghost don't eat breadcrumb)
		char currPos = theGame->getBoardPosition(position);
		position.draw(currPos);

		if (isHitFruit1)
			theGame->handleFruitAndGhost(0);
		if (isHitFruit2)
			theGame->handleFruitAndGhost(1);
	
		position.move(direction);
		position.draw('$');
	}
}

// Moves function calculate the next VALID position according ghost type and return it
// smart move goes as close as it can to pacman position in every step
Point Ghost::smartMove() {
	Point pacmanPos = theGame->getPacmanPosition();
	bool isHitWall, isHitBorder;

	// if x ghost != x pacman try to move according to x
	// if ghost is stuck try to go according to y
	if (position.getX() != pacmanPos.getX()) {
		if (position.getX() < pacmanPos.getX())
			setDirection(RIGHT);

		else if (position.getX() > pacmanPos.getX())
			setDirection(LEFT);
		
		isHitWall = theGame->isWall(position.next(direction));
		isHitBorder = theGame->isInBorders(position.next(direction));

		// if x direction go to dead end try the y direction
		if (isHitWall || isHitBorder) {
			if (position.getY() < pacmanPos.getY())
				setDirection(DOWN);
			else if (position.getY() > pacmanPos.getY())
				setDirection(UP);
		}
	}
	
	// if x ghost == x pacman try to go according to y
	else {
		// if x ghost == x pacman check y values
		if (position.getY() < pacmanPos.getY())
			setDirection(DOWN);
		else if (position.getY() > pacmanPos.getY())
			setDirection(UP);
	}

	isHitWall = theGame->isWall(position.next(direction));
	isHitBorder = theGame->isInBorders(position.next(direction));
	
	// check valid next position
	// run until valid next poistion
	while (isHitWall || isHitBorder) {
		// get new direction and set the current ghost direction
		setDirection(getRandomDirection());

		// get the new status for bool values with new direction
		isHitWall = theGame->isWall(position.next(direction));
		isHitBorder = theGame->isInBorders(position.next(direction));
	}
	return position.next(direction);
}

// Moves function calculate the next VALID position according ghost type and return it
// good move use smart and novice moves
Point Ghost::goodMove() {
	int newDirection;
	bool isHitWall, isHitBorder;

	// need to execute smart move
	if (smartMoveForGoodGhost != 0) {
		smartMoveForGoodGhost--;
		return smartMove();
	}
	// else smart moves are done -> (smartMoveForGoodGhost == 0)
	else{
		// still continue with novice step
		if (noviceMoveForGoodGhost != 0) {
			noviceMoveForGoodGhost--;
			return noviceMove();
		}
		// else both smart and novice moves are done - reset both
		else {
			smartMoveForGoodGhost = 1 + rand() % 20;
			noviceMoveForGoodGhost = 5;

			// move
			smartMoveForGoodGhost--;
			return smartMove();
		}
	}
}
// Moves function calculate the next VALID position according ghost type and return it
// novice move generate the direction to move the ghost randomly
Point Ghost::noviceMove() {
	int newDirection;
	bool isHitWall, isHitBorder;

	// every 20 moves change direction
	if(PacmanGame::ghostMove % 20 == 0){
		newDirection = getRandomDirection();
		setDirection(newDirection);
	}

	isHitWall = theGame->isWall(position.next(direction));
	isHitBorder = theGame->isInBorders(position.next(direction));

	// check valid next position
	// run until valid next poistion
	while (isHitWall || isHitBorder) {
		// get new direction and set the current ghost direction
		newDirection = getRandomDirection();
		setDirection(newDirection);

		// get the new status for bool values with new direction
		isHitWall = theGame->isWall(position.next(direction));
		isHitBorder = theGame->isInBorders(position.next(direction));
	}

	return position.next(direction);
}
// Function set ghost type
void Ghost::setGhostType(char c) {
	ghostType = c;
}

// Function get ghost type
char Ghost::getGhostType() const {
	return ghostType;
}