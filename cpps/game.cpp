#include "..\Classes\game.h"

static sf::Int32 MS_PER_UPDATE = 10.0;


Game::Game() : m_window(sf::VideoMode(1200, 800), "AI") {
		
	m_window.setFramerateLimit(60);

	m_worldTexture.loadFromFile("assets/mapSnip.PNG");
	m_worldSprite.setTexture(m_worldTexture);
	m_worldSprite.setScale(5, 5);
	m_worldSprite.setOrigin(m_worldSprite.getLocalBounds().width / 2, m_worldSprite.getLocalBounds().height / 2);
	
	m_heartTex.loadFromFile("assets/heart.png");
	m_heartSprite.setTexture(m_heartTex);
	m_heartSprite.setOrigin(m_heartSprite.getLocalBounds().width / 2, m_heartSprite.getLocalBounds().height / 2);
	
	m_workerTex.loadFromFile("assets/worker.png");
	m_workerSprite.setTexture(m_workerTex);
	m_workerSprite.setOrigin(m_workerSprite.getLocalBounds().width / 2, m_workerSprite.getLocalBounds().height / 2);
	m_workerSprite.setScale(2, 2);

	if (!m_font.loadFromFile("assets/arial.ttf"))	// Checks to make sure font is correct
	{
		std::cout << "Problem loading font file!" << std::endl;
	}

	m_heartText.setFont(m_font);
	m_heartText.setFillColor(sf::Color::White);
	m_heartText.setOrigin(m_heartText.getLocalBounds().width / 2, m_heartText.getLocalBounds().height / 2);

	m_workerText.setFont(m_font);
	m_workerText.setFillColor(sf::Color::White);
	m_workerText.setOrigin(m_workerText.getLocalBounds().width / 2, m_workerText.getLocalBounds().height / 2);

	m_mapBorder.setOutlineThickness(10.0f);
	m_mapBorder.setOutlineColor(sf::Color::Black);
	m_mapBorder.setSize(sf::Vector2f(300, 200));

	m_workers.push_back(new Worker(act::WANDER, sf::Vector2f(200, 200)));
	m_nests.push_back(new Nest(sf::Vector2f(300, -200)));

	m_miniMap.zoom(2);
	grid = new Grid();

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

	grid->update(m_window);
	player.update(*grid);
	for (int i = 0; i < m_nests.size(); i++) {
		m_nests.at(i)->update();
		player.checkNest(*m_nests.at(i));
		player.checkEnemies(m_nests.at(i)->m_enemies);
		if (m_nests.at(i)->m_dead) {
			for (Enemy * e : m_nests.at(i)->m_enemies) {
				m_remainingEnemies.push_back(e);
			}
			m_nests.erase(m_nests.begin() + i);
			std::cout << "" << std::endl;
		}
	}
	player.checkEnemies(m_remainingEnemies);
	for (Worker * en : m_workers) {
		en->update();
	}
	player.checkCollection(&m_workers);
	
	for (Enemy* enemy : m_remainingEnemies) {
		// Two vectors will be changed to player position and velocity
		enemy->update(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	}
	
	updateUI();
}

void Game::render() {
	m_window.clear();
	m_window.setView(player.m_view);
	
	m_window.draw(m_worldSprite);
	grid->draw(m_window);
	for (Nest * nest : m_nests) {
		nest->render(m_window);
	}
	for (Worker * en : m_workers) {
		en->render(m_window);
	}
	for (Enemy* enemy : m_remainingEnemies) {
		enemy->render(m_window);
	}
	
	player.render(m_window);
	m_window.draw(m_heartSprite);
	m_window.draw(m_workerSprite);
	m_window.draw(m_heartText);
	m_window.draw(m_workerText);
	
	m_mapBorder.setPosition(player.m_sprite.getPosition().x + 300,player.m_sprite.getPosition().y + 200);
	m_window.draw(m_mapBorder);
	m_window.setView(m_miniMap);

	
	
	m_window.draw(m_worldSprite);
	m_miniMap.setCenter(player.m_sprite.getPosition());
	for (Nest * nest : m_nests) {
		nest->render(m_window);
	}
	for (Worker * en : m_workers) {
		en->render(m_window);
	}
	for (Enemy* enemy : m_remainingEnemies) {
		enemy->render(m_window);
	}
	m_window.draw(player.m_sprite);
	m_miniMap.setViewport(sf::FloatRect(0.75, 0.75, 0.25, 0.25));
	
	
	

	m_window.display();
	
}

void Game::updateUI() {

	m_heartSprite.setPosition(
		player.m_sprite.getPosition().x - 550,
		player.m_sprite.getPosition().y - 350
	);

	m_workerSprite.setPosition(
		player.m_sprite.getPosition().x + 450,
		player.m_sprite.getPosition().y - 350
	);

	m_heartText.setString(std::to_string(player.m_health));
	m_heartText.setPosition(
		player.m_sprite.getPosition().x - 500,
		player.m_sprite.getPosition().y - 370
	);

	m_workerText.setString(std::to_string(player.m_collected));
	m_workerText.setPosition(
		player.m_sprite.getPosition().x + 500,
		player.m_sprite.getPosition().y - 370
	);
}
