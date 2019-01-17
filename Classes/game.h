#ifndef GAME_H
#define GAME_H

#include "Nest.h"
#include "Player.h"
#include "Worker.h"
#include "grid.h"
#include <iostream>
#include <vector>
#include "ParticleSystem.h"
#include "PowerUp.h"

// Referencing grid before compiling
class grid;

class Game
{
public:
	Game();

	~Game();

	void run();
	void update();
	void checkEntities();	// Function to monitor the updating of all entities
	void render();
	void updateUI();	// Updates UI on screen

	Player player = Player();	// Declaring the user controlled player
	sf::RenderWindow m_window;

	std::vector<Nest *> m_nests;	// The vector containing all nests in game
	 
	const int SCREEN_WIDTH = 1200;
	const int SCREEN_HEIGHT = 800;

	// Current and max amount of predators
	int predCount = 0;
	int predMax = 15;

	Grid* grid;	// Our grid object

private:
	sf::Texture m_worldTexture;
	sf::Sprite m_worldSprite;

	sf::View m_miniMap;
	sf::RectangleShape m_mapBorder;

	std::vector<Worker *> m_workers;	// The vector containing all workers in game
	std::vector<Enemy *> m_remainingEnemies;	// The vector containing all enemies not being updates by nests
	
	std::vector<PowerUp *> m_powerUps; // The vector containing all power ups in game
	sf::Texture m_powerTex;
	sf::Texture m_blastTex;
	sf::Texture m_healthTex;

	sf::Texture m_heartTex;
	sf::Texture m_workerTex;

	sf::Sprite m_heartSprite;
	sf::Sprite m_workerSprite;

	sf::Text m_heartText;
	sf::Text m_workerText;
	sf::Font m_font;

	std::vector<ParticleSystem *> m_particles; // The vector containing all particles in game
	sf::Texture m_bulletTex;

	// Bools for the win and lose conditions
	bool m_win = false;
	bool m_lose = false;

	int m_totalWorkers = 1;	// Total number of workers in game

	sf::Texture m_winTex;
	sf::Sprite m_winSprite;
	sf::Texture m_loseTex;
	sf::Sprite m_loseSprite;
};

#endif //!GAME_H
