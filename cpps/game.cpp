#include "..\Classes\game.h"

static sf::Int32 MS_PER_UPDATE = 10.0;


Game::Game() : m_window(sf::VideoMode(1200, 800), "AI") {
		
	m_window.setFramerateLimit(60);

	m_worldTexture.loadFromFile("assets/world.png");
	m_worldSprite.setTexture(m_worldTexture);
	m_worldSprite.setScale(4, 4);
	m_worldSprite.setOrigin(m_worldSprite.getLocalBounds().width / 2, m_worldSprite.getLocalBounds().height / 2);

	
	//m_miniMap.zoom(1);
	
	
	m_mapBorder.setOutlineThickness(10.0f);
	m_mapBorder.setOutlineColor(sf::Color::Black);
	m_mapBorder.setSize(sf::Vector2f(300, 200)); // SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.25));
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
	m_window.setView(player.m_view);
	m_window.draw(m_worldSprite);
	player.render(m_window);
	m_mapBorder.setPosition(player.m_sprite.getPosition().x + 300,player.m_sprite.getPosition().y + 200);
	m_window.draw(m_mapBorder);

	m_window.setView(m_miniMap);
	
	
	m_miniMap.setCenter(player.m_position);
	m_window.draw(m_worldSprite);
	m_window.draw(player.m_sprite);
	m_miniMap.setViewport(sf::FloatRect(0.75, 0.75, 0.25, 0.25));
	
	
	
	m_window.display();
	
}