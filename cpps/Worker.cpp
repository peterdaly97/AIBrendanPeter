#include "../Classes/Worker.h"

Worker::Worker(act behaviour, sf::Vector2f pos) {

	m_texture.loadFromFile("assets/worker.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(3, 3);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_speed = 2.5;
	m_position = pos;
	m_sprite.setPosition(pos);

	m_targetPos.x = rand() % 2048;
	m_targetPos.y = rand() % 1080;
	b = behaviour;
}

Worker::~Worker() {

}

void Worker::update() {
	switch (b)
	{
	case FLEE:
		steer = flee(sf::Vector2f(0,0));
		break;
	case WANDER:
		steer = wander();
		break;
	default:
		break;
	}
	m_position += steer.linear;
	m_sprite.setPosition(m_position);
	m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed,
		m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed);

}

handling Worker::wander() {
	m_velocity = m_targetPos - m_position;
	startCalc();
	m_rotation = m_rotation + (MAX_ROTATION * ((rand() % 1) - 1));

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

	handling wanderSteer;
	wanderSteer.linear = m_velocity;
	wanderSteer.angular = 0.0;
	return wanderSteer;
}

handling Worker::flee(sf::Vector2f playerPos) {
	m_velocity = m_position - playerPos;
	startCalc();
	m_sprite.setRotation(m_rotation);

	handling fleeSteering;
	fleeSteering.linear = m_velocity;
	fleeSteering.angular = 0.0;
	return fleeSteering;
}

void Worker::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

float Worker::getNewRotation(float rot, sf::Vector2f vel)
{
	if (mag(m_velocity) > 0.0) {
		float rotation = std::atan2(-m_velocity.x, m_velocity.y) * (180 / 3.14159);
		return (rotation + 90);
	}
	else {
		return rot;
	}

}

float Worker::mag(sf::Vector2f v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}

void Worker::startCalc() {
	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		float magnitude = mag(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x / magnitude, m_velocity.y / magnitude);
		m_velocity = m_velocity * m_speed;
		m_rotation = getNewRotation(m_rotation, m_velocity);
	}

}

float Worker::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}