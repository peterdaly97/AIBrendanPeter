#ifndef NEST_H
#define NEST_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include "Enemy.h"

class Nest
{
public:
	Nest(sf::Vector2f pos);

	~Nest();

	void update();
	void render(sf::RenderWindow &window);
	void spawn();
	void loseHealth();


	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Texture m_enemyTex;

	sf::Vector2f m_position;

	int m_health;
private:
	std::vector<Enemy *> m_enemies;
	const int SPAWN_NEXT = 100;
	int m_spawnTimer;

};

#endif //!NEST_H