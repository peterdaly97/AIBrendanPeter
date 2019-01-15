#include "../Classes/Missile.h"

Missile::Missile(sf::Vector2f pos) : m_position(pos) {
	m_speed = 1.5;
	m_texture.loadFromFile("assets/missile.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

}

void Missile::update(sf::Vector2f playerPos, int & health) {

	steer = seek(playerPos);
		
	m_position += steer.linear;
	m_sprite.setPosition(m_position);

	m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed,
		m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed);

	if (dist(playerPos, m_position) < 45) {
		health--;
		m_dead = true;
	}

	m_time += m_clock.restart();
	if (m_time.asSeconds() > 5) {
		m_dead = true;
	}
}


pathing Missile::seek(sf::Vector2f playerPos) {

	m_velocity = playerPos - m_position;
	startCalc();
	m_sprite.setRotation(m_rotation);

	pathing seekSteering;
	seekSteering.linear = m_velocity;
	seekSteering.angular = 0.0;
	return seekSteering;
}

void Missile::render(sf::RenderWindow & window) {

	window.draw(m_sprite);
}

float Missile::getNewRotation(float rot, sf::Vector2f vel) {

	if (mag(m_velocity) > 0.0) {
		float rotation = std::atan2(-m_velocity.x, m_velocity.y) * (180 / 3.14159);
		return (rotation + 90);
	}
	else {
		return rot;
	}

}

float Missile::mag(sf::Vector2f v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}

void Missile::startCalc() {
	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		float magnitude = mag(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x / magnitude, m_velocity.y / magnitude);
		m_velocity = m_velocity * m_speed;
		m_rotation = getNewRotation(m_rotation, m_velocity);
	}

}

float Missile::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}
