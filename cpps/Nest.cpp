#include "../Classes/Nest.h"

/// <summary>
/// Constructor for the nest object
/// </summary>
/// <param name="pos"></param>
Nest::Nest(sf::Vector2f pos) : m_position(pos) {
	// Setting up visual attributes of the nest
	m_texture.loadFromFile("assets/nest.png");
	m_enemyTex.loadFromFile("assets/alien.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(m_position);


	m_health = 4;	// Assigns the health of the nest
	m_spawnTimer = 0;	// Starting spawn timer for sweeper bots
}

/// <summary>
/// Deconstructor for the nest
/// </summary>
Nest::~Nest() {}

/// <summary>
/// Update function to handle all non-rendering functionality
/// </summary>
/// <param name="playerPos"></param>
/// <param name="health"></param>
/// <param name="ps"></param>
/// <param name="grid"></param>
/// <param name="wpos"></param>
void Nest::update(sf::Vector2f playerPos, int & health, std::vector<ParticleSystem *> & ps, Grid &grid, std::vector<Worker *> wpos) {
	// Increment timers for spawning enemies
	m_spawnTimer++;
	predSpawnTimer++;

	if (m_spawnTimer > SPAWN_NEXT && m_enemies.size() < 5) {
		// If time to spawn sweeper bot and the maximum number hasn't been reached
		spawn();	// Spawn sweeper bot
	}
	for (Enemy* enemy : m_enemies) {
		// Loop through enemies

		enemy->update(playerPos, sf::Vector2f(0, 0));	// Update sweeper
		enemy->checkCollision(grid);	// Check sweeper for collision with walls
		enemy->lookFor(wpos);	// Have enemies check if worker is in line of sight
	}
	for (int i = 0; i < m_missiles.size(); i++) {
		// Loop through missiles
		m_missiles.at(i)->update(playerPos, health);	// Update missiles
		if (m_missiles.at(i)->m_dead) {
			// If missile is dead
			// Spawn particles at missiles position
			ps.push_back(new ParticleSystem(1000, m_missiles.at(i)->m_position));
			m_missiles.erase(m_missiles.begin() + i);	// Delete missile 
		}
	}
}

/// <summary>
/// Function for checking whether or not a predator should be spawned
/// </summary>
/// <returns></returns>
int Nest::spawnPredator()
{
	if (predSpawnTimer > 100) {
		// If its time to spawn a predator
		predSpawnTimer = 0;	// Reset timer 
		return 1; // Return true 
	}
	else {
		return 0;	// Return false
	}
}

/// <summary>
/// Function that is called when the nest is hit by a bullet
/// </summary>
void Nest::loseHealth(int & score) {
	m_health--;	// Deduct health 
	if (m_health <= 0) {
		// Checks if nest has run out of health
		m_dead = true;	// Set nest to be dead
		score += 20;
	}
}

/// <summary>
/// Function that will fire missile at player 
/// </summary>
void Nest::addMissile() {
	if (m_missiles.size() < 1) {
		// If missile is currently fired 
		m_missiles.push_back(new Missile(m_position));	// Fire missile
	}
}

/// <summary>
/// Function that handles all the rendering of the nest
/// </summary>
/// <param name="window"></param>
void Nest::render(sf::RenderWindow &window) {
	window.draw(m_sprite);	// Draw nest
	for (Enemy* enemy : m_enemies) {
		enemy->render(window);	// Draw all the enemies
	}
	for (Missile* m : m_missiles) {
		m->render(window);	// Draw all the missiles
	}
}

/// <summary>
/// Function for rendering a dot to the mini map at the nests position
/// </summary>
/// <param name="window"></param>
void Nest::renderDot(sf::RenderWindow &window) {
	// Sets up the dot
	sf::CircleShape shape(250);
	shape.setFillColor(sf::Color(153, 0, 204));
	shape.setPosition(m_sprite.getPosition());

	for (Enemy* enemy : m_enemies) {
		enemy->renderEnemyDot(window);	// Draw all the enemies
	}

	// Draws the dot to the screen
	window.draw(shape);
}

// Function for spawning a new sweeper bot
void Nest::spawn() {
	m_spawnTimer = 0;	// Reset the timer

						// Spawn a new sweeper
	m_enemies.push_back(new Enemy(behaviour::PATROL, m_position, 5.0f, &m_enemyTex));
}