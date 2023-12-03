#include "BattleshipCore.h"

bool BattleshipCore::caseAdjacenteLibre(int ligne, int colonne, typeCase(*grilleCible)[nbCol])
{
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int l = ligne + i;
            int c = colonne + j;
            if (l >= 0 && l < nbLig && c >= 0 && c < nbCol) {
                if (grilleCible[l][c] != typeCase::vide) {
                    return false; // Une case adjacente n'est pas vide
                }
            }
        }
    }
    return true; // Toutes les cases adjacentes sont libres
}
