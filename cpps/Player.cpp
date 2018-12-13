#include "..\Classes\Player.h"

Player::Player()
{
	m_texture.loadFromFile("assets/ship.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.5, 0.5);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

	m_position = sf::Vector2f(300, 100);
	m_velocity = sf::Vector2f(0, 0);
	m_sprite.setPosition(m_position);
	m_rotation = 0;
	m_speed = 0;
	m_view.setSize(1920, 1080);
}



Player::~Player()
{
}

void Player::update()
{
	handleInput();
	move();
}

void Player::handleInput() {
	if (m_keys.isKeyPressed(sf::Keyboard::Up))
	{
		if (m_speed < MAX_FORWARD_SPEED)
			m_speed += 0.15;
	}
	if (m_keys.isKeyPressed(sf::Keyboard::Down))
	{
		if (m_speed > MAX_BACKWARD_SPEED)
			m_speed -= 0.05;
	}
	if (m_keys.isKeyPressed(sf::Keyboard::Left))
	{
		m_rotation -= 3;
	}
	if (m_keys.isKeyPressed(sf::Keyboard::Right))
	{
		m_rotation += 3;
	}
}

void Player::move() {
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_rotation);
	m_velocity = sf::Vector2f(std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed,
		std::sin(DEG_TO_RAD * (m_rotation)) * m_speed);
	m_position += m_velocity;

	m_speed *= 0.999;

}

void Player::render(sf::RenderWindow & window)
{
	m_view.setCenter(m_sprite.getPosition());
	window.setView(m_view);
	window.draw(m_sprite);
}