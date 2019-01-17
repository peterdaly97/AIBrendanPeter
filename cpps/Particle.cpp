#include "../Classes/Particle.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="pos"></param>
/// <param name="index"></param>
Particle::Particle(sf::Vector2f pos, int index) : 
	m_position(pos), m_index(index) {
	
	m_circle = sf::CircleShape(3);
	m_circle.setPosition(m_position);

	// Make red and yellow random to make circle more unique
	m_red = rand() % 55 + 200;
	m_yellow = rand() % 200;
	m_circle.setFillColor(sf::Color(m_red, m_yellow, 0, m_alpha));

	m_lifetime = rand() % 75;	// Make each particle have a random lifetime

	// Give each circle a random velocity
	m_velocity.x = 6.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0 - 18.1)));
	m_velocity.y = 6.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0 - 18.1)));
	
}

/// <summary>
/// Function that updates the particles 
/// </summary>
void Particle::update() {
	m_lifetime--;	// Decrements lifetime

	// Sets alpha based on lifetime so particle will slowly fade out
	m_circle.setFillColor(sf::Color(m_red, m_yellow, 0, m_lifetime));

	// Update position of particle
	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;
	m_circle.setPosition(m_position);
}

/// <summary>
/// Function for rendering the particle
/// </summary>
/// <param name="window"></param>
void Particle::draw(sf::RenderWindow & window) {
	window.draw(m_circle);	// Draw particle
}
