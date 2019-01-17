#include <iostream>
#include "..\Classes\game.h"

// Entry point for the program
int main() {
	Game* game = new Game();	// Instantiate a game object
	game->run();	// Run the game

	return 0;
}