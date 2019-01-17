#include "../Classes/AI.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265

/// <summary>
/// Constructor for predator ai.
/// Assign texture reference to sprites.
/// Set scale and start position for predators.
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="aiTexture"></param>
/// <param name="bulTex"></param>
AI::AI(int x, int y, sf::Texture &aiTexture, sf::Texture & bulTex)
{

	aiPosition = sf::Vector2f(x, y);


	aiSprite.setTexture(aiTexture);
	aiSprite.setScale(0.2, 0.2);
	aiSprite.setOrigin(aiSprite.getLocalBounds().width / 2, aiSprite.getLocalBounds().height / 2);
	aiSprite.setPosition(aiPosition);

	aiVelocity = sf::Vector2f(0, 0);
	aiRotation = 0;
	aiSpeed = 5;

	m_bulletTexture = bulTex;
}

/// <summary>
/// AI deconstructor
/// </summary>
AI::~AI()
{
}


/// <summary>
/// Update predators.
/// Update every bullet in the container.
/// Control predator behaviour.
/// </summary>
/// <param name="playerPosition"></param>
/// <param name="health"></param>
void AI::update(sf::Vector2f playerPosition, int &health, Grid &grid)
{
	for (Bullet * bullet : m_bullets) {
		bullet->update();
		bullet->checkCollision(grid);
		if (bullet->m_lifeTime > bullet->MAX_LIFE) {
			m_bullets.erase(m_bullets.begin());

		}
	}
	for (int i = 0; i < m_bullets.size(); i++) {
		if (dist(m_bullets.at(i)->m_pos, playerPosition) < 35)  // Check if bullet hits player
		{
			health = health - 1;  // Reduce player health
			m_bullets.erase(m_bullets.begin() + i);  // Delete bullet after hit.
		}
	}



	m_bulletCounter++;  // Iterator bullet timer so can shoot again
	if (dist(aiSprite.getPosition(), playerPosition) < 900)  // Check if ai is close enough to player to shoot/surround
	{

		float angle = atan2(playerPosition.y - aiSprite.getPosition().y, playerPosition.x - aiSprite.getPosition().x);  // Angle to face the player.
		angle = angle * 180 / PI;

		aiSprite.setRotation(angle);  // Set sprite to face player.

		if (m_bulletCounter >= 35)  // Check if shoot is available
		{
			m_bulletCounter = 0;
			m_bullets.push_back(new Bullet(aiSprite.getPosition(), angle, m_bulletTexture));
		}
		surroundNow = true;
	}
	else
	{
		surroundNow = false;
		if (surrounded == true)  // Check to see if it has been counted before.
		{
			removeCount = true;  // Set bool to tell grid to remove a count from the surround amount.
			surrounded = false;  // Set the counted before to false. 
		}
	}


}

/// <summary>
/// Moves the predator with the desired vector
/// </summary>
/// <param name="vectorX"></param>
/// <param name="vectorY"></param>
void AI::move(double vectorX, double vectorY)
{
	// set velocity vector to 0 if that direction is not available.
	if (surroundNow != true)
	{
		aiSprite.setPosition(aiSprite.getPosition().x + vectorX * aiSpeed, aiSprite.getPosition().y + vectorY * aiSpeed);  // Move with pathfinding vector.
	}
	else
	{
		if (leftAvailable == false)
		{
			if (aiVelocity.x < 0)
			{
				aiVelocity.x = 0;
			}
		}
		if (rightAvailable == false)
		{
			if (aiVelocity.x > 0)
			{
				aiVelocity.x = 0;
			}
		}
		if (upAvailable == false)
		{
			if (aiVelocity.y < 0)
			{
				aiVelocity.y = 0;
			}
		}
		if (downAvailable == false)
		{
			if (aiVelocity.y > 0)
			{
				aiVelocity.y = 0;
			}
		}
		aiSprite.setPosition(aiSprite.getPosition().x + aiVelocity.x * aiSpeed, aiSprite.getPosition().y + aiVelocity.y * aiSpeed);  // Move with spot in circle vector.
	}
}


/// <summary>
/// Draw the predator and call bullets to draw themselves
/// </summary>
/// <param name="window"></param>
void AI::draw(sf::RenderWindow & window)
{
	window.draw(aiSprite);

	for (Bullet * bullet : m_bullets) {
		if (bullet) {
			bullet->render(window);
		}

	}
}

/// <summary>
/// Check to see if all directions are available and set bools accordingly.
/// </summary>
/// <param name="AIgrid"></param>
/// <param name="nodes"></param>
void AI::checkWalls(int AIgrid, std::vector<Node*> &nodes)
{
	int indexHorizontal = 50;
	int indexVertical = 1;
	leftAvailable = true;
	rightAvailable = true;
	upAvailable = true;
	downAvailable = true;

	if (nodes[AIgrid - indexHorizontal]->getCost() >= 9000)  // Left check
	{
		leftAvailable = false;
	}
	if (nodes[AIgrid + indexHorizontal]->getCost() >= 9000)  // Right check
	{
		rightAvailable = false;
	}
	if (nodes[AIgrid - indexVertical]->getCost() >= 9000)  // Up check
	{
		upAvailable = false;
	}
	if (nodes[AIgrid + indexVertical]->getCost() >= 9000)  // Down check
	{
		downAvailable = false;
	}
}

/// <summary>
/// Calculate distance between 2 vectors.
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float AI::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}

/// <summary>
/// Draw the predator dot for the radar
/// </summary>
/// <param name="window"></param>
void AI::renderDot(sf::RenderWindow &window) {
	sf::CircleShape shape(100);
	shape.setFillColor(sf::Color(255, 0, 0));
	shape.setPosition(aiSprite.getPosition());
	window.draw(shape);
}

/// <summary>
/// Calculate the velocity to desired position.
/// Use the player position and offset calculated by setSpot().
/// </summary>
/// <param name="position"></param>
void AI::surround(sf::Vector2f position)
{
	position.x = position.x + xOffset;
	position.y = position.y + yOffset;
	aiVelocity = position - aiSprite.getPosition();
	aiVelocity = normalise(aiVelocity);
}

/// <summary>
/// Calculate the spot in surround circle given amount of ais in the circle.
/// i = This ais iterator to get different spot to others.
/// </summary>
/// <param name="surroundCount"></param>
/// <param name="i"></param>
void AI::setSpot(int surroundCount, int i)
{
	xOffset = cos(2 * PI / surroundCount * i) * 300;
	yOffset = sin(2 * PI / surroundCount * i) * 300;
	surrounded = true;
}

/// <summary>
/// Normalise a vector
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
sf::Vector2f AI::normalise(sf::Vector2f vector)
{
	float length = sqrt((vector.x * vector.x) + (vector.y * vector.y));
	if (length != 0)
	{
		vector.x = vector.x / length;
		vector.y = vector.y / length;
	}
	return vector;
}

/// <summary>
/// Get the position of the ais.
/// Used for grid position calculation.
/// </summary>
/// <returns></returns>
int AI::getPositionX()
{
	return aiSprite.getPosition().x;
}

/// <summary>
/// Get the position of the ais.
/// Used for grid position calculation.
/// </summary>
/// <returns></returns>
int AI::getPositionY()
{
	return aiSprite.getPosition().y;
}
