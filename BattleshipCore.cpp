#include "BattleshipCore.h"
#include<iostream>

BattleshipCore::BattleshipCore()
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

        std::cout << "r : " << r << " c : " << c << std::endl;
        if (r >= nbLig || c >= nbCol || playerGrid[r][c] != CellType::empty) {
            isPlacementValid = false;
            break;
        }
    }
    return isPlacementValid;
}

bool BattleshipCore::placeBoat(int row, int column, int boatSize, bool isRotated)
{
    for (int i = 0; i < boatSize; ++i) {
        int l = row - 4 + (isRotated == 0 ? 0 : i);
        int c = column - 2 + (isRotated == 1 ? 0-1 : i);
        playerGrid[l][c] = CellType::boat;
       
    }
    std::cout << serialisationJoueur();

    return true;
}

bool BattleshipCore::removeBoat(int row, int column, int boatSize, bool isRotated)
{
    for (int i = 0; i < boatSize; ++i) {
        int l = row - 4 + (isRotated == 0 ? 0 : i);
        int c = column - 2 + (isRotated == 1 ? 0-1 : i);
        playerGrid[l][c] = CellType::empty;
    }
    std::cout << serialisationJoueur();

    return true;
}

std::string BattleshipCore::serialisationJoueur() const {
    std::string result;
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