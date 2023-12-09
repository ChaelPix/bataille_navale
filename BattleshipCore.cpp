#include "BattleshipCore.h"
#include<iostream>

bool BattleshipCore::areAllEnnemyBoatsDown()
{
    std::cout << "Ennemy boat : " << enemyBoatDown << std::endl;
    return enemyBoatDown >= 5;
}

bool BattleshipCore::areAllPlayerBoatsDown()
{
    std::cout << "Player boat : " << enemyBoatDown << std::endl;
    return playerBoatsDown >= 5;
}

BattleshipCore::BattleshipCore()
{
    hasReceivedOpponentGrid = false;
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
      
        if (r >= nbLig || c >= nbCol || c < 0 || r < 0 || playerGrid[r][c] != CellType::empty || !isAdjacentCellFree(r, c, playerGrid)) {         
            isPlacementValid = false;
            break;
        }

        std::cout << "r : " << r << " c : " << c << std::endl;
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

        if (row < 0) row = 0;
        if (column < 0) column = 0;

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


std::string BattleshipCore::serializePlayerGrid(bool isPlayer) {
    CellType(*grilleCible)[nbCol] = isPlayer ? playerGrid : targetGrid;

    std::string result = "B";

    for (int i = 0; i < nbLig; i++) {
        for (int j = 0; j < nbCol; j++) {  
            switch (grilleCible[i][j]) {
            case CellType::empty: result += 'V'; break;
            case CellType::boat: result += 'B'; break;
            case CellType::hit: result += 'T'; break;
            case CellType::water: result += 'E'; break;
            }
        }
        result += '\n';
    }
    return result;
}


bool BattleshipCore::getHasReceivedOpponentGrid() const
{
    return hasReceivedOpponentGrid;
}

bool BattleshipCore::isTargetCellEmpty(int x, int y)
{
    return targetGrid[x][y] != CellType::hit;

}

BattleshipCore::CellType BattleshipCore::getTargetCellType(int x, int y)
{
    return targetGrid[x][y];
}

void BattleshipCore::setTargetGrid(std::string grid)
{
    grid.erase(0, 1); //remove msg identification ('B')

    int l = 0, c = 0; 

    for (char caractere : grid) {
        if (caractere == '\n') {
            l++;
            c = 0;
            continue;
        }

        CellType caseType;
        switch (caractere) {
        case 'B': caseType = CellType::boat; break;
        case 'T': caseType = CellType::hit; break;
        case 'E': caseType = CellType::water; break;
        case 'V':
        default:
            caseType = CellType::empty; break;
        }

        targetGrid[l][c] = caseType;
        c++;
    }

    hasReceivedOpponentGrid = true;
}

std::string BattleshipCore::serializeAttack(float x, float y)
{
    return "Gx:" + std::to_string(x) + "y:" + std::to_string(y);
}

BattleshipCore::CellType BattleshipCore::deserializeAttack(std::string msg)
{
    int xPos = msg.find("x:");
    int yPos = msg.find("y:");
    std::string xStr = msg.substr(xPos + 2, yPos - (xPos + 2));
    std::string yStr = msg.substr(yPos + 2);
    int x = std::stoi(xStr);
    int y = std::stoi(yStr);

    return Attack(y, x, false);
}

BattleshipCore::CellType BattleshipCore::Attack(int x, int y, bool isOnOpponent) {

    CellType(*grilleCible)[nbCol] = isOnOpponent ? targetGrid : playerGrid;

    if (grilleCible[x][y] == CellType::boat)
        grilleCible[x][y] = CellType::hit;
    else 
        grilleCible[x][y] = CellType::water;

    return grilleCible[x][y];
}

bool BattleshipCore::CheckIfBoatDown(int x, int y, bool isOnOpponent, bool doCountAttack, int origX, int origY) {
    CellType(*grilleCible)[nbCol] = isOnOpponent ? targetGrid : playerGrid;

    //Check if there is a boat cell, or a hit cell which is not the cell that calls the recursive method
    // top
    if (x > 0 && ((grilleCible[x - 1][y] == CellType::boat) 
        || (grilleCible[x - 1][y] == CellType::hit 
            && !(x - 1 == origX && y == origY) 
            && !CheckIfBoatDown(x - 1, y, isOnOpponent, false, x, y)))) {
        return false;
    }

    // down
    if (x < nbLig - 1 && ((grilleCible[x + 1][y] == CellType::boat) 
        || (grilleCible[x + 1][y] == CellType::hit 
            && !(x + 1 == origX && y == origY) 
            && !CheckIfBoatDown(x + 1, y, isOnOpponent, false, x, y)))) {
        return false;
    }

    // left
    if (y > 0 && ((grilleCible[x][y - 1] == CellType::boat) 
        || (grilleCible[x][y - 1] == CellType::hit 
            && !(x == origX && y - 1 == origY) 
            && !CheckIfBoatDown(x, y - 1, isOnOpponent, false, x, y)))) {
        return false;
    }

    // right
    if (y < nbCol - 1 && ((grilleCible[x][y + 1] == CellType::boat) 
        || (grilleCible[x][y + 1] == CellType::hit 
            && !(x == origX && y + 1 == origY) 
            && !CheckIfBoatDown(x, y + 1, isOnOpponent, false, x, y)))) {
        return false;
    }

    if (doCountAttack)
        isOnOpponent ? enemyBoatDown++ : playerBoatsDown++;

    return true;
}


