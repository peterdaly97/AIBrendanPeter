#include "../Classes/Bullet.h"

/// <summary>
/// Bullet constructor which will initialise the bullet
/// </summary>
/// <param name="pos"></param>
/// <param name="rot"></param>
/// <param name="tex"></param>
Bullet::Bullet(sf::Vector2f pos, float rot, sf::Texture & tex) : m_pos(pos), m_rot(rot) {
	m_speed = 15;	// Sets bullet speed

	// Sets up visual properties of the bullet
	m_sprite.setTexture(tex);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

	m_lifeTime = 0;	// Sets current lifetime of bullet

	// Assign position and rotation of bullet
	m_sprite.setPosition(m_pos);
	m_sprite.setRotation(m_rot);
}

/// <summary>
/// Function that checks if the player has hit a wall
/// </summary>
/// <param name="grid"></param>
void Bullet::checkCollision(Grid &grid)
{
	// Sets up the position to check based on the player position and velocity 
	float scalar = 1.03;
	sf::Vector2f playerPursue = m_pos + (m_impulse * scalar);

	// Sets up grid dimensions
	int gridX = 50;
	int gridY = 50;
	int indexHorizontal = gridY;
	int indexVertical = 1;

	// Checks what tile the player is in
	playerGridX = (playerPursue.x + 5000) / 200;
	playerGridY = (playerPursue.y + 5000) / 200;
	playerGrid = playerGridX * 50 + (playerGridY);

	
	if (playerGrid >= 0 && playerGrid < 2500)
	{
		if (grid.nodes[playerGrid]->getCost() >= 9999) {
			// Checks if bullet is hitting a wall
			m_lifeTime = 101;
		}
	}

}


/// <summary>
/// Function for updating the bullet
/// </summary>
void Bullet::update() {
	// Updates position of bullet 
	m_impulse = sf::Vector2f(std::cos(DEG_TO_RAD  * (m_rot)) * m_speed,
		std::sin(DEG_TO_RAD * (m_rot)) * m_speed);
	m_pos += m_impulse;

	m_lifeTime++;	//Increment bullets lifetime	
	m_sprite.setPosition(m_pos);
}

/// <summary>
/// Function that handles the rendering of the bullet
/// </summary>
/// <param name="window"></param>
void Bullet::render(sf::RenderWindow & window) {
	window.draw(m_sprite); // Draws bullet
}
