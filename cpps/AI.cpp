#include "../Classes/AI.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265

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

AI::~AI()
{
}



void AI::update(sf::Vector2f playerPosition, int &health)
{
	for (Bullet * bullet : m_bullets) {
		bullet->update();
		if (bullet->m_lifeTime > bullet->MAX_LIFE) {
			m_bullets.erase(m_bullets.begin()); // ToDo: Stop memory leak

		}
	}
	for (int i = 0; i < m_bullets.size(); i++) {
		if (dist(m_bullets.at(i)->m_pos, playerPosition) < 35) {
			//player.loseHealth();
			health = health - 1;
			m_bullets.erase(m_bullets.begin() + i);
		}
	}



	m_bulletCounter++;
	if (dist(aiSprite.getPosition(),playerPosition) < 900) //&&
		//m_bulletCounter > BULLET_TIME)
	{	

		float angle = atan2(playerPosition.y - aiSprite.getPosition().y, playerPosition.x - aiSprite.getPosition().x);
		angle = angle * 180 / PI;

		aiSprite.setRotation(angle);
	    
		if (m_bulletCounter >= 35)
		{
			m_bulletCounter = 0;
			m_bullets.push_back(new Bullet(aiSprite.getPosition(), angle, m_bulletTexture));
		}
		surroundNow = true;
	}


}
void AI::move(double vectorX,double vectorY)
{
	if (surroundNow != true)
	{
		aiSprite.setPosition(aiSprite.getPosition().x + vectorX * aiSpeed, aiSprite.getPosition().y + vectorY * aiSpeed);
	}
	else
	{
		aiSprite.setPosition(aiSprite.getPosition().x + aiVelocity.x * aiSpeed, aiSprite.getPosition().y + aiVelocity.y * aiSpeed);
	}
	//double rotation = atan2(vectorY, vectorX)*180/PI;
	//aiSprite.setRotation(rotation);
}

int AI::getPositionX()
{
	return aiSprite.getPosition().x;
}
int AI::getPositionY()
{
	return aiSprite.getPosition().y;
}
void AI::draw(sf::RenderWindow & window)
{
	window.draw(aiSprite);

	for (Bullet * bullet : m_bullets) {
		if (bullet) {
			bullet->render(window);
		}

	}
}
float AI::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}
void AI::renderDot(sf::RenderWindow &window) {
	sf::CircleShape shape(100);
	shape.setFillColor(sf::Color(255, 0, 0));
	shape.setPosition(aiSprite.getPosition());
	window.draw(shape);
}
void AI::surround(sf::Vector2f position)
{
	/*
	if (spot == 1)
	{
		position.x = position.x - 300;  //left
	}
	if (spot == 2)
	{
		position.y = position.y - 300;  //bottom
	}
	if (spot == 3)
	{
		position.x = position.x + 300;  //right
	}
	if (spot == 4)
	{
		position.y = position.y + 300;  //bottom
	}
	if (spot == 5)
	{
		position.x = position.x - 200;
		position.y = position.y - 200;  //top left
	}
	if (spot == 6)
	{
		position.x = position.x - 200;
		position.y = position.y + 200;  //bottom left
	}
	if (spot == 7)
	{
		position.x = position.x + 200;
		position.y = position.y - 200;  //top right
	}
	if (spot == 8)
	{
		position.x = position.x + 200;
		position.y = position.y + 200;  //bottom right
	}
	if (spot == 9)
	{
		position.x = position.x + 200;
		position.y = position.y + 200;  //bottom right right
	}
	if (spot == 10)
	{
		position.x = position.x + 200;
		position.y = position.y + 200;  //top right right
	}
	if (spot == 11)
	{
		position.x = position.x + 150;
		position.y = position.y + 150;  //bottom left left
	}
	if (spot == 12)
	{
		position.x = position.x + 200;
		position.y = position.y + 200;  //top left left
	} */
	// return [(math.cos(2*pi/n*x)*r,math.sin(2*pi/n*x)*r) for x in range(0,n+1)]
	position.x = position.x + xOffset;
	position.y = position.y + yOffset;
	aiVelocity = position - aiSprite.getPosition();
	aiVelocity = normalise(aiVelocity);
	//aiVelocity.x = aiVelocity.x * maxSpeed;
	//aiVelocity.y = aiVelocity.y * maxSpeed;
}
void AI::setSpot(int surroundCount, int i)
{
	xOffset = cos(2 * PI / surroundCount * i) * 300;
	yOffset = sin(2 * PI / surroundCount * i) * 300;
	//spot = surroundCount;
	surrounded = true;
}
sf::Vector2f AI::normalise(sf::Vector2f vector)
{
	//length = sqrt((ax * ax) + (ay * ay) + (az * az))
	float length = sqrt((vector.x * vector.x) + (vector.y * vector.y));
	//divide each by length
	if (length != 0)
	{
		vector.x = vector.x / length;
		vector.y = vector.y / length;
	}
	return vector;

}
