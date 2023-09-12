
Pacman Game supports: 
1. A full game - option 1 in the main menu. 
We're loading all available screens from the project's folder of files with a name that ends with "screen" (for example, "pacman_01.screen"...). We sort all the screens in lexigoraphical order, and start the full game from the first screen and run it until the final screen (unless the user loses).

2. A single game - option 2 in the main menu. 
The user is given an option to enter a file name that's located in the project's folder, and play that screen. Only this screen is available, so the game stops after it. 
If the screen is not found, an error will be presented and the main menu will appear again.

3. Ghosts setting - after the user chooses a game (full or single level), the user should choose the ghost's level:
	a) BEST
	b) GOOD
	c) NOVICE
After choosing Ghost setting the game will run with the same setting the whole game.
Also, We support 0-4 number of ghosts.

4. Fruits - during a game, we're adding multiple fruits that appear in random positions in the screen. The fruits appear and disappear randomly during the game. The fruit's value is chosen randomly from 5-9.
if Pacman eats the fruit, he gets the scores value in the fruit.
if ghost eats the fruit, the fruit will dissapear with no additions points to the score.
moreover, the fruit will appear again even if it was eaten by a player in random times.

5. files - we added 3 screens in the project folder:
pacman_a.screen
pacman_b.screen
pacman_c.screen

