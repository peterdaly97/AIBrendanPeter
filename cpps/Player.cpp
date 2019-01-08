#include "..\Classes\Player.h"
#include "..\Classes\Nest.h"

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
void Player::checkCollision(Grid grid)
{
	UpAvailable = true;
	DownAvailable = true;
	LeftAvailable = true;
	RightAvailable = true;


	int gridX = 50;
	int gridY = 50;
	int indexHorizontal = gridY;
	int indexVertical = 1;

	playerGridX = (m_sprite.getPosition().x+4800) / 200;
	playerGridY = (m_sprite.getPosition().y+4800) / 200;
	playerGrid = playerGridX*50 + (playerGridY +1);


	if (playerGrid < gridY)
	{
		LeftAvailable = false;
	}
	if (playerGrid > ((gridX * gridY) - (gridY + 1))) //2249
	{
		RightAvailable = false;
	}
	if (playerGrid % gridY == 0)
	{
		UpAvailable = false;
	}
	for (int x = 0; x < gridX; x++)
	{
		if (playerGrid == ((gridY - 1) + (gridY * x)))
		{
			DownAvailable = false;
		}
	}
	if (UpAvailable == true)
	{
		if (grid.nodes[playerGrid - indexVertical]->getCost() >= 9999)
		{
			UpAvailable = false;
		}
	}
	if (DownAvailable == true)
	{
		if (grid.nodes[playerGrid + indexVertical]->getCost() >= 9999)
		{
			DownAvailable = false;
		}
	}
	if (LeftAvailable == true)
	{
		if (grid.nodes[playerGrid - indexHorizontal]->getCost() >= 9999)
		{
			LeftAvailable = false;
		}
	}
	if (RightAvailable == true)
	{
		if (grid.nodes[playerGrid + indexHorizontal]->getCost() >= 9999)
		{
			RightAvailable = false;
		}
	}

	if (LeftAvailable == false)
	{
		m_velocity.x = 0;
	}
	if (RightAvailable == false)
	{
		m_velocity.x = 0;
		m_speed = 0;
	}

}
void Player::update(Grid grid)
{
	handleInput();
	move();
	checkCollision(grid);

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

	m_bulletCounter++;
	if (m_keys.isKeyPressed(sf::Keyboard::Space) && 
		m_bulletCounter > BULLET_TIME)
	{
		m_bulletCounter = 0;
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

void Player::checkNest(Nest & nest) {
	for (int i = 0; i < m_bullets.size(); i++) {
		if (dist(m_bullets.at(i)->m_pos, nest.m_position) < 150) {
			nest.loseHealth();
			m_bullets.erase(m_bullets.begin() + i);
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