#ifndef _MENU_H_
#define _MENU_H_
#include "PacmanGame.h"

class Menu {
private:
	constexpr static char START_FULL_GAME = '1';
	constexpr static char START_SINGLE_GAME = '2';
	constexpr static char INSTRUCTION_AND_KEYS = '8';
	constexpr static char EXIT = '9';
	PacmanGame game;
	void instructionAndKeys();
	void printPacmanStartMenu();
	void printPacmanLogo();
	void printScreensMenu();
	void printGhostsTypeMenu();
	char chooseGhost();
	string chooseScreen();
	bool has_ending(std::string const& fullString, std::string const& ending);
	void listdir(const string& path, std::vector<string>& files, const string& suffix);


public:
	Menu();
	void start();
};
#endif
