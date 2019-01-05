#include "../Classes/Nest.h"

Nest::Nest(sf::Vector2f pos) : m_position(pos) {
	m_texture.loadFromFile("assets/nest.png");
	m_enemyTex.loadFromFile("assets/alien.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(m_position);

	m_health = 4;
	m_spawnTimer = 0;
}

Nest::~Nest() {

}

void Nest::update() {
	m_spawnTimer++;
	if (m_spawnTimer > SPAWN_NEXT && m_enemies.size() < 5) {
		spawn();
	}
	for (Enemy* enemy : m_enemies) {
		// Two vectors will be changed to player position and velocity
		enemy->update(sf::Vector2f(0,0), sf::Vector2f(0, 0));
	}
}

void Nest::loseHealth() {
	m_health--;
	if (m_health <= 0) {
		m_dead = true;
	}
}

void Nest::render(sf::RenderWindow &window) {
	window.draw(m_sprite);
	for (Enemy* enemy : m_enemies) {
		enemy->render(window);
	}
}

void Nest::spawn() {
	m_spawnTimer = 0;
	m_enemies.push_back(new Enemy(behaviour::PATROL, m_position, 5.0f, &m_enemyTex));
}