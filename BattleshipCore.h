#pragma once

#include <iostream>
#include <sstream>

class BattleshipCore
{
public:
	struct BoatInfo
	{
		int row;
		int column;
		bool isRotated;
	};

	enum class CellType { empty, boat, hit, water, error = 99 };
private:
	enum class boatTypes { PorteAvion = 5, Croiseur = 4, ContreTorpilleur = 3, Torpilleur = 2 };

	static const int nbLig = 10;
	static const int nbCol = 10;

	CellType playerGrid[nbLig][nbCol];
	CellType targetGrid[nbLig][nbCol];

	bool hasReceivedOpponentGrid;
	int playerBoatsDown = 0;
	int enemyBoatDown = 0;

	

public:
	BattleshipCore();
	void NewGrid();
	bool isAdjacentCellFree(int row, int column, CellType(*targetGrid)[nbCol]);
	bool canPlaceBoat(int row, int column, int boatSize, bool isRotated);
	bool modifyBoat(int row, int column, int boatSize, bool isRotated, bool isPlacing);

	BoatInfo randomPlacing(int boatSize);

	std::string serializePlayerGrid() const;

	bool getHasReceivedOpponentGrid() const;
	bool isTargetCellEmpty(int x, int y);
	CellType getTargetCellType(int x, int y);

	void setTargetGrid(std::string grid);
	std::string serializeAttack(float x, float y);
	BattleshipCore::CellType deserializeAttack(std::string msg);
	bool CheckIfBoatDown(int x, int y, bool isOnOpponent);
	BattleshipCore::CellType Attack(int x, int y, bool isOnOpponent);

	bool areAllEnnemyBoatsDown();
	bool areAllPlayerBoatsDown();
};

