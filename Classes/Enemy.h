#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Player.h"

// An enum that has all states the enemy can be in
enum behaviour
{
	EVADE,
	PATROL,
	SEEK
};

// A struct that will hold the enemies current steering information
struct steering { 
	sf::Vector2f linear; 
	float angular; 
};

class Enemy
{
public:
	// Constructor
	Enemy(behaviour behaviour, sf::Vector2f pos, float maxSpeed, sf::Texture * tex);

	~Enemy();	// Destructor


	void update(sf::Vector2f playerPos, sf::Vector2f playerVel);	// Update function
	void render(sf::RenderWindow &window);	// Render function

	// Function fo rendering dot on minimap at enemies position
	void renderEnemyDot(sf::RenderWindow &window);	

	// Function that updates enemies rotation
	float getNewRotation(float rot, sf::Vector2f vel);

	// Three functions that handle enemy movement based on their behaviour
	steering wander();
	steering seek(sf::Vector2f playerPos);
	steering flee(sf::Vector2f playerPos);


	float mag(sf::Vector2f v);	// Math function for calculating magniude of a vector

	void startCalc();	// Function to calculate velocity and call other move functions

	float dist(sf::Vector2f v1, sf::Vector2f v2);	// Calculates distance between 2 vectors
	bool lookFor(std::vector<Worker *> enemies);	// Function looks for workers in line of sight

	// Visual attributes of enemy
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	// Physical attributes of enemy
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_rotation;
	sf::Vector2f * m_targetPos = new sf::Vector2f();
	const double DEG_TO_RAD = 3.14159 / 180.0f;
	const double RAD_TO_DEG = 180.0f / 3.14159;
	float m_speed;
	float MAX_FORWARD_SPEED = 2.5;
	const float MAX_ROTATION = 45;
	const float MAX_BACKWARD_SPEED = 2.5;
	const float TIME_TO_TARGET = 80.0f;

	void checkCollision(Grid &grid);	// Function for checking enemy against all the walls
	void checkPlayer(sf::Vector2f playerPos);	// Function checks if player is near

	bool m_dead = false;	// Whether enemy is dead or not

	int tempGrid = 999999;
	bool gridChanged = false;

	int m_collected = 0;	// How many workers the enemy has collected

private:
	behaviour b;	// Behaviour of enemy

	float m_detectedColl = 0.0f;

	float m_angleDev = 0.0f;
	float m_changeAngle = 1.0f;
	steering steer;	// Current steering of player


	int playerGrid = 0;
	int playerGridX = 0;
	int playerGridY = 0;
};

#endif //!Enemy_H

