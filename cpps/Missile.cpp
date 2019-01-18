#include "../Classes/Missile.h"

/// <summary>
/// Constructor for the missile
/// </summary>
/// <param name="pos"></param>
Missile::Missile(sf::Vector2f pos) : m_position(pos) {
	m_speed = 1.5;

	// Sets up the visual attributes
	m_texture.loadFromFile("assets/missile.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
}

/// <summary>
/// Update function for the missile
/// </summary>
/// <param name="playerPos"></param>
/// <param name="health"></param>
void Missile::update(sf::Vector2f playerPos, int & health) {
	// Calculates steer needed to follow the player
	steer = seek(playerPos);
		
	// Assigns this steer to the missile
	m_position += steer.linear;
	m_sprite.setPosition(m_position);

	// Update position based on velocity
	m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed,
		m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed);

	if (dist(playerPos, m_position) < 45) {
	// If missile has hit player
		health = health - 15;	// Hurt the player
		m_dead = true;	// Missile is dead
	}

	// Update time
	m_time += m_clock.restart();
	if (m_time.asSeconds() > 5) {
	// If 5 seconds have passed since missile was spawned
		m_dead = true;	// Destroy missile
	}
}

/// <summary>
/// Function for calculating how to get the missile to chase the player
/// </summary>
/// <param name="playerPos"></param>
/// <returns></returns>
pathing Missile::seek(sf::Vector2f playerPos) {
	// Finds difference between missile position and player position
	m_velocity = playerPos - m_position;
	startCalc();
	m_sprite.setRotation(m_rotation);

	pathing seekSteering;
	seekSteering.linear = m_velocity;
	seekSteering.angular = 0.0;
	return seekSteering;
}

/// <summary>
/// Function for handling the render of the missile
/// </summary>
/// <param name="window"></param>
void Missile::render(sf::RenderWindow & window) {
	window.draw(m_sprite);	// Draw the missile
}

/// <summary>
/// Function for updating the rotation of the missile
/// </summary>
/// <param name="rot"></param>
/// <param name="vel"></param>
/// <returns></returns>
float Missile::getNewRotation(float rot, sf::Vector2f vel) {

	if (mag(m_velocity) > 0.0) {
	// If missile is moving
		// Calculates new rotation
		float rotation = std::atan2(-m_velocity.x, m_velocity.y) * (180 / 3.14159);
		return (rotation + 90);
	}
	else {
		return rot;	// Just return old rotation
	}

}

/// <summary>
/// Calculates magnitude of vector
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
float Missile::mag(sf::Vector2f v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}

/// <summary>
/// Function for updating all movement attributes of the missile
/// </summary>
void Missile::startCalc() {
	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		float magnitude = mag(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x / magnitude, m_velocity.y / magnitude);
		m_velocity = m_velocity * m_speed;
		m_rotation = getNewRotation(m_rotation, m_velocity);
	}

}

/// <summary>
/// Function that calculates the distance between 2 vectors
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Missile::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}
