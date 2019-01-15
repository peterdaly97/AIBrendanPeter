#include "../Classes/Worker.h"

#define PI 3.14159265

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

void Worker::checkCollision(Grid &grid) {
	float scalar = 1.03;
	sf::Vector2f playerPursue = m_position + (m_velocity * scalar);

	//playerPursue = sf::Vector2f(playerPursue.x * scalar, playerPursue.y * scalar);

	int gridX = 50;
	int gridY = 50;
	int indexHorizontal = gridY;
	int indexVertical = 1;

	playerGridX = (playerPursue.x + 5000) / 200;
	playerGridY = (playerPursue.y + 5000) / 200;
	playerGrid = playerGridX * 50 + (playerGridY);
	if (tempGrid != playerGrid)
	{
		gridChanged = true;
	}
	tempGrid = playerGrid;

	//std::cout << playerGrid << std::endl;
	if (grid.nodes[playerGrid]->getCost() >= 9999) {
		m_position -= m_velocity;
		m_velocity.x = -m_velocity.x * 0.6;
		m_velocity.y = -m_velocity.y * 0.6;

		m_targetPos.x = rand() % 3840;
		m_targetPos.y = rand() % 2160;
	}
}

void Worker::move(double vectorX, double vectorY)
{
	m_sprite.setPosition(m_sprite.getPosition().x + vectorX * 5, m_sprite.getPosition().y + vectorY * 5);
	m_position = m_sprite.getPosition();
	double rotation = atan2(vectorY, vectorX)*180/PI;
	m_sprite.setRotation(rotation);
}
void Worker::update(std::vector<Node*> &nodes, int goalNode) {
	if (magnet == false)
	{
		switch (b)
		{
		case FLEE:
			steer = flee(sf::Vector2f(0, 0));
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
	else {
		int WorkergridX = (m_sprite.getPosition().x + 5000) / 200;
		int WorkergridY = (m_sprite.getPosition().y + 5000) / 200;
		int Workergrid = WorkergridX * 50 + (WorkergridY);

		if (Workergrid == goalNode)
		{
			//ais.erase(ais.begin() + x);
		}
		else
		{
			move(nodes[Workergrid]->getVectX(), nodes[Workergrid]->getVectY());
		}
		
	}

}

handling Worker::wander() {
	m_velocity = m_targetPos - m_position;
	startCalc();
	//m_rotation = m_rotation +(MAX_ROTATION * ((rand() % 1) - 1));

	/*m_angleDev += m_changeAngle;
	m_rotation += m_angleDev;
	if (m_angleDev > MAX_ROTATION || m_angleDev < -MAX_ROTATION) {
		m_changeAngle *= -1;
	}*/
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
void Worker::renderDot(sf::RenderWindow &window) {
	sf::CircleShape shape(100);
	shape.setFillColor(sf::Color(255, 255, 0));
	shape.setPosition(m_sprite.getPosition());
	window.draw(shape);
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