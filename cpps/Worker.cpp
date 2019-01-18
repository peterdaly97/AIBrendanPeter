#include "../Classes/Worker.h"

#define PI 3.14159265

/// <summary>
/// Constructor
/// </summary>
/// <param name="behaviour"></param>
/// <param name="pos"></param>
Worker::Worker(act behaviour, sf::Vector2f pos) {
	// Set up visual attributes
	m_texture.loadFromFile("assets/worker.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(3, 3);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

	// Set up physical attributes
	m_speed = 2.5;
	m_position = pos;
	m_sprite.setPosition(pos);

	// Give worker new random position to wander to
	m_targetPos.x = rand() % 9600 - 4800;
	m_targetPos.y = rand() % 9600 - 4800;

	b = behaviour; // Give worker a behaviour
}

/// <summary>
/// Deconstructor
/// </summary>
Worker::~Worker() {}

/// <summary>
/// Function to check for collisions between player and walls
/// </summary>
/// <param name="grid"></param>
void Worker::checkCollision(Grid &grid) {
	// Sets up the position to check based on the worker position and velocity 
	float scalar = 1.03;
	sf::Vector2f playerPursue = m_position + (m_velocity * scalar);

	// Sets up grid dimensions
	int gridX = 50;
	int gridY = 50;
	int indexHorizontal = gridY;
	int indexVertical = 1;

	// Checks what tile the worker is in
	playerGridX = (playerPursue.x + 5000) / 200;
	playerGridY = (playerPursue.y + 5000) / 200;
	playerGrid = playerGridX * 50 + (playerGridY);
	if (tempGrid != playerGrid)
	{// If worker has changed tile since the last check
		gridChanged = true;
	}
	
	if (playerGrid >= 0 && playerGrid < 2500)
	{
		if (grid.nodes[playerGrid]->getCost() >= 9999) {
			// Checks if worker is hitting a wall	

				// Knock worker back
			m_position -= (m_velocity * 3.0f);
			m_velocity.x = -m_velocity.x * 0.6;
			m_velocity.y = -m_velocity.y * 0.6;

			// Change position worker is moving towards
			m_targetPos.x = rand() % 9600 - 4800;
			m_targetPos.y = rand() % 9600 - 4800;
		}
	}
	
}

/// <summary>
/// Function to calculate and update workers position
/// </summary>
/// <param name="vectorX"></param>
/// <param name="vectorY"></param>
void Worker::move(double vectorX, double vectorY) {
	// Calculate and assign position
	m_sprite.setPosition(m_sprite.getPosition().x + vectorX * 5, m_sprite.getPosition().y + vectorY * 5);
	m_position = m_sprite.getPosition();

	// Calculate and assign rotation
	double rotation = atan2(vectorY, vectorX)*180/PI;
	m_sprite.setRotation(rotation);
}

/// <summary>
/// Update function for the worker
/// </summary>
/// <param name="nodes"></param>
/// <param name="goalNode"></param>
void Worker::update(std::vector<Node*> &nodes, int goalNode) {
	
	if (magnet == false)
	{// If worker isn't pathfinding to player
		switch (b)
		{// Check workers behaviour
		case WANDER:
			steer = wander();	// Wander around
			break;
		default:
			break;
		}
		// Update position
		m_position += steer.linear;
		m_sprite.setPosition(m_position);
		m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed,
			m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed);
	}
	else {
	// worker is pathfinding to player
		// Find out what tile worker is in
		int WorkergridX = (m_sprite.getPosition().x + 5000) / 200;
		int WorkergridY = (m_sprite.getPosition().y + 5000) / 200;
		int Workergrid = WorkergridX * 50 + (WorkergridY);

		if (Workergrid != goalNode)
		{
			// Move towards player
			move(nodes[Workergrid]->getVectX(), nodes[Workergrid]->getVectY());
		}
		
	}

}

/// <summary>
/// Function for handling how the worker wanders
/// </summary>
/// <returns></returns>
handling Worker::wander() {
	// Calculates velocity based on position relative to target position
	m_velocity = m_targetPos - m_position;
	startCalc();

	// Updates angle so that sweeper will move left and right as they 
	// move towards their goal
	m_rotation = m_rotation +(MAX_ROTATION * ((rand() % 1) - 1));

	m_angleDev += m_changeAngle;
	m_rotation += m_angleDev;
	if (m_angleDev > MAX_ROTATION || m_angleDev < -MAX_ROTATION) {
		m_changeAngle *= -1;
	}
	m_sprite.setRotation(m_rotation); // Assigns new rotation to the sprite

	if (dist(m_targetPos, m_position) < 10) {
	// If worker has reached destination
		// Assign a new target destination
		m_targetPos.x = rand() % 9600 - 4800;
		m_targetPos.y = rand() % 9600 - 4800;
	}

	handling wanderSteer;
	wanderSteer.linear = m_velocity;
	wanderSteer.angular = 0.0;
	// Return new velocity
	return wanderSteer;
}

/// <summary>
/// Function that handles the rendering of the worker
/// </summary>
/// <param name="window"></param>
void Worker::render(sf::RenderWindow & window) {
	window.draw(m_sprite);	// Draws worker
}

/// <summary>
/// Function to render a dot onto the minimap at the workers position
/// </summary>
/// <param name="window"></param>
void Worker::renderDot(sf::RenderWindow &window) {
	// Set up dot
	sf::CircleShape shape(100);
	shape.setFillColor(sf::Color(255, 255, 0));
	shape.setPosition(m_sprite.getPosition());

	// Draw dot
	window.draw(shape);
}

/// <summary>
/// Function to calculate rotation so that worker faces its target
/// </summary>
/// <param name="rot"></param>
/// <param name="vel"></param>
/// <returns></returns>
float Worker::getNewRotation(float rot, sf::Vector2f vel) {
	if (mag(m_velocity) > 0.0) {
	// Makes sure worker is moving
	// Calculates rotation based on which way worker is moving
		float rotation = std::atan2(-m_velocity.x, m_velocity.y) * (180 / 3.14159);
		return (rotation + 90);
	}
	else {
	// If worker isn't moving
		return rot; // Just return current rotation
	}

}

/// <summary>
/// Function for calculating magnitude of a vector
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
float Worker::mag(sf::Vector2f v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}

/// <summary>
/// Function that handles updating of velocity and rotation
/// </summary>
void Worker::startCalc() {
	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		float magnitude = mag(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x / magnitude, m_velocity.y / magnitude);
		m_velocity = m_velocity * m_speed;
		m_rotation = getNewRotation(m_rotation, m_velocity);
	}

}

/// <summary>
/// Function that calculates and returns the distance between two vectors
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Worker::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}