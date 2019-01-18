#include "../Classes/Enemy.h"

/// <summary>
/// Constructor for the sweeper bot
/// </summary>
/// <param name="behaviour"></param>
/// <param name="pos"></param>
/// <param name="maxSpeed"></param>
/// <param name="tex"></param>
Enemy::Enemy(behaviour behaviour, sf::Vector2f pos, float maxSpeed, sf::Texture * tex) {
	// Sets up texture and sprite for sweeper bot
	m_sprite.setTexture(*tex);
	m_sprite.setScale(0.05, 0.05);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

	// Sets up physical attributes of sweeper
	m_position = pos;
	MAX_FORWARD_SPEED = maxSpeed;
	m_speed = 2.5;

	// Chooses random positon for sweeper to wander towards
	m_targetPos->x = rand() % maxRandom + minRandom;
	m_targetPos->y = rand() % maxRandom + minRandom;

	// Assigns a behaviour to the sweeper bot
	b = behaviour;
}

/// <summary>
/// Destructor for the enemy 
/// </summary>
Enemy::~Enemy() {}

/// <summary>
/// Update the enemy
/// </summary>
/// <param name="playerPos"></param>
/// <param name="playerVel"></param>
void Enemy::update(sf::Vector2f playerPos, sf::Vector2f playerVel) {

	checkPlayer(playerPos);	// Checks to see if the player is near

							// Checks what behaviour the sweeper has
	switch (b)
	{
	case SEEK:
		steer = seek(*m_targetPos);	// Seeks the target position
		break;
	case EVADE:
		steer = flee(playerPos);	// Flees from the player
		break;
	case PATROL:
		steer = wander();	// Wanders around
		break;
	default:
		break;
	}
	// Updates the players position
	m_position += steer.linear;
	m_sprite.setPosition(m_position);

	m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed,
		m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed);

}

/// <summary>
/// Checks for collisions between the sweeper bot and walls
/// </summary>
/// <param name="grid"></param>
void Enemy::checkCollision(Grid &grid) {

	// Sets up the position to check based on the sweeper position and velocity 
	float scalar = 1.03;
	sf::Vector2f playerPursue = m_position + (m_velocity * scalar);

	// Sets up grid dimensions
	int gridX = 50;
	int gridY = 50;
	int indexHorizontal = gridY;
	int indexVertical = 1;

	// Checks what tile the sweeper is in
	playerGridX = (playerPursue.x + 5000) / 200;
	playerGridY = (playerPursue.y + 5000) / 200;
	playerGrid = playerGridX * 50 + (playerGridY);
	if (tempGrid != playerGrid)
	{// If sweeper has changed tile since the last check
		gridChanged = true;
	}
	tempGrid = playerGrid;

	if (grid.nodes[playerGrid]->getCost() >= 9999) {
		// Checks if sweeper is hitting a wall

		// Knock sweeper back
		m_position -= (m_velocity * 3.0f);
		m_velocity.x = -m_velocity.x * 0.6;
		m_velocity.y = -m_velocity.y * 0.6;

		// Change position sweeper is moving towards
		m_targetPos->x = rand() % maxRandom + minRandom;
		m_targetPos->y = rand() % maxRandom + minRandom;
	}
}

/// <summary>
/// Function for checking how close the player is
/// </summary>
/// <param name="playerPos"></param>
void Enemy::checkPlayer(sf::Vector2f playerPos) {
	if (dist(playerPos, m_position) < 300) {
		// Is player less than 300 pixels away
		// Change position sweeper is moving towards
		m_targetPos->x = rand() % maxRandom + minRandom;
		m_targetPos->y = rand() % maxRandom + minRandom;
		if (b == behaviour::PATROL) {
			b = behaviour::EVADE;	// Evade the player
		}
	}
	else if (b == behaviour::EVADE) {
		// If player is further away 
		b = behaviour::PATROL;	// Go back to patrolling
	}
}

/// <summary>
/// Function for sweeper wandering around the base
/// </summary>
/// <returns></returns>
steering Enemy::wander() {
	// Calculates velocity based on position relative to target position
	m_velocity = *m_targetPos - m_position;
	startCalc();

	// Updates angle so that sweeper will move left and right as they 
	// move towards their goal
	m_angleDev += m_changeAngle;
	m_rotation += m_angleDev;
	if (m_angleDev > MAX_ROTATION || m_angleDev < -MAX_ROTATION) {
		m_changeAngle *= -1;
	}
	m_sprite.setRotation(m_rotation);	// Assigns new rotation to the sprite

	if (dist(*m_targetPos, m_position) < 10) {
		// If sweeper has reached destination
		// Assign a new target destination
		m_targetPos->x = rand() % maxRandom + minRandom;
		m_targetPos->y = rand() % maxRandom + minRandom;
	}

	steering wanderSteer;
	wanderSteer.linear = m_velocity;
	wanderSteer.angular = 0.0;
	// Return new velocity
	return wanderSteer;
}

/// <summary>
/// Function to handle fleeing from the player
/// </summary>
/// <param name="playerPos"></param>
/// <returns></returns>
steering Enemy::flee(sf::Vector2f playerPos) {
	// Calculates velocity based on position relative to player position 
	m_velocity = m_position - playerPos;	// Position - player position because you're moving away
	startCalc();
	m_sprite.setRotation(m_rotation);

	steering fleeSteering;
	fleeSteering.linear = m_velocity;
	fleeSteering.angular = 0.0;
	return fleeSteering;
}

/// <summary>
/// Function handle the sweeper chasing a position
/// </summary>
/// <param name="playerPos"></param>
/// <returns></returns>
steering Enemy::seek(sf::Vector2f playerPos) {
	// Calculates velocity based on position relative to player position
	m_velocity = playerPos - m_position; // Player position - position because you're moving towards
	startCalc();
	m_sprite.setRotation(m_rotation);

	steering seekSteering;
	seekSteering.linear = m_velocity;
	seekSteering.angular = 0.0;
	return seekSteering;
}

/// <summary>
/// Function that checks if theres a worker in the line of sight of the sweeper
/// </summary>
/// <param name="enemies"></param>
/// <returns></returns>
bool Enemy::lookFor(std::vector<Worker *> enemies) {
	for (Worker * w : enemies) {
		// Loops through workers
		if (mag(m_position - w->m_position) < 300 && w->m_position != m_position) {
			// Cheks if worker is close enough
			sf::Vector2f realVelPos = m_velocity + m_position;

			// C = m_position A = m_velocity B = Player Pos
			double Dir_C_to_A = atan2(realVelPos.y - m_position.y, realVelPos.x - m_position.x);
			double Dir_C_to_B = atan2(w->m_position.y - m_position.y, w->m_position.x - m_position.x);
			double Angle_ACB = Dir_C_to_A - Dir_C_to_B;

			// Handle wrap around
			const double Pi = acos(-1);
			if (Angle_ACB > Pi) Angle_ACB -= 2 * Pi;
			else if (Angle_ACB < -Pi) Angle_ACB += 2 * Pi;

			// Angle represents the angle between the worker and the sweeper
			float angle = Angle_ACB;
			angle = angle * RAD_TO_DEG;

			if (dist(w->m_position, m_position) < 50) {
				// If sweeper has caught worker
				b = behaviour::PATROL;	// Worker goes back to patrolling
				m_collected++;	// Increment amount sweeper has caught
				w->m_collected = true;	// Set worker to have been collected
				angle = 180;
			}

			if (angle < 45 && angle > -45) {
				// Worker is in line of sight of sweeper
				m_targetPos = &w->m_position;	// Sets target position to workers position
				b = behaviour::SEEK;	// Sweeper will now seek worker
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

/// <summary>
/// Function to render the sweeper
/// </summary>
/// <param name="window"></param>
void Enemy::render(sf::RenderWindow & window) {
	window.draw(m_sprite);	// Draws sweeper
}

/// <summary>
/// Function to render a dot onto the minimap at the sweepers position
/// </summary>
/// <param name="window"></param>
void Enemy::renderEnemyDot(sf::RenderWindow &window) {
	// Sets up dot
	sf::CircleShape shape(100);
	shape.setFillColor(sf::Color(255, 51, 204));
	shape.setPosition(m_sprite.getPosition());

	// Draws dot onto the minimap
	window.draw(shape);
}

/// <summary>
/// Function to calculate rotation so that sweeper faces its target
/// </summary>
/// <param name="rot"></param>
/// <param name="vel"></param>
/// <returns></returns>
float Enemy::getNewRotation(float rot, sf::Vector2f vel) {

	if (mag(m_velocity) > 0.0) {
		// Makes sure sweeper is moving
		// Calculates rotation based on which way sweeper is moving
		float rotation = std::atan2(-m_velocity.x, m_velocity.y) * (180 / 3.14159);
		return (rotation + 90);
	}
	else {
		// If sweeper isn't moving
		return rot;	// Just return current rotation
	}

}

/// <summary>
/// Function for calculating magnitude of a vector
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
float Enemy::mag(sf::Vector2f v) {
	// Return magnitude of passed vector
	return std::sqrt(v.x * v.x + v.y * v.y);
}

/// <summary>
/// Function that handles updating of velocity and rotation
/// </summary>
void Enemy::startCalc() {
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
float Enemy::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}
