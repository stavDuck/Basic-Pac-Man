#include "Menu.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <algorithm>
namespace fs = std::filesystem;

using std::vector;

using std::cout;
using std::cin;
using std::endl;

Menu::Menu() : game(){}

// start Pacmnam game
void Menu::start() {
	bool isGameRunning = true;
	char userChoice;
	char ghostType;
	string screen;

	// get file list
	vector<string> files;
	listdir(".", files, "screen");
	sort(files.begin(), files.end());

	if (files.size() > 0) {
		while (isGameRunning) {
			printPacmanStartMenu();
			cin >> userChoice;

			switch (userChoice)
			{
			case START_FULL_GAME:
				ghostType = chooseGhost();
				game.startNewGame(false, ghostType, files, files.size());
				break;
			case START_SINGLE_GAME:
				ghostType = chooseGhost();
				screen = chooseScreen();
				game.startNewGame(true, ghostType, files, 1, screen);
				break;
			case INSTRUCTION_AND_KEYS:
				instructionAndKeys();
				break;
			case EXIT:
				isGameRunning = false;
				break;
			default:
				cout << "invalid choice, please try again" << endl;
				break;
			}
		}
	}

	// no files in the game folder
	else {
		cout << "Error ! No files found";
	}
}

// print the instuction and keys information to the user on the screen
void Menu::instructionAndKeys() {
	//bool isGamePaused = true;
	clear_screen();

	cout << "Instructions and Keys" << endl;
	cout << "*********************" << endl << endl;

	// print instruction and keys
	cout << "1. Start the Game: Launch the Pacman game by choosing full game or a single level" << endl;
	cout << "2. Understand the game: The objective of Pacman is to guide the '@' character (Pacman) through a maze, eating all the breadcrumbs while avoiding the ghosts. The player loses a life if Pacman comes in contact with a ghost." << endl;
	cout << "3. Learn the controls: Use these keys to move : 'a' or 'A' - move left, 'd' or 'D' - move right, 'w' or 'W' - move up, 'x' or 'X' - move down, 's' or 'S'- stay (dont move)." << endl;
	cout << "4. Collect breadcrumbs and fruits: Move Pacman around the maze to collect all the breadcrumbs. Each breadcrumb is worth one point. Occasionally, fruits will appear. If the Pacman eats the fruits, it will receive 5 to 9 points - depends on the fruit's value." << endl;
	cout << "5. Avoid the ghosts : The ghosts are the enemy in Pacman. There can be 0 to 4 ghosts('$' character), they move throughout the maze and will try to catch Pacman. If Pacman comes in contact with a ghost, he will lose a life." << endl;
	cout << "6. Clear the board: The game is finished once all the breadcrumbs have been eaten." << endl;
	cout << "7. Keep track of lives and score: The player starts with three lives. Each time Pacman loses a life, the game will restart at the beginning of the current level. Keep track of the score, as the goal is to get as many points as possible." << endl;
	cout << "That's it! Enjoy playing Pacman!" << endl << endl;
	cout << "Enter any key to return to the menu" << endl;
	game.waitForKey();
	clear_screen();
}

// print the logo and the main menu of the game
void Menu::printPacmanStartMenu() {
	printPacmanLogo();

	cout << "Welcome, please select one of the options:" << endl;
	cout << "1) Start a full game" << endl;
	cout << "2) Start a single level" << endl;
	cout << "8) Present instructions and keys" << endl;
	cout << "9) EXIT" << endl;
}

// Pring pacman logo
void Menu::printPacmanLogo() {
	clear_screen();

	cout << "$$$$$$$$\\  $$$$$$\\   $$$$$$\\  $$\\      $$\\  $$$$$$\\  $$\\   $$\\ " << endl;
	cout << "$$  __$$\\ $$  __$$\\ $$  __$$\\ $$$\\    $$$ |$$  __$$\\ $$$\\  $$ |" << endl;
	cout << "$$ |  $$ |$$ /  $$ |$$ /  \\__|$$$$\\  $$$$ |$$ /  $$ |$$$$\\ $$ |" << endl;
	cout << "$$$$$$$  |$$$$$$$$ |$$ |      $$\\$$\\$$ $$ |$$$$$$$$ |$$ $$\\$$ |" << endl;
	cout << "$$  ____/ $$  __$$ |$$ |      $$ \\$$$  $$ |$$  __$$ |$$ \\$$$$ |" << endl;
	cout << "$$ |      $$ |  $$ |$$ |  $$\\ $$ |\\$  /$$ |$$ |  $$ |$$ |\\$$$ |" << endl;
	cout << "$$ |      $$ |  $$ |\\$$$$$$  |$$ | \\_/ $$ |$$ |  $$ |$$ | \\$$ |" << endl;
	cout << "\\__|      \\__|  \\__| \\______/ \\__|     \\__|\\__|  \\__|\\__|  \\__|" << endl << endl << endl;

}

// Print screen menu
void Menu::printScreensMenu() {
	printPacmanLogo();

	cout << "Please enter the full name of the file:" << endl;
}

// print Ghost type menu
void Menu::printGhostsTypeMenu() {
	printPacmanLogo();

	cout << "Please select a ghost type:" << endl;
	cout << "a) Smart - Hard" << endl;
	cout << "b) Good - Medium" << endl;
	cout << "c) Novice - Easy" << endl;
}

// Function get ghost from user
char Menu::chooseGhost() {
	bool isValidChoice = false;
	char userChoice;

	printGhostsTypeMenu();
	while (!isValidChoice) {
		cin >> userChoice;
		userChoice = tolower(userChoice);

		if (userChoice == 'a' || userChoice == 'b' || userChoice == 'c')
			isValidChoice = true;
		else
			cout << "Invalid choice, try again." << endl;
	}
	return userChoice;	
}

// Function get file name as string and return it
string Menu::chooseScreen() {
	string fileName;
	printScreensMenu();
	cin >> fileName;
	return fileName;
}

// Helper function to crate a list of screen files
bool Menu::has_ending(std::string const& fullString, std::string const& ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

// Helper function to crate a list of screen files
void Menu::listdir(const string& path, vector<string>& files, const string& suffix) {
	for (const auto& entry : fs::directory_iterator(path)) {
		string entryStr = entry.path().string();

		if (has_ending(entryStr, suffix)) {
			files.push_back(entryStr);
		}
	}
}