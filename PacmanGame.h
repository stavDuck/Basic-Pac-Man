#ifndef _PACMANGAM_H_
#define _PACMANGAM_H_

#include "io_utils.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include <string>
#include <fstream>
#include <vector>
using std::string;
using std::vector;

constexpr static int SCORE_X = 19;
constexpr static int SCORE_Y = 24;
constexpr static int LIVES_X = 9;
constexpr static int LIVES_Y = 24;
constexpr static int PAUSE_MSG_LINE1_X = 34;
constexpr static int PAUSE_MSG_LINE1_Y = 7;
constexpr static int PAUSE_MSG_LINE2_X = 26;
constexpr static int PAUSE_MSG_LINE2_Y = 8;
constexpr static int GAME_FINISHED_LINE1_X = 0;
constexpr static int GAME_FINISHED_LINE1_Y = 5;
constexpr static int GAME_FINISHED_LINE2_X = 25;
constexpr static int GAME_FINISHED_LINE2_Y = 13;

enum { ROWS = 25, COLS = 80 };

class PacmanGame {
private: 
	enum {ESC = 27};
	Pacman pacman;
	Ghost ghost[4];
	Fruit fruit[2];
	int numGhosts = 0;
	int score;
	int totalBreadCrumbs;
	int eatenBreadCrumbs;
	int lives;
	bool isLoseGame;
	bool isWinGame;
	bool isFileInvalid;
	bool startGhostMove;
	bool startFruitMove;
	int numOfScreens;
	char originalBoard[ROWS][COLS + 1];	
	char board[ROWS][COLS + 1];	
	void handleObjectCreationFromBoard(); 
	void printCreatures();
	void printScoreAndLives();
	void pauseGame();
	
public:
	static int ghostMove;
	PacmanGame();
	void initBoard(); // copy original board to actual board
	void printBoard(); // print to screen the current board
	void printCurrentBoradWithOriginalPosCreatures();
	bool isWall(const Point& p);
	bool isInBorders(const Point& p);
	bool isHitGhost(const Point& p);
	bool isHitPacman(const Point& p);
	bool isHitFruit(int indexFruit, const Point& p);
	void handleStrike();
	void handleFruitAndPacman(int indexFruit);
	void handleFruitAndGhost(int indexFruit);
	void printWin();
	void printGameOver();
	void printLevel(int i);
	void run(); 
	void startNewGame(bool isSingleGame, char ghostType, vector<string>& files, int numOfScreens = 1, string screen = ""); // default number screen 1, and play with 3 screens
	void resetPacmanGameValues();
	void resetCreaturesValuesInLevel(char ghostType);
	void waitForKey();
	void fruitStep(int indexFruit, int modSteps, int& countStepsFruit);
	
	// setters
	void setOriginalBoard(string screen);
	void setScore(int value = 1); //default increase by 1
	void setEatenBreadCrumbs(); // increase by 1
	void setLives(); // decrease by 1
	void setLoseGame(bool res);
	void setWinGame(bool res);
	void setBoardPosition(const Point& p, char c);
	void setNumGhosts(int num);

	// getters
	int getScore() const;
	int getEatenBreadCrumbs() const;
	int getTotalBreadCrumbs() const;
	int getLives() const;
	bool getLoseGame() const;
	bool getWinGame() const;
	char getBoardPosition(const Point& p) const;
	int getNumGhosts() const;
	Point getPacmanPosition() const;
};

#endif