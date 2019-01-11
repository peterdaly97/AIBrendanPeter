#include "../Classes/AI.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265

AI::AI(int x, int y, sf::Texture &aiTexture)
{

	aiPosition = sf::Vector2f(x, y);


	aiSprite.setTexture(aiTexture);
	aiSprite.setScale(0.3, 0.3);
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



void AI::update(double dt)
{


}
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
}