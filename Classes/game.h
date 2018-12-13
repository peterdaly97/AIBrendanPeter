#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "Player.h"

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

private:
	sf::Texture m_worldTexture;
	sf::Sprite m_worldSprite;
};

#endif //!GAME_H
