#pragma once
#include <SFML/Graphics.hpp>


class PowerUp
{
public:
	// Constructor
	PowerUp(int x, int y, sf::Texture &powerTexture, int value);
	~PowerUp();	// Deconstructor

	// Render function
	void draw(sf::RenderWindow & window);

	// Function for rendering dot on the mini map
	void renderDot(sf::RenderWindow & window);

	// Function for checking to see if it was collected by the player
	int checkCollected(sf::Vector2f playerPosition);

	int m_value;	// The value which determines what type of powerup its is

	bool m_collected = false;

private:
	
	sf::CircleShape shape;	// Shape to be drawn on minimap

	// Function that calculates the distance between 2 vectors
	float dist(sf::Vector2f v1, sf::Vector2f v2);	

	sf::Sprite powerSprite;	// Sprite of pick up

	sf::Vector2f powerPosition;	// Position of pick up
};
