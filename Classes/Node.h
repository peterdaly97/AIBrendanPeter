#pragma once
#include <SFML/Graphics.hpp>

class Node
{
public:
	Node(int x, int y, int size, sf::Font &costFont, sf::Texture &groundTexture, sf::Texture &obstacleTexture, int obstacle);
	~Node();
	void update(double dt);
	void draw(sf::RenderWindow & window);
	int getPositionX();
	int getPositionY();
	double getVectX();
	double getVectY();
	void setColor(sf::Color color);
	void setCost(double x);
	void setDistance(int goalX,int goalY);
	void setVector(double vectorX, double vectorY);
	void setIntegrationField(double field);
	void setCheck(int num);
	double getCost();
	double getIntegrationField();
	bool checkSet();
	int rectSize;
	//sf::Vertex Line[2];
	void swapIntegrationCalc();

private:

	sf::Sprite m_groundSprite;

	bool useDistance = true;
	double vectX = 0;
	double vectY = 0;
	double integrationField = 0;
	sf::RectangleShape rectangle;
	bool start = false;
	bool goal = false;
	bool costSet = false;
	double cost = 0;
};