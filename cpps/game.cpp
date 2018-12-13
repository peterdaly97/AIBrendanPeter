#include "..\Classes\game.h"

static sf::Int32 MS_PER_UPDATE = 10.0;


Game::Game() : m_window(sf::VideoMode(1920, 1080), "AI") {
		
	m_window.setFramerateLimit(60);

	m_worldTexture.loadFromFile("assets/world.png");
	m_worldSprite.setTexture(m_worldTexture);
	m_worldSprite.setScale(5, 5);
	m_worldSprite.setOrigin(m_worldSprite.getLocalBounds().width / 2, m_worldSprite.getLocalBounds().height / 2);
}

Game::~Game() {

}

void Game::run() {

	while (m_window.isOpen()) {
		update();
		render();
	}
}

void Game::update() {
	
	player.update();

}

void Game::render() {
	m_window.clear();
	m_window.draw(m_worldSprite);
	player.render(m_window);
	m_window.display();
	
}