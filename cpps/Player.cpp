#include "..\Classes\Player.h"
#include "..\Classes\Nest.h"

Player::Player()
{
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
	//m_fireSprite.setOrigin(m_sprite.getOrigin());
	m_fireSprite.setOrigin(m_fireSprite.getLocalBounds().width + 30, m_fireSprite.getLocalBounds().height / 2);

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

void Player::checkCollision(Grid &grid)
{
	float scalar = 1.03;
	sf::Vector2f playerPursue = m_position + (m_velocity * scalar);

	//playerPursue = sf::Vector2f(playerPursue.x * scalar, playerPursue.y * scalar);

	int gridX = 50;
	int gridY = 50;
	int indexHorizontal = gridY;
	int indexVertical = 1;

	playerGridX = (playerPursue.x+5000) / 200;
	playerGridY = (playerPursue.y+5000) / 200;
	playerGrid = playerGridX*50 + (playerGridY);
	if (tempGrid != playerGrid)
	{
		gridChanged = true;
	}
	tempGrid = playerGrid;

	//std::cout << playerGrid << std::endl;
	if (grid.nodes[playerGrid]->getCost() >= 9999) {
		m_velocity.x = -m_velocity.x * 0.6;
		m_velocity.y = -m_velocity.y * 0.6;
		m_speed = -m_speed;
	}

}
void Player::animationUpdate()
{
	if (rectSourceSprite.top < 320)
	{
		rectSourceSprite.top += 64;
	}
	else
	{
		rectSourceSprite.top = 0;
		if (rectSourceSprite.left > 0)
		{
			rectSourceSprite.left -= 64;
		}
		else
		{
			rectSourceSprite.left = 320;
		}
	}
	m_fireSprite.setTextureRect(rectSourceSprite);
	//m_fireSprite.setScale(0.1, 1);
}
void Player::update(Grid &grid)
{
	animationUpdate();
	handleInput();
	move();
	checkCollision(grid);
	grid.updateAI(m_position, m_health);
	if (gridChanged == true)
	{
		gridChangedCount += 1;
		if (gridChangedCount == 100)
		{
			grid.seek(playerGrid);
			gridChanged = false;
			gridChangedCount = 0;
		}
	}

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
		drawFireBack = true;
		if (m_speed < MAX_FORWARD_SPEED)
			m_speed += 0.15;
	}
	else
	{
		drawFireBack = false;
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

	m_bulletCounter++;
	if (m_keys.isKeyPressed(sf::Keyboard::Space) && 
		m_bulletCounter > BULLET_TIME)
	{
		m_bulletCounter = 0;
		m_bullets.push_back(new Bullet(m_sprite.getPosition(), m_sprite.getRotation()));
	}
	if (m_keys.isKeyPressed(sf::Keyboard::Q) && m_blast) {
		for (int i = 0; i < 360; i += 15) {
			m_bullets.push_back(new Bullet(m_sprite.getPosition(), i));
			m_blast = false;
		}
	}
}

void Player::move() {
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_rotation);
	m_fireSprite.setPosition(m_position.x,m_position.y);
	m_fireSprite.setRotation(m_rotation);
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
	// Set Workers to be attracted if magnet got
	for (int i = 0; i < workers->size(); i++) {
		if (magnet == true) {
			workers->at(i)->magnet = true;
		}
	}
}

void Player::checkNest(Nest & nest) {
	if (dist(m_position, nest.m_position) < 500) {
		nest.addMissile();
	}
	for (int i = 0; i < m_bullets.size(); i++) {
		if (dist(m_bullets.at(i)->m_pos, nest.m_position) < 150) {
			nest.loseHealth();
			m_bullets.erase(m_bullets.begin() + i);
		}
		
	}
}

void Player::checkEnemies(std::vector<Enemy *> & enemies, std::vector<ParticleSystem *> & ps) {
	for (int i = 0; i < m_bullets.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {
			if (m_bullets.size() > i && dist(m_bullets.at(i)->m_pos, enemies.at(j)->m_position) < 75) {
				ps.push_back(new ParticleSystem(1000, enemies.at(j)->m_position));
				enemies.erase(enemies.begin() + j);
				m_bullets.erase(m_bullets.begin() + i);
			}
		}
	}
}
bool Player::checkPreds(std::vector<AI *> & ais, std::vector<ParticleSystem *> & ps) {
	for (int i = 0; i < m_bullets.size(); i++) {
		for (int j = 0; j < ais.size(); j++) {
			if (m_bullets.size() > i && dist(m_bullets.at(i)->m_pos, ais.at(j)->aiSprite.getPosition()) < 75) {
				ps.push_back(new ParticleSystem(1000, ais.at(j)->aiSprite.getPosition()));
				ais.erase(ais.begin() + j);
				m_bullets.erase(m_bullets.begin() + i);
				return true;
			}
		
		}
	}
	return false;
}

void Player::render(sf::RenderWindow & window)
{
	m_view.setCenter(m_sprite.getPosition());
	window.setView(m_view);
	window.draw(m_sprite);
	if (drawFireBack == true)
	{
		window.draw(m_fireSprite);
	}
	for (Bullet * bullet : m_bullets) {
		if (bullet) {
			bullet->render(window); 
		}
		
	}
}
void Player::powerUp(int power)
{
	if (power == 1) {
		magnet = true;
	}
	else if (power == 2) {
		m_blast = true;
	}
	else if (power == 3) {
		if (m_health < 90) {
			m_health += 10;
		}
		else {
			m_health = 100;
		}
	}
}
void Player::renderDot(sf::RenderWindow &window) {
	sf::CircleShape shape(100);
	shape.setFillColor(sf::Color(0, 255, 0));
	shape.setPosition(m_sprite.getPosition());
	window.draw(shape);
}

float Player::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}