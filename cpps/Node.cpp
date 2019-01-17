#include "../Classes/Node.h"
#include <iostream>
#include <math.h>

/// <summary>
/// Creates a node and assignes the cost if it is an obstacle.
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="size"></param>
/// <param name="obstacle"></param>
Node::Node(int x, int y, int size, int obstacle)
{
	rectSize = size;
	rectangle.setSize(sf::Vector2f(size, size));
	rectangle.setPosition(x, y);
	if (obstacle == 1)
	{
		setCost(999999);
	}
}

/// <summary>
/// Deconstructor for node.
/// </summary>
Node::~Node()
{
}

/// <summary>
/// Set the cost of a node for flow field pathfinding.
/// Set the costSet so it is not used again.
/// </summary>
/// <param name="x"></param>
void Node::setCost(double x)
{
	cost = x;
	costSet = true;
}

/// <summary>
/// Return the cost of the node
/// </summary>
/// <returns></returns>
double Node::getCost()
{
	return cost;
}

/// <summary>
/// Check if the node has already been used
/// </summary>
/// <returns></returns>
bool Node::checkSet()
{
	return costSet;
}

/// <summary>
/// Set the node has been used or not used.
/// Is used for reseting nodes.
/// </summary>
/// <param name="num"></param>
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

/// <summary>
/// Distance no longer used for efficiency
/// </summary>
/// <param name="goalX"></param>
/// <param name="goalY"></param>
void Node::setDistance(int goalX, int goalY)
{
	integrationField = cost;
}

/// <summary>
/// Get the integration field of a node.
/// </summary>
/// <returns></returns>
double Node::getIntegrationField()
{
	return integrationField;
}

/// <summary>
/// Set the integration field of a node.
/// </summary>
/// <param name="field"></param>
void Node::setIntegrationField(double field)
{
	integrationField = field;
}

/// <summary>
/// Set the vector used by ais for pathfinding.
/// </summary>
/// <param name="vectorX"></param>
/// <param name="vectorY"></param>
void Node::setVector(double vectorX, double vectorY)
{
	vectX = vectorX;
	vectY = vectorY;
}

/// <summary>
/// Get the X vector used for pathfinding.
/// </summary>
/// <returns></returns>
double Node::getVectX()
{
	return vectX;
}

/// <summary>
/// Get the Y vector used for pathfinding.
/// </summary>
/// <returns></returns>
double Node::getVectY()
{
	return vectY;
}


/// <summary>
/// Gets the position of node used for vector calculation
/// </summary>
/// <returns></returns>
int Node::getPositionX()
{
	return rectangle.getPosition().x;
}

/// <summary>
/// Gets the position of node used for vector calculation
/// </summary>
/// <returns></returns>
int Node::getPositionY()
{
	return rectangle.getPosition().y;
}