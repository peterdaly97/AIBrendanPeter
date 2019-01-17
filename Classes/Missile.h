#ifndef MISSILE_H
#define MISSILE_H

#include <SFML/Graphics.hpp>
#include <iostream>

// Struct that handles the physical properties of the missile
struct pathing {
	sf::Vector2f linear;
	float angular;
};

class Missile
{
public:
	Missile(sf::Vector2f pos);	// Constructor
	~Missile() {}	// Deconstructor

	// Update and render functions
	void update(sf::Vector2f playerPos, int & health);
	void render(sf::RenderWindow &window);

	float getNewRotation(float rot, sf::Vector2f vel);	// Function for updating missile rotation
	pathing seek(sf::Vector2f playerPos);	// Function for seeking the player

	float mag(sf::Vector2f v);	// Function that calculates the magnitude of a vector
	void startCalc();	// Function for calling all movement functions

	// Function that calculates the distance between 2 vectors
	float dist(sf::Vector2f v1, sf::Vector2f v2);

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
	float MAX_FORWARD_SPEED = 3.0;
	const float MAX_ROTATION = 45;

	bool m_dead = false;	// Whether or not the missile is alive
private:
	// Time and clock for checking how long missile has been alive
	sf::Time m_time;
	sf::Clock m_clock;

	pathing steer; // Steering of the missile
};
#endif // !MISSILE_H

