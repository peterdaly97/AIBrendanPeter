#include "../Classes/grid.h"
#include <iostream>
#include <fstream>
#include <math.h>


/// <summary>
/// Grid constructor.
/// Load in textures for predators.
/// Call create.
/// </summary>
Grid::Grid()
{
	AItexture.loadFromFile("assets/predator.png");
	createGrid(randomSize);
}

/// <summary>
/// Initialises a new grid with hard coded values
/// </summary>
/// <param name="random"></param>
void Grid::createGrid(int random)
{
	srand(time(NULL));

	// values for grid world. 1 = obstacle
	int map[50][50] =
	{ { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	// For loop to create a nide at each grid spot and pass if it is an obstacle
	for (int x = 1; x <= gridX; x++)
	{
		for (int y = 1; y <= gridY; y++)
		{

			node = new Node(-5200 + x * (rectSize), -5200 + y * (rectSize), rectSize, map[x - 1][y - 1]);
			nodes.push_back(node);
		}
	}
}

/// <summary>
/// deconstructor for grid
/// </summary>
Grid::~Grid()
{
}

/// <summary>
/// creates a predator AI at the desired position
/// </summary>
/// <param name="position"></param>
void Grid::spawnPred(sf::Vector2f position)
{
	// Pass position and textures to new ai and push to ai container.
	ai = new AI(position.x + (rectSize / 2), position.y + (rectSize / 2), AItexture, m_bulletTex);
	ais.push_back(ai);
	// Start set will initiate the pathfinding
	startSet = true;
}

/// <summary>
/// Move the predators is called
/// Grid key press functionality removed
/// </summary>
/// <param name="window"></param>
void Grid::update(sf::RenderWindow & window)
{
	sf::Time deltaTime;
	if (goalSet == true)
	{
		moveAI();
	}
}

/// <summary>
/// Resets all paramaters of nodes so they can be used for new path
/// </summary>
void Grid::clearAll()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->getCost() < 999)  // does not reset obstacles
		{
			nodes[i]->setCost(0);
			nodes[i]->setCheck(0);
		}
		nodes[i]->setVector(0, 0);
		nodes[i]->setIntegrationField(0);
	}
}

/// <summary>
/// Set the cost of each obstacle for the flow field pathfinding
/// </summary>
void Grid::setCost()
{
	std::vector<int> que;  // Que of node index to perform cost calculation on.
	que.push_back(goalNode);  // Start with goal.
	nodes[goalNode]->setCost(0);  // Goal cost will always be 0.
	int indexHorizontal = gridY;
	int indexVertical = 1;
	while (que.empty() == false)
	{
		// Calculate what directions are available.
		UpAvailable = true;
		DownAvailable = true;
		LeftAvailable = true;
		RightAvailable = true;

		if (que.front() < gridY)  // Furthest left possible.
		{
			LeftAvailable = false;
		}
		if (que.front() > ((gridX * gridY) - (gridY + 1))) // Greater than max right value (2249).
		{
			RightAvailable = false;
		}
		if (que.front() % gridY == 0)  // Checks if is on top row of nodes.
		{
			UpAvailable = false;
		}
		for (int x = 0; x < gridX; x++)
		{
			if (que.front() == ((gridY - 1) + (gridY * x)))  // Checks if is on bottom row of nodes.
			{
				DownAvailable = false;
			}
		}
		if (UpAvailable == true)
		{
			if (nodes[que.front() - indexVertical]->checkSet() == false)
			{
				nodes[(que.front() - indexVertical)]->setCost(nodes[que.front()]->getCost() + 1);   // Set cost to previous + 1.
				que.push_back(que.front() - indexVertical);  // Push onto que so cost is performed on this node.
			}
		}
		if (DownAvailable == true)
		{
			if (nodes[que.front() + indexVertical]->checkSet() == false)
			{
				nodes[(que.front() + indexVertical)]->setCost(nodes[que.front()]->getCost() + 1);
				que.push_back(que.front() + indexVertical);
			}
		}
		if (LeftAvailable == true)
		{
			if (nodes[que.front() - indexHorizontal]->checkSet() == false)
			{
				nodes[(que.front() - indexHorizontal)]->setCost(nodes[que.front()]->getCost() + 1);
				que.push_back(que.front() - indexHorizontal);
			}
		}
		if (RightAvailable == true)
		{
			if (nodes[que.front() + indexHorizontal]->checkSet() == false)
			{
				nodes[(que.front() + indexHorizontal)]->setCost(nodes[que.front()]->getCost() + 1);
				que.push_back(que.front() + indexHorizontal);
			}
		}
		que.erase(que.begin());  // Get rid of node index just used.
	}
}

/// <summary>
/// set the vector of each node used by ai to move
/// </summary>
void Grid::setVector()
{
	for (int i = 0; i < nodes.size(); i++)
	{

		UpAvailable = true;
		DownAvailable = true;
		LeftAvailable = true;
		RightAvailable = true;
		int indexHorizontal = gridY;
		int indexVertical = 1;
		double leftIntField = 0;
		double rightIntField = 0;
		double upIntField = 0;
		double downIntField = 0;
		double vectorX = 0;
		double vectorY = 0;
		int offset = 19;  // Offset to force ai away from walls.
		if (nodes[i]->getIntegrationField() < 9000)
		{
			// Calculate what directions are available.
			if (i < gridY)
			{
				LeftAvailable = false;
			}
			if (i >((gridX * gridY) - (gridY + 1)))
			{
				RightAvailable = false;
			}
			if (i % gridY == 0)
			{
				UpAvailable = false;
			}
			for (int iter = 0; iter < gridX; iter++)
			{
				if (i == ((gridY - 1) + (gridY * iter)))
				{
					DownAvailable = false;
				}
			}
			// Get the integration field of all available nodes and use to calculate vector
			if (UpAvailable == true)
			{
				if (nodes[i - indexVertical]->getIntegrationField() < 9000)
				{
					upIntField = nodes[i - indexVertical]->getIntegrationField();
				}
				else
				{
					upIntField = nodes[i]->getIntegrationField() + nodes[i]->getIntegrationField() / offset;  // Use own value + offset if node is an obstacle;
				}
			}
			else
			{
				upIntField = nodes[i]->getIntegrationField() + nodes[i]->getIntegrationField() / offset;  // Use own value if node is unavailable;
			}
			if (DownAvailable == true)
			{

				if (nodes[i + indexVertical]->getIntegrationField() < 9000)
				{
					downIntField = nodes[i + indexVertical]->getIntegrationField();
				}
				else
				{
					downIntField = nodes[i]->getIntegrationField() + nodes[i]->getIntegrationField() / offset;
				}
			}
			else
			{
				downIntField = nodes[i]->getIntegrationField() + nodes[i]->getIntegrationField() / offset;
			}
			if (LeftAvailable == true)
			{
				if (nodes[i - indexHorizontal]->getIntegrationField() < 9000)
				{
					leftIntField = nodes[i - indexHorizontal]->getIntegrationField();
				}
				else
				{
					leftIntField = nodes[i]->getIntegrationField() + nodes[i]->getIntegrationField() / offset;
				}
			}
			else
			{
				leftIntField = nodes[i]->getIntegrationField() + nodes[i]->getIntegrationField() / offset;
			}
			if (RightAvailable == true)
			{
				if (nodes[i + indexHorizontal]->getIntegrationField() < 9000)
				{
					rightIntField = nodes[i + indexHorizontal]->getIntegrationField();
				}
				else
				{
					rightIntField = nodes[i]->getIntegrationField() + nodes[i]->getIntegrationField() / offset;
				}
			}
			else
			{
				rightIntField = nodes[i]->getIntegrationField() + nodes[i]->getIntegrationField() / offset;
			}
			// Combine surrounding cost values to create a vector.
			vectorX = leftIntField - rightIntField;
			vectorY = upIntField - downIntField;
			// Turn into a unit vector
			double vectMag = sqrt(((((nodes[i]->getPositionX() + (rectSize / 2)) + vectorX) - (nodes[i]->getPositionX() + (rectSize / 2))) * (((nodes[i]->getPositionX() + (rectSize / 2)) + vectorX) - (nodes[i]->getPositionX() + (rectSize / 2)))) + ((((nodes[i]->getPositionY() + (rectSize / 2)) + vectorY) - (nodes[i]->getPositionY() + (rectSize / 2))) * (((nodes[i]->getPositionY() + (rectSize / 2)) + vectorY) - (nodes[i]->getPositionY() + (rectSize / 2)))));
			vectorX = vectorX / vectMag;
			vectorY = vectorY / vectMag;
			nodes[i]->setVector(vectorX, vectorY);  // Assign the unit vector to the node.
		}


	}
}

/// <summary>
/// Goes through predator container and moves them all with the pathfinding vector.
/// </summary>
void Grid::moveAI()
{
	if (startSet == true && goalSet == true)
	{
		if (ais.size() > 0)
		{
			for (int x = 0; x < ais.size(); x++)
			{
				// Turn position into the grid number.
				int AIgridX = (ais[x]->getPositionX() + 5000) / 200;
				int AIgridY = (ais[x]->getPositionY() + 5000) / 200;
				int AIgrid = AIgridX * 50 + (AIgridY);

				if (AIgrid == goalNode)
				{
					if (ais[x]->surroundNow == true)
					{
						ais[x]->move(nodes[AIgrid]->getVectX(), nodes[AIgrid]->getVectY());
					}
				}
				else
				{
					if (AIgrid <= 2500 && AIgrid >= -2500)
					{
						ais[x]->move(nodes[AIgrid]->getVectX(), nodes[AIgrid]->getVectY());  // Use grid number to apply correct vector to the predator.
					}
				}
				ais[x]->checkWalls(AIgrid, nodes);
			}
		}
	}
}

/// <summary>
/// Updates the ai.
/// Player health is passed so they can decrease it if they hit.
/// Player position is passed to determin the behaviour of ai.
/// </summary>
/// <param name="playerPosition"></param>
/// <param name="health"></param>
void Grid::updateAI(sf::Vector2f playerPosition, int &health)
{
	if (ais.size() > 0)
	{
		for (int x = 0; x < ais.size(); x++)
		{
			if (ais[x]->removeCount == true)
			{
				surroundCount = surroundCount - 1;
				ais[x]->removeCount = false;
			}
			Grid * g = this;
			ais[x]->update(playerPosition, health, *g);
			if (ais[x]->surroundNow == true)  // Within surround distance.
			{
				if (ais[x]->surrounded == false)  // Ensure has not been given a surround spot already.
				{
					surroundCount = surroundCount + 1;  // Increase surround spot amount.
				}
				ais[x]->setSpot(surroundCount, x);  // Calculates the ai spot in circle around player
				ais[x]->surround(playerPosition);  // Ai seeks its spot position
			}
		}
	}

}

/// <summary>
/// Sets the goal node.
/// Calls all functions to set up a path to seek to that node.
/// </summary>
/// <param name="goal"></param>
void Grid::seek(int goal)
{
	int i = goal;

	clearAll();
	goalNode = goal;
	setCost();
	setDistance();
	setVector();
	goalSet = true;  // Is set to true so AI can pathfind
}

/// <summary>
/// Calls the set distance of each node for pathfinding.
/// </summary>
void Grid::setDistance()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i]->setDistance((nodes[goalNode]->getPositionX() + (rectSize / 2)), (nodes[goalNode]->getPositionY() + (rectSize / 2)));
	}
}

/// <summary>
/// Calls the draw of all predators.
/// Grid no longer drawn.
/// </summary>
/// <param name="window"></param>
void Grid::draw(sf::RenderWindow & window)
{


	if (startSet == true)
	{
		if (ais.size() > 0)
		{

			for (int x = 0; x < ais.size(); x++)
			{
				ais[x]->draw(window);
			}
		}

	}
}

/// <summary>
/// Draws dots for predators for radar.
/// </summary>
/// <param name="window"></param>
void Grid::renderDots(sf::RenderWindow & window)
{
	if (startSet == true)
	{
		if (ais.size() > 0)
		{

			for (int x = 0; x < ais.size(); x++)
			{
				ais[x]->renderDot(window);
			}
		}

	}
}