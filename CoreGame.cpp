//Fichier de définition de ma classe CoreGame, (CoreGame.cpp)

#include "CoreGame.h"
#include <iostream>

CoreGame::CoreGame() : nombreTotalBateaux(4), bateauxCoulés(0) {
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

// Fonction pour réinitialiser la couleur du texte à sa valeur par défaut
void resetTextColor() {
    std::cout << "\033[0m"; // Code ANSI pour réinitialiser la couleur
}

// Fonction pour changer la couleur du texte en rouge
void setGreenText() {
    std::cout << "\033[32m"; // Code ANSI pour le texte en rouge
}

void CoreGame::afficheGrille() const {
    std::cout << espace << "Votre Grille:" << "           Grille Adversaire:\n";

    // Afficher les repères de colonne
    std::cout << espace << "  ";
    for (int i = 0; i < nbCol; ++i) {
        std::cout << "\033[90m" << i << "\033[0m" << " ";
    }
    std::cout << "    ";
    for (int i = 0; i < nbCol; ++i) {
        std::cout << "\033[90m" << i << "\033[0m" << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < nbLig; ++i) {
        // Afficher le repère de ligne
        std::cout << espace << "\033[90m" << i << "\033[0m" << " ";

        // Afficher la grille du joueur
        for (int j = 0; j < nbCol; ++j) {
            afficherCaractereAvecCouleur(grille[i][j], false);
            std::cout << " ";
        }

        std::cout << "\t" << "\033[90m" << i << "\033[0m" << " "; // Repère de ligne pour la grille de l'adversaire

        // Afficher la grille de l'adversaire
        for (int j = 0; j < nbCol; ++j) {
            // Afficher seulement les tirs effectués sur la grille de l'adversaire
            if (grilleAdversaire[i][j] == typeCase::touche || grilleAdversaire[i][j] == typeCase::eau) {
                afficherCaractereAvecCouleur(grilleAdversaire[i][j], true);
            }
            else {
                // Afficher 'O' pour les cases vides et celles contenant des bateaux non découverts
                afficherCaractereAvecCouleur(typeCase::vide, true);
            }
            std::cout << " ";
        }

        std::cout << std::endl;
    }
}



void CoreGame::afficherCaractereAvecCouleur(typeCase caseType, bool estGrilleAdversaire) const {

    // Codes de couleur ANSI
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";     // Pour "touche"
    const std::string BLUE = "\033[34m";    // Pour "bateau"
    const std::string CYAN = "\033[36m";    // Pour "eau"
    const std::string VERT = "\033[32m";  // Pour "vide"
    const std::string GREY = "\033[90m";    // Pour un caractère inconnu
    const std::string YELLOW = "\033[33m";    // Pour un caractère inconnu

    std::string couleur;
    char caractere;

    switch (caseType) {
    case typeCase::vide:
        couleur = estGrilleAdversaire ? YELLOW : VERT; // Rouge pour adversaire, bleu pour joueur
        caractere = 'O';
        break;
    case typeCase::bateau:
        couleur = RESET;
        caractere = 'B';
        break;
    case typeCase::touche:
        couleur = RED;
        caractere = 'X';
        break;
    case typeCase::eau:
        couleur = CYAN;
        caractere = '~';
        break;
    default:
        couleur = GREY;
        caractere = '?';
        break;
    }

    std::cout << couleur << caractere << RESET;
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
    std::cout << std::endl << espace 
        << "            Entrez la ligne: ";
    std::cin >> ligne; std::cout << std::endl;
    std::cout << espace 
        << "            Entrez la colonne: ";
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

std::string CoreGame::serialisationJoueur() const {
    // Convertit l'\202tat actuel de la grille en une chaîne de caractères.
    std::string result;
    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            result += std::to_string(static_cast<int>(grille[i][j])) + " ";
        }
        result += "\n";
    }
    return result;
}

std::string CoreGame::serialisationAdversaire() const {
    // Convertit l'\202tat actuel de la grille en une chaîne de caractères.
    std::string result;
    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            result += std::to_string(static_cast<int>(grilleAdversaire[i][j])) + " ";
        }
        result += "\n";
    }
    return result;
}

bool CoreGame::deserialisation(const std::string& trame) {
    std::istringstream iss(trame);
    std::string ligneTrame;
    int numLigne = 0;

    while (std::getline(iss, ligneTrame) && numLigne < nbLig) {
        std::istringstream issLigne(ligneTrame);
        int valeur;
        int numColonne = 0;

        while (issLigne >> valeur && numColonne < nbCol) {
            grille[numLigne][numColonne] = static_cast<typeCase>(valeur);
            numColonne++;
        }

        numLigne++;
    }

    return (numLigne == nbLig);
}

bool CoreGame::deserialisationAdversaire(const std::string& trame) {
    std::istringstream iss(trame);
    std::string ligneTrame;
    int numLigne = 0;

    while (std::getline(iss, ligneTrame) && numLigne < nbLig) {
        std::istringstream issLigne(ligneTrame);
        int valeur;
        int numColonne = 0;

        while (issLigne >> valeur && numColonne < nbCol) {
            grilleAdversaire[numLigne][numColonne] = static_cast<typeCase>(valeur);
            numColonne++;
        }

        numLigne++;
    }

    return (numLigne == nbLig);
}


bool CoreGame::caseAdjacenteLibre(int ligne, int colonne, typeCase(*grilleCible)[nbCol]) {
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

bool CoreGame::estPlacementValide(typeBateau bateau, int ligne, int colonne, int direction) {
    int tailleBateau = static_cast<int>(bateau);

    // Vérifier si le bateau sort de la grille
    if (direction == 0 && ligne + tailleBateau > nbLig) return false; // Vertical
    if (direction == 1 && colonne + tailleBateau > nbCol) return false; // Horizontal

    // Vérifier si le bateau chevauche un autre bateau
    for (int i = 0; i < tailleBateau; ++i) {
        int l = ligne + (direction == 0 ? i : 0);
        int c = colonne + (direction == 1 ? i : 0);
        if (grille[l][c] != typeCase::vide) return false;
    }

    return true; // Le placement est valide
}


void CoreGame::placerBateau(typeBateau bateau, int ligne, int colonne, int direction) {
    if (estPlacementValide(bateau, ligne, colonne, direction)) {
        int tailleBateau = static_cast<int>(bateau);

        // Placez le bateau sur la grille en fonction de la direction
        for (int i = 0; i < tailleBateau; ++i) {
            int l = ligne + (direction == 0 ? 0 : i); // Direction verticale
            int c = colonne + (direction == 1 ? 0 : i); // Direction horizontale

            grille[l][c] = typeCase::bateau; // Assumer que cette méthode place les bateaux sur la grille du joueur
        }
    }
}




bool CoreGame::attaqueJoueur(int ligne, int colonne) {
    // Si la case a déjà été attaquée, ne rien faire
    if (grilleAdversaire[ligne][colonne] == typeCase::touche || grilleAdversaire[ligne][colonne] == typeCase::eau) {
        return false;
    }

    // Vérification simple de la case attaquée
    if (grilleAdversaire[ligne][colonne] == typeCase::bateau) {
        grilleAdversaire[ligne][colonne] = typeCase::touche; // Marquer la case comme touchée sur la grille de l'adversaire
        verifierBateauCoule(ligne, colonne, true); // Vérifier si un bateau a été coulé sur la grille de l'adversaire
        return true;
    }
    else {
        grilleAdversaire[ligne][colonne] = typeCase::eau; // Marquer la case comme eau (manqué) sur la grille de l'adversaire
        return false;
    }
}




void CoreGame::attaqueIA() {
    int ligne, colonne;
    do {
        ligne = std::rand() % nbLig;
        colonne = std::rand() % nbCol;
    } while (grille[ligne][colonne] == typeCase::touche || grille[ligne][colonne] == typeCase::eau); // \202viter les cases d\202jà attaqu\202es
    // L'IA attaque une case
    if (grille[ligne][colonne] == typeCase::bateau) {
        std::cout << espace5 << "\033[31mL'IA a touch\202 un bateau !\033[0m" << std::endl << std::endl;
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
        //std::cout  << "MOI: " << std::endl << serialisationJoueur() << std::endl;
        //std::cout  << "ADVERSAIRE: " << std::endl << serialisationAdversaire();
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
    bool joueurPerdu = true, adversairePerdu = true;

    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            if (grille[i][j] == typeCase::bateau) {
                joueurPerdu = false;
            }
            if (grilleAdversaire[i][j] == typeCase::bateau) {
                adversairePerdu = false;
            }
        }
    }

    if (joueurPerdu) {
        std::cout << "Vous avez perdu la partie." << std::endl;
    }
    else if (adversairePerdu) {
        std::cout << "Vous avez gagn\202 la partie !" << std::endl;
    }

    return joueurPerdu || adversairePerdu;
}


void CoreGame::verifierBateauCoule(int ligne, int colonne, bool pourAdversaire) {
    typeCase(*grilleCible)[nbCol] = pourAdversaire ? grilleAdversaire : grille;

    // Vérifier d'abord si la case contient un bateau touché
    if (grilleCible[ligne][colonne] != typeCase::touche) {
        return; // Si la case n'est pas un bateau touché, aucune vérification supplémentaire n'est nécessaire
    }

    // Vérifiez s'il reste des parties de bateau non touchées autour de cette case
    bool bateauCoulé = true;

    // Vérifier les cases adjacentes
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int voisinLigne = ligne + i;
            int voisinColonne = colonne + j;

            // Vérifier les limites de la grille
            if (voisinLigne >= 0 && voisinLigne < nbLig && voisinColonne >= 0 && voisinColonne < nbCol) {
                if (grilleCible[voisinLigne][voisinColonne] == typeCase::bateau) {
                    bateauCoulé = false; // Il reste des parties non touchées du bateau
                    break;
                }
            }
        }
        if (!bateauCoulé) break;
    }

    // Mettre à jour le compteur si un bateau a été coulé
    if (bateauCoulé) {
        ++bateauxCoulés;
    }
}

// obselete
void CoreGame::afficherBateauxCoules() const {
    //std::cout << espace << "Bateaux coul\202s: " << bateauxCoulés << " sur " << nombreTotalBateaux << std::endl;
}
