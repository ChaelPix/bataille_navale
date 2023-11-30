#pragma once
#include <SFML/Graphics.hpp>

class Grid
{
private:
	sf::RectangleShape hline;
	sf::RectangleShape vline;

	std::vector<sf::RectangleShape> grid;
	sf::Vector2f startGridPos;

	int nbPixels, pixelSize, gridSize;

	void SetupGrid();

public:
	Grid(int nbPixels, int gridSize, sf::Vector2f startPos, sf::Color lineColor);

	void DrawGrid(sf::RenderWindow& window);
};

