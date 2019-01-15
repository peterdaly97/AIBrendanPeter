#include "../Classes/AI.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265

AI::AI(int x, int y, sf::Texture &aiTexture)
{

	aiPosition = sf::Vector2f(x, y);


	aiSprite.setTexture(aiTexture);
	aiSprite.setScale(0.2, 0.2);
	aiSprite.setOrigin(aiSprite.getLocalBounds().width / 2, aiSprite.getLocalBounds().height / 2);
	aiSprite.setPosition(aiPosition);

	aiVelocity = sf::Vector2f(0, 0);
	aiRotation = 0;
	aiSpeed = 5;
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
			m_bullets.push_back(new Bullet(aiSprite.getPosition(), angle));
		}
	}


}
void AI::move(double vectorX,double vectorY)
{
	aiSprite.setPosition(aiSprite.getPosition().x + vectorX * aiSpeed, aiSprite.getPosition().y + vectorY * aiSpeed);
	double rotation = atan2(vectorY, vectorX)*180/PI;
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