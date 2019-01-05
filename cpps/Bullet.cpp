#include "../Classes/Bullet.h"

Bullet::Bullet(sf::Vector2f pos, float rot) : m_pos(pos), m_rot(rot) {
	m_speed = 15;
	m_tex.loadFromFile("assets/bullet.png");
	m_sprite.setTexture(m_tex);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);


	m_lifeTime = 0;

	m_sprite.setPosition(m_pos);
	m_sprite.setRotation(m_rot);
}

void Bullet::update() {
	m_impulse = sf::Vector2f(std::cos(DEG_TO_RAD  * (m_rot)) * m_speed,
		std::sin(DEG_TO_RAD * (m_rot)) * m_speed);
	m_pos += m_impulse;

	m_lifeTime++;
	m_sprite.setPosition(m_pos);
}

void Bullet::render(sf::RenderWindow & window) {

	window.draw(m_sprite);
}
