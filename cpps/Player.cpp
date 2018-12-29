#include "..\Classes\Player.h"

Player::Player()
{
	m_texture.loadFromFile("assets/ship.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.3, 0.3);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

	m_position = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
	m_sprite.setPosition(m_position);
	m_rotation = 0;
	m_speed = 0;
	m_view.setSize(1200, 800);
	
}



Player::~Player()
{
}

void Player::update()
{
	handleInput();
	move();

	for (Bullet * bullet : m_bullets) {
		bullet->update();
		if (bullet->m_lifeTime > bullet->MAX_LIFE) {
			m_bullets.erase(m_bullets.begin()); // ToDo: Stop memory leak
		}
	}
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
	if (m_keys.isKeyPressed(sf::Keyboard::Space))
	{
		m_bullets.push_back(new Bullet(m_sprite.getPosition(), m_sprite.getRotation()));
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

void Player::checkCollection(std::vector<Worker*> * workers) {
	for (int i = 0; i < workers->size(); i++) {
		if (dist(m_position, workers->at(i)->m_position) < 30) {
			workers->erase(workers->begin() + i);
			m_collected++;
		}
	}
}

void Player::render(sf::RenderWindow & window)
{
	m_view.setCenter(m_sprite.getPosition());
	window.setView(m_view);
	window.draw(m_sprite);
	for (Bullet * bullet : m_bullets) {
		if (bullet) {
			bullet->render(window); 
		}
		
	}
}

float Player::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}