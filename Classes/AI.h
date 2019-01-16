#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Player;

class AI
{
public:
	AI(int x, int y, sf::Texture &aiTexture);
	~AI();
	void update(sf::Vector2f playerPosition, int &health);
	void draw(sf::RenderWindow & window);
	void renderDot(sf::RenderWindow & window);
	void move(double vectorX,double vectorY);
	int getPositionX();
	int getPositionY();

	sf::Sprite aiSprite;

	std::vector<Bullet *> m_bullets;

private:
	int m_bulletCounter = 0;
	const int BULLET_TIME = 30;

	void checkPlayer(sf::Vector2f playerPosition);

	sf::CircleShape shape;

	float dist(sf::Vector2f v1, sf::Vector2f v2);


	sf::Vector2f aiPosition;
	sf::Vector2f aiVelocity;
	float aiRotation;
	double aiSpeed = 5;
};