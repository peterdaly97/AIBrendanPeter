#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Nest.h"
#include "Worker.h"
#include <iostream>
#include <vector>

class Game
{
public:
	Game();

	~Game();

	void run();
	void update();
	void render();


	Player player = Player();
	sf::RenderWindow m_window;

	Nest nest = Nest(sf::Vector2f(300,-200));
	 
	const int SCREEN_WIDTH = 1200;
	const int SCREEN_HEIGHT = 800;

private:
	sf::Texture m_worldTexture;
	sf::Sprite m_worldSprite;

	sf::View m_miniMap;
	sf::RectangleShape m_mapBorder;

	std::vector<Worker *> m_workers;
};

#endif //!GAME_H
