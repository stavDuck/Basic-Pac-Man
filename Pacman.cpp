#include "Pacman.h"
#include "PacmanGame.h"
// Pacman ctor
Pacman::Pacman(PacmanGame* _theGame, const char* keys): Creature(_theGame,Point(3,3)){
	this->setArrowKeys(keys);
}

// Function moves Pacman on the screen
void Pacman::move()
{
	Point nextPosition = position.next(direction);
	bool isHitFruit1 = theGame->isHitFruit(0, nextPosition);
	bool isHitFruit2 = theGame->isHitFruit(1, nextPosition);

	// if current poisition has breadcrumb
	if (theGame->getBoardPosition(position) == '.') {
		theGame->setScore(); // ++ score
		theGame->setEatenBreadCrumbs(); // ++ eaten
		theGame->setBoardPosition(position, ' ');
		printScore();
	}

	// winner
	if (theGame->getEatenBreadCrumbs() == theGame->getTotalBreadCrumbs()) {
	//if(theGame->getScore() % 10 == 0){
		theGame->setWinGame(true);
	}

	// continue play
	else {
		// check if hit ghost
		if (theGame->isHitGhost(nextPosition)) {
			theGame->handleStrike();
		}

		// else not ghost
		else {
			// get the char in board in curr position and print (ghost don't eat breadcrumb)
			char currPos = theGame->getBoardPosition(position);
			position.draw(currPos);

			// check if hit fruit
			if (isHitFruit1) 
				theGame->handleFruitAndPacman(0);
			if (isHitFruit2)
				theGame->handleFruitAndPacman(1);

			if ((*theGame).isWall(nextPosition))
				// STAY if meet a wall
				direction = 4; 

			position.move(direction);
			position.draw('@');
		}
	}
}

// function prints the score to the screen
void Pacman::printScore() {
	gotoxy(SCORE_X, SCORE_Y);
	cout << "    "; //max score digits is 4
	gotoxy(SCORE_X, SCORE_Y);
	cout << theGame->getScore();
}

// function gets pacman current direction
int Pacman::getDirection(char key) const{
	for (int i = 0; i < KEYS_ARR_SIZE; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}