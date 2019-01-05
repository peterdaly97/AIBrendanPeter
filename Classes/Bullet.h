#ifndef BULLET_H
#define BULLET_H

#include <SFML\Graphics.hpp>
#include <iostream>

class Bullet
{
public:

	Bullet(sf::Vector2f pos, float rot);

	~Bullet() { }

	void update();
	void render(sf::RenderWindow & window);

	sf::Vector2f m_pos;
	float m_rot;

	sf::Vector2f m_impulse;
	int m_lifeTime;


	sf::Sprite m_sprite;

	const int MAX_LIFE = 100;

private:

	sf::Texture m_tex;

	const double DEG_TO_RAD = 3.14159 / 180.0f;

	int m_speed;
};
#endif // !BULLET_H

