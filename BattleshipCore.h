#pragma once

#include <iostream>

class BattleshipCore
{
private:
	enum class CellType { empty, boat, hit, water, error = 99 };
	enum class boatTypes { PorteAvion = 5, Croiseur = 4, ContreTorpilleur = 3, Torpilleur = 2 };

	static const int nbLig = 10;
	static const int nbCol = 10;

	CellType playerGrid[nbLig][nbCol];
	CellType targetGrid[nbLig][nbCol];

public:
	BattleshipCore();
	bool isAdjacentCellFree(int row, int column, CellType(*targetGrid)[nbCol]);
	bool canPlaceBoat(int row, int column, int boatSize, bool isRotated);
	bool modifyBoat(int row, int column, int boatSize, bool isRotated, bool isPlacing);

	std::string serialisationJoueur() const;
};

