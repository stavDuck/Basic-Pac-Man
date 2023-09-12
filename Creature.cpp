#include "Creature.h"

// Creature ctor
Creature::Creature(PacmanGame* _theGame, Point _originalPosition) {
	theGame = _theGame;
	originalPosition = _originalPosition;
}

// function set position
void Creature::setPosition(int x, int y) {
	position.set(x, y);
}
// function set direction
void Creature::setDirection(int dir) {
	direction = dir;
}
// function set the game
void Creature::setGame(PacmanGame* _theGame) {
	theGame = _theGame;
}
// function set original position
void Creature::setOriginalPosition(int x, int y) {
	originalPosition.set(x, y);
}
// function gets original position for Pacman player in the board
Point Creature::getOriginalPosition() const{
	return originalPosition;
}
// function gets pacman current position
Point Creature::getPosition() const{
	return position;
}
// function return direction
int Creature::getDirection() const{
	return direction;
}

// function generate a new direction - number between 0-3
int Creature::getRandomDirection() const{
	int direction = rand() % 4;
	return direction;
}