#include "CoreGame.h"
#include <iostream>

// Vous n'avez pas besoin de d\202clarer nbLig et nbCol dans le .cpp car ils sont d\202j� d\202clar\202s comme 'static const' dans le .h

CoreGame::CoreGame() : nombreTotalBateaux(0), bateauxCoul�s(0) {
    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            grille[i][j] = typeCase::vide;
            grilleAdversaire[i][j] = typeCase::vide; // Initialisation de la grille de l'adversaire
        }
    }
}


CoreGame::typeCase CoreGame::getCase(int ligne, int colonne) const {
    return grille[ligne][colonne];
}

void CoreGame::setCase(int ligne, int colonne, CoreGame::typeCase type) {
    grille[ligne][colonne] = type;
}

// Fonction pour changer la couleur du texte en rouge
void setRedText() {
    std::cout << "\033[33m"; // Code ANSI pour le texte en rouge
}

// Fonction pour r�initialiser la couleur du texte � sa valeur par d�faut
void resetTextColor() {
    std::cout << "\033[0m"; // Code ANSI pour r�initialiser la couleur
}

// Fonction pour changer la couleur du texte en rouge
void setGreenText() {
    std::cout << "\033[32m"; // Code ANSI pour le texte en rouge
}

void CoreGame::afficheGrille() const {
    std::cout << espace << "Votre Grille:" << "           Grille Adversaire:\n";
    for (int i = 0; i < nbLig; ++i) {
        // Afficher l'espace de centrage avant la grille du joueur
        std::cout << espace;

        // Afficher la ligne de la grille du joueur
        for (int j = 0; j < nbCol; ++j) {
            setGreenText(); // Changer la couleur du texte en rouge
            std::cout << getRepresentationCaractere(grille[i][j]) << " ";
            resetTextColor(); // R�initialiser la couleur du texte
        }

        std::cout << "\t";

        // Afficher la ligne de la grille de l'adversaire
        for (int j = 0; j < nbCol; ++j) {
            // Ne pas montrer les bateaux adverses, seulement les tirs effectu�s
            if (grilleAdversaire[i][j] == typeCase::bateau) {
                setRedText(); // Changer la couleur du texte en rouge
                std::cout << getRepresentationCaractere(typeCase::vide) << " ";
                resetTextColor(); // R�initialiser la couleur du texte
            }
            else {
                setRedText(); // Changer la couleur du texte en rouge
                std::cout << getRepresentationCaractere(grilleAdversaire[i][j]) << " ";
                resetTextColor(); // R�initialiser la couleur du texte
            }
        }

        std::cout << std::endl;
    }
}


char CoreGame::getRepresentationCaractere(typeCase caseType) const {
    switch (caseType) {
    case typeCase::vide: return 'O';
    case typeCase::bateau: return 'B';
    case typeCase::touche: return 'X';
    case typeCase::eau: return '~';
    default: return '?';
    }
}

std::pair<int, int> CoreGame::saisieJoueur() {
    // lire les entr\202es du joueur.
    int ligne, colonne;
    std::cout << std::endl << espace << "            Entrez la ligne: ";
    std::cin >> ligne; std::cout << std::endl;
    std::cout << espace << "            Entrez la colonne: ";
    std::cin >> colonne; std::cout << std::endl;
    return { ligne, colonne };
   
}

bool CoreGame::partiePerdu() const {
    // Impl\202mentation de la v\202rification pour voir si la partie est perdue.
    // Par exemple, v\202rifier s'il reste des cases 'bateau'.
    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            if (grille[i][j] == typeCase::bateau) {
                return false; // Il reste encore des bateaux.
            }
        }
    }
    return true; // Plus de bateaux, la partie est perdue.
}

std::string CoreGame::serialisation() const {
    // Convertit l'\202tat actuel de la grille en une cha�ne de caract�res.
    std::string result;
    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            result += std::to_string(static_cast<int>(grille[i][j])) + " ";
        }
        result += "\n";
    }
    return result;
}

bool CoreGame::deserialisation(std::string trame) {
    // Construit l'\202tat de la grille � partir d'une cha�ne de caract�res.
    // � compl\202ter selon le format de la trame.
    return true;
}

void CoreGame::placerBateaux() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed pour la g\202n\202ration de nombres al\202atoires
    // Supposons que nous pla�ons un seul bateau de taille 3 pour l'exemple
    int direction = std::rand() % 2; // 0 pour horizontal, 1 pour vertical
    int tailleBateau = 3;

    int ligne = std::rand() % nbLig;
    int colonne = std::rand() % nbCol;

    // V\202rifier si le placement est possible et placer le bateau
    // Ce code ne g�re pas les collisions de bateaux ou les bateaux sortant de la grille.
    for (int i = 0; i < tailleBateau; ++i) {
        if (direction == 0) {
            grille[ligne][(colonne + i) % nbCol] = typeCase::bateau; // Wrap-around pour simplifier
        }
        else {
            grille[(ligne + i) % nbLig][colonne] = typeCase::bateau; // Wrap-around pour simplifier
        }
    }
}

bool CoreGame::attaqueJoueur(int ligne, int colonne) {
    // V�rification simple de la case attaqu�e
    if (grille[ligne][colonne] == typeCase::bateau) {
        grille[ligne][colonne] = typeCase::touche; // Marquer la case comme touch�e sur votre grille
        grilleAdversaire[ligne][colonne] = typeCase::touche; // Marquer la case comme touch�e sur la grille de l'adversaire
        verifierBateauCoule(ligne, colonne); // V�rifier si un bateau a �t� coul�
        return true;
    }
    else {
        grilleAdversaire[ligne][colonne] = typeCase::eau; // Marquer la case comme eau (manqu�) sur la grille de l'adversaire
        return false;
    }
}


void CoreGame::attaqueIA() {
    int ligne, colonne;
    do {
        ligne = std::rand() % nbLig;
        colonne = std::rand() % nbCol;
    } while (grille[ligne][colonne] == typeCase::touche || grille[ligne][colonne] == typeCase::eau); // \202viter les cases d\202j� attaqu\202es
    // L'IA attaque une case
    if (grille[ligne][colonne] == typeCase::bateau) {
        std::cout << espace3 << "\033[31mL'IA a touch\202 un bateau !\033[0m" << std::endl << std::endl;
        grille[ligne][colonne] = typeCase::touche;
    }
    else {
        std::cout << espace2 << "\033[34mL'IA a manqu\202.\033[0m" << std::endl << std::endl;
        grille[ligne][colonne] = typeCase::eau;
    }
}

void CoreGame::jouer() {
    // Boucle principale du jeu, alternant entre le joueur et l'IA
    while (!estFinDuJeu()) {
        
        afficherBateauxCoules();
        afficheGrille();
        std::pair<int, int> saisie = saisieJoueur(); // Utilisez le type explicite au lieu de 'auto'
        int ligne = saisie.first;
        int colonne = saisie.second;
        std::cout << espace3 << "L'adversaire joue...";
        Sleep(1000);
        system("cls");
        std::cout << std::endl;
        if (attaqueJoueur(ligne, colonne)) {
            std::cout << std::endl << std::endl << std::endl << std::endl;
            std::cout << espace4 << "\033[34mTouch\202!\033[0m" << std::endl << std::endl;
        }
        else {
            std::cout << std::endl << std::endl << std::endl << std::endl;
            std::cout << espace4 << "\033[31mManqu\202!\033[0m" << std::endl << std::endl;
        }
        attaqueIA();
    }
}


bool CoreGame::estFinDuJeu() const {
    // V\202rifier si tous les bateaux ont \202t\202 coul\202s
    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            if (grille[i][j] == typeCase::bateau) {
                return false; // Il reste encore des bateaux non coul\202s
            }
        }
    }
    return true; // Tous les bateaux ont \202t\202 coul\202s
}

void CoreGame::verifierBateauCoule(int ligne, int colonne) {
    // V�rifier d'abord si la case contient un bateau touch�
    if (grille[ligne][colonne] != typeCase::touche) {
        return; // Si la case n'est pas un bateau touch�, aucune v�rification suppl�mentaire n'est n�cessaire
    }

    // V�rifiez s'il reste des parties de bateau non touch�es autour de cette case
    bool bateauCoul� = true;

    // V�rifier les cases adjacentes
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int voisinLigne = ligne + i;
            int voisinColonne = colonne + j;

            // V�rifier les limites de la grille
            if (voisinLigne >= 0 && voisinLigne < nbLig && voisinColonne >= 0 && voisinColonne < nbCol) {
                if (grille[voisinLigne][voisinColonne] == typeCase::bateau) {
                    bateauCoul� = false; // Il reste des parties non touch�es du bateau
                    break;
                }
            }
        }
        if (!bateauCoul�) break;
    }

    // Mettre � jour le compteur si un bateau a �t� coul�
    if (bateauCoul�) {
        ++bateauxCoul�s;
    }
}


void CoreGame::afficherBateauxCoules() const {
   /* std::cout << espace << "Bateaux coul\202s: " << bateauxCoul�s << " sur " << nombreTotalBateaux << std::endl;*/
}
