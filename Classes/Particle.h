#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\Graphics.hpp>
#include <iostream>

class Particle
{
public:
	// Constructor
	Particle(sf::Vector2f pos, int index);

	// Update and render functions
	void update();
	void draw(sf::RenderWindow & window);

	int m_lifetime;	// How long the particle will be alive for
	int m_index;	// The particles index in the particle system

private:
	// Physical attributes of the particle
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::CircleShape m_circle;
	int m_red;
	int m_yellow;
	int m_alpha = 255;
};
#endif // !Particle_H

