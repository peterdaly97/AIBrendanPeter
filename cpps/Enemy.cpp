#include "../Classes/Enemy.h"

Enemy::Enemy(behaviour behaviour, sf::Vector2f pos, float maxSpeed, sf::Texture * tex) {

	srand(time(0));
	m_sprite.setTexture(*tex);
	m_position = pos;
	MAX_FORWARD_SPEED = maxSpeed;
	m_sprite.setScale(0.05, 0.05);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

	m_speed = 2.5;

	m_targetPos.x = rand() % 2048;
	m_targetPos.y = rand() % 1080;
	b = behaviour;
	m_original = behaviour;

	if (!m_font.loadFromFile("assets/arial.ttf"))	// Checks to make sure font is correct
	{
		std::cout << "Problem loading font file!" << std::endl;
	}

	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::White);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);

	m_cone = sf::CircleShape(150);
	m_cone.setFillColor(sf::Color(255,255,255, 80));
	m_cone.setOrigin(m_cone.getLocalBounds().width / 2, m_cone.getLocalBounds().height / 2);
}



Enemy::~Enemy() {}


void Enemy::update(sf::Vector2f playerPos, sf::Vector2f playerVel) {
	
	
	int scalar = 30;
	playerVel = sf::Vector2f(playerVel.x * scalar, playerVel.y * scalar);
	sf::Vector2f playerPursue = playerPos + playerVel;

	switch (b)
	{
	case PURSUE:
		m_text.setString("Pursue");
		steer = seek(playerPursue);
		break;
	case SEEK:
		m_text.setString("Seek");
		steer = seek(playerPos);
		break;
	case EVADE:
		m_text.setString("Evade");
		if (m_detected) {
			m_detectedColl++;
			steer = flee(m_detectedVec);
			if (m_detectedColl >= 120) {
				b = m_original;
				m_detected = false;
				m_detectedColl = 0;
			}
		}
		else {
			steer = flee(playerPos);
		}
		break;
	case PATROL:
		m_text.setString("Patrol");
		steer = wander();
		break;
	case ARRIVE:
		m_text.setString("Arrive");
		steer = arrive(playerPos);
		break;
	default:
		break;
	}
	m_position += steer.linear;
	m_sprite.setPosition(m_position);

	m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed,
		m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed);
	m_text.setPosition(m_position);
	m_cone.setPosition(m_position.x, m_position.y);
}

steering Enemy::wander() {
	m_velocity = m_targetPos - m_position;
	startCalc();
	//m_rotation = m_rotation + (MAX_ROTATION * ((rand() % 1) - 1));

	m_angleDev += m_changeAngle;
	m_rotation += m_angleDev;
	if (m_angleDev > MAX_ROTATION || m_angleDev < -MAX_ROTATION) {
		m_changeAngle *= -1;
	}
	m_sprite.setRotation(m_rotation);
	
	if (dist(m_targetPos, m_position) < 10) {
		m_targetPos.x = rand() % 3840;
		m_targetPos.y = rand() % 2160;
	}

	steering wanderSteer;
	wanderSteer.linear = m_velocity;
	wanderSteer.angular = 0.0;
	return wanderSteer;
}

steering Enemy::flee(sf::Vector2f playerPos) {
	m_velocity = m_position - playerPos;
	startCalc();
	m_sprite.setRotation(m_rotation);

	steering fleeSteering;
	fleeSteering.linear = m_velocity;
	fleeSteering.angular = 0.0;
	return fleeSteering;
}

steering Enemy::seek(sf::Vector2f playerPos) {
	
	m_velocity = playerPos - m_position;
	startCalc();
	m_sprite.setRotation(m_rotation);

	steering seekSteering;
	seekSteering.linear = m_velocity;
	seekSteering.angular = 0.0;
	return seekSteering;
}

steering Enemy::arrive(sf::Vector2f playerPos) {
	m_velocity = playerPos - m_position;
	m_velocity = sf::Vector2f(m_velocity.x / TIME_TO_TARGET, m_velocity.y / TIME_TO_TARGET);
	if (mag(m_velocity) > MAX_FORWARD_SPEED) {
		m_velocity = sf::Vector2f(m_velocity.x / mag(m_velocity), m_velocity.y / mag(m_velocity));
		m_velocity *= MAX_FORWARD_SPEED;
	}
	m_rotation = getNewRotation(m_rotation, m_velocity);
	m_sprite.setRotation(m_rotation);
	steering arriveSteer;
	arriveSteer.linear = m_velocity;
	arriveSteer.angular = 0.0;
	return arriveSteer;
}

bool Enemy::avoid(std::vector<sf::Vector2f *> enemies) {
	for (sf::Vector2f * enemy : enemies) {
		if (mag(m_position - *enemy) < m_cone.getRadius() && *enemy != m_position) {
			sf::Vector2f realVelPos = m_velocity + m_position;

			// C = m_position A = m_velocity B = Player Pos
			double Dir_C_to_A = atan2(realVelPos.y - m_position.y, realVelPos.x - m_position.x);
			double Dir_C_to_B = atan2(enemy->y - m_position.y, enemy->x - m_position.x);
			double Angle_ACB = Dir_C_to_A - Dir_C_to_B;

			// Handle wrap around
			const double Pi = acos(-1);
			if (Angle_ACB > Pi) Angle_ACB -= 2 * Pi;
			else if (Angle_ACB < -Pi) Angle_ACB += 2 * Pi;

			float angle = Angle_ACB;
			angle = angle * RAD_TO_DEG;

			if (angle < 45 && angle > -45) {
				b = behaviour::EVADE;
				m_detectedVec = *enemy;
				m_detected = true;
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

void Enemy::die() {
	delete this;
}


void Enemy::render(sf::RenderWindow & window) {

	window.draw(m_sprite);
	window.draw(m_text);
	window.draw(m_cone);
}

float Enemy::getNewRotation(float rot, sf::Vector2f vel) {

	if (mag(m_velocity) > 0.0) {
		float rotation = std::atan2(-m_velocity.x, m_velocity.y) * (180 / 3.14159);
		return (rotation + 90);
	}
	else {
		return rot;
	}

}

float Enemy::mag(sf::Vector2f v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}

void Enemy::startCalc() {
	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		float magnitude = mag(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x / magnitude, m_velocity.y / magnitude);
		m_velocity = m_velocity * m_speed;
		m_rotation = getNewRotation(m_rotation, m_velocity);
	}
	
}

float Enemy::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}
