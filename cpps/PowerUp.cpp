#include "../Classes/PowerUp.h"
#include <iostream>
#include <math.h>

/// <summary>
/// Constructor
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="powerTexture"></param>
/// <param name="value"></param>
PowerUp::PowerUp(int x, int y, sf::Texture &powerTexture, int value) {
	// Give pick up a position
	powerPosition = sf::Vector2f(x, y);

	m_value = value;	// Set the value of the power up

	// Set up the visual attributes of the pick up
	powerSprite.setTexture(powerTexture);
	powerSprite.setOrigin(powerSprite.getLocalBounds().width / 2, powerSprite.getLocalBounds().height / 2);
	powerSprite.setPosition(powerPosition);
}

/// <summary>
/// Deconstructor 
/// </summary>
PowerUp::~PowerUp() {}

/// <summary>
/// Function for checking if pick up was collected
/// </summary>
/// <param name="playerPosition"></param>
/// <returns></returns>
int PowerUp::checkCollected(sf::Vector2f playerPosition) {
	if (dist(powerSprite.getPosition(), playerPosition) < 80) {
	// Checks if player hit pick up
		return m_value;	// Return the value of the collected pick up
	}
	return 0;
}

/// <summary>
/// Function for drawing the pick ups
/// </summary>
/// <param name="window"></param>
void PowerUp::draw(sf::RenderWindow & window) {
	window.draw(powerSprite); // Draws the pick up
}

/// <summary>
/// Function that calculates the distance between 2 vectors
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float PowerUp::dist(sf::Vector2f v1, sf::Vector2f v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}

/// <summary>
/// Function to position and render dots on minimap
/// </summary>
/// <param name="window"></param>
void PowerUp::renderDot(sf::RenderWindow &window) {
	// Sets up dot
	sf::CircleShape shape(100);
	shape.setFillColor(sf::Color(51, 153, 255));
	shape.setPosition(powerSprite.getPosition());

	// Draws dot
	window.draw(shape);
}