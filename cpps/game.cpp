#include "..\Classes\game.h"

/// <summary>
/// Game constructor which initialises our render window
/// </summary>
Game::Game() : m_window(sf::VideoMode(1200, 800), "AI") {
		
	// Setting the update time for the game
	m_window.setFramerateLimit(60);

	// Loading in all our assets
	m_worldTexture.loadFromFile("assets/tileBack.png");
	m_worldSprite.setTexture(m_worldTexture);
	m_worldSprite.setScale(1, 1);
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

	m_bulletTex.loadFromFile("assets/bullet.png");

	m_powerTex.loadFromFile("assets/magnet.png");
	m_blastTex.loadFromFile("assets/blast.png");
	m_healthTex.loadFromFile("assets/health.png");

	m_heartText.setFont(m_font);
	m_heartText.setFillColor(sf::Color::White);
	m_heartText.setOrigin(m_heartText.getLocalBounds().width / 2, m_heartText.getLocalBounds().height / 2);

	m_workerText.setFont(m_font);
	m_workerText.setFillColor(sf::Color::White);
	m_workerText.setOrigin(m_workerText.getLocalBounds().width / 2, m_workerText.getLocalBounds().height / 2);

	m_mapBorder.setOutlineThickness(10.0f);
	m_mapBorder.setOutlineColor(sf::Color::Black);
	m_mapBorder.setSize(sf::Vector2f(300, 200));

	// Initialising and positioning the workers
	m_workers.push_back(new Worker(act::WANDER, sf::Vector2f(200, 200)));

	// Initialising and positioning the nests
	m_nests.push_back(new Nest(sf::Vector2f(0, -4000)));
	m_nests.push_back(new Nest(sf::Vector2f(-3500, 2000)));
	m_nests.push_back(new Nest(sf::Vector2f(3500, -2000)));
	
	// Initialising and positioning the power ups
	m_powerUps.push_back(new PowerUp(500, 500, m_powerTex, 1));
	m_powerUps.push_back(new PowerUp(500, 1000, m_blastTex, 2));
	m_powerUps.push_back(new PowerUp(500, 1500, m_healthTex, 3));


	m_miniMap.zoom(10);	// Setting how zoomed out the mini map is
	grid = new Grid();	// Initialising the grid

	// Passing the loaded in bullet texture to the player and grid
	player.m_bulletTex = m_bulletTex;
	grid->m_bulletTex = m_bulletTex;

	m_winTex.loadFromFile("assets/win.png");
	m_winSprite.setTexture(m_winTex);
	m_winSprite.setOrigin(m_winSprite.getLocalBounds().width / 2, m_winSprite.getLocalBounds().height / 2);
	m_winSprite.setPosition(sf::Vector2f(0, 0));
	m_winSprite.setColor(sf::Color(255, 255, 255, 150));
	m_winSprite.setScale(1.2, 1.2);

	m_loseTex.loadFromFile("assets/lose.png");
	m_loseSprite.setTexture(m_loseTex);
	m_loseSprite.setOrigin(m_loseSprite.getLocalBounds().width / 2, m_loseSprite.getLocalBounds().height / 2);
	m_loseSprite.setPosition(sf::Vector2f(0, 0));
	m_loseSprite.setColor(sf::Color(255, 255, 255, 150));
	m_loseSprite.setScale(1.2, 1.2);
}

/// <summary>
/// Destructor for game object
/// </summary>
Game::~Game() { }

/// <summary>
/// function handles the updating of the game
/// </summary>
void Game::run() {

	// While game is running
	while (m_window.isOpen()) {
		update();
		render();
	}
}

/// <summary>
/// Update actions of the game
/// </summary>
void Game::update() {

	for (PowerUp * powerUp : m_powerUps) { 
	// Loops through power ups
		// Checks if power up was collected
		if (powerUp->checkCollected(player.m_sprite.getPosition()) > 0)
		{
			// Carries out effect on player based on which power up was collected
			player.powerUp(powerUp->m_value);
		}

	}

	if (!m_win && !m_lose) {
		grid->update(m_window);	// Updates grid
	}

	checkEntities(); // Calls function which updates every entity

	for (int i = 0; i < m_particles.size(); i++) {
	// Loops through particle systems
		m_particles.at(i)->update(); 

		//Checks if the particle system is empty
		if (m_particles.at(i)->m_particles.size() <= 0) {
			// Deletes the particle system
			m_particles.erase(m_particles.begin() + i);
		}
	}

	updateUI(); // Calls function which updates the UI

	if (player.m_health <= 0) {
		m_lose = true;
	}
	if (player.m_collected >= m_totalWorkers) {
		m_win = true;
	}
}

/// <summary>
/// Function which updates and checks every active entity
/// </summary>
void Game::checkEntities() {
	if (!m_win && !m_lose) {
		player.update(*grid); // Updates the player

		if (player.checkPreds(grid->ais, m_particles) == 1)
		{ // Checks if player has killed predator	
			predCount = predCount - 1;	// Reduces amount of current predators

			grid->surroundCount = grid->surroundCount - 1; // Reduces amount of predators surrounding player
		}
		for (int i = 0; i < m_nests.size(); i++) {
			// Loops through nests
			if (m_nests.at(i)->spawnPredator() == 1 && predCount < predMax)
			{ // Checks if theres availability for another predator
			  // Spawns a predator at the current nest being checked
				grid->spawnPred(m_nests.at(i)->m_sprite.getPosition());
				predCount = predCount + 1; // Increment amount of current predators
			}
			// Update the nest
			m_nests.at(i)->update(player.m_position, player.m_health, m_particles, *grid, m_workers);
			player.checkNest(*m_nests.at(i));	// Player checks nest for bullet collision
			player.checkEnemies(m_nests.at(i)->m_enemies, m_particles); // Player checks enemies for bullet collision
			if (m_nests.at(i)->m_dead) {
				// Checks if nest is dead
				for (Enemy * e : m_nests.at(i)->m_enemies) {
					// Loops through enemies belonging to dead nest
					m_remainingEnemies.push_back(e);	// Pushes these enemies onto vector of enemies
				}
				// Spawn particles at dead nest position
				m_particles.push_back(new ParticleSystem(500, m_nests.at(i)->m_position));
				m_nests.erase(m_nests.begin() + i);	// Delete nest
			}
		}
		// Player checks enemies for bullet collision
		player.checkEnemies(m_remainingEnemies, m_particles);
		for (int i = 0; i < m_workers.size(); i++) {
			// Loops through workeres
			m_workers.at(i)->update(grid->nodes, grid->goalNode);	// Calls update on workers
			m_workers.at(i)->checkCollision(*grid);	// Checks collision between walls and workers
			if (m_workers.at(i)->m_collected) {
				// Checks if worker has been collected
				m_workers.erase(m_workers.begin() + i);	// Deletes worker
			}
		}
		player.checkCollection(&m_workers);	// Checks if player is collecting any workers

		for (Enemy* enemy : m_remainingEnemies) {
			// Loops through enemies not belonging to a nest

			enemy->update(player.m_position, sf::Vector2f(0, 0));	// Updates enemy
			enemy->checkCollision(*grid); // Checks collision between walls and enemy
			enemy->lookFor(m_workers);	// Checks if workers are in line of sight
		}
	}
}

/// <summary>
/// Function that handles rendering of all game entities
/// </summary>
void Game::render() {
	m_window.clear();	// Clears window
	m_window.setView(player.m_view);	// Sets view of window to be the players view
	
	m_window.draw(m_worldSprite);	// Draws background
	grid->draw(m_window);	// Draws all the tiles
	for (PowerUp * powerUp : m_powerUps)
	{
		powerUp->draw(m_window);	// Draw powerup
	}
	for (Nest * nest : m_nests) {
		nest->render(m_window);	// Draw nest
	}
	for (Worker * en : m_workers) {
		en->render(m_window);	// Draw worker
	}
	for (Enemy* enemy : m_remainingEnemies) {
		enemy->render(m_window);	// Draw remaining enemy
	}
	for (ParticleSystem* ps : m_particles) {
		ps->draw(m_window); // Draw particle system
	}

	
	player.render(m_window);	// Draw the player

	// Draw UI
	m_window.draw(m_heartSprite);
	m_window.draw(m_workerSprite);
	m_window.draw(m_heartText);
	m_window.draw(m_workerText);
	if (!m_win && !m_lose) {
		m_mapBorder.setPosition(player.m_sprite.getPosition().x + 300, player.m_sprite.getPosition().y + 200);
		m_window.draw(m_mapBorder);

		m_window.setView(m_miniMap);	// Set view to the mini map view

		m_window.draw(m_worldSprite);	// Draw background
		m_miniMap.setCenter(0, 0);	// Set center of mini map

									// Draw all game entites as dots
		for (Nest * nest : m_nests) {
			nest->renderDot(m_window);
		}
		for (Worker * en : m_workers) {
			en->renderDot(m_window);
		}
		for (Enemy* enemy : m_remainingEnemies) {
			enemy->renderEnemyDot(m_window);	// Draw remaining enemy
		}
		for (PowerUp * powerUp : m_powerUps)
		{
			powerUp->renderDot(m_window);
		}
		grid->renderDots(m_window);
		player.renderDot(m_window);

		// Set mini map viewport to bottom right corner of the screen
		m_miniMap.setViewport(sf::FloatRect(0.75, 0.75, 0.25, 0.25));
	}
	
	if (m_win) {
		m_winSprite.setPosition(player.m_position);
		m_window.draw(m_winSprite);
	}
	if (m_lose) {
		m_loseSprite.setPosition(player.m_position);
		m_window.draw(m_loseSprite);
	}
	m_window.display();		// Display the window 
}

/// <summary>
/// Function for positioning UI objects
/// </summary>
void Game::updateUI() {
	// Set the position of the two sprites corresponding to health and workers collected
	m_heartSprite.setPosition(
		player.m_sprite.getPosition().x - 550,
		player.m_sprite.getPosition().y - 350
	);
	m_workerSprite.setPosition(
		player.m_sprite.getPosition().x + 450,
		player.m_sprite.getPosition().y - 350
	);

	// Set the position of the text objects displaying the current amount
	// of health and workers collected
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
