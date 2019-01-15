#ifndef NEST_H
#define NEST_H

#include "Enemy.h"
#include "Missile.h"

class Nest
{
public:
	Nest(sf::Vector2f pos);

	~Nest();

	void update(sf::Vector2f playerPos, int & heath, std::vector<ParticleSystem *> & ps);
	void render(sf::RenderWindow &window);
	void renderDot(sf::RenderWindow &window);
	void spawn();
	void loseHealth();

	void addMissile();

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Texture m_enemyTex;

	sf::Vector2f m_position;

	int m_health = 3;

	bool m_dead = false;

	std::vector<Enemy *> m_enemies;
	std::vector<Missile *> m_missiles;
private:
	
	const int SPAWN_NEXT = 100;
	int m_spawnTimer;

};

#endif //!NEST_H