#include "Grid.h"

Grid::Grid(int nbPixels, int gridSize, sf::Vector2f startGridPos, sf::Color lineColor)
{
	hline.setSize(sf::Vector2f(gridSize, 1));
	vline.setSize(sf::Vector2f(1, gridSize));

	hline.setFillColor(lineColor);
	vline.setFillColor(lineColor);
 
	this->nbPixels = nbPixels;
	this->pixelSize = gridSize / nbPixels;
	this->gridSize = gridSize;
	this->startGridPos = startGridPos;

	SetupGrid();
}

void Grid::SetupGrid()
{
	for (int i = 1; i < nbPixels; i++)
	{
		sf::RectangleShape line = hline;
		line.setPosition(sf::Vector2f(0 + startGridPos.x, i * pixelSize + startGridPos.y));
		grid.push_back(line);

		line = vline;
		line.setPosition(sf::Vector2f(i * pixelSize + startGridPos.x, 0 + startGridPos.y));
		grid.push_back(line);
	}
}

void Grid::DrawGrid(sf::RenderWindow& window)
{
	for (const auto& line : grid)
		window.draw(line);
}