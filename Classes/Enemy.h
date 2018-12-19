#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Player.h"

enum behaviour
{
	PURSUE,
	EVADE,
	PATROL,
	ARRIVE,
	SEEK
};

struct steering { 
	sf::Vector2f linear; 
	float angular; 
};

class Enemy
{
public:
	Enemy(behaviour behaviour, sf::Vector2f pos, float maxSpeed);

	~Enemy();

	void update(sf::Vector2f playerPos, sf::Vector2f playerVel);
	void render(sf::RenderWindow &window);

	float getNewRotation(float rot, sf::Vector2f vel);
	steering wander();
	steering seek(sf::Vector2f playerPos);
	steering flee(sf::Vector2f playerPos);
	float mag(sf::Vector2f v);
	void startCalc();
	float dist(sf::Vector2f v1, sf::Vector2f v2);
	steering arrive(sf::Vector2f playerPos);
	bool avoid(std::vector<sf::Vector2f *> enemies);

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_rotation;
	sf::Vector2f m_targetPos;

	const double DEG_TO_RAD = 3.14159 / 180.0f;
	const double RAD_TO_DEG = 180.0f / 3.14159;
	float m_speed;
	float MAX_FORWARD_SPEED = 2.5;
	const float MAX_ROTATION = 45;
	const float MAX_BACKWARD_SPEED = 2.5;
	const float TIME_TO_TARGET = 80.0f;

private:
	behaviour b;
	sf::Text m_text;
	sf::Font m_font;
	sf::CircleShape m_cone;

	float m_detectedColl = 0.0f;
	bool m_detected = false;
	sf::Vector2f m_detectedVec;
	behaviour m_original;

	float m_angleDev = 0.0f;
	float m_changeAngle = 1.0f;
	steering steer;
};

#endif //!Enemy_H

