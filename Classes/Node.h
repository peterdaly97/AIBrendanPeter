#pragma once
#include <SFML/Graphics.hpp>

class Node
{
public:
	Node(int x, int y, int size, int obstacle);
	~Node();
	double getVectX();
	int getPositionX();
	int getPositionY();
	double getVectY();
	void setCost(double x);
	void setDistance(int goalX, int goalY);
	void setVector(double vectorX, double vectorY);
	void setIntegrationField(double field);
	void setCheck(int num);
	double getCost();
	double getIntegrationField();
	bool checkSet();
	int rectSize;

private:

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