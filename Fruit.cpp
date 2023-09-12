#include "Fruit.h"
#include "PacmanGame.h"

// Ghost ctor
Fruit::Fruit(PacmanGame* _theGame, int index) : Creature(_theGame, Point()) {
	this->index = index;
}

// initiate the Fruit data members every time the fruit appears
void Fruit::init() {
	Point pos;

	isInBoard = true;
	// set value of fruit
	value = getRandomValue();
	// set direction
	direction = getRandomDirection();
	// set position and original position
	pos = getRandomPosition();
	originalPosition = pos;
	position = pos;
}

// move Fruit in the board, if going to hit a wall or a tunnel we generate a new direction
void Fruit::move()
{
	int newDirection;
	Point nextPosition = position.next(direction);
	bool isHitWall = theGame->isWall(nextPosition);
	bool isHitBorder = theGame->isInBorders(nextPosition);

	// get the char in board in curr position and print (ghost don't eat breadcrumb)
	// This action need to happend in any case
	char currPos = theGame->getBoardPosition(position);
	position.draw(currPos);

	// check if hit pacman
	if (theGame->isHitPacman(nextPosition)) {
		theGame->handleFruitAndPacman(index);
	}
	else if (theGame->isHitGhost(nextPosition)) {
		theGame->handleFruitAndGhost(index);
	}

	// continue game with fruit on board
	else {
		// get new direction until next move is valid
		while (isHitWall || isHitBorder) {
			// get new direction and set the current ghost direction
			newDirection = getRandomDirection();
			setDirection(newDirection);

			// get the new status for bool values with new direction
			isHitWall = theGame->isWall(position.next(direction));
			isHitBorder = theGame->isInBorders(position.next(direction));
		}

		position.move(direction);
		position.draw(value + '0');	
	}
}

// setters
// set isBoard value as res
void Fruit::setIsInBoard(bool res) {
	isInBoard = res;
}

// set index 
void Fruit::setIndex(int index) {
	this->index = index;
}

// getters
// Function get isInBoard value
bool Fruit::getIsInBoard() const{
	return isInBoard;
}
// Function generate and return value in between 5 to 9
int Fruit::getRandomValue() const{
	int direction = rand() % 5 + 5;
	return direction;
}

// Function return value of the fruit
int Fruit::getValue() const{
	return value;
}

// Function generate position in the board and return a valid position - not in wall and not in border
Point Fruit::getRandomPosition() const{
	int x, y;
	Point position;
	bool isPositionValid = false;
	bool isHitWall, isHitBorder;

	while (!isPositionValid) {
		 x = rand() % 80;
		 y = rand() % 24;
		 position.set(x, y);

		 isHitWall = theGame->isWall(position);
		 isHitBorder = theGame->isInBorders(position);
		 
		 if (!isHitWall && !isHitBorder)
			 isPositionValid = true;
	}
	
	return position;
}

// Function get index
int Fruit::getIndex() const {
	return index;
}