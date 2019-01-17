#ifndef WORKER_H
#define WORKER_H

#include "SFML/Graphics.hpp"
#include "Grid.h"

// An enum that has all states the worker can be in
enum act
{
	FLEE,
	WANDER	
};

// A struct that will hold the workers current steering information
struct handling {
	sf::Vector2f linear;
	float angular;
};

class Worker
{
public:
	Worker(act behaviour, sf::Vector2f pos);	// Constructor
	~Worker();	// Deconstructor

	// Update and render functions
	void update(std::vector<Node*> &nodes,int goalNode);
	void render(sf::RenderWindow &window);

	// Function for rendering dot to the mini map
	void renderDot(sf::RenderWindow &window);

	void checkCollision(Grid &grid);	// Checks for collision between the wall and worker
	// Gets new rotation of the worker
	float getNewRotation(float rot, sf::Vector2f vel);
	handling wander();	// Function that handles the worker wandering 

	float mag(sf::Vector2f v);	// Returns magnitude of passed vector
	void startCalc();
	float dist(sf::Vector2f v1, sf::Vector2f v2);	// Returns distance between the passed vectors

	bool m_collected = false;

	// Visual attributes
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	// Physical attributes
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_rotation;
	sf::Vector2f m_targetPos;
	const double DEG_TO_RAD = 3.14159 / 180.0f;
	const double RAD_TO_DEG = 180.0f / 3.14159;
	float m_speed;
	float MAX_FORWARD_SPEED = 2.5;
	const float MAX_ROTATION = 30;
	const float MAX_BACKWARD_SPEED = 2.5;
	const float TIME_TO_TARGET = 80.0f;

	bool magnet = false;	// If the worker is moving towards the player
	void move(double vectorX, double vectorY);	// Function handles moving the worker

	int tempGrid = 999999;
	bool gridChanged = false;

private:
	act b;
	float m_angleDev = 0.0f;
	float m_changeAngle = 1.0f;
	handling steer;

	int playerGrid = 0;
	int playerGridX = 0;
	int playerGridY = 0;
};
#endif // !WORKER_H

