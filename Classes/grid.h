#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "AI.h"

class Node;
class AI;

class Grid
{
public:
	Grid();
	~Grid();
	void update(sf::RenderWindow & window);
	void updateAI(sf::Vector2f position, int &health);
	void draw(sf::RenderWindow & window);
	void renderDots(sf::RenderWindow & window);
	void seek(int goal);
	std::vector<Node*> nodes;

	int goalNode = 0;

	std::vector<AI*> ais;
	

private:

	sf::Texture m_groundTexture;
	sf::Texture AItexture;
	sf::Texture m_obstacleTexture;

	bool zPressed = false;
	int randomSize = 1;
	int rectSize = 200;
	int gridX = 50;
	int gridY = 50;
	void setCost();
	void setVector();
	void setDistance();
	void moveAI();
	void createGrid(int random);
	void makeMap();
	void clearAll();
	//Player* m_player;
	sf::Font costFont;

	sf::Text randomText;

	bool UpPressed = false;
	bool DownPressed = false;

	bool mapMade = false;

	int mapCount = 0;

	bool UpAvailable = true;
	bool DownAvailable = true;
	bool LeftAvailable = true;
	bool RightAvailable = true;
	bool startSet = false;
	bool goalSet = false;
	bool leftPressed = false;
	double tempX = 0;
	double tempY = 0;

	sf::RectangleShape rectangle;
	Node* node;
	
	AI* ai;
};
