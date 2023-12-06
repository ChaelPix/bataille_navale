#include "BattleshipCore.h"
#include<iostream>

BattleshipCore::BattleshipCore()
{
    NewGrid();
}

void BattleshipCore::NewGrid()
{
    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            playerGrid[i][j] = CellType::empty;
            targetGrid[i][j] = CellType::empty;
        }
    }
}

bool BattleshipCore::isAdjacentCellFree(int row, int column, CellType(*targetGrid)[nbCol])
{
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int r = row + i;
            int c = column + j;
            if (r >= 0 && r < nbLig && c >= 0 && c < nbCol) {
                if (targetGrid[r][c] != CellType::empty) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool BattleshipCore::canPlaceBoat(int row, int column, int boatSize, bool isRotated)
{
    bool isPlacementValid = true;
    for (int i = 0; i < boatSize; ++i) 
    {
        int r = row - 4 + (isRotated == 0 ? 0 : i);
        int c = column - 2 + (isRotated == 1 ? 0-1 : i);

      
        if (r >= nbLig || c >= nbCol || playerGrid[r][c] != CellType::empty) {
            std::cout << "r : " << r << " c : " << c << std::endl;
            isPlacementValid = false;
            break;
        }
    }
    return isPlacementValid;
}


bool BattleshipCore::modifyBoat(int row, int column, int boatSize, bool isRotated, bool isPlacing)
{
    CellType newCellType = isPlacing ? CellType::boat : CellType::empty;

    for (int i = 0; i < boatSize; ++i) {
        int l = row - 4 + (isRotated == 0 ? 0 : i);
        int c = column - 2 + (isRotated == 1 ? 0 - 1 : i);
        playerGrid[l][c] = newCellType;
    }

    std::cout << serializePlayerGrid();
    return true;
}

BattleshipCore::BoatInfo BattleshipCore::randomPlacing(int boatSize)
{
    bool isOk = false;

    while (!isOk)
    {
        int dir = std::rand() % 2; // 0 pour horizontal, 1 pour vertical
        int row = (std::rand() % nbLig);
        int column = (std::rand() % nbCol);

        if (canPlaceBoat(row + 4, column + 2, boatSize, dir == 1))
        {
            isOk = true;
            modifyBoat(row + 4, column + 2, boatSize, dir == 1, true);

            BoatInfo boatInfo;
            boatInfo.row = row ;
            boatInfo.column = column;
            boatInfo.isRotated = dir == 1;

            return boatInfo;
        }
    }
}


std::string BattleshipCore::serializePlayerGrid() const {
    std::string result = "G";
    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            switch (playerGrid[i][j]) {
            case CellType::empty: result += 'V'; break;
            case CellType::boat: result += 'B'; break;
            case CellType::hit: result += 'T'; break;
            case CellType::water: result += 'E'; break;
            default: result += '?'; break;
            }
        }
        result += "\n";
    }
    return result;
}