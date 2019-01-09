#pragma once
#include <SFML/Graphics.hpp>

class AI
{
public:
	AI(int x, int y, sf::Texture &aiTexture);
	~AI();
	void update(double dt);
	void draw(sf::RenderWindow & window);
	void move(double vectorX,double vectorY);
	int getPositionX();
	int getPositionY();

private:
	sf::CircleShape shape;

	sf::Sprite aiSprite;

	sf::Vector2f aiPosition;
	sf::Vector2f aiVelocity;
	float aiRotation;
	double aiSpeed = 5;
};