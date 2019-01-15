#ifndef MISSILE_H
#define MISSILE_H

#include <SFML/Graphics.hpp>
#include <iostream>

struct pathing {
	sf::Vector2f linear;
	float angular;
};

class Missile
{
public:
	Missile(sf::Vector2f pos);
	~Missile() {}

	void update(sf::Vector2f playerPos, int & health);
	void render(sf::RenderWindow &window);

	float getNewRotation(float rot, sf::Vector2f vel);
	pathing seek(sf::Vector2f playerPos);

	float mag(sf::Vector2f v);
	void startCalc();
	float dist(sf::Vector2f v1, sf::Vector2f v2);

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_rotation;
	sf::Vector2f m_targetPos;

	const double DEG_TO_RAD = 3.14159 / 180.0f;
	const double RAD_TO_DEG = 180.0f / 3.14159;
	float m_speed;
	float MAX_FORWARD_SPEED = 3.0;
	const float MAX_ROTATION = 45;

	bool m_dead = false;
private:
	sf::Time m_time;
	sf::Clock m_clock;
	pathing steer;

};
#endif // !MISSILE_H

