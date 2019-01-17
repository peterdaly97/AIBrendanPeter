#ifndef BULLET_H
#define BULLET_H

#include <SFML\Graphics.hpp>
#include <iostream>

class Bullet
{
public:
	// Constructor
	Bullet(sf::Vector2f pos, float rot, sf::Texture & tex);

	~Bullet() { }	// Deconstructor 

	// Update and render functions
	void update();	
	void render(sf::RenderWindow & window);

	// Physical attributes
	sf::Vector2f m_pos;
	float m_rot;
	sf::Vector2f m_impulse;
	int m_lifeTime;
	const int MAX_LIFE = 100;
	int m_speed;
	const double DEG_TO_RAD = 3.14159 / 180.0f;

	// Visual attributes
	sf::Sprite m_sprite;
	sf::Texture m_tex;
};
#endif // !BULLET_H

