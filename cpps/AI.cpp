#include "../Classes/AI.h"
#include <iostream>
#include <math.h>

AI::AI(int x, int y)
{
	shape.setRadius(4);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(x, y);
}

AI::~AI()
{
}



void AI::update(double dt)
{


}
void AI::move(double vectorX,double vectorY)
{
	shape.setPosition(shape.getPosition().x + vectorX * speed, shape.getPosition().y + vectorY * speed);
}


int AI::getPositionX()
{
	return shape.getPosition().x;
}
int AI::getPositionY()
{
	return shape.getPosition().y;
}
void AI::draw(sf::RenderWindow & window)
{
	window.draw(shape);
}