#pragma once
#include <SFML/Graphics.hpp>

class AI
{
public:
	AI(int x, int y);
	~AI();
	void update(double dt);
	void draw(sf::RenderWindow & window);
	void move(double vectorX,double vectorY);
	int getPositionX();
	int getPositionY();

private:
	sf::CircleShape shape;
	double speed = 5;
};