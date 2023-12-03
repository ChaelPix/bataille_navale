#pragma once
class BattleshipCore
{
private:
	enum class typeCase { vide, bateau, touche, eau, erreur = 99 };
	enum class boatTypes { PorteAvion = 5, Croiseur = 4, ContreTorpilleur = 3, Torpilleur = 2 };

	static const int nbLig = 10;
	static const int nbCol = 10;
	typeCase grille[nbLig][nbCol];


public:
	bool caseAdjacenteLibre(int ligne, int colonne, typeCase(*grilleCible)[nbCol]);
};

