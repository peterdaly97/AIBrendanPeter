#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\Graphics.hpp>
#include <iostream>

class Particle
{
public:
	Particle(sf::Vector2f pos, int index);

	void update();

	void draw(sf::RenderWindow & window);
	int m_lifetime;
	int m_index;

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::CircleShape m_circle;
	int m_red;
	int m_alpha = 255;
};
#endif // !Particle_H

