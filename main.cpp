#include <windows.h>
#include <iostream>
#include "Menu.h"

int main() {
	hideCursor();
	srand(time(NULL));
	Menu menu;
	menu.start();
}