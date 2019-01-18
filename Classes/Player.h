#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Bullet.h"
#include <vector>
#include "Worker.h"
#include "grid.h"
#include "ParticleSystem.h"

// Declaring classes so that player can reference them before they can compile
class Nest;
class Enemy;

class Player
{
public:
	Player();	// Constructor

	~Player();	// Destructor

	void update(Grid &grid);	// Update function

	void checkCollision(Grid &grid);	// Function that checks walls for collision

	void render(sf::RenderWindow &window);	// Render function
	void renderDot(sf::RenderWindow &window);	// Function to position and render dots on minimap
	void handleInput();	// Function to check input and call necessary functions based on it
	void move();	// Function to handle the movement of the player
	void animationUpdate();	// Function that updates the animation of the engine fire
	void powerUp(int power);	// Function that is triggered when player collects power up

	void checkCollection(std::vector<Worker *> * workers);	// Function to check if worker was collected

	void checkNest(Nest & nest);	// Checks to see if any bullets have hit nest

	// Functions to see if any nests were hit by bullets
	void checkEnemies(std::vector<Enemy *> & enemies, std::vector<ParticleSystem *> & ps);
	bool checkPreds(std::vector<AI *> & ais, std::vector<ParticleSystem *> & ps);

	// Math function that checks and returns the distance between two vectors
	float dist(sf::Vector2f v1, sf::Vector2f v2);

	// All textures and sprites belonging to the player
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Texture m_fireTexture;
	sf::Sprite m_fireSprite;
	sf::IntRect rectSourceSprite;

	sf::Keyboard m_keys;	// Keyboard object that will be checked

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_rotation;

	const double DEG_TO_RAD = 3.14159 / 180.0f;
	float m_speed;
	const float MAX_FORWARD_SPEED = 10;
	const float MAX_BACKWARD_SPEED = -5;

	sf::View m_view;	// View for the main game screen. Based on player position

	std::vector<Bullet *> m_bullets;	// All bullets fired by the player that are currently alive

	int m_health = 100;

	int m_collected = 0;	// How many workers collected by the player

	bool gridChanged = false;	// Has the player moved into a new grid section
	int tempGrid = 999999;	// Tempory value for cost of moving into new grid section

	bool magnet = false;	// Has the player hit the magnet power up

	bool m_blast = false;	// Can the player use the blast attack

	sf::Texture m_bulletTex;

	int m_score = 0; // The players score

private:
	int maxMagnet = 400;
	int magnetCount = 0;

	int gridChangedCount = 0;

	// Current time and max amount of time before player can fire another bullet
	int m_bulletCounter = 0;
	const int BULLET_TIME = 15;

	bool drawFireBack = false;

	int playerGrid = 0;
	int playerGridX = 0;
	int playerGridY = 0;

};


#endif // !PLAYER_H



