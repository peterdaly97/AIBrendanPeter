#include "../Classes/Particle.h"

Particle::Particle(sf::Vector2f pos, int index) : 
	m_position(pos), m_index(index) {

	m_circle = sf::CircleShape(3);
	m_circle.setPosition(m_position);
	m_red = rand() % 55 + 200;
	m_circle.setFillColor(sf::Color(m_red, 0, 0, m_alpha));
	m_lifetime = rand() % 1000;

	m_velocity.x = 6.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0 - 18.1)));
	m_velocity.y = 6.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0 - 18.1)));
}

void Particle::update() {
	m_lifetime--;
	m_alpha = (m_lifetime / 1000) * 255;
	//m_circle.setFillColor(sf::Color(m_red, 0, 0, m_alpha));

	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;
	m_circle.setPosition(m_position);
}

void Particle::draw(sf::RenderWindow & window) {
	window.draw(m_circle);
}
