#include "../Classes/PowerUp.h"
#include <iostream>
#include <math.h>


PowerUp::PowerUp(int x, int y, sf::Texture &powerTexture, int value)
{

	powerPosition = sf::Vector2f(x, y);

	m_value = value;
	powerSprite.setTexture(powerTexture);
	powerSprite.setOrigin(powerSprite.getLocalBounds().width / 2, powerSprite.getLocalBounds().height / 2);
	powerSprite.setPosition(powerPosition);
}

PowerUp::~PowerUp()
{
}



void PowerUp::update(sf::Vector2f playerPosition, int &health)
{
}
int PowerUp::checkCollected(sf::Vector2f playerPosition)
{
	if (dist(powerSprite.getPosition(), playerPosition) < 80) {
		//player.loseHealth();
		return m_value;
	}
	return 0;
}



void PowerUp::draw(sf::RenderWindow & window)
{
	window.draw(powerSprite);
}
float PowerUp::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}
void PowerUp::renderDot(sf::RenderWindow &window) {
	sf::CircleShape shape(100);
	shape.setFillColor(sf::Color(51, 153, 255));
	shape.setPosition(powerSprite.getPosition());
	window.draw(shape);
}