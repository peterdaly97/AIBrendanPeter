#ifndef GAME_H
#define GAME_H

#include "Nest.h"
#include "Player.h"
#include "Worker.h"
#include "grid.h"
#include <iostream>
#include <vector>
#include "ParticleSystem.h"

class grid;

class Game
{
public:
	Game();

	~Game();

	void run();
	void update();
	void checkEntities();
	void render();
	void updateUI();

	Player player = Player();
	sf::RenderWindow m_window;

	std::vector<Nest *> m_nests;
	 
	const int SCREEN_WIDTH = 1200;
	const int SCREEN_HEIGHT = 800;

	Grid* grid;

private:
	sf::Texture m_worldTexture;
	sf::Sprite m_worldSprite;

	sf::View m_miniMap;
	sf::RectangleShape m_mapBorder;

	std::vector<Worker *> m_workers;
	std::vector<Enemy *> m_remainingEnemies;

	sf::Texture m_heartTex;
	sf::Texture m_workerTex;

	sf::Sprite m_heartSprite;
	sf::Sprite m_workerSprite;

	sf::Text m_heartText;
	sf::Text m_workerText;
	sf::Font m_font;

	std::vector<ParticleSystem *> m_particles;
	
};

#endif //!GAME_H
