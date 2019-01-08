#include "../Classes/Node.h"
#include <iostream>
#include <math.h>

Node::Node(int x, int y, int size, sf::Font &costFont, int obstacle)
{


	rectSize = size;

	rectangle.setSize(sf::Vector2f(size, size));
	rectangle.setFillColor(sf::Color::White);
	rectangle.setPosition(x, y);

	if (obstacle == 1)
	{
		setCost(999999);
	}

}

Node::~Node()
{
}



void Node::update(double dt)
{


}
void Node::swapIntegrationCalc()
{
	if (useDistance == false)
	{
		useDistance = true;
	}
	else
	{
		useDistance = false;
	}
}
void Node::setCost(double x)
{
	cost = x;
	if (cost < 64)
	{
		rectangle.setFillColor(sf::Color(0, 255 - (cost * 4), 255, 255));
	}
	else
	{
		rectangle.setFillColor(sf::Color(0, 0, 255, 255));
	}
	if (cost >= 999999)
	{
		rectangle.setFillColor(sf::Color(0, 0, 0, 0));
	}
	
	costSet = true;
}
double Node::getCost()
{
	return cost;
}
bool Node::checkSet()
{
	return costSet;
}
void Node::setCheck(int num)
{
	if (num == 0)
	{
		costSet = false;
	}
	if (num == 1)
	{
		costSet = true;
	}
}


void Node::setDistance(int goalX, int goalY)
{
	//distanceToGoal = sqrt((((goalX - (rectangle.getPosition().x + (rectSize/2)))*(goalX - (rectangle.getPosition().x + (rectSize / 2)))) + ((goalY - (rectangle.getPosition().y + (rectSize / 2)))*(goalY - (rectangle.getPosition().y + (rectSize / 2))))));
	integrationField = cost;
}
double Node::getIntegrationField()
{
	return integrationField;
}
void Node::setIntegrationField(double field)
{
	integrationField = field;
}
void Node::setColor(sf::Color color)
{
	if (start == false)
	{
		rectangle.setFillColor(color);
		start = true;
	}
	else if (goal == false)
	{
		rectangle.setFillColor(sf::Color::Red);
		goal = true;
	}
	//rectangle.setFillColor(color);
}
void Node::setVector(double vectorX, double vectorY)
{
	vectX = vectorX;
	vectY = vectorY;
}
double Node::getVectX()
{
	return vectX;
}
double Node::getVectY()
{
	return vectY;
}
int Node::getPositionX()
{
	return rectangle.getPosition().x;
}
int Node::getPositionY()
{
	return rectangle.getPosition().y;
}
void Node::draw(sf::RenderWindow & window)
{
	//window.draw(rectangle);
	//window.draw(m_groundSprite);

//	sf::Vertex line[] =
//	{
//		sf::Vertex(sf::Vector2f((rectangle.getPosition().x + (rectSize / 2)), (rectangle.getPosition().y + (rectSize / 2))),sf::Color::Magenta),
//		sf::Vertex(sf::Vector2f((rectangle.getPosition().x + (rectSize / 2))+ (vectX * 15), (rectangle.getPosition().y + (rectSize / 2)) + (vectY * 15)),sf::Color::Magenta)
//	};
//	if (vectorDraw == true)
//	{
//		window.draw(line, 2, sf::Lines);
//	}
}