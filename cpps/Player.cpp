#include "..\Classes\Player.h"
#include "..\Classes\Nest.h"

/// <summary>
/// Constructor for the player
/// </summary>
Player::Player()
{
	// Sets up all the textures and sprites for the player object
	m_texture.loadFromFile("assets/ship.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.3, 0.3);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_fireTexture.loadFromFile("assets/fire.png");
	rectSourceSprite.left = 320;
	rectSourceSprite.top = 0;
	rectSourceSprite.width = 64;
	rectSourceSprite.height = 64;
	m_fireSprite.setTexture(m_fireTexture);
	m_fireSprite.setTextureRect(rectSourceSprite);
	m_fireSprite.setOrigin(m_fireSprite.getLocalBounds().width + 30, m_fireSprite.getLocalBounds().height / 2);

	// Sets up all the current physical attributes of the player object
	m_position = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
	m_sprite.setPosition(m_position);
	m_rotation = 0;
	m_speed = 0;

	// Sets the size of the main view
	m_view.setSize(1200, 800);
}


/// <summary>
/// Destructor for the player
/// </summary>
Player::~Player() {}

/// <summary>
/// Function that checks if the player has hit a wall
/// </summary>
/// <param name="grid"></param>
void Player::checkCollision(Grid &grid)
{
	// Sets up the position to check based on the player position and velocity 
	float scalar = 1.03;
	sf::Vector2f playerPursue = m_position + (m_velocity * scalar);

	// Sets up grid dimensions
	int gridX = 50;
	int gridY = 50;
	int indexHorizontal = gridY;
	int indexVertical = 1;

	// Checks what tile the player is in
	playerGridX = (playerPursue.x + 5000) / 200;
	playerGridY = (playerPursue.y + 5000) / 200;
	playerGrid = playerGridX * 50 + (playerGridY);

	if (tempGrid != playerGrid)
	{// If player has changed tile since the last check
		gridChanged = true;
	}
	tempGrid = playerGrid;

	if (playerGrid >= 0 && playerGrid < 2500)
	{
		if (grid.nodes[playerGrid]->getCost() >= 9999) {
			// Checks if player is hitting a wall
			// Knocks the player back
			m_velocity.x = -m_velocity.x * 0.6;
			m_velocity.y = -m_velocity.y * 0.6;
			m_speed = -m_speed;
		}
	}

}

/// <summary>
/// Function that updates the animation
/// </summary>
void Player::animationUpdate()
{
	if (rectSourceSprite.top < 320)
	{// Checks that aniamtion hasn't reached the end
		rectSourceSprite.top += 64;	// Loops up through animation
	}
	else
	{
		rectSourceSprite.top = 0;	// Resets the animation
		if (rectSourceSprite.left > 0)
		{ // Checks that aniamtion hasn't reached the end
			rectSourceSprite.left -= 64; // Loops left through animation
		}
		else
		{
			rectSourceSprite.left = 320; // Resets the animation
		}
	}

	// Assigns current stage of animation to the engine fire texture
	m_fireSprite.setTextureRect(rectSourceSprite);
}

/// <summary>
/// Function that handles the updating of the player
/// </summary>
/// <param name="grid"></param>
void Player::update(Grid &grid)
{
	animationUpdate();	// Calls function to update the animation
	handleInput();	// Calls function to check input
	move();	// Calls function to move the player
	checkCollision(grid);	// Calls function to check walls for collision

	grid.updateAI(m_position, m_health);	// Calls on the grid object to update the predators

	if (gridChanged == true)
	{	// If player has changed tile
		gridChangedCount += 1;
		if (gridChangedCount == 100)
		{
			grid.seek(playerGrid);	// Calls on predators to pathfind to player
			gridChanged = false;
			gridChangedCount = 0;
		}
	}

	for (Bullet * bullet : m_bullets) {
		// Loops through players bullets
		bullet->update();	// Updates bullets
		bullet->checkCollision(grid);
		if (bullet->m_lifeTime > bullet->MAX_LIFE) {
			// Checks if bullet has reached its lifetime
			m_bullets.erase(m_bullets.begin()); // Delete bullet
		}
	}

	// Turn magnet off after set time.
	if (magnet)
	{
		magnetCount = magnetCount + 1;
		if (magnetCount >= maxMagnet)
		{
			magnet = false;
			magnetCount = 0;
		}
	}
}

/// <summary>
/// Function for checking for keyboard input and 
/// handling said input
/// </summary>
void Player::handleInput() {
	if (m_keys.isKeyPressed(sf::Keyboard::Up)) {
		// Checks for the up arrow being pressed
		drawFireBack = true;
		if (m_speed < MAX_FORWARD_SPEED)
			m_speed += 0.15;	// Increments speed
	}
	else {
		drawFireBack = false;
	}
	if (m_keys.isKeyPressed(sf::Keyboard::Down)) {
		// Checks for the down arrow being pressed
		if (m_speed > MAX_BACKWARD_SPEED)
			m_speed -= 0.05;	// Decrement speed 
	}
	if (m_keys.isKeyPressed(sf::Keyboard::Left)) {
		// Checks for the left arrow being pressed
		m_rotation -= 3;	// Rotate ship anti-clockwise
	}
	if (m_keys.isKeyPressed(sf::Keyboard::Right)) {
		// Checks for the right arrow being pressed
		m_rotation += 3; // Rotate ship clockwise
	}

	m_bulletCounter++;	// Increment bullet times
	if (m_keys.isKeyPressed(sf::Keyboard::Space) &&
		m_bulletCounter > BULLET_TIME) {
		// If enough time has passed and player hits space
		m_bulletCounter = 0;	// Reset bullet timer
								// Spawn bullet
		m_bullets.push_back(new Bullet(m_sprite.getPosition(), m_sprite.getRotation(), m_bulletTex));
	}
	if (m_keys.isKeyPressed(sf::Keyboard::Q) && m_blast) {
		// Checks if Q key was pressed and player has blast attack activated
		for (int i = 0; i < 360; i += 15) {
			// Spawn ring of bullets around player
			m_bullets.push_back(new Bullet(m_sprite.getPosition(), i, m_bulletTex));
			m_blast = false;	// Player has used up his ability
		}
	}

	// Cheats for testing.
	if (m_keys.isKeyPressed(sf::Keyboard::H)) {
		m_health = m_health + 1000;
	}
}

/// <summary>
/// Function that handles the players movement 
/// </summary>
void Player::move() {
	// Sets players current physical attributes
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_rotation);
	m_fireSprite.setPosition(m_position.x, m_position.y);
	m_fireSprite.setRotation(m_rotation);

	// Calculates velocity based on speed and rotation
	m_velocity = sf::Vector2f(std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed,
		std::sin(DEG_TO_RAD * (m_rotation)) * m_speed);
	m_position += m_velocity;

	m_speed *= 0.999;	// Friction causes player to slow down

}

/// <summary>
/// Function checks if player has collected any workers
/// </summary>
/// <param name="workers"></param>
void Player::checkCollection(std::vector<Worker*> * workers) {
	for (int i = 0; i < workers->size(); i++) {
		// Loops through all the workers
		if (dist(m_position, workers->at(i)->m_position) < 40) {
			// Checks if player has hit the worker
			workers->at(i)->m_collected = true;	// Sets worker to be collected
			m_collected++;	// Increments amount of workers collected
			m_score += 5;
		}
		if (magnet) {
			// Checks if player has magnet power up
			workers->at(i)->magnet = true;	// Sets worker to move towards player
		}
		else {
			workers->at(i)->magnet = false;
		}
	}

}

/// <summary>
/// Checks nest if it has been by one of the players bullets
/// </summary>
/// <param name="nest"></param>
void Player::checkNest(Nest & nest) {
	if (dist(m_position, nest.m_position) < 500) {
		// Checks if player is close to the nest
		nest.addMissile();	// Nest fires bullet at player
	}
	for (int i = 0; i < m_bullets.size(); i++) {
		// Loops through all of the player bullets
		if (dist(m_bullets.at(i)->m_pos, nest.m_position) < 150) {
			// Checks to see if a bullet has hit the nest
			nest.loseHealth(m_score);	// Nest loses health
			m_bullets.erase(m_bullets.begin() + i);	// Delete bullet
		}

	}
}

/// <summary>
/// Checks if any of the sweeper bots have been hit by the players bullets
/// </summary>
/// <param name="enemies"></param>
/// <param name="ps"></param>
void Player::checkEnemies(std::vector<Enemy *> & enemies, std::vector<ParticleSystem *> & ps) {
	for (int i = 0; i < m_bullets.size(); i++) {
		// Loops through all of the players bullets
		for (int j = 0; j < enemies.size(); j++) {
			// Loops through all the sweeper bots
			if (m_bullets.size() > i && dist(m_bullets.at(i)->m_pos, enemies.at(j)->m_position) < 75) {
				// Checks if bullet has hit enemy
				m_collected += enemies.at(j)->m_collected;	// Player gets any worker that sweeper has collected
				ps.push_back(new ParticleSystem(500, enemies.at(j)->m_position));	// Spawn particles at dead sweepers position
				enemies.erase(enemies.begin() + j);	// Delete sweeper
				m_bullets.erase(m_bullets.begin() + i);	// Delete bullet
				m_score += 2;
			}
		}
	}
}

/// <summary>
/// Checks if any of the predators have been hit by the players bullets
/// </summary>
/// <param name="ais"></param>
/// <param name="ps"></param>
/// <returns></returns>
bool Player::checkPreds(std::vector<AI *> & ais, std::vector<ParticleSystem *> & ps) {
	for (int i = 0; i < m_bullets.size(); i++) {
		// Loops through player bullets
		for (int j = 0; j < ais.size(); j++) {
			// Loops through predators
			if (m_bullets.size() > i && dist(m_bullets.at(i)->m_pos, ais.at(j)->aiSprite.getPosition()) < 75) {
				// Checks if player has hit predator
				ps.push_back(new ParticleSystem(500, ais.at(j)->aiSprite.getPosition())); // Spawn particles at dead predators position
				ais.erase(ais.begin() + j);	// Delete predator
				m_bullets.erase(m_bullets.begin() + i);	// Delete bullet
				m_score += 2;
				return true;
			}

		}
	}
	return false;
}

/// <summary>
/// Function that handles all the rendering 
/// </summary>
/// <param name="window"></param>
void Player::render(sf::RenderWindow & window)
{
	m_view.setCenter(m_sprite.getPosition());	// Sets the center of the main view so that the player will always be in the center
	window.setView(m_view);	// Assigns this view to the window
	window.draw(m_sprite);	// Draw the ship
	if (drawFireBack == true)
	{ // If player is holding the up key
		window.draw(m_fireSprite);	// Draw the engine fire
	}
	for (Bullet * bullet : m_bullets) {
		// Loops through bullets
		if (bullet) {
			// If the bullet is alive
			bullet->render(window);	// Draw bullet 
		}

	}
}

/// <summary>
/// Function that is triggered when player collects powerup
/// It checks which powerup was collected and updates player based on which powerup it was
/// </summary>
/// <param name="power"></param>
void Player::powerUp(int power)
{
	if (power == 1) {
		// If magnet was collected
		magnet = true;	// Player is now a magnet for workers
	}
	else if (power == 2) {
		// If blast attack was collected
		m_blast = true;	// Player can now use blast attack
	}
	else if (power == 3) {
		// If health pack was collected
		if (m_health < 90) {
			m_health += 10;
		}
		else {
			m_health = 100;
		}
	}
}

/// <summary>
/// Function that draws dot on minimap at players position
/// </summary>
/// <param name="window"></param>
void Player::renderDot(sf::RenderWindow &window) {
	// Sets up dot
	sf::CircleShape shape(100);
	shape.setFillColor(sf::Color(0, 255, 0));
	shape.setPosition(m_sprite.getPosition());

	// Draws dot
	window.draw(shape);
}

/// <summary>
/// Function for checking and returning the distance between two vectors
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Player::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}