#include "../Classes/Bullet.h"

/// <summary>
/// Bullet constructor which will initialise the bullet
/// </summary>
/// <param name="pos"></param>
/// <param name="rot"></param>
/// <param name="tex"></param>
Bullet::Bullet(sf::Vector2f pos, float rot, sf::Texture & tex) : m_pos(pos), m_rot(rot) {
	m_speed = 15;	// Sets bullet speed

	// Sets up visual properties of the bullet
	m_sprite.setTexture(tex);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

	m_lifeTime = 0;	// Sets current lifetime of bullet

	// Assign position and rotation of bullet
	m_sprite.setPosition(m_pos);
	m_sprite.setRotation(m_rot);
}

/// <summary>
/// Function for updating the bullet
/// </summary>
void Bullet::update() {
	// Updates position of bullet 
	m_impulse = sf::Vector2f(std::cos(DEG_TO_RAD  * (m_rot)) * m_speed,
		std::sin(DEG_TO_RAD * (m_rot)) * m_speed);
	m_pos += m_impulse;

	m_lifeTime++;	//Increment bullets lifetime	
	m_sprite.setPosition(m_pos);
}

/// <summary>
/// Function that handles the rendering of the bullet
/// </summary>
/// <param name="window"></param>
void Bullet::render(sf::RenderWindow & window) {
	window.draw(m_sprite); // Draws bullet
}
