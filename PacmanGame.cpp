#include "PacmanGame.h"
#include <limits>

using std::cout;
using std::endl;
using std::ifstream;
using std::filesystem::path;

int PacmanGame::ghostMove = 0;
// Pacman game ctor
PacmanGame::PacmanGame() : pacman(this, "wxads"), ghost{ {this, Point()}, {this, Point()}, {this, Point()}, {this, Point()} }, fruit{ { this, 0 }, { this, 1 } }{
}

// Function gets the original board number and update the orig board in pacman object
void PacmanGame::setOriginalBoard(string screen)
{
	char c;
	numGhosts = 0;

	ifstream boardFile(screen);
	// if file is opened successfuly
	if (boardFile.is_open()) {
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				c = boardFile.get();

				if (c == '@') {
					pacman.setOriginalPosition(j, i);
					c = '.';
				}
				else if (c == '$') {
					ghost[numGhosts].setOriginalPosition(j, i);
					numGhosts++;
					c = '.';
				}
				else if (c == '%')
					c = ' ';
			
				originalBoard[i][j] = c;
			}
			boardFile.get(); // skip \n every line
			originalBoard[i][COLS] = '\0';
		}
		boardFile.close();
	}

	else {
		isFileInvalid = true;
	}
}

// Function reset creatures values in between level in full game mode
void PacmanGame::resetCreaturesValuesInLevel(char ghostType) {
	isLoseGame = false;
	isWinGame = false;
	isFileInvalid = false;
	totalBreadCrumbs = 0;
	eatenBreadCrumbs = 0;

	// reset creature values per level
	fruit[0].setIsInBoard(false);
	fruit[1].setIsInBoard(false);

	for (int i = 0; i < numGhosts; i++)
	{
		ghost[i].setGhostType(ghostType);
	}
}

// Function initiate pacman and ghosts in the game and print all the board to screen
void PacmanGame::initBoard()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			// save num of bread crumbs for win check
			if (originalBoard[i][j] == '.') 
				totalBreadCrumbs++;

			gotoxy(j, i);
			cout << originalBoard[i][j];
			cout.flush();
			board[i][j] = originalBoard[i][j];
		}
		board[i][COLS] = '\0';
	}
	
	handleObjectCreationFromBoard();
	printCreatures();
	printScoreAndLives();
}

// Function Prints the current board
void PacmanGame::printBoard() {
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			cout << board[i][j];
			cout.flush();
		}
	}

	printCreatures();
	printScoreAndLives();
}

// Function gets all orignal position for all cretrues
void PacmanGame::handleObjectCreationFromBoard()
{
	int x, y;
	// set packman on board and update current position
	x = pacman.getOriginalPosition().getX();
	y = pacman.getOriginalPosition().getY();
	pacman.setPosition(x, y);

	// set all ghosts on board and update current position
	for (int i = 0; i < numGhosts; i++)
	{
		x = ghost[i].getOriginalPosition().getX();
		y = ghost[i].getOriginalPosition().getY();
		ghost[i].setPosition(x, y);
	}
	
}

// function prints all creatures to the screen
void PacmanGame::printCreatures() {
		pacman.getPosition().draw('@');

		for (int i = 0; i < numGhosts; i++)
		{
			ghost[i].getPosition().draw('$');
		}
}

// function prints score and lives to the screen
void PacmanGame::printScoreAndLives() {
	// print score and lives
	gotoxy(LIVES_X, LIVES_Y);
	cout << getLives();
	gotoxy(SCORE_X, SCORE_Y);
	cout << getScore();
}

// function reset cretures piositions to original pos and print curre board
void PacmanGame::printCurrentBoradWithOriginalPosCreatures() {
	handleObjectCreationFromBoard();
	printBoard();
}

// function start a new game
void PacmanGame::startNewGame(bool isSingleGame, char ghostType, vector<string>& files, int numOfScreens, string screen) {
	int i = 0;
	isFileInvalid = false;
	isLoseGame = false;
	isWinGame = false;

	// if only one screen while will run only one time
	// numOfScreens is 1 or 3
	while((i < numOfScreens) && (!isLoseGame)){
		clear_screen();

		// if singel game - use free txt from user
		// else run on full list of pacman screens
		if(isSingleGame)
			setOriginalBoard(screen);
		// full game
		else {
			setOriginalBoard(files[i]);
			// in full game mode print in between levels message to user
			printLevel(i + 1);
		}
		
		// in case of issues with loading the screen - isFileInvalid changed to true
		// if file is ok set the board and run the game
		if(!isFileInvalid){
			// in the first game - reset all values for the new game
			if (i == 0) {
				resetPacmanGameValues();
			}
			resetCreaturesValuesInLevel(ghostType);
			initBoard();
			run();
		}
		i++;
	}

	if (isLoseGame)
		printGameOver();
	else if (isFileInvalid) {
		cout << "File is not found, please try again" << endl << endl;
		cout << "Press any key to go to the menu" << endl;
		waitForKey();
	}
	else 
		printWin();
}

// reset all values for new game
void PacmanGame::resetPacmanGameValues(){
	// reset all data members for the first game
	score = 0;
	lives = 3;
}

// run a new game
void PacmanGame::run()
{
	char key = 0;
	int dir;
	int countStepsPacman = 0; // every 10 steps need to randomaized the ghosts directions
	PacmanGame::ghostMove = 0;
	int countStepsFruit = 0;
	
	// set ghost and pacman stay every start of the game
	startGhostMove = false;
	startFruitMove = false;
	pacman.setDirection(4);

	do
	{
		if (_kbhit()) 
		{
			key = _getch();

			if (key == ESC) {
				pauseGame();
			}

			// to support upper case letters W A D X S
			else {
				key = tolower(key);
			}

			if ((dir = pacman.getDirection(key)) != -1) {
				pacman.setDirection(dir);

				startGhostMove = true;
				startFruitMove = true;
			}
		}

		// Fruit move
		if(startFruitMove){
			fruitStep(0, 30, countStepsFruit);
			fruitStep(1, 40, countStepsFruit);

			countStepsFruit++;
		}

		// Pacman move
		pacman.move();
		countStepsPacman++;

		// Ghosts moves
		// make sure no change in direction at the start of the game
		// and the game is still running
		if((!isLoseGame && !isWinGame) && (startGhostMove)){
			 
			// make ghosts move slower by 2 from pacman
			if (PacmanGame::ghostMove % 2 == 0) {

				for (int i = 0; ((i < numGhosts) && (!isLoseGame) && (!isWinGame)); i++)
				{
					ghost[i].move();
				}
			}
			PacmanGame::ghostMove++;
		}

		Sleep(300);
	} while (!isLoseGame && !isWinGame);
}

// Function update fruit moves according to modSteps and if needed initiate new fruit
void PacmanGame::fruitStep(int indexFruit, int modSteps, int& countStepsFruit) {
	// turn on fruit to appear in screen
	if ((countStepsFruit % modSteps == 0) && !fruit[indexFruit].getIsInBoard()) {
		fruit[indexFruit].init(); // set isInBoard ture and generate all data members
	}

	// turn off fruit from screen
	else if ((countStepsFruit % (modSteps + 20) == 0) && fruit[indexFruit].getIsInBoard()) {
		fruit[indexFruit].setIsInBoard(false);
		// get the char in board in curr position and print (ghost don't eat breadcrumb)
		char currPos = getBoardPosition(fruit[indexFruit].getPosition());
		fruit[indexFruit].getPosition().draw(currPos);
	}

	// run anyway
	if ((!isLoseGame && !isWinGame) && (fruit[indexFruit].getIsInBoard())) {
		if (countStepsFruit % 5 == 0) {
			fruit[indexFruit].move();
		}
	}
}


// function calculate if the point is a wall in the board
bool PacmanGame::isWall(const Point& p) {
	return (board[p.getY()][p.getX()] == '#');
}

// function calculate if the point is a border in the board
bool PacmanGame::isInBorders(const Point& p) {
	return ((p.getX() == 0) ||
			(p.getX() == 79)||
			(p.getY() == 0) ||
			(p.getY() == 23));
}

// Function geta next position and check if any ghosts are in poistion
bool PacmanGame::isHitGhost(const Point& p) {
	bool resIsHit = false;
	for (int i = 0; ((i < numGhosts) && !resIsHit); i++)
	{
		resIsHit = (ghost[i].getPosition().getX() == p.getX()) && (ghost[i].getPosition().getY() == p.getY());
	}
	return resIsHit;
}

// get next position and check if pacman is in poistion
bool PacmanGame::isHitPacman(const Point& p) {
	return  (pacman.getPosition().getX() == p.getX()) && (pacman.getPosition().getY() == p.getY());
}

// get next position and check if fruit is in position
bool PacmanGame::isHitFruit(int indexFruit, const Point& p) {
	return ((fruit[indexFruit].getPosition().getX() == p.getX()) &&
			(fruit[indexFruit].getPosition().getY() == p.getY()));
}

// after losing 1 round need to set lives and end game if needed
void PacmanGame::handleStrike() {
	// if lives > 1 return orig position
	if (getLives() > 1) {
		setLives(); // -- lives

		// delete all screen
		clear_screen();
		// print original positions for all creatures with new lives count
		printCurrentBoradWithOriginalPosCreatures();
		// set all crea
		pacman.setDirection(STAY);
		startGhostMove = false;
		startFruitMove = false;
	}

	// else live = 0 GAME OVER
	else {
		setLoseGame(true);
	}
}

// if pacman hit fruit or fruit hit pacman need to get the score and update fruit status
void PacmanGame::handleFruitAndPacman(int indexFruit) {
	setScore(fruit[indexFruit].getValue());
	fruit[indexFruit].setIsInBoard(false);
}

// if ghost hit fruit or fruit hit ghost need to get the score and update fruit status
void PacmanGame::handleFruitAndGhost(int indexFruit) {
	fruit[indexFruit].setIsInBoard(false);
}

// print game over to the screen
void PacmanGame::printGameOver(){
	// delete all screen
	clear_screen();
	gotoxy(GAME_FINISHED_LINE1_X, GAME_FINISHED_LINE1_Y);
	cout << " ######      ###    ##     ## ########     #######  ##     ## ######## ########  " << endl;
	cout << "##    ##    ## ##   ###   ### ##          ##     ## ##     ## ##       ##     ## " << endl;
	cout << "##         ##   ##  #### #### ##          ##     ## ##     ## ##       ##     ## " << endl;
	cout << "##   #### ##     ## ## ### ## ######      ##     ## ##     ## ######   ########  " << endl;
	cout << "##    ##  ######### ##     ## ##          ##     ##  ##   ##  ##       ##   ##   " << endl;
	cout << "##    ##  ##     ## ##     ## ##          ##     ##   ## ##   ##       ##    ##  " << endl;
	cout << " ######   ##     ## ##     ## ########     #######     ###    ######## ##     ## " << endl;

	gotoxy(GAME_FINISHED_LINE2_X, GAME_FINISHED_LINE2_Y);
	cout << "Press any key to go to the menu" << endl << endl;
	waitForKey();
}
// print message before starting the leve
void PacmanGame::printLevel(int i) {
	clear_screen();
	gotoxy(PAUSE_MSG_LINE1_X, PAUSE_MSG_LINE1_Y);
	cout << "Get ready to LEVEL " << (i) << endl << endl;
	gotoxy(PAUSE_MSG_LINE1_X - 1, PAUSE_MSG_LINE1_Y + 1);
	cout << "Press any key to start" << endl << endl;

	waitForKey();
}
// After wining the game, function prints on the screen winner 
void PacmanGame::printWin() {
	// delete all screen
	clear_screen();
	gotoxy(GAME_FINISHED_LINE1_X, GAME_FINISHED_LINE1_Y);

	cout << "##      ## #### ##    ## ##    ## ######## ########   ##\n";
	cout << "##  ##  ##  ##  ###   ## ###   ## ##       ##     ##  ##\n";
	cout << "##  ##  ##  ##  ####  ## ####  ## ##       ##     ##  ##\n";
	cout << "##  ##  ##  ##  ## ## ## ## ## ## ######   ########   ##\n";
	cout << "##  ##  ##  ##  ##  #### ##  #### ##       ##   ##    ##\n";
	cout << "##  ##  ##  ##  ##   ### ##   ### ##       ##    ##   \n";
	cout << " ###  ###  #### ##    ## ##    ## ######## ##     ##  ##\n";

	gotoxy(GAME_FINISHED_LINE2_X - 17, GAME_FINISHED_LINE2_Y);
	cout << "Press any key to go to the menu" << endl << endl;
	waitForKey();
}

// function paused the game until user press any key
void PacmanGame::waitForKey() {
	bool isGamePaused = true;
	// waite to get any key
	while (isGamePaused) {
		if (_kbhit())
		{
			isGamePaused = false;
		}
	}
}

// function set score plus 1
void PacmanGame::setScore(int value) {
	score += value;
}
// function set eaten bread crumbs plus 1
void PacmanGame::setEatenBreadCrumbs() {
	eatenBreadCrumbs++;
}

// function set lives minus 1
void PacmanGame::setLives() {
	lives--;
}
// function get score
int PacmanGame::getScore() const{
	return score;
}

// function get eaten brad crumbs
int PacmanGame::getEatenBreadCrumbs() const{
	return eatenBreadCrumbs;
}

// function get total bread crumbs numbers
int PacmanGame::getTotalBreadCrumbs() const{
	return totalBreadCrumbs;
}

// function get Lives
int PacmanGame::getLives() const{
	return lives;
}

// Function return the value of isLoseGame
bool PacmanGame::getLoseGame() const{
	return isLoseGame;
}
// Function return the value of isWinGame
bool PacmanGame::getWinGame() const{
	return isWinGame;
}
// Function set value in isLoseGame
void PacmanGame::setLoseGame(bool res) {
	isLoseGame = res;
}
// Function set value in isWinGame
void PacmanGame::setWinGame(bool res) {
	isWinGame = res;
}

// function set Board Position
void PacmanGame::setBoardPosition(const Point& p, char c) {
	board[p.getY()][p.getX()] = c;
}

// function get Board Position
char PacmanGame::getBoardPosition(const Point& p) const{
	return board[p.getY()][p.getX()];
}

// function pause the game
void PacmanGame::pauseGame() {
	bool isGamePaused = true;
	char key = 0;

	// clear the screen and print GAME PAUSED
	clear_screen();
	gotoxy(PAUSE_MSG_LINE1_X, PAUSE_MSG_LINE1_Y);
	cout << "GAME PAUSED";
	gotoxy(PAUSE_MSG_LINE2_X, PAUSE_MSG_LINE2_Y);
	cout << "press ESC again to continue";

	while (isGamePaused) {
		if (_kbhit())
		{
			key = _getch();

			if (key == ESC) {
				isGamePaused = false;
			}
		}
	}
	printBoard();
}

void PacmanGame::setNumGhosts(int num) {
	numGhosts = num;
}

int PacmanGame::getNumGhosts() const{
	return numGhosts;
}

Point PacmanGame::getPacmanPosition() const {
	return pacman.getPosition();
}