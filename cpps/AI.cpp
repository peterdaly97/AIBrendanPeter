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

	aiPosition = sf::Vector2f(x, y);
	aiVelocity = sf::Vector2f(0, 0);
	aiSprite.setPosition(aiPosition);
	aiRotation = 0;
	aiSpeed = 5;
}

AI::~AI()
{
}



void AI::update(sf::Vector2f playerPosition)
{
	for (Bullet * bullet : m_bullets) {
		bullet->update();
		if (bullet->m_lifeTime > bullet->MAX_LIFE) {
			m_bullets.erase(m_bullets.begin()); // ToDo: Stop memory leak
		}
	}



	m_bulletCounter++;
	if (dist(aiSprite.getPosition(),playerPosition) < 900) //&&
		//m_bulletCounter > BULLET_TIME)
	{
		double angleToPlayer = 0;
		/*
		double angleToPlayer = 0;
		float length1 = sqrt(playerPosition.x * playerPosition.x + playerPosition.y * playerPosition.y);// calculate modulus of Vector V1 i.e. |V1|
		float length2 = sqrt(aiSprite.getPosition().x * aiSprite.getPosition().x + aiSprite.getPosition().y * aiSprite.getPosition().y);
		// calculate modulus of Vector V2 i.e. |V2|
		float dot = playerPosition.x * aiSprite.getPosition().x + playerPosition.y * aiSprite.getPosition().y; // calculate dot product between two vectors.

		float a = dot / (length1 * length2);

		if (a >= 1.0)
			angleToPlayer = 0.0;
		else if (a <= -1.0)
			angleToPlayer = PI;// PI means π 
		else
			angleToPlayer = acos(a); // 0..PI

			*/
		double dot = aiSprite.getPosition().x * playerPosition.x + aiSprite.getPosition().y * playerPosition.y;
		double det = aiSprite.getPosition().x * playerPosition.y - aiSprite.getPosition().y * playerPosition.x;
		angleToPlayer = atan2(det, dot);


		angleToPlayer = angleToPlayer * 180 / PI;
		std::cout << "angle = " << +angleToPlayer << std::endl;
		m_bulletCounter = 0;
		m_bullets.push_back(new Bullet(aiSprite.getPosition(), angleToPlayer));
	}


}
/*void AI::checkPlayer() {
	for (int i = 0; i < m_bullets.size(); i++) {
		if (dist(m_bullets.at(i)->m_pos, player.m_position) < 150) {
			player.loseHealth();
			m_bullets.erase(m_bullets.begin() + i);
		}
	}
}*/
void AI::move(double vectorX,double vectorY)
{
	aiSprite.setPosition(aiSprite.getPosition().x + vectorX * aiSpeed, aiSprite.getPosition().y + vectorY * aiSpeed);
	double rotation = atan2(vectorY, vectorX)*180/PI;
	aiSprite.setRotation(rotation);
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