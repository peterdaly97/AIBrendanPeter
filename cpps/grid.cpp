#include "../Classes/grid.h"
#include <iostream>
#include <fstream>
#include <math.h>

Grid::Grid()
{

	if (!costFont.loadFromFile("font.ttf"))
	{
	}
	if (!m_groundTexture.loadFromFile("assets/ground.jpg"))
	{

	}
	if (!m_obstacleTexture.loadFromFile("assets/obstacle.jpg"))
	{

	}
	createGrid(randomSize);

	//m_player = new Player();
}
void Grid::createGrid(int random)
{
	srand(time(NULL));

	int map[50][50] =
	{{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
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
	{ 0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,0,0,0,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0 },
	{ 0,0,0,1,1,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0 },
	{ 0,0,1,1,0,0,0,1,1,0,0,0,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,1,0,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0 },
	{ 1,1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,0 },
	{ 1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 },
	{ 1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0 },
	{ 1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 1,1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,1,0,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,0,1,1,0,0,0,1,1,0,0,0,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0 },
	{ 0,0,0,1,1,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,1,1,0,0,0,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
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
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }};

	for (int x = 1; x <= gridX; x++)
	{
		for (int y = 1; y <= gridY; y++)
		{

			node = new Node(-5200 + x * (rectSize),-5200 + y * (rectSize), rectSize, costFont, map[x - 1][y - 1]);
			nodes.push_back(node);
		}
	}
}
void Grid::makeMap()
{
	if (mapMade == false)
	{
		using namespace std;

		ofstream myfile("map.txt");
		if (myfile.is_open())
		{
			myfile << "{{";
			for (int i = 0; i < nodes.size(); i++)
			{

				if (mapCount == 50)
				{
					myfile << "},\n";
					myfile << "{";
					mapCount = 0;
				}
				if (nodes[i]->getCost() > 9999)
				{
					if (mapCount != 49)
					{
						myfile << "1,";
					}
					else
					{
						myfile << "1";
					}
				}
				else
				{
					if (mapCount != 49)
					{
						myfile << "0,";
					}
					else
					{
						myfile << "0";
					}
				}
				mapCount++;

			}
			myfile << "}};";
			myfile.close();
			mapMade = true;
		}

		else cout << "Unable to open file";
	}
}

Grid::~Grid()
{
}



void Grid::update(sf::RenderWindow & window)
{
	sf::Time deltaTime;
	//m_player->update(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
	{
		sf::Vector2i position = sf::Mouse::getPosition(window);

		for (int i = 0; i < nodes.size(); i++)
		{
			if (position.x > nodes[i]->getPositionX() && position.x < nodes[i]->getPositionX() + rectSize && position.y > nodes[i]->getPositionY() && position.y < nodes[i]->getPositionY() + rectSize)
			{
				nodes[i]->setCost(999999);
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
	{
		sf::Vector2i position = sf::Mouse::getPosition(window);

		for (int i = 0; i < nodes.size(); i++)
		{
			if (position.x > nodes[i]->getPositionX() && position.x < nodes[i]->getPositionX() + rectSize && position.y > nodes[i]->getPositionY() && position.y < nodes[i]->getPositionY() + rectSize)
			{
				nodes[i]->setCost(0);
				nodes[i]->setCheck(0);
				nodes[i]->setVector(0, 0);
				nodes[i]->setIntegrationField(0);
				nodes[i]->setColor(sf::Color::White);
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
	{
		if (zPressed == false)
		{
			zPressed = true;
			for (int i = 0; i < nodes.size(); i++)
			{
				nodes[i]->swapIntegrationCalc();
			}
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
	{
		zPressed = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		//sf::Vector2i position = sf::Mouse::getPosition(window);

		//for (int i = 0; i < nodes.size(); i++)
		//{
		//if (position.x > nodes[i]->getPositionX() && position.x < nodes[i]->getPositionX() + rectSize && position.y > nodes[i]->getPositionY() && position.y < nodes[i]->getPositionY() + rectSize)
		//{
		int i = 550;
		if (goalSet == true)
		{
			clearAll();
			goalNode = 2030;
			setCost();
			setDistance();
			setVector();
			nodes[i]->setColor(sf::Color::Red);
		}
		else
		{
			goalNode = 2030;
			setCost();
			setDistance();
			setVector();
			nodes[i]->setColor(sf::Color::Red);
			goalSet = true;
		}

		//}
		//}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
	{
		goalSet = false;
		startSet = false;
		ais.clear();
		nodes.clear();
		createGrid(randomSize);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
	{
		makeMap();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
	{
		mapMade = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		UpPressed = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		DownPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		if (UpPressed == false)
		{
			UpPressed = true;
			if (randomSize < 99)
			{
				randomSize = randomSize + 1;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (DownPressed == false)
		{
			DownPressed = true;
			if (randomSize > 1)
			{
				randomSize = randomSize - 1;
			}
		}
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		leftPressed = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (leftPressed == false)
		{
			//sf::Vector2i position = sf::Mouse::getPosition(window);

			ai = new AI(0 + (rectSize / 2), 0 + (rectSize / 2));
			ais.push_back(ai);
			startSet = true;
			leftPressed = true;

			/*for (int i = 0; i < nodes.size(); i++)
			{
			if (position.x > nodes[i]->getPositionX() && position.x < nodes[i]->getPositionX() + rectSize && position.y > nodes[i]->getPositionY() && position.y < nodes[i]->getPositionY() + rectSize)
			{
			ai = new AI(nodes[i]->getPositionX() + (rectSize / 2), nodes[i]->getPositionY() + (rectSize / 2));
			ais.push_back(ai);
			startSet = true;
			leftPressed = true;
			}

			}*/

		}
	}
	if (startSet == true && goalSet == true)
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			for (int x = 0; x < ais.size(); x++)
			{
				if (ais[x]->getPositionX() >= nodes[i]->getPositionX() && ais[x]->getPositionX() <= nodes[i]->getPositionX() + rectSize && ais[x]->getPositionY() >= nodes[i]->getPositionY() && ais[x]->getPositionY() <= nodes[i]->getPositionY() + rectSize)
				{
					if (i == goalNode)
					{
						ais.erase(ais.begin() + x);
					}
					else
					{
						if (nodes[i]->getVectX() != 0)
						{
							tempX = nodes[i]->getVectX();
						}
						if (nodes[i]->getVectX() != 0)
						{
							tempY = nodes[i]->getVectY();
						}
						if (nodes[i]->getVectX() == 0 && nodes[i]->getVectY() == 0)
						{
							if (tempX > tempY)
							{
								if (tempX <= 0)
								{
									ais[x]->move(-tempX, tempY);
								}
								if (tempX > 0)
								{

									ais[x]->move(tempX, -tempY);

								}
							}
							else if (tempY > tempX)
							{
								if (tempY <= 0)
								{
									ais[x]->move(tempX, -tempY);
								}
								if (tempY > 0)
								{
									ais[x]->move(-tempX, tempY);
								}
							}
						}
						else
						{
							ais[x]->move(nodes[i]->getVectX(), nodes[i]->getVectY());
						}
					}
				}
			}
		}
	}
}
void Grid::clearAll()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->getCost() < 999)
		{
			nodes[i]->setCost(0);
			nodes[i]->setCheck(0);
			nodes[i]->setColor(sf::Color::White);
		}
		nodes[i]->setVector(0, 0);
		nodes[i]->setIntegrationField(0);
	}
}
void Grid::setCost()
{
	std::vector<int> que;
	que.push_back(goalNode);
	nodes[goalNode]->setCost(0);
	int indexHorizontal = gridY;
	int indexVertical = 1;
	while (que.empty() == false)
	{
		UpAvailable = true;
		DownAvailable = true;
		LeftAvailable = true;
		RightAvailable = true;

		if (que.front() < gridY)
		{
			LeftAvailable = false;
		}
		if (que.front() > ((gridX * gridY) - (gridY + 1))) //2249
		{
			RightAvailable = false;
		}
		if (que.front() % gridY == 0)
		{
			UpAvailable = false;
		}
		for (int x = 0; x < gridX; x++)
		{
			if (que.front() == ((gridY - 1) + (gridY * x)))
			{
				DownAvailable = false;
			}
		}
		if (UpAvailable == true)
		{
			if (nodes[que.front() - indexVertical]->checkSet() == false)
			{
				nodes[(que.front() - indexVertical)]->setCost(nodes[que.front()]->getCost() + 1);
				que.push_back(que.front() - indexVertical);
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
		que.erase(que.begin());
	}
}
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
		int offset = 19;
		if (nodes[i]->getIntegrationField() < 9000)
		{
			if (i < gridY)
			{
				LeftAvailable = false;
			}
			if (i >((gridX * gridY) - (gridY + 1))) //2249
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
			if (UpAvailable == true)
			{
				if (nodes[i - indexVertical]->getIntegrationField() < 9000)
				{
					upIntField = nodes[i - indexVertical]->getIntegrationField();
				}
				else
				{
					upIntField = nodes[i]->getIntegrationField() + nodes[i]->getIntegrationField() / offset;
				}
			}
			else
			{
				upIntField = nodes[i]->getIntegrationField() + nodes[i]->getIntegrationField() / offset;
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
			vectorX = leftIntField - rightIntField;
			vectorY = upIntField - downIntField;
			double vectMag = sqrt(((((nodes[i]->getPositionX() + (rectSize / 2)) + vectorX) - (nodes[i]->getPositionX() + (rectSize / 2))) * (((nodes[i]->getPositionX() + (rectSize / 2)) + vectorX) - (nodes[i]->getPositionX() + (rectSize / 2)))) + ((((nodes[i]->getPositionY() + (rectSize / 2)) + vectorY) - (nodes[i]->getPositionY() + (rectSize / 2))) * (((nodes[i]->getPositionY() + (rectSize / 2)) + vectorY) - (nodes[i]->getPositionY() + (rectSize / 2)))));
			vectorX = vectorX / vectMag;
			vectorY = vectorY / vectMag;
			nodes[i]->setVector(vectorX, vectorY);
		}


	}
}
void Grid::setDistance()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i]->setDistance((nodes[goalNode]->getPositionX() + (rectSize / 2)), (nodes[goalNode]->getPositionY() + (rectSize / 2)));
	}
}

void Grid::draw(sf::RenderWindow & window)
{
	//m_player->draw(m_window);
	//for (int i = 0; i < nodes.size(); i++)
	//{
	//	nodes[i]->draw(window);
	//}

	if (startSet == true)
	{
		for (int x = 0; x < ais.size(); x++)
		{
			ais[x]->draw(window);
		}
	}
}