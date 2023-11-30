#include "PlayerBoatsManager.h"



PlayerBoatsManager::PlayerBoatsManager(int bottomGridOffset)
{
	boatsType.push_back(CoreGame::boatTypes::ContreTorpilleur);
	boatsType.push_back(CoreGame::boatTypes::ContreTorpilleur);
	boatsType.push_back(CoreGame::boatTypes::Croiseur);
	boatsType.push_back(CoreGame::boatTypes::PorteAvion);
	boatsType.push_back(CoreGame::boatTypes::Torpilleur);

	InstiantiateBoats(bottomGridOffset);
}

void PlayerBoatsManager::InstiantiateBoats(int bottomGridOffset)
{
	GridSettings gridSettings;
	int gridCellSize = gridSettings.squareSize / gridSettings.nbPixels;
	int totalSize = 0;

	for (int i = 0; i < boatsType.size(); i++)
	{
		int boatTypeInt = static_cast<int>(boatsType.at(i));
		Boat boat(i, boatsType.at(i), sf::Vector2f(gridCellSize * boatTypeInt, gridCellSize));

		boat.setPosition(gridSettings.playerGridPosition.x + totalSize * gridCellSize, gridSettings.playerGridPosition.y + bottomGridOffset * (gridSettings.nbPixels + 1));

		totalSize += boatTypeInt + 1;
		boatsList.push_back(boat);
	}
}


void PlayerBoatsManager::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < boatsList.size(); i++)
	{
		boatsList.at(i).draw(window);
	}
}
