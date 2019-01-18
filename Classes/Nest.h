#ifndef NEST_H
#define NEST_H

#include "Enemy.h"
#include "Missile.h"

class Nest
{
public:
	Nest(sf::Vector2f pos);	// Constructor

	~Nest();	// Destructor

	// Update function
	void update(sf::Vector2f playerPos, int & heath, std::vector<ParticleSystem *> & ps, Grid &grid, std::vector<Worker *> wpos);
	void render(sf::RenderWindow &window);	// Render function
	void renderDot(sf::RenderWindow &window);	// Function for rendering dots to the minimap

	void spawn();	// Function for spawning sweeper bots
	int spawnPredator();	// Function for spawning predators

	int predSpawnTimer = 0;	// Timer between predator spawns

	void loseHealth(int & score);	// Function called when nest hit by player bullet

	void addMissile();	// Function to fire missile at player

	// Visual attributes 
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Texture m_enemyTex;

	// Physical attributes
	sf::Vector2f m_position;

	int m_health;	// Health of the nest

	bool m_dead = false;	// Whether or not the nest is dead

	std::vector<Enemy *> m_enemies;	// The nests vector of enemies
	std::vector<Missile *> m_missiles;	// The nests vector of missiles
private:
	
	const int SPAWN_NEXT = 100;	// Time that has to pass before next predator spawn
	int m_spawnTimer; // Timer for sweeper spawns
};

#endif //!NEST_H