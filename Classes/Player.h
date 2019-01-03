#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Bullet.h"
#include <vector>
#include "Worker.h"

class Player
{
public:
	Player();

	~Player();

	void update();
	void render(sf::RenderWindow &window);
	void handleInput();
	void move();

	void checkCollection(std::vector<Worker *> * workers);

	float dist(sf::Vector2f v1, sf::Vector2f v2);
	
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Keyboard m_keys;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_rotation;

	const double DEG_TO_RAD = 3.14159 / 180.0f;
	float m_speed;
	const float MAX_FORWARD_SPEED = 10;
	const float MAX_BACKWARD_SPEED = -5;

	sf::View m_view;

	std::vector<Bullet *> m_bullets;

	int m_health = 100;

	int m_collected = 0;

private:
	
	
};

#endif //!PLAYER_H
