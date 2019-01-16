#pragma once
#include <SFML/Graphics.hpp>


class PowerUp
{
public:
	PowerUp(int x, int y, sf::Texture &powerTexture, int value);
	~PowerUp();
	void update(sf::Vector2f playerPosition, int &health);
	void draw(sf::RenderWindow & window);
	void renderDot(sf::RenderWindow & window);
	int checkCollected(sf::Vector2f playerPosition);

	int m_value;

private:
	
	sf::CircleShape shape;

	float dist(sf::Vector2f v1, sf::Vector2f v2);

	sf::Sprite powerSprite;

	sf::Vector2f powerPosition;
};
